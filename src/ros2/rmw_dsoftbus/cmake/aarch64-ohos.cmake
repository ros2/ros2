# CMake toolchain file for OpenHarmony aarch64 (musl-based)
# Target: rk3588s KaihongOS

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# OHOS SDK paths
# Allow overriding via environment variables for different workspaces/machines.
if(DEFINED ENV{OHOS_ROOT})
  set(OHOS_ROOT "$ENV{OHOS_ROOT}")
else()
  get_filename_component(OHOS_ROOT "${CMAKE_CURRENT_LIST_DIR}/../../OpenHarmony" ABSOLUTE)
endif()

if(DEFINED ENV{OHOS_SDK_ROOT})
  set(OHOS_SDK_ROOT "$ENV{OHOS_SDK_ROOT}")
else()
  set(OHOS_SDK_ROOT "${OHOS_ROOT}/prebuilts/ohos-sdk/linux/11/native")
endif()

if(DEFINED ENV{OHOS_LLVM_ROOT})
  set(OHOS_LLVM_ROOT "$ENV{OHOS_LLVM_ROOT}")
else()
  set(OHOS_LLVM_ROOT "${OHOS_ROOT}/prebuilts/clang/ohos/linux-x86_64/llvm")
endif()

set(OHOS_SYSROOT "${OHOS_SDK_ROOT}/sysroot")

if(NOT EXISTS "${OHOS_LLVM_ROOT}/bin/clang++")
  message(FATAL_ERROR "OHOS clang++ not found: ${OHOS_LLVM_ROOT}/bin/clang++ (set OHOS_ROOT/OHOS_LLVM_ROOT)")
endif()
if(NOT EXISTS "${OHOS_SYSROOT}")
  message(FATAL_ERROR "OHOS sysroot not found: ${OHOS_SYSROOT} (set OHOS_ROOT/OHOS_SDK_ROOT)")
endif()

# Cross-compiler settings
set(CMAKE_C_COMPILER "${OHOS_LLVM_ROOT}/bin/clang")
set(CMAKE_CXX_COMPILER "${OHOS_LLVM_ROOT}/bin/clang++")
set(CMAKE_AR "${OHOS_LLVM_ROOT}/bin/llvm-ar")
set(CMAKE_RANLIB "${OHOS_LLVM_ROOT}/bin/llvm-ranlib")
set(CMAKE_STRIP "${OHOS_LLVM_ROOT}/bin/llvm-strip")

# Set sysroot
set(CMAKE_SYSROOT "${OHOS_SYSROOT}")

# Target triple for aarch64 OHOS
set(CMAKE_C_COMPILER_TARGET "aarch64-linux-ohos")
set(CMAKE_CXX_COMPILER_TARGET "aarch64-linux-ohos")

# Search paths
set(CMAKE_FIND_ROOT_PATH "${OHOS_SYSROOT}")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Compiler/linker flags
set(CMAKE_CXX_FLAGS_INIT "-stdlib=libc++")
# KaihongOS/OpenHarmony uses musl loader at this fixed path.
set(CMAKE_EXE_LINKER_FLAGS_INIT "-fuse-ld=lld -pie -Wl,--dynamic-linker=/system/lib/ld-musl-aarch64.so.1")
set(CMAKE_SHARED_LINKER_FLAGS_INIT "-fuse-ld=lld")
