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

#include "rmw_dsoftbus/graph_cache.h"
#include "rmw_dsoftbus/discovery_manager.h"  // For make_node_key

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <unistd.h>

// Forward declaration of rmw_trigger_guard_condition (C linkage)
extern "C" {
    rmw_ret_t rmw_trigger_guard_condition(const rmw_guard_condition_t* guard_condition);
}

namespace rmw_dsoftbus {

// ============================================================
// Singleton Instance
// ============================================================

GraphCache& GraphCache::instance()
{
    static GraphCache instance;
    return instance;
}

GraphCache::GraphCache()
{
}

GraphCache::~GraphCache()
{
    shutdown();
}

// ============================================================
// Initialization / Shutdown
// ============================================================

bool GraphCache::initialize()
{
    std::lock_guard<std::mutex> lock(mutex_);

    if (initialized_) {
        return true;
    }

    fprintf(stderr, "[GraphCache] Initializing local graph cache\n");
    initialized_ = true;
    return true;
}

void GraphCache::shutdown()
{
    std::lock_guard<std::mutex> lock(mutex_);

    if (!initialized_) {
        return;
    }

    fprintf(stderr, "[GraphCache] Shutting down, clearing %zu local nodes, %zu local endpoints\n",
            local_nodes_.size(), local_endpoints_.size());

    local_nodes_.clear();
    local_endpoints_.clear();
    remote_nodes_.clear();
    remote_endpoints_.clear();
    publishers_by_topic_.clear();
    subscriptions_by_topic_.clear();
    services_by_name_.clear();
    clients_by_name_.clear();

    initialized_ = false;
}

// ============================================================
// Node Registration
// ============================================================

void GraphCache::register_node(
    const char* node_name,
    const char* node_namespace,
    const char* enclave)
{
    if (!node_name || !node_namespace) {
        return;
    }

    std::lock_guard<std::mutex> lock(mutex_);

    // Create node key using normalized function
    std::string key = std::string(node_namespace) + ":" + std::string(node_name);

    GraphNodeInfo node_info;
    node_info.node_name = node_name;
    node_info.node_namespace = node_namespace;
    node_info.enclave = enclave ? enclave : "";
    node_info.network_id = get_local_network_id();
    node_info.creation_time_ns = get_timestamp_ns();

    local_nodes_[key] = node_info;

    fprintf(stderr, "[GraphCache] Registered local node: %s (namespace: %s)\n",
            node_name, node_namespace);

    trigger_graph_change();
}

void GraphCache::unregister_node(
    const char* node_name,
    const char* node_namespace)
{
    if (!node_name || !node_namespace) {
        return;
    }

    std::lock_guard<std::mutex> lock(mutex_);

    std::string key = std::string(node_namespace) + ":" + std::string(node_name);

    auto it = local_nodes_.find(key);
    if (it != local_nodes_.end()) {
        local_nodes_.erase(it);
        fprintf(stderr, "[GraphCache] Unregistered local node: %s (namespace: %s)\n",
                node_name, node_namespace);
        trigger_graph_change();
    }
}

// ============================================================
// Endpoint Registration
// ============================================================

void GraphCache::add_endpoint_internal(const GraphEndpointInfo& endpoint)
{
    // Add to local GID index
    local_endpoints_[endpoint.gid] = endpoint;

    // Add to topic/service index
    switch (endpoint.type) {
        case EndpointType::PUBLISHER:
            publishers_by_topic_[endpoint.topic_name].push_back(endpoint.gid);
            break;
        case EndpointType::SUBSCRIPTION:
            subscriptions_by_topic_[endpoint.topic_name].push_back(endpoint.gid);
            break;
        case EndpointType::SERVICE:
            services_by_name_[endpoint.topic_name].push_back(endpoint.gid);
            break;
        case EndpointType::CLIENT:
            clients_by_name_[endpoint.topic_name].push_back(endpoint.gid);
            break;
    }
}

void GraphCache::register_publisher(
    const char* topic_name,
    const char* type_name,
    const char* node_name,
    const char* node_namespace,
    const rmw_qos_profile_t* qos,
    const rmw_gid_t* gid,
    void* impl_ptr)
{
    if (!topic_name || !type_name || !node_name || !gid) {
        return;
    }

    std::lock_guard<std::mutex> lock(mutex_);

    GraphEndpointInfo endpoint;
    endpoint.topic_name = topic_name;
    endpoint.type_name = type_name;
    endpoint.node_name = node_name;
    endpoint.node_namespace = node_namespace ? node_namespace : "/";
    endpoint.network_id = get_local_network_id();
    memcpy(&endpoint.gid, gid, sizeof(rmw_gid_t));
    if (qos) {
        endpoint.qos = *qos;
    }
    endpoint.type = EndpointType::PUBLISHER;
    endpoint.impl_ptr = impl_ptr;
    endpoint.creation_time_ns = get_timestamp_ns();

    add_endpoint_internal(endpoint);

    fprintf(stderr, "[GraphCache] Registered publisher: topic=%s, type=%s, node=%s\n",
            topic_name, type_name, node_name);

    trigger_graph_change();
}

void GraphCache::register_subscription(
    const char* topic_name,
    const char* type_name,
    const char* node_name,
    const char* node_namespace,
    const rmw_qos_profile_t* qos,
    const rmw_gid_t* gid,
    void* impl_ptr)
{
    if (!topic_name || !type_name || !node_name || !gid) {
        return;
    }

    std::lock_guard<std::mutex> lock(mutex_);

    GraphEndpointInfo endpoint;
    endpoint.topic_name = topic_name;
    endpoint.type_name = type_name;
    endpoint.node_name = node_name;
    endpoint.node_namespace = node_namespace ? node_namespace : "/";
    endpoint.network_id = get_local_network_id();
    memcpy(&endpoint.gid, gid, sizeof(rmw_gid_t));
    if (qos) {
        endpoint.qos = *qos;
    }
    endpoint.type = EndpointType::SUBSCRIPTION;
    endpoint.impl_ptr = impl_ptr;
    endpoint.creation_time_ns = get_timestamp_ns();

    add_endpoint_internal(endpoint);

    fprintf(stderr, "[GraphCache] Registered subscription: topic=%s, type=%s, node=%s\n",
            topic_name, type_name, node_name);

    trigger_graph_change();
}

void GraphCache::register_service(
    const char* service_name,
    const char* type_name,
    const char* node_name,
    const char* node_namespace,
    const rmw_qos_profile_t* qos,
    const rmw_gid_t* gid,
    void* impl_ptr,
    int session_id)
{
    if (!service_name || !type_name || !node_name || !gid) {
        return;
    }

    std::lock_guard<std::mutex> lock(mutex_);

    GraphEndpointInfo endpoint;
    endpoint.topic_name = service_name;
    endpoint.type_name = type_name;
    endpoint.node_name = node_name;
    endpoint.node_namespace = node_namespace ? node_namespace : "/";
    endpoint.network_id = get_local_network_id();
    memcpy(&endpoint.gid, gid, sizeof(rmw_gid_t));
    if (qos) {
        endpoint.qos = *qos;
    }
    endpoint.type = EndpointType::SERVICE;
    endpoint.impl_ptr = impl_ptr;
    endpoint.session_id = session_id;  // Phase 3: Store session_id for liveness check
    endpoint.creation_time_ns = get_timestamp_ns();

    add_endpoint_internal(endpoint);

    fprintf(stderr, "[GraphCache] Registered service: name=%s, type=%s, node=%s, session_id=%d\n",
            service_name, type_name, node_name, session_id);

    trigger_graph_change();
}

void GraphCache::register_client(
    const char* service_name,
    const char* type_name,
    const char* node_name,
    const char* node_namespace,
    const rmw_qos_profile_t* qos,
    const rmw_gid_t* gid,
    void* impl_ptr)
{
    if (!service_name || !type_name || !node_name || !gid) {
        return;
    }

    std::lock_guard<std::mutex> lock(mutex_);

    GraphEndpointInfo endpoint;
    endpoint.topic_name = service_name;
    endpoint.type_name = type_name;
    endpoint.node_name = node_name;
    endpoint.node_namespace = node_namespace ? node_namespace : "/";
    endpoint.network_id = get_local_network_id();
    memcpy(&endpoint.gid, gid, sizeof(rmw_gid_t));
    if (qos) {
        endpoint.qos = *qos;
    }
    endpoint.type = EndpointType::CLIENT;
    endpoint.impl_ptr = impl_ptr;
    endpoint.creation_time_ns = get_timestamp_ns();

    add_endpoint_internal(endpoint);

    fprintf(stderr, "[GraphCache] Registered client: service=%s, type=%s, node=%s\n",
            service_name, type_name, node_name);

    trigger_graph_change();
}

void GraphCache::unregister_endpoint(const rmw_gid_t* gid)
{
    if (!gid) {
        return;
    }

    std::lock_guard<std::mutex> lock(mutex_);

    auto it = local_endpoints_.find(*gid);
    if (it == local_endpoints_.end()) {
        return;
    }

    const GraphEndpointInfo& endpoint = it->second;
    const std::string& name = endpoint.topic_name;

    // Remove from topic/service index
    std::map<std::string, std::vector<rmw_gid_t>>* index = nullptr;
    switch (endpoint.type) {
        case EndpointType::PUBLISHER:
            index = &publishers_by_topic_;
            break;
        case EndpointType::SUBSCRIPTION:
            index = &subscriptions_by_topic_;
            break;
        case EndpointType::SERVICE:
            index = &services_by_name_;
            break;
        case EndpointType::CLIENT:
            index = &clients_by_name_;
            break;
    }

    if (index) {
        auto index_it = index->find(name);
        if (index_it != index->end()) {
            auto& gid_list = index_it->second;
            gid_list.erase(
                std::remove_if(gid_list.begin(), gid_list.end(),
                    [gid](const rmw_gid_t& g) {
                        return memcmp(g.data, gid->data, RMW_GID_STORAGE_SIZE) == 0;
                    }),
                gid_list.end());

            // Remove empty entries
            if (gid_list.empty()) {
                index->erase(index_it);
            }
        }
    }

    fprintf(stderr, "[GraphCache] Unregistered local endpoint: %s (type=%d)\n",
            name.c_str(), static_cast<int>(endpoint.type));

    // Remove from GID index
    local_endpoints_.erase(it);

    trigger_graph_change();
}

// ============================================================
// Query APIs
// ============================================================

std::vector<GraphNodeInfo> GraphCache::get_all_nodes() const
{
    std::lock_guard<std::mutex> lock(mutex_);

    std::vector<GraphNodeInfo> result;

    // Collect local nodes
    for (const auto& pair : local_nodes_) {
        result.push_back(pair.second);
    }

    // Collect remote nodes (from all devices)
    for (const auto& device_pair : remote_nodes_) {
        for (const auto& node_pair : device_pair.second) {
            result.push_back(node_pair.second);
        }
    }

    return result;
}

std::map<std::string, std::set<std::string>> GraphCache::get_topic_names_and_types() const
{
    std::lock_guard<std::mutex> lock(mutex_);

    std::map<std::string, std::set<std::string>> result;

    // Collect from local endpoints
    for (const auto& pair : local_endpoints_) {
        const GraphEndpointInfo& ep = pair.second;
        if (ep.type == EndpointType::PUBLISHER || ep.type == EndpointType::SUBSCRIPTION) {
            result[ep.topic_name].insert(ep.type_name);
        }
    }

    // Collect from remote endpoints
    for (const auto& pair : remote_endpoints_) {
        const GraphEndpointInfo& ep = pair.second;
        if (ep.type == EndpointType::PUBLISHER || ep.type == EndpointType::SUBSCRIPTION) {
            result[ep.topic_name].insert(ep.type_name);
        }
    }

    return result;
}

std::map<std::string, std::set<std::string>> GraphCache::get_service_names_and_types() const
{
    std::lock_guard<std::mutex> lock(mutex_);

    std::map<std::string, std::set<std::string>> result;

    // Collect from local endpoints
    for (const auto& pair : local_endpoints_) {
        const GraphEndpointInfo& ep = pair.second;
        if (ep.type == EndpointType::SERVICE || ep.type == EndpointType::CLIENT) {
            result[ep.topic_name].insert(ep.type_name);
        }
    }

    // Collect from remote endpoints
    for (const auto& pair : remote_endpoints_) {
        const GraphEndpointInfo& ep = pair.second;
        if (ep.type == EndpointType::SERVICE || ep.type == EndpointType::CLIENT) {
            result[ep.topic_name].insert(ep.type_name);
        }
    }

    return result;
}

size_t GraphCache::count_publishers(const char* topic_name) const
{
    if (!topic_name) {
        return 0;
    }

    std::lock_guard<std::mutex> lock(mutex_);
    std::string topic_str(topic_name);
    size_t count = 0;

    // Count local publishers (from index)
    auto it = publishers_by_topic_.find(topic_str);
    if (it != publishers_by_topic_.end()) {
        count += it->second.size();
    }

    // Count remote publishers
    for (const auto& pair : remote_endpoints_) {
        const GraphEndpointInfo& ep = pair.second;
        if (ep.type == EndpointType::PUBLISHER && ep.topic_name == topic_str) {
            count++;
        }
    }

    return count;
}

size_t GraphCache::count_subscribers(const char* topic_name) const
{
    if (!topic_name) {
        return 0;
    }

    std::lock_guard<std::mutex> lock(mutex_);
    std::string topic_str(topic_name);
    size_t count = 0;

    // Count local subscriptions (from index)
    auto it = subscriptions_by_topic_.find(topic_str);
    if (it != subscriptions_by_topic_.end()) {
        count += it->second.size();
    }

    // Count remote subscriptions
    for (const auto& pair : remote_endpoints_) {
        const GraphEndpointInfo& ep = pair.second;
        if (ep.type == EndpointType::SUBSCRIPTION && ep.topic_name == topic_str) {
            count++;
        }
    }

    return count;
}

size_t GraphCache::count_services(const char* service_name) const
{
    if (!service_name) {
        return 0;
    }

    std::lock_guard<std::mutex> lock(mutex_);
    std::string name_str(service_name);
    size_t count = 0;

    // Count local services (from index)
    auto it = services_by_name_.find(name_str);
    if (it != services_by_name_.end()) {
        count += it->second.size();
    }

    // Count remote services
    for (const auto& pair : remote_endpoints_) {
        const GraphEndpointInfo& ep = pair.second;
        if (ep.type == EndpointType::SERVICE && ep.topic_name == name_str) {
            count++;
        }
    }

    return count;
}

size_t GraphCache::count_clients(const char* service_name) const
{
    if (!service_name) {
        return 0;
    }

    std::lock_guard<std::mutex> lock(mutex_);
    std::string name_str(service_name);
    size_t count = 0;

    // Count local clients (from index)
    auto it = clients_by_name_.find(name_str);
    if (it != clients_by_name_.end()) {
        count += it->second.size();
    }

    // Count remote clients
    for (const auto& pair : remote_endpoints_) {
        const GraphEndpointInfo& ep = pair.second;
        if (ep.type == EndpointType::CLIENT && ep.topic_name == name_str) {
            count++;
        }
    }

    return count;
}

std::optional<ServiceInfo> GraphCache::get_service_info(const char* service_name) const
{
    if (!service_name) {
        return std::nullopt;
    }

    std::lock_guard<std::mutex> lock(mutex_);
    std::string name_str(service_name);

    // Search local services first (from index)
    auto it = services_by_name_.find(name_str);
    if (it != services_by_name_.end() && !it->second.empty()) {
        // Return the first matching service
        const rmw_gid_t& gid = it->second.front();
        auto ep_it = local_endpoints_.find(gid);
        if (ep_it != local_endpoints_.end()) {
            const GraphEndpointInfo& ep = ep_it->second;
            ServiceInfo info;
            info.service_name = ep.topic_name;
            info.session_id = ep.session_id;
            info.server_gid = ep.gid;
            return info;
        }
    }

    // Search remote services
    for (const auto& pair : remote_endpoints_) {
        const GraphEndpointInfo& ep = pair.second;
        if (ep.type == EndpointType::SERVICE && ep.topic_name == name_str) {
            ServiceInfo info;
            info.service_name = ep.topic_name;
            info.session_id = ep.session_id;
            info.server_gid = ep.gid;
            return info;
        }
    }

    return std::nullopt;
}

std::vector<GraphEndpointInfo> GraphCache::get_publishers_for_topic(const char* topic_name) const
{
    std::vector<GraphEndpointInfo> result;

    if (!topic_name) {
        return result;
    }

    std::lock_guard<std::mutex> lock(mutex_);
    std::string topic_str(topic_name);

    // Collect local publishers
    auto it = publishers_by_topic_.find(topic_str);
    if (it != publishers_by_topic_.end()) {
        for (const auto& gid : it->second) {
            auto endpoint_it = local_endpoints_.find(gid);
            if (endpoint_it != local_endpoints_.end()) {
                result.push_back(endpoint_it->second);
            }
        }
    }

    // Collect remote publishers
    for (const auto& pair : remote_endpoints_) {
        const GraphEndpointInfo& ep = pair.second;
        if (ep.type == EndpointType::PUBLISHER && ep.topic_name == topic_str) {
            result.push_back(ep);
        }
    }

    return result;
}

std::vector<GraphEndpointInfo> GraphCache::get_subscribers_for_topic(const char* topic_name) const
{
    std::vector<GraphEndpointInfo> result;

    if (!topic_name) {
        return result;
    }

    std::lock_guard<std::mutex> lock(mutex_);
    std::string topic_str(topic_name);

    // Collect local subscriptions
    auto it = subscriptions_by_topic_.find(topic_str);
    if (it != subscriptions_by_topic_.end()) {
        for (const auto& gid : it->second) {
            auto endpoint_it = local_endpoints_.find(gid);
            if (endpoint_it != local_endpoints_.end()) {
                result.push_back(endpoint_it->second);
            }
        }
    }

    // Collect remote subscriptions
    for (const auto& pair : remote_endpoints_) {
        const GraphEndpointInfo& ep = pair.second;
        if (ep.type == EndpointType::SUBSCRIPTION && ep.topic_name == topic_str) {
            result.push_back(ep);
        }
    }

    return result;
}

const GraphEndpointInfo* GraphCache::lookup_endpoint_by_gid(const rmw_gid_t* gid) const
{
    if (!gid) {
        return nullptr;
    }

    std::lock_guard<std::mutex> lock(mutex_);

    // Search in local endpoints first
    auto it = local_endpoints_.find(*gid);
    if (it != local_endpoints_.end()) {
        return &it->second;
    }

    // Note: Remote endpoints use composite key (network_id + gid).
    // This function only looks up by GID, so we can't efficiently search remote.
    // For remote lookup, use network_id + gid directly.
    return nullptr;
}

// ============================================================
// By-Node Query APIs (Phase 5)
// ============================================================

std::map<std::string, std::set<std::string>> GraphCache::get_publisher_names_and_types_by_node(
    const char* node_name,
    const char* node_namespace) const
{
    std::map<std::string, std::set<std::string>> result;

    if (!node_name || !node_namespace) {
        return result;
    }

    std::lock_guard<std::mutex> lock(mutex_);
    std::string name_str(node_name);
    std::string ns_str(node_namespace);

    // Search local endpoints
    for (const auto& pair : local_endpoints_) {
        const GraphEndpointInfo& ep = pair.second;
        if (ep.type == EndpointType::PUBLISHER &&
            ep.node_name == name_str &&
            ep.node_namespace == ns_str) {
            result[ep.topic_name].insert(ep.type_name);
        }
    }

    // Search remote endpoints
    for (const auto& pair : remote_endpoints_) {
        const GraphEndpointInfo& ep = pair.second;
        if (ep.type == EndpointType::PUBLISHER &&
            ep.node_name == name_str &&
            ep.node_namespace == ns_str) {
            result[ep.topic_name].insert(ep.type_name);
        }
    }

    return result;
}

std::map<std::string, std::set<std::string>> GraphCache::get_subscriber_names_and_types_by_node(
    const char* node_name,
    const char* node_namespace) const
{
    std::map<std::string, std::set<std::string>> result;

    if (!node_name || !node_namespace) {
        return result;
    }

    std::lock_guard<std::mutex> lock(mutex_);
    std::string name_str(node_name);
    std::string ns_str(node_namespace);

    // Search local endpoints
    for (const auto& pair : local_endpoints_) {
        const GraphEndpointInfo& ep = pair.second;
        if (ep.type == EndpointType::SUBSCRIPTION &&
            ep.node_name == name_str &&
            ep.node_namespace == ns_str) {
            result[ep.topic_name].insert(ep.type_name);
        }
    }

    // Search remote endpoints
    for (const auto& pair : remote_endpoints_) {
        const GraphEndpointInfo& ep = pair.second;
        if (ep.type == EndpointType::SUBSCRIPTION &&
            ep.node_name == name_str &&
            ep.node_namespace == ns_str) {
            result[ep.topic_name].insert(ep.type_name);
        }
    }

    return result;
}

std::map<std::string, std::set<std::string>> GraphCache::get_service_names_and_types_by_node(
    const char* node_name,
    const char* node_namespace) const
{
    std::map<std::string, std::set<std::string>> result;

    if (!node_name || !node_namespace) {
        return result;
    }

    std::lock_guard<std::mutex> lock(mutex_);
    std::string name_str(node_name);
    std::string ns_str(node_namespace);

    // Search local endpoints
    for (const auto& pair : local_endpoints_) {
        const GraphEndpointInfo& ep = pair.second;
        if (ep.type == EndpointType::SERVICE &&
            ep.node_name == name_str &&
            ep.node_namespace == ns_str) {
            result[ep.topic_name].insert(ep.type_name);
        }
    }

    // Search remote endpoints
    for (const auto& pair : remote_endpoints_) {
        const GraphEndpointInfo& ep = pair.second;
        if (ep.type == EndpointType::SERVICE &&
            ep.node_name == name_str &&
            ep.node_namespace == ns_str) {
            result[ep.topic_name].insert(ep.type_name);
        }
    }

    return result;
}

std::map<std::string, std::set<std::string>> GraphCache::get_client_names_and_types_by_node(
    const char* node_name,
    const char* node_namespace) const
{
    std::map<std::string, std::set<std::string>> result;

    if (!node_name || !node_namespace) {
        return result;
    }

    std::lock_guard<std::mutex> lock(mutex_);
    std::string name_str(node_name);
    std::string ns_str(node_namespace);

    // Search local endpoints
    for (const auto& pair : local_endpoints_) {
        const GraphEndpointInfo& ep = pair.second;
        if (ep.type == EndpointType::CLIENT &&
            ep.node_name == name_str &&
            ep.node_namespace == ns_str) {
            result[ep.topic_name].insert(ep.type_name);
        }
    }

    // Search remote endpoints
    for (const auto& pair : remote_endpoints_) {
        const GraphEndpointInfo& ep = pair.second;
        if (ep.type == EndpointType::CLIENT &&
            ep.node_name == name_str &&
            ep.node_namespace == ns_str) {
            result[ep.topic_name].insert(ep.type_name);
        }
    }

    return result;
}

// ============================================================
// Graph Guard Condition
// ============================================================

void GraphCache::set_graph_guard_condition(void* guard_condition)
{
    std::lock_guard<std::mutex> lock(mutex_);
    graph_guard_condition_ = guard_condition;
}

uint64_t GraphCache::get_graph_version() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return graph_version_;
}

void GraphCache::trigger_graph_change()
{
    // Note: mutex_ is already held by caller

    // Increment graph version (monotonic counter)
    graph_version_++;

    if (!graph_guard_condition_) {
        return;
    }

    // Wake up any wait sets / executors waiting on graph changes
    auto* gc = static_cast<rmw_guard_condition_t*>(graph_guard_condition_);
    (void)rmw_trigger_guard_condition(gc);
}

// ============================================================
// Phase 2.3: Cross-device Discovery (Reserved)
// ============================================================

void GraphCache::on_remote_node_discovered(const GraphNodeInfo& remote_node)
{
    // Phase 2.3: Merge remote node into cache
    std::lock_guard<std::mutex> lock(mutex_);

    // Only add if from different network_id (remote)
    if (remote_node.network_id == get_local_network_id()) {
        return;  // Ignore local echoes
    }

    std::string key = remote_node.node_namespace + ":" + remote_node.node_name;

    // Store in remote_nodes_ indexed by network_id
    remote_nodes_[remote_node.network_id][key] = remote_node;

    fprintf(stderr, "[GraphCache] Discovered remote node: %s (network: %s)\n",
            remote_node.node_name.c_str(), remote_node.network_id.c_str());

    trigger_graph_change();
}

void GraphCache::on_remote_endpoint_discovered(const GraphEndpointInfo& remote_endpoint)
{
    // Phase 2.3: Merge remote endpoint into cache
    // Phase 4: Trigger subscriber discovery callback for 1:N auto-routing

    // Phase 4 Fix: Capture callback INSIDE lock to prevent use-after-free
    SubscriberDiscoveryCallback cb_to_call = nullptr;
    bool is_subscription = (remote_endpoint.type == EndpointType::SUBSCRIPTION);

    {
        std::lock_guard<std::mutex> lock(mutex_);

        // Only add if from different network_id (remote)
        if (remote_endpoint.network_id == get_local_network_id()) {
            return;  // Ignore local echoes
        }

        // Use composite key (network_id + gid) to prevent GID collision
        RemoteEndpointKey key;
        key.network_id = remote_endpoint.network_id;
        key.gid = remote_endpoint.gid;

        remote_endpoints_[key] = remote_endpoint;

        fprintf(stderr, "[GraphCache] Discovered remote endpoint: %s type=%d (network: %s)\n",
                remote_endpoint.topic_name.c_str(),
                static_cast<int>(remote_endpoint.type),
                remote_endpoint.network_id.c_str());

        trigger_graph_change();

        // Phase 4 Fix: Capture callback while still holding mutex_ (before releasing)
        // This prevents race with set_subscriber_callbacks(nullptr, nullptr) during shutdown
        if (is_subscription) {
            std::lock_guard<std::mutex> cb_lock(callback_mutex_);
            cb_to_call = subscriber_discovered_cb_;
        }
    }

    // Call callback outside data lock (safe: callback was captured while holding locks)
    if (cb_to_call) {
        fprintf(stderr, "[GraphCache] Triggering subscriber discovered callback: topic=%s, peer=%s\n",
                remote_endpoint.topic_name.c_str(), remote_endpoint.network_id.c_str());
        cb_to_call(remote_endpoint.topic_name, remote_endpoint.network_id, remote_endpoint.gid);
    }
}

void GraphCache::merge_remote_snapshot(
    const std::string& network_id,
    const std::vector<GraphNodeInfo>& nodes,
    const std::vector<GraphEndpointInfo>& endpoints)
{
    // Batch merge: single lock, single guard trigger
    std::lock_guard<std::mutex> lock(mutex_);

    std::string local_id = get_local_network_id();

    // Skip if this is somehow our own network_id (shouldn't happen)
    if (network_id == local_id) {
        return;
    }

    bool changed = false;

    // Merge nodes
    auto& node_map = remote_nodes_[network_id];
    for (const auto& node : nodes) {
        std::string key = make_node_key(node.node_namespace, node.node_name);
        if (node_map.find(key) == node_map.end()) {
            changed = true;
        }
        node_map[key] = node;
    }

    // Merge endpoints
    for (const auto& ep : endpoints) {
        RemoteEndpointKey key;
        key.network_id = network_id;
        key.gid = ep.gid;

        if (remote_endpoints_.find(key) == remote_endpoints_.end()) {
            changed = true;
        }
        remote_endpoints_[key] = ep;
    }

    // Only trigger guard condition if something actually changed
    if (changed) {
        trigger_graph_change();
    }

    fprintf(stderr, "[GraphCache] Batch merged from %s: %zu nodes, %zu endpoints\n",
            network_id.c_str(), nodes.size(), endpoints.size());
}

GraphSnapshot GraphCache::snapshot() const
{
    std::lock_guard<std::mutex> lock(mutex_);

    GraphSnapshot snap;
    snap.timestamp_ns = get_timestamp_ns();

    // Copy local nodes
    for (const auto& pair : local_nodes_) {
        snap.nodes.push_back(pair.second);
    }

    // Copy remote nodes
    for (const auto& device_pair : remote_nodes_) {
        for (const auto& node_pair : device_pair.second) {
            snap.nodes.push_back(node_pair.second);
        }
    }

    // Copy local endpoints
    for (const auto& pair : local_endpoints_) {
        snap.endpoints.push_back(pair.second);
    }

    // Copy remote endpoints
    for (const auto& pair : remote_endpoints_) {
        snap.endpoints.push_back(pair.second);
    }

    return snap;
}

GraphSnapshot GraphCache::snapshot_local_only() const
{
    std::lock_guard<std::mutex> lock(mutex_);

    GraphSnapshot snap;
    snap.timestamp_ns = get_timestamp_ns();

    // Copy local nodes only
    snap.nodes.reserve(local_nodes_.size());
    for (const auto& pair : local_nodes_) {
        snap.nodes.push_back(pair.second);
    }

    // Copy local endpoints only
    snap.endpoints.reserve(local_endpoints_.size());
    for (const auto& pair : local_endpoints_) {
        snap.endpoints.push_back(pair.second);
    }

    return snap;
}

std::map<std::string, GraphNodeInfo> GraphCache::get_local_nodes() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return local_nodes_;
}

void GraphCache::remove_remote_node(const std::string& network_id, const std::string& node_key)
{
    std::lock_guard<std::mutex> lock(mutex_);

    auto device_it = remote_nodes_.find(network_id);
    if (device_it == remote_nodes_.end()) {
        return;
    }

    auto node_it = device_it->second.find(node_key);
    if (node_it != device_it->second.end()) {
        fprintf(stderr, "[GraphCache] Removing remote node: %s (network: %s)\n",
                node_key.c_str(), network_id.c_str());
        device_it->second.erase(node_it);

        // Clean up empty device entry
        if (device_it->second.empty()) {
            remote_nodes_.erase(device_it);
        }

        trigger_graph_change();
    }
}

void GraphCache::remove_remote_endpoint(const std::string& network_id, const rmw_gid_t& gid)
{
    // Phase 4: Capture endpoint info for callback before removing
    // Phase 4 Fix: Capture callback INSIDE lock to prevent use-after-free
    SubscriberRemovalCallback cb_to_call = nullptr;
    std::string topic_name;
    std::string peer_network_id;
    rmw_gid_t endpoint_gid;
    bool was_subscription = false;

    {
        std::lock_guard<std::mutex> lock(mutex_);

        RemoteEndpointKey key;
        key.network_id = network_id;
        key.gid = gid;

        auto it = remote_endpoints_.find(key);
        if (it != remote_endpoints_.end()) {
            // Capture info before removal
            topic_name = it->second.topic_name;
            peer_network_id = it->second.network_id;  // Preserve for callback
            endpoint_gid = it->second.gid;
            was_subscription = (it->second.type == EndpointType::SUBSCRIPTION);

            fprintf(stderr, "[GraphCache] Removing remote endpoint: %s (network: %s)\n",
                    topic_name.c_str(), network_id.c_str());
            remote_endpoints_.erase(it);
            trigger_graph_change();

            // Phase 4 Fix: Capture callback while still holding mutex_ (before releasing)
            if (was_subscription) {
                std::lock_guard<std::mutex> cb_lock(callback_mutex_);
                cb_to_call = subscriber_removed_cb_;
            }
        } else {
            return;  // Nothing to remove
        }
    }

    // Call callback outside data lock (safe: callback was captured while holding locks)
    if (cb_to_call) {
        fprintf(stderr, "[GraphCache] Triggering subscriber removed callback: topic=%s, peer=%s\n",
                topic_name.c_str(), peer_network_id.c_str());
        cb_to_call(topic_name, peer_network_id, endpoint_gid);
    }
}

void GraphCache::remove_all_from_network_id(const std::string& network_id)
{
    std::lock_guard<std::mutex> lock(mutex_);

    bool changed = false;

    // Remove all nodes from this network
    auto node_it = remote_nodes_.find(network_id);
    if (node_it != remote_nodes_.end()) {
        fprintf(stderr, "[GraphCache] Removing %zu nodes from network: %s\n",
                node_it->second.size(), network_id.c_str());
        remote_nodes_.erase(node_it);
        changed = true;
    }

    // Remove all endpoints from this network
    for (auto it = remote_endpoints_.begin(); it != remote_endpoints_.end(); ) {
        if (it->first.network_id == network_id) {
            it = remote_endpoints_.erase(it);
            changed = true;
        } else {
            ++it;
        }
    }

    if (changed) {
        fprintf(stderr, "[GraphCache] Removed all entities from network: %s\n", network_id.c_str());
        trigger_graph_change();
    }
}

void GraphCache::broadcast_local_graph()
{
    // Phase 2.3: Delegate to DiscoveryManager
    // DiscoveryManager will call snapshot_local_only() and broadcast
    fprintf(stderr, "[GraphCache] broadcast_local_graph() - use DiscoveryManager\n");
}

// ============================================================
// Internal Helpers
// ============================================================

std::string GraphCache::get_local_network_id() const
{
    // Phase 2.2: Use process ID as local identifier
    // Phase 2.3: Use actual dsoftbus network ID
    static std::string local_id;
    if (local_id.empty()) {
        char buf[64];
        snprintf(buf, sizeof(buf), "local_pid_%d", getpid());
        local_id = buf;
    }
    return local_id;
}

uint64_t GraphCache::get_timestamp_ns() const
{
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return static_cast<uint64_t>(ts.tv_sec) * 1000000000ULL +
           static_cast<uint64_t>(ts.tv_nsec);
}

// ============================================================
// Phase 4: 1:N Auto-Routing Callbacks
// ============================================================

void GraphCache::set_subscriber_callbacks(
    SubscriberDiscoveryCallback on_discovered,
    SubscriberRemovalCallback on_removed)
{
    std::lock_guard<std::mutex> lock(callback_mutex_);
    subscriber_discovered_cb_ = on_discovered;
    subscriber_removed_cb_ = on_removed;

    fprintf(stderr, "[GraphCache] Subscriber callbacks registered: discovered=%p, removed=%p\n",
            reinterpret_cast<void*>(on_discovered), reinterpret_cast<void*>(on_removed));
}

std::string GraphCache::get_local_network_id_public() const
{
    return get_local_network_id();
}

}  // namespace rmw_dsoftbus
