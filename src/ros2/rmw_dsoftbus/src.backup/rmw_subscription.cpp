// Copyright (c) 2024 ROS2 KaihongOS Port Project
// Licensed under the Apache License, Version 2.0

#include "rmw_dsoftbus/rmw_dsoftbus.h"
#include "rmw_dsoftbus/types.h"
#include <rcutils/allocator.h>  // Foundation layer memory management
#include "rmw_dsoftbus/qos_mapper.h"
#include "rmw_dsoftbus/cdr_serializer.h"
#include "rmw_dsoftbus/socket_direct.h"

#include <chrono>
#include <cstring>
#include <memory>
#include <fcntl.h>
#include <unistd.h>

// Forward declarations for dsoftbus adapter
namespace rmw_dsoftbus {
    extern int create_topic_subscription(const char* topic_name, const char* type_name, void* subscription_impl);
    extern void destroy_topic_subscription(const char* topic_name);
    extern std::string encode_topic_for_session(const char* topic_name);
}

// rosidl_runtime_c__String structure (from rosidl_runtime_c/string.h)
struct rosidl_runtime_c__String {
    char* data;
    size_t size;
    size_t capacity;
};

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

    // Allocate subscription implementation
    auto sub_impl = new (std::nothrow) rmw_dsoftbus::SubscriptionImpl();
    if (!sub_impl) {
        RMW_SET_ERROR_MSG("failed to allocate subscription impl");
        return nullptr;
    }

    sub_impl->node = node_impl;
    sub_impl->topic_name = topic_name;
    sub_impl->type_name = type_support->typesupport_identifier;

    // Map ROS2 QoS profile to dsoftbus QoS config (extensible)
    sub_impl->qos_config = rmw_dsoftbus::map_qos_profile(qos_policies);

    // Legacy fields (for backward compatibility)
    sub_impl->queue_depth = sub_impl->qos_config.history_depth;
    sub_impl->reliable = (sub_impl->qos_config.reliability == rmw_dsoftbus::DSOFTBUS_RELIABILITY_FULL);

    // Encode topic name for dsoftbus
    sub_impl->encoded_topic = rmw_dsoftbus::encode_topic_for_session(topic_name);

    // Check if using introspection typesupport
    bool is_introspection = type_support->typesupport_identifier &&
        (strstr(type_support->typesupport_identifier, "introspection") != nullptr);

    if (is_introspection) {
        // Introspection typesupport - data is rosidl_typesupport_introspection_c__MessageMembers
        // Don't try to extract callbacks as the structure is different
        fprintf(stderr, "[DEBUG][rmw_create_subscription] Using introspection typesupport\n");
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

    // Create pipe for wait notification
    if (pipe(sub_impl->pipe_fd) != 0) {
        delete sub_impl;
        RMW_SET_ERROR_MSG("failed to create pipe for subscription");
        return nullptr;
    }

    // Make read end non-blocking
    int flags = fcntl(sub_impl->pipe_fd[0], F_GETFL, 0);
    fcntl(sub_impl->pipe_fd[0], F_SETFL, flags | O_NONBLOCK);

    // === Backend Selection for Subscription ===
    bool use_dsoftbus = (rmw_dsoftbus::get_active_backend() == rmw_dsoftbus::BackendType::DSOFTBUS ||
                         rmw_dsoftbus::get_active_backend() == rmw_dsoftbus::BackendType::AUTO);

    if (rmw_dsoftbus::get_active_backend() == rmw_dsoftbus::BackendType::SOCKET_DIRECT) {
        // Create socket_direct listener for this topic
        int listener_id = socket_direct_create_listener(topic_name);
        if (listener_id < 0) {
            close(sub_impl->pipe_fd[0]);
            close(sub_impl->pipe_fd[1]);
            delete sub_impl;
            RMW_SET_ERROR_MSG("failed to create socket_direct listener");
            return nullptr;
        }
        sub_impl->socket_direct_listener_id = listener_id;
        int port = socket_direct_get_listener_port(listener_id);
        fprintf(stderr, "[INFO][rmw_create_subscription] socket_direct listener created: id=%d, port=%d, topic=%s\n",
                listener_id, port, topic_name);
    } else if (use_dsoftbus) {
        // Register with dsoftbus - creates session server for this topic
        int server_id = rmw_dsoftbus::create_topic_subscription(
            topic_name,
            type_support->typesupport_identifier,
            sub_impl);
        if (server_id < 0) {
            close(sub_impl->pipe_fd[0]);
            close(sub_impl->pipe_fd[1]);
            delete sub_impl;
            RMW_SET_ERROR_MSG("failed to create dsoftbus topic subscription");
            return nullptr;
        }
    } else {
        // INTRA_PROCESS mode - no network subscription needed
        fprintf(stderr, "[INFO][rmw_create_subscription] intra-process mode, no network subscription\n");
    }

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
    subscription->options = nullptr;  // QoS stored in impl
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
        // Cleanup based on backend type
        if (sub_impl->socket_direct_listener_id >= 0) {
            // socket_direct backend - destroy listener
            socket_direct_destroy_listener(sub_impl->socket_direct_listener_id);
        } else {
            // dsoftbus backend - unregister from dsoftbus
            rmw_dsoftbus::destroy_topic_subscription(sub_impl->topic_name.c_str());
        }
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

    // === socket_direct backend: poll for messages ===
    if (sub_impl->socket_direct_listener_id >= 0) {
        static thread_local std::vector<uint8_t> recv_buffer(65536);
        char sender_ip[64] = {0};

        // Try to receive a message (non-blocking, 0 timeout)
        int received = socket_direct_recv(
            sub_impl->socket_direct_listener_id,
            recv_buffer.data(),
            static_cast<int>(recv_buffer.size()),
            sender_ip,
            sizeof(sender_ip));

        if (received <= 0) {
            // No message available or timeout
            *taken = false;
            return RMW_RET_OK;
        }

        // Got a message - deserialize it
        bool use_fallback = (sub_impl->deserialize == nullptr && sub_impl->message_size == 0);
        if (!deserialize_message_cdr(
                recv_buffer.data(),
                static_cast<size_t>(received),
                sub_impl->message_size,
                sub_impl->deserialize,
                ros_message,
                use_fallback)) {
            RMW_SET_ERROR_MSG("failed to deserialize CDR message from socket_direct");
            *taken = false;
            return RMW_RET_ERROR;
        }

        fprintf(stderr, "[DEBUG][rmw_take] socket_direct received %d bytes from %s\n",
                received, sender_ip);
        *taken = true;
        return RMW_RET_OK;
    }

    // === dsoftbus backend: check message queue ===
    std::lock_guard<std::mutex> lock(sub_impl->queue_mutex);

    if (sub_impl->message_queue.empty()) {
        *taken = false;
        return RMW_RET_OK;
    }

    auto& msg_item = sub_impl->message_queue.front();

    // Deserialize message from CDR format
    // Use fallback if no deserialize function and no message_size (introspection typesupport)
    bool use_fallback = (sub_impl->deserialize == nullptr && sub_impl->message_size == 0);
    if (!deserialize_message_cdr(
            msg_item.data.data(),
            msg_item.data.size(),
            sub_impl->message_size,
            sub_impl->deserialize,
            ros_message,
            use_fallback)) {
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
    // Use fallback if no deserialize function and no message_size (introspection typesupport)
    bool use_fallback = (sub_impl->deserialize == nullptr && sub_impl->message_size == 0);
    if (!deserialize_message_cdr(
            msg_item.data.data(),
            msg_item.data.size(),
            sub_impl->message_size,
            sub_impl->deserialize,
            ros_message,
            use_fallback)) {
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
    memcpy(message_info->publisher_gid, msg_item.publisher_gid.data,
           sizeof(message_info->publisher_gid));

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

    // === socket_direct backend: poll for serialized messages ===
    if (sub_impl->socket_direct_listener_id >= 0) {
        // Use the provided buffer directly - don't try to resize
        // The caller is responsible for providing a large enough buffer
        if (serialized_message->buffer_capacity == 0 || serialized_message->buffer == nullptr) {
            RMW_SET_ERROR_MSG("serialized_message buffer not allocated");
            *taken = false;
            return RMW_RET_INVALID_ARGUMENT;
        }

        char sender_ip[64] = {0};

        // Try to receive a message (non-blocking, 0 timeout)
        int received = socket_direct_recv(
            sub_impl->socket_direct_listener_id,
            serialized_message->buffer,
            static_cast<int>(serialized_message->buffer_capacity),
            sender_ip,
            sizeof(sender_ip));

        if (received <= 0) {
            // No message available or timeout
            *taken = false;
            return RMW_RET_OK;
        }

        serialized_message->buffer_length = static_cast<size_t>(received);
        fprintf(stderr, "[DEBUG][rmw_take_serialized] socket_direct received %d bytes from %s\n",
                received, sender_ip);
        *taken = true;
        return RMW_RET_OK;
    }

    // === dsoftbus backend: check message queue ===
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
    memcpy(message_info->publisher_gid, msg_item.publisher_gid.data,
           sizeof(message_info->publisher_gid));

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

    // TODO: Implement discovery-based publisher counting
    *publisher_count = 0;

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
        // Use fallback if no deserialize function and no message_size (introspection typesupport)
        bool use_fallback = (sub_impl->deserialize == nullptr && sub_impl->message_size == 0);
        void* ros_message = message_sequence->data[i];
        if (!deserialize_message_cdr(
                msg_item.data.data(),
                msg_item.data.size(),
                sub_impl->message_size,
                sub_impl->deserialize,
                ros_message,
                use_fallback)) {
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
        memcpy(message_info_sequence->data[i].publisher_gid, msg_item.publisher_gid.data,
               sizeof(message_info_sequence->data[i].publisher_gid));

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
