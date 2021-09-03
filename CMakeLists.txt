cmake_minimum_required(VERSION 3.18)

project(PricingEngine VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_SOURCE_DIR build)
set(CMAKE_BINARY_DIR build)

include(CTest)
enable_testing()

add_subdirectory(PricingEngine)

