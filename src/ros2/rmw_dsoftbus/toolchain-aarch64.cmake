# CMake Toolchain for aarch64-linux-gnu (gcc-linaro)
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# Toolchain paths
set(TOOLCHAIN_ROOT "/home/jiusi/M-DDS/openharmony_prebuilts/gcc-linaro-7.5.0-2019.12-x86_64_aarch64-linux-gnu")

set(CMAKE_C_COMPILER "${TOOLCHAIN_ROOT}/bin/aarch64-linux-gnu-gcc")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_ROOT}/bin/aarch64-linux-gnu-g++")
set(CMAKE_AR "${TOOLCHAIN_ROOT}/bin/aarch64-linux-gnu-ar")
set(CMAKE_STRIP "${TOOLCHAIN_ROOT}/bin/aarch64-linux-gnu-strip")

# Compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -O2 -fPIC" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O2 -fPIC" CACHE STRING "" FORCE)

# Linker flags for RPATH
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,/data -Wl,-rpath,/system/lib64 -static-libstdc++ -static-libgcc")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-rpath,/data -Wl,-rpath,/system/lib64 -static-libstdc++ -static-libgcc")

# Find settings
set(CMAKE_FIND_ROOT_PATH "${TOOLCHAIN_ROOT}/aarch64-linux-gnu")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
