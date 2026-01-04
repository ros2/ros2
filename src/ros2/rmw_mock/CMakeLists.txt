# Copyright (c) 2026 ROS2 KaihongOS Port Project
# Licensed under the Apache License, Version 2.0
#
# CMakeLists.txt for local development and testing
# Note: Primary build system is GN for OHOS, this is for convenience

cmake_minimum_required(VERSION 3.14)
project(rmw_mock VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find ROS2 dependencies (for local builds)
find_package(rmw QUIET)
find_package(rcutils QUIET)

# If ROS2 packages not found, use local mock headers
if(NOT rmw_FOUND)
  message(WARNING "rmw package not found, using mock headers")
  set(RMW_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/../ros2/src/ros2/rmw/rmw/include")
endif()

if(NOT rcutils_FOUND)
  message(WARNING "rcutils package not found, using mock headers")
  set(RCUTILS_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/../ros2/src/ros2/rcutils/include")
endif()

# Additional ROS2 include directories
set(ROSIDL_INCLUDE_DIRS
  "${CMAKE_SOURCE_DIR}/../ros2/src/ros2/rosidl/rosidl_runtime_c/include"
  "${CMAKE_SOURCE_DIR}/../ros2/src/ros2/rosidl/rosidl_typesupport_interface/include"
  "${CMAKE_SOURCE_DIR}/../ros2/src/ros2/rosidl_dynamic_typesupport/include"
)

#==============================================================================
# Library: librmw_mock.so
#==============================================================================

add_library(rmw_mock SHARED
  # Level 1
  src/level1/rmw_identifier.cpp
  src/level1/rmw_init.cpp
  src/level1/rmw_node.cpp
  # Level 2
  src/level2/mock_router.cpp
  src/level2/rmw_publisher.cpp
  src/level2/rmw_subscription.cpp
  src/level2/rmw_stubs.cpp
  # Level 3
  src/level3/rmw_wait_set.cpp
  src/level3/rmw_guard_condition.cpp
  src/level3/rmw_wait.cpp
  # Stubs for rmw/rcutils helper functions
  src/rmw_rcutils_stubs.cpp
)

target_include_directories(rmw_mock
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    ${RMW_INCLUDE_DIRS}
    ${RCUTILS_INCLUDE_DIRS}
    ${ROSIDL_INCLUDE_DIRS}
)

target_compile_definitions(rmw_mock PRIVATE RMW_MOCK_BUILDING_DLL)

target_compile_options(rmw_mock PRIVATE
  -Wall
  -Wextra
  -Wno-unused-parameter
  -fvisibility=hidden
)

# Link against found packages or nothing (zero deps)
if(rmw_FOUND)
  target_link_libraries(rmw_mock PRIVATE rmw::rmw)
endif()
if(rcutils_FOUND)
  target_link_libraries(rmw_mock PRIVATE rcutils::rcutils)
endif()

#==============================================================================
# Test: Level 1
#==============================================================================

add_executable(test_init_node test/level1/test_init_node.cpp)
target_link_libraries(test_init_node rmw_mock)
target_include_directories(test_init_node PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${RMW_INCLUDE_DIRS}
  ${RCUTILS_INCLUDE_DIRS}
  ${ROSIDL_INCLUDE_DIRS}
)

#==============================================================================
# Test: Level 2
#==============================================================================

add_executable(test_pubsub test/level2/test_pubsub.cpp)
target_link_libraries(test_pubsub rmw_mock)
target_include_directories(test_pubsub PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${RMW_INCLUDE_DIRS}
  ${RCUTILS_INCLUDE_DIRS}
  ${ROSIDL_INCLUDE_DIRS}
)

#==============================================================================
# Test: Level 3
#==============================================================================

add_executable(test_executor test/level3/test_executor.cpp)
target_link_libraries(test_executor rmw_mock pthread)
target_include_directories(test_executor PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${RMW_INCLUDE_DIRS}
  ${RCUTILS_INCLUDE_DIRS}
  ${ROSIDL_INCLUDE_DIRS}
)

#==============================================================================
# Test targets
#==============================================================================

enable_testing()
add_test(NAME test_level1_init_node COMMAND test_init_node)
add_test(NAME test_level2_pubsub COMMAND test_pubsub)
add_test(NAME test_level3_executor COMMAND test_executor)

#==============================================================================
# Install
#==============================================================================

install(TARGETS rmw_mock
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
)

install(DIRECTORY include/ DESTINATION include)
