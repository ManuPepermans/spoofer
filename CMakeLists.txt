cmake_minimum_required(VERSION 3.9)
project(spoofer)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE CMAKE_SOURCE_DIR)


add_executable(spoofer main.cpp connection.h json.hpp)

target_include_directories(spoofer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
