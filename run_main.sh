#!/bin/bash

# Create a build directory and navigate into it
rm -rf build
mkdir -p build
cd build

# Run CMake to configure the project and build it
cmake ..
make

# Run the executable
./main


