cmake_minimum_required(VERSION 3.18)

project(PricingEngine VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include(CTest)
enable_testing()

add_subdirectory(PricingEngine)

