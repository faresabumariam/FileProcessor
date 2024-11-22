#ifndef FILEHANDLERFACTORY_H
#define FILEHANDLERFACTORY_H

#include "FileHandler.h"
#include <string>
#include <memory>

class FileHandlerFactory {
public:
    virtual std::unique_ptr<FileHandler> createHandler() const = 0;
    virtual ~FileHandlerFactory() = default;
};

#endif
