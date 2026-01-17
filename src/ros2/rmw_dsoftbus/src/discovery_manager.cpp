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

#include "rmw_dsoftbus/discovery_manager.h"
#include "dsoftbus/softbus_error_code.h"
#include "rmw_dsoftbus/dsoftbus_session.h"
#include "rmw_dsoftbus/native_token.h"
#include "rmw_dsoftbus/types.h"

#include <cstdio>
#include <cstring>
#include <ctime>
#include <unistd.h>

// dsoftbus APIs are declared in dsoftbus_session.h (NodeBasicInfo, etc.)
// and implemented in dsoftbus_stubs.cpp (weak symbols) or libsoftbus_client.so

// Forward declaration for GetPeerDeviceId (from dlopen shim or real libsoftbus)
extern "C" {
int GetPeerDeviceId(int sessionId, char *networkId, unsigned int len);
}

namespace rmw_dsoftbus {

// ============================================================
// Lock Ordering Documentation
// ============================================================
//
// To prevent deadlocks, locks MUST be acquired in this order:
//   1. GraphCache::mutex_ (highest priority - acquired last if needed)
//   2. peer_mutex_
//   3. seq_mutex_
//   4. liveness_mutex_ (lowest priority - can be acquired first)
//
// Rules:
// - Never hold a higher-priority lock while trying to acquire a lower one
// - Keep lock durations short
// - Release locks before calling GraphCache methods when possible
// ============================================================

// ============================================================
// Discovery Session Callbacks (SoftBus C API bridge)
// ============================================================

// Static callbacks for SoftBus ISessionListener
static int Discovery_OnSessionOpened(int sessionId, int result) {
  if (result != 0) {
    fprintf(stderr,
            "[Discovery Callback] Session open failed: id=%d result=%d\n",
            sessionId, result);
    DiscoveryManager::instance().on_discovery_session_open_failed(sessionId,
                                                                  result);
    return result;
  }

  fprintf(stderr, "[Discovery Callback] Session opened: id=%d\n", sessionId);

  // STRATEGY: Try GetPeerDeviceId first (normal path for outbound sessions)
  char peer_network_id[65] = {0};
  int ret = GetPeerDeviceId(sessionId, peer_network_id, sizeof(peer_network_id));

  if (ret == 0 && peer_network_id[0] != '\0') {
    // SUCCESS PATH: Update state machine
    std::string peer_id(peer_network_id);
    fprintf(stderr, "[Discovery Callback] Session %d opened → peer %s\n",
            sessionId, peer_id.c_str());

    // Register legacy mapping first
    DiscoveryManager::instance().on_discovery_session_opened(sessionId, peer_id);

    // Update state machine via public method (determines role internally)
    DiscoveryManager::instance().on_session_opened_statemachine(sessionId, peer_id);

  } else {
    // DEFERRED PATH: Mark as untracked, will register on first message
    fprintf(stderr,
            "[Discovery Callback] GetPeerDeviceId failed for session %d (ret=%d), "
            "deferring registration until first message\n",
            sessionId, ret);
    DiscoveryManager::instance().on_discovery_session_pending(sessionId);
  }

  return 0;  // Always return success to dsoftbus
}

static void Discovery_OnSessionClosed(int sessionId) {
  fprintf(stderr, "[Discovery Callback] Session closed: id=%d\n", sessionId);
  DiscoveryManager::instance().on_discovery_session_closed(sessionId);
}

static void Discovery_OnBytesReceived(int sessionId, const void *data,
                                      unsigned int dataLen) {
  DiscoveryManager::instance().on_discovery_bytes_received(sessionId, data,
                                                           dataLen);
}

// Global discovery listener
static ISessionListener g_discovery_listener = {
    .OnSessionOpened = Discovery_OnSessionOpened,
    .OnSessionClosed = Discovery_OnSessionClosed,
    .OnBytesReceived = Discovery_OnBytesReceived,
    .OnMessageReceived = nullptr,
    .OnStreamReceived = nullptr,
    .OnQosEvent = nullptr};

// ============================================================
// Helper: List Peers via GetAllNodeDeviceInfo
// ============================================================

static std::vector<std::string> list_peers_network_id() {
  std::vector<std::string> peers;

  NodeBasicInfo *info = nullptr;
  int32_t num = 0;
  int ret = GetAllNodeDeviceInfo(RMW_DSOFTBUS_PACKAGE_NAME, &info, &num);

  if (ret != 0 || num <= 0 || info == nullptr) {
    fprintf(
        stderr,
        "[Discovery] GetAllNodeDeviceInfo failed or no peers: ret=%d num=%d\n",
        ret, num);
    return peers;
  }

  fprintf(stderr, "[Discovery] Found %d device(s) in network:\n", num);
  for (int32_t i = 0; i < num; i++) {
    fprintf(stderr, "  [%d] %s (%s)\n", i, info[i].networkId,
            info[i].deviceName);
    peers.emplace_back(info[i].networkId);
  }

  FreeNodeInfo(info);
  return peers;
}

// ============================================================
// Singleton Instance
// ============================================================

DiscoveryManager &DiscoveryManager::instance() {
  static DiscoveryManager instance;
  return instance;
}

DiscoveryManager::DiscoveryManager() {}

DiscoveryManager::~DiscoveryManager() { shutdown(); }

// ============================================================
// Initialization / Shutdown
// ============================================================

// Generate unique instance ID at startup
static uint64_t generate_instance_id() {
  struct timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);
  uint64_t id = static_cast<uint64_t>(ts.tv_sec) * 1000000000ULL + ts.tv_nsec;
  id ^= static_cast<uint64_t>(getpid()) << 32;
  return id;
}

bool DiscoveryManager::initialize() {
  if (initialized_.load()) {
    return true;
  }

  fprintf(stderr, "[DiscoveryManager] Initializing discovery subsystem\n");
  fflush(stderr);

  // Initialize NativeToken using system API (not ioctl hack)
  fprintf(stderr, "[DiscoveryManager] Initializing NativeToken via system API...\n");
  fflush(stderr);
  bool token_ok = InitializeNativeToken("com.huawei.ros2_rmw_dsoftbus");
  if (!token_ok) {
    fprintf(stderr, "[DiscoveryManager] WARNING: NativeToken init failed, fallback to ioctl\n");
    fflush(stderr);
    (void)try_init_native_token();  // Fallback to ioctl
  } else {
    fprintf(stderr, "[DiscoveryManager] ✅ NativeToken initialized via system API\n");
    fflush(stderr);
  }

  // Generate local identity
  local_instance_id_ = generate_instance_id();

  // Get local network ID from dsoftbus
  NodeBasicInfo local_info;
  memset(&local_info, 0, sizeof(local_info));
  int ret = GetLocalNodeDeviceInfo(RMW_DSOFTBUS_PACKAGE_NAME, &local_info);
  if (ret == 0 && local_info.networkId[0] != '\0') {
    local_network_id_ = local_info.networkId;
    fprintf(stderr, "[DiscoveryManager] Got network_id from dsoftbus: %s\n",
            local_network_id_.c_str());
  } else {
    // Fallback to process ID (for stub mode or API failure)
    char buf[64];
    snprintf(buf, sizeof(buf), "local_pid_%d", getpid());
    local_network_id_ = buf;
    fprintf(stderr, "[DiscoveryManager] Using fallback network_id: %s\n",
            local_network_id_.c_str());
  }
  fflush(stderr);

  // CRITICAL: Ensure local_network_id_ is non-empty
  // Empty network_id would cause origin_len=0, which receivers will DROP
  if (local_network_id_.empty()) {
    fprintf(stderr, "[DiscoveryManager] FATAL: local_network_id is empty, "
                    "cannot initialize\n");
    fflush(stderr);
    return false;
  }

  fprintf(stderr,
          "[DiscoveryManager] Local identity: network_id=%s, instance_id=%lu\n",
          local_network_id_.c_str(), local_instance_id_);
  fflush(stderr);

  // Create discovery session server with FIXED name
  // All devices must use the same session name to connect to each other
  discovery_session_name_ = DISCOVERY_SESSION_NAME;

  fprintf(stderr, "[DiscoveryManager] Creating SessionServer: name=%s\n",
          discovery_session_name_.c_str());
  fflush(stderr);

  discovery_server_id_ = CreateSessionServer(
      RMW_DSOFTBUS_PACKAGE_NAME,
      discovery_session_name_.c_str(),
      &g_discovery_listener);

  if (discovery_server_id_ < 0) {
    fprintf(stderr, "[DiscoveryManager] CreateSessionServer failed: %d\n",
            discovery_server_id_);
    fflush(stderr);
    if (discovery_server_id_ == SOFTBUS_ACCESS_TOKEN_DENIED ||
        discovery_server_id_ == SOFTBUS_PERMISSION_DENIED ||
        discovery_server_id_ == SOFTBUS_ERR) {
      fprintf(stderr,
              "[DiscoveryManager] Hint: need AccessToken permission "
              "(ohos.permission.DISTRIBUTED_DATASYNC); "
              "native ELF must set NativeToken (/dev/access_token_id) or run "
              "via HAP '%s'\n",
              RMW_DSOFTBUS_PACKAGE_NAME);
      fflush(stderr);
    }
    return false;
  }
  fprintf(stderr, "[DiscoveryManager] SessionServer created: id=%d name=%s\n",
          discovery_server_id_, DISCOVERY_SESSION_NAME);
  fflush(stderr);

  // Start heartbeat thread (which will also handle peer connection attempts)
  running_.store(true);
  heartbeat_thread_ =
      std::thread(&DiscoveryManager::heartbeat_thread_func, this);

  initialized_.store(true);

  // Print initialization summary
  fprintf(stderr,
          "[DiscoveryManager] Init complete: local=%s server_id=%d peers=%u "
          "shim=loaded\n",
          local_network_id_.c_str(), discovery_server_id_,
          stats_.peer_sessions_count.load());
  fflush(stderr);

  return true;
}

// ============================================================
// Peer Connection
// ============================================================

void DiscoveryManager::connect_all_peers_once() {
  fprintf(stderr, "[DiscoveryManager] Connecting to peers (leader election)...\n");
  fprintf(stderr, "[DiscoveryManager] Local network_id: %s\n",
          local_network_id_.c_str());

  std::vector<std::string> peers = list_peers_network_id();

  if (peers.empty()) {
    fprintf(stderr, "[DiscoveryManager] No peers found in network\n");
    return;
  }

  int connected_count = 0;
  int skipped_server = 0;
  for (const auto &peer_id : peers) {
    // Skip self
    if (peer_id == local_network_id_) {
      continue;
    }

    // ============================================================
    // Leader Election: Avoid bidirectional connection conflicts
    // ============================================================
    // Rule: Only the device with smaller network_id initiates connection.
    // - If local < peer: I'm the client, initiate OpenSession
    // - If local > peer: I'm the server, wait for peer to connect
    //
    // This ensures exactly ONE connection between any two devices,
    // avoiding SoftBus's duplicate session detection and closure.
    // ============================================================
    if (local_network_id_ > peer_id) {
      fprintf(stderr,
              "[DiscoveryManager] SKIP %s (I'm server, local > peer)\n",
              peer_id.c_str());
      skipped_server++;
      continue;
    }

    fprintf(stderr,
            "[DiscoveryManager] CONNECT to %s (I'm client, local < peer)\n",
            peer_id.c_str());

    // Check if already connected or already opening
    {
      std::lock_guard<std::mutex> lock(peer_mutex_);
      if (peer_sessions_.find(peer_id) != peer_sessions_.end() ||
          opening_peer_sessions_.find(peer_id) != opening_peer_sessions_.end()) {
        fprintf(stderr, "[DiscoveryManager] Already connected/opening to %s\n",
                peer_id.c_str());
        continue;
      }
    }

    // Open session to peer
    SessionAttribute attr;
    memset(&attr, 0, sizeof(attr));
    attr.dataType = TYPE_BYTES;

    int session_id =
        OpenSession(discovery_session_name_.c_str(), // mySessionName
                    discovery_session_name_.c_str(), // peerSessionName (symmetric)
                    peer_id.c_str(),                 // peerNetworkId
                    "",                              // groupId (empty for discovery)
                    &attr);

    if (session_id < 0) {
      fprintf(stderr, "[DiscoveryManager] OpenSession to %s failed: %d\n",
              peer_id.c_str(), session_id);
      continue;
    }

    fprintf(stderr,
            "[DiscoveryManager] OpenSession to %s succeeded: session_id=%d\n",
            peer_id.c_str(), session_id);

    // Create SessionContext for Dialer role (state machine v1)
    {
      std::lock_guard<std::mutex> lock(sessions_mutex_);
      // Use piecewise_construct to avoid move/copy
      sessions_.emplace(std::piecewise_construct,
                       std::forward_as_tuple(session_id),
                       std::forward_as_tuple());
      auto& ctx = sessions_.at(session_id);
      ctx.state = SessionState::PENDING;
      ctx.peer_network_id = peer_id;
      ctx.is_dialer = true;
      fprintf(stderr, "[STATE] Session %d created: PENDING (Dialer)\n", session_id);
    }

    // Track as "opening" until OnSessionOpened confirms usability.
    {
      std::lock_guard<std::mutex> lock(peer_mutex_);
      opening_peer_sessions_[peer_id] = session_id;
      opening_session_to_peer_[session_id] = peer_id;
    }
    connected_count++;
  }

  fprintf(stderr,
          "[DiscoveryManager] Leader election result: connected=%d, skipped(server)=%d\n",
          connected_count, skipped_server);
}

void DiscoveryManager::shutdown() {
  if (!initialized_.load()) {
    return;
  }

  fprintf(stderr, "[DiscoveryManager] Shutting down\n");

  // Stop heartbeat thread
  running_.store(false);
  if (heartbeat_thread_.joinable()) {
    heartbeat_thread_.join();
  }

  // Close all peer sessions
  {
    std::lock_guard<std::mutex> lock(peer_mutex_);
    for (const auto &pair : peer_sessions_) {
      CloseSession(pair.second);
    }
    for (const auto &pair : opening_peer_sessions_) {
      CloseSession(pair.second);
    }
    peer_sessions_.clear();
    session_to_peer_.clear();
    opening_peer_sessions_.clear();
    opening_session_to_peer_.clear();
    stats_.peer_sessions_count = 0;
  }

  // Remove discovery session server
  if (discovery_server_id_ >= 0) {
    int ret =
        RemoveSessionServer(RMW_DSOFTBUS_PACKAGE_NAME, discovery_session_name_.c_str());
    if (ret != 0) {
      fprintf(stderr, "[DiscoveryManager] RemoveSessionServer failed: %d\n",
              ret);
    } else {
      fprintf(stderr, "[DiscoveryManager] SessionServer removed\n");
    }
    discovery_server_id_ = -1;
  }

  // Clear deduplication state
  {
    std::lock_guard<std::mutex> lock(seq_mutex_);
    last_seq_seen_.clear();
    known_instance_ids_.clear();
  }

  // Clear liveliness state
  {
    std::lock_guard<std::mutex> lock(liveness_mutex_);
    remote_node_liveness_.clear();
  }

  // Clear untracked sessions
  {
    std::lock_guard<std::mutex> lock(untracked_mutex_);
    untracked_sessions_.clear();
  }

  initialized_.store(false);
  fprintf(stderr, "[DiscoveryManager] Shutdown complete\n");
}

// ============================================================
// Broadcast APIs
// ============================================================

void DiscoveryManager::broadcast_node_added(const GraphNodeInfo &node) {
  if (!initialized_.load())
    return;

  auto msg = build_node_add_message(node);
  if (msg.empty()) {
    fprintf(stderr, "[DiscoveryManager] broadcast_node_added: build failed, "
                    "not broadcasting\n");
    return;
  }
  broadcast_to_all_peers(msg);
}

void DiscoveryManager::broadcast_node_removed(const std::string &node_key) {
  if (!initialized_.load())
    return;

  auto msg = build_node_remove_message(node_key);
  if (msg.empty()) {
    fprintf(stderr, "[DiscoveryManager] broadcast_node_removed: build failed, "
                    "not broadcasting\n");
    return;
  }
  broadcast_to_all_peers(msg);
}

void DiscoveryManager::broadcast_endpoint_added(
    const GraphEndpointInfo &endpoint) {
  if (!initialized_.load())
    return;

  auto msg = build_endpoint_add_message(endpoint);
  if (msg.empty()) {
    fprintf(stderr, "[DiscoveryManager] broadcast_endpoint_added: build "
                    "failed, not broadcasting\n");
    return;
  }
  broadcast_to_all_peers(msg);
}

void DiscoveryManager::broadcast_endpoint_removed(const rmw_gid_t &gid) {
  if (!initialized_.load())
    return;

  auto msg = build_endpoint_remove_message(gid);
  broadcast_to_all_peers(msg);
}

// ============================================================
// Session Callbacks
// ============================================================

void DiscoveryManager::on_discovery_session_opened(
    int sessionId, const std::string &peer_network_id) {
  fprintf(stderr, "[DiscoveryManager] Session opened: id=%d, peer=%s\n",
          sessionId, peer_network_id.c_str());

  {
    std::lock_guard<std::mutex> lock(peer_mutex_);
    auto opening_it = opening_session_to_peer_.find(sessionId);
    if (opening_it != opening_session_to_peer_.end()) {
      opening_peer_sessions_.erase(opening_it->second);
      opening_session_to_peer_.erase(opening_it);
    }
    peer_sessions_[peer_network_id] = sessionId;
    session_to_peer_[sessionId] = peer_network_id;
    stats_.peer_sessions_count = static_cast<uint32_t>(peer_sessions_.size());
  }

  // NOTE: QUERY is NOT sent here - it's sent in handle_hello() after handshake
  // The handshake protocol is: Server sends HELLO → Client sends HELLO_ACK + QUERY
}

void DiscoveryManager::on_discovery_session_open_failed(int sessionId,
                                                       int result) {
  // Remove from untracked sessions (if present)
  {
    std::lock_guard<std::mutex> lock(untracked_mutex_);
    untracked_sessions_.erase(sessionId);
  }

  // Remove from state machine (if present)
  {
    std::lock_guard<std::mutex> lock(sessions_mutex_);
    sessions_.erase(sessionId);
  }

  // Clear legacy/opening bookkeeping
  std::string peer_id;
  {
    std::lock_guard<std::mutex> lock(peer_mutex_);

    auto opening_it = opening_session_to_peer_.find(sessionId);
    if (opening_it != opening_session_to_peer_.end()) {
      peer_id = opening_it->second;
      opening_peer_sessions_.erase(peer_id);
      opening_session_to_peer_.erase(opening_it);
    }

    auto it = session_to_peer_.find(sessionId);
    if (it != session_to_peer_.end()) {
      peer_sessions_.erase(it->second);
      session_to_peer_.erase(it);
      stats_.peer_sessions_count = static_cast<uint32_t>(peer_sessions_.size());
    }
  }

  if (!peer_id.empty()) {
    fprintf(stderr,
            "[DiscoveryManager] Session open failed: id=%d peer=%s result=%d\n",
            sessionId, peer_id.c_str(), result);
  }
}

void DiscoveryManager::on_discovery_session_pending(int sessionId) {
  fprintf(stderr, "[DiscoveryManager] Session %d pending (awaiting peer identification)\n",
          sessionId);

  std::lock_guard<std::mutex> lock(untracked_mutex_);
  untracked_sessions_.insert(sessionId);
}

void DiscoveryManager::on_session_opened_statemachine(int sessionId,
                                                      const std::string& peer_network_id) {
  bool should_send_hello = false;

  {
    std::lock_guard<std::mutex> lock(sessions_mutex_);
    auto it = sessions_.find(sessionId);
    bool is_dialer = (it != sessions_.end());  // Dialer = ctx already exists (created in OpenSession)

    if (!is_dialer) {
      // Acceptor (Server): create new context
      sessions_.emplace(std::piecewise_construct,
                       std::forward_as_tuple(sessionId),
                       std::forward_as_tuple());
      auto& ctx = sessions_.at(sessionId);
      ctx.state = SessionState::OPENED;
      ctx.peer_network_id = peer_network_id;
      ctx.is_dialer = false;
      fprintf(stderr, "[STATE] Session %d created: OPENED (Acceptor)\n", sessionId);
      fflush(stderr);

      should_send_hello = true;  // Server sends HELLO
    } else {
      // Dialer (Client): update existing context
      it->second.peer_network_id = peer_network_id;
      it->second.state = SessionState::OPENED;  // PENDING → OPENED
      fprintf(stderr, "[STATE] Session %d: PENDING → OPENED (Dialer)\n", sessionId);
      fflush(stderr);
      // Client does NOT send, waits for HELLO
    }
  }  // Lock released here

  // Send HELLO outside lock (avoids deadlock with send_to_peer)
  if (should_send_hello) {
    send_hello(sessionId);
  }
}

void DiscoveryManager::on_discovery_session_closed(int sessionId) {
  std::string peer_id;
  {
    std::lock_guard<std::mutex> lock(peer_mutex_);
    auto it = session_to_peer_.find(sessionId);
    if (it != session_to_peer_.end()) {
      peer_id = it->second;
      peer_sessions_.erase(peer_id);
      session_to_peer_.erase(it);
    } else {
      // Session might have failed before we registered legacy mapping.
      auto opening_it = opening_session_to_peer_.find(sessionId);
      if (opening_it != opening_session_to_peer_.end()) {
        peer_id = opening_it->second;
        opening_peer_sessions_.erase(peer_id);
        opening_session_to_peer_.erase(opening_it);
      }
    }
    stats_.peer_sessions_count = static_cast<uint32_t>(peer_sessions_.size());
  }

  // Remove from untracked sessions (if present)
  {
    std::lock_guard<std::mutex> lock(untracked_mutex_);
    untracked_sessions_.erase(sessionId);
  }

  if (!peer_id.empty()) {
    fprintf(stderr, "[DiscoveryManager] Session closed: id=%d, peer=%s\n",
            sessionId, peer_id.c_str());
  } else {
    fprintf(stderr, "[DiscoveryManager] Session closed: id=%d (was untracked or unknown)\n",
            sessionId);
  }
}

void DiscoveryManager::on_discovery_bytes_received(int sessionId,
                                                   const void *data,
                                                   unsigned int len) {
  // Observability: count all received messages
  stats_.rx_total++;

  DiscoveryHeader header;
  const uint8_t *payload = nullptr;

  // Parse and validate
  if (!parse_and_validate(data, len, &header, &payload)) {
    stats_.drop_invalid++;
    return; // DROP: invalid message
  }

  // Check if session is pending registration (deferred from OnSessionOpened callback)
  std::string deferred_peer_id;
  {
    std::lock_guard<std::mutex> lock(untracked_mutex_);
    if (untracked_sessions_.count(sessionId) > 0) {
      // Extract peer network_id from validated message header
      deferred_peer_id.assign(header.origin_network_id, header.origin_len);

      fprintf(stderr,
              "[DiscoveryManager] Registering untracked session %d → peer %s (from header)\n",
              sessionId, deferred_peer_id.c_str());

      // Register session (same as on_discovery_session_opened)
      {
        std::lock_guard<std::mutex> peer_lock(peer_mutex_);
        auto opening_it = opening_session_to_peer_.find(sessionId);
        if (opening_it != opening_session_to_peer_.end()) {
          opening_peer_sessions_.erase(opening_it->second);
          opening_session_to_peer_.erase(opening_it);
        }
        peer_sessions_[deferred_peer_id] = sessionId;
        session_to_peer_[sessionId] = deferred_peer_id;
        stats_.peer_sessions_count = static_cast<uint32_t>(peer_sessions_.size());
      }

      untracked_sessions_.erase(sessionId);
    }
  }
  // If we just registered a deferred session, update state machine (outside locks)
  if (!deferred_peer_id.empty()) {
    on_session_opened_statemachine(sessionId, deferred_peer_id);
    // NOTE: QUERY will be sent via handle_hello() for Client, or not at all for Server
  }

  // Get sender's network ID
  std::string sender_id = get_peer_network_id(sessionId);
  if (sender_id.empty()) {
    fprintf(stderr, "[DiscoveryManager] DROP: unknown session %d\n", sessionId);
    stats_.drop_invalid++;
    return;
  }

  // Check origin validity (anti-flooding)
  if (!check_origin_valid(header, sender_id)) {
    stats_.drop_forwarded++;
    return; // DROP: forwarded or self-echo
  }

  // Check sequence deduplication
  if (!check_seq_dedup(header)) {
    stats_.drop_dup++;
    return; // DROP: duplicate
  }

  // Process message
  process_message(header, payload, sender_id);
}

void DiscoveryManager::on_peer_online(const char *networkId) {
  if (!initialized_.load()) {
    return;
  }

  if (networkId == nullptr || networkId[0] == '\0') {
    fprintf(stderr, "[DiscoveryManager] Peer online: empty networkId, ignore\n");
    return;
  }

  std::string peer_id(networkId);

  // Skip self
  if (peer_id == local_network_id_) {
    fprintf(stderr, "[DiscoveryManager] Peer online: skip self (%s)\n",
            peer_id.c_str());
    return;
  }

  // ============================================================
  // Leader Election: Same rule as connect_all_peers_once()
  // ============================================================
  // Only the device with smaller network_id initiates connection.
  // If local > peer, we are the server - peer will connect to us.
  // ============================================================
  if (local_network_id_ > peer_id) {
    fprintf(stderr,
            "[DiscoveryManager] Peer online: SKIP %s (I'm server, local > peer)\n",
            peer_id.c_str());
    return;
  }

  fprintf(stderr,
          "[DiscoveryManager] Peer online: CONNECT to %s (I'm client, local < peer)\n",
          peer_id.c_str());

  // Idempotency: if already connected/opening, do nothing
  {
    std::lock_guard<std::mutex> lock(peer_mutex_);
    if (peer_sessions_.find(peer_id) != peer_sessions_.end() ||
        opening_peer_sessions_.find(peer_id) != opening_peer_sessions_.end()) {
      fprintf(stderr,
              "[DiscoveryManager] Peer online: already connected/opening (%s)\n",
              peer_id.c_str());
      return;
    }
  }

  // Open discovery session to this peer (same pattern as connect_all_peers_once)
  SessionAttribute attr;
  memset(&attr, 0, sizeof(attr));
  attr.dataType = TYPE_BYTES;

  int session_id =
      OpenSession(discovery_session_name_.c_str(), // mySessionName
                  discovery_session_name_.c_str(), // peerSessionName (symmetric)
                  peer_id.c_str(),                 // peerNetworkId
                  "",                              // groupId
                  &attr);

  if (session_id < 0) {
    fprintf(stderr, "[DiscoveryManager] Peer online: OpenSession to %s failed: %d\n",
            peer_id.c_str(), session_id);
    // Minimal correct behavior: no retry here (defer to stability phase)
    return;
  }

  fprintf(stderr,
          "[DiscoveryManager] Peer online: OpenSession to %s ok: session_id=%d\n",
          peer_id.c_str(), session_id);

  // Create SessionContext for Dialer role (state machine v1)
  {
    std::lock_guard<std::mutex> lock(sessions_mutex_);
    sessions_.emplace(std::piecewise_construct,
                      std::forward_as_tuple(session_id),
                      std::forward_as_tuple());
    auto &ctx = sessions_.at(session_id);
    ctx.state = SessionState::PENDING;
    ctx.peer_network_id = peer_id;
    ctx.is_dialer = true;
    fprintf(stderr, "[STATE] Session %d created: PENDING (Dialer)\n", session_id);
    fflush(stderr);
  }

  // Track as "opening" until OnSessionOpened confirms usability.
  {
    std::lock_guard<std::mutex> lock(peer_mutex_);
    opening_peer_sessions_[peer_id] = session_id;
    opening_session_to_peer_[session_id] = peer_id;
  }
}

void DiscoveryManager::on_peer_offline(const char *networkId) {
  if (networkId == nullptr || networkId[0] == '\0') {
    fprintf(stderr, "[DiscoveryManager] Peer offline: empty networkId, ignore\n");
    return;
  }

  std::string peer_id(networkId);
  fprintf(stderr, "[DiscoveryManager] Peer offline: %s\n", peer_id.c_str());

  // 1) Close and remove session (best-effort)
  int session_id = -1;
  int opening_session_id = -1;
  {
    std::lock_guard<std::mutex> lock(peer_mutex_);
    auto it = peer_sessions_.find(peer_id);
    if (it != peer_sessions_.end()) {
      session_id = it->second;
      peer_sessions_.erase(it);
      session_to_peer_.erase(session_id);
      stats_.peer_sessions_count = static_cast<uint32_t>(peer_sessions_.size());
    }
    auto opening_it = opening_peer_sessions_.find(peer_id);
    if (opening_it != opening_peer_sessions_.end()) {
      opening_session_id = opening_it->second;
      opening_peer_sessions_.erase(opening_it);
      opening_session_to_peer_.erase(opening_session_id);
    }
  }
  if (session_id >= 0) {
    CloseSession(session_id);
    fprintf(stderr, "[DiscoveryManager] Closed session %d for peer %s\n",
            session_id, peer_id.c_str());
  }
  if (opening_session_id >= 0) {
    CloseSession(opening_session_id);
    fprintf(stderr, "[DiscoveryManager] Closed opening session %d for peer %s\n",
            opening_session_id, peer_id.c_str());
  }

  // 2) Clear dedup state for this peer
  {
    std::lock_guard<std::mutex> lock(seq_mutex_);
    known_instance_ids_.erase(peer_id);
    for (auto it = last_seq_seen_.begin(); it != last_seq_seen_.end();) {
      if (it->first.network_id == peer_id) {
        it = last_seq_seen_.erase(it);
      } else {
        ++it;
      }
    }
  }

  // 3) Clear liveliness
  {
    std::lock_guard<std::mutex> lock(liveness_mutex_);
    remote_node_liveness_.erase(peer_id);
  }

  // 4) Remove all graph entities from this peer (will trigger graph change if changed)
  GraphCache::instance().remove_all_from_network_id(peer_id);
}

// ============================================================
// Message Building
// ============================================================

std::vector<uint8_t> DiscoveryManager::build_header(DiscoveryMessageType type,
                                                    uint32_t payload_len) {
  std::vector<uint8_t> header(DISCOVERY_HEADER_SIZE, 0);
  uint8_t *p = header.data();

  // Magic (Little-Endian)
  p[0] = DISCOVERY_MAGIC & 0xFF;
  p[1] = (DISCOVERY_MAGIC >> 8) & 0xFF;
  p += 2;

  // Version
  *p++ = DISCOVERY_VERSION;

  // Message type
  *p++ = static_cast<uint8_t>(type);

  // Payload length (Little-Endian)
  p[0] = payload_len & 0xFF;
  p[1] = (payload_len >> 8) & 0xFF;
  p[2] = (payload_len >> 16) & 0xFF;
  p[3] = (payload_len >> 24) & 0xFF;
  p += 4;

  // Seq (Little-Endian)
  uint64_t seq = get_next_seq();
  for (int i = 0; i < 8; i++) {
    p[i] = (seq >> (i * 8)) & 0xFF;
  }
  p += 8;

  // Timestamp (Little-Endian)
  uint64_t ts = get_timestamp_ns();
  for (int i = 0; i < 8; i++) {
    p[i] = (ts >> (i * 8)) & 0xFF;
  }
  p += 8;

  // Origin instance ID (Little-Endian)
  for (int i = 0; i < 8; i++) {
    p[i] = (local_instance_id_ >> (i * 8)) & 0xFF;
  }
  p += 8;

  // Origin length
  uint8_t origin_len =
      static_cast<uint8_t>(std::min(local_network_id_.size(), size_t(64)));
  *p++ = origin_len;

  // Origin network ID
  memcpy(p, local_network_id_.c_str(), origin_len);

  return header;
}

std::vector<uint8_t> DiscoveryManager::build_query_message() {
  return build_header(DiscoveryMessageType::QUERY, 0);
}

std::vector<uint8_t> DiscoveryManager::build_hello_message() {
  return build_header(DiscoveryMessageType::HELLO, 0);
}

std::vector<uint8_t> DiscoveryManager::build_hello_ack_message() {
  return build_header(DiscoveryMessageType::HELLO_ACK, 0);
}

std::vector<uint8_t> DiscoveryManager::build_snapshot_message() {
  // Get local-only snapshot
  GraphSnapshot snap = GraphCache::instance().snapshot_local_only();

  // FAIL-FAST: Reject if counts exceed uint16_t (protocol limit)
  if (snap.nodes.size() > UINT16_MAX) {
    fprintf(stderr,
            "[DiscoveryManager] REJECT: node count %zu exceeds UINT16_MAX, "
            "cannot build SNAPSHOT\n",
            snap.nodes.size());
    return {}; // Empty = failure
  }
  if (snap.endpoints.size() > UINT16_MAX) {
    fprintf(stderr,
            "[DiscoveryManager] REJECT: endpoint count %zu exceeds UINT16_MAX, "
            "cannot build SNAPSHOT\n",
            snap.endpoints.size());
    return {};
  }

  // Build payload
  std::vector<uint8_t> payload;

  // Node count (2 bytes)
  uint16_t node_count = static_cast<uint16_t>(snap.nodes.size());
  payload.push_back(node_count & 0xFF);
  payload.push_back((node_count >> 8) & 0xFF);

  // Endpoint count (2 bytes)
  uint16_t endpoint_count = static_cast<uint16_t>(snap.endpoints.size());
  payload.push_back(endpoint_count & 0xFF);
  payload.push_back((endpoint_count >> 8) & 0xFF);

  // Timestamp (4 bytes)
  uint32_t ts_sec = static_cast<uint32_t>(snap.timestamp_ns / 1000000000ULL);
  payload.push_back(ts_sec & 0xFF);
  payload.push_back((ts_sec >> 8) & 0xFF);
  payload.push_back((ts_sec >> 16) & 0xFF);
  payload.push_back((ts_sec >> 24) & 0xFF);

  // Serialize nodes
  for (const auto &node : snap.nodes) {
    // namespace
    uint8_t ns_len =
        static_cast<uint8_t>(std::min(node.node_namespace.size(), size_t(255)));
    payload.push_back(ns_len);
    payload.insert(payload.end(), node.node_namespace.begin(),
                   node.node_namespace.begin() + ns_len);

    // name
    uint8_t name_len =
        static_cast<uint8_t>(std::min(node.node_name.size(), size_t(255)));
    payload.push_back(name_len);
    payload.insert(payload.end(), node.node_name.begin(),
                   node.node_name.begin() + name_len);

    // enclave
    uint8_t enc_len =
        static_cast<uint8_t>(std::min(node.enclave.size(), size_t(255)));
    payload.push_back(enc_len);
    payload.insert(payload.end(), node.enclave.begin(),
                   node.enclave.begin() + enc_len);
  }

  // Serialize endpoints
  for (const auto &ep : snap.endpoints) {
    // type
    payload.push_back(static_cast<uint8_t>(ep.type));

    // topic name
    uint8_t topic_len =
        static_cast<uint8_t>(std::min(ep.topic_name.size(), size_t(255)));
    payload.push_back(topic_len);
    payload.insert(payload.end(), ep.topic_name.begin(),
                   ep.topic_name.begin() + topic_len);

    // type name
    uint8_t type_len =
        static_cast<uint8_t>(std::min(ep.type_name.size(), size_t(255)));
    payload.push_back(type_len);
    payload.insert(payload.end(), ep.type_name.begin(),
                   ep.type_name.begin() + type_len);

    // gid (24 bytes)
    payload.insert(payload.end(), ep.gid.data,
                   ep.gid.data + RMW_GID_STORAGE_SIZE);

    // node name
    uint8_t node_name_len =
        static_cast<uint8_t>(std::min(ep.node_name.size(), size_t(255)));
    payload.push_back(node_name_len);
    payload.insert(payload.end(), ep.node_name.begin(),
                   ep.node_name.begin() + node_name_len);

    // node namespace
    uint8_t node_ns_len =
        static_cast<uint8_t>(std::min(ep.node_namespace.size(), size_t(255)));
    payload.push_back(node_ns_len);
    payload.insert(payload.end(), ep.node_namespace.begin(),
                   ep.node_namespace.begin() + node_ns_len);
  }

  // Build header
  auto header = build_header(DiscoveryMessageType::SNAPSHOT,
                             static_cast<uint32_t>(payload.size()));

  // Combine
  header.insert(header.end(), payload.begin(), payload.end());
  return header;
}

std::vector<uint8_t> DiscoveryManager::build_heartbeat_message() {
  // Get local nodes
  auto local_nodes = GraphCache::instance().get_local_nodes();

  // Build payload
  std::vector<uint8_t> payload;

  // Node count (2 bytes)
  uint16_t node_count = static_cast<uint16_t>(local_nodes.size());
  payload.push_back(node_count & 0xFF);
  payload.push_back((node_count >> 8) & 0xFF);

  // Serialize node keys (namespace + name tuples)
  for (const auto &pair : local_nodes) {
    const GraphNodeInfo &node = pair.second;

    // namespace
    uint8_t ns_len =
        static_cast<uint8_t>(std::min(node.node_namespace.size(), size_t(255)));
    payload.push_back(ns_len);
    payload.insert(payload.end(), node.node_namespace.begin(),
                   node.node_namespace.begin() + ns_len);

    // name
    uint8_t name_len =
        static_cast<uint8_t>(std::min(node.node_name.size(), size_t(255)));
    payload.push_back(name_len);
    payload.insert(payload.end(), node.node_name.begin(),
                   node.node_name.begin() + name_len);
  }

  // Build header
  auto header = build_header(DiscoveryMessageType::HEARTBEAT,
                             static_cast<uint32_t>(payload.size()));

  // Combine
  header.insert(header.end(), payload.begin(), payload.end());
  return header;
}

std::vector<uint8_t>
DiscoveryManager::build_node_add_message(const GraphNodeInfo &node) {
  // FAIL-FAST: Reject strings exceeding 255 bytes (protocol limit)
  if (node.node_namespace.size() > 255) {
    fprintf(stderr,
            "[DiscoveryManager] REJECT: node_namespace too long (%zu > 255)\n",
            node.node_namespace.size());
    return {};
  }
  if (node.node_name.size() > 255) {
    fprintf(stderr,
            "[DiscoveryManager] REJECT: node_name too long (%zu > 255)\n",
            node.node_name.size());
    return {};
  }
  if (node.enclave.size() > 255) {
    fprintf(stderr, "[DiscoveryManager] REJECT: enclave too long (%zu > 255)\n",
            node.enclave.size());
    return {};
  }

  std::vector<uint8_t> payload;

  // namespace
  uint8_t ns_len = static_cast<uint8_t>(node.node_namespace.size());
  payload.push_back(ns_len);
  payload.insert(payload.end(), node.node_namespace.begin(),
                 node.node_namespace.end());

  // name
  uint8_t name_len = static_cast<uint8_t>(node.node_name.size());
  payload.push_back(name_len);
  payload.insert(payload.end(), node.node_name.begin(), node.node_name.end());

  // enclave
  uint8_t enc_len = static_cast<uint8_t>(node.enclave.size());
  payload.push_back(enc_len);
  payload.insert(payload.end(), node.enclave.begin(), node.enclave.end());

  auto header = build_header(DiscoveryMessageType::NODE_ADD,
                             static_cast<uint32_t>(payload.size()));
  header.insert(header.end(), payload.begin(), payload.end());
  return header;
}

std::vector<uint8_t>
DiscoveryManager::build_node_remove_message(const std::string &node_key) {
  // Parse node_key to get namespace and name
  // Format: "{namespace}:{name}"
  size_t colon_pos = node_key.rfind(':');
  std::string ns =
      (colon_pos != std::string::npos) ? node_key.substr(0, colon_pos) : "/";
  std::string name = (colon_pos != std::string::npos)
                         ? node_key.substr(colon_pos + 1)
                         : node_key;

  // FAIL-FAST: Reject strings exceeding 255 bytes
  if (ns.size() > 255 || name.size() > 255) {
    fprintf(stderr,
            "[DiscoveryManager] REJECT: node_key components too long (ns=%zu, "
            "name=%zu)\n",
            ns.size(), name.size());
    return {};
  }

  std::vector<uint8_t> payload;

  // namespace
  uint8_t ns_len = static_cast<uint8_t>(ns.size());
  payload.push_back(ns_len);
  payload.insert(payload.end(), ns.begin(), ns.end());

  // name
  uint8_t name_len = static_cast<uint8_t>(name.size());
  payload.push_back(name_len);
  payload.insert(payload.end(), name.begin(), name.end());

  auto header = build_header(DiscoveryMessageType::NODE_REMOVE,
                             static_cast<uint32_t>(payload.size()));
  header.insert(header.end(), payload.begin(), payload.end());
  return header;
}

std::vector<uint8_t> DiscoveryManager::build_endpoint_add_message(
    const GraphEndpointInfo &endpoint) {
  // FAIL-FAST: Reject strings exceeding 255 bytes (protocol limit)
  if (endpoint.topic_name.size() > 255) {
    fprintf(stderr,
            "[DiscoveryManager] REJECT: topic_name too long (%zu > 255)\n",
            endpoint.topic_name.size());
    return {}; // Empty = failure
  }
  if (endpoint.type_name.size() > 255) {
    fprintf(stderr,
            "[DiscoveryManager] REJECT: type_name too long (%zu > 255)\n",
            endpoint.type_name.size());
    return {};
  }
  if (endpoint.node_name.size() > 255) {
    fprintf(stderr,
            "[DiscoveryManager] REJECT: node_name too long (%zu > 255)\n",
            endpoint.node_name.size());
    return {};
  }
  if (endpoint.node_namespace.size() > 255) {
    fprintf(stderr,
            "[DiscoveryManager] REJECT: node_namespace too long (%zu > 255)\n",
            endpoint.node_namespace.size());
    return {};
  }

  std::vector<uint8_t> payload;

  // type
  payload.push_back(static_cast<uint8_t>(endpoint.type));

  // topic name
  uint8_t topic_len = static_cast<uint8_t>(endpoint.topic_name.size());
  payload.push_back(topic_len);
  payload.insert(payload.end(), endpoint.topic_name.begin(),
                 endpoint.topic_name.end());

  // type name
  uint8_t type_len = static_cast<uint8_t>(endpoint.type_name.size());
  payload.push_back(type_len);
  payload.insert(payload.end(), endpoint.type_name.begin(),
                 endpoint.type_name.end());

  // gid
  payload.insert(payload.end(), endpoint.gid.data,
                 endpoint.gid.data + RMW_GID_STORAGE_SIZE);

  // node name
  uint8_t node_name_len = static_cast<uint8_t>(endpoint.node_name.size());
  payload.push_back(node_name_len);
  payload.insert(payload.end(), endpoint.node_name.begin(),
                 endpoint.node_name.end());

  // node namespace
  uint8_t node_ns_len = static_cast<uint8_t>(endpoint.node_namespace.size());
  payload.push_back(node_ns_len);
  payload.insert(payload.end(), endpoint.node_namespace.begin(),
                 endpoint.node_namespace.end());

  auto header = build_header(DiscoveryMessageType::ENDPOINT_ADD,
                             static_cast<uint32_t>(payload.size()));
  header.insert(header.end(), payload.begin(), payload.end());
  return header;
}

std::vector<uint8_t>
DiscoveryManager::build_endpoint_remove_message(const rmw_gid_t &gid) {
  std::vector<uint8_t> payload;

  // gid only (24 bytes)
  payload.insert(payload.end(), gid.data, gid.data + RMW_GID_STORAGE_SIZE);

  auto header = build_header(DiscoveryMessageType::ENDPOINT_REMOVE,
                             static_cast<uint32_t>(payload.size()));
  header.insert(header.end(), payload.begin(), payload.end());
  return header;
}

// ============================================================
// Message Parsing
// ============================================================

bool DiscoveryManager::parse_and_validate(const void *data, size_t len,
                                          DiscoveryHeader *header,
                                          const uint8_t **payload_out) {
  const uint8_t *p = static_cast<const uint8_t *>(data);

  // Check minimum length
  if (len < DISCOVERY_HEADER_SIZE) {
    fprintf(stderr, "[DiscoveryManager] DROP: len %zu < HEADER_SIZE %zu\n", len,
            DISCOVERY_HEADER_SIZE);
    return false;
  }

  // Parse header (Little-Endian)
  header->magic = p[0] | (p[1] << 8);
  if (header->magic != DISCOVERY_MAGIC) {
    fprintf(stderr, "[DiscoveryManager] DROP: invalid magic 0x%04X\n",
            header->magic);
    return false;
  }

  header->version = p[2];
  header->msg_type = p[3];

  // Validate msg_type range [0x01, 0x09]
  // 0x01-0x07: QUERY, SNAPSHOT, NODE_ADD/REMOVE, ENDPOINT_ADD/REMOVE, HEARTBEAT
  // 0x08-0x09: HELLO, HELLO_ACK (session handshake)
  if (header->msg_type < 0x01 || header->msg_type > 0x09) {
    fprintf(
        stderr,
        "[DiscoveryManager] DROP: invalid msg_type 0x%02X (valid: 0x01-0x09)\n",
        header->msg_type);
    return false;
  }

  header->payload_len = p[4] | (p[5] << 8) | (p[6] << 16) | (p[7] << 24);

  // Check payload limit
  if (header->payload_len > MAX_DISCOVERY_PAYLOAD) {
    fprintf(stderr, "[DiscoveryManager] DROP: payload_len %u > MAX %zu\n",
            header->payload_len, MAX_DISCOVERY_PAYLOAD);
    return false;
  }

  // Strict length match
  if (len != DISCOVERY_HEADER_SIZE + header->payload_len) {
    fprintf(stderr,
            "[DiscoveryManager] DROP: len %zu != HEADER + payload (%zu + %u)\n",
            len, DISCOVERY_HEADER_SIZE, header->payload_len);
    return false;
  }

  // Parse seq
  header->seq = 0;
  for (int i = 0; i < 8; i++) {
    header->seq |= static_cast<uint64_t>(p[8 + i]) << (i * 8);
  }

  // Parse ts_ns
  header->ts_ns = 0;
  for (int i = 0; i < 8; i++) {
    header->ts_ns |= static_cast<uint64_t>(p[16 + i]) << (i * 8);
  }

  // Parse origin_instance_id
  header->origin_instance_id = 0;
  for (int i = 0; i < 8; i++) {
    header->origin_instance_id |= static_cast<uint64_t>(p[24 + i]) << (i * 8);
  }

  // Parse origin_len
  header->origin_len = p[32];
  if (header->origin_len == 0 || header->origin_len > 64) {
    fprintf(stderr, "[DiscoveryManager] DROP: invalid origin_len %u\n",
            header->origin_len);
    return false;
  }

  // Parse origin_network_id
  memcpy(header->origin_network_id, p + 33, header->origin_len);

  *payload_out = p + DISCOVERY_HEADER_SIZE;
  return true;
}

bool DiscoveryManager::parse_node_entry(const uint8_t *data, size_t len,
                                        GraphNodeInfo *node, size_t *consumed) {
  const uint8_t *p = data;
  size_t remaining = len;

  // namespace
  if (remaining < 1)
    return false;
  uint8_t ns_len = *p++;
  remaining--;
  if (remaining < ns_len)
    return false;
  node->node_namespace.assign(reinterpret_cast<const char *>(p), ns_len);
  p += ns_len;
  remaining -= ns_len;

  // name (MUST be non-empty per ROS2 naming rules)
  if (remaining < 1)
    return false;
  uint8_t name_len = *p++;
  remaining--;
  if (name_len == 0) {
    fprintf(stderr, "[DiscoveryManager] parse_node_entry: name_len=0 is "
                    "invalid (ROS2 requires non-empty node name)\n");
    return false;
  }
  if (remaining < name_len)
    return false;
  node->node_name.assign(reinterpret_cast<const char *>(p), name_len);
  p += name_len;
  remaining -= name_len;

  // enclave
  if (remaining < 1)
    return false;
  uint8_t enc_len = *p++;
  remaining--;
  if (remaining < enc_len)
    return false;
  node->enclave.assign(reinterpret_cast<const char *>(p), enc_len);
  p += enc_len;
  remaining -= enc_len;

  *consumed = len - remaining;
  return true;
}

bool DiscoveryManager::parse_endpoint_entry(const uint8_t *data, size_t len,
                                            GraphEndpointInfo *endpoint,
                                            size_t *consumed) {
  const uint8_t *p = data;
  size_t remaining = len;

  // type (validate range [0, 3])
  if (remaining < 1)
    return false;
  uint8_t raw_type = *p++;
  remaining--;
  if (raw_type > 3) {
    fprintf(stderr,
            "[DiscoveryManager] parse_endpoint_entry: invalid EndpointType %u "
            "(valid: 0-3)\n",
            raw_type);
    return false;
  }
  endpoint->type = static_cast<EndpointType>(raw_type);

  // topic name (MUST be non-empty)
  if (remaining < 1)
    return false;
  uint8_t topic_len = *p++;
  remaining--;
  if (topic_len == 0) {
    fprintf(
        stderr,
        "[DiscoveryManager] parse_endpoint_entry: topic_len=0 is invalid\n");
    return false;
  }
  if (remaining < topic_len)
    return false;
  endpoint->topic_name.assign(reinterpret_cast<const char *>(p), topic_len);
  p += topic_len;
  remaining -= topic_len;

  // type name
  if (remaining < 1)
    return false;
  uint8_t type_len = *p++;
  remaining--;
  if (remaining < type_len)
    return false;
  endpoint->type_name.assign(reinterpret_cast<const char *>(p), type_len);
  p += type_len;
  remaining -= type_len;

  // gid
  if (remaining < RMW_GID_STORAGE_SIZE)
    return false;
  memcpy(endpoint->gid.data, p, RMW_GID_STORAGE_SIZE);
  p += RMW_GID_STORAGE_SIZE;
  remaining -= RMW_GID_STORAGE_SIZE;

  // node name
  if (remaining < 1)
    return false;
  uint8_t node_name_len = *p++;
  remaining--;
  if (remaining < node_name_len)
    return false;
  endpoint->node_name.assign(reinterpret_cast<const char *>(p), node_name_len);
  p += node_name_len;
  remaining -= node_name_len;

  // node namespace
  if (remaining < 1)
    return false;
  uint8_t node_ns_len = *p++;
  remaining--;
  if (remaining < node_ns_len)
    return false;
  endpoint->node_namespace.assign(reinterpret_cast<const char *>(p),
                                  node_ns_len);
  p += node_ns_len;
  remaining -= node_ns_len;

  *consumed = len - remaining;
  return true;
}

bool DiscoveryManager::parse_heartbeat_payload(
    const uint8_t *payload, size_t len, std::vector<std::string> *node_keys) {
  const uint8_t *p = payload;
  size_t remaining = len;

  // Node count
  if (remaining < 2)
    return false;
  uint16_t node_count = p[0] | (p[1] << 8);
  p += 2;
  remaining -= 2;

  for (uint16_t i = 0; i < node_count; i++) {
    // namespace
    if (remaining < 1)
      return false;
    uint8_t ns_len = *p++;
    remaining--;
    if (remaining < ns_len)
      return false;
    std::string ns(reinterpret_cast<const char *>(p), ns_len);
    p += ns_len;
    remaining -= ns_len;

    // name
    if (remaining < 1)
      return false;
    uint8_t name_len = *p++;
    remaining--;
    if (remaining < name_len)
      return false;
    std::string name(reinterpret_cast<const char *>(p), name_len);
    p += name_len;
    remaining -= name_len;

    node_keys->push_back(make_node_key(ns, name));
  }

  return true;
}

// ============================================================
// Protocol Logic
// ============================================================

bool DiscoveryManager::check_origin_valid(const DiscoveryHeader &header,
                                          const std::string &sender_id) {
  std::string origin(header.origin_network_id, header.origin_len);

  // Rule 1: Self-echo → DROP
  if (origin == local_network_id_) {
    return false;
  }

  // Rule 2: Forwarded message (origin != sender) → DROP
  if (origin != sender_id) {
    fprintf(stderr, "[DiscoveryManager] DROP forwarded: origin=%s, sender=%s\n",
            origin.c_str(), sender_id.c_str());
    return false;
  }

  return true;
}

bool DiscoveryManager::check_seq_dedup(const DiscoveryHeader &header) {
  std::lock_guard<std::mutex> lock(seq_mutex_);

  std::string origin(header.origin_network_id, header.origin_len);

  // Check for instance_id change (device restart)
  auto inst_it = known_instance_ids_.find(origin);
  if (inst_it != known_instance_ids_.end() &&
      inst_it->second != header.origin_instance_id) {
    // Instance ID changed → device restarted
    fprintf(stderr,
            "[DiscoveryManager] Origin %s restarted (instance %lu -> %lu)\n",
            origin.c_str(), inst_it->second, header.origin_instance_id);

    // Clear old seq record
    OriginKey old_key{origin, inst_it->second};
    last_seq_seen_.erase(old_key);

    // Observability: track resync events
    stats_.resync_triggered++;
  }
  known_instance_ids_[origin] = header.origin_instance_id;

  // Check seq deduplication
  OriginKey key{origin, header.origin_instance_id};
  auto it = last_seq_seen_.find(key);

  if (it != last_seq_seen_.end() && header.seq <= it->second) {
    // Duplicate or stale → DROP
    return false;
  }

  last_seq_seen_[key] = header.seq;
  return true;
}

void DiscoveryManager::process_message(const DiscoveryHeader &header,
                                       const uint8_t *payload,
                                       const std::string &sender_id) {
  std::string origin(header.origin_network_id, header.origin_len);
  int sessionId = 0;
  {
    std::lock_guard<std::mutex> lock(peer_mutex_);
    auto it = peer_sessions_.find(sender_id);
    if (it != peer_sessions_.end()) {
      sessionId = it->second;
    }
  }

  switch (static_cast<DiscoveryMessageType>(header.msg_type)) {
  case DiscoveryMessageType::HELLO:
    handle_hello(header, payload, sender_id, sessionId);
    break;
  case DiscoveryMessageType::HELLO_ACK:
    handle_hello_ack(header, payload, sender_id, sessionId);
    break;
  case DiscoveryMessageType::QUERY:
    handle_query(sender_id, sessionId);
    break;
  case DiscoveryMessageType::SNAPSHOT:
    handle_snapshot(origin, payload, header.payload_len);
    break;
  case DiscoveryMessageType::NODE_ADD:
    handle_node_add(origin, payload, header.payload_len);
    break;
  case DiscoveryMessageType::NODE_REMOVE:
    handle_node_remove(origin, payload, header.payload_len);
    break;
  case DiscoveryMessageType::ENDPOINT_ADD:
    handle_endpoint_add(origin, payload, header.payload_len);
    break;
  case DiscoveryMessageType::ENDPOINT_REMOVE:
    handle_endpoint_remove(origin, payload, header.payload_len);
    break;
  case DiscoveryMessageType::HEARTBEAT:
    handle_heartbeat(origin, payload, header.payload_len);
    break;
  default:
    fprintf(stderr, "[DiscoveryManager] Unknown message type: %u\n",
            header.msg_type);
    break;
  }
}

void DiscoveryManager::handle_query(const std::string &sender_id,
                                    int sessionId) {
  fprintf(stderr, "[DiscoveryManager] Received QUERY from %s\n",
          sender_id.c_str());

  // Respond with local-only snapshot
  auto msg = build_snapshot_message();
  if (msg.empty()) {
    fprintf(stderr, "[DiscoveryManager] handle_query: failed to build "
                    "snapshot, not responding\n");
    return;
  }
  send_to_peer(sessionId, msg);
}

void DiscoveryManager::handle_snapshot(const std::string &origin_id,
                                       const uint8_t *payload, size_t len) {
  fprintf(stderr, "[DiscoveryManager] Received SNAPSHOT from %s\n",
          origin_id.c_str());
  stats_.snapshot_recv++;

  const uint8_t *p = payload;
  size_t remaining = len;

  // Minimum header check (8 bytes: node_count + endpoint_count + timestamp)
  if (remaining < 8) {
    fprintf(stderr, "[DiscoveryManager] DROP: SNAPSHOT too short (%zu < 8)\n",
            len);
    stats_.drop_parse_error++;
    return;
  }

  // Parse counts and timestamp
  uint16_t node_count = p[0] | (p[1] << 8);
  uint16_t endpoint_count = p[2] | (p[3] << 8);
  p += 8;
  remaining -= 8;

  // ============================================================
  // Fix 1: Hard limits on counts (DoS protection)
  // ============================================================
  if (node_count > MAX_NODES_PER_SNAPSHOT) {
    fprintf(stderr,
            "[DiscoveryManager] DROP: node_count %u exceeds limit %u (DoS "
            "protection)\n",
            node_count, MAX_NODES_PER_SNAPSHOT);
    stats_.drop_count_limit++;
    return; // DROP entire snapshot, do not attempt partial parse
  }
  if (endpoint_count > MAX_ENDPOINTS_PER_SNAPSHOT) {
    fprintf(stderr,
            "[DiscoveryManager] DROP: endpoint_count %u exceeds limit %u (DoS "
            "protection)\n",
            endpoint_count, MAX_ENDPOINTS_PER_SNAPSHOT);
    stats_.drop_count_limit++;
    return;
  }

  // ============================================================
  // Fix 2: Minimum size feasibility check (early rejection)
  // ============================================================
  size_t min_required = node_count * MIN_NODE_ENTRY_SIZE +
                        endpoint_count * MIN_ENDPOINT_ENTRY_SIZE;
  if (remaining < min_required) {
    fprintf(stderr,
            "[DiscoveryManager] DROP: payload too small for declared counts "
            "(remaining=%zu, min_required=%zu for %u nodes + %u endpoints)\n",
            remaining, min_required, node_count, endpoint_count);
    stats_.drop_parse_error++;
    return;
  }

  // ============================================================
  // Parse all entries into temporary vectors (for batch merge)
  // ============================================================
  std::vector<GraphNodeInfo> parsed_nodes;
  std::vector<GraphEndpointInfo> parsed_endpoints;
  std::vector<std::string> node_keys; // For batch liveliness update

  parsed_nodes.reserve(node_count);
  parsed_endpoints.reserve(endpoint_count);
  node_keys.reserve(node_count);

  // Parse nodes
  for (uint16_t i = 0; i < node_count; i++) {
    GraphNodeInfo node;
    size_t consumed = 0;
    if (!parse_node_entry(p, remaining, &node, &consumed)) {
      fprintf(stderr, "[DiscoveryManager] Failed to parse node entry %u/%u\n",
              i, node_count);
      stats_.drop_parse_error++;
      return; // Abort entire snapshot on any parse failure
    }
    if (consumed > remaining) {
      fprintf(
          stderr,
          "[DiscoveryManager] Parse consumed more than available (node %u)\n",
          i);
      stats_.drop_parse_error++;
      return;
    }
    p += consumed;
    remaining -= consumed;

    node.network_id = origin_id;
    node_keys.push_back(make_node_key(node.node_namespace, node.node_name));
    parsed_nodes.push_back(std::move(node));
  }

  // Parse endpoints
  for (uint16_t i = 0; i < endpoint_count; i++) {
    GraphEndpointInfo endpoint;
    size_t consumed = 0;
    if (!parse_endpoint_entry(p, remaining, &endpoint, &consumed)) {
      fprintf(stderr,
              "[DiscoveryManager] Failed to parse endpoint entry %u/%u\n", i,
              endpoint_count);
      stats_.drop_parse_error++;
      return;
    }
    if (consumed > remaining) {
      fprintf(stderr,
              "[DiscoveryManager] Parse consumed more than available (endpoint "
              "%u)\n",
              i);
      stats_.drop_parse_error++;
      return;
    }
    p += consumed;
    remaining -= consumed;

    endpoint.network_id = origin_id;
    parsed_endpoints.push_back(std::move(endpoint));
  }

  // ============================================================
  // Fix 6: Batch merge into GraphCache (single lock, single guard trigger)
  // ============================================================
  GraphCache::instance().merge_remote_snapshot(origin_id, parsed_nodes,
                                               parsed_endpoints);

  // ============================================================
  // Fix 5: Batch liveliness update (single lock for all nodes)
  // ============================================================
  uint64_t now = get_timestamp_ns();
  {
    std::lock_guard<std::mutex> lock(liveness_mutex_);
    auto &origin_liveness = remote_node_liveness_[origin_id];
    for (const auto &key : node_keys) {
      origin_liveness[key] = now;
    }
  }

  fprintf(
      stderr,
      "[DiscoveryManager] SNAPSHOT merged: %zu nodes, %zu endpoints from %s\n",
      parsed_nodes.size(), parsed_endpoints.size(), origin_id.c_str());

  // Client (Dialer) receives SNAPSHOT → enter READY (state machine v1)
  // Find sessionId from origin_id
  int sessionId = -1;
  {
    std::lock_guard<std::mutex> lock(peer_mutex_);
    auto it = peer_sessions_.find(origin_id);
    if (it != peer_sessions_.end()) {
      sessionId = it->second;
    }
  }

  if (sessionId >= 0) {
    std::lock_guard<std::mutex> lock(sessions_mutex_);
    auto it = sessions_.find(sessionId);
    if (it != sessions_.end() && it->second.is_dialer && it->second.state == SessionState::OPENED) {
      it->second.state = SessionState::READY;
      fprintf(stderr, "[STATE] Session %d: OPENED → READY (Dialer, received SNAPSHOT)\n",
              sessionId);
      fflush(stderr);

      // Flush data queue (queued heartbeat/future messages)
      for (auto& msg : it->second.data_queue) {
        send_to_peer_internal(sessionId, msg);
      }
      it->second.data_queue.clear();
    }
  }
}

void DiscoveryManager::handle_node_add(const std::string &origin_id,
                                       const uint8_t *payload, size_t len) {
  stats_.node_add_recv++;

  GraphNodeInfo node;
  size_t consumed = 0;
  if (!parse_node_entry(payload, len, &node, &consumed)) {
    stats_.drop_parse_error++;
    return;
  }

  node.network_id = origin_id;
  GraphCache::instance().on_remote_node_discovered(node);

  // Refresh liveliness
  std::string key = make_node_key(node.node_namespace, node.node_name);
  {
    std::lock_guard<std::mutex> lock(liveness_mutex_);
    remote_node_liveness_[origin_id][key] = get_timestamp_ns();
  }

  fprintf(stderr, "[DiscoveryManager] NODE_ADD: %s from %s\n",
          node.node_name.c_str(), origin_id.c_str());
}

void DiscoveryManager::handle_node_remove(const std::string &origin_id,
                                          const uint8_t *payload, size_t len) {
  stats_.node_remove_recv++;

  const uint8_t *p = payload;
  size_t remaining = len;

  // Parse namespace and name
  if (remaining < 1)
    return;
  uint8_t ns_len = *p++;
  remaining--;
  if (remaining < ns_len)
    return;
  std::string ns(reinterpret_cast<const char *>(p), ns_len);
  p += ns_len;
  remaining -= ns_len;

  if (remaining < 1)
    return;
  uint8_t name_len = *p++;
  remaining--;
  if (remaining < name_len)
    return;
  std::string name(reinterpret_cast<const char *>(p), name_len);

  std::string key = make_node_key(ns, name);
  GraphCache::instance().remove_remote_node(origin_id, key);

  // Remove from liveliness
  {
    std::lock_guard<std::mutex> lock(liveness_mutex_);
    auto dev_it = remote_node_liveness_.find(origin_id);
    if (dev_it != remote_node_liveness_.end()) {
      dev_it->second.erase(key);
    }
  }

  fprintf(stderr, "[DiscoveryManager] NODE_REMOVE: %s from %s\n", key.c_str(),
          origin_id.c_str());
}

void DiscoveryManager::handle_endpoint_add(const std::string &origin_id,
                                           const uint8_t *payload, size_t len) {
  stats_.endpoint_add_recv++;

  GraphEndpointInfo endpoint;
  size_t consumed = 0;
  if (!parse_endpoint_entry(payload, len, &endpoint, &consumed)) {
    stats_.drop_parse_error++;
    return;
  }

  endpoint.network_id = origin_id;
  GraphCache::instance().on_remote_endpoint_discovered(endpoint);

  fprintf(stderr, "[DiscoveryManager] ENDPOINT_ADD: %s from %s\n",
          endpoint.topic_name.c_str(), origin_id.c_str());
}

void DiscoveryManager::handle_endpoint_remove(const std::string &origin_id,
                                              const uint8_t *payload,
                                              size_t len) {
  stats_.endpoint_remove_recv++;

  if (len < RMW_GID_STORAGE_SIZE) {
    stats_.drop_parse_error++;
    return;
  }

  rmw_gid_t gid;
  memcpy(gid.data, payload, RMW_GID_STORAGE_SIZE);

  GraphCache::instance().remove_remote_endpoint(origin_id, gid);

  fprintf(stderr, "[DiscoveryManager] ENDPOINT_REMOVE from %s\n",
          origin_id.c_str());
}

void DiscoveryManager::handle_heartbeat(const std::string &origin_id,
                                        const uint8_t *payload, size_t len) {
  stats_.heartbeat_recv++;

  std::vector<std::string> node_keys;
  if (!parse_heartbeat_payload(payload, len, &node_keys)) {
    stats_.drop_parse_error++;
    return;
  }

  // Refresh liveliness for all nodes
  uint64_t now = get_timestamp_ns();
  {
    std::lock_guard<std::mutex> lock(liveness_mutex_);
    for (const auto &key : node_keys) {
      remote_node_liveness_[origin_id][key] = now;
    }
  }
}

void DiscoveryManager::handle_hello(const DiscoveryHeader& header,
                                   const uint8_t* payload,
                                   const std::string& sender_id,
                                   int sessionId) {
  (void)header; (void)payload;  // HELLO has no payload

  fprintf(stderr, "[HANDSHAKE] Received HELLO from %s (session %d)\n",
          sender_id.c_str(), sessionId);
  fflush(stderr);

  // Client (Dialer) receives HELLO → send HELLO_ACK
  send_hello_ack(sessionId);

  // After sending HELLO_ACK, Client can send QUERY (will be queued until READY)
  send_query(sessionId);
}

void DiscoveryManager::handle_hello_ack(const DiscoveryHeader& header,
                                       const uint8_t* payload,
                                       const std::string& sender_id,
                                       int sessionId) {
  (void)header; (void)payload;

  fprintf(stderr, "[HANDSHAKE] Received HELLO_ACK from %s (session %d)\n",
          sender_id.c_str(), sessionId);
  fflush(stderr);

  // Server (Acceptor) receives HELLO_ACK → enter READY
  {
    std::lock_guard<std::mutex> lock(sessions_mutex_);
    auto it = sessions_.find(sessionId);
    if (it != sessions_.end() && it->second.state == SessionState::OPENED) {
      it->second.state = SessionState::READY;
      fprintf(stderr, "[STATE] Session %d: OPENED → READY (Acceptor, received HELLO_ACK)\n",
              sessionId);
      fflush(stderr);

      // Flush data queue (queued QUERY/heartbeat)
      for (auto& msg : it->second.data_queue) {
        send_to_peer_internal(sessionId, msg);
      }
      it->second.data_queue.clear();
    }
  }
}

// ============================================================
// Networking
// ============================================================

void DiscoveryManager::send_to_peer(int sessionId,
                                    const std::vector<uint8_t> &msg) {
  if (sessionId < 0 || msg.empty())
    return;

  // Determine message type
  bool is_control_frame = false;
  bool is_query = false;
  if (msg.size() >= DISCOVERY_HEADER_SIZE) {
    uint8_t msg_type = msg[3];  // header.msg_type at offset 3
    is_control_frame = (msg_type == 0x08 || msg_type == 0x09);  // HELLO/HELLO_ACK
    is_query = (msg_type == 0x01);  // QUERY - must bypass barrier to prevent deadlock
  }

  std::lock_guard<std::mutex> lock(sessions_mutex_);
  auto it = sessions_.find(sessionId);
  if (it == sessions_.end()) {
    fprintf(stderr, "[SENDBYTES] Session %d not found (not in state machine), dropping\n", sessionId);
    return;
  }

  SessionContext& ctx = it->second;

  // State-based routing (HARD BARRIER: no business data before READY)
  // EXCEPTION: QUERY must bypass barrier to prevent Client/Server deadlock:
  //   - Client sends QUERY → Server responds with SNAPSHOT → Client becomes READY
  //   - If QUERY is blocked, Client waits for SNAPSHOT forever
  if (ctx.state == SessionState::PENDING) {
    // Queue all messages
    if (is_control_frame) {
      ctx.control_queue.push_back(msg);
    } else {
      ctx.data_queue.push_back(msg);
    }
    fprintf(stderr, "[QUEUE] Session %d PENDING, queued (%s queue)\n",
            sessionId, is_control_frame ? "control" : "data");
    return;
  }

  if (ctx.state == SessionState::OPENED) {
    if (is_control_frame || is_query) {
      // Control frames + QUERY: allow (handshake/discovery sync in progress)
      send_to_peer_internal(sessionId, msg);
    } else {
      // Other data frames: HARD BARRIER - queue until READY
      ctx.data_queue.push_back(msg);
      fprintf(stderr, "[QUEUE] Session %d OPENED (handshaking), data queued (len=%zu)\n",
              sessionId, msg.size());
    }
    return;
  }

  if (ctx.state == SessionState::READY) {
    // All frames allowed
    send_to_peer_internal(sessionId, msg);
    return;
  }

  // CLOSED: drop
  fprintf(stderr, "[SENDBYTES] Session %d CLOSED, drop (len=%zu)\n",
          sessionId, msg.size());
}

void DiscoveryManager::send_to_peer_internal(int sessionId,
                                             const std::vector<uint8_t> &msg) {
  // Direct send (no state check, called from within lock or for control frames)
  int ret = SendBytes(sessionId, msg.data(), static_cast<unsigned int>(msg.size()));
  if (ret != 0) {
    fprintf(stderr, "[SENDBYTES] ❌ FAILED: session=%d ret=%d len=%zu\n",
            sessionId, ret, msg.size());
    fflush(stderr);
  } else {
    fprintf(stderr, "[SENDBYTES] ✅ OK: session=%d len=%zu\n",
            sessionId, msg.size());
    fflush(stderr);
  }
  stats_.tx_total++;
}

void DiscoveryManager::broadcast_to_all_peers(const std::vector<uint8_t> &msg) {
  std::lock_guard<std::mutex> lock(peer_mutex_);
  for (const auto &pair : peer_sessions_) {
    send_to_peer(pair.second, msg);
  }
}

void DiscoveryManager::send_query(int sessionId) {
  fprintf(stderr, "[QUERY] Sending QUERY to session %d...\n", sessionId);
  fflush(stderr);
  auto msg = build_query_message();
  send_to_peer(sessionId, msg);
  stats_.query_sent++;
}

void DiscoveryManager::send_hello(int sessionId) {
  std::lock_guard<std::mutex> lock(sessions_mutex_);
  auto it = sessions_.find(sessionId);
  if (it == sessions_.end()) return;

  // Idempotent: check once-flag
  if (it->second.hello_sent.exchange(true)) {
    fprintf(stderr, "[HANDSHAKE] HELLO already sent to session %d, skip\n", sessionId);
    return;
  }

  fprintf(stderr, "[HANDSHAKE] Sending HELLO to session %d (Acceptor role)\n", sessionId);
  fflush(stderr);

  auto msg = build_hello_message();
  send_to_peer_internal(sessionId, msg);  // Bypass queue, force send
}

void DiscoveryManager::send_hello_ack(int sessionId) {
  std::lock_guard<std::mutex> lock(sessions_mutex_);
  auto it = sessions_.find(sessionId);
  if (it == sessions_.end()) return;

  // Idempotent: check once-flag
  if (it->second.hello_ack_sent.exchange(true)) {
    fprintf(stderr, "[HANDSHAKE] HELLO_ACK already sent to session %d, skip\n", sessionId);
    return;
  }

  fprintf(stderr, "[HANDSHAKE] Sending HELLO_ACK to session %d (Dialer role)\n", sessionId);
  fflush(stderr);

  auto msg = build_hello_ack_message();
  send_to_peer_internal(sessionId, msg);  // Bypass queue
}

// ============================================================
// Heartbeat & Liveliness
// ============================================================

void DiscoveryManager::heartbeat_thread_func() {
  // Attempt peer connections on first iteration
  // This runs asynchronously without blocking initialization
  connect_all_peers_once();

  while (running_.load()) {
    // Sleep for heartbeat interval
    for (int i = 0; i < 50 && running_.load(); i++) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    if (!running_.load())
      break;

    // Send heartbeat to all peers
    auto msg = build_heartbeat_message();
    broadcast_to_all_peers(msg);

    // Check node liveliness
    check_node_liveliness();
  }
}

void DiscoveryManager::check_node_liveliness() {
  uint64_t now = get_timestamp_ns();

  std::lock_guard<std::mutex> lock(liveness_mutex_);

  for (auto dev_it = remote_node_liveness_.begin();
       dev_it != remote_node_liveness_.end();) {

    const std::string &network_id = dev_it->first;
    auto &nodes = dev_it->second;

    for (auto node_it = nodes.begin(); node_it != nodes.end();) {
      if (now - node_it->second > NODE_TIMEOUT_NS) {
        // Node timeout
        fprintf(stderr, "[DiscoveryManager] Node timeout: %s on device %s\n",
                node_it->first.c_str(), network_id.c_str());

        GraphCache::instance().remove_remote_node(network_id, node_it->first);
        node_it = nodes.erase(node_it);
      } else {
        ++node_it;
      }
    }

    // Clean up empty device entry
    if (nodes.empty()) {
      dev_it = remote_node_liveness_.erase(dev_it);
    } else {
      ++dev_it;
    }
  }
}

// ============================================================
// Utilities
// ============================================================

uint64_t DiscoveryManager::get_timestamp_ns() const {
  struct timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);
  return static_cast<uint64_t>(ts.tv_sec) * 1000000000ULL +
         static_cast<uint64_t>(ts.tv_nsec);
}

uint64_t DiscoveryManager::get_next_seq() { return seq_counter_.fetch_add(1); }

std::string DiscoveryManager::get_peer_network_id(int sessionId) const {
  std::lock_guard<std::mutex> lock(peer_mutex_);
  auto it = session_to_peer_.find(sessionId);
  if (it != session_to_peer_.end()) {
    return it->second;
  }
  return "";
}

// ============================================================
// Testing Helper Functions
// ============================================================

std::vector<uint8_t> DiscoveryManager::build_heartbeat_message_for_test() {
  return build_heartbeat_message();
}

int DiscoveryManager::get_first_peer_session_id() const {
  std::lock_guard<std::mutex> lock(peer_mutex_);
  if (peer_sessions_.empty()) {
    return -1;
  }
  return peer_sessions_.begin()->second;
}

} // namespace rmw_dsoftbus
