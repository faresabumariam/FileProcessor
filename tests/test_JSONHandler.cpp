#include <gtest/gtest.h>
#include "JSONHandler.h"
#include <fstream>
#include <iostream>
#include "FactoryUtils.h"



TEST(JSONHandlerTest, CanReadValidJSON) {
    JSONHandler handler;
    std::string testFile = std::string(TEST_DATA_PATH) + "/sample.json";
    EXPECT_NO_THROW(handler.readFile(testFile));
}

TEST(JSONHandlerTest, FailsOnMalformedJSON) {
    JSONHandler handler;
    std::string testFile = std::string(TEST_DATA_PATH) + "/malformed.json";
    EXPECT_THROW(handler.readFile(testFile), nlohmann::json::parse_error);
}

TEST(JSONHandlerTest, FailsOnMissingFile) {
    JSONHandler handler;
    std::string testFile = std::string(TEST_DATA_PATH) + "/missing.json";
    EXPECT_THROW(handler.readFile(testFile), std::runtime_error);
}


TEST(JSONHandlerTest, CanWriteValidJSON) {
    JSONHandler handler;
    std::string testFile = std::string(TEST_DATA_PATH) + "/sample.json";
    handler.readFile(testFile);
    handler.processData();

    // Create a temp file for testing and cleanup
    std::string tempFile = "temp_output.json";
    EXPECT_NO_THROW(handler.writeFile(tempFile));
    std::remove(tempFile.c_str());

}

TEST(JSONHandlerTest, AddsValidProcessedTimestamp) {
    JSONHandler handler;

    // Path to the test JSON file
    std::string testFile = std::string(TEST_DATA_PATH) + "/sample.json";
    handler.readFile(testFile);  // Read from file
    handler.processData();
    const auto& jsonData = handler.getJsonData();  // Use a getter to validate

    ASSERT_TRUE(jsonData.is_array());
    ASSERT_TRUE(jsonData[0].contains("processed_timestamp"));

    // Validate timestamp format
    std::string timestamp = jsonData[0]["processed_timestamp"];
    EXPECT_TRUE(timestamp.find("T") != std::string::npos);  // Contains 'T' separator
    EXPECT_TRUE(timestamp.find("Z") != std::string::npos);  // Ends with 'Z'
}

TEST(JSONHandlerTest, HandlesMissingFieldsGracefully) {
    JSONHandler handler;

    // Path to the test JSON file with missing fields
    std::string testFile = std::string(TEST_DATA_PATH) + "/missing_fields.json";
    handler.readFile(testFile);  // Read from file
    EXPECT_NO_THROW(handler.processData());
    const auto& jsonData = handler.getJsonData();  // Use a getter to validate

    ASSERT_TRUE(jsonData.is_array());

    // Validate the first object
    const auto& obj1 = jsonData[0];
    EXPECT_FALSE(obj1["metrics"].contains("blink_rate_intensity"));  // No intensity due to missing pupilSize
    EXPECT_EQ(obj1["processed"], true);

    // Validate the second object
    const auto& obj2 = jsonData[1];
    EXPECT_FALSE(obj2.contains("retina_focus_intensity"));  // No metrics, no processing
    EXPECT_EQ(obj2["processed"], true);  // Still adds processed flag and timestamp
}

TEST(JSONHandlerTest, FullWorkflowIntegration) {
    std::string testFile = std::string(TEST_DATA_PATH) + "/sample.json";
   
    std::unique_ptr<FileHandlerFactory> factory = getFactory(testFile);
    std::unique_ptr<FileHandler> handler = factory->createHandler();
        
    handler->readFile(testFile);
    handler->processData();
    
    // use temp file for testing and cleanup later
    std::string tempFile = "temp_output.csv";
    EXPECT_NO_THROW(handler->writeFile(tempFile));


    // validate the written file
    std::ifstream output(tempFile);
    ASSERT_TRUE(output.is_open());
    nlohmann::json resultJson;
    output >> resultJson;  // Load the written JSON
    output.close();

    ASSERT_TRUE(resultJson.is_array());
    EXPECT_TRUE(resultJson[0].contains("processed"));
    EXPECT_TRUE(resultJson[0].contains("processed_timestamp"));
    EXPECT_TRUE(resultJson[0]["metrics"].contains("blink_rate_intensity"));

    // Cleanup
    std::remove(tempFile.c_str());
}

