cmake_minimum_required(VERSION 3.10)

add_executable(TestClawk TestClawk.cpp)
target_link_libraries(TestClawk PUBLIC gtest_main Clawk)

add_test(NAME TestClawk COMMAND TestClawk)

# Include the headers in the tests directory if needed
target_include_directories(TestClawk PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})