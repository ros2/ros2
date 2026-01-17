cmake_minimum_required(VERSION 3.14)
project(ros2_demo_cpp VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Simple stub-based compilation (for aarch64 cross-compilation)
# This builds standalone talker/listener without full ROS2 dependencies

# Mock RMW includes
set(RMW_MOCK_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../rmw_dsoftbus/mock_includes")

# Talker executable
add_executable(talker_aarch64 src/talker.cpp)
target_include_directories(talker_aarch64 PRIVATE
    ${RMW_MOCK_INCLUDE_DIR}
    ${RMW_MOCK_INCLUDE_DIR}/rmw
    ${RMW_MOCK_INCLUDE_DIR}/rcutils
)
target_compile_options(talker_aarch64 PRIVATE -std=c++17 -O2 -Wall -Wextra)
target_link_options(talker_aarch64 PRIVATE -Wl,-rpath,/data/lib64:/system/lib64)
target_link_libraries(talker_aarch64 PRIVATE pthread)

# Listener executable
add_executable(listener_aarch64 src/listener.cpp)
target_include_directories(listener_aarch64 PRIVATE
    ${RMW_MOCK_INCLUDE_DIR}
    ${RMW_MOCK_INCLUDE_DIR}/rmw
    ${RMW_MOCK_INCLUDE_DIR}/rcutils
)
target_compile_options(listener_aarch64 PRIVATE -std=c++17 -O2 -Wall -Wextra)
target_link_options(listener_aarch64 PRIVATE -Wl,-rpath,/data/lib64:/system/lib64)
target_link_libraries(listener_aarch64 PRIVATE pthread)
