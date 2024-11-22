cmake_minimum_required(VERSION 3.14)
project(NeuroClues)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

# Add include directories for headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add the main application executable
add_executable(main src/main.cpp src/CSVHandler.cpp src/JSONHandler.cpp src/FactoryUtils.cpp)
add_compile_definitions(TEST_DATA_PATH="${CMAKE_SOURCE_DIR}/data")
target_link_libraries(main PRIVATE gtest gtest_main)

# Define the test executables, link libraries, and link to ctest
add_executable(test_CSVHandler tests/test_CSVHandler.cpp src/JSONHandler.cpp src/CSVHandler.cpp src/FactoryUtils.cpp)
target_compile_definitions(test_CSVHandler PRIVATE TEST_DATA_PATH="${CMAKE_SOURCE_DIR}/data")
target_link_libraries(test_CSVHandler PRIVATE gtest gtest_main)
add_test(NAME CSVHandlerTests COMMAND test_CSVHandler)

add_executable(test_JSONHandler tests/test_JSONHandler.cpp src/JSONHandler.cpp src/CSVHandler.cpp src/FactoryUtils.cpp)
target_compile_definitions(test_JSONHandler PRIVATE TEST_DATA_PATH="${CMAKE_SOURCE_DIR}/data")
target_link_libraries(test_JSONHandler PRIVATE gtest gtest_main)
add_test(NAME JSONHandlerTests COMMAND test_JSONHandler)

add_executable(test_FileHandlerFactory tests/test_FileHandlerFactory.cpp src/CSVHandler.cpp src/JSONHandler.cpp src/FactoryUtils.cpp)
target_link_libraries(test_FileHandlerFactory PRIVATE gtest gtest_main)
add_test(NAME FileHandlerFactoryTests COMMAND test_FileHandlerFactory)