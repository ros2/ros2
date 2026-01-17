# CMake toolchain file for aarch64-linux-gnu (KaihongOS/OpenHarmony)
# Usage: cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-aarch64-ohos.cmake ..

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# Toolchain location
set(TOOLCHAIN_ROOT "/home/jiusi/M-DDS/openharmony_prebuilts/gcc-linaro-7.5.0-2019.12-x86_64_aarch64-linux-gnu")
set(CMAKE_SYSROOT "${TOOLCHAIN_ROOT}/aarch64-linux-gnu/libc")

# Compiler paths
set(CMAKE_C_COMPILER "${TOOLCHAIN_ROOT}/bin/aarch64-linux-gnu-gcc")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_ROOT}/bin/aarch64-linux-gnu-g++")
set(CMAKE_AR "${TOOLCHAIN_ROOT}/bin/aarch64-linux-gnu-ar")
set(CMAKE_RANLIB "${TOOLCHAIN_ROOT}/bin/aarch64-linux-gnu-ranlib")
set(CMAKE_STRIP "${TOOLCHAIN_ROOT}/bin/aarch64-linux-gnu-strip")

# Search paths
set(CMAKE_FIND_ROOT_PATH "${CMAKE_SYSROOT}")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Compiler flags - Use static C++ runtime to avoid libstdc++ dependency
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=armv8-a -mtune=cortex-a72")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=armv8-a -mtune=cortex-a72 -static-libstdc++ -static-libgcc")

# Output info
message(STATUS "Cross-compiling for aarch64-linux (KaihongOS)")
message(STATUS "  Toolchain: ${TOOLCHAIN_ROOT}")
message(STATUS "  Sysroot: ${CMAKE_SYSROOT}")
message(STATUS "  C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "  CXX Compiler: ${CMAKE_CXX_COMPILER}")
