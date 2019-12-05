cmake_minimum_required(VERSION 3.1)

find_package(fmt)

add_executable(hello_fmt hello_fmt.cpp)
target_link_libraries(hello_fmt fmt::fmt)