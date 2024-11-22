#include "JSONHandler.h"
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

void JSONHandler::readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open JSON file: " + filename);
    }

    try {
        file >> jsonData;  // Parse JSON
    } catch (nlohmann::json::parse_error& e) {
        throw;  // Re-throw parse errors for malformed JSON
    }
}


void JSONHandler::processData() {
    ensureArray();

    // Get the current time
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);

    // Convert time_t to tm as UTC (Coordinated Universal Time)
    std::tm now_tm = *gmtime(&now_c);
    std::stringstream ss;
    ss << std::put_time(&now_tm, "%Y-%m-%dT%H:%M:%SZ");  // Format the time

    // Process each object in the array
    for (auto& item : jsonData) {
        if (item.contains("metrics") && item["metrics"].is_object()) {
            auto& metrics = item["metrics"];

            if (metrics.contains("pupilSize") && metrics.contains("blinkRate")) {
                double pupilSize = metrics["pupilSize"];
                double blinkRate = metrics["blinkRate"];
                metrics["blink_rate_intensity"] = pupilSize * blinkRate;  // Add to metrics
            }

            if (metrics.contains("retinaAngleDegrees")) {
                double retinaAngle = metrics["retinaAngleDegrees"];
                double pupilSize = metrics["pupilSize"];
                item["retina_focus_intensity"] = pupilSize * retinaAngle / 100.0;  // Add to parent object
            }
        }

        // Add global processed metadata
        item["processed"] = true;
        item["processed_timestamp"] = ss.str();
    }
}


void JSONHandler::writeFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to write JSON file: " + filename);
    }
    file << jsonData.dump(4);
    file.close();
}

void JSONHandler::ensureArray() {
    if (!jsonData.is_array()) {
        nlohmann::json temp = nlohmann::json::array();
        temp.push_back(jsonData);
        jsonData = temp;
    }
}

const nlohmann::json& JSONHandler::getJsonData() const {
    return jsonData;
}