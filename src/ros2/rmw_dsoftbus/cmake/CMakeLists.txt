# Copyright (c) 2024 ROS2 KaihongOS Port Project
# CMakeLists.txt for local testing of rmw_dsoftbus components
#
# Usage:
#   mkdir -p build && cd build
#   cmake ../cmake
#   make
#   ./test_cdr_serializer

cmake_minimum_required(VERSION 3.10)
project(rmw_dsoftbus_test CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/../include
    ${CMAKE_SOURCE_DIR}/../mock_includes
)

# CDR Serializer test (standalone, no dependencies)
add_executable(test_cdr_serializer
    ${CMAKE_SOURCE_DIR}/../test/test_cdr_serializer.cpp
    ${CMAKE_SOURCE_DIR}/../src/cdr_serializer.cpp
)

target_compile_options(test_cdr_serializer PRIVATE -Wall -Wextra)

# Enable testing
enable_testing()
add_test(NAME cdr_serializer_test COMMAND test_cdr_serializer)
