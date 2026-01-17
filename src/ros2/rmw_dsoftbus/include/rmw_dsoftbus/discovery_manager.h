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
 * @file discovery_manager.h
 *
 * @brief Declares discovery manager for ROS2 RMW node discovery.
 *
 * Provides mechanisms for discovering ROS2 nodes and endpoints across
 * devices using dsoftbus session-based messaging.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef RMW_DSOFTBUS__DISCOVERY_MANAGER_H_
#define RMW_DSOFTBUS__DISCOVERY_MANAGER_H_

#include <atomic>
#include <cstdint>
#include <functional>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "rmw_dsoftbus/graph_cache.h"

namespace rmw_dsoftbus {

// ============================================================
// Protocol Constants (v3.1)
// ============================================================

static constexpr size_t DISCOVERY_HEADER_SIZE = 97;
static constexpr size_t MAX_DISCOVERY_PAYLOAD = 256 * 1024;  // 256KB
static constexpr uint64_t NODE_TIMEOUT_NS = 30ULL * 1000000000ULL;  // 30s
static constexpr uint64_t HEARTBEAT_INTERVAL_NS = 5ULL * 1000000000ULL;  // 5s
static constexpr uint16_t DISCOVERY_MAGIC = 0x524F;  // "RO"
static constexpr uint8_t DISCOVERY_VERSION = 1;

// DoS protection: hard limits on snapshot counts
// These are implementation limits, not protocol limits (uint16_t allows 65535)
static constexpr uint16_t MAX_NODES_PER_SNAPSHOT = 1024;
static constexpr uint16_t MAX_ENDPOINTS_PER_SNAPSHOT = 4096;

// Minimum entry sizes for feasibility check (prevents count inflation attacks)
// NodeEntry: ns_len(1) + name_len(1) + name(>=1) + enc_len(1) = 4 bytes min
// (name must be non-empty per ROS2 naming rules)
static constexpr size_t MIN_NODE_ENTRY_SIZE = 4;
// EndpointEntry: type(1) + topic_len(1) + topic(>=1) + type_len(1) + gid(24) + name_len(1) + ns_len(1) = 30 min
static constexpr size_t MIN_ENDPOINT_ENTRY_SIZE = 30;

// Discovery session name (MUST match permission pattern: com.huawei.dmsdp.*)
// Using dmsdp pattern which has complete APP_INFO configurations (system_app, self_app, native_app)
static constexpr const char* DISCOVERY_SESSION_NAME = "com.huawei.dmsdp.ros2_discovery";

// ============================================================
// Message Types
// ============================================================

enum class DiscoveryMessageType : uint8_t {
    QUERY           = 0x01,  // Request full snapshot
    SNAPSHOT        = 0x02,  // Full snapshot response (local-only)
    NODE_ADD        = 0x03,  // Incremental: node online
    NODE_REMOVE     = 0x04,  // Incremental: node offline
    ENDPOINT_ADD    = 0x05,  // Incremental: endpoint created
    ENDPOINT_REMOVE = 0x06,  // Incremental: endpoint destroyed
    HEARTBEAT       = 0x07,  // Heartbeat (refresh liveliness)
    HELLO           = 0x08,  // Session handshake request (Server → Client)
    HELLO_ACK       = 0x09   // Session handshake ACK (Client → Server)
};

// ============================================================
// Session State Machine (for reliable handshake)
// ============================================================

/**
 * @brief Session lifecycle states
 *
 * State transitions are MONOTONIC (never go backwards except to CLOSED).
 * Critical: State transitions must be idempotent with once-flags to prevent
 * duplicate side effects (e.g., sending HELLO twice).
 */
enum class SessionState : uint8_t {
    PENDING,  // OpenSession called, awaiting OnSessionOpened callback
    OPENED,   // OnSessionOpened(result=0), handshake in progress (control frames only)
    READY,    // Handshake complete, full communication allowed (data + heartbeat)
    CLOSED    // OnSessionClosed or handshake failed
};

/**
 * @brief Session context for state tracking and queued messages
 */
struct SessionContext {
    SessionState state{SessionState::PENDING};
    std::string peer_network_id;
    bool is_dialer{false};  // true if we called OpenSession (role determination)

    // Queued messages (for PENDING/OPENED states)
    std::vector<std::vector<uint8_t>> control_queue;  // HELLO/HELLO_ACK (flush on OPENED)
    std::vector<std::vector<uint8_t>> data_queue;     // QUERY/business/heartbeat (flush on READY)

    // Handshake completion flags (idempotent, set only once)
    std::atomic<bool> hello_sent{false};
    std::atomic<bool> hello_ack_sent{false};

    // Delete copy (atomic is not copyable)
    SessionContext() = default;
    SessionContext(const SessionContext&) = delete;
    SessionContext& operator=(const SessionContext&) = delete;
    // Allow move
    SessionContext(SessionContext&&) = default;
    SessionContext& operator=(SessionContext&&) = default;
};

// ============================================================
// Discovery Header (97 bytes, Little-Endian)
// ============================================================

struct DiscoveryHeader {
    uint16_t magic;              // 0x524F "RO"
    uint8_t  version;            // 1
    uint8_t  msg_type;           // DiscoveryMessageType
    uint32_t payload_len;        // Payload length in bytes
    uint64_t seq;                // Monotonic sequence number (per origin)
    uint64_t ts_ns;              // Send timestamp (nanoseconds)
    uint64_t origin_instance_id; // Random at startup, constant for process lifetime
    uint8_t  origin_len;         // Length of origin_network_id [1,64]
    char     origin_network_id[64];  // Sender's network ID (NOT null-terminated!)
};

/**
 * @brief Safe comparison for origin_network_id (MUST use this, never strcmp!)
 *
 * origin_network_id is length-prefixed, NOT null-terminated.
 * Using strcmp() would cause undefined behavior (buffer overread).
 */
inline bool origin_equals(const DiscoveryHeader& h, const std::string& id) {
    if (h.origin_len != id.size()) return false;
    return memcmp(h.origin_network_id, id.data(), h.origin_len) == 0;
}

/**
 * @brief Extract origin as std::string (safe, uses origin_len)
 */
inline std::string origin_to_string(const DiscoveryHeader& h) {
    return std::string(h.origin_network_id, h.origin_len);
}

// ============================================================
// Deduplication Key
// ============================================================

struct OriginKey {
    std::string network_id;
    uint64_t instance_id;

    bool operator==(const OriginKey& other) const {
        return network_id == other.network_id && instance_id == other.instance_id;
    }
};

struct OriginKeyHash {
    size_t operator()(const OriginKey& key) const {
        return std::hash<std::string>()(key.network_id) ^
               std::hash<uint64_t>()(key.instance_id);
    }
};

// ============================================================
// Discovery Statistics (Observability Counters)
// ============================================================

/**
 * @brief Non-atomic snapshot of discovery statistics
 *
 * Used as return type for get_stats() to allow copying.
 */
struct DiscoveryStatsSnapshot {
    // Message counters
    uint64_t rx_total{0};           // Total messages received
    uint64_t tx_total{0};           // Total messages sent

    // Drop counters (by reason)
    uint64_t drop_invalid{0};       // Invalid header/magic/version
    uint64_t drop_forwarded{0};     // Forwarded messages (origin != sender)
    uint64_t drop_dup{0};           // Duplicate seq dropped
    uint64_t drop_oversize{0};      // Payload exceeds limit
    uint64_t drop_count_limit{0};   // Node/endpoint count exceeds limit
    uint64_t drop_parse_error{0};   // Payload parse failure

    // Protocol events
    uint64_t query_sent{0};         // QUERY messages sent
    uint64_t snapshot_recv{0};      // SNAPSHOT messages received
    uint64_t heartbeat_recv{0};     // HEARTBEAT messages received
    uint64_t node_add_recv{0};      // NODE_ADD messages received
    uint64_t node_remove_recv{0};   // NODE_REMOVE messages received
    uint64_t endpoint_add_recv{0};  // ENDPOINT_ADD messages received
    uint64_t endpoint_remove_recv{0}; // ENDPOINT_REMOVE messages received

    // Resync events
    uint64_t resync_triggered{0};   // Full resync due to instance_id change

    // Graph state (point-in-time, not cumulative)
    uint32_t remote_nodes_count{0};     // Current remote node count
    uint32_t remote_endpoints_count{0}; // Current remote endpoint count
    uint32_t peer_sessions_count{0};    // Current peer session count
};

/**
 * @brief Discovery protocol statistics for observability
 *
 * All counters are atomic for thread-safe access without locking.
 * Use DiscoveryManager::get_stats() to retrieve current values as snapshot.
 */
struct DiscoveryStats {
    // Message counters
    std::atomic<uint64_t> rx_total{0};           // Total messages received
    std::atomic<uint64_t> tx_total{0};           // Total messages sent

    // Drop counters (by reason)
    std::atomic<uint64_t> drop_invalid{0};       // Invalid header/magic/version
    std::atomic<uint64_t> drop_forwarded{0};     // Forwarded messages (origin != sender)
    std::atomic<uint64_t> drop_dup{0};           // Duplicate seq dropped
    std::atomic<uint64_t> drop_oversize{0};      // Payload exceeds limit
    std::atomic<uint64_t> drop_count_limit{0};   // Node/endpoint count exceeds limit
    std::atomic<uint64_t> drop_parse_error{0};   // Payload parse failure

    // Protocol events
    std::atomic<uint64_t> query_sent{0};         // QUERY messages sent
    std::atomic<uint64_t> snapshot_recv{0};      // SNAPSHOT messages received
    std::atomic<uint64_t> heartbeat_recv{0};     // HEARTBEAT messages received
    std::atomic<uint64_t> node_add_recv{0};      // NODE_ADD messages received
    std::atomic<uint64_t> node_remove_recv{0};   // NODE_REMOVE messages received
    std::atomic<uint64_t> endpoint_add_recv{0};  // ENDPOINT_ADD messages received
    std::atomic<uint64_t> endpoint_remove_recv{0}; // ENDPOINT_REMOVE messages received

    // Resync events
    std::atomic<uint64_t> resync_triggered{0};   // Full resync due to instance_id change

    // Graph state (point-in-time, not cumulative)
    std::atomic<uint32_t> remote_nodes_count{0};     // Current remote node count
    std::atomic<uint32_t> remote_endpoints_count{0}; // Current remote endpoint count
    std::atomic<uint32_t> peer_sessions_count{0};    // Current peer session count

    // Get non-atomic snapshot of all counters
    DiscoveryStatsSnapshot snapshot() const {
        DiscoveryStatsSnapshot s;
        s.rx_total = rx_total.load();
        s.tx_total = tx_total.load();
        s.drop_invalid = drop_invalid.load();
        s.drop_forwarded = drop_forwarded.load();
        s.drop_dup = drop_dup.load();
        s.drop_oversize = drop_oversize.load();
        s.drop_count_limit = drop_count_limit.load();
        s.drop_parse_error = drop_parse_error.load();
        s.query_sent = query_sent.load();
        s.snapshot_recv = snapshot_recv.load();
        s.heartbeat_recv = heartbeat_recv.load();
        s.node_add_recv = node_add_recv.load();
        s.node_remove_recv = node_remove_recv.load();
        s.endpoint_add_recv = endpoint_add_recv.load();
        s.endpoint_remove_recv = endpoint_remove_recv.load();
        s.resync_triggered = resync_triggered.load();
        s.remote_nodes_count = remote_nodes_count.load();
        s.remote_endpoints_count = remote_endpoints_count.load();
        s.peer_sessions_count = peer_sessions_count.load();
        return s;
    }
};

// ============================================================
// DiscoveryManager
// ============================================================

class DiscoveryManager
{
public:
    /**
     * @brief Get singleton instance
     */
    static DiscoveryManager& instance();

    /**
     * @brief Initialize discovery subsystem
     * - Create discovery session server
     * - Start heartbeat thread
     * - Connect to known peers
     * @return true on success
     */
    bool initialize();

    /**
     * @brief Shutdown discovery subsystem
     */
    void shutdown();

    /**
     * @brief Check if initialized
     */
    bool is_initialized() const { return initialized_.load(); }

    /**
     * @brief Get current discovery statistics (thread-safe snapshot)
     * @return Copy of current statistics
     */
    DiscoveryStatsSnapshot get_stats() const { return stats_.snapshot(); }

    /**
     * @brief Get reference to stats for direct counter access
     * @return Reference to internal stats (for incrementing counters)
     */
    DiscoveryStats& stats() { return stats_; }

    // ========================================
    // Testing Helper Functions
    // ========================================

    /**
     * @brief Build heartbeat message for testing (exposes private method)
     */
    std::vector<uint8_t> build_heartbeat_message_for_test();

    /**
     * @brief Get first available peer session ID (for testing)
     * @return Session ID, or -1 if no peers
     */
    int get_first_peer_session_id() const;

    // ========================================
    // Broadcast APIs (called by GraphCache)
    // ========================================

    /**
     * @brief Broadcast node added event
     */
    void broadcast_node_added(const GraphNodeInfo& node);

    /**
     * @brief Broadcast node removed event
     */
    void broadcast_node_removed(const std::string& node_key);

    /**
     * @brief Broadcast endpoint added event
     */
    void broadcast_endpoint_added(const GraphEndpointInfo& endpoint);

    /**
     * @brief Broadcast endpoint removed event
     */
    void broadcast_endpoint_removed(const rmw_gid_t& gid);

    // ========================================
    // Session Callbacks (called by SessionManager)
    // ========================================

    /**
     * @brief Handle discovery session opened
     */
    void on_discovery_session_opened(int sessionId, const std::string& peer_network_id);

    /**
     * @brief Handle discovery session closed
     */
    void on_discovery_session_closed(int sessionId);

    /**
     * @brief Handle discovery session open failure (cleanup only)
     *
     * OpenSession() returning a positive sessionId does not mean the session is usable.
     * When the OnSessionOpened callback reports a non-zero result, we must clear any
     * "opening" bookkeeping so reconnection attempts are not blocked.
     */
    void on_discovery_session_open_failed(int sessionId, int result);

    /**
     * @brief Mark session as pending (awaiting peer network_id)
     */
    void on_discovery_session_pending(int sessionId);

    /**
     * @brief Handle session opened callback (state machine update)
     * @param sessionId Session ID from callback
     * @param peer_network_id Peer's network ID
     */
    void on_session_opened_statemachine(int sessionId, const std::string& peer_network_id);

    /**
     * @brief Handle discovery bytes received
     */
    void on_discovery_bytes_received(int sessionId, const void* data, unsigned int len);

    /**
     * @brief Handle peer device online (from dsoftbus)
     */
    void on_peer_online(const char* networkId);

    /**
     * @brief Handle peer device offline (from dsoftbus)
     */
    void on_peer_offline(const char* networkId);

private:
    DiscoveryManager();
    ~DiscoveryManager();

    // Disable copy
    DiscoveryManager(const DiscoveryManager&) = delete;
    DiscoveryManager& operator=(const DiscoveryManager&) = delete;

    // ========================================
    // Internal: Message Building
    // ========================================

    std::vector<uint8_t> build_header(DiscoveryMessageType type, uint32_t payload_len);
    std::vector<uint8_t> build_query_message();
    std::vector<uint8_t> build_snapshot_message();
    std::vector<uint8_t> build_heartbeat_message();
    std::vector<uint8_t> build_hello_message();      // Session handshake (Server → Client)
    std::vector<uint8_t> build_hello_ack_message();  // Session handshake ACK (Client → Server)
    std::vector<uint8_t> build_node_add_message(const GraphNodeInfo& node);
    std::vector<uint8_t> build_node_remove_message(const std::string& node_key);
    std::vector<uint8_t> build_endpoint_add_message(const GraphEndpointInfo& endpoint);
    std::vector<uint8_t> build_endpoint_remove_message(const rmw_gid_t& gid);

    // ========================================
    // Internal: Message Parsing
    // ========================================

    bool parse_and_validate(const void* data, size_t len,
                           DiscoveryHeader* header,
                           const uint8_t** payload_out);
    bool parse_snapshot_payload(const uint8_t* payload, size_t len, GraphSnapshot* snap);
    bool parse_node_entry(const uint8_t* data, size_t len, GraphNodeInfo* node, size_t* consumed);
    bool parse_endpoint_entry(const uint8_t* data, size_t len, GraphEndpointInfo* endpoint, size_t* consumed);
    bool parse_heartbeat_payload(const uint8_t* payload, size_t len,
                                 std::vector<std::string>* node_keys);

    // ========================================
    // Internal: Protocol Logic
    // ========================================

    bool check_origin_valid(const DiscoveryHeader& header, const std::string& sender_id);
    bool check_seq_dedup(const DiscoveryHeader& header);
    void process_message(const DiscoveryHeader& header, const uint8_t* payload,
                        const std::string& sender_id);

    void handle_query(const std::string& sender_id, int sessionId);
    void handle_snapshot(const std::string& origin_id, const uint8_t* payload, size_t len);
    void handle_node_add(const std::string& origin_id, const uint8_t* payload, size_t len);
    void handle_node_remove(const std::string& origin_id, const uint8_t* payload, size_t len);
    void handle_endpoint_add(const std::string& origin_id, const uint8_t* payload, size_t len);
    void handle_endpoint_remove(const std::string& origin_id, const uint8_t* payload, size_t len);
    void handle_heartbeat(const std::string& origin_id, const uint8_t* payload, size_t len);
    void handle_hello(const DiscoveryHeader& header, const uint8_t* payload,
                     const std::string& sender_id, int sessionId);
    void handle_hello_ack(const DiscoveryHeader& header, const uint8_t* payload,
                         const std::string& sender_id, int sessionId);

    // ========================================
    // Internal: Networking
    // ========================================

    void connect_all_peers_once();
    void send_to_peer(int sessionId, const std::vector<uint8_t>& msg);
    void send_to_peer_internal(int sessionId, const std::vector<uint8_t>& msg);  // Bypass state check
    void broadcast_to_all_peers(const std::vector<uint8_t>& msg);
    void send_query(int sessionId);
    void send_hello(int sessionId);      // Send HELLO handshake (Server)
    void send_hello_ack(int sessionId);  // Send HELLO_ACK (Client)

    // ========================================
    // Internal: Heartbeat & Liveliness
    // ========================================

    void heartbeat_thread_func();
    void check_node_liveliness();

    // ========================================
    // Internal: Utilities
    // ========================================

    uint64_t get_timestamp_ns() const;
    uint64_t get_next_seq();
    std::string get_peer_network_id(int sessionId) const;

private:
    std::atomic<bool> initialized_{false};
    std::atomic<bool> running_{false};

    // Observability counters (mutable for const get_stats())
    mutable DiscoveryStats stats_;

    // Local identity
    std::string local_network_id_;
    uint64_t local_instance_id_{0};
    std::atomic<uint64_t> seq_counter_{0};

    // Discovery session server
    int discovery_server_id_{-1};
    std::string discovery_session_name_;  // Dynamic session name (PID-based)

    // Session state machine (NEW: replaces simple session tracking)
    std::unordered_map<int, SessionContext> sessions_;  // sessionId -> context
    mutable std::mutex sessions_mutex_;

    // Legacy session tracking (kept for backward compatibility during transition)
    std::unordered_map<std::string, int> peer_sessions_;  // network_id -> session_id
    std::unordered_map<int, std::string> session_to_peer_;  // Reverse lookup
    mutable std::mutex peer_mutex_;

    // Outgoing sessions in progress (OpenSession succeeded but OnSessionOpened not yet OK).
    // Used to avoid duplicate OpenSession attempts before the callback fires.
    std::unordered_map<std::string, int> opening_peer_sessions_;  // peer_network_id -> session_id
    std::unordered_map<int, std::string> opening_session_to_peer_;  // session_id -> peer_network_id

    // Deduplication: (network_id, instance_id) -> last_seq
    std::unordered_map<OriginKey, uint64_t, OriginKeyHash> last_seq_seen_;
    std::unordered_map<std::string, uint64_t> known_instance_ids_;  // network_id -> instance_id
    mutable std::mutex seq_mutex_;

    // Node liveliness: network_id -> (node_key -> last_seen_ns)
    std::unordered_map<std::string, std::unordered_map<std::string, uint64_t>> remote_node_liveness_;
    mutable std::mutex liveness_mutex_;

    // Untracked sessions: sessionIds awaiting peer_network_id resolution
    // These sessions failed GetPeerDeviceId() during OnSessionOpened callback
    // Will be registered when first message arrives (using header.origin_network_id)
    std::unordered_set<int> untracked_sessions_;
    mutable std::mutex untracked_mutex_;

    // Heartbeat thread
    std::thread heartbeat_thread_;
};

// ============================================================
// NodeKey Normalization (used globally)
// ============================================================

/**
 * @brief Normalize NodeKey generation (global unique rule)
 *
 * Rules:
 *   - namespace starts with '/'
 *   - root namespace is "/"
 *   - node name cannot contain '/'
 *   - output format: "{namespace}:{name}"
 *
 * Examples:
 *   make_node_key("/ns1", "talker")  -> "/ns1:talker"
 *   make_node_key("/", "listener")   -> "/:listener"
 *   make_node_key("", "node")        -> "/:node"  (empty -> root)
 */
inline std::string make_node_key(const char* ns, const char* name) {
    std::string normalized_ns;

    if (ns == nullptr || ns[0] == '\0') {
        normalized_ns = "/";
    } else if (ns[0] != '/') {
        normalized_ns = std::string("/") + ns;
    } else {
        normalized_ns = ns;
    }

    return normalized_ns + ":" + (name ? name : "");
}

inline std::string make_node_key(const std::string& ns, const std::string& name) {
    return make_node_key(ns.c_str(), name.c_str());
}

}  // namespace rmw_dsoftbus

#endif  // RMW_DSOFTBUS__DISCOVERY_MANAGER_H_
