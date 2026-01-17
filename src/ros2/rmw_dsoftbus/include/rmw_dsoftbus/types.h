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

/**
 * @addtogroup RMW_DSoftBus
 * @{
 *
 * @brief Provides ROS2 RMW implementation based on OpenHarmony dsoftbus.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file types.h
 *
 * @brief Declares core data types and structures for ROS2 RMW dsoftbus implementation.
 *
 * Defines essential types for:
 * - Global identifiers (GID) for publishers and subscriptions
 * - Session management
 * - Message handling
 * - QoS configuration
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef RMW_DSOFTBUS__TYPES_H_
#define RMW_DSOFTBUS__TYPES_H_

#include <cstdint>
#include <ctime>
#include <mutex>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>
#include <condition_variable>
#include <atomic>
#include <unistd.h>

#include "rmw_dsoftbus/qos_types.h"
#include "rmw/types.h"  // For rmw_gid_t

// Forward declaration for ROS IDL type support
struct rosidl_message_type_support_t;
struct rosidl_service_type_support_t;

// Package name for dsoftbus permission configuration (ROS2 RMW system service)
#define RMW_DSOFTBUS_PACKAGE_NAME "com.huawei.ros2_rmw_dsoftbus"  // Custom system package for ROS2 RMW
// Session name prefix for topic identification (must match SoftBus permission config)
#define RMW_DSOFTBUS_SESSION_PREFIX "com.huawei.ros2_rmw_dsoftbus."
#define RMW_DSOFTBUS_GID_SIZE 24

namespace rmw_dsoftbus
{

// Message size limit (4MB for SendBytes)
#define RMW_DSOFTBUS_MAX_MESSAGE_SIZE (4 * 1024 * 1024)

// GID (Global Identifier) for publishers/subscriptions
// Layout: [0-7] PID, [8-15] timestamp_ns, [16-23] counter + type_flag
struct GID {
    uint8_t data[RMW_DSOFTBUS_GID_SIZE];

    GID() { for(int i=0; i<RMW_DSOFTBUS_GID_SIZE; ++i) data[i]=0; }

    bool operator==(const GID& other) const {
        for(int i=0; i<RMW_DSOFTBUS_GID_SIZE; ++i) if(data[i]!=other.data[i]) return false;
        return true;
    }
};

/**
 * @brief Generate a deterministic GID with zero-initialization guarantee
 *
 * Layout (24 bytes, Little-Endian):
 *   [0-7]   : PID (padded to 8 bytes)
 *   [8-15]  : timestamp_ns (monotonic clock)
 *   [16-23] : counter (56 bits) | type_flag (8 bits)
 *
 * Type flags:
 *   0x01 = Publisher
 *   0x02 = Subscription
 *   0x03 = Service
 *   0x04 = Client
 *
 * @param type_flag Entity type identifier
 * @return Zero-initialized GID with unique content
 */
// Helper function to copy bytes (avoiding cstring dependency in header)
inline void gid_copy_bytes(uint8_t* dest, const void* src, size_t n) {
    const uint8_t* s = static_cast<const uint8_t*>(src);
    for (size_t i = 0; i < n; ++i) dest[i] = s[i];
}

inline GID generate_gid(uint8_t type_flag) {
    static std::atomic<uint64_t> gid_counter{0};

    GID gid;  // Zero-initialized by constructor

    // [0-7] PID
    int64_t pid = static_cast<int64_t>(getpid());
    gid_copy_bytes(gid.data, &pid, sizeof(pid));

    // [8-15] Timestamp
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    uint64_t timestamp = static_cast<uint64_t>(ts.tv_sec) * 1000000000ULL +
                         static_cast<uint64_t>(ts.tv_nsec);
    gid_copy_bytes(gid.data + 8, &timestamp, sizeof(timestamp));

    // [16-23] Counter (56 bits) | type_flag (8 bits)
    uint64_t counter = gid_counter.fetch_add(1);
    uint64_t counter_with_flag = (counter << 8) | type_flag;
    gid_copy_bytes(gid.data + 16, &counter_with_flag, sizeof(counter_with_flag));

    return gid;
}

// Type flags for generate_gid()
constexpr uint8_t GID_TYPE_PUBLISHER    = 0x01;
constexpr uint8_t GID_TYPE_SUBSCRIPTION = 0x02;
constexpr uint8_t GID_TYPE_SERVICE      = 0x03;
constexpr uint8_t GID_TYPE_CLIENT       = 0x04;

// Message queue item for received data
struct MessageItem {
    std::vector<uint8_t> data;
    uint64_t timestamp_ns;
    uint64_t sequence_number;
    GID publisher_gid;
    bool from_intra_process{false};
};

// Context implementation - manages dsoftbus lifecycle
struct ContextImpl {
    bool is_initialized{false};
    std::string instance_id;
    std::mutex mutex;

    // Peer network ID (for cross-device communication)
    std::string peer_network_id;
};

// Node implementation - represents a ROS2 node
struct NodeImpl {
    std::string name;
    std::string namespace_;
    std::string fqn;  // fully qualified name: namespace/name
    char session_name[256];
    ContextImpl* context{nullptr};

    // Guard condition for graph changes
    void* graph_guard_condition{nullptr};
};

// Serialization function types
typedef size_t (*GetSerializedSizeFn)(const void* ros_message);
typedef bool (*SerializeFn)(const void* ros_message, void* serialized_buffer, size_t buffer_size);
typedef bool (*DeserializeFn)(const void* serialized_data, size_t data_len, void* ros_message);

// Publisher implementation
struct PublisherImpl {
    NodeImpl* node{nullptr};
    std::string topic_name;
    std::string type_name;
    std::string encoded_topic;  // Encoded topic for dsoftbus session
    GID gid;                    // Publisher GID
    std::atomic<uint64_t> sequence_number{0};

    // dsoftbus sessions to all subscribers
    std::vector<int> session_ids;
    std::mutex session_mutex;

    // Phase 4: Track peer_network_id -> session_id mapping for deduplication
    // Prevents duplicate sessions when the same Subscriber is discovered multiple times
    std::unordered_map<std::string, int> peer_to_session;

    // QoS configuration (extensible)
    DsoftbusQosConfig qos_config;

    // Legacy QoS accessors (for backward compatibility)
    size_t history_depth{10};
    bool reliable{true};

    // Serialization support
    size_t message_size{0};     // Fixed message size (0 = use callbacks)
    GetSerializedSizeFn get_serialized_size{nullptr};
    SerializeFn serialize{nullptr};
    const rosidl_message_type_support_t* type_support{nullptr};  // For introspection-based serialization

    // Durability cache (for TRANSIENT_LOCAL)
    std::vector<MessageItem> durability_cache;
    std::mutex durability_mutex;

    // Statistics
    std::atomic<size_t> matched_count{0};
};

// Subscription implementation
struct SubscriptionImpl {
    NodeImpl* node{nullptr};
    std::string topic_name;
    std::string type_name;
    std::string encoded_topic;  // Encoded topic for dsoftbus session
    GID gid;                    // Subscription GID

    // Message queue with thread safety
    std::queue<MessageItem> message_queue;
    std::mutex queue_mutex;
    std::condition_variable queue_cv;
    size_t queue_depth{10};

    // Session server ID (for receiving messages)
    int session_server_id{-1};

    // Pipe for wait notification (write to [1] on message arrival, read from [0] in wait)
    int pipe_fd[2]{-1, -1};

    // QoS configuration (extensible)
    DsoftbusQosConfig qos_config;

    // Legacy QoS accessors (for backward compatibility)
    bool reliable{true};

    // Deserialization support
    size_t message_size{0};     // Fixed message size (0 = use callbacks)
    DeserializeFn deserialize{nullptr};
    const rosidl_message_type_support_t* type_support{nullptr};  // For introspection-based deserialization

    // Statistics
    std::atomic<size_t> matched_count{0};

    // Sequence number tracking for received messages
    std::atomic<uint64_t> received_sequence_number{0};

    ~SubscriptionImpl() {
        if (pipe_fd[0] >= 0) close(pipe_fd[0]);
        if (pipe_fd[1] >= 0) close(pipe_fd[1]);
    }
};

// Service request item
struct ServiceRequest {
    MessageItem message;
    int64_t request_id;
    int client_session_id;  // Session to send response back
    GID client_gid;
};

// Service implementation
struct ServiceImpl {
    NodeImpl* node{nullptr};
    std::string service_name;
    std::string type_name;
    std::string encoded_name;
    int session_server_id{-1};
    rmw_gid_t gid;  // GID for GraphCache registration (Phase 3)

    // Type support for serialization (stored during creation)
    const rosidl_service_type_support_t* service_type_support{nullptr};

    // Request queue
    std::queue<ServiceRequest> request_queue;
    std::mutex queue_mutex;

    // Pipe for wait notification
    int pipe_fd[2]{-1, -1};

    // Active client connections
    std::unordered_map<int, GID> client_sessions;  // session_id -> client_gid
    std::mutex session_mutex;

    ~ServiceImpl() {
        if (pipe_fd[0] >= 0) close(pipe_fd[0]);
        if (pipe_fd[1] >= 0) close(pipe_fd[1]);
    }
};

// Pending request for client
struct PendingRequest {
    int64_t request_id;
    uint64_t send_timestamp;
};

// Client implementation
struct ClientImpl {
    NodeImpl* node{nullptr};
    std::string service_name;
    std::string type_name;
    std::string encoded_name;
    GID gid;
    int session_id{-1};
    std::atomic<int64_t> sequence_number{0};

    // Type support for serialization (stored during creation)
    const rosidl_service_type_support_t* service_type_support{nullptr};

    // Pending requests
    std::unordered_map<int64_t, PendingRequest> pending_requests;
    std::mutex pending_mutex;

    // Response queue
    std::queue<MessageItem> response_queue;
    std::mutex queue_mutex;
    std::condition_variable response_cv;

    // Pipe for wait notification
    int pipe_fd[2]{-1, -1};

    ~ClientImpl() {
        if (pipe_fd[0] >= 0) close(pipe_fd[0]);
        if (pipe_fd[1] >= 0) close(pipe_fd[1]);
    }
};

// Guard Condition implementation
struct GuardConditionImpl {
    std::atomic<bool> triggered{false};
    std::mutex mutex;
    std::condition_variable cv;

    // Pipe for wait notification (using eventfd would be more efficient on Linux)
    int pipe_fd[2]{-1, -1};

    ~GuardConditionImpl() {
        if (pipe_fd[0] >= 0) close(pipe_fd[0]);
        if (pipe_fd[1] >= 0) close(pipe_fd[1]);
    }
};

// WaitSet implementation
struct WaitSetImpl {
    std::vector<void*> subscriptions;
    std::vector<void*> guard_conditions;
    std::vector<void*> services;
    std::vector<void*> clients;
    std::vector<void*> events;
    std::mutex mutex;
};

// Event implementation
struct EventImpl {
    void* parent{nullptr};  // publisher or subscription
    int event_type{0};
    bool triggered{false};
};

// === Context Access API (defined in rmw_init.cpp) ===
ContextImpl* get_context_impl();

}  // namespace rmw_dsoftbus

#endif  // RMW_DSOFTBUS__TYPES_H_
