cmake_minimum_required(VERSION 3.10)
project(OSLab2.1_tests)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(OSLab2.1_tests OSLab2.1_tests/test.cpp)

target_link_libraries(OSLab2.1_tests PUBLIC gtest_main OSLab2.1)

target_include_directories(OSLab2.1_tests PUBLIC ${CMAKE_SOURCE_DIR})

include(GoogleTest)
add_test(NAME OSLab2.1_tests COMMAND OSLab2.1_tests)

