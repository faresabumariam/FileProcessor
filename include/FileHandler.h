#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>

class FileHandler {
public:
    virtual ~FileHandler() = default;
    virtual void readFile(const std::string& filename) = 0;
    virtual void processData() = 0;
    virtual void writeFile(const std::string& filename) = 0;
};

#endif