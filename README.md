# Overview

This project is a C++ application designed to process and analyze CSV and JSON files. It uses a factory design pattern to create handlers for different file types, ensuring scalability and modularity. The project includes unit tests for core functionality and integration tests for end-to-end workflow validation.

This project offers easy extensibility to add support for processing more file types in the future.

---

## Features

- **Factory Design Pattern**: Dynamically creates handlers for CSV and JSON file types.
- **File Processing**: 
  - Adds metadata and performs calculations such as:
    - `blink_rate_intensity` for CSV files.
    - `retina_focus_intensity` for JSON files.
  - Supports modular processing and validation.
- **Unit and Integration Testing**: Comprehensive tests implemented using the Google Test framework.
- **Code Coverage**: Code coverage reporting using `lcov` and `genhtml` tools.

---

## Dependencies

- **C++ Compiler**: GCC 9+ or Clang
- **CMake**: Version 3.14 or higher
- **Google Test Framework**: Fetched automatically during the build process.
- **LCOV**: For generating code coverage reports.

---

## Build and Run

### **Manual Instructions**

#### Steps:
1. Clone the repository (if applicable):
    ```bash
    git clone <repository-url>
    cd NeuroClues
    ```

2. Create a build directory:
    ```bash
    mkdir build
    cd build
    ```

3. Run CMake to configure the project:
    ```bash
    cmake -DCMAKE_BUILD_TYPE=Debug ..
    ```

4. Compile the project:
    ```bash
    make
    ```

5. Run the main application:
    ```bash
    ./main
    ```

6. Run tests:
    ```bash
    ctest --output-on-failure
    ```
7. Run specific:
    ```bash
    ./test_CSVHandler
    ./test_JSONHandler
    ./test_FileHandler
    ```

8. Generate code coverage reports:
    ```bash
    lcov --capture --directory . --output-file coverage.info
    lcov --remove coverage.info '/usr/*' 'build/*' 'gtest/*' 'tests/*' 'include/json.hpp' --output-file coverage_filtered.info
    genhtml coverage_filtered.info --output-directory coverage_report
    ```
    Open the report in your default browser:
    ```bash
    xdg-open coverage_report/index.html
    ```

---

## Automated Scripts

You can use the provided shell scripts to simplify building, running, and testing the application.

### *`run_main.sh` and *`run_tests.sh` Script**
These scripts automates the following steps:
- Builds the project.
- Runs the main or all tests.
- Generates a code coverage report (for `run_tests.sh`).

#### Usage:
1. Make the script executable:
   ```bash
   chmod +x run_main.sh
   ./run_main.sh
    ```

    or 

     ```bash
   chmod +x run_tests.sh
   ./run_tests.sh
    ```


