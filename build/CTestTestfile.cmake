# CMake generated Testfile for 
# Source directory: /home/fares/Desktop/NeuroClues
# Build directory: /home/fares/Desktop/NeuroClues/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(CSVHandlerTests "/home/fares/Desktop/NeuroClues/build/test_CSVHandler")
set_tests_properties(CSVHandlerTests PROPERTIES  _BACKTRACE_TRIPLES "/home/fares/Desktop/NeuroClues/CMakeLists.txt;37;add_test;/home/fares/Desktop/NeuroClues/CMakeLists.txt;0;")
add_test(JSONHandlerTests "/home/fares/Desktop/NeuroClues/build/test_JSONHandler")
set_tests_properties(JSONHandlerTests PROPERTIES  _BACKTRACE_TRIPLES "/home/fares/Desktop/NeuroClues/CMakeLists.txt;42;add_test;/home/fares/Desktop/NeuroClues/CMakeLists.txt;0;")
add_test(FileHandlerFactoryTests "/home/fares/Desktop/NeuroClues/build/test_FileHandlerFactory")
set_tests_properties(FileHandlerFactoryTests PROPERTIES  _BACKTRACE_TRIPLES "/home/fares/Desktop/NeuroClues/CMakeLists.txt;46;add_test;/home/fares/Desktop/NeuroClues/CMakeLists.txt;0;")
subdirs("_deps/googletest-build")
