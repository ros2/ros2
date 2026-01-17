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
// Service/Client Manager - Session-based RPC implementation
// Phase 2.1: Using environment variables for peer discovery
// Phase 2.2: Will use SoftBus Discovery API
//
// ============================================================================
// ⚠️ CRITICAL ENGINEERING RULE: sessionId 来源规则（工程规范）
// ============================================================================
//
// sessionId 的 ONLY 合法来源：
//   1. OpenSession(...) 的返回值 - Client 主动连接时
//   2. OnSessionOpened(sessionId, ...) 回调 - Server 被动接受连接时
//
// CreateSessionServer(...) 的返回值：
//   ❌ NOT a sessionId!
//   ✅ 只表示"监听器注册成功"
//   ✅ 不能用于 SendBytes / g_session_to_* 映射
//
// STUB MODE WARNING (Phase 2.1):
//   - 当前 stub 的 OpenSession 返回伪值（100, 101, ...）
//   - OnSessionOpened 可能不会被调用
//   - OnBytesReceived 不会被触发（没有真实网络通信）
//   - 这些都是"逻辑验证用伪值"，仅用于代码路径测试
//
// REAL MODE (Phase 2.2):
//   - 使用真实 libsoftbus_client.so
//   - OnSessionOpened 会被正确调用
//   - sessionId 是真实的网络连接标识
//   - g_session_to_* 映射表会被正确填充
//
// 《商君书·慎法》："法立而不备，则乱生。"
// ============================================================================

// C standard library (must come before C++ headers for gcc-linaro compatibility)
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "dsoftbus/softbus_error_code.h"
#include "rmw_dsoftbus/dsoftbus_session.h"
#include "rmw_dsoftbus/message_header.h"
#include "rmw_dsoftbus/native_token.h"
#include "rmw_dsoftbus/rmw_dsoftbus.h"
#include "rmw_dsoftbus/types.h"
#include "rmw_dsoftbus/graph_cache.h"
#include "rmw_dsoftbus/session_manager.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <unordered_map>

namespace rmw_dsoftbus {

// Explicit C functions for gcc-linaro compatibility
using ::memcpy;
using ::memset;
using ::memcmp;
using ::strerror;

// ============================================================================
// Data Structures
// ============================================================================

// Service Server 管理信息 (renamed to avoid conflict with graph_cache.h)
struct ServiceServerInfo {
  std::string service_name; // metadata only
  void *service_impl;       // ServiceImpl* - 真实唯一标识
  int listener_id; // CreateSessionServer 返回值（NOT a sessionId!）
  std::string session_name; // dsoftbus session name

  // ⚠️ CRITICAL: sessionId 只能来自 OnSessionOpened 回调
  // listener_id 只表示"监听器注册成功"，不是通信用的 sessionId
  // 客户端连接时，OnSessionOpened 会提供真实的 sessionId
  std::unordered_map<int, GID>
      client_sessions; // sessionId -> client_gid（真实的 sessionId）
};

// Client 管理信息 (renamed to avoid conflict)
struct ServiceClientInfo {
  std::string service_name; // metadata only
  void *client_impl;        // ClientImpl* - 真实唯一标识
  int response_listener_id; // CreateSessionServer 返回值（NOT a sessionId!）
  int request_session_id; // OpenSession 返回值（真实 sessionId，-1 = 未连接）
  std::string peer_network_id; // Phase 2.1: env; Phase 2.2: Discovery
  std::string session_name;    // dsoftbus session name

  // ⚠️ CRITICAL: sessionId 来源规则
  // - response_listener_id: CreateSessionServer 返回值（仅表示监听器注册）
  // - request_session_id: OpenSession 返回值（真实的通信 sessionId）
  // 当 Server 向 Client 发送响应时，使用的是 OnSessionOpened 提供的 sessionId
};

// ============================================================================
// Global State (使用指针作为 key，避免同名 service 问题)
// ============================================================================

static std::unordered_map<void *, ServiceServerInfo> g_services; // key = service_impl
static std::unordered_map<void *, ServiceClientInfo> g_clients;   // key = client_impl
static std::mutex g_service_mutex;

// Session -> Impl 反向映射（用于回调路由）
static std::unordered_map<int, void *>
    g_session_to_service; // sessionId -> service_impl
static std::unordered_map<int, void *>
    g_session_to_client; // sessionId -> client_impl

// ============================================================================
// Forward Declarations
// ============================================================================

static int on_session_opened(int sessionId, int result);
static void on_session_closed(int sessionId);
static void on_bytes_received(int sessionId, const void *data,
                              unsigned int dataLen);

// Session listener callbacks
static ISessionListener g_service_client_listener = {
    on_session_opened, // OnSessionOpened
    on_session_closed, // OnSessionClosed
    on_bytes_received, // OnBytesReceived
    nullptr,           // OnMessageReceived
    nullptr,           // OnStreamReceived
    nullptr,           // OnQosEvent (6th field)
};

// ============================================================================
// Helper Functions
// ============================================================================

// 查找 Service by session_id
static ServiceImpl *find_service_by_session(int sessionId) {
  std::lock_guard<std::mutex> lock(g_service_mutex);
  auto it = g_session_to_service.find(sessionId);
  if (it == g_session_to_service.end()) {
    return nullptr;
  }
  return static_cast<ServiceImpl *>(it->second);
}

// 查找 Client by session_id
static ClientImpl *find_client_by_session(int sessionId) {
  std::lock_guard<std::mutex> lock(g_service_mutex);
  auto it = g_session_to_client.find(sessionId);
  if (it == g_session_to_client.end()) {
    return nullptr;
  }
  return static_cast<ClientImpl *>(it->second);
}

// 查找 Service by impl pointer
[[maybe_unused]]
static ServiceServerInfo *find_service_by_impl(void *service_impl) {
  std::lock_guard<std::mutex> lock(g_service_mutex);
  auto it = g_services.find(service_impl);
  if (it == g_services.end()) {
    return nullptr;
  }
  return &it->second;
}

// 查找 Client by impl pointer
[[maybe_unused]]
static ServiceClientInfo *find_client_by_impl(void *client_impl) {
  std::lock_guard<std::mutex> lock(g_service_mutex);
  auto it = g_clients.find(client_impl);
  if (it == g_clients.end()) {
    return nullptr;
  }
  return &it->second;
}

// ============================================================================
// Session Callbacks
// ============================================================================

static int on_session_opened(int sessionId, int result) {
  fprintf(stderr,
          "[ServiceClientManager] OnSessionOpened: sessionId=%d, result=%d\n",
          sessionId, result);

  // ⚠️ Session 异常处理：检查连接结果
  if (result != 0) {
    fprintf(stderr, "[ERROR] Session open failed: sessionId=%d, result=%d\n",
            sessionId, result);
    return result; // Propagate error
  }

  std::lock_guard<std::mutex> lock(g_service_mutex);

  // ⚠️ CRITICAL: sessionId 来源规则
  // OnSessionOpened 是建立 sessionId → impl 反向映射的 CORRECT 位置
  //
  // 场景 1: Client 发起的 OpenSession（request_session_id）
  //   - 已经在 send_service_request 中添加到 g_session_to_client
  //   - 这里只需确认连接成功
  //
  // 场景 2: 远端 Client 连接到我们的 Service Server
  //   - sessionId 是 FIRST TIME 在这里获得的
  //   - 需要找到对应的 service_impl 并建立映射
  //
  // STUB MODE WARNING:
  // 当前 stub 的 OpenSession 返回值是伪造的（100, 101, ...）
  // OnSessionOpened 可能不会被调用，或 sessionId 不匹配
  // Phase 2.2 使用真实 libsoftbus_client.so 时，这个回调会被正确调用

  // Check if this is a client request session (already in mapping from
  // send_service_request)
  auto client_it = g_session_to_client.find(sessionId);
  if (client_it != g_session_to_client.end()) {
    ClientImpl *client = static_cast<ClientImpl *>(client_it->second);
    fprintf(stderr,
            "[ServiceClientManager] Client request session confirmed: "
            "service=%s, sessionId=%d\n",
            client->service_name.c_str(), sessionId);
    return 0; // Success
  }

  // TODO Phase 2.2: This is a remote client connecting to our service server
  // We need to:
  // 1. Identify which service this session belongs to (by session name)
  // 2. Add mapping: g_session_to_service[sessionId] = service_impl
  // 3. Register in ServiceServerInfo.client_sessions
  //
  // For Phase 2.1 (stub mode), this path is not triggered
  fprintf(stderr,
          "[INFO] Remote client session opened: sessionId=%d (Phase 2.2 will "
          "map to service)\n",
          sessionId);

  return 0; // Success
}

static void on_session_closed(int sessionId) {
  fprintf(stderr, "[ServiceClientManager] Session closed: sessionId=%d\n",
          sessionId);

  std::lock_guard<std::mutex> lock(g_service_mutex);

  // ⚠️ Session 生命周期异常处理：断开处理

  // 1. Check if this was a service session
  auto service_it = g_session_to_service.find(sessionId);
  if (service_it != g_session_to_service.end()) {
    fprintf(stderr, "[WARN] Service session closed: sessionId=%d\n", sessionId);
    g_session_to_service.erase(service_it);
  }

  // 2. Check if this was a client request session
  auto client_it = g_session_to_client.find(sessionId);
  if (client_it != g_session_to_client.end()) {
    ClientImpl *client = static_cast<ClientImpl *>(client_it->second);

    // Find the ServiceClientInfo and mark for reconnection
    for (auto &pair : g_clients) {
      if (pair.first == client) {
        if (pair.second.request_session_id == sessionId) {
          fprintf(stderr,
                  "[WARN] Client request session closed: service=%s, "
                  "sessionId=%d\n",
                  pair.second.service_name.c_str(), sessionId);
          fprintf(stderr, "[INFO] Marking for auto-reconnect on next "
                          "send_service_request\n");
          pair.second.request_session_id = -1; // Mark for reconnection
        }
        break;
      }
    }

    g_session_to_client.erase(client_it);
  }

  // 3. Update ServiceServerInfo: remove client session from tracking
  for (auto &pair : g_services) {
    auto &info = pair.second;
    auto cs_it = info.client_sessions.find(sessionId);
    if (cs_it != info.client_sessions.end()) {
      fprintf(stderr,
              "[WARN] Removing client session from service tracking: "
              "sessionId=%d\n",
              sessionId);
      info.client_sessions.erase(cs_it);

      // Notify Service: Session closed, pending requests should be marked as failed
      // Service layer should handle timeout for requests that won't receive responses
      ServiceImpl* srv_impl = static_cast<ServiceImpl*>(pair.first);
      if (srv_impl) {
        fprintf(stderr,
                "[INFO] Service '%s' should timeout pending requests for closed session %d\n",
                info.service_name.c_str(), sessionId);
        // Note: Actual request timeout handling is in rmw_wait.cpp (WaitSet timeout)
        // This is just a notification - WaitSet will detect pipe closed if service crashes
      }
    }
  }
}

static void on_bytes_received(int sessionId, const void *data,
                              unsigned int dataLen) {
  fprintf(stderr,
          "[ServiceClientManager] OnBytesReceived: sessionId=%d, len=%u\n",
          sessionId, dataLen);

  if (!data || dataLen < sizeof(ServiceHeader)) {
    fprintf(stderr, "[ERROR] Invalid data: len=%u (expected >= %zu)\n", dataLen,
            sizeof(ServiceHeader));
    return;
  }

  // Parse ServiceHeader
  const ServiceHeader *header = static_cast<const ServiceHeader *>(data);
  if (!header->base.is_valid()) {
    fprintf(stderr, "[ERROR] Invalid message header (magic mismatch)\n");
    return;
  }

  const uint8_t *payload =
      static_cast<const uint8_t *>(data) + sizeof(ServiceHeader);
  size_t payload_len = dataLen - sizeof(ServiceHeader);

  if (header->base.msg_type == MessageType::REQUEST) {
    // Route to Service
    ServiceImpl *srv_impl = find_service_by_session(sessionId);
    if (!srv_impl) {
      fprintf(stderr, "[ERROR] No service found for sessionId=%d\n", sessionId);
      return;
    }

    // ⚠️ Session 异常处理：重复 request_id 检测
    // 检查是否是已知 client session
    {
      std::lock_guard<std::mutex> lock(srv_impl->session_mutex);
      auto cs_it = srv_impl->client_sessions.find(sessionId);
      if (cs_it != srv_impl->client_sessions.end()) {
        // 已知 session - 检查 request_id 是否重复
        int64_t last_id = cs_it->second.data[0]; // Stored as GID data[0]
        if (header->request_id <= last_id) {
          fprintf(stderr,
                  "[WARN] Duplicate or out-of-order request_id: current=%ld, "
                  "last=%ld, session=%d\n",
                  header->request_id, last_id, sessionId);
          // 不拒绝，只警告（允许幂等性重试）
        }
        // 更新 last request_id
        memcpy(cs_it->second.data, &header->request_id, sizeof(int64_t));
      } else {
        // 新 client session - 添加到跟踪
        GID client_gid;
        memcpy(&client_gid.data, header->client_gid, GID_SIZE);
        // 存储 request_id 在 GID.data[0]
        memcpy(client_gid.data, &header->request_id, sizeof(int64_t));
        srv_impl->client_sessions[sessionId] = client_gid;
        fprintf(stderr, "[INFO] New client session registered: sessionId=%d\n",
                sessionId);
      }
    }

    // Push request to queue
    ServiceRequest req;
    req.request_id = header->request_id;
    req.client_session_id = sessionId;
    memcpy(&req.client_gid.data, header->client_gid, GID_SIZE);
    req.message.data.assign(payload, payload + payload_len);
    req.message.timestamp_ns = header->base.timestamp_ns;
    req.message.sequence_number = header->base.sequence_number;

    {
      std::lock_guard<std::mutex> lock(srv_impl->queue_mutex);
      srv_impl->request_queue.push(req);
    }

    // Notify wait (write to pipe)
    char notify = 'R';
    ssize_t n = write(srv_impl->pipe_fd[1], &notify, 1);
    if (n != 1) {
      fprintf(stderr, "[WARN] Failed to notify service wait: %s\n",
              strerror(errno));
    }

    fprintf(stderr,
            "[ServiceClientManager] REQUEST routed to service: %s, "
            "request_id=%ld, session=%d\n",
            srv_impl->service_name.c_str(), req.request_id, sessionId);

  } else if (header->base.msg_type == MessageType::RESPONSE) {
    // Route to Client
    ClientImpl *cli_impl = find_client_by_session(sessionId);
    if (!cli_impl) {
      fprintf(stderr, "[ERROR] No client found for sessionId=%d\n", sessionId);
      return;
    }

    // Push response to queue
    MessageItem resp;
    resp.data.assign(payload, payload + payload_len);
    resp.timestamp_ns = header->base.timestamp_ns;
    resp.sequence_number = static_cast<uint64_t>(header->request_id);

    {
      std::lock_guard<std::mutex> lock(cli_impl->queue_mutex);
      cli_impl->response_queue.push(resp);
    }

    // Notify wait (write to pipe)
    char notify = 'R';
    ssize_t n = write(cli_impl->pipe_fd[1], &notify, 1);
    if (n != 1) {
      fprintf(stderr, "[WARN] Failed to notify client wait: %s\n",
              strerror(errno));
    }

    fprintf(stderr,
            "[ServiceClientManager] RESPONSE routed to client: %s, "
            "request_id=%ld\n",
            cli_impl->service_name.c_str(), header->request_id);
  } else {
    fprintf(stderr, "[WARN] Unknown message type: %d\n",
            static_cast<int>(header->base.msg_type));
  }
}

// ============================================================================
// Service Server API Implementation
// ============================================================================

int create_service_server(const char *service_name, [[maybe_unused]] const char *type_name,
                          void *service_impl) {
  if (!service_name || !service_impl) {
    fprintf(stderr, "[ERROR] create_service_server: Invalid parameters\n");
    return -1;
  }

  (void)try_init_native_token();

  std::lock_guard<std::mutex> lock(g_service_mutex);

  // Check if already exists
  auto it = g_services.find(service_impl);
  if (it != g_services.end()) {
    fprintf(stderr, "[WARN] Service already exists: %s\n", service_name);
    return it->second.listener_id; // Return existing listener_id
  }

  // Generate session name: "com.huawei.dmsdp.ros2.service.<service_name>"
  std::string session_name =
      std::string("com.huawei.dmsdp.ros2.service.") + service_name;

  // Create dsoftbus Session Server（监听请求）
  int listener_id = CreateSessionServer(
      RMW_DSOFTBUS_PACKAGE_NAME, session_name.c_str(), &g_service_client_listener);
  if (listener_id < 0) {
    fprintf(stderr,
            "[ERROR] CreateSessionServer failed for service: %s (ret=%d)\n",
            service_name, listener_id);
    if (listener_id == SOFTBUS_ACCESS_TOKEN_DENIED ||
        listener_id == SOFTBUS_PERMISSION_DENIED ||
        listener_id == SOFTBUS_ERR) {
      fprintf(stderr,
              "[ServiceClientManager] Hint: need AccessToken permission "
              "(ohos.permission.DISTRIBUTED_DATASYNC); "
              "native ELF must set NativeToken (/dev/access_token_id) or run "
              "via HAP '%s'\n",
              RMW_DSOFTBUS_PACKAGE_NAME);
    }
    return -1;
  }

  // Store service info (使用 service_impl 指针作为 key)
  ServiceServerInfo info;
  info.service_name = service_name; // metadata only
  info.service_impl = service_impl;
  info.listener_id =
      listener_id; // NOT a sessionId! Only indicates listener registered
  info.session_name = session_name;
  g_services[service_impl] = info;

  // ⚠️ CRITICAL: DO NOT map listener_id to service_impl in g_session_to_service!
  //
  // CORRECT sessionId mapping happens in OnSessionOpened callback:
  //   OnSessionOpened(int sessionId, ...) {
  //       g_session_to_service[sessionId] = service_impl;  // ← ONLY HERE
  //   }
  //
  // STUB MODE WARNING:
  // Current stub's OnSessionOpened may not provide real sessionIds.
  // For Phase 2.1 stub testing, OnBytesReceived won't be called anyway.
  // Real mapping will be established in Phase 2.2 with real
  // libsoftbus_client.so

  fprintf(stderr,
          "[ServiceClientManager] Created service server: %s, session=%s, "
          "listener_id=%d\n",
          service_name, session_name.c_str(), listener_id);
  fprintf(stderr, "[INFO] NOTE: listener_id is NOT a sessionId. Real "
                  "sessionIds come from OnSessionOpened.\n");

  return listener_id;
}

void destroy_service_server(const char *service_name) {
  // Note: We need service_impl to find the service, but this legacy API only
  // has service_name For now, search by service_name in metadata (not ideal,
  // but maintains API compatibility)

  std::lock_guard<std::mutex> lock(g_service_mutex);

  for (auto it = g_services.begin(); it != g_services.end(); ++it) {
    if (it->second.service_name == service_name) {
      // Close all client sessions
      for (auto &session_pair : it->second.client_sessions) {
        CloseSession(session_pair.first);
        g_session_to_service.erase(session_pair.first);
      }

      // Remove session server
      RemoveSessionServer(RMW_DSOFTBUS_PACKAGE_NAME, it->second.session_name.c_str());

      g_services.erase(it);
      fprintf(stderr, "[ServiceClientManager] Destroyed service server: %s\n",
              service_name);
      return;
    }
  }

  fprintf(stderr, "[WARN] Service not found for destroy: %s\n", service_name);
}

int send_service_response(const char *service_name, int client_session_id,
                          int64_t request_id, const void *response_data,
                          unsigned int len, const uint8_t *service_gid) {
  if (!response_data || len == 0) {
    fprintf(stderr, "[ERROR] send_service_response: Invalid data\n");
    return -1;
  }

  // Build ServiceHeader
  ServiceHeader header;
  header.base.msg_type = MessageType::RESPONSE;
  header.base.sequence_number = static_cast<uint64_t>(request_id);
  header.base.timestamp_ns = get_timestamp_ns();
  header.base.data_length = len;
  header.request_id = request_id;

  if (service_gid) {
    memcpy(header.base.publisher_gid, service_gid, GID_SIZE);
  }

  // Allocate buffer: header + data
  std::vector<uint8_t> buffer(sizeof(ServiceHeader) + len);
  memcpy(buffer.data(), &header, sizeof(ServiceHeader));
  memcpy(buffer.data() + sizeof(ServiceHeader), response_data, len);

  // Send via dsoftbus
  int ret = SendBytes(client_session_id, buffer.data(), buffer.size());
  if (ret != 0) {
    fprintf(stderr, "[ERROR] SendBytes failed for response: ret=%d\n", ret);
    return -1;
  }

  fprintf(stderr,
          "[ServiceClientManager] Sent response: service=%s, request_id=%ld, "
          "session=%d, len=%zu\n",
          service_name, request_id, client_session_id, buffer.size());

  return 0;
}

bool is_service_available(const char *service_name) {
  if (!service_name) {
    return false;
  }

  // Phase 3: Dual check (GraphCache + Session state)
  //
  // Condition 1: Service must exist in GraphCache
  if (GraphCache::instance().count_services(service_name) == 0) {
    fprintf(stderr, "[is_service_available] Service '%s' not found in GraphCache\n", service_name);
    return false;
  }

  // Condition 2: Session must be alive
  auto info = GraphCache::instance().get_service_info(service_name);
  if (!info) {
    fprintf(stderr, "[is_service_available] Service '%s' info not found\n", service_name);
    return false;
  }

  // Check session state
  if (info->session_id < 0) {
    // session_id not set (legacy registration without session tracking)
    fprintf(stderr, "[is_service_available] Service '%s' has no session_id, assuming available\n", service_name);
    return true;  // Fallback: trust GraphCache
  }

  bool session_alive = SessionManager::instance().is_session_alive(info->session_id);
  if (!session_alive) {
    fprintf(stderr, "[is_service_available] Service '%s' session %d is not alive\n",
            service_name, info->session_id);
    return false;
  }

  fprintf(stderr, "[is_service_available] Service '%s' is available (session %d alive)\n",
          service_name, info->session_id);
  return true;
}

// ============================================================================
// Service Client API Implementation
// ============================================================================

int create_service_client(const char *service_name, [[maybe_unused]] const char *type_name,
                          void *client_impl) {
  if (!service_name || !client_impl) {
    fprintf(stderr, "[ERROR] create_service_client: Invalid parameters\n");
    return -1;
  }

  (void)try_init_native_token();

  std::lock_guard<std::mutex> lock(g_service_mutex);

  // Check if already exists
  auto it = g_clients.find(client_impl);
  if (it != g_clients.end()) {
    fprintf(stderr, "[WARN] Client already exists: %s\n", service_name);
    return 0;
  }

  // Generate session names
  std::string session_name =
      std::string("com.huawei.dmsdp.ros2.service.") + service_name;
  std::string response_session = session_name + ".response";

  // Create response receiver Session Server
  int listener_id = CreateSessionServer(
      RMW_DSOFTBUS_PACKAGE_NAME, response_session.c_str(), &g_service_client_listener);
  if (listener_id < 0) {
    fprintf(
        stderr,
        "[ERROR] CreateSessionServer failed for client response: %s (ret=%d)\n",
        service_name, listener_id);
    if (listener_id == SOFTBUS_ACCESS_TOKEN_DENIED ||
        listener_id == SOFTBUS_PERMISSION_DENIED ||
        listener_id == SOFTBUS_ERR) {
      fprintf(stderr,
              "[ServiceClientManager] Hint: need AccessToken permission "
              "(ohos.permission.DISTRIBUTED_DATASYNC); "
              "native ELF must set NativeToken (/dev/access_token_id) or run "
              "via HAP '%s'\n",
              RMW_DSOFTBUS_PACKAGE_NAME);
    }
    return -1;
  }

  // Phase 2.1: Read peer_network_id from environment (权宜之计)
  // Phase 2.2: Will use Discovery API
  const char *peer_id = std::getenv("RMW_DSOFTBUS_SERVICE_PEER_ID");

  // Store client info (使用 client_impl 指针作为 key)
  ServiceClientInfo info;
  info.service_name = service_name; // metadata only
  info.client_impl = client_impl;
  info.response_listener_id =
      listener_id; // NOT a sessionId! Only indicates listener registered
  info.request_session_id = -1; // 延迟连接（在第一次 send_request 时通过
                                // OpenSession 获取真实 sessionId）
  info.peer_network_id = peer_id ? peer_id : "";
  info.session_name = session_name;
  g_clients[client_impl] = info;

  // ⚠️ CRITICAL: DO NOT map listener_id to client_impl in g_session_to_client!
  //
  // CORRECT sessionId mapping happens when:
  // 1. Client sends request via OpenSession → request_session_id is the real
  // sessionId
  // 2. Server sends response → OnSessionOpened provides the sessionId for
  // routing
  //
  // STUB MODE WARNING:
  // Current stub mode doesn't call OnSessionOpened with real sessionIds.
  // For Phase 2.1, this is acceptable since we're only testing code paths.

  fprintf(stderr,
          "[ServiceClientManager] Created service client: %s, listener_id=%d, "
          "peer=%s\n",
          service_name, listener_id, info.peer_network_id.c_str());
  fprintf(stderr, "[INFO] NOTE: listener_id is NOT a sessionId. Real "
                  "sessionIds established on first request.\n");

  return 0;
}

void destroy_service_client(const char *service_name) {
  // Note: We need client_impl to find the client, but this legacy API only has
  // service_name For now, search by service_name in metadata

  std::lock_guard<std::mutex> lock(g_service_mutex);

  for (auto it = g_clients.begin(); it != g_clients.end(); ++it) {
    if (it->second.service_name == service_name) {
      // Close request session if open (真实的 sessionId)
      if (it->second.request_session_id >= 0) {
        CloseSession(it->second.request_session_id);
        g_session_to_client.erase(
            it->second.request_session_id); // Remove real sessionId mapping
      }

      // Remove response listener (NOT removing from g_session_to_client -
      // listener_id was never added)
      RemoveSessionServer(RMW_DSOFTBUS_PACKAGE_NAME,
                          (it->second.session_name + ".response").c_str());

      g_clients.erase(it);
      fprintf(stderr, "[ServiceClientManager] Destroyed service client: %s\n",
              service_name);
      return;
    }
  }

  fprintf(stderr, "[WARN] Client not found for destroy: %s\n", service_name);
}

int send_service_request(const char *service_name, int64_t request_id,
                         const void *request_data, unsigned int len,
                         const uint8_t *client_gid) {
  if (!request_data || len == 0) {
    fprintf(stderr, "[ERROR] send_service_request: Invalid data\n");
    return -1;
  }

  // Find client by service_name (temporary - should use client_impl)
  ServiceClientInfo *client = nullptr;
  {
    std::lock_guard<std::mutex> lock(g_service_mutex);
    for (auto &pair : g_clients) {
      if (pair.second.service_name == service_name) {
        client = &pair.second;
        break;
      }
    }
  }

  if (!client) {
    fprintf(stderr, "[ERROR] Client not found: %s\n", service_name);
    return -1;
  }

  // Phase 2.1: Connect to service if not connected（延迟连接）
  if (client->request_session_id < 0) {
    if (client->peer_network_id.empty()) {
      fprintf(stderr, "[ERROR] RMW_DSOFTBUS_SERVICE_PEER_ID not set\n");
      return -1;
    }

    SessionAttribute attr;
    memset(&attr, 0, sizeof(attr));
    attr.dataType = TYPE_BYTES;

    // ⚠️ CORRECT: OpenSession 返回真实的 sessionId（通信用）
    int session_id =
        OpenSession(client->session_name.c_str(), client->session_name.c_str(),
                    client->peer_network_id.c_str(), "GROUP_ID", &attr);

    if (session_id < 0) {
      fprintf(stderr, "[ERROR] OpenSession failed for service: %s, peer=%s\n",
              service_name, client->peer_network_id.c_str());
      return -1;
    }

    // ⚠️ CRITICAL: sessionId 来源规则 - OpenSession 返回值是 CORRECT 来源
    // 这是真实的通信 sessionId，可以用于 SendBytes
    client->request_session_id = session_id;

    // 建立反向映射：sessionId → client_impl（用于 OnBytesReceived 路由
    // RESPONSE）
    {
      std::lock_guard<std::mutex> lock(g_service_mutex);
      g_session_to_client[session_id] = client->client_impl;
    }

    fprintf(stderr,
            "[ServiceClientManager] Connected to service: %s, session_id=%d "
            "(REAL sessionId from OpenSession)\n",
            service_name, session_id);
    fprintf(stderr,
            "[ServiceClientManager] Established reverse mapping: sessionId %d "
            "-> client_impl %p\n",
            session_id, client->client_impl);
  }

  // Build ServiceHeader + data
  ServiceHeader header;
  header.base.msg_type = MessageType::REQUEST;
  header.base.sequence_number = static_cast<uint64_t>(request_id);
  header.base.timestamp_ns = get_timestamp_ns();
  header.base.data_length = len;
  header.request_id = request_id; // client-local, not global

  if (client_gid) {
    memcpy(header.client_gid, client_gid, GID_SIZE);
  }

  // Allocate buffer: header + data
  std::vector<uint8_t> buffer(sizeof(ServiceHeader) + len);
  memcpy(buffer.data(), &header, sizeof(ServiceHeader));
  memcpy(buffer.data() + sizeof(ServiceHeader), request_data, len);

  // Send via dsoftbus
  int ret = SendBytes(client->request_session_id, buffer.data(), buffer.size());
  if (ret != 0) {
    // ⚠️ Session 异常处理：发送失败，标记需要重连
    fprintf(stderr,
            "[ERROR] SendBytes failed for request: ret=%d, service=%s, "
            "session=%d\n",
            ret, service_name, client->request_session_id);
    fprintf(stderr,
            "[INFO] Marking session for reconnection on next request\n");

    // 标记为未连接，下次 send_request 会自动重连
    client->request_session_id = -1;
    return -1;
  }

  fprintf(stderr,
          "[ServiceClientManager] Sent request: service=%s, request_id=%ld, "
          "session=%d, len=%zu\n",
          service_name, request_id, client->request_session_id, buffer.size());

  return 0;
}

} // namespace rmw_dsoftbus
