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
 * @file session_manager.h
 *
 * @brief Declares session manager for managing dsoftbus sessions.
 *
 * @since 1.0
 * @version 1.0
 */
#ifndef RMW_DSOFTBUS__SESSION_MANAGER_H_
#define RMW_DSOFTBUS__SESSION_MANAGER_H_

#include <string>
#include <unordered_map>
#include <mutex>
#include <vector>

namespace rmw_dsoftbus {

// Forward declaration
struct SubscriptionImpl;

// Session connection tracking
struct SessionConnection {
    int session_id{-1};
    std::string topic_name;
    std::string session_name;     // Full session name (for matching)
    std::string peer_network_id;
    bool is_connected{false};
    bool is_inbound{false};       // true if opened by remote device, false if we opened it
    int retry_count{0};
    uint64_t last_attempt_time{0};
};

class SessionManager
{
public:
    static SessionManager& instance();

    // Initialize dsoftbus and create global listener
    bool initialize();
    void shutdown();

    // Subscription: Register topic server (passive)
    int register_subscription(const std::string& topic_name, SubscriptionImpl* sub);
    void unregister_subscription(const std::string& topic_name);

    // Publisher: Open session to peer (active)
    int open_session(const std::string& topic_name, const std::string& peer_network_id);
    void close_session(int session_id);

    // Send data through session
    int send_bytes(int session_id, const void* data, unsigned int len);

    // Session state query (for is_service_available)
    bool is_session_alive(int session_id) const;

    // Global callbacks (called by dsoftbus)
    static int on_session_opened_callback(int sessionId, int result);
    static void on_session_closed_callback(int sessionId);
    static void on_bytes_received_callback(int sessionId, const void* data, unsigned int dataLen);

private:
    SessionManager();
    ~SessionManager();

    SessionManager(const SessionManager&) = delete;
    SessionManager& operator=(const SessionManager&) = delete;

    // Internal callback handlers
    void on_session_opened(int sessionId, int result);
    void on_session_closed(int sessionId);
    void on_bytes_received(int sessionId, const void* data, unsigned int dataLen);

    mutable std::mutex mutex_;
    bool initialized_{false};

    // Session tracking
    std::unordered_map<int, SessionConnection> sessions_;  // session_id -> connection
    std::unordered_map<std::string, SubscriptionImpl*> subscriptions_;  // topic -> sub

    // Session server IDs for topics
    std::unordered_map<std::string, int> topic_servers_;  // topic -> server_id
};

}  // namespace rmw_dsoftbus

#endif  // RMW_DSOFTBUS__SESSION_MANAGER_H_
