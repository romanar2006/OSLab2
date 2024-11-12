cmake_minimum_required(VERSION 3.10)
project(OSLab2.1)

set(CMAKE_CXX_STANDARD 17)

add_library(OSLab2.1 OSLab2.1.cpp OSLab2.1.h)
add_executable(OSLab2-1 OSLab2.1.cpp)
target_include_directories(OSLab2.1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
