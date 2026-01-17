# Copyright (c) 2024 ROS2 KaihongOS Port Project
# CMakeLists.txt - Standalone build for rmw_dsoftbus (host testing)
#
# This CMake file is for host compilation testing only.
# For OpenHarmony deployment, use the BUILD.gn with the OHOS build system.

cmake_minimum_required(VERSION 3.14)
project(rmw_dsoftbus VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build options
option(BUILD_TESTING "Build tests" OFF)
option(USE_REAL_SOFTBUS "Use real dsoftbus (requires OHOS SDK)" ON)  # Phase 3: Enable real dsoftbus on device

# Compiler flags
add_compile_options(-Wall -Wextra -Wpedantic)

# Real dsoftbus or stub mode
if(USE_REAL_SOFTBUS)
    add_compile_definitions(RMW_DSOFTBUS_USE_REAL_SOFTBUS=1)
    # Path to softbus_client library on device (will be linked at runtime)
    set(SOFTBUS_CLIENT_LIB "softbus_client")

    # Include paths for OpenHarmony dsoftbus headers
    set(OPENHARMONY_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../OpenHarmony")
    set(DSOFTBUS_KITS "${OPENHARMONY_ROOT}/foundation/communication/dsoftbus/interfaces/kits")
    include_directories(
        ${DSOFTBUS_KITS}
        ${DSOFTBUS_KITS}/transport
        ${DSOFTBUS_KITS}/bus_center
        ${DSOFTBUS_KITS}/common
        ${DSOFTBUS_KITS}/kh_trans
        ${DSOFTBUS_KITS}/discovery
    )
else()
    add_compile_definitions(RMW_DSOFTBUS_STUB_MODE=1)
endif()

# Find RMW headers (mock if not available)
set(RMW_MOCK_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/mock_includes)

# Create mock RMW headers if they don't exist
if(NOT EXISTS ${RMW_MOCK_INCLUDE_DIR})
    file(MAKE_DIRECTORY ${RMW_MOCK_INCLUDE_DIR}/rmw)
    file(MAKE_DIRECTORY ${RMW_MOCK_INCLUDE_DIR}/rcutils)
    file(MAKE_DIRECTORY ${RMW_MOCK_INCLUDE_DIR}/rosidl_runtime_c)
    file(MAKE_DIRECTORY ${RMW_MOCK_INCLUDE_DIR}/rosidl_typesupport_interface)
endif()

# Source files
set(RMW_DSOFTBUS_SOURCES
    # Core RMW API implementation
    src/rmw_init.cpp
    src/rmw_node.cpp
    src/rmw_publisher.cpp
    src/rmw_subscription.cpp
    src/rmw_wait.cpp
    src/rmw_service.cpp
    src/rmw_client.cpp
    src/rmw_guard_condition.cpp
    src/rmw_get_info.cpp
    src/rmw_event.cpp
    src/rmw_qos.cpp
    src/rmw_serialize.cpp
    src/rmw_allocation.cpp
    src/rmw_logging.cpp
    src/rmw_missing_apis.cpp

    # Session management
    src/session_manager.cpp
    src/service_client_manager.cpp   # Service/Client RPC implementation (Phase 2)
    src/publisher_discovery_handler.cpp  # 1:N Publisher auto-discovery (Phase 2.2)
    src/dsoftbus_stubs.cpp           # Provides weak symbols for dsoftbus Session API
    src/native_token.cpp             # Native token initialization for SoftBus permissions

    # Graph Discovery (Phase 2.2/2.3)
    src/graph_cache.cpp              # Local graph cache for node/endpoint discovery
    src/discovery_manager.cpp        # Cross-device discovery protocol (Phase 2.3)

    # Local IPC (Phase 2.5.2)
    src/ipc_client.cpp               # IPC client for librmw → daemon communication
    src/ipc_server.cpp               # IPC server for daemon
    src/ipc_handlers.cpp             # IPC request handlers

    # Serialization
    src/cdr_serializer.cpp
    src/rmw_typesupport_serializer.cpp      # Generic introspection-based serializer
    src/service_typesupport_serializer.cpp  # Phase 3: Service RPC serializer
    src/rosidl_introspection_stub.c         # Introspection identifier stub
    src/qos_mapper.cpp
)

# Header files
set(RMW_DSOFTBUS_HEADERS
    include/rmw_dsoftbus/rmw_dsoftbus.h
    include/rmw_dsoftbus/types.h
    include/rmw_dsoftbus/session_manager.h
    include/rmw_dsoftbus/dsoftbus_session.h
    include/rmw_dsoftbus/message_header.h
    include/rmw_dsoftbus/cdr_serializer.h
    include/rmw_dsoftbus/typesupport_serializer.h  # Generic introspection serializer header
    include/rmw_dsoftbus/qos_types.h
    include/rmw_dsoftbus/qos_mapper.h
    include/rmw_dsoftbus/visibility.h
    include/rmw_dsoftbus/graph_cache.h             # Phase 2.2/2.3 graph cache
    include/rmw_dsoftbus/discovery_manager.h       # Phase 2.3 cross-device discovery
    include/rmw_dsoftbus/ipc_protocol.h            # Phase 2.5.2 local IPC protocol
    include/rmw_dsoftbus/ipc_client.h              # Phase 2.5.2 IPC client
    include/rmw_dsoftbus/ipc_server.h              # Phase 2.5.2 IPC server
    include/rmw_dsoftbus/service_envelope.h        # Phase 3 Service RPC envelope
    include/rmw_dsoftbus/service_typesupport_serializer.h  # Phase 3 Service serializer
    include/rmw_dsoftbus/typesupport_helpers.h     # Phase 3 TypeSupport variant detection
)

# Main library
add_library(rmw_dsoftbus SHARED ${RMW_DSOFTBUS_SOURCES})

target_include_directories(rmw_dsoftbus
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${RMW_MOCK_INCLUDE_DIR}
)

target_compile_definitions(rmw_dsoftbus PRIVATE RMW_DSOFTBUS_BUILDING_LIBRARY)

# Link pthread and enable static C++ runtime
find_package(Threads)
if(Threads_FOUND)
    target_link_libraries(rmw_dsoftbus PRIVATE Threads::Threads)
else()
    # OHOS clang: pthread is part of libc, link manually
    target_link_libraries(rmw_dsoftbus PRIVATE pthread)
endif()

# Static link C++ runtime for device deployment (avoid libstdc++.so.6 dependency)
target_link_options(rmw_dsoftbus PRIVATE
    "-static-libstdc++"
    "-static-libgcc"
    "-Wl,--allow-shlib-undefined"  # Allow runtime symbol resolution on device
)

# Note: dsoftbus Session API and AccessToken functions are expected to be available at runtime
# We use weak symbols for device-specific functions - they will be resolved when loaded on target

# Link dl for dynamic loading
target_link_libraries(rmw_dsoftbus PRIVATE ${CMAKE_DL_LIBS})

# Set library properties
set_target_properties(rmw_dsoftbus PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 0
    PUBLIC_HEADER "${RMW_DSOFTBUS_HEADERS}"
)

# Tests
if(BUILD_TESTING)
    enable_testing()

    add_executable(rmw_dsoftbus_test
        test/test_main.cpp
        test/test_init.cpp
        test/test_node.cpp
        test/test_pubsub.cpp
        test/service_rpc_test.cpp  # Phase 3: Service/Client RPC tests
    )

    target_link_libraries(rmw_dsoftbus_test PRIVATE rmw_dsoftbus)
    target_include_directories(rmw_dsoftbus_test PRIVATE ${RMW_MOCK_INCLUDE_DIR})

    add_test(NAME rmw_dsoftbus_test COMMAND rmw_dsoftbus_test)
endif()

# Verification test (always built)
add_executable(rmw_verify_test test/rmw_test_main.cpp)
target_link_libraries(rmw_verify_test PRIVATE rmw_dsoftbus)
target_include_directories(rmw_verify_test PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${RMW_MOCK_INCLUDE_DIR}
)

# Installation (optional)
install(TARGETS rmw_dsoftbus
    LIBRARY DESTINATION lib
    PUBLIC_HEADER DESTINATION include/rmw_dsoftbus
)
