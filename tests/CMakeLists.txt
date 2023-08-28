cmake_minimum_required(VERSION 3.10)


add_executable(TestClawk TestClawk.cpp)
target_link_libraries(TestClawk PUBLIC gtest_main Clawk)

add_test(NAME TestClawk COMMAND TestClawk)

