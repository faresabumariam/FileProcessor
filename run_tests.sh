#!/bin/bash

# Create a build directory and navigate into it
mkdir -p build
cd build

# Configure and build the project
cmake -DCMAKE_BUILD_TYPE=Debug ..
make

# Run all test executables
./test_CSVHandler
./test_JSONHandler
./test_FileHandler

# Run all tests with ctest
ctest --output-on-failure

# Generate coverage data
lcov --capture --directory . --output-file coverage.info --ignore-errors mismatch,unexecuted,tracefile
lcov --remove coverage.info '/usr/*' 'build/*' 'gtest/*' 'tests/*' 'include/nlohmann/*' --output-file coverage_filtered.info
genhtml coverage_filtered.info --output-directory coverage_report

# Open the coverage report
if [ -f coverage_report/index.html ]; then
    xdg-open coverage_report/index.html
else
    echo "Coverage report not found. Check for errors."
fi
