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
 * @file graph_cache.h
 *
 * @brief Declares graph cache for ROS2 node and endpoint graph.
 *
 * @since 1.0
 * @version 1.0
 */
#ifndef RMW_DSOFTBUS__GRAPH_CACHE_H_
#define RMW_DSOFTBUS__GRAPH_CACHE_H_

#include <cstdint>
#include <map>
#include <mutex>
#include <optional>
#include <set>
#include <string>
#include <vector>

#include "rmw_dsoftbus/compat_clib.h"  // Cross-compilation C library compatibility
#include "rmw/types.h"

namespace rmw_dsoftbus {

// Endpoint type (publisher or subscription)
enum class EndpointType : uint8_t {
    PUBLISHER = 0,
    SUBSCRIPTION = 1,
    SERVICE = 2,
    CLIENT = 3
};

// Node information
struct GraphNodeInfo {
    std::string node_name;
    std::string node_namespace;
    // NOTE: enclave is a placeholder string in non-DDS environments (OpenHarmony/dsoftbus).
    // It does NOT provide DDS-level security isolation. Empty string is valid.
    std::string enclave;
    std::string network_id;  // Device network ID (local for Phase 2.2)
    uint64_t creation_time_ns{0};
};

// Endpoint information (Publisher/Subscription/Service/Client)
struct GraphEndpointInfo {
    std::string topic_name;      // Topic or service name
    std::string type_name;       // Message/service type name
    rmw_gid_t gid;               // Global unique identifier
    std::string node_name;
    std::string node_namespace;
    std::string network_id;
    rmw_qos_profile_t qos;
    EndpointType type;
    void* impl_ptr{nullptr};     // PublisherImpl* or SubscriptionImpl* for lookup
    int session_id{-1};          // Session ID for liveness check (Phase 3)
    uint64_t creation_time_ns{0};
};

// Service info for is_service_available check (Phase 3)
struct ServiceInfo {
    std::string service_name;
    int session_id;
    rmw_gid_t server_gid;
};

// Topic aggregated information
struct GraphTopicInfo {
    std::string topic_name;
    std::set<std::string> type_names;  // One topic may have multiple types
    std::vector<GraphEndpointInfo> publishers;
    std::vector<GraphEndpointInfo> subscriptions;
};

// GID comparator for use in std::map
struct GIDComparator {
    bool operator()(const rmw_gid_t& a, const rmw_gid_t& b) const {
        return memcmp(a.data, b.data, RMW_GID_STORAGE_SIZE) < 0;
    }
};

// Remote endpoint composite key (network_id + gid)
// Prevents GID collision across different devices
struct RemoteEndpointKey {
    std::string network_id;
    rmw_gid_t gid;

    bool operator<(const RemoteEndpointKey& other) const {
        int net_cmp = network_id.compare(other.network_id);
        if (net_cmp != 0) return net_cmp < 0;
        return memcmp(gid.data, other.gid.data, RMW_GID_STORAGE_SIZE) < 0;
    }
};

/**
 * @brief Immutable snapshot of the graph cache
 *
 * Used for Phase 2.3 discovery broadcast - allows serializing graph state
 * without holding locks during network I/O.
 */
struct GraphSnapshot {
    std::vector<GraphNodeInfo> nodes;
    std::vector<GraphEndpointInfo> endpoints;
    uint64_t timestamp_ns{0};
};

// ============================================================
// Phase 4: 1:N Auto-Routing Callback Types
// ============================================================

/**
 * @brief Callback type for subscriber discovery events
 *
 * Called when a new remote Subscriber is discovered on the network.
 * Publishers can use this to automatically establish sessions.
 *
 * @param topic_name Topic name the Subscriber is interested in
 * @param peer_network_id Remote device network ID
 * @param subscriber_gid Subscriber's global unique identifier
 */
typedef void (*SubscriberDiscoveryCallback)(
    const std::string& topic_name,
    const std::string& peer_network_id,
    const rmw_gid_t& subscriber_gid);

/**
 * @brief Callback type for subscriber removal events
 *
 * Called when a remote Subscriber goes offline or unregisters.
 *
 * @param topic_name Topic name
 * @param peer_network_id Remote device network ID (for cleanup of peer_to_session map)
 * @param subscriber_gid Subscriber's global unique identifier
 */
typedef void (*SubscriberRemovalCallback)(
    const std::string& topic_name,
    const std::string& peer_network_id,
    const rmw_gid_t& subscriber_gid);

/**
 * @brief Graph cache for local node and endpoint registration
 *
 * SCOPE SEMANTICS:
 * - Current scope: PROCESS-LOCAL (not node-local, not device-global)
 * - GraphCache represents a single process's view of the ROS graph
 * - All nodes/endpoints in this cache belong to the current process
 * - Remote graph data will be merged in Phase 2.3 via __discovery__ session
 *
 * Phase 2.2: Local registration only (in-process pub/sub visible to ros2 tools)
 * Phase 2.3: Cross-device discovery via dsoftbus broadcast
 * Phase 4: 1:N auto-routing via subscriber discovery callbacks
 *
 * Thread-safe: All public methods are protected by mutex
 */
class GraphCache {
public:
    /**
     * @brief Get singleton instance
     */
    static GraphCache& instance();

    /**
     * @brief Initialize the graph cache
     * @return true on success
     */
    bool initialize();

    /**
     * @brief Shutdown and clear the graph cache
     */
    void shutdown();

    // ========================================
    // Node Registration (Phase 2.2)
    // ========================================

    /**
     * @brief Register a local node
     * @param node_name Node name
     * @param node_namespace Node namespace
     * @param enclave Security enclave (optional)
     */
    void register_node(
        const char* node_name,
        const char* node_namespace,
        const char* enclave);

    /**
     * @brief Unregister a local node
     * @param node_name Node name
     * @param node_namespace Node namespace
     */
    void unregister_node(
        const char* node_name,
        const char* node_namespace);

    // ========================================
    // Endpoint Registration (Phase 2.2)
    // ========================================

    /**
     * @brief Register a publisher endpoint
     * @param topic_name Topic name
     * @param type_name Message type name
     * @param node_name Parent node name
     * @param node_namespace Parent node namespace
     * @param qos QoS profile
     * @param gid Publisher GID (pre-generated)
     * @param impl_ptr Pointer to PublisherImpl for reverse lookup
     */
    void register_publisher(
        const char* topic_name,
        const char* type_name,
        const char* node_name,
        const char* node_namespace,
        const rmw_qos_profile_t* qos,
        const rmw_gid_t* gid,
        void* impl_ptr);

    /**
     * @brief Register a subscription endpoint
     */
    void register_subscription(
        const char* topic_name,
        const char* type_name,
        const char* node_name,
        const char* node_namespace,
        const rmw_qos_profile_t* qos,
        const rmw_gid_t* gid,
        void* impl_ptr);

    /**
     * @brief Register a service endpoint
     * @param session_id Session ID for liveness check (Phase 3), -1 if unknown
     */
    void register_service(
        const char* service_name,
        const char* type_name,
        const char* node_name,
        const char* node_namespace,
        const rmw_qos_profile_t* qos,
        const rmw_gid_t* gid,
        void* impl_ptr,
        int session_id = -1);

    /**
     * @brief Register a client endpoint
     */
    void register_client(
        const char* service_name,
        const char* type_name,
        const char* node_name,
        const char* node_namespace,
        const rmw_qos_profile_t* qos,
        const rmw_gid_t* gid,
        void* impl_ptr);

    /**
     * @brief Unregister an endpoint by GID
     * @param gid Endpoint GID
     */
    void unregister_endpoint(const rmw_gid_t* gid);

    // ========================================
    // Query APIs (for rmw_get_info.cpp)
    // ========================================

    /**
     * @brief Get all registered nodes
     * @return Vector of node info
     */
    std::vector<GraphNodeInfo> get_all_nodes() const;

    /**
     * @brief Get all registered topics with their types
     * @return Map of topic name to set of type names
     */
    std::map<std::string, std::set<std::string>> get_topic_names_and_types() const;

    /**
     * @brief Get all registered services with their types
     * @return Map of service name to set of type names
     */
    std::map<std::string, std::set<std::string>> get_service_names_and_types() const;

    /**
     * @brief Count publishers for a topic
     * @param topic_name Topic name
     * @return Number of publishers
     */
    size_t count_publishers(const char* topic_name) const;

    /**
     * @brief Count subscribers for a topic
     * @param topic_name Topic name
     * @return Number of subscribers
     */
    size_t count_subscribers(const char* topic_name) const;

    /**
     * @brief Count services for a service name
     * @param service_name Service name
     * @return Number of services
     */
    size_t count_services(const char* service_name) const;

    /**
     * @brief Count clients for a service name
     * @param service_name Service name
     * @return Number of clients
     */
    size_t count_clients(const char* service_name) const;

    /**
     * @brief Get service info for is_service_available check (Phase 3)
     * @param service_name Service name
     * @return ServiceInfo if found, nullopt otherwise
     */
    std::optional<ServiceInfo> get_service_info(const char* service_name) const;

    /**
     * @brief Get publishers info for a topic
     * @param topic_name Topic name
     * @return Vector of endpoint info
     */
    std::vector<GraphEndpointInfo> get_publishers_for_topic(const char* topic_name) const;

    /**
     * @brief Get subscribers info for a topic
     * @param topic_name Topic name
     * @return Vector of endpoint info
     */
    std::vector<GraphEndpointInfo> get_subscribers_for_topic(const char* topic_name) const;

    /**
     * @brief Lookup endpoint by GID
     * @param gid Endpoint GID
     * @return Pointer to endpoint info, or nullptr if not found
     */
    const GraphEndpointInfo* lookup_endpoint_by_gid(const rmw_gid_t* gid) const;

    // ========================================
    // By-Node Query APIs (Phase 5)
    // ========================================

    /**
     * @brief Get publisher topics and types for a specific node
     * @param node_name Node name
     * @param node_namespace Node namespace
     * @return Map of topic name to set of type names
     */
    std::map<std::string, std::set<std::string>> get_publisher_names_and_types_by_node(
        const char* node_name,
        const char* node_namespace) const;

    /**
     * @brief Get subscriber topics and types for a specific node
     * @param node_name Node name
     * @param node_namespace Node namespace
     * @return Map of topic name to set of type names
     */
    std::map<std::string, std::set<std::string>> get_subscriber_names_and_types_by_node(
        const char* node_name,
        const char* node_namespace) const;

    /**
     * @brief Get service names and types for a specific node
     * @param node_name Node name
     * @param node_namespace Node namespace
     * @return Map of service name to set of type names
     */
    std::map<std::string, std::set<std::string>> get_service_names_and_types_by_node(
        const char* node_name,
        const char* node_namespace) const;

    /**
     * @brief Get client names and types for a specific node
     * @param node_name Node name
     * @param node_namespace Node namespace
     * @return Map of service name to set of type names
     */
    std::map<std::string, std::set<std::string>> get_client_names_and_types_by_node(
        const char* node_name,
        const char* node_namespace) const;

    // ========================================
    // Graph Guard Condition (for event notification)
    // ========================================

    /**
     * @brief Set the graph guard condition to trigger on graph changes
     * @param guard_condition Guard condition handle
     */
    void set_graph_guard_condition(void* guard_condition);

    /**
     * @brief Get current graph version (monotonic)
     * @return Current graph version number
     */
    uint64_t get_graph_version() const;

    // ========================================
    // Phase 2.3: Cross-device Discovery (Reserved)
    // ========================================

    /**
     * @brief Get immutable snapshot of current graph state (all nodes/endpoints)
     *
     * Used by Phase 2.3 discovery to serialize graph without holding locks.
     * @return Copy of current nodes and endpoints
     */
    GraphSnapshot snapshot() const;

    /**
     * @brief Get local-only snapshot (excludes remote nodes/endpoints)
     *
     * Used for Discovery SNAPSHOT response - only includes local entities.
     * @return Copy of local nodes and endpoints only
     */
    GraphSnapshot snapshot_local_only() const;

    /**
     * @brief Get all local nodes (for heartbeat)
     * @return Map of node_key -> node info for local nodes only
     */
    std::map<std::string, GraphNodeInfo> get_local_nodes() const;

    /**
     * @brief Receive remote node discovery (Phase 2.3)
     */
    void on_remote_node_discovered(const GraphNodeInfo& remote_node);

    /**
     * @brief Receive remote endpoint discovery (Phase 2.3)
     */
    void on_remote_endpoint_discovered(const GraphEndpointInfo& remote_endpoint);

    /**
     * @brief Batch merge remote snapshot (Phase 2.3 optimization)
     *
     * Merges all nodes and endpoints from a remote device in a single operation,
     * minimizing lock contention and guard condition triggers.
     *
     * @param network_id Remote device network ID
     * @param nodes Vector of remote nodes
     * @param endpoints Vector of remote endpoints
     */
    void merge_remote_snapshot(
        const std::string& network_id,
        const std::vector<GraphNodeInfo>& nodes,
        const std::vector<GraphEndpointInfo>& endpoints);

    /**
     * @brief Remove a remote node and its endpoints
     * @param network_id Device network ID
     * @param node_key Node key (from make_node_key)
     */
    void remove_remote_node(const std::string& network_id, const std::string& node_key);

    /**
     * @brief Remove a remote endpoint by composite key
     * @param network_id Device network ID
     * @param gid Endpoint GID
     */
    void remove_remote_endpoint(const std::string& network_id, const rmw_gid_t& gid);

    /**
     * @brief Remove all nodes and endpoints from a device
     * @param network_id Device network ID
     */
    void remove_all_from_network_id(const std::string& network_id);

    /**
     * @brief Broadcast local graph to network (Phase 2.3)
     */
    void broadcast_local_graph();

    // ========================================
    // Phase 4: 1:N Auto-Routing Callbacks
    // ========================================

    /**
     * @brief Set callbacks for Subscriber discovery events
     *
     * Used by Publisher discovery handler to receive notifications
     * when remote Subscribers are discovered or removed.
     *
     * @param on_discovered Callback for new Subscriber discovery (can be nullptr)
     * @param on_removed Callback for Subscriber removal (can be nullptr)
     */
    void set_subscriber_callbacks(
        SubscriberDiscoveryCallback on_discovered,
        SubscriberRemovalCallback on_removed);

    /**
     * @brief Get local network ID (for filtering local vs remote)
     * @return Local network ID string
     */
    std::string get_local_network_id_public() const;

private:
    GraphCache();
    ~GraphCache();

    // Disable copy
    GraphCache(const GraphCache&) = delete;
    GraphCache& operator=(const GraphCache&) = delete;

    // Internal helper: add endpoint to storage
    void add_endpoint_internal(const GraphEndpointInfo& endpoint);

    // Internal helper: trigger graph guard condition
    void trigger_graph_change();

    // Get local network ID (process-local for Phase 2.2)
    std::string get_local_network_id() const;

    // Get current timestamp in nanoseconds
    uint64_t get_timestamp_ns() const;

private:
    bool initialized_{false};

    // ========================================
    // Local Storage (this process only)
    // ========================================

    // Local node registry: key = "namespace:name"
    std::map<std::string, GraphNodeInfo> local_nodes_;

    // Local endpoint registry by GID
    std::map<rmw_gid_t, GraphEndpointInfo, GIDComparator> local_endpoints_;

    // ========================================
    // Remote Storage (from other devices)
    // ========================================

    // Remote nodes: network_id -> (node_key -> info)
    std::map<std::string, std::map<std::string, GraphNodeInfo>> remote_nodes_;

    // Remote endpoints: composite key (network_id + gid) -> info
    std::map<RemoteEndpointKey, GraphEndpointInfo> remote_endpoints_;

    // ========================================
    // Topic/Service Index (aggregated)
    // ========================================

    // Topic index: topic_name -> list of GIDs (local only, remote use composite key)
    std::map<std::string, std::vector<rmw_gid_t>> publishers_by_topic_;
    std::map<std::string, std::vector<rmw_gid_t>> subscriptions_by_topic_;

    // Service index: service_name -> list of GIDs
    std::map<std::string, std::vector<rmw_gid_t>> services_by_name_;
    std::map<std::string, std::vector<rmw_gid_t>> clients_by_name_;

    // ========================================
    // Other
    // ========================================

    // Graph guard condition for change notification
    void* graph_guard_condition_{nullptr};

    // Graph version (monotonic counter, incremented on every change)
    uint64_t graph_version_{0};

    // Thread safety
    mutable std::mutex mutex_;

    // ========================================
    // Phase 4: Subscriber Discovery Callbacks
    // ========================================
    SubscriberDiscoveryCallback subscriber_discovered_cb_{nullptr};
    SubscriberRemovalCallback subscriber_removed_cb_{nullptr};
    std::mutex callback_mutex_;  // Separate mutex for callbacks (avoid deadlock)
};

}  // namespace rmw_dsoftbus

#endif  // RMW_DSOFTBUS__GRAPH_CACHE_H_
