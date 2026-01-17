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

#include <rcutils/allocator.h>  // Foundation layer memory management

#include <cstring>
#include <ctime>
#include <memory>
#include <fcntl.h>
#include <unistd.h>

// Forward declarations for dsoftbus adapter
namespace rmw_dsoftbus {
    extern std::string encode_service_for_session(const char* service_name);
    extern int create_service_client(const char* service_name, const char* type_name, void* client_impl);
    extern void destroy_service_client(const char* service_name);
    extern int send_service_request(const char* service_name, int64_t request_id,
                                    const void* request_data, unsigned int len,
                                    const uint8_t* client_gid);
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

rmw_client_t * rmw_create_client(
    const rmw_node_t * node,
    const rosidl_service_type_support_t * type_support,
    const char * service_name,
    const rmw_qos_profile_t * qos_policies)
{
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
    // Reject C++ introspection typesupport for non-builtin clients
    //
    // Same constraint as services: only C introspection is supported for real serialization.
    // C++ typesupport is allowed only for builtin parameter clients.
    //
    // 《商君书》："法不明，则民无所措手足。"- Be explicit about constraints.
    if (type_support->typesupport_identifier &&
        is_cpp_introspection(type_support->typesupport_identifier) &&
        !is_builtin_parameter_service(service_name)) {

        fprintf(stderr, "[ERROR] Client '%s' uses C++ introspection typesupport, "
                "which is NOT supported by rmw_dsoftbus.\n", service_name);
        fprintf(stderr, "[ERROR] Please use C introspection typesupport (rosidl_typesupport_introspection_c).\n");
        fprintf(stderr, "[ERROR] User-defined clients cannot use C++ typesupport in this RMW implementation.\n");
        RMW_SET_ERROR_MSG("C++ introspection typesupport not supported for user clients");
        return nullptr;
    }

    // Allocate client implementation
    auto cli_impl = new (std::nothrow) rmw_dsoftbus::ClientImpl();
    if (!cli_impl) {
        RMW_SET_ERROR_MSG("failed to allocate client impl");
        return nullptr;
    }

    cli_impl->node = node_impl;
    cli_impl->service_name = service_name;
    cli_impl->type_name = type_support->typesupport_identifier;
    cli_impl->service_type_support = type_support;  // Store for serialization

    // Encode service name for dsoftbus
    cli_impl->encoded_name = rmw_dsoftbus::encode_service_for_session(service_name);

    // Generate GID for this client
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    memcpy(cli_impl->gid.data, &ts.tv_sec, sizeof(ts.tv_sec));
    memcpy(cli_impl->gid.data + sizeof(ts.tv_sec), &ts.tv_nsec, sizeof(ts.tv_nsec));
    pid_t pid = getpid();
    memcpy(cli_impl->gid.data + sizeof(ts.tv_sec) + sizeof(ts.tv_nsec), &pid, sizeof(pid));

    // Create pipe for wait notification
    if (pipe(cli_impl->pipe_fd) != 0) {
        delete cli_impl;
        RMW_SET_ERROR_MSG("failed to create pipe for client");
        return nullptr;
    }

    // Make read end non-blocking
    int flags = fcntl(cli_impl->pipe_fd[0], F_GETFL, 0);
    fcntl(cli_impl->pipe_fd[0], F_SETFL, flags | O_NONBLOCK);

    // Register with dsoftbus - creates session server for response receiving
    int session_id = rmw_dsoftbus::create_service_client(
        service_name,
        type_support->typesupport_identifier,
        cli_impl);
    if (session_id < 0) {
        close(cli_impl->pipe_fd[0]);
        close(cli_impl->pipe_fd[1]);
        delete cli_impl;
        RMW_SET_ERROR_MSG("failed to create dsoftbus service client");
        return nullptr;
    }
    cli_impl->session_id = session_id;

    // Allocate rmw_client_t
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    auto client = static_cast<rmw_client_t*>(allocator.allocate(sizeof(rmw_client_t), allocator.state));
    if (!client) {
        rmw_dsoftbus::destroy_service_client(service_name);
        close(cli_impl->pipe_fd[0]);
        close(cli_impl->pipe_fd[1]);
        delete cli_impl;
        RMW_SET_ERROR_MSG("failed to allocate rmw_client_t");
        return nullptr;
    }

    client->implementation_identifier = rmw_get_implementation_identifier();
    client->data = cli_impl;
    client->service_name = cli_impl->service_name.c_str();

    return client;
}

rmw_ret_t rmw_destroy_client(rmw_node_t * node, rmw_client_t * client)
{
    if (!node) {
        RMW_SET_ERROR_MSG("node is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!client) {
        RMW_SET_ERROR_MSG("client is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (client->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    auto cli_impl = static_cast<rmw_dsoftbus::ClientImpl*>(client->data);
    if (cli_impl) {
        // Unregister from dsoftbus
        rmw_dsoftbus::destroy_service_client(cli_impl->service_name.c_str());
        delete cli_impl;
    }

    // Deallocate using Foundation layer allocator
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    allocator.deallocate(client, allocator.state);

    return RMW_RET_OK;
}

rmw_ret_t rmw_send_request(
    const rmw_client_t * client,
    const void * ros_request,
    int64_t * sequence_id)
{
    if (!client) {
        RMW_SET_ERROR_MSG("client is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!ros_request) {
        RMW_SET_ERROR_MSG("ros_request is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!sequence_id) {
        RMW_SET_ERROR_MSG("sequence_id is null");
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

    // Generate request_id using ServiceEnvelope generator
    uint64_t request_id = rmw_dsoftbus::generate_request_id();
    *sequence_id = static_cast<int64_t>(request_id);

    // Record pending request
    {
        std::lock_guard<std::mutex> lock(cli_impl->pending_mutex);
        rmw_dsoftbus::PendingRequest pending;
        pending.request_id = request_id;
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        pending.send_timestamp = ts.tv_sec * 1000000000ULL + ts.tv_nsec;
        cli_impl->pending_requests[request_id] = pending;
    }

    // Serialize request with ServiceEnvelope
    uint8_t* buffer = nullptr;
    size_t size = 0;
    rmw_ret_t ret = rmw_dsoftbus_serialize_request(
        ros_request,
        cli_impl->service_type_support,
        request_id,
        &buffer,
        &size);

    if (ret != RMW_RET_OK) {
        // Remove pending request on failure
        std::lock_guard<std::mutex> lock(cli_impl->pending_mutex);
        cli_impl->pending_requests.erase(request_id);
        // Error message already set by serialize function
        return ret;
    }

    // Send request via dsoftbus
    int send_ret = rmw_dsoftbus::send_service_request(
        cli_impl->service_name.c_str(),
        static_cast<int64_t>(request_id),
        buffer,
        static_cast<unsigned int>(size),
        cli_impl->gid.data);

    // Free buffer
    free(buffer);

    if (send_ret != 0) {
        // Remove pending request on failure
        std::lock_guard<std::mutex> lock(cli_impl->pending_mutex);
        cli_impl->pending_requests.erase(request_id);
        RMW_SET_ERROR_MSG("failed to send request via dsoftbus");
        return RMW_RET_ERROR;
    }

    return RMW_RET_OK;
}

rmw_ret_t rmw_take_response(
    const rmw_client_t * client,
    rmw_service_info_t * request_header,
    void * ros_response,
    bool * taken)
{
    if (!client) {
        RMW_SET_ERROR_MSG("client is null");
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
    if (!taken) {
        RMW_SET_ERROR_MSG("taken is null");
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

    std::lock_guard<std::mutex> lock(cli_impl->queue_mutex);

    if (cli_impl->response_queue.empty()) {
        *taken = false;
        return RMW_RET_OK;
    }

    // Get response from queue
    auto& resp = cli_impl->response_queue.front();

    // Deserialize response with ServiceEnvelope
    uint64_t request_id = 0;
    if (!resp.data.empty()) {
        rmw_ret_t deser_ret = rmw_dsoftbus_deserialize_response(
            resp.data.data(),
            resp.data.size(),
            cli_impl->service_type_support,
            &request_id,
            ros_response);

        if (deser_ret != RMW_RET_OK) {
            // If deserialization fails, try fallback (raw memcpy for compatibility)
            fprintf(stderr, "[rmw_take_response] Deserialization failed (ret=%d), using fallback\n", deser_ret);
            memcpy(ros_response, resp.data.data(), resp.data.size());
            request_id = static_cast<uint64_t>(resp.sequence_number);
        }
    } else {
        request_id = static_cast<uint64_t>(resp.sequence_number);
    }

    // Fill response header
    request_header->source_timestamp.sec = resp.timestamp_ns / 1000000000ULL;
    request_header->source_timestamp.nsec = resp.timestamp_ns % 1000000000ULL;
    request_header->received_timestamp = request_header->source_timestamp;
    request_header->request_id.sequence_number = static_cast<int64_t>(request_id);
    memcpy(request_header->request_id.writer_guid, resp.publisher_gid.data,
           sizeof(request_header->request_id.writer_guid) < RMW_DSOFTBUS_GID_SIZE ?
           sizeof(request_header->request_id.writer_guid) : RMW_DSOFTBUS_GID_SIZE);

    // Remove from pending requests
    {
        std::lock_guard<std::mutex> pending_lock(cli_impl->pending_mutex);
        cli_impl->pending_requests.erase(static_cast<int64_t>(request_id));
    }

    cli_impl->response_queue.pop();
    *taken = true;

    // Drain one byte from pipe to match the notification
    if (cli_impl->pipe_fd[0] >= 0) {
        char c;
        read(cli_impl->pipe_fd[0], &c, 1);
    }

    return RMW_RET_OK;
}

}  // extern "C"
