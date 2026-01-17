// Copyright (c) 2024 ROS2 KaihongOS Port Project
// Licensed under the Apache License, Version 2.0

#include "rmw_dsoftbus/rmw_dsoftbus.h"
#include "rmw_dsoftbus/types.h"
#include "rmw_dsoftbus/qos_mapper.h"
#include "rmw_dsoftbus/socket_direct.h"

#include <cstring>
#include <cstdlib>
#include <memory>
#include <sstream>

// Forward declaration for dsoftbus adapter
namespace rmw_dsoftbus {
bool dsoftbus_initialize(const char* pkg_name);
void dsoftbus_shutdown();

// Parse comma-separated peer list from environment variable
static std::vector<std::string> parse_peers(const char* peers_str) {
    std::vector<std::string> peers;
    if (!peers_str || peers_str[0] == '\0') {
        return peers;
    }

    std::string str(peers_str);
    std::stringstream ss(str);
    std::string peer;

    while (std::getline(ss, peer, ',')) {
        // Trim whitespace
        size_t start = peer.find_first_not_of(" \t");
        size_t end = peer.find_last_not_of(" \t");
        if (start != std::string::npos && end != std::string::npos) {
            peers.push_back(peer.substr(start, end - start + 1));
        }
    }

    return peers;
}

// Global context for backend access
static ContextImpl* g_context_impl = nullptr;

}  // namespace rmw_dsoftbus

// Global options (outside namespace for extern "C" access)
static rmw_dsoftbus_options_t g_options = {
    RMW_DSOFTBUS_PACKAGE_NAME,
    RMW_DSOFTBUS_SESSION_PREFIX,
    5000,
    1000,
};

extern "C"
{

const char * rmw_get_implementation_identifier(void)
{
    return RMW_DSOFTBUS_IDENTIFIER;
}

const char * rmw_get_serialization_format(void)
{
    return "cdr";
}

rmw_ret_t rmw_init_options_init(
    rmw_init_options_t * init_options,
    rcutils_allocator_t allocator)
{
    if (!init_options) {
        RMW_SET_ERROR_MSG("init_options is null");
        return RMW_RET_INVALID_ARGUMENT;
    }

    init_options->allocator = allocator;
    init_options->implementation_identifier = rmw_get_implementation_identifier();
    init_options->impl = nullptr;
    init_options->enclave = nullptr;
    init_options->domain_id = RMW_DEFAULT_DOMAIN_ID;
    init_options->security_options = rmw_get_zero_initialized_security_options();

    return RMW_RET_OK;
}

rmw_ret_t rmw_init_options_copy(
    const rmw_init_options_t * src,
    rmw_init_options_t * dst)
{
    if (!src || !dst) {
        RMW_SET_ERROR_MSG("src or dst is null");
        return RMW_RET_INVALID_ARGUMENT;
    }

    if (src->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    dst->allocator = src->allocator;
    dst->implementation_identifier = src->implementation_identifier;
    dst->domain_id = src->domain_id;
    dst->security_options = src->security_options;
    dst->impl = nullptr;  // Don't copy impl

    if (src->enclave) {
        dst->enclave = rcutils_strdup(src->enclave, dst->allocator);
        if (!dst->enclave) {
            RMW_SET_ERROR_MSG("failed to copy enclave");
            return RMW_RET_BAD_ALLOC;
        }
    } else {
        dst->enclave = nullptr;
    }

    return RMW_RET_OK;
}

rmw_ret_t rmw_init_options_fini(rmw_init_options_t * init_options)
{
    if (!init_options) {
        RMW_SET_ERROR_MSG("init_options is null");
        return RMW_RET_INVALID_ARGUMENT;
    }

    if (init_options->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    if (init_options->enclave) {
        init_options->allocator.deallocate(
            const_cast<char*>(init_options->enclave),
            init_options->allocator.state);
        init_options->enclave = nullptr;
    }

    *init_options = rmw_get_zero_initialized_init_options();

    return RMW_RET_OK;
}

rmw_ret_t rmw_init(
    const rmw_init_options_t * options,
    rmw_context_t * context)
{
    fprintf(stderr, "[DEBUG][rmw_init] called: options=%p, context=%p\n", (void*)options, (void*)context);
    fflush(stderr);

    if (!options) {
        RMW_SET_ERROR_MSG("options is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!context) {
        RMW_SET_ERROR_MSG("context is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (options->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    // Initialize QoS settings from environment variables
    rmw_dsoftbus::init_qos_from_environment();

    // Allocate context implementation
    auto context_impl = new (std::nothrow) rmw_dsoftbus::ContextImpl();
    if (!context_impl) {
        RMW_SET_ERROR_MSG("failed to allocate context impl");
        return RMW_RET_BAD_ALLOC;
    }

    // === Backend Selection ===
    // Read from environment variable: RMW_DSOFTBUS_BACKEND=socket|dsoftbus|intra|auto
    const char* backend_env = std::getenv("RMW_DSOFTBUS_BACKEND");
    context_impl->active_backend = rmw_dsoftbus::backend_from_string(backend_env);

    // Read peer list for socket_direct backend: RMW_DSOFTBUS_PEERS=192.168.11.192,192.168.11.210
    const char* peers_env = std::getenv("RMW_DSOFTBUS_PEERS");
    context_impl->socket_peers = rmw_dsoftbus::parse_peers(peers_env);

    fprintf(stderr, "[INFO][rmw_dsoftbus] Backend: %s (from env: %s)\n",
            rmw_dsoftbus::backend_to_string(context_impl->active_backend),
            backend_env ? backend_env : "not set");

    if (!context_impl->socket_peers.empty()) {
        fprintf(stderr, "[INFO][rmw_dsoftbus] Peers: ");
        for (size_t i = 0; i < context_impl->socket_peers.size(); i++) {
            fprintf(stderr, "%s%s", context_impl->socket_peers[i].c_str(),
                    (i < context_impl->socket_peers.size() - 1) ? ", " : "");
        }
        fprintf(stderr, "\n");
    }
    fflush(stderr);

    // Initialize based on backend type
    bool init_success = false;

    if (context_impl->active_backend == rmw_dsoftbus::BackendType::SOCKET_DIRECT) {
        // Initialize socket_direct backend only
        if (socket_direct_init(nullptr) == 0) {
            fprintf(stderr, "[INFO][rmw_dsoftbus] socket_direct backend initialized\n");
            init_success = true;
        } else {
            fprintf(stderr, "[WARN][rmw_dsoftbus] socket_direct init failed, falling back to dsoftbus\n");
            context_impl->active_backend = rmw_dsoftbus::BackendType::DSOFTBUS;
        }
    }

    if (context_impl->active_backend == rmw_dsoftbus::BackendType::DSOFTBUS ||
        context_impl->active_backend == rmw_dsoftbus::BackendType::AUTO) {
        // Initialize dsoftbus
        if (rmw_dsoftbus::dsoftbus_initialize(g_options.package_name)) {
            fprintf(stderr, "[INFO][rmw_dsoftbus] dsoftbus backend initialized\n");
            init_success = true;

            // For AUTO mode, set to DSOFTBUS if socket_direct not preferred
            if (context_impl->active_backend == rmw_dsoftbus::BackendType::AUTO) {
                // If peers are configured, prefer socket_direct for cross-device
                if (!context_impl->socket_peers.empty()) {
                    socket_direct_init(nullptr);
                    context_impl->active_backend = rmw_dsoftbus::BackendType::SOCKET_DIRECT;
                    fprintf(stderr, "[INFO][rmw_dsoftbus] AUTO mode: peers configured, using socket_direct\n");
                } else {
                    context_impl->active_backend = rmw_dsoftbus::BackendType::DSOFTBUS;
                }
            }
        }
    }

    if (context_impl->active_backend == rmw_dsoftbus::BackendType::INTRA_PROCESS) {
        // Intra-process mode doesn't need external initialization
        fprintf(stderr, "[INFO][rmw_dsoftbus] intra-process backend (no network)\n");
        init_success = true;
    }

    if (!init_success) {
        delete context_impl;
        RMW_SET_ERROR_MSG("failed to initialize any backend");
        return RMW_RET_ERROR;
    }

    // Store global reference for publisher/subscription access
    rmw_dsoftbus::g_context_impl = context_impl;

    context_impl->is_initialized = true;
    context->implementation_identifier = rmw_get_implementation_identifier();
    context->impl = context_impl;

    fprintf(stderr, "[INFO][rmw_dsoftbus] Initialized with backend: %s\n",
            rmw_dsoftbus::backend_to_string(context_impl->active_backend));
    fflush(stderr);

    return RMW_RET_OK;
}

rmw_ret_t rmw_shutdown(rmw_context_t * context)
{
    fprintf(stderr, "[DEBUG][rmw_shutdown] called: context=%p\n", (void*)context);
    fflush(stderr);

    if (!context) {
        RMW_SET_ERROR_MSG("context is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (context->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    auto context_impl = static_cast<rmw_dsoftbus::ContextImpl*>(context->impl);
    if (context_impl && context_impl->is_initialized) {
        // Shutdown based on active backend
        if (context_impl->active_backend == rmw_dsoftbus::BackendType::SOCKET_DIRECT) {
            socket_direct_shutdown();
        }
        // Always try dsoftbus shutdown (it's safe even if not initialized)
        rmw_dsoftbus::dsoftbus_shutdown();

        context_impl->is_initialized = false;
        rmw_dsoftbus::g_context_impl = nullptr;
    }

    return RMW_RET_OK;
}

rmw_ret_t rmw_context_fini(rmw_context_t * context)
{
    if (!context) {
        RMW_SET_ERROR_MSG("context is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (context->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    auto context_impl = static_cast<rmw_dsoftbus::ContextImpl*>(context->impl);
    if (context_impl) {
        if (context_impl->is_initialized) {
            rmw_shutdown(context);
        }
        delete context_impl;
        context->impl = nullptr;
    }

    *context = rmw_get_zero_initialized_context();

    return RMW_RET_OK;
}

// rmw_dsoftbus specific API implementation
rmw_dsoftbus_options_t rmw_dsoftbus_get_default_options(void)
{
    return {
        .package_name = RMW_DSOFTBUS_PACKAGE_NAME,
        .session_name_prefix = RMW_DSOFTBUS_SESSION_PREFIX,
        .connection_timeout_ms = 5000,
        .discovery_interval_ms = 1000,
    };
}

int rmw_dsoftbus_set_options(const rmw_dsoftbus_options_t * options)
{
    if (!options) {
        return -1;
    }
    g_options = *options;
    return 0;
}

rmw_dsoftbus_options_t rmw_dsoftbus_get_options(void)
{
    return g_options;
}

}  // extern "C"

// === Backend Access API (for internal use by publisher/subscription) ===
namespace rmw_dsoftbus {

BackendType get_active_backend() {
    if (g_context_impl) {
        return g_context_impl->active_backend;
    }
    return BackendType::AUTO;  // Not initialized yet
}

const std::vector<std::string>& get_socket_peers() {
    static std::vector<std::string> empty;
    if (g_context_impl) {
        return g_context_impl->socket_peers;
    }
    return empty;
}

ContextImpl* get_context_impl() {
    return g_context_impl;
}

}  // namespace rmw_dsoftbus
