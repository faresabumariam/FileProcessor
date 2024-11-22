#include "FileHandlerFactory.h"
#include "CSVHandler.h"

class CSVHandlerFactory : public FileHandlerFactory {
public:
    std::unique_ptr<FileHandler> createHandler() const override {
        return std::make_unique<CSVHandler>();
    }
};
