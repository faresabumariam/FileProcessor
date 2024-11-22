#include "CSVHandler.h"

const std::vector<std::string>& CSVHandler::getData() const {
    return data;
}


void CSVHandler::readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open CSV file: " + filename);
    }
    
    std::string line;
    while (getline(file, line)) {
        data.push_back(line);
    }
    file.close();

    // Optionally print the first line (header) to verify
    std::cout << "Header: " << data.front() << std::endl;
}


void CSVHandler::processData() {
    if (data.empty()) return;

    // Define new columns to be added dynamically
    std::vector<std::string> newColumns = {"processed", "processed_timestamp", "retina_focus_intensity"};

    // Split the header row and append new columns
    std::stringstream headerStream(data[0]);
    std::string cell;
    std::vector<std::string> header;

    while (std::getline(headerStream, cell, ',')) {
        header.push_back(cell);
    }

    // Append new column headers
    for (const auto& col : newColumns) {
        header.push_back(col);
    }

    // Recreate the header row
    std::ostringstream headerOutput;
    for (size_t i = 0; i < header.size(); ++i) {
        headerOutput << header[i];
        if (i < header.size() - 1) headerOutput << ",";
    }
    data[0] = headerOutput.str();

    // Get current time for processing
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *gmtime(&now_c);
    std::stringstream ss;
    ss << std::put_time(&now_tm, "%Y-%m-%dT%H:%M:%SZ"); // ISO 8601 format

    // Process each data row (skip the header row)
    for (size_t i = 1; i < data.size(); ++i) {
        std::stringstream rowStream(data[i]);
        std::vector<std::string> row;

        // Split the row into individual cells
        while (std::getline(rowStream, cell, ',')) {
            row.push_back(cell);
        }

        // Extract necessary values
        double retinaAngle = std::stod(row[2]);  // Assuming 3rd column is retinaAngleDegrees
        double pupilSize = std::stod(row[3]);   // Assuming 4th column is pupilSize

        // Calculate retina focus intensity
        double retinaFocusIntensity = pupilSize * retinaAngle / 100.0;

        // Append new calculated values to the row
        row.push_back("true");                     // Processed flag
        row.push_back(ss.str());                   // Processed timestamp
        row.push_back(std::to_string(retinaFocusIntensity));  // Retina focus intensity

        // Recreate the row as a string
        std::ostringstream rowOutput;
        for (size_t j = 0; j < row.size(); ++j) {
            rowOutput << row[j];
            if (j < row.size() - 1) rowOutput << ",";
        }
        data[i] = rowOutput.str();
    }
}


void CSVHandler::writeFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to write CSV file: " + filename);
    }
    
    for (const auto& line : data) {
        file << line << "\n";
    }
    file.close();
}
