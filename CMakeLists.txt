cmake_minimum_required(VERSION 3.10)

project(Clawk)

# Specify the required C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directory for the project
include_directories(include)

# Enable testing functionality
enable_testing()

# Add the test directory
add_subdirectory(googletest)
add_subdirectory(tests)

add_library(Clawk INTERFACE
        include/OutputInterface.hpp)
target_include_directories(Clawk INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
