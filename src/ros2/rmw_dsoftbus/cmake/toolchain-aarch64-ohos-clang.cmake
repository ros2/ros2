# CMake toolchain file for aarch64-linux-ohos (KaihongOS/OpenHarmony with Clang)
# Usage: cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-aarch64-ohos-clang.cmake ..

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# OHOS Clang toolchain location
set(OHOS_CLANG_ROOT "/home/jiusi/M-DDS/openharmony_prebuilts/clang_linux-x86_64-81cdec-20240308")

# Compiler paths (use OHOS-specific clang wrappers - they have builtin paths)
set(CMAKE_C_COMPILER "${OHOS_CLANG_ROOT}/bin/aarch64-unknown-linux-ohos-clang")
set(CMAKE_CXX_COMPILER "${OHOS_CLANG_ROOT}/bin/aarch64-unknown-linux-ohos-clang++")
set(CMAKE_AR "${OHOS_CLANG_ROOT}/bin/llvm-ar")
set(CMAKE_RANLIB "${OHOS_CLANG_ROOT}/bin/llvm-ranlib")
set(CMAKE_STRIP "${OHOS_CLANG_ROOT}/bin/llvm-strip")

# Don't use sysroot - the aarch64-unknown-linux-ohos-clang++ wrapper has builtin paths
# Just let it use its defaults

# Disable compiler checks (we know the compiler works)
set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_CXX_COMPILER_WORKS TRUE)

# Search paths
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE NEVER)

# Output info
message(STATUS "Cross-compiling for aarch64-linux-ohos (KaihongOS with Clang)")
message(STATUS "  Toolchain: ${OHOS_CLANG_ROOT}")
message(STATUS "  C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "  CXX Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "  Using builtin sysroot from compiler wrapper")
message(STATUS "  C++ Runtime: libc++ (LLVM)")
