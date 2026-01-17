// Copyright (c) 2024 ROS2 KaihongOS Port Project
// Licensed under the Apache License, Version 2.0

#include "rmw_dsoftbus/rmw_dsoftbus.h"
#include "rmw_dsoftbus/types.h"

#include <rcutils/allocator.h>  // Foundation layer memory management

#include <cstdio>
#include <cstring>
#include <memory>
#include <fcntl.h>
#include <unistd.h>

// Forward declarations for dsoftbus adapter
namespace rmw_dsoftbus {
int create_session_server(const char* session_name);
void remove_session_server(const char* session_name);
bool dsoftbus_initialize(const char* pkg_name);
}

// Use rmw_dsoftbus_get_options from header
rmw_dsoftbus_options_t rmw_dsoftbus_get_options(void);

extern "C"
{

rmw_node_t * rmw_create_node(
    rmw_context_t * context,
    const char * name,
    const char * namespace_)
{
    fprintf(stderr, "[DEBUG][rmw_create_node] called: context=%p, name=%s, namespace=%s\n",
            (void*)context, name ? name : "NULL", namespace_ ? namespace_ : "NULL");
    fflush(stderr);

    if (!context) {
        fprintf(stderr, "[DEBUG][rmw_create_node] context is null\n");
        RMW_SET_ERROR_MSG("context is null");
        return nullptr;
    }
    if (!name || strlen(name) == 0) {
        fprintf(stderr, "[DEBUG][rmw_create_node] node name is null or empty\n");
        RMW_SET_ERROR_MSG("node name is null or empty");
        return nullptr;
    }
    if (!namespace_) {
        fprintf(stderr, "[DEBUG][rmw_create_node] namespace is null\n");
        RMW_SET_ERROR_MSG("namespace is null");
        return nullptr;
    }

    // Debug: compare identifiers
    const char* ctx_id = context->implementation_identifier;
    const char* our_id = rmw_get_implementation_identifier();
    fprintf(stderr, "[DEBUG][rmw_create_node] context->impl_id=%p (%s)\n", (void*)ctx_id, ctx_id ? ctx_id : "NULL");
    fprintf(stderr, "[DEBUG][rmw_create_node] our_impl_id=%p (%s)\n", (void*)our_id, our_id);

    // Use strcmp for string comparison instead of pointer comparison
    if (!ctx_id || strcmp(ctx_id, our_id) != 0) {
        fprintf(stderr, "[DEBUG][rmw_create_node] implementation identifier mismatch\n");
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return nullptr;
    }

    auto context_impl = static_cast<rmw_dsoftbus::ContextImpl*>(context->impl);
    if (!context_impl) {
        fprintf(stderr, "[DEBUG][rmw_create_node] context_impl is null\n");
        fflush(stderr);
        RMW_SET_ERROR_MSG("context impl is null");
        return nullptr;
    }

    // Check backend type
    bool use_dsoftbus = (context_impl->active_backend == rmw_dsoftbus::BackendType::DSOFTBUS ||
                         context_impl->active_backend == rmw_dsoftbus::BackendType::AUTO);

    if (!context_impl->is_initialized && use_dsoftbus) {
        fprintf(stderr, "[DEBUG][rmw_create_node] context_impl->is_initialized is false, reinitializing dsoftbus...\n");
        fflush(stderr);
        // Try to reinitialize dsoftbus
        auto options = rmw_dsoftbus_get_options();
        if (!rmw_dsoftbus::dsoftbus_initialize(options.package_name)) {
            fprintf(stderr, "[DEBUG][rmw_create_node] dsoftbus reinit failed\n");
            fflush(stderr);
            RMW_SET_ERROR_MSG("failed to reinitialize dsoftbus");
            return nullptr;
        }
        context_impl->is_initialized = true;
    }

    // Allocate node implementation
    auto node_impl = new (std::nothrow) rmw_dsoftbus::NodeImpl();
    if (!node_impl) {
        RMW_SET_ERROR_MSG("failed to allocate node impl");
        return nullptr;
    }

    node_impl->name = name;
    node_impl->namespace_ = namespace_;
    node_impl->context = context_impl;

    // Create fully qualified name
    if (strlen(namespace_) > 0 && namespace_[0] == '/') {
        node_impl->fqn = std::string(namespace_) + "/" + name;
    } else {
        node_impl->fqn = "/" + std::string(namespace_) + "/" + name;
    }

    // Generate session name for this node
    auto options = rmw_dsoftbus_get_options();
    snprintf(node_impl->session_name, sizeof(node_impl->session_name),
             "%s%s", options.session_name_prefix, name);

    // Create dsoftbus session server for this node (only if using dsoftbus backend)
    // For socket_direct or intra_process backends, skip session server creation
    if (use_dsoftbus) {
        // create_session_server returns server_id >= 0 on success, -1 on failure
        int ret = rmw_dsoftbus::create_session_server(node_impl->session_name);
        if (ret < 0) {
            fprintf(stderr, "[WARN][rmw_create_node] create_session_server failed, continuing without session\n");
            // Don't fail - dsoftbus session server is optional for cross-device discovery
            // Local pub/sub can still work with socket_direct backend
        }
    } else {
        fprintf(stderr, "[INFO][rmw_create_node] Skipping dsoftbus session server (backend: %s)\n",
                rmw_dsoftbus::backend_to_string(context_impl->active_backend));
    }

    // Create graph guard condition for this node
    auto gc_impl = new (std::nothrow) rmw_dsoftbus::GuardConditionImpl();
    if (!gc_impl) {
        rmw_dsoftbus::remove_session_server(node_impl->session_name);
        delete node_impl;
        RMW_SET_ERROR_MSG("failed to allocate graph guard condition impl");
        return nullptr;
    }

    // Create pipe for wait notification
    if (pipe(gc_impl->pipe_fd) < 0) {
        delete gc_impl;
        rmw_dsoftbus::remove_session_server(node_impl->session_name);
        delete node_impl;
        RMW_SET_ERROR_MSG("failed to create pipe for graph guard condition");
        return nullptr;
    }

    // Set pipe to non-blocking
    int flags = fcntl(gc_impl->pipe_fd[0], F_GETFL, 0);
    fcntl(gc_impl->pipe_fd[0], F_SETFL, flags | O_NONBLOCK);
    flags = fcntl(gc_impl->pipe_fd[1], F_GETFL, 0);
    fcntl(gc_impl->pipe_fd[1], F_SETFL, flags | O_NONBLOCK);

    // Allocate rmw_guard_condition_t for graph
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    auto graph_gc = static_cast<rmw_guard_condition_t*>(
        allocator.allocate(sizeof(rmw_guard_condition_t), allocator.state));
    if (!graph_gc) {
        delete gc_impl;
        rmw_dsoftbus::remove_session_server(node_impl->session_name);
        delete node_impl;
        RMW_SET_ERROR_MSG("failed to allocate graph guard condition");
        return nullptr;
    }

    graph_gc->implementation_identifier = rmw_get_implementation_identifier();
    graph_gc->data = gc_impl;
    graph_gc->context = context;
    node_impl->graph_guard_condition = graph_gc;

    fprintf(stderr, "[DEBUG][rmw_create_node] graph_guard_condition created: %p\n", (void*)graph_gc);
    fflush(stderr);

    // Allocate rmw_node_t using Foundation layer allocator
    auto node = static_cast<rmw_node_t*>(allocator.allocate(sizeof(rmw_node_t), allocator.state));
    if (!node) {
        allocator.deallocate(graph_gc, allocator.state);
        delete gc_impl;
        rmw_dsoftbus::remove_session_server(node_impl->session_name);
        delete node_impl;
        RMW_SET_ERROR_MSG("failed to allocate rmw_node_t");
        return nullptr;
    }

    node->implementation_identifier = rmw_get_implementation_identifier();
    node->data = node_impl;
    node->name = node_impl->name.c_str();
    node->namespace_ = node_impl->namespace_.c_str();
    node->context = context;

    return node;
}

rmw_ret_t rmw_destroy_node(rmw_node_t * node)
{
    fprintf(stderr, "[DEBUG][rmw_destroy_node] called: node=%p\n", (void*)node);
    fflush(stderr);

    if (!node) {
        RMW_SET_ERROR_MSG("node is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (node->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    auto node_impl = static_cast<rmw_dsoftbus::NodeImpl*>(node->data);
    if (node_impl) {
        // Remove dsoftbus session server
        rmw_dsoftbus::remove_session_server(node_impl->session_name);

        // Cleanup graph guard condition if exists
        if (node_impl->graph_guard_condition) {
            auto graph_gc = static_cast<rmw_guard_condition_t*>(node_impl->graph_guard_condition);
            if (graph_gc) {
                auto gc_impl = static_cast<rmw_dsoftbus::GuardConditionImpl*>(graph_gc->data);
                if (gc_impl) {
                    // GuardConditionImpl destructor closes pipe fds
                    delete gc_impl;
                }
                // Deallocate the guard condition struct
                rcutils_allocator_t allocator = rcutils_get_default_allocator();
                allocator.deallocate(graph_gc, allocator.state);
            }
            node_impl->graph_guard_condition = nullptr;
        }

        delete node_impl;
    }

    // Deallocate using Foundation layer allocator
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    allocator.deallocate(node, allocator.state);

    return RMW_RET_OK;
}

const rmw_guard_condition_t * rmw_node_get_graph_guard_condition(
    const rmw_node_t * node)
{
    if (!node) {
        RMW_SET_ERROR_MSG("node is null");
        return nullptr;
    }
    if (node->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return nullptr;
    }

    auto node_impl = static_cast<rmw_dsoftbus::NodeImpl*>(node->data);
    if (!node_impl) {
        RMW_SET_ERROR_MSG("node impl is null");
        return nullptr;
    }

    return static_cast<const rmw_guard_condition_t*>(node_impl->graph_guard_condition);
}

}  // extern "C"
