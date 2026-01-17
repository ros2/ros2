/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Copyright (c) 2024 ROS2 KaihongOS Port Project
#include <string.h>  /* C memcpy/memset for OHOS SDK compatibility */
#include <stdlib.h>

// Licensed under the Apache License, Version 2.0

#include "rmw_dsoftbus/rmw_dsoftbus.h"
#include "rmw_dsoftbus/types.h"
#include "rmw_dsoftbus/service_typesupport_serializer.h"
#include "rmw_dsoftbus/service_envelope.h"
#include "rmw_dsoftbus/graph_cache.h"
#include "rmw_dsoftbus/session_manager.h"

#include <rcutils/allocator.h>  // Foundation layer memory management

#include <cstring>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <fcntl.h>
#include <unistd.h>

// Forward declarations for dsoftbus adapter
namespace rmw_dsoftbus {
    extern std::string encode_service_for_session(const char* service_name);
    extern int create_service_server(const char* service_name, const char* type_name, void* service_impl);
    extern void destroy_service_server(const char* service_name);
    extern int send_service_response(const char* service_name, int client_session_id,
                                     int64_t request_id, const void* response_data, unsigned int len,
                                     const uint8_t* service_gid);
    extern bool is_service_available(const char* service_name);
}

// Helper: Check if service is a builtin parameter service
static bool is_builtin_parameter_service(const char* service_name) {
    if (!service_name) return false;

    // Builtin parameter services (allowed to use C++ typesupport fallback)
    return (strstr(service_name, "get_parameters") != nullptr ||
            strstr(service_name, "set_parameters") != nullptr ||
            strstr(service_name, "list_parameters") != nullptr ||
            strstr(service_name, "describe_parameters") != nullptr ||
            strstr(service_name, "get_parameter_types") != nullptr ||
            strstr(service_name, "get_type_description") != nullptr);
}

// Helper: Check if typesupport is C++ introspection
static bool is_cpp_introspection(const char* identifier) {
    return identifier && strcmp(identifier, "rosidl_typesupport_introspection_cpp") == 0;
}

extern "C"
{

rmw_service_t * rmw_create_service(
    const rmw_node_t * node,
    const rosidl_service_type_support_t * type_support,
    const char * service_name,
    const rmw_qos_profile_t * qos_policies)
{
    fprintf(stderr, "[rmw_create_service] ENTRY: service_name=%s\n", service_name ? service_name : "NULL");
    fflush(stderr);

    if (!node) {
        RMW_SET_ERROR_MSG("node is null");
        return nullptr;
    }
    if (!type_support) {
        RMW_SET_ERROR_MSG("type_support is null");
        return nullptr;
    }
    if (!service_name || strlen(service_name) == 0) {
        RMW_SET_ERROR_MSG("service_name is null or empty");
        return nullptr;
    }
    if (!qos_policies) {
        RMW_SET_ERROR_MSG("qos_policies is null");
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

    // ⚠️ SERIALIZATION CAPABILITY CHECK ⚠️
    // Reject C++ introspection typesupport for non-builtin services
    //
    // This RMW only supports C introspection typesupport for real serialization.
    // C++ introspection has a different struct layout and will fail at runtime.
    //
    // We allow C++ typesupport ONLY for builtin parameter services (/get_parameters, etc.)
    // because they use empty CDR fallback (4-byte header) which is acceptable for system internals.
    //
    // For user-defined services: MUST use C introspection typesupport, or create will fail.
    // 《商君书》："法不明，则民无所措手足。"- Be explicit about constraints.
    if (type_support->typesupport_identifier &&
        is_cpp_introspection(type_support->typesupport_identifier) &&
        !is_builtin_parameter_service(service_name)) {

        fprintf(stderr, "[ERROR] Service '%s' uses C++ introspection typesupport, "
                "which is NOT supported by rmw_dsoftbus.\n", service_name);
        fprintf(stderr, "[ERROR] Please use C introspection typesupport (rosidl_typesupport_introspection_c).\n");
        fprintf(stderr, "[ERROR] User-defined services cannot use C++ typesupport in this RMW implementation.\n");
        RMW_SET_ERROR_MSG("C++ introspection typesupport not supported for user services");
        return nullptr;
    }

    // Allocate service implementation
    auto srv_impl = new (std::nothrow) rmw_dsoftbus::ServiceImpl();
    if (!srv_impl) {
        RMW_SET_ERROR_MSG("failed to allocate service impl");
        return nullptr;
    }

    srv_impl->node = node_impl;
    srv_impl->service_name = service_name;
    srv_impl->type_name = type_support->typesupport_identifier;
    srv_impl->service_type_support = type_support;  // Store for serialization

    // Encode service name for dsoftbus
    srv_impl->encoded_name = rmw_dsoftbus::encode_service_for_session(service_name);

    // Create pipe for wait notification
    if (pipe(srv_impl->pipe_fd) != 0) {
        delete srv_impl;
        RMW_SET_ERROR_MSG("failed to create pipe for service");
        return nullptr;
    }

    // Make read end non-blocking
    int flags = fcntl(srv_impl->pipe_fd[0], F_GETFL, 0);
    fcntl(srv_impl->pipe_fd[0], F_SETFL, flags | O_NONBLOCK);

    // Create dsoftbus session server for this service
    int server_id = rmw_dsoftbus::create_service_server(
        service_name,
        type_support->typesupport_identifier,
        srv_impl);

    if (server_id < 0) {
        close(srv_impl->pipe_fd[0]);
        close(srv_impl->pipe_fd[1]);
        delete srv_impl;
        RMW_SET_ERROR_MSG("failed to create dsoftbus service server");
        return nullptr;
    }
    srv_impl->session_server_id = server_id;
    fprintf(stderr, "[rmw_create_service] Created service server: %s, server_id=%d\n",
            service_name, server_id);

    // Generate GID for this service
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    memset(&srv_impl->gid, 0, sizeof(srv_impl->gid));
    memcpy(srv_impl->gid.data, &ts.tv_sec, sizeof(ts.tv_sec));
    memcpy(srv_impl->gid.data + sizeof(ts.tv_sec), &ts.tv_nsec, sizeof(ts.tv_nsec));
    pid_t pid = getpid();
    memcpy(srv_impl->gid.data + sizeof(ts.tv_sec) + sizeof(ts.tv_nsec), &pid, sizeof(pid));

    // Register with GraphCache (Phase 3)
    rmw_dsoftbus::GraphCache::instance().register_service(
        service_name,
        type_support->typesupport_identifier,
        node_impl->name.c_str(),
        node_impl->namespace_.c_str(),
        qos_policies,
        &srv_impl->gid,
        srv_impl,
        server_id);  // session_id for liveness check

    // Allocate rmw_service_t
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    auto service = static_cast<rmw_service_t*>(allocator.allocate(sizeof(rmw_service_t), allocator.state));
    if (!service) {
        delete srv_impl;
        RMW_SET_ERROR_MSG("failed to allocate rmw_service_t");
        return nullptr;
    }

    service->implementation_identifier = rmw_get_implementation_identifier();
    service->data = srv_impl;
    service->service_name = srv_impl->service_name.c_str();

    return service;
}

rmw_ret_t rmw_destroy_service(rmw_node_t * node, rmw_service_t * service)
{
    if (!node) {
        RMW_SET_ERROR_MSG("node is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!service) {
        RMW_SET_ERROR_MSG("service is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (service->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    auto srv_impl = static_cast<rmw_dsoftbus::ServiceImpl*>(service->data);
    if (srv_impl) {
        // Unregister from dsoftbus
        rmw_dsoftbus::destroy_service_server(srv_impl->service_name.c_str());
        delete srv_impl;
    }

    // Deallocate using Foundation layer allocator
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    allocator.deallocate(service, allocator.state);

    return RMW_RET_OK;
}

rmw_ret_t rmw_take_request(
    const rmw_service_t * service,
    rmw_service_info_t * request_header,
    void * ros_request,
    bool * taken)
{
    if (!service) {
        RMW_SET_ERROR_MSG("service is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!request_header) {
        RMW_SET_ERROR_MSG("request_header is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!ros_request) {
        RMW_SET_ERROR_MSG("ros_request is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!taken) {
        RMW_SET_ERROR_MSG("taken is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (service->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    auto srv_impl = static_cast<rmw_dsoftbus::ServiceImpl*>(service->data);
    if (!srv_impl) {
        RMW_SET_ERROR_MSG("service impl is null");
        return RMW_RET_ERROR;
    }

    std::lock_guard<std::mutex> lock(srv_impl->queue_mutex);

    if (srv_impl->request_queue.empty()) {
        *taken = false;
        return RMW_RET_OK;
    }

    // Get request from queue
    auto& req = srv_impl->request_queue.front();

    // Deserialize request with ServiceEnvelope
    uint64_t request_id = 0;
    if (!req.message.data.empty()) {
        rmw_ret_t deser_ret = rmw_dsoftbus_deserialize_request(
            req.message.data.data(),
            req.message.data.size(),
            srv_impl->service_type_support,
            &request_id,
            ros_request);

        if (deser_ret != RMW_RET_OK) {
            // If deserialization fails, try fallback (raw memcpy for compatibility)
            fprintf(stderr, "[rmw_take_request] Deserialization failed (ret=%d), using fallback\n", deser_ret);
            memcpy(ros_request, req.message.data.data(), req.message.data.size());
            request_id = static_cast<uint64_t>(req.request_id);
        }
    } else {
        request_id = static_cast<uint64_t>(req.request_id);
    }

    // Fill request header with client info
    request_header->source_timestamp.sec = req.message.timestamp_ns / 1000000000ULL;
    request_header->source_timestamp.nsec = req.message.timestamp_ns % 1000000000ULL;
    request_header->received_timestamp = request_header->source_timestamp;
    request_header->request_id.sequence_number = static_cast<int64_t>(request_id);
    // Store client session ID in writer_guid for later response routing
    memset(request_header->request_id.writer_guid, 0, sizeof(request_header->request_id.writer_guid));
    memcpy(request_header->request_id.writer_guid, &req.client_session_id, sizeof(int));

    srv_impl->request_queue.pop();
    *taken = true;

    // Drain one byte from pipe to match the notification
    if (srv_impl->pipe_fd[0] >= 0) {
        char c;
        read(srv_impl->pipe_fd[0], &c, 1);
    }

    return RMW_RET_OK;
}

rmw_ret_t rmw_send_response(
    const rmw_service_t * service,
    rmw_request_id_t * request_header,
    void * ros_response)
{
    if (!service) {
        RMW_SET_ERROR_MSG("service is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!request_header) {
        RMW_SET_ERROR_MSG("request_header is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!ros_response) {
        RMW_SET_ERROR_MSG("ros_response is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (service->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    auto srv_impl = static_cast<rmw_dsoftbus::ServiceImpl*>(service->data);
    if (!srv_impl) {
        RMW_SET_ERROR_MSG("service impl is null");
        return RMW_RET_ERROR;
    }

    // Extract client session ID from request header (stored in writer_guid)
    int client_session_id = 0;
    memcpy(&client_session_id, request_header->writer_guid, sizeof(int));

    // Get request_id from sequence_number (echo back for correlation)
    uint64_t request_id = static_cast<uint64_t>(request_header->sequence_number);

    // Serialize response with ServiceEnvelope
    uint8_t* buffer = nullptr;
    size_t size = 0;
    rmw_ret_t ret = rmw_dsoftbus_serialize_response(
        ros_response,
        srv_impl->service_type_support,
        request_id,  // Echo back request_id for correlation
        &buffer,
        &size);

    if (ret != RMW_RET_OK) {
        // Error message already set by serialize function
        return ret;
    }

    // Send response via dsoftbus
    int send_ret = rmw_dsoftbus::send_service_response(
        srv_impl->service_name.c_str(),
        client_session_id,
        static_cast<int64_t>(request_id),
        buffer,
        static_cast<unsigned int>(size),
        nullptr);

    // Free buffer
    free(buffer);

    if (send_ret != 0) {
        RMW_SET_ERROR_MSG("failed to send response via dsoftbus");
        return RMW_RET_ERROR;
    }

    return RMW_RET_OK;
}

rmw_ret_t rmw_service_server_is_available(
    const rmw_node_t * node,
    const rmw_client_t * client,
    bool * is_available)
{
    if (!node) {
        RMW_SET_ERROR_MSG("node is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!client) {
        RMW_SET_ERROR_MSG("client is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!is_available) {
        RMW_SET_ERROR_MSG("is_available is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (client->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    auto cli_impl = static_cast<rmw_dsoftbus::ClientImpl*>(client->data);
    if (!cli_impl) {
        RMW_SET_ERROR_MSG("client impl is null");
        return RMW_RET_ERROR;
    }

    // Check service availability via dsoftbus discovery
    *is_available = rmw_dsoftbus::is_service_available(cli_impl->service_name.c_str());

    return RMW_RET_OK;
}

}  // extern "C"
