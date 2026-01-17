# CMake toolchain file for OHOS clang (prebuilts)
# Target: aarch64-linux-ohos (musl libc)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# OHOS prebuilts clang toolchain
set(OHOS_PREBUILTS_DIR "/home/jiusi/M-DDS/openharmony_prebuilts/clang_linux-x86_64-81cdec-20240308")

# Compilers (use wrapper scripts that set --sysroot and -D__MUSL__)
set(CMAKE_C_COMPILER "${OHOS_PREBUILTS_DIR}/bin/aarch64-unknown-linux-ohos-clang")
set(CMAKE_CXX_COMPILER "${OHOS_PREBUILTS_DIR}/bin/aarch64-unknown-linux-ohos-clang++")

# Sysroot (automatically set by wrapper scripts)
set(CMAKE_SYSROOT "${OHOS_PREBUILTS_DIR}/sysroot")

# Find programs in native system
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# Find libraries and includes only in sysroot
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -fvisibility=hidden" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fPIC -fvisibility=hidden -stdlib=libc++" CACHE STRING "" FORCE)

# Linker flags (use libc++ instead of libstdc++)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lc++ -lc++abi" CACHE STRING "" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -lc++ -lc++abi" CACHE STRING "" FORCE)

# Build type specific flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG" CACHE STRING "" FORCE)

# Disable static linking (use shared libc++.so on device)
set(BUILD_SHARED_LIBS ON)
