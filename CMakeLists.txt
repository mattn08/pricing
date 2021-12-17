cmake_minimum_required(VERSION 3.18)

project(PricingEngine VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/release/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/release/lib)

include(CTest)
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

add_subdirectory(PricingEngine)
add_subdirectory(Testing)

