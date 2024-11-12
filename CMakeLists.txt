cmake_minimum_required(VERSION 3.10)
project(OSLab2.1)

set(CMAKE_CXX_STANDARD 17)

# Подключаем модуль FetchContent
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

add_subdirectory(OSLab2.1)
add_subdirectory(OSLab2.1_tests)
target_include_directories(OSLab2.1 PUBLIC ${CMAKE_SOURCE_DIR})
