#include "FactoryUtils.h"
#include <algorithm>
#include <stdexcept>

std::string getExtension(const std::string& filename) {
    size_t pos = filename.find_last_of(".");
    if (pos != std::string::npos && pos != 0 && pos != filename.size() - 1) {
        return filename.substr(pos + 1); // Extract the part after the last dot
    }
    return "";
}

std::unique_ptr<FileHandlerFactory> getFactory(const std::string& filename) {
    std::string extension = getExtension(filename);

    // Lowercase the extension to ensure case insensitivity
    std::transform(extension.begin(), extension.end(), extension.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    if (extension == "csv") {
        return std::make_unique<CSVHandlerFactory>();
    } else if (extension == "json") {
        return std::make_unique<JSONHandlerFactory>();
    } else {
        throw std::invalid_argument("Unsupported file type: " + extension);
    }
}
