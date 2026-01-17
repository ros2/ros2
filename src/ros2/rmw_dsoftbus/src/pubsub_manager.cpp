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

#include "rmw_dsoftbus/pubsub_manager.h"
#include "rmw_dsoftbus/protocol.h"

#include <cstdio>
#include <cstring>
#include <algorithm>  // For std::remove

namespace rmw_dsoftbus {

PubSubManager::PubSubManager() {
}

PubSubManager::~PubSubManager() {
    shutdown();
}

rmw_ret_t PubSubManager::initialize() {
    std::lock_guard<std::mutex> lock(managers_mutex_);

    fprintf(stderr, "[PubSubManager] Initializing PubSubManager\n");

    return RMW_RET_OK;
}

void PubSubManager::shutdown() {
    std::lock_guard<std::mutex> lock(managers_mutex_);

    fprintf(stderr, "[PubSubManager] Shutting down PubSubManager\n");

    // Clear all publishers and subscribers
    publishers_.clear();
    subscribers_.clear();
    subscribers_by_topic_.clear();
}

// ============================================================================
// Publisher Management
// ============================================================================

rmw_ret_t PubSubManager::create_publisher(
    rmw_publisher_t* publisher,
    const rmw_node_t* node,
    const rosidl_message_type_support_t* type_support,
    const char* topic_name,
    const rmw_qos_profile_t* qos_profile) {

    if (!publisher || !node || !type_support || !topic_name || !qos_profile) {
        fprintf(stderr, "[PubSubManager] Invalid arguments to create_publisher\n");
        return RMW_RET_INVALID_ARGUMENT;
    }

    std::lock_guard<std::mutex> lock(managers_mutex_);

    fprintf(stderr, "[PubSubManager] Creating publisher for topic '%s'\n", topic_name);

    // Create publisher implementation
    PublisherImpl pub_impl;
    pub_impl.topic_name = topic_name;
    pub_impl.type_name = "unknown";  // TODO: Extract from type_support
    pub_impl.qos = *qos_profile;
    pub_impl.type_support = type_support;
    pub_impl.node = node;
    pub_impl.owner_network_id = "";  // Will be set when sending

    // Store in map
    publishers_[publisher] = pub_impl;

    fprintf(stderr, "[PubSubManager] Publisher created for topic '%s'\n", topic_name);

    return RMW_RET_OK;
}

rmw_ret_t PubSubManager::destroy_publisher(const rmw_publisher_t* publisher) {
    if (!publisher) {
        return RMW_RET_INVALID_ARGUMENT;
    }

    std::lock_guard<std::mutex> lock(managers_mutex_);

    auto it = publishers_.find(publisher);
    if (it == publishers_.end()) {
        fprintf(stderr, "[PubSubManager] Publisher not found\n");
        return RMW_RET_OK;
    }

    fprintf(stderr, "[PubSubManager] Destroying publisher for topic '%s'\n",
            it->second.topic_name.c_str());

    publishers_.erase(it);

    return RMW_RET_OK;
}

rmw_ret_t PubSubManager::publish(
    const rmw_publisher_t* publisher,
    const void* ros_message) {

    if (!publisher || !ros_message) {
        return RMW_RET_INVALID_ARGUMENT;
    }

    std::vector<uint8_t> serialized;

    auto it = publishers_.find(publisher);
    if (it == publishers_.end()) {
        fprintf(stderr, "[PubSubManager] Publisher not found\n");
        return RMW_RET_ERROR;
    }

    // Serialize the message
    rmw_ret_t ret = serialize_message(ros_message, it->second.type_support, serialized);
    if (ret != RMW_RET_OK) {
        fprintf(stderr, "[PubSubManager] Message serialization failed\n");
        return ret;
    }

    return publish_bytes(publisher, serialized.data(), serialized.size());
}

rmw_ret_t PubSubManager::publish_bytes(
    const rmw_publisher_t* publisher,
    const uint8_t* serialized_msg,
    size_t len) {

    if (!publisher || !serialized_msg || len == 0) {
        return RMW_RET_INVALID_ARGUMENT;
    }

    std::lock_guard<std::mutex> lock(managers_mutex_);

    auto it = publishers_.find(publisher);
    if (it == publishers_.end()) {
        fprintf(stderr, "[PubSubManager] Publisher not found\n");
        return RMW_RET_ERROR;
    }

    fprintf(stderr, "[PubSubManager] Publishing %zu bytes on topic '%s'\n",
            len, it->second.topic_name.c_str());

    // TODO: Send via SessionPool to all matching subscribers
    // This will be implemented in Phase 3.2/3.3

    return RMW_RET_OK;
}

// ============================================================================
// Subscriber Management
// ============================================================================

rmw_ret_t PubSubManager::create_subscription(
    rmw_subscription_t* subscription,
    const rmw_node_t* node,
    const rosidl_message_type_support_t* type_support,
    const char* topic_name,
    const rmw_qos_profile_t* qos_profile) {

    if (!subscription || !node || !type_support || !topic_name || !qos_profile) {
        fprintf(stderr, "[PubSubManager] Invalid arguments to create_subscription\n");
        return RMW_RET_INVALID_ARGUMENT;
    }

    std::lock_guard<std::mutex> lock(managers_mutex_);

    fprintf(stderr, "[PubSubManager] Creating subscription for topic '%s'\n", topic_name);

    // Create subscriber implementation
    SubscriberImpl sub_impl;
    sub_impl.topic_name = topic_name;
    sub_impl.type_name = "unknown";  // TODO: Extract from type_support
    sub_impl.qos = *qos_profile;
    sub_impl.type_support = type_support;
    sub_impl.node = node;

    // Store in map
    subscribers_[subscription] = sub_impl;

    // Add to topic index
    subscribers_by_topic_[topic_name].push_back(subscription);

    fprintf(stderr, "[PubSubManager] Subscription created for topic '%s'\n", topic_name);

    return RMW_RET_OK;
}

rmw_ret_t PubSubManager::destroy_subscription(const rmw_subscription_t* subscription) {
    if (!subscription) {
        return RMW_RET_INVALID_ARGUMENT;
    }

    std::lock_guard<std::mutex> lock(managers_mutex_);

    auto it = subscribers_.find(subscription);
    if (it == subscribers_.end()) {
        fprintf(stderr, "[PubSubManager] Subscription not found\n");
        return RMW_RET_OK;
    }

    const std::string& topic_name = it->second.topic_name;

    fprintf(stderr, "[PubSubManager] Destroying subscription for topic '%s'\n",
            topic_name.c_str());

    // Remove from topic index
    auto topic_it = subscribers_by_topic_.find(topic_name);
    if (topic_it != subscribers_by_topic_.end()) {
        auto& subs = topic_it->second;
        subs.erase(std::remove(subs.begin(), subs.end(), subscription), subs.end());

        if (subs.empty()) {
            subscribers_by_topic_.erase(topic_it);
        }
    }

    subscribers_.erase(it);

    return RMW_RET_OK;
}

rmw_ret_t PubSubManager::take(
    const rmw_subscription_t* subscription,
    void* ros_message,
    bool* taken,
    rmw_message_info_t* message_info) {

    if (!subscription || !ros_message || !taken) {
        return RMW_RET_INVALID_ARGUMENT;
    }

    *taken = false;

    std::lock_guard<std::mutex> lock(managers_mutex_);

    auto it = subscribers_.find(subscription);
    if (it == subscribers_.end()) {
        fprintf(stderr, "[PubSubManager] Subscription not found\n");
        return RMW_RET_ERROR;
    }

    SubscriberImpl& sub = it->second;

    {
        // NOTE: Already protected by managers_mutex_ from lock_guard above

        if (sub.message_queue.empty()) {
            return RMW_RET_OK;
        }

        // Get message from queue
        const std::vector<uint8_t>& serialized_msg = sub.message_queue.front();

        // Deserialize message
        rmw_ret_t ret = deserialize_message(serialized_msg.data(), serialized_msg.size(),
                                           sub.type_support, ros_message);
        if (ret != RMW_RET_OK) {
            fprintf(stderr, "[PubSubManager] Message deserialization failed\n");
            sub.message_queue.pop();
            return ret;
        }

        // Get source network ID if available
        if (!sub.source_network_ids.empty()) {
            std::string source_id = sub.source_network_ids.front();
            sub.source_network_ids.pop();
            fprintf(stderr, "[PubSubManager] Message received from %s\n", source_id.c_str());
        }

        sub.message_queue.pop();
        *taken = true;

        if (message_info) {
            std::memset(message_info, 0, sizeof(*message_info));
            // TODO: Fill in message_info with sequence number, timestamp, etc.
        }
    }

    return RMW_RET_OK;
}

rmw_ret_t PubSubManager::take_bytes(
    const rmw_subscription_t* subscription,
    uint8_t* serialized_msg,
    size_t* len,
    bool* taken) {

    if (!subscription || !serialized_msg || !len || !taken) {
        return RMW_RET_INVALID_ARGUMENT;
    }

    *taken = false;

    std::lock_guard<std::mutex> lock(managers_mutex_);

    auto it = subscribers_.find(subscription);
    if (it == subscribers_.end()) {
        return RMW_RET_ERROR;
    }

    SubscriberImpl& sub = it->second;

    {
        // NOTE: Already protected by managers_mutex_ from lock_guard above

        if (sub.message_queue.empty()) {
            return RMW_RET_OK;
        }

        const std::vector<uint8_t>& msg = sub.message_queue.front();

        if (*len < msg.size()) {
            fprintf(stderr, "[PubSubManager] Buffer too small: %zu < %zu\n", *len, msg.size());
            return RMW_RET_ERROR;
        }

        std::memcpy(serialized_msg, msg.data(), msg.size());
        *len = msg.size();
        *taken = true;

        sub.message_queue.pop();
    }

    return RMW_RET_OK;
}

// ============================================================================
// Message Routing
// ============================================================================

void PubSubManager::route_message(const std::string& topic_name,
                                  const uint8_t* data,
                                  size_t len,
                                  const std::string& source_network_id) {

    std::lock_guard<std::mutex> lock(managers_mutex_);

    fprintf(stderr, "[PubSubManager] Routing %zu bytes for topic '%s' from %s\n",
            len, topic_name.c_str(), source_network_id.c_str());

    // Find matching subscribers
    auto topic_it = subscribers_by_topic_.find(topic_name);
    if (topic_it == subscribers_by_topic_.end()) {
        fprintf(stderr, "[PubSubManager] No subscribers for topic '%s'\n", topic_name.c_str());
        return;
    }

    // Deliver to all matching subscribers
    for (const auto* sub_ptr : topic_it->second) {
        auto sub_it = subscribers_.find(sub_ptr);
        if (sub_it == subscribers_.end()) {
            continue;
        }

        SubscriberImpl& sub = sub_it->second;

        {
            // NOTE: Already protected by managers_mutex_ from lock_guard above

            std::vector<uint8_t> msg(data, data + len);
            sub.message_queue.push(std::move(msg));
            sub.source_network_ids.push(source_network_id);

            fprintf(stderr, "[PubSubManager] Message queued for subscription on topic '%s'\n",
                    topic_name.c_str());
        }
    }
}

std::vector<const rmw_subscription_t*> PubSubManager::find_matching_subscribers(
    const std::string& topic_name) {

    std::lock_guard<std::mutex> lock(managers_mutex_);

    auto it = subscribers_by_topic_.find(topic_name);
    if (it != subscribers_by_topic_.end()) {
        return it->second;
    }

    return {};
}

std::vector<const rmw_publisher_t*> PubSubManager::find_publishers_by_topic(
    const std::string& topic_name) {

    std::lock_guard<std::mutex> lock(managers_mutex_);

    std::vector<const rmw_publisher_t*> result;

    for (const auto& pair : publishers_) {
        if (pair.second.topic_name == topic_name) {
            result.push_back(pair.first);
        }
    }

    return result;
}

// ============================================================================
// Topic Query
// ============================================================================

rmw_ret_t PubSubManager::get_topic_names_and_types(
    rmw_names_and_types_t* topic_names_and_types,
    rcutils_allocator_t* allocator,
    bool no_demangle) {

    if (!topic_names_and_types || !allocator) {
        return RMW_RET_INVALID_ARGUMENT;
    }

    std::lock_guard<std::mutex> lock(managers_mutex_);

    // TODO: Implement topic enumeration
    // For now, return OK with empty list
    fprintf(stderr, "[PubSubManager] get_topic_names_and_types called\n");

    return RMW_RET_OK;
}

rmw_ret_t PubSubManager::get_publishers_info_by_topic(
    const rmw_node_t* node,
    rcutils_allocator_t* allocator,
    const char* topic_name,
    bool no_demangle,
    rmw_topic_endpoint_info_array_t* publishers_info) {

    if (!node || !allocator || !topic_name || !publishers_info) {
        return RMW_RET_INVALID_ARGUMENT;
    }

    std::lock_guard<std::mutex> lock(managers_mutex_);

    // TODO: Implement publisher info query
    fprintf(stderr, "[PubSubManager] get_publishers_info_by_topic called for '%s'\n", topic_name);

    return RMW_RET_OK;
}

rmw_ret_t PubSubManager::get_subscriptions_info_by_topic(
    const rmw_node_t* node,
    rcutils_allocator_t* allocator,
    const char* topic_name,
    bool no_demangle,
    rmw_topic_endpoint_info_array_t* subscriptions_info) {

    if (!node || !allocator || !topic_name || !subscriptions_info) {
        return RMW_RET_INVALID_ARGUMENT;
    }

    std::lock_guard<std::mutex> lock(managers_mutex_);

    // TODO: Implement subscription info query
    fprintf(stderr, "[PubSubManager] get_subscriptions_info_by_topic called for '%s'\n",
            topic_name);

    return RMW_RET_OK;
}

// ============================================================================
// Private Helper Methods
// ============================================================================

rmw_ret_t PubSubManager::serialize_message(
    const void* ros_message,
    const rosidl_message_type_support_t* type_support,
    std::vector<uint8_t>& serialized) {

    // TODO: Implement CDR serialization
    // For now, just return OK
    fprintf(stderr, "[PubSubManager] serialize_message called\n");

    return RMW_RET_OK;
}

rmw_ret_t PubSubManager::deserialize_message(
    const uint8_t* serialized_msg,
    size_t len,
    const rosidl_message_type_support_t* type_support,
    void* ros_message) {

    // TODO: Implement CDR deserialization
    // For now, just return OK
    fprintf(stderr, "[PubSubManager] deserialize_message called with %zu bytes\n", len);

    return RMW_RET_OK;
}

bool PubSubManager::topic_matches(const std::string& pub_topic,
                                   const std::string& sub_topic) {

    // Simple exact match for now
    // TODO: Implement wildcard matching if needed
    return pub_topic == sub_topic;
}

}  // namespace rmw_dsoftbus
