// Copyright (c) 2024 ROS2 KaihongOS Port Project
// Licensed under the Apache License, Version 2.0

#include "rmw_dsoftbus/rmw_dsoftbus.h"
#include "rmw_dsoftbus/types.h"
#include <rcutils/allocator.h>  // Foundation layer memory management
#include "rmw_dsoftbus/qos_mapper.h"
#include "rmw_dsoftbus/cdr_serializer.h"
#include "rmw_dsoftbus/socket_direct.h"

#include <cstring>
#include <ctime>
#include <memory>
#include <vector>
#include <unistd.h>

// Forward declarations for dsoftbus adapter
namespace rmw_dsoftbus {
    extern int open_session(const char* peer_network_id, const char* group_id, const char* session_name);
    extern void close_session(int session_id);
    extern int send_bytes(int session_id, const void* data, unsigned int len);
    extern int publish_to_topic(const char* topic_name, const void* data, unsigned int len,
                                uint64_t sequence_number, const uint8_t* publisher_gid);
    extern std::string encode_topic_for_session(const char* topic_name);
    extern int create_topic_subscription(const char* topic_name, const char* type_name, void* subscription_impl);
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

// Helper: serialize std_msgs/String using CDR
static bool serialize_std_msgs_string(
    const void* ros_message,
    std::vector<uint8_t>& output)
{
    using namespace rmw_dsoftbus::cdr;

    const auto* msg = static_cast<const std_msgs__msg__String*>(ros_message);
    if (!msg) {
        return false;
    }

    // Get string data and size
    const char* str_data = msg->data.data ? msg->data.data : "";
    size_t str_len = msg->data.size;

    fprintf(stderr, "[DEBUG][serialize_std_msgs_string] str_len=%zu, str_data='%s'\n",
            str_len, str_data);
    fflush(stderr);

    // CDR string: uint32_t length (including null terminator) + chars + null
    size_t serialized_size = 4 + str_len + 1;  // 4 bytes for length + string + null

    CdrSerializer ser(CDR_ENCAPSULATION_SIZE + serialized_size);
    ser.write_encapsulation();

    // Write string length (including null terminator)
    uint32_t len_with_null = static_cast<uint32_t>(str_len + 1);
    ser.serialize_pod(&len_with_null, 4, CDR_ALIGN_4);

    // Write string data including null terminator
    if (str_len > 0) {
        ser.serialize_raw(str_data, str_len);
    }
    uint8_t null_byte = 0;
    ser.serialize_raw(&null_byte, 1);

    output = ser.finalize();
    return true;
}

// Helper: POD serialization with CDR encapsulation
static bool serialize_message_cdr(
    const void* ros_message,
    size_t message_size,
    rmw_dsoftbus::GetSerializedSizeFn get_size_fn,
    rmw_dsoftbus::SerializeFn serialize_fn,
    std::vector<uint8_t>& output,
    const char* topic_name = nullptr)
{
    using namespace rmw_dsoftbus::cdr;

    // Check if this is a String topic (heuristic: topic contains "chatter" or type is unknown)
    // For introspection typesupport, we need to handle known types specially
    if (message_size == 0 && !get_size_fn && !serialize_fn) {
        // DISABLED: Fallback serialization is unsafe - it assumes std_msgs/String
        // which causes segfaults when the actual type is different
        fprintf(stderr, "[ERROR][serialize_message_cdr] No serialization method available "
                "(message_size=0, get_size_fn=null, serialize_fn=null) for topic=%s\n",
                topic_name ? topic_name : "unknown");
        fflush(stderr);
        return false;  // Return error instead of crashing

        // OLD CODE (UNSAFE):
        // fprintf(stderr, "[DEBUG][serialize_message_cdr] Using fallback serialization (std_msgs/String)\n");
        // fflush(stderr);
        // return serialize_std_msgs_string(ros_message, output);
    }

    // Determine serialized size
    size_t serialized_size = 0;
    if (get_size_fn) {
        serialized_size = get_size_fn(ros_message);
    } else if (message_size > 0) {
        serialized_size = message_size;
    } else {
        return false;
    }

    // Create CDR serializer with encapsulation
    CdrSerializer ser(CDR_ENCAPSULATION_SIZE + serialized_size);
    ser.write_encapsulation();

    // Serialize the message
    if (serialize_fn) {
        // Use custom serialization callback
        std::vector<uint8_t> temp_buffer(serialized_size);
        if (!serialize_fn(ros_message, temp_buffer.data(), serialized_size)) {
            return false;
        }
        ser.serialize_raw(temp_buffer.data(), serialized_size);
    } else if (message_size > 0) {
        // POD serialization - direct memcpy
        ser.serialize_pod(ros_message, message_size, CDR_ALIGN_1);
    } else {
        return false;
    }

    output = ser.finalize();
    return true;
}

extern "C"
{

rmw_publisher_t * rmw_create_publisher(
    const rmw_node_t * node,
    const rosidl_message_type_support_t * type_support,
    const char * topic_name,
    const rmw_qos_profile_t * qos_policies,
    const rmw_publisher_options_t * publisher_options)
{
    (void)publisher_options;

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

    // Allocate publisher implementation
    auto pub_impl = new (std::nothrow) rmw_dsoftbus::PublisherImpl();
    if (!pub_impl) {
        RMW_SET_ERROR_MSG("failed to allocate publisher impl");
        return nullptr;
    }

    pub_impl->node = node_impl;
    pub_impl->topic_name = topic_name;
    pub_impl->type_name = type_support->typesupport_identifier;

    // Map ROS2 QoS profile to dsoftbus QoS config (extensible)
    pub_impl->qos_config = rmw_dsoftbus::map_qos_profile(qos_policies);

    // Legacy fields (for backward compatibility)
    pub_impl->history_depth = pub_impl->qos_config.history_depth;
    pub_impl->reliable = (pub_impl->qos_config.reliability == rmw_dsoftbus::DSOFTBUS_RELIABILITY_FULL);

    // Encode topic name for dsoftbus
    pub_impl->encoded_topic = rmw_dsoftbus::encode_topic_for_session(topic_name);

    // Handle type support - check if introspection or regular
    fprintf(stderr, "[DEBUG][rmw_create_publisher] type_support=%p, data=%p, typesupport_id=%s\n",
            (void*)type_support, (void*)type_support->data,
            type_support->typesupport_identifier ? type_support->typesupport_identifier : "NULL");
    fflush(stderr);

    // For introspection typesupport, we need to use introspection-based serialization
    // The data pointer is rosidl_typesupport_introspection_c__MessageMembers, not callbacks
    const char* introspection_id = "rosidl_typesupport_introspection_c";
    bool is_introspection = type_support->typesupport_identifier &&
        (strstr(type_support->typesupport_identifier, "introspection") != nullptr);

    if (is_introspection) {
        fprintf(stderr, "[DEBUG][rmw_create_publisher] Using introspection typesupport\n");
        // For introspection typesupport, we'll use CDR serialization without callbacks
        // The message_size and serialize/deserialize will be handled by CDR serializer
        pub_impl->message_size = 0;
        pub_impl->get_serialized_size = nullptr;
        pub_impl->serialize = nullptr;
    } else if (type_support->data) {
        // For regular typesupport, use the callbacks
        auto callbacks = static_cast<const rosidl_message_type_support_callbacks_t*>(type_support->data);
        fprintf(stderr, "[DEBUG][rmw_create_publisher] callbacks=%p, message_size=%zu\n",
                (void*)callbacks, callbacks->message_size);
        fprintf(stderr, "[DEBUG][rmw_create_publisher] callbacks->get_serialized_size=%p, callbacks->serialize=%p\n",
                (void*)callbacks->get_serialized_size, (void*)callbacks->serialize);
        fflush(stderr);

        if (callbacks->message_size > 0) {
            pub_impl->message_size = callbacks->message_size;
        }
        if (callbacks->get_serialized_size) {
            pub_impl->get_serialized_size = reinterpret_cast<rmw_dsoftbus::GetSerializedSizeFn>(
                callbacks->get_serialized_size);
        }
        if (callbacks->serialize) {
            pub_impl->serialize = reinterpret_cast<rmw_dsoftbus::SerializeFn>(
                callbacks->serialize);
        }
    }

    // Generate unique GID for this publisher
    // Use combination of process ID, timestamp, and counter
    static uint64_t gid_counter = 0;
    uint64_t timestamp = static_cast<uint64_t>(time(nullptr));
    uint64_t pid = static_cast<uint64_t>(getpid());
    memcpy(pub_impl->gid.data, &pid, sizeof(pid));
    memcpy(pub_impl->gid.data + 8, &timestamp, sizeof(timestamp));
    memcpy(pub_impl->gid.data + 16, &gid_counter, sizeof(gid_counter));
    gid_counter++;

    // Note: Sessions to subscribers will be established on first publish
    // when we discover peers with matching topic subscription servers

    // === Socket Direct Backend Setup ===
    if (rmw_dsoftbus::get_active_backend() == rmw_dsoftbus::BackendType::SOCKET_DIRECT) {
        // Add all configured peers for this topic
        const auto& peers = rmw_dsoftbus::get_socket_peers();
        int peer_port = socket_direct_topic_to_port(topic_name);

        for (const auto& peer_ip : peers) {
            if (socket_direct_add_peer(topic_name, peer_ip.c_str(), peer_port) == 0) {
                fprintf(stderr, "[INFO][rmw_create_publisher] Added socket_direct peer: %s:%d for topic %s\n",
                        peer_ip.c_str(), peer_port, topic_name);
            } else {
                fprintf(stderr, "[WARN][rmw_create_publisher] Failed to add peer: %s:%d\n",
                        peer_ip.c_str(), peer_port);
            }
        }
        fflush(stderr);
    }

    // Allocate rmw_publisher_t using Foundation layer allocator
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    auto publisher = static_cast<rmw_publisher_t*>(allocator.allocate(sizeof(rmw_publisher_t), allocator.state));
    if (!publisher) {
        delete pub_impl;
        RMW_SET_ERROR_MSG("failed to allocate rmw_publisher_t");
        return nullptr;
    }

    publisher->implementation_identifier = rmw_get_implementation_identifier();
    publisher->data = pub_impl;
    publisher->topic_name = pub_impl->topic_name.c_str();
    publisher->options = nullptr;  // QoS stored in impl
    publisher->can_loan_messages = false;

    return publisher;
}

rmw_ret_t rmw_destroy_publisher(rmw_node_t * node, rmw_publisher_t * publisher)
{
    if (!node) {
        RMW_SET_ERROR_MSG("node is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!publisher) {
        RMW_SET_ERROR_MSG("publisher is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (publisher->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    auto pub_impl = static_cast<rmw_dsoftbus::PublisherImpl*>(publisher->data);
    if (pub_impl) {
        // Close all sessions
        for (int sid : pub_impl->session_ids) {
            if (sid >= 0) {
                rmw_dsoftbus::close_session(sid);
            }
        }
        delete pub_impl;
    }

    // Deallocate using Foundation layer allocator
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    allocator.deallocate(publisher, allocator.state);

    return RMW_RET_OK;
}

rmw_ret_t rmw_publish(
    const rmw_publisher_t * publisher,
    const void * ros_message,
    rmw_publisher_allocation_t * allocation)
{
    (void)allocation;

    fprintf(stderr, "[DEBUG][rmw_publish] called: publisher=%p, ros_message=%p\n",
            (void*)publisher, ros_message);
    fflush(stderr);

    if (!publisher) {
        RMW_SET_ERROR_MSG("publisher is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!ros_message) {
        RMW_SET_ERROR_MSG("ros_message is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (publisher->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    auto pub_impl = static_cast<rmw_dsoftbus::PublisherImpl*>(publisher->data);
    if (!pub_impl) {
        RMW_SET_ERROR_MSG("publisher impl is null");
        return RMW_RET_ERROR;
    }

    fprintf(stderr, "[DEBUG][rmw_publish] pub_impl=%p, topic=%s, message_size=%zu\n",
            (void*)pub_impl, pub_impl->topic_name.c_str(), pub_impl->message_size);
    fprintf(stderr, "[DEBUG][rmw_publish] get_serialized_size=%p, serialize=%p\n",
            (void*)pub_impl->get_serialized_size, (void*)pub_impl->serialize);
    fflush(stderr);

    // Serialize the message with CDR encapsulation
    std::vector<uint8_t> buffer;
    fprintf(stderr, "[DEBUG][rmw_publish] about to serialize...\n");
    fflush(stderr);

    if (!serialize_message_cdr(
            ros_message,
            pub_impl->message_size,
            pub_impl->get_serialized_size,
            pub_impl->serialize,
            buffer)) {
        RMW_SET_ERROR_MSG("failed to serialize message to CDR format");
        return RMW_RET_ERROR;
    }

    fprintf(stderr, "[DEBUG][rmw_publish] serialized %zu bytes\n", buffer.size());
    fflush(stderr);

    int sent = 0;
    uint64_t seq = pub_impl->sequence_number++;

    // === Backend Selection for Sending ===
    if (rmw_dsoftbus::get_active_backend() == rmw_dsoftbus::BackendType::SOCKET_DIRECT) {
        // Send via socket_direct backend
        sent = socket_direct_send(
            pub_impl->topic_name.c_str(),
            buffer.data(),
            static_cast<int>(buffer.size()));

        fprintf(stderr, "[DEBUG][rmw_publish] socket_direct sent to %d peer(s), seq=%lu\n", sent, seq);
    } else {
        // Publish via dsoftbus topic layer (default)
        sent = rmw_dsoftbus::publish_to_topic(
            pub_impl->topic_name.c_str(),
            buffer.data(),
            static_cast<unsigned int>(buffer.size()),
            seq,
            pub_impl->gid.data);

        fprintf(stderr, "[DEBUG][rmw_publish] dsoftbus sent to %d peer(s)\n", sent);
    }
    fflush(stderr);

    // sent is number of peers message was sent to
    // 0 means no subscribers found (not an error in ROS2 semantics)
    (void)sent;

    return RMW_RET_OK;
}

rmw_ret_t rmw_publish_serialized_message(
    const rmw_publisher_t * publisher,
    const rmw_serialized_message_t * serialized_message,
    rmw_publisher_allocation_t * allocation)
{
    (void)allocation;

    if (!publisher) {
        RMW_SET_ERROR_MSG("publisher is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!serialized_message) {
        RMW_SET_ERROR_MSG("serialized_message is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (publisher->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    auto pub_impl = static_cast<rmw_dsoftbus::PublisherImpl*>(publisher->data);
    if (!pub_impl) {
        RMW_SET_ERROR_MSG("publisher impl is null");
        return RMW_RET_ERROR;
    }

    int sent = 0;
    uint64_t seq = pub_impl->sequence_number++;

    // === Backend Selection for Sending ===
    if (rmw_dsoftbus::get_active_backend() == rmw_dsoftbus::BackendType::SOCKET_DIRECT) {
        // Send via socket_direct backend
        sent = socket_direct_send(
            pub_impl->topic_name.c_str(),
            serialized_message->buffer,
            static_cast<int>(serialized_message->buffer_length));

        fprintf(stderr, "[DEBUG][rmw_publish_serialized] socket_direct sent to %d peer(s), topic=%s, len=%zu, seq=%lu\n",
                sent, pub_impl->topic_name.c_str(), serialized_message->buffer_length, seq);
        fflush(stderr);
    } else {
        // Publish via dsoftbus - this handles discovery and session management
        sent = rmw_dsoftbus::publish_to_topic(
            pub_impl->topic_name.c_str(),
            serialized_message->buffer,
            serialized_message->buffer_length,
            seq,
            pub_impl->gid.data);
    }

    // sent is number of peers message was sent to
    // 0 means no subscribers found (not an error in ROS2 semantics)
    (void)sent;

    return RMW_RET_OK;
}

rmw_ret_t rmw_publisher_count_matched_subscriptions(
    const rmw_publisher_t * publisher,
    size_t * subscription_count)
{
    if (!publisher) {
        RMW_SET_ERROR_MSG("publisher is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!subscription_count) {
        RMW_SET_ERROR_MSG("subscription_count is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (publisher->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    // TODO: Implement discovery-based subscription counting
    *subscription_count = 0;

    return RMW_RET_OK;
}

rmw_ret_t rmw_publisher_get_actual_qos(
    const rmw_publisher_t * publisher,
    rmw_qos_profile_t * qos)
{
    if (!publisher) {
        RMW_SET_ERROR_MSG("publisher is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!qos) {
        RMW_SET_ERROR_MSG("qos is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (publisher->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    auto pub_impl = static_cast<rmw_dsoftbus::PublisherImpl*>(publisher->data);
    if (!pub_impl) {
        RMW_SET_ERROR_MSG("publisher impl is null");
        return RMW_RET_ERROR;
    }

    qos->history = RMW_QOS_POLICY_HISTORY_KEEP_LAST;
    qos->depth = pub_impl->history_depth;
    qos->reliability = pub_impl->reliable ?
        RMW_QOS_POLICY_RELIABILITY_RELIABLE :
        RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT;
    qos->durability = RMW_QOS_POLICY_DURABILITY_VOLATILE;
    qos->deadline = RMW_QOS_DEADLINE_DEFAULT;
    qos->lifespan = RMW_QOS_LIFESPAN_DEFAULT;
    qos->liveliness = RMW_QOS_POLICY_LIVELINESS_AUTOMATIC;
    qos->liveliness_lease_duration = RMW_QOS_LIVELINESS_LEASE_DURATION_DEFAULT;

    return RMW_RET_OK;
}

rmw_ret_t rmw_borrow_loaned_message(
    const rmw_publisher_t * publisher,
    const rosidl_message_type_support_t * type_support,
    void ** ros_message)
{
    (void)publisher;
    (void)type_support;
    (void)ros_message;
    RMW_SET_ERROR_MSG("rmw_borrow_loaned_message not supported");
    return RMW_RET_UNSUPPORTED;
}

rmw_ret_t rmw_return_loaned_message_from_publisher(
    const rmw_publisher_t * publisher,
    void * loaned_message)
{
    (void)publisher;
    (void)loaned_message;
    RMW_SET_ERROR_MSG("rmw_return_loaned_message_from_publisher not supported");
    return RMW_RET_UNSUPPORTED;
}

}  // extern "C"
