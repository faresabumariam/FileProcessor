#ifndef FACTORYUTILS_H
#define FACTORYUTILS_H


#include "CSVHandlerFactory.h"
#include "JSONHandlerFactory.h"
#include <memory>
#include <stdexcept>
#include <string>
#include <algorithm>

std::string getExtension(const std::string& filename);
std::unique_ptr<FileHandlerFactory> getFactory(const std::string& filename);

#endif
