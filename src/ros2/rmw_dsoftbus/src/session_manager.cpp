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

#include "rmw_dsoftbus/session_manager.h"
#include "dsoftbus/softbus_error_code.h"
#include "rmw_dsoftbus/dsoftbus_session.h"
#include "rmw_dsoftbus/native_token.h"
#include "rmw_dsoftbus/types.h"

#include <cstdio>
#include <chrono>
#include <unistd.h>

// C library functions for memory/string operations
extern "C" {
    void *memset(void *s, int c, size_t n);
    void *memcpy(void *dest, const void *src, size_t n);
    size_t strlen(const char *s);
}

// dsoftbus Session API types already declared in dsoftbus_session.h

namespace rmw_dsoftbus {

// gcc-linaro compatibility - Use C style directly instead of cstring
// Note: memcpy, memset, memcmp are available from <string.h>

SessionManager &SessionManager::instance() {
  static SessionManager instance;
  return instance;
}

SessionManager::SessionManager() {}

SessionManager::~SessionManager() { shutdown(); }

bool SessionManager::initialize() {
  std::lock_guard<std::mutex> lock(mutex_);

  if (initialized_) {
    return true;
  }

  fprintf(stderr, "[SessionManager] Initializing dsoftbus session layer\n");

  // Try OpenHarmony AccessToken API first (preferred method)
  fprintf(stderr, "[SessionManager] Attempting AccessToken API initialization...\n");
  if (InitializeNativeToken("com.huawei.ros2_rmw_dsoftbus")) {
    fprintf(stderr, "[SessionManager] AccessToken API initialization succeeded\n");
  } else {
    fprintf(stderr, "[SessionManager] AccessToken API initialization failed, falling back to ioctl method\n");
    // Fallback to ioctl-based method
    (void)try_init_native_token();
  }

  initialized_ = true;
  return true;
}

void SessionManager::shutdown() {
  std::lock_guard<std::mutex> lock(mutex_);

  if (!initialized_) {
    return;
  }

  // Close all sessions
  for (auto &pair : sessions_) {
    CloseSession(pair.first);
  }
  sessions_.clear();

  // Remove all session servers
  for (auto &pair : topic_servers_) {
    RemoveSessionServer(RMW_DSOFTBUS_PACKAGE_NAME, pair.first.c_str());
  }
  topic_servers_.clear();

  subscriptions_.clear();
  initialized_ = false;
}

int SessionManager::register_subscription(const std::string &topic_name,
                                          SubscriptionImpl *sub) {
  std::lock_guard<std::mutex> lock(mutex_);

  if (!initialized_) {
    fprintf(stderr, "[SessionManager] Not initialized\n");
    return -1;
  }

  // Check if already registered
  if (topic_servers_.find(topic_name) != topic_servers_.end()) {
    fprintf(stderr, "[SessionManager] Topic already registered: %s\n",
            topic_name.c_str());
    subscriptions_[topic_name] = sub;
    return 0;
  }

  // Use topic-based session name (no PID) for cross-device matching
  // Format: <prefix><topic_name>
  // Example: com.huawei.ros2_rmw_dsoftbus.chatter
  // Note: No PID because talker needs to know this name to connect
  char session_buffer[256];
  snprintf(session_buffer, sizeof(session_buffer), "%s%s",
           RMW_DSOFTBUS_SESSION_PREFIX, topic_name.c_str());
  std::string session_name = session_buffer;

  // Setup callbacks
  static ISessionListener listener = {
      .OnSessionOpened = on_session_opened_callback,
      .OnSessionClosed = on_session_closed_callback,
      .OnBytesReceived = on_bytes_received_callback,
      .OnMessageReceived = nullptr,
      .OnStreamReceived = nullptr,
      .OnQosEvent = nullptr};

  // Create session server
  fprintf(stderr,
          "[SessionManager] Creating session server for topic '%s' with session_name='%s'\n",
          topic_name.c_str(), session_name.c_str());

  int ret = CreateSessionServer(RMW_DSOFTBUS_PACKAGE_NAME, session_name.c_str(),
                                &listener);
  if (ret != 0) {
    fprintf(stderr,
            "[SessionManager] CreateSessionServer failed: ret=%d for topic '%s', session_name='%s'\n",
            ret, topic_name.c_str(), session_name.c_str());
    if (ret == SOFTBUS_ACCESS_TOKEN_DENIED ||
        ret == SOFTBUS_PERMISSION_DENIED || ret == SOFTBUS_ERR) {
      fprintf(stderr,
              "[SessionManager] Hint: need AccessToken permission "
              "(ohos.permission.DISTRIBUTED_DATASYNC); "
              "check that package '%s' is in softbus_trans_permission.json "
              "and session pattern '%s.*' is allowed\n",
              RMW_DSOFTBUS_PACKAGE_NAME, RMW_DSOFTBUS_SESSION_PREFIX);
    }
    return -1;
  }

  fprintf(stderr,
          "[SessionManager] Created session server: topic='%s', session_name='%s', server_id=%d\n",
          topic_name.c_str(), session_name.c_str(), ret);
  topic_servers_[topic_name] = ret;
  subscriptions_[topic_name] = sub;

  return 0;
}

void SessionManager::unregister_subscription(const std::string &topic_name) {
  std::lock_guard<std::mutex> lock(mutex_);

  auto it = topic_servers_.find(topic_name);
  if (it != topic_servers_.end()) {
    std::string session_name =
        std::string(RMW_DSOFTBUS_SESSION_PREFIX) + topic_name;
    RemoveSessionServer(RMW_DSOFTBUS_PACKAGE_NAME, session_name.c_str());
    topic_servers_.erase(it);
  }

  subscriptions_.erase(topic_name);
}

int SessionManager::open_session(const std::string &topic_name,
                                 const std::string &peer_network_id) {
  std::lock_guard<std::mutex> lock(mutex_);

  if (!initialized_) {
    fprintf(stderr, "[SessionManager] Not initialized\n");
    return -1;
  }

  // Both sides use the SAME topic-based session name (no PID)
  // This allows cross-device matching without needing to know the peer's PID
  // Format: <prefix><topic_name>
  // Example: com.huawei.ros2_rmw_dsoftbus.chatter
  char session_buffer[256];
  snprintf(session_buffer, sizeof(session_buffer), "%s%s",
           RMW_DSOFTBUS_SESSION_PREFIX, topic_name.c_str());
  std::string my_session_name = session_buffer;

  // Peer session name is the same (topic-based, no PID for cross-device matching)
  std::string peer_session_name = my_session_name;

  // Setup session attributes
  SessionAttribute attr;
  memset(&attr, 0, sizeof(attr));
  attr.dataType = TYPE_BYTES;
  attr.linkTypeNum = 1;
  attr.linkType[0] = LINK_TYPE_WIFI_WLAN_5G;
  // Note: Encryption config not needed in stub mode

  // Log session information
  fprintf(stderr,
          "[SessionManager] Opening session: topic='%s', my_session='%s', peer_session='%s', "
          "peer_id='%s', my_pid=%d\n",
          topic_name.c_str(), my_session_name.c_str(), peer_session_name.c_str(),
          peer_network_id.c_str(), getpid());

  // Open session
  int session_id =
      OpenSession(my_session_name.c_str(), peer_session_name.c_str(),
                  peer_network_id.c_str(),
                  "", // No group ID
                  &attr);

  if (session_id < 0) {
    fprintf(stderr,
            "[SessionManager] OpenSession failed: ret=%d for session_name='%s', "
            "peer_id='%s'\n",
            session_id, my_session_name.c_str(), peer_network_id.c_str());
    return -1;
  }

  fprintf(stderr,
          "[SessionManager] OpenSession succeeded: session_id=%d, session_name='%s'\n",
          session_id, my_session_name.c_str());

  // Track connection (outbound session)
  SessionConnection conn;
  conn.session_id = session_id;
  conn.topic_name = topic_name;
  conn.session_name = my_session_name;
  conn.peer_network_id = peer_network_id;
  conn.is_connected = false; // Will be set in callback
  conn.is_inbound = false;   // We opened this session
  sessions_[session_id] = conn;

  fprintf(stderr,
          "[SessionManager] Opened outbound session %d for topic '%s' to peer '%s'\n",
          session_id, topic_name.c_str(), peer_network_id.c_str());

  return session_id;
}

void SessionManager::close_session(int session_id) {
  std::lock_guard<std::mutex> lock(mutex_);

  auto it = sessions_.find(session_id);
  if (it != sessions_.end()) {
    CloseSession(session_id);
    sessions_.erase(it);
  }
}

int SessionManager::send_bytes(int session_id, const void *data,
                               unsigned int len) {
  if (len > RMW_DSOFTBUS_MAX_MESSAGE_SIZE) {
    fprintf(stderr, "[SessionManager] Message too large: %u bytes (max %d)\n",
            len, RMW_DSOFTBUS_MAX_MESSAGE_SIZE);
    return -1;
  }

  return SendBytes(session_id, data, len);
}

bool SessionManager::is_session_alive(int session_id) const {
  std::lock_guard<std::mutex> lock(mutex_);

  auto it = sessions_.find(session_id);
  if (it == sessions_.end()) {
    return false;
  }

  return it->second.is_connected;
}

// Static callback wrappers
int SessionManager::on_session_opened_callback(int sessionId, int result) {
  instance().on_session_opened(sessionId, result);
  return 0; // Accept connection
}

void SessionManager::on_session_closed_callback(int sessionId) {
  instance().on_session_closed(sessionId);
}

void SessionManager::on_bytes_received_callback(int sessionId, const void *data,
                                                unsigned int dataLen) {
  instance().on_bytes_received(sessionId, data, dataLen);
}

// Helper: Extract topic name from session name
// Format: com.huawei.ros2_rmw_dsoftbus.<topic>
// Note: No PID suffix anymore - topic name comes directly after prefix
static std::string extract_topic_from_session_name(const char *session_name) {
  std::string name(session_name);

  // Find prefix position
  const char *prefix = RMW_DSOFTBUS_SESSION_PREFIX;
  size_t prefix_len = strlen(prefix);

  if (name.length() <= prefix_len) {
    return "";
  }

  // Skip prefix - everything after is the topic name
  return name.substr(prefix_len);
}

// Internal handlers
void SessionManager::on_session_opened(int sessionId, int result) {
  std::lock_guard<std::mutex> lock(mutex_);

  auto it = sessions_.find(sessionId);
  if (it != sessions_.end()) {
    // Outbound session: we opened it, update status
    it->second.is_connected = (result == 0);
    fprintf(stderr, "[SessionManager] Outbound session %d opened: %s\n", sessionId,
            result == 0 ? "success" : "failed");
  } else if (result == 0) {
    // Inbound session: remote device opened it to us
    // This is critical - we must track it to receive messages!
    fprintf(stderr, "[SessionManager] Inbound session %d opened - tracking...\n", sessionId);

    // Get peer information using dsoftbus APIs
    char peerNetworkId[NETWORK_ID_BUF_LEN] = {0};
    char peerSessionName[256] = {0};

    int ret = GetPeerDeviceId(sessionId, peerNetworkId, sizeof(peerNetworkId));
    if (ret != 0) {
      fprintf(stderr, "[SessionManager] Warning: GetPeerDeviceId failed: %d\n", ret);
    }

    ret = GetPeerSessionName(sessionId, peerSessionName, sizeof(peerSessionName));
    if (ret != 0) {
      fprintf(stderr, "[SessionManager] Warning: GetPeerSessionName failed: %d\n", ret);
    }

    // Extract topic name from session name
    std::string topic_name = extract_topic_from_session_name(peerSessionName);

    fprintf(stderr, "[SessionManager] Inbound session details:\n"
            "  sessionId=%d\n"
            "  peerNetworkId=%s\n"
            "  peerSessionName=%s\n"
            "  extracted_topic=%s\n",
            sessionId, peerNetworkId, peerSessionName, topic_name.c_str());

    // Track the inbound session
    SessionConnection conn;
    conn.session_id = sessionId;
    conn.topic_name = topic_name;
    conn.session_name = peerSessionName;
    conn.peer_network_id = peerNetworkId;
    conn.is_connected = true;
    conn.is_inbound = true;
    sessions_[sessionId] = conn;

    fprintf(stderr, "[SessionManager] Inbound session %d now tracked for topic '%s'\n",
            sessionId, topic_name.c_str());
  } else {
    fprintf(stderr, "[SessionManager] Unknown session %d opened with error: %d\n",
            sessionId, result);
  }
}

void SessionManager::on_session_closed(int sessionId) {
  std::lock_guard<std::mutex> lock(mutex_);

  auto it = sessions_.find(sessionId);
  if (it != sessions_.end()) {
    fprintf(stderr, "[SessionManager] Session %d closed (topic='%s', inbound=%s)\n",
            sessionId, it->second.topic_name.c_str(),
            it->second.is_inbound ? "yes" : "no");
    it->second.is_connected = false;

    // For inbound sessions, remove from tracking completely
    // (outbound sessions may be retried, so keep them)
    if (it->second.is_inbound) {
      sessions_.erase(it);
      fprintf(stderr, "[SessionManager] Removed inbound session %d from tracking\n", sessionId);
    }
  } else {
    fprintf(stderr, "[SessionManager] Session %d closed (not tracked)\n", sessionId);
  }
}

void SessionManager::on_bytes_received(int sessionId, const void *data,
                                       unsigned int dataLen) {
  std::lock_guard<std::mutex> lock(mutex_);

  // Direct lookup by sessionId (O(1) instead of O(n))
  auto it = sessions_.find(sessionId);
  if (it == sessions_.end()) {
    fprintf(stderr, "[SessionManager] Received data from untracked session %d "
            "(may be inbound session that wasn't tracked)\n", sessionId);

    // Try to get session info and track it dynamically
    char peerSessionName[256] = {0};
    int ret = GetPeerSessionName(sessionId, peerSessionName, sizeof(peerSessionName));
    if (ret == 0) {
      std::string topic_name = extract_topic_from_session_name(peerSessionName);
      fprintf(stderr, "[SessionManager] Late-tracking session %d for topic '%s'\n",
              sessionId, topic_name.c_str());

      // Add to tracking
      SessionConnection conn;
      conn.session_id = sessionId;
      conn.topic_name = topic_name;
      conn.session_name = peerSessionName;
      conn.is_connected = true;
      conn.is_inbound = true;
      sessions_[sessionId] = conn;
      it = sessions_.find(sessionId);
    } else {
      fprintf(stderr, "[SessionManager] Cannot identify session %d, dropping data\n", sessionId);
      return;
    }
  }

  std::string topic_name = it->second.topic_name;

  // Log reception details
  fprintf(stderr, "[SessionManager] Received %u bytes on session %d (topic='%s', inbound=%s)\n",
          dataLen, sessionId, topic_name.c_str(),
          it->second.is_inbound ? "yes" : "no");

  if (topic_name.empty()) {
    fprintf(stderr, "[SessionManager] Session %d has no topic association\n", sessionId);
    return;
  }

  // Route to subscription
  auto sub_it = subscriptions_.find(topic_name);
  if (sub_it == subscriptions_.end()) {
    fprintf(stderr, "[SessionManager] No subscription for topic %s\n",
            topic_name.c_str());
    return;
  }

  SubscriptionImpl *sub = sub_it->second;
  if (!sub) {
    return;
  }

  // Add to message queue
  {
    std::lock_guard<std::mutex> queue_lock(sub->queue_mutex);

    MessageItem msg;
    msg.data.assign(static_cast<const uint8_t *>(data),
                    static_cast<const uint8_t *>(data) + dataLen);

    // Add timestamp (nanoseconds since epoch)
    auto now = std::chrono::steady_clock::now();
    msg.timestamp_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
        now.time_since_epoch()).count();

    // Increment sequence number per subscription
    msg.sequence_number = sub->received_sequence_number++;

    sub->message_queue.push(std::move(msg));

    // Notify via pipe
    if (sub->pipe_fd[1] >= 0) {
      char notify = 1;
      ssize_t written = write(sub->pipe_fd[1], &notify, 1);
      (void)written;
    }
  }
}

} // namespace rmw_dsoftbus
