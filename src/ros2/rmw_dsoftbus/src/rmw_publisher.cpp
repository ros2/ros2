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
#include "rmw_dsoftbus/typesupport_serializer.h"  // Generic introspection serializer
#include "rmw_dsoftbus/publisher_discovery_handler.h"  // 1:N auto-routing
#include <rosidl_typesupport_introspection_c/message_introspection.h>
#include <rosidl_runtime_c/string.h>  // For rosidl_runtime_c__String type

#include <cstring>
#include <ctime>
#include <memory>
#include <vector>
#include <unistd.h>

// rosidl_runtime_c__String is already defined in rosidl_runtime_c/string.h

// std_msgs/msg/String structure
struct std_msgs__msg__String {
    rosidl_runtime_c__String data;
};

// Helper: serialize std_msgs/String using CDR
[[maybe_unused]]
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

    // ⚠️ SERIALIZATION CAPABILITY CHECK ⚠️
    // Reject C++ introspection typesupport for non-system topics
    //
    // This RMW only supports C introspection for real serialization.
    // C++ typesupport is allowed ONLY for system topics (/rosout, /parameter_events).
    //
    // 《商君书》："法不明，则民无所措手足。"- Be explicit about constraints.
    const char* cpp_introspection_id = "rosidl_typesupport_introspection_cpp";
    bool is_cpp = type_support->typesupport_identifier &&
                  strcmp(type_support->typesupport_identifier, cpp_introspection_id) == 0;
    bool is_system_topic = (strcmp(topic_name, "/rosout") == 0 ||
                           strcmp(topic_name, "/parameter_events") == 0);

    if (is_cpp && !is_system_topic) {
        fprintf(stderr, "[ERROR] Topic '%s' uses C++ introspection typesupport, "
                "which is NOT supported by rmw_dsoftbus.\n", topic_name);
        fprintf(stderr, "[ERROR] Please use C introspection typesupport (rosidl_typesupport_introspection_c).\n");
        fprintf(stderr, "[ERROR] User-defined topics cannot use C++ typesupport in this RMW implementation.\n");
        RMW_SET_ERROR_MSG("C++ introspection typesupport not supported for user topics");
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

    // Extract type name from type_support
    // For introspection typesupport, we can get the actual message type name
    bool is_introspection_ts = type_support->typesupport_identifier &&
        (strstr(type_support->typesupport_identifier, "introspection") != nullptr);

    if (is_introspection_ts && type_support->data) {
        auto members = static_cast<const rosidl_typesupport_introspection_c__MessageMembers*>(
            type_support->data);
        if (members->message_namespace_ && members->message_name_) {
            // Build fully qualified type name: "namespace/msg/MessageName"
            pub_impl->type_name = std::string(members->message_namespace_) + "/" +
                                  std::string(members->message_name_);
        } else {
            pub_impl->type_name = type_support->typesupport_identifier;
        }
    } else {
        pub_impl->type_name = type_support->typesupport_identifier;
    }

    // Map ROS2 QoS profile to dsoftbus QoS config (extensible)
    pub_impl->qos_config = rmw_dsoftbus::map_qos_profile(qos_policies);

    // Legacy fields (for backward compatibility)
    pub_impl->history_depth = pub_impl->qos_config.history_depth;
    pub_impl->reliable = (pub_impl->qos_config.reliability == rmw_dsoftbus::DSOFTBUS_RELIABILITY_FULL);

    // Encode topic name for session
    pub_impl->encoded_topic = topic_name;

    // Handle type support - check if introspection or regular
    fprintf(stderr, "[DEBUG][rmw_create_publisher] type_support=%p, data=%p, typesupport_id=%s\n",
            (void*)type_support, (void*)type_support->data,
            type_support->typesupport_identifier ? type_support->typesupport_identifier : "NULL");
    fflush(stderr);

    // For introspection typesupport, we need to use introspection-based serialization
    // The data pointer is rosidl_typesupport_introspection_c__MessageMembers, not callbacks
    bool is_introspection = type_support->typesupport_identifier &&
        (strstr(type_support->typesupport_identifier, "introspection") != nullptr);

    if (is_introspection) {
        fprintf(stderr, "[DEBUG][rmw_create_publisher] Using introspection typesupport\n");
        // Store type_support for generic introspection-based serialization
        pub_impl->type_support = type_support;
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
    static uint64_t gid_counter = 0;
    uint64_t timestamp = static_cast<uint64_t>(time(nullptr));
    uint64_t pid = static_cast<uint64_t>(getpid());
    memcpy(pub_impl->gid.data, &pid, sizeof(pid));
    memcpy(pub_impl->gid.data + 8, &timestamp, sizeof(timestamp));
    memcpy(pub_impl->gid.data + 16, &gid_counter, sizeof(gid_counter));
    gid_counter++;

    // Phase 2.2: Register publisher with GraphCache for discovery
    // Convert internal GID to rmw_gid_t
    rmw_gid_t rmw_gid;
    rmw_gid.implementation_identifier = rmw_get_implementation_identifier();
    memcpy(rmw_gid.data, pub_impl->gid.data, sizeof(rmw_gid.data));

    rmw_dsoftbus::GraphCache::instance().register_publisher(
        topic_name,
        pub_impl->type_name.c_str(),
        node->name,
        node->namespace_,
        qos_policies,
        &rmw_gid,
        pub_impl);
    fprintf(stderr, "[DEBUG][rmw_create_publisher] Registered publisher with GraphCache: %s\n",
            topic_name);
    fflush(stderr);

    // Open session to peer if configured
    auto context = rmw_dsoftbus::get_context_impl();
    if (context && !context->peer_network_id.empty()) {
        int session_id = rmw_dsoftbus::SessionManager::instance().open_session(
            topic_name,
            context->peer_network_id);

        if (session_id >= 0) {
            pub_impl->session_ids.push_back(session_id);
            fprintf(stderr, "[INFO][rmw_create_publisher] Opened session %d for topic %s\n",
                    session_id, topic_name);
        } else {
            fprintf(stderr, "[WARN][rmw_create_publisher] Failed to open session for topic %s\n",
                    topic_name);
        }
    } else {
        fprintf(stderr, "[INFO][rmw_create_publisher] No peer configured, enabling auto-discovery\n");

        // Register for 1:N auto-discovery
        rmw_dsoftbus::register_publisher_for_discovery(topic_name, pub_impl);
    }
    fflush(stderr);

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
    publisher->options.rmw_specific_publisher_payload = nullptr;  // QoS stored in impl
    publisher->options.require_unique_network_flow_endpoints = false;
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
        // Phase 2.2: Unregister publisher from GraphCache
        rmw_gid_t rmw_gid;
        rmw_gid.implementation_identifier = rmw_get_implementation_identifier();
        memcpy(rmw_gid.data, pub_impl->gid.data, sizeof(rmw_gid.data));
        rmw_dsoftbus::GraphCache::instance().unregister_endpoint(&rmw_gid);
        fprintf(stderr, "[DEBUG][rmw_destroy_publisher] Unregister Publisher from GraphCache: %s\n",
                pub_impl->topic_name.c_str());
        fflush(stderr);

        // Unregister from auto-discovery
        rmw_dsoftbus::unregister_publisher_from_discovery(pub_impl->topic_name, pub_impl);

        // Close all sessions
        for (int sid : pub_impl->session_ids) {
            if (sid >= 0) {
                rmw_dsoftbus::SessionManager::instance().close_session(sid);
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

    // Check if we have introspection-based type support
    if (pub_impl->type_support) {
        // Use generic introspection-based serializer
        uint8_t* cdr_buffer = nullptr;
        size_t cdr_size = 0;

        fprintf(stderr, "[DEBUG][rmw_publish] using generic introspection serializer\n");
        fflush(stderr);

        if (!rmw_dsoftbus_serialize_ros_message(
                ros_message,
                pub_impl->type_support,
                &cdr_buffer,
                &cdr_size)) {
            RMW_SET_ERROR_MSG("failed to serialize message using introspection");
            return RMW_RET_ERROR;
        }

        buffer.assign(cdr_buffer, cdr_buffer + cdr_size);
        free(cdr_buffer);

        fprintf(stderr, "[DEBUG][rmw_publish] serialized %zu bytes (introspection)\n", buffer.size());
        fflush(stderr);
    } else {
        // Fallback to old callback-based serialization
        fprintf(stderr, "[DEBUG][rmw_publish] using callback-based serializer\n");
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

        fprintf(stderr, "[DEBUG][rmw_publish] serialized %zu bytes (callbacks)\n", buffer.size());
        fflush(stderr);
    }

    uint64_t seq = pub_impl->sequence_number++;

    // Send via SessionManager to all open sessions
    int sent_count = 0;
    for (int session_id : pub_impl->session_ids) {
        if (session_id >= 0) {
            int ret = rmw_dsoftbus::SessionManager::instance().send_bytes(
                session_id,
                buffer.data(),
                static_cast<unsigned int>(buffer.size()));

            if (ret == 0) {
                sent_count++;
            } else {
                fprintf(stderr, "[WARN][rmw_publish] Failed to send on session %d: %d\n",
                        session_id, ret);
            }
        }
    }

    fprintf(stderr, "[DEBUG][rmw_publish] Sent to %d/%zu session(s), seq=%lu\n",
            sent_count, pub_impl->session_ids.size(), seq);
    fflush(stderr);

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

    uint64_t seq = pub_impl->sequence_number++;

    // Send via SessionManager to all open sessions
    int sent_count = 0;
    for (int session_id : pub_impl->session_ids) {
        if (session_id >= 0) {
            int ret = rmw_dsoftbus::SessionManager::instance().send_bytes(
                session_id,
                serialized_message->buffer,
                serialized_message->buffer_length);

            if (ret == 0) {
                sent_count++;
            }
        }
    }

    fprintf(stderr, "[DEBUG][rmw_publish_serialized] Sent to %d/%zu session(s), topic=%s, len=%zu, seq=%lu\n",
            sent_count, pub_impl->session_ids.size(), pub_impl->topic_name.c_str(),
            serialized_message->buffer_length, seq);
    fflush(stderr);

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

    auto pub_impl = static_cast<rmw_dsoftbus::PublisherImpl*>(publisher->data);
    if (!pub_impl) {
        RMW_SET_ERROR_MSG("publisher impl is null");
        return RMW_RET_ERROR;
    }

    // Phase 2.4: Use GraphCache to count matching subscriptions
    *subscription_count = rmw_dsoftbus::GraphCache::instance().count_subscribers(
        pub_impl->topic_name.c_str());

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
