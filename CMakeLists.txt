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
        tests/include/TestAllDivisions.hpp
        tests/include/testOnPulseFunction.hpp
        tests/include/TestClawk.hpp
        include/Clawk.hpp)
target_include_directories(Clawk INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(ARDUINO_PREFIX "Arduino")
# Find all hpp files in include directory and set them as HPP_FILES
file(GLOB ORIGINAL_INCLUDES "${CMAKE_SOURCE_DIR}/include/*.hpp")
set(ARDUINO_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/arduino/main/include/")
# For hpp_file in hpp_files
foreach(ORIGINAL_INCLUDE ${ORIGINAL_INCLUDES})
    # Get the file name without the full path or extension
    get_filename_component(FILE_NAME ${ORIGINAL_INCLUDE} NAME_WE)

    # From the new name with .h now instead
    set(NEW_FILE_NAME "${ARDUINO_PREFIX}${FILE_NAME}.h")
    set(ARDUINO_INCLUDE_PATH "${ARDUINO_INCLUDE_DIR}${NEW_FILE_NAME}")

    # Copy the file with the new extension
    configure_file("${ORIGINAL_INCLUDE}" "${ARDUINO_INCLUDE_PATH}" COPYONLY)
endforeach()