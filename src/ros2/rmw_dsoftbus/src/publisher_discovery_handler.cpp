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

//
// Publisher Discovery Handler - 1:N Auto-routing
// Integrates with GraphCache to automatically connect Publishers to discovered Subscribers
//

// C standard library (must come before C++ headers for gcc-linaro compatibility)
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "rmw_dsoftbus/types.h"
#include "rmw_dsoftbus/graph_cache.h"
#include "rmw_dsoftbus/session_manager.h"
#include "rmw/rmw.h"

#include <algorithm>  // for std::remove
#include <cstdio>
#include <mutex>
#include <unordered_map>
#include <vector>

namespace rmw_dsoftbus {

// ============================================================================
// Global State
// ============================================================================

// Publisher impl tracking for discovery events
static std::unordered_map<std::string, std::vector<PublisherImpl*>> g_publishers_by_topic;
static std::mutex g_discovery_mutex;

// ============================================================================
// Discovery Event Handlers
// ============================================================================

/**
 * @brief Handle subscriber discovery event from GraphCache
 *
 * When a remote Subscriber is discovered via Graph Discovery,
 * all local Publishers on the same topic automatically establish sessions.
 * Phase 4: Includes deduplication via peer_to_session map.
 *
 * @param topic_name Topic name
 * @param peer_network_id Remote device network ID
 * @param subscriber_gid Subscriber GID
 */
void on_subscriber_discovered(const std::string& topic_name,
                                const std::string& peer_network_id,
                                const rmw_gid_t& subscriber_gid) {
    std::lock_guard<std::mutex> lock(g_discovery_mutex);

    fprintf(stderr, "[PublisherDiscovery] Subscriber discovered: topic=%s, peer=%s\n",
            topic_name.c_str(), peer_network_id.c_str());

    // Find all local Publishers on this topic
    auto it = g_publishers_by_topic.find(topic_name);
    if (it == g_publishers_by_topic.end() || it->second.empty()) {
        fprintf(stderr, "[PublisherDiscovery] No local publishers for topic %s\n",
                topic_name.c_str());
        return;
    }

    // For each Publisher, establish session to remote Subscriber
    for (PublisherImpl* pub_impl : it->second) {
        std::lock_guard<std::mutex> session_lock(pub_impl->session_mutex);

        // Phase 4: Deduplication check using peer_to_session map
        if (pub_impl->peer_to_session.count(peer_network_id) > 0) {
            fprintf(stderr,
                    "[PublisherDiscovery] Already connected to peer: topic=%s, peer=%s, existing_session=%d\n",
                    topic_name.c_str(), peer_network_id.c_str(),
                    pub_impl->peer_to_session[peer_network_id]);
            continue;  // Skip duplicate connection
        }

        // Open session to remote Subscriber
        int session_id = SessionManager::instance().open_session(
            topic_name, peer_network_id);

        if (session_id >= 0) {
            // Add to session tracking
            pub_impl->session_ids.push_back(session_id);
            pub_impl->peer_to_session[peer_network_id] = session_id;
            pub_impl->matched_count++;

            fprintf(stderr,
                    "[PublisherDiscovery] Auto-connected Publisher to Subscriber: "
                    "topic=%s, peer=%s, session=%d, total_sessions=%zu\n",
                    topic_name.c_str(), peer_network_id.c_str(), session_id,
                    pub_impl->session_ids.size());
        } else {
            fprintf(stderr,
                    "[ERROR] Failed to auto-connect Publisher: topic=%s, peer=%s, ret=%d\n",
                    topic_name.c_str(), peer_network_id.c_str(), session_id);
        }
    }
}

/**
 * @brief Handle subscriber removal event from GraphCache
 *
 * When a Subscriber goes offline, close the corresponding sessions
 * and clean up tracking maps.
 *
 * Phase 4 Fix: Now properly cleans up peer_to_session and session_ids.
 *
 * @param topic_name Topic name
 * @param peer_network_id Remote device network ID (for cleaning up peer_to_session)
 * @param subscriber_gid Subscriber GID
 */
void on_subscriber_removed(const std::string& topic_name,
                             const std::string& peer_network_id,
                             const rmw_gid_t& subscriber_gid) {
    std::lock_guard<std::mutex> lock(g_discovery_mutex);

    fprintf(stderr, "[PublisherDiscovery] Subscriber removed: topic=%s, peer=%s\n",
            topic_name.c_str(), peer_network_id.c_str());

    // Find all local Publishers on this topic
    auto it = g_publishers_by_topic.find(topic_name);
    if (it == g_publishers_by_topic.end()) {
        return;
    }

    // For each Publisher, close session to this peer and clean up tracking
    for (PublisherImpl* pub_impl : it->second) {
        std::lock_guard<std::mutex> session_lock(pub_impl->session_mutex);

        // Phase 4 Fix: Look up session by peer_network_id and clean up properly
        auto peer_it = pub_impl->peer_to_session.find(peer_network_id);
        if (peer_it != pub_impl->peer_to_session.end()) {
            int session_id = peer_it->second;

            // Close the session (SessionManager handles actual dsoftbus CloseSession)
            SessionManager::instance().close_session(session_id);

            // Remove from session_ids vector
            auto sid_it = std::find(pub_impl->session_ids.begin(),
                                     pub_impl->session_ids.end(),
                                     session_id);
            if (sid_it != pub_impl->session_ids.end()) {
                pub_impl->session_ids.erase(sid_it);
            }

            // Remove from peer_to_session map
            pub_impl->peer_to_session.erase(peer_it);

            // Update matched count
            if (pub_impl->matched_count > 0) {
                pub_impl->matched_count--;
            }

            fprintf(stderr,
                    "[PublisherDiscovery] Cleaned up session %d for peer %s, "
                    "remaining sessions: %zu, matched_count: %zu\n",
                    session_id, peer_network_id.c_str(),
                    pub_impl->session_ids.size(), pub_impl->matched_count.load());
        } else {
            fprintf(stderr,
                    "[PublisherDiscovery] No session found for peer %s on topic %s\n",
                    peer_network_id.c_str(), topic_name.c_str());
        }
    }
}

// ============================================================================
// Publisher Registration API
// ============================================================================

/**
 * @brief Register Publisher for discovery events
 *
 * Called by rmw_create_publisher to enable auto-discovery.
 * Phase 4: Also queries GraphCache for existing Subscribers (late-join scenario).
 *
 * @param topic_name Topic name
 * @param pub_impl Publisher implementation
 */
void register_publisher_for_discovery(const std::string& topic_name,
                                        PublisherImpl* pub_impl) {
    // Register with tracking map
    {
        std::lock_guard<std::mutex> lock(g_discovery_mutex);
        g_publishers_by_topic[topic_name].push_back(pub_impl);
    }

    fprintf(stderr, "[PublisherDiscovery] Registered Publisher for auto-discovery: %s\n",
            topic_name.c_str());

    // Phase 4: Late-join - Query GraphCache for existing Subscribers on this topic
    std::vector<GraphEndpointInfo> existing_subs =
        GraphCache::instance().get_subscribers_for_topic(topic_name.c_str());

    std::string local_network_id = GraphCache::instance().get_local_network_id_public();

    size_t remote_count = 0;
    for (const auto& sub_ep : existing_subs) {
        // Skip local subscribers (same process) - use network_id check
        if (sub_ep.network_id == local_network_id) {
            continue;
        }

        // Trigger discovery handler for each existing remote Subscriber
        // This will establish sessions with deduplication
        on_subscriber_discovered(topic_name, sub_ep.network_id, sub_ep.gid);
        remote_count++;
    }

    fprintf(stderr, "[PublisherDiscovery] Late-join: found %zu existing remote subscribers for topic %s\n",
            remote_count, topic_name.c_str());
}

/**
 * @brief Unregister Publisher from discovery events
 *
 * Called by rmw_destroy_publisher.
 * Phase 4 Fix: Properly closes all sessions before unregistering.
 *
 * @param topic_name Topic name
 * @param pub_impl Publisher implementation
 */
void unregister_publisher_from_discovery(const std::string& topic_name,
                                          PublisherImpl* pub_impl) {
    // Phase 4 Fix: Close all sessions before unregistering to prevent resource leaks
    {
        std::lock_guard<std::mutex> session_lock(pub_impl->session_mutex);

        for (int session_id : pub_impl->session_ids) {
            fprintf(stderr, "[PublisherDiscovery] Closing session %d for unregistering publisher: %s\n",
                    session_id, topic_name.c_str());
            SessionManager::instance().close_session(session_id);
        }

        pub_impl->session_ids.clear();
        pub_impl->peer_to_session.clear();
        pub_impl->matched_count = 0;
    }

    // Now remove from tracking map
    std::lock_guard<std::mutex> lock(g_discovery_mutex);

    auto it = g_publishers_by_topic.find(topic_name);
    if (it != g_publishers_by_topic.end()) {
        auto& pubs = it->second;
        // Use <algorithm> std::remove, not <stdio.h> remove
        pubs.erase(std::remove(pubs.begin(), pubs.end(), pub_impl), pubs.end());

        if (pubs.empty()) {
            g_publishers_by_topic.erase(it);
        }

        fprintf(stderr, "[PublisherDiscovery] Unregistered Publisher: %s\n",
                topic_name.c_str());
    }
}

// ============================================================================
// GraphCache Integration Hooks
// ============================================================================

/**
 * @brief Initialize discovery handler
 *
 * Register callbacks with GraphCache for Subscriber discovery events.
 * Called during rmw_init.
 */
void init_publisher_discovery_handler() {
    // TODO Phase 3: Register callbacks with GraphCache
    // GraphCache::instance().register_subscriber_callback(on_subscriber_discovered, on_subscriber_removed);

    fprintf(stderr, "[PublisherDiscovery] Discovery handler initialized (Phase 2.2 stub)\n");
    fprintf(stderr, "[INFO] Phase 3: Will register GraphCache callbacks for auto-discovery\n");
}

/**
 * @brief Shutdown discovery handler
 *
 * Unregister callbacks and clear state.
 * Called during rmw_shutdown.
 */
void shutdown_publisher_discovery_handler() {
    std::lock_guard<std::mutex> lock(g_discovery_mutex);

    g_publishers_by_topic.clear();

    fprintf(stderr, "[PublisherDiscovery] Discovery handler shutdown\n");
}

} // namespace rmw_dsoftbus
