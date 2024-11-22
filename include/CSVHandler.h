#ifndef CSVHANDLER_H
#define CSVHANDLER_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <iomanip>
#include "FileHandler.h"

class CSVHandler : public FileHandler{
private:
    std::vector<std::string> data;

public:
    const std::vector<std::string>& getData() const;

    void readFile(const std::string& filename) override;
    void processData() override;
    void writeFile(const std::string& filename) override; 
    
};

#endif