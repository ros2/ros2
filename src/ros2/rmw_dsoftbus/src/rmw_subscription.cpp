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
#include "rmw_dsoftbus/graph_cache.h"  // Phase 2.2: Graph Discovery
#include <rcutils/allocator.h>  // Foundation layer memory management
#include "rmw_dsoftbus/qos_mapper.h"
#include "rmw_dsoftbus/cdr_serializer.h"
#include "rmw_dsoftbus/session_manager.h"
#include "rmw_dsoftbus/typesupport_serializer.h"  // Generic introspection deserializer
#include <rosidl_typesupport_introspection_c/message_introspection.h>
#include <rosidl_runtime_c/string.h>  // For rosidl_runtime_c__String type
#include <ctime>  // For GID generation

#include <chrono>
#include <memory>
#include <fcntl.h>
#include <unistd.h>

// C library functions are already available from string.h included above
// rosidl_runtime_c__String is defined in mock_includes/rosidl_runtime_c/string.h

// std_msgs/msg/String structure
struct std_msgs__msg__String {
    rosidl_runtime_c__String data;
};

// Helper: Deserialize std_msgs/String from CDR
static bool deserialize_std_msgs_string(
    const uint8_t* cdr_data,
    size_t cdr_len,
    void* ros_message)
{
    using namespace rmw_dsoftbus::cdr;

    if (cdr_len < CDR_ENCAPSULATION_SIZE + 4) {
        fprintf(stderr, "[DEBUG][deserialize_std_msgs_string] data too short: %zu\n", cdr_len);
        return false;
    }

    CdrDeserializer deser(cdr_data, cdr_len);
    if (!deser.read_encapsulation()) {
        fprintf(stderr, "[DEBUG][deserialize_std_msgs_string] failed to read encapsulation\n");
        return false;
    }

    // Read string length (uint32_t, including null terminator)
    uint32_t str_len = 0;
    if (!deser.deserialize_pod(&str_len, 4, CDR_ALIGN_4)) {
        fprintf(stderr, "[DEBUG][deserialize_std_msgs_string] failed to read string length\n");
        return false;
    }

    // String length includes null terminator, so actual string length is str_len - 1
    size_t actual_len = (str_len > 0) ? str_len - 1 : 0;

    auto* msg = static_cast<std_msgs__msg__String*>(ros_message);

    // Allocate or reallocate string buffer
    if (msg->data.capacity < str_len) {
        char* new_buf = static_cast<char*>(realloc(msg->data.data, str_len));
        if (!new_buf) {
            fprintf(stderr, "[DEBUG][deserialize_std_msgs_string] failed to allocate buffer\n");
            return false;
        }
        msg->data.data = new_buf;
        msg->data.capacity = str_len;
    }

    // Read string content
    if (actual_len > 0) {
        if (!deser.deserialize_raw(msg->data.data, actual_len)) {
            fprintf(stderr, "[DEBUG][deserialize_std_msgs_string] failed to read string content\n");
            return false;
        }
    }
    msg->data.data[actual_len] = '\0';
    msg->data.size = actual_len;

    fprintf(stderr, "[DEBUG][deserialize_std_msgs_string] success: len=%zu, data='%s'\n",
            actual_len, msg->data.data);
    return true;
}

// Helper: Deserialize CDR message to ROS message
static bool deserialize_message_cdr(
    const uint8_t* data,
    size_t len,
    size_t message_size,
    rmw_dsoftbus::DeserializeFn deserialize_fn,
    void* ros_message,
    bool use_fallback = false)
{
    using namespace rmw_dsoftbus::cdr;

    // Check minimum size (CDR encapsulation header)
    if (len < CDR_ENCAPSULATION_SIZE) {
        return false;
    }

    // Create CDR deserializer
    CdrDeserializer deser(data, len);

    // Read encapsulation header
    if (!deser.read_encapsulation()) {
        return false;
    }

    // Deserialize the message
    if (deserialize_fn) {
        // Use custom deserialization callback
        // Note: callback expects raw data without encapsulation
        const uint8_t* payload_data = data + CDR_ENCAPSULATION_SIZE;
        size_t payload_len = len - CDR_ENCAPSULATION_SIZE;
        return deserialize_fn(payload_data, payload_len, ros_message);
    } else if (message_size > 0) {
        // POD deserialization - direct memcpy
        return deser.deserialize_pod(ros_message, message_size, CDR_ALIGN_1);
    } else if (use_fallback) {
        // Fallback: try std_msgs/String deserialization
        fprintf(stderr, "[DEBUG][deserialize_message_cdr] Using fallback (std_msgs/String)\n");
        return deserialize_std_msgs_string(data, len, ros_message);
    }

    return false;
}

extern "C"
{

rmw_subscription_t * rmw_create_subscription(
    const rmw_node_t * node,
    const rosidl_message_type_support_t * type_support,
    const char * topic_name,
    const rmw_qos_profile_t * qos_policies,
    const rmw_subscription_options_t * subscription_options)
{
    (void)subscription_options;

    if (!node) {
        RMW_SET_ERROR_MSG("node is null");
        return nullptr;
    }
    if (!type_support) {
        RMW_SET_ERROR_MSG("type_support is null");
        return nullptr;
    }
    if (!topic_name || strlen(topic_name) == 0) {
        RMW_SET_ERROR_MSG("topic_name is null or empty");
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
    // Reject C++ introspection typesupport for non-system topics
    //
    // This RMW only supports C introspection for real deserialization.
    // C++ typesupport is allowed ONLY for system topics (/rosout, /parameter_events).
    const char* cpp_introspection_id = "rosidl_typesupport_introspection_cpp";
    bool is_cpp = type_support->typesupport_identifier &&
                  strcmp(type_support->typesupport_identifier, cpp_introspection_id) == 0;
    bool is_system_topic = (strcmp(topic_name, "/rosout") == 0 ||
                           strcmp(topic_name, "/parameter_events") == 0);

    if (is_cpp && !is_system_topic) {
        fprintf(stderr, "[ERROR] Subscription for topic '%s' uses C++ introspection typesupport, "
                "which is NOT supported by rmw_dsoftbus.\n", topic_name);
        fprintf(stderr, "[ERROR] Please use C introspection typesupport (rosidl_typesupport_introspection_c).\n");
        fprintf(stderr, "[ERROR] User-defined subscriptions cannot use C++ typesupport in this RMW implementation.\n");
        RMW_SET_ERROR_MSG("C++ introspection typesupport not supported for user subscriptions");
        return nullptr;
    }

    // Allocate subscription implementation
    auto sub_impl = new (std::nothrow) rmw_dsoftbus::SubscriptionImpl();
    if (!sub_impl) {
        RMW_SET_ERROR_MSG("failed to allocate subscription impl");
        return nullptr;
    }

    sub_impl->node = node_impl;
    sub_impl->topic_name = topic_name;

    // Check if using introspection typesupport
    bool is_introspection = type_support->typesupport_identifier &&
        (strstr(type_support->typesupport_identifier, "introspection") != nullptr);

    // Extract type name from type_support
    if (is_introspection && type_support->data) {
        auto members = static_cast<const rosidl_typesupport_introspection_c__MessageMembers*>(
            type_support->data);
        if (members->message_namespace_ && members->message_name_) {
            sub_impl->type_name = std::string(members->message_namespace_) + "/" +
                                  std::string(members->message_name_);
        } else {
            sub_impl->type_name = type_support->typesupport_identifier;
        }
    } else {
        sub_impl->type_name = type_support->typesupport_identifier;
    }

    // Map ROS2 QoS profile to dsoftbus QoS config (extensible)
    sub_impl->qos_config = rmw_dsoftbus::map_qos_profile(qos_policies);

    // Legacy fields (for backward compatibility)
    sub_impl->queue_depth = sub_impl->qos_config.history_depth;
    sub_impl->reliable = (sub_impl->qos_config.reliability == rmw_dsoftbus::DSOFTBUS_RELIABILITY_FULL);

    // Encode topic name for session
    sub_impl->encoded_topic = topic_name;

    if (is_introspection) {
        // Introspection typesupport - data is rosidl_typesupport_introspection_c__MessageMembers
        // Store type_support for generic introspection-based deserialization
        fprintf(stderr, "[DEBUG][rmw_create_subscription] Using introspection typesupport\n");
        sub_impl->type_support = type_support;
        sub_impl->message_size = 0;
        sub_impl->deserialize = nullptr;
    } else if (type_support->data) {
        // Standard typesupport - extract deserialization callbacks
        auto callbacks = static_cast<const rosidl_message_type_support_callbacks_t*>(type_support->data);
        if (callbacks->message_size > 0) {
            sub_impl->message_size = callbacks->message_size;
        }
        if (callbacks->deserialize) {
            sub_impl->deserialize = reinterpret_cast<rmw_dsoftbus::DeserializeFn>(
                callbacks->deserialize);
        }
    }

    // Generate unique GID for this subscription (Phase 2.2)
    static uint64_t sub_gid_counter = 0;
    uint64_t timestamp = static_cast<uint64_t>(time(nullptr));
    uint64_t pid = static_cast<uint64_t>(getpid());
    memcpy(sub_impl->gid.data, &pid, sizeof(pid));
    memcpy(sub_impl->gid.data + 8, &timestamp, sizeof(timestamp));
    uint64_t counter_with_flag = sub_gid_counter | 0x8000000000000000ULL;  // Set high bit for subscription
    memcpy(sub_impl->gid.data + 16, &counter_with_flag, sizeof(counter_with_flag));
    sub_gid_counter++;

    // Create pipe for wait notification
    if (pipe(sub_impl->pipe_fd) != 0) {
        delete sub_impl;
        RMW_SET_ERROR_MSG("failed to create pipe for subscription");
        return nullptr;
    }

    // Make read end non-blocking
    int flags = fcntl(sub_impl->pipe_fd[0], F_GETFL, 0);
    fcntl(sub_impl->pipe_fd[0], F_SETFL, flags | O_NONBLOCK);

    // Register with SessionManager (creates session server)
    int server_id = rmw_dsoftbus::SessionManager::instance().register_subscription(
        topic_name,
        sub_impl);

    if (server_id < 0) {
        close(sub_impl->pipe_fd[0]);
        close(sub_impl->pipe_fd[1]);
        delete sub_impl;
        RMW_SET_ERROR_MSG("failed to register subscription with SessionManager");
        return nullptr;
    }

    sub_impl->session_server_id = server_id;
    fprintf(stderr, "[INFO][rmw_create_subscription] Registered subscription for topic %s\n", topic_name);

    // Phase 2.2: Register subscription with GraphCache for discovery
    rmw_gid_t rmw_gid;
    rmw_gid.implementation_identifier = rmw_get_implementation_identifier();
    memcpy(rmw_gid.data, sub_impl->gid.data, sizeof(rmw_gid.data));

    rmw_dsoftbus::GraphCache::instance().register_subscription(
        topic_name,
        sub_impl->type_name.c_str(),
        node->name,
        node->namespace_,
        qos_policies,
        &rmw_gid,
        sub_impl);
    fprintf(stderr, "[DEBUG][rmw_create_subscription] Registered subscription with GraphCache: %s\n",
            topic_name);
    fflush(stderr);

    // Allocate rmw_subscription_t
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    auto subscription = static_cast<rmw_subscription_t*>(allocator.allocate(sizeof(rmw_subscription_t), allocator.state));
    if (!subscription) {
        delete sub_impl;
        RMW_SET_ERROR_MSG("failed to allocate rmw_subscription_t");
        return nullptr;
    }

    subscription->implementation_identifier = rmw_get_implementation_identifier();
    subscription->data = sub_impl;
    subscription->topic_name = sub_impl->topic_name.c_str();
    // Initialize options struct (QoS stored in impl)
    subscription->options.rmw_specific_subscription_payload = nullptr;
    subscription->options.ignore_local_publications = false;
    subscription->options.require_unique_network_flow_endpoints = false;
    subscription->can_loan_messages = false;
    subscription->is_cft_enabled = false;

    return subscription;
}

rmw_ret_t rmw_destroy_subscription(rmw_node_t * node, rmw_subscription_t * subscription)
{
    if (!node) {
        RMW_SET_ERROR_MSG("node is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!subscription) {
        RMW_SET_ERROR_MSG("subscription is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (subscription->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    auto sub_impl = static_cast<rmw_dsoftbus::SubscriptionImpl*>(subscription->data);
    if (sub_impl) {
        // Phase 2.2: Unregister subscription from GraphCache
        rmw_gid_t rmw_gid;
        rmw_gid.implementation_identifier = rmw_get_implementation_identifier();
        memcpy(rmw_gid.data, sub_impl->gid.data, sizeof(rmw_gid.data));
        rmw_dsoftbus::GraphCache::instance().unregister_endpoint(&rmw_gid);
        fprintf(stderr, "[DEBUG][rmw_destroy_subscription] Unregistered subscription from GraphCache: %s\n",
                sub_impl->topic_name.c_str());
        fflush(stderr);

        // Unregister from SessionManager
        rmw_dsoftbus::SessionManager::instance().unregister_subscription(sub_impl->topic_name);
        delete sub_impl;
    }

    // Deallocate using Foundation layer allocator
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    allocator.deallocate(subscription, allocator.state);

    return RMW_RET_OK;
}

rmw_ret_t rmw_take(
    const rmw_subscription_t * subscription,
    void * ros_message,
    bool * taken,
    rmw_subscription_allocation_t * allocation)
{
    (void)allocation;

    if (!subscription) {
        RMW_SET_ERROR_MSG("subscription is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!ros_message) {
        RMW_SET_ERROR_MSG("ros_message is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!taken) {
        RMW_SET_ERROR_MSG("taken is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (subscription->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    auto sub_impl = static_cast<rmw_dsoftbus::SubscriptionImpl*>(subscription->data);
    if (!sub_impl) {
        RMW_SET_ERROR_MSG("subscription impl is null");
        return RMW_RET_ERROR;
    }

    // Check message queue (populated by SessionManager callback)
    std::lock_guard<std::mutex> lock(sub_impl->queue_mutex);

    if (sub_impl->message_queue.empty()) {
        *taken = false;
        return RMW_RET_OK;
    }

    auto& msg_item = sub_impl->message_queue.front();

    // Deserialize message from CDR format
    bool deserialization_success = false;

    // Check if we have introspection-based type support
    if (sub_impl->type_support) {
        // Use generic introspection-based deserializer
        fprintf(stderr, "[DEBUG][rmw_take] using generic introspection deserializer\n");
        fflush(stderr);

        deserialization_success = rmw_dsoftbus_deserialize_ros_message(
            msg_item.data.data(),
            msg_item.data.size(),
            sub_impl->type_support,
            ros_message);

        if (!deserialization_success) {
            fprintf(stderr, "[ERROR][rmw_take] introspection deserialization failed\n");
            fflush(stderr);
        }
    } else {
        // Fallback to old callback-based deserialization
        fprintf(stderr, "[DEBUG][rmw_take] using callback-based deserializer\n");
        fflush(stderr);

        bool use_fallback = (sub_impl->deserialize == nullptr && sub_impl->message_size == 0);
        deserialization_success = deserialize_message_cdr(
            msg_item.data.data(),
            msg_item.data.size(),
            sub_impl->message_size,
            sub_impl->deserialize,
            ros_message,
            use_fallback);
    }

    if (!deserialization_success) {
        RMW_SET_ERROR_MSG("failed to deserialize CDR message");
        *taken = false;
        return RMW_RET_ERROR;
    }

    // Drain pipe notification byte
    if (sub_impl->pipe_fd[0] >= 0) {
        char c;
        while (read(sub_impl->pipe_fd[0], &c, 1) > 0) {}
    }

    sub_impl->message_queue.pop();
    *taken = true;

    return RMW_RET_OK;
}

rmw_ret_t rmw_take_with_info(
    const rmw_subscription_t * subscription,
    void * ros_message,
    bool * taken,
    rmw_message_info_t * message_info,
    rmw_subscription_allocation_t * allocation)
{
    (void)allocation;

    if (!subscription) {
        RMW_SET_ERROR_MSG("subscription is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!ros_message) {
        RMW_SET_ERROR_MSG("ros_message is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!taken) {
        RMW_SET_ERROR_MSG("taken is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!message_info) {
        RMW_SET_ERROR_MSG("message_info is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (subscription->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    auto sub_impl = static_cast<rmw_dsoftbus::SubscriptionImpl*>(subscription->data);
    if (!sub_impl) {
        RMW_SET_ERROR_MSG("subscription impl is null");
        return RMW_RET_ERROR;
    }

    std::lock_guard<std::mutex> lock(sub_impl->queue_mutex);

    if (sub_impl->message_queue.empty()) {
        *taken = false;
        return RMW_RET_OK;
    }

    auto& msg_item = sub_impl->message_queue.front();

    // Deserialize message from CDR format
    bool deserialization_success = false;

    // Check if we have introspection-based type support
    if (sub_impl->type_support) {
        // Use generic introspection-based deserializer
        fprintf(stderr, "[DEBUG][rmw_take_with_info] using generic introspection deserializer\n");
        fflush(stderr);

        deserialization_success = rmw_dsoftbus_deserialize_ros_message(
            msg_item.data.data(),
            msg_item.data.size(),
            sub_impl->type_support,
            ros_message);

        if (!deserialization_success) {
            fprintf(stderr, "[ERROR][rmw_take_with_info] introspection deserialization failed\n");
            fflush(stderr);
        }
    } else {
        // Fallback to old callback-based deserialization
        fprintf(stderr, "[DEBUG][rmw_take_with_info] using callback-based deserializer\n");
        fflush(stderr);

        bool use_fallback = (sub_impl->deserialize == nullptr && sub_impl->message_size == 0);
        deserialization_success = deserialize_message_cdr(
            msg_item.data.data(),
            msg_item.data.size(),
            sub_impl->message_size,
            sub_impl->deserialize,
            ros_message,
            use_fallback);
    }

    if (!deserialization_success) {
        RMW_SET_ERROR_MSG("failed to deserialize CDR message");
        *taken = false;
        return RMW_RET_ERROR;
    }

    // Fill message info from the message item
    message_info->source_timestamp.sec = msg_item.timestamp_ns / 1000000000ULL;
    message_info->source_timestamp.nsec = msg_item.timestamp_ns % 1000000000ULL;
    message_info->received_timestamp = message_info->source_timestamp;
    message_info->publication_sequence_number = msg_item.sequence_number;
    message_info->reception_sequence_number = msg_item.sequence_number;
    message_info->from_intra_process = msg_item.from_intra_process;

    // Copy publisher GID
    memcpy(&message_info->publisher_gid.data, msg_item.publisher_gid.data,
           sizeof(message_info->publisher_gid.data));

    // Drain pipe notification byte
    if (sub_impl->pipe_fd[0] >= 0) {
        char c;
        while (read(sub_impl->pipe_fd[0], &c, 1) > 0) {}
    }

    sub_impl->message_queue.pop();
    *taken = true;

    return RMW_RET_OK;
}

rmw_ret_t rmw_take_serialized_message(
    const rmw_subscription_t * subscription,
    rmw_serialized_message_t * serialized_message,
    bool * taken,
    rmw_subscription_allocation_t * allocation)
{
    (void)allocation;

    if (!subscription) {
        RMW_SET_ERROR_MSG("subscription is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!serialized_message) {
        RMW_SET_ERROR_MSG("serialized_message is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!taken) {
        RMW_SET_ERROR_MSG("taken is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (subscription->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    auto sub_impl = static_cast<rmw_dsoftbus::SubscriptionImpl*>(subscription->data);
    if (!sub_impl) {
        RMW_SET_ERROR_MSG("subscription impl is null");
        return RMW_RET_ERROR;
    }

    // Check message queue (populated by SessionManager callback)
    std::lock_guard<std::mutex> lock(sub_impl->queue_mutex);

    if (sub_impl->message_queue.empty()) {
        *taken = false;
        return RMW_RET_OK;
    }

    auto& msg_item = sub_impl->message_queue.front();

    // Copy serialized data
    if (serialized_message->buffer_capacity < msg_item.data.size()) {
        rmw_ret_t ret = rmw_serialized_message_resize(serialized_message, msg_item.data.size());
        if (ret != RMW_RET_OK) {
            return ret;
        }
    }

    memcpy(serialized_message->buffer, msg_item.data.data(), msg_item.data.size());
    serialized_message->buffer_length = msg_item.data.size();

    sub_impl->message_queue.pop();
    *taken = true;

    return RMW_RET_OK;
}

rmw_ret_t rmw_take_serialized_message_with_info(
    const rmw_subscription_t * subscription,
    rmw_serialized_message_t * serialized_message,
    bool * taken,
    rmw_message_info_t * message_info,
    rmw_subscription_allocation_t * allocation)
{
    (void)allocation;

    if (!subscription) {
        RMW_SET_ERROR_MSG("subscription is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!serialized_message) {
        RMW_SET_ERROR_MSG("serialized_message is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!taken) {
        RMW_SET_ERROR_MSG("taken is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!message_info) {
        RMW_SET_ERROR_MSG("message_info is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (subscription->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    auto sub_impl = static_cast<rmw_dsoftbus::SubscriptionImpl*>(subscription->data);
    if (!sub_impl) {
        RMW_SET_ERROR_MSG("subscription impl is null");
        return RMW_RET_ERROR;
    }

    std::lock_guard<std::mutex> lock(sub_impl->queue_mutex);

    if (sub_impl->message_queue.empty()) {
        *taken = false;
        return RMW_RET_OK;
    }

    auto& msg_item = sub_impl->message_queue.front();

    // Copy serialized data
    if (serialized_message->buffer_capacity < msg_item.data.size()) {
        rmw_ret_t ret = rmw_serialized_message_resize(serialized_message, msg_item.data.size());
        if (ret != RMW_RET_OK) {
            return ret;
        }
    }

    memcpy(serialized_message->buffer, msg_item.data.data(), msg_item.data.size());
    serialized_message->buffer_length = msg_item.data.size();

    // Fill message info from the message item
    message_info->source_timestamp.sec = msg_item.timestamp_ns / 1000000000ULL;
    message_info->source_timestamp.nsec = msg_item.timestamp_ns % 1000000000ULL;
    message_info->received_timestamp = message_info->source_timestamp;
    message_info->publication_sequence_number = msg_item.sequence_number;
    message_info->reception_sequence_number = msg_item.sequence_number;
    message_info->from_intra_process = msg_item.from_intra_process;

    // Copy publisher GID
    memcpy(&message_info->publisher_gid.data, msg_item.publisher_gid.data,
           sizeof(message_info->publisher_gid.data));

    // Drain pipe notification byte
    if (sub_impl->pipe_fd[0] >= 0) {
        char c;
        while (read(sub_impl->pipe_fd[0], &c, 1) > 0) {}
    }

    sub_impl->message_queue.pop();
    *taken = true;

    return RMW_RET_OK;
}

rmw_ret_t rmw_subscription_count_matched_publishers(
    const rmw_subscription_t * subscription,
    size_t * publisher_count)
{
    if (!subscription) {
        RMW_SET_ERROR_MSG("subscription is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!publisher_count) {
        RMW_SET_ERROR_MSG("publisher_count is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (subscription->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    auto sub_impl = static_cast<rmw_dsoftbus::SubscriptionImpl*>(subscription->data);
    if (!sub_impl) {
        RMW_SET_ERROR_MSG("subscription impl is null");
        return RMW_RET_ERROR;
    }

    // Phase 2.4: Use GraphCache to count matching publishers
    *publisher_count = rmw_dsoftbus::GraphCache::instance().count_publishers(
        sub_impl->topic_name.c_str());

    return RMW_RET_OK;
}

rmw_ret_t rmw_subscription_get_actual_qos(
    const rmw_subscription_t * subscription,
    rmw_qos_profile_t * qos)
{
    if (!subscription) {
        RMW_SET_ERROR_MSG("subscription is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!qos) {
        RMW_SET_ERROR_MSG("qos is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (subscription->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    auto sub_impl = static_cast<rmw_dsoftbus::SubscriptionImpl*>(subscription->data);
    if (!sub_impl) {
        RMW_SET_ERROR_MSG("subscription impl is null");
        return RMW_RET_ERROR;
    }

    qos->history = RMW_QOS_POLICY_HISTORY_KEEP_LAST;
    qos->depth = sub_impl->queue_depth;
    qos->reliability = sub_impl->reliable ?
        RMW_QOS_POLICY_RELIABILITY_RELIABLE :
        RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT;
    qos->durability = RMW_QOS_POLICY_DURABILITY_VOLATILE;
    qos->deadline = RMW_QOS_DEADLINE_DEFAULT;
    qos->lifespan = RMW_QOS_LIFESPAN_DEFAULT;
    qos->liveliness = RMW_QOS_POLICY_LIVELINESS_AUTOMATIC;
    qos->liveliness_lease_duration = RMW_QOS_LIVELINESS_LEASE_DURATION_DEFAULT;

    return RMW_RET_OK;
}

rmw_ret_t rmw_take_loaned_message(
    const rmw_subscription_t * subscription,
    void ** loaned_message,
    bool * taken,
    rmw_subscription_allocation_t * allocation)
{
    (void)subscription;
    (void)loaned_message;
    (void)taken;
    (void)allocation;
    RMW_SET_ERROR_MSG("rmw_take_loaned_message not supported");
    return RMW_RET_UNSUPPORTED;
}

rmw_ret_t rmw_take_loaned_message_with_info(
    const rmw_subscription_t * subscription,
    void ** loaned_message,
    bool * taken,
    rmw_message_info_t * message_info,
    rmw_subscription_allocation_t * allocation)
{
    (void)subscription;
    (void)loaned_message;
    (void)taken;
    (void)message_info;
    (void)allocation;
    RMW_SET_ERROR_MSG("rmw_take_loaned_message_with_info not supported");
    return RMW_RET_UNSUPPORTED;
}

rmw_ret_t rmw_return_loaned_message_from_subscription(
    const rmw_subscription_t * subscription,
    void * loaned_message)
{
    (void)subscription;
    (void)loaned_message;
    RMW_SET_ERROR_MSG("rmw_return_loaned_message_from_subscription not supported");
    return RMW_RET_UNSUPPORTED;
}

rmw_ret_t rmw_take_sequence(
    const rmw_subscription_t * subscription,
    size_t count,
    rmw_message_sequence_t * message_sequence,
    rmw_message_info_sequence_t * message_info_sequence,
    size_t * taken,
    rmw_subscription_allocation_t * allocation)
{
    (void)allocation;

    // Validate arguments
    if (!subscription) {
        RMW_SET_ERROR_MSG("subscription is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!message_sequence) {
        RMW_SET_ERROR_MSG("message_sequence is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!message_info_sequence) {
        RMW_SET_ERROR_MSG("message_info_sequence is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!taken) {
        RMW_SET_ERROR_MSG("taken is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (count == 0) {
        RMW_SET_ERROR_MSG("count is zero");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (message_sequence->capacity < count) {
        RMW_SET_ERROR_MSG("message_sequence capacity is less than count");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (message_info_sequence->capacity < count) {
        RMW_SET_ERROR_MSG("message_info_sequence capacity is less than count");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (subscription->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    auto sub_impl = static_cast<rmw_dsoftbus::SubscriptionImpl*>(subscription->data);
    if (!sub_impl) {
        RMW_SET_ERROR_MSG("subscription impl is null");
        return RMW_RET_ERROR;
    }

    std::lock_guard<std::mutex> lock(sub_impl->queue_mutex);

    // Take up to 'count' messages from the queue
    *taken = 0;
    size_t max_to_take = std::min(count, sub_impl->message_queue.size());

    for (size_t i = 0; i < max_to_take; i++) {
        if (sub_impl->message_queue.empty()) {
            break;  // No more messages available
        }

        auto& msg_item = sub_impl->message_queue.front();

        // Deserialize message from CDR format
        bool deserialization_success = false;
        void* ros_message = message_sequence->data[i];

        // Check if we have introspection-based type support
        if (sub_impl->type_support) {
            // Use generic introspection-based deserializer
            deserialization_success = rmw_dsoftbus_deserialize_ros_message(
                msg_item.data.data(),
                msg_item.data.size(),
                sub_impl->type_support,
                ros_message);
        } else {
            // Fallback to old callback-based deserialization
            bool use_fallback = (sub_impl->deserialize == nullptr && sub_impl->message_size == 0);
            deserialization_success = deserialize_message_cdr(
                msg_item.data.data(),
                msg_item.data.size(),
                sub_impl->message_size,
                sub_impl->deserialize,
                ros_message,
                use_fallback);
        }

        if (!deserialization_success) {
            // Failed to deserialize - this is an error, but we've already
            // taken some messages successfully. We'll leave the queue as is
            // and return what we have so far.
            break;
        }

        // Populate message info from message item fields
        message_info_sequence->data[i].source_timestamp.sec = msg_item.timestamp_ns / 1000000000ULL;
        message_info_sequence->data[i].source_timestamp.nsec = msg_item.timestamp_ns % 1000000000ULL;
        message_info_sequence->data[i].received_timestamp = message_info_sequence->data[i].source_timestamp;
        message_info_sequence->data[i].publication_sequence_number = msg_item.sequence_number;
        message_info_sequence->data[i].reception_sequence_number = msg_item.sequence_number;
        message_info_sequence->data[i].from_intra_process = msg_item.from_intra_process;
        memcpy(&message_info_sequence->data[i].publisher_gid.data, msg_item.publisher_gid.data,
               sizeof(message_info_sequence->data[i].publisher_gid.data));

        // Remove message from queue
        sub_impl->message_queue.pop();
        (*taken)++;
    }

    // Drain pipe notification bytes (one per message taken)
    if (sub_impl->pipe_fd[0] >= 0 && *taken > 0) {
        char c;
        for (size_t i = 0; i < *taken; i++) {
            read(sub_impl->pipe_fd[0], &c, 1);
        }
        // Drain any remaining bytes
        while (read(sub_impl->pipe_fd[0], &c, 1) > 0) {}
    }

    // Update sequence sizes
    message_sequence->size = *taken;
    message_info_sequence->size = *taken;

    return RMW_RET_OK;
}

}  // extern "C"
