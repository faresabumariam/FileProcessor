#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include "FileHandler.h"
#include <nlohmann/json.hpp>
#include <string>

class JSONHandler : public FileHandler {
private:
    nlohmann::json jsonData;

public:
    void readFile(const std::string& filename) override;
    void processData() override;
    void writeFile(const std::string& filename) override;
    void ensureArray();
    const nlohmann::json& getJsonData() const;
};

#endif
