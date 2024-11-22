#include "FileHandlerFactory.h"
#include "JSONHandler.h"

class JSONHandlerFactory : public FileHandlerFactory {
public:
    std::unique_ptr<FileHandler> createHandler() const override {
        return std::make_unique<JSONHandler>();
    }
};