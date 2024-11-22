#include <iostream>
#include <memory>
#include <stdexcept>
#include "FactoryUtils.h"

// Function to test handler creation and file processing
void runFileHandler(const std::string& filename) {
    try {
        // Get the appropriate factory based on the file extension
        std::unique_ptr<FileHandlerFactory> factory = getFactory(filename);
        
        // Create the corresponding handler using the factory
        std::unique_ptr<FileHandler> handler = factory->createHandler();
        
        // Use the handler to process the file (for testing, just call readFile)
        handler->readFile(filename);
        handler->processData();
        handler->writeFile( filename);
        
        std::cout << "File processing completed for: " << filename << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error processing file " << filename << ": " << e.what() << std::endl;
    }
}

int main() {
    // Test with both a CSV and JSON file
    std::string csvFile = "../data/sample.csv";
    std::string jsonFile = "../data/sample.json";
    
    // Test file processing for the CSV file
    runFileHandler(csvFile);
    
    // Test file processing for the JSON file
    runFileHandler(jsonFile);
    
    return 0;
}
