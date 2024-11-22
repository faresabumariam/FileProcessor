#include <gtest/gtest.h>
#include "CSVHandler.h"
#include <fstream>
#include <iostream>
#include "FactoryUtils.h"


TEST(CSVHandlerTest, CanReadValidCSV) {
    CSVHandler handler;
    std::string testFile = std::string(TEST_DATA_PATH) + "/sample.csv";
    EXPECT_NO_THROW(handler.readFile(testFile));
}

TEST(CSVHandlerTest, FailsOnMissingCSVFile) {
    CSVHandler handler;
    std::string testFile = std::string(TEST_DATA_PATH) + "/missing.csv";
    EXPECT_THROW(handler.readFile(testFile), std::runtime_error);
}

TEST(CSVHandlerTest, CanWriteProcessedCSV) {
    CSVHandler handler;
    std::string testFile = std::string(TEST_DATA_PATH) + "/sample.csv";
    handler.readFile(testFile);
    handler.processData();

    //create temp file and clean up
    std::string tempFile = "temp_output.csv";
    EXPECT_NO_THROW(handler.writeFile(tempFile));
    std::remove(tempFile.c_str());
}

TEST(CSVHandlerTest, AddsProcessedColumnsToHeader) {
    CSVHandler handler;
    std::string testFile = std::string(TEST_DATA_PATH) + "/sample.csv";
    handler.readFile(testFile);
    handler.processData();

    const auto& data = handler.getData();
    EXPECT_FALSE(data.empty());  // Ensure the data is not empty

    // Verify the headers include the new columns
    EXPECT_TRUE(data[0].find("processed") != std::string::npos);
    EXPECT_TRUE(data[0].find("processed_timestamp") != std::string::npos);
    EXPECT_TRUE(data[0].find("retina_focus_intensity") != std::string::npos);
}

TEST(CSVHandlerTest, CalculatesRetinaFocusIntensity) {
    CSVHandler handler;
    std::string testFile = std::string(TEST_DATA_PATH) + "/sample.csv";
    handler.readFile(testFile);
    handler.processData();

    const auto& data = handler.getData();
    ASSERT_GE(data.size(), 2);  // Ensure at least one data row exists

    // Split first data row into cells
    std::stringstream rowStream(data[1]);
    std::string cell;
    std::vector<std::string> cells;
    while (std::getline(rowStream, cell, ',')) {
        cells.push_back(cell);
    }

    // Extract and validate the retina focus intensity
    double expectedRetinaFocusIntensity = 3.2 * 45.0 / 100.0;  // Example for row 1
    EXPECT_NEAR(std::stod(cells.back()), expectedRetinaFocusIntensity, 0.001);  // Compare with a tolerance
}


TEST(CSVHandlerTest, AddsCorrectTimestampFormat) {
    CSVHandler handler;
    std::string testFile = std::string(TEST_DATA_PATH) + "/sample.csv";
    handler.readFile(testFile);
    handler.processData();

    const auto& data = handler.getData();
    ASSERT_GE(data.size(), 2);  // Ensure at least one data row exists

    // Split the second row (first data row) into cells
    std::stringstream rowStream(data[1]);
    std::string cell;
    std::vector<std::string> cells;
    while (std::getline(rowStream, cell, ',')) {
        cells.push_back(cell);
    }

    // Verify the timestamp format in the processed row
    std::string timestamp = cells[cells.size() - 2];  // Second last column
    EXPECT_TRUE(timestamp.find("T") != std::string::npos);  // Ensure 'T' separator is present
    EXPECT_TRUE(timestamp.find("Z") != std::string::npos);  // Ensure 'Z' suffix is present
}

TEST(CSVHandlerTest, FullWorkflowWithCSV) {
    std::string testFile = std::string(TEST_DATA_PATH) + "/sample.csv";

    std::unique_ptr<FileHandlerFactory> factory = getFactory(testFile);
    std::unique_ptr<FileHandler> handler = factory->createHandler();
        
    handler->readFile(testFile);
    handler->processData();
    
    // use temp file for testing and cleanup later
    std::string tempFile = "temp_output.csv";
    EXPECT_NO_THROW(handler->writeFile(tempFile));

    //Validate the contents of the written file
    std::ifstream output(tempFile);
    std::string line;
    ASSERT_TRUE(output.is_open());
    ASSERT_TRUE(std::getline(output, line));  // Read the header
    EXPECT_TRUE(line.find("processed") != std::string::npos);
    EXPECT_TRUE(line.find("processed_timestamp") != std::string::npos);
    EXPECT_TRUE(line.find("retina_focus_intensity") != std::string::npos);

    //Cleanup
    output.close();
    std::remove(tempFile.c_str());
}
