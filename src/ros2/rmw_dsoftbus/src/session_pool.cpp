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

#include "rmw_dsoftbus/session_pool.h"
#include "rmw_dsoftbus/types.h"

#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <chrono>
#include <dlfcn.h>

namespace rmw_dsoftbus {

// ============================================================================
// DSoftBus API Type Definitions (for dlopen loading)
// ============================================================================

typedef int (*CreateSessionServer_t)(const char* pkgName, const char* sessionName,
                                      const void* listener);
typedef int (*RemoveSessionServer_t)(const char* pkgName, const char* sessionName);
typedef int (*OpenSession_t)(const char* mySessionName, const char* peerSessionName,
                             const char* peerNetworkId, const char* groupId,
                             const void* attr);
typedef void (*CloseSession_t)(int sessionId);
typedef int (*SendBytes_t)(int sessionId, const void* data, unsigned int dataLen);

// DSoftBus callback types
struct ISessionListener {
    int (*OnSessionOpened)(int sessionId, int result);
    void (*OnSessionClosed)(int sessionId);
    void (*OnBytesReceived)(int sessionId, const void* data, unsigned int dataLen);
    void (*OnMessageReceived)(int sessionId, const void* data, unsigned int dataLen);
    void (*OnStreamReceived)(int sessionId, const void* data, unsigned int dataLen);
    void (*OnQosEvent)(int sessionId, int eventId, int tvCount, const void* tvList);
};

struct SessionAttribute {
    int dataType;
    int linkTypeNum;
    int linkType[2];
};

// DSoftBus API function pointers (loaded via dlopen)
static CreateSessionServer_t g_CreateSessionServer = nullptr;
static RemoveSessionServer_t g_RemoveSessionServer = nullptr;
static OpenSession_t g_OpenSession = nullptr;
static CloseSession_t g_CloseSession = nullptr;
static SendBytes_t g_SendBytes = nullptr;

// ============================================================================
// SessionPool Implementation
// ============================================================================

SessionPool::SessionPool() : initialized_(false), dsoftbus_handle_(nullptr) {
}

SessionPool::~SessionPool() {
    shutdown();
}

int SessionPool::initialize() {
    std::lock_guard<std::mutex> lock(pool_mutex_);

    if (initialized_) {
        fprintf(stderr, "[SessionPool] Already initialized\n");
        return 0;
    }

    fprintf(stderr, "[SessionPool] Initializing SessionPool with dlopen DSoftBus\n");

    // Load DSoftBus library dynamically
    dsoftbus_handle_ = dlopen("/system/lib64/platformsdk/libsoftbus_client.z.so",
                              RTLD_NOW | RTLD_GLOBAL);
    if (!dsoftbus_handle_) {
        fprintf(stderr, "[SessionPool] Failed to dlopen DSoftBus library: %s\n", dlerror());
        // Try alternative path for development/testing
        dsoftbus_handle_ = dlopen("libsoftbus_client.z.so", RTLD_NOW | RTLD_GLOBAL);
        if (!dsoftbus_handle_) {
            fprintf(stderr, "[SessionPool] Failed to dlopen DSoftBus from alternative path: %s\n",
                    dlerror());
            return -1;
        }
    }

    fprintf(stderr, "[SessionPool] DSoftBus library loaded successfully\n");

    // Load DSoftBus API symbols
    g_CreateSessionServer = (CreateSessionServer_t)dlsym(dsoftbus_handle_, "CreateSessionServer");
    g_RemoveSessionServer = (RemoveSessionServer_t)dlsym(dsoftbus_handle_, "RemoveSessionServer");
    g_OpenSession = (OpenSession_t)dlsym(dsoftbus_handle_, "OpenSession");
    g_CloseSession = (CloseSession_t)dlsym(dsoftbus_handle_, "CloseSession");
    g_SendBytes = (SendBytes_t)dlsym(dsoftbus_handle_, "SendBytes");

    if (!g_CreateSessionServer || !g_RemoveSessionServer || !g_OpenSession ||
        !g_CloseSession || !g_SendBytes) {
        fprintf(stderr, "[SessionPool] Failed to load all DSoftBus symbols\n");
        if (!g_CreateSessionServer) fprintf(stderr, "  - CreateSessionServer: missing\n");
        if (!g_RemoveSessionServer) fprintf(stderr, "  - RemoveSessionServer: missing\n");
        if (!g_OpenSession) fprintf(stderr, "  - OpenSession: missing\n");
        if (!g_CloseSession) fprintf(stderr, "  - CloseSession: missing\n");
        if (!g_SendBytes) fprintf(stderr, "  - SendBytes: missing\n");
        dlclose(dsoftbus_handle_);
        dsoftbus_handle_ = nullptr;
        return -1;
    }

    initialized_ = true;
    fprintf(stderr, "[SessionPool] SessionPool initialization complete\n");
    return 0;
}

void SessionPool::shutdown() {
    std::lock_guard<std::mutex> lock(pool_mutex_);

    if (!initialized_) {
        return;
    }

    fprintf(stderr, "[SessionPool] Shutting down SessionPool\n");

    // Close all active sessions
    for (auto& pair : sessions_) {
        close_session_internal(pair.second.session_id);
    }
    sessions_.clear();

    if (dsoftbus_handle_) {
        dlclose(dsoftbus_handle_);
        dsoftbus_handle_ = nullptr;
    }

    initialized_ = false;
    fprintf(stderr, "[SessionPool] SessionPool shutdown complete\n");
}

bool SessionPool::is_initialized() const {
    std::lock_guard<std::mutex> lock(pool_mutex_);
    return initialized_;
}

int SessionPool::get_or_create_session(const std::string& target_network_id,
                                       const std::string& session_name) {
    std::lock_guard<std::mutex> lock(pool_mutex_);

    if (!initialized_) {
        fprintf(stderr, "[SessionPool] Not initialized\n");
        return -1;
    }

    // Check if session already exists
    auto it = sessions_.find(target_network_id);
    if (it != sessions_.end() && it->second.is_active) {
        fprintf(stderr, "[SessionPool] Reusing existing session %d for NetworkID %s\n",
                it->second.session_id, target_network_id.c_str());
        it->second.last_used_ms = get_current_time_ms();
        return it->second.session_id;
    }

    // Create new session
    int session_id = create_session_internal(target_network_id, session_name);
    if (session_id < 0) {
        fprintf(stderr, "[SessionPool] Failed to create session for NetworkID %s\n",
                target_network_id.c_str());
        return -1;
    }

    return session_id;
}

void SessionPool::release_session(int session_id) {
    std::lock_guard<std::mutex> lock(pool_mutex_);

    for (auto it = sessions_.begin(); it != sessions_.end(); ++it) {
        if (it->second.session_id == session_id) {
            close_session_internal(session_id);
            sessions_.erase(it);
            return;
        }
    }
}

bool SessionPool::is_session_active(int session_id) const {
    std::lock_guard<std::mutex> lock(pool_mutex_);

    for (const auto& pair : sessions_) {
        if (pair.second.session_id == session_id && pair.second.is_active) {
            return true;
        }
    }
    return false;
}

std::string SessionPool::get_session_network_id(int session_id) const {
    std::lock_guard<std::mutex> lock(pool_mutex_);

    for (const auto& pair : sessions_) {
        if (pair.second.session_id == session_id) {
            return pair.second.network_id;
        }
    }
    return "";
}

int SessionPool::send_bytes(const std::string& target_network_id,
                            const uint8_t* data, size_t len) {
    std::lock_guard<std::mutex> lock(pool_mutex_);

    if (!initialized_) {
        fprintf(stderr, "[SessionPool] Not initialized\n");
        return -1;
    }

    // Get or create session
    auto it = sessions_.find(target_network_id);
    if (it == sessions_.end() || !it->second.is_active) {
        fprintf(stderr, "[SessionPool] No active session for NetworkID %s\n",
                target_network_id.c_str());
        return -1;
    }

    int session_id = it->second.session_id;
    return send_bytes_on_session(session_id, data, len);
}

int SessionPool::send_bytes_on_session(int session_id,
                                       const uint8_t* data, size_t len) {
    if (!initialized_ || !g_SendBytes) {
        fprintf(stderr, "[SessionPool] Not initialized or SendBytes unavailable\n");
        return -1;
    }

    if (len > RMW_DSOFTBUS_MAX_MESSAGE_SIZE) {
        fprintf(stderr, "[SessionPool] Message too large: %zu bytes (max %d)\n",
                len, RMW_DSOFTBUS_MAX_MESSAGE_SIZE);
        return -1;
    }

    int ret = g_SendBytes(session_id, data, static_cast<unsigned int>(len));
    if (ret != 0) {
        fprintf(stderr, "[SessionPool] SendBytes failed: ret=%d for session_id=%d\n",
                ret, session_id);
        return -1;
    }

    return 0;
}

void SessionPool::set_on_bytes_received_callback(OnBytesReceivedCallback callback) {
    std::lock_guard<std::mutex> lock(callback_mutex_);
    on_bytes_received_ = callback;
}

void SessionPool::set_on_session_state_changed_callback(OnSessionStateChangedCallback callback) {
    std::lock_guard<std::mutex> lock(callback_mutex_);
    on_session_state_changed_ = callback;
}

void SessionPool::cleanup_inactive_sessions(uint64_t timeout_ms) {
    std::lock_guard<std::mutex> lock(pool_mutex_);

    uint64_t now = get_current_time_ms();

    for (auto it = sessions_.begin(); it != sessions_.end(); ) {
        if (it->second.is_active && (now - it->second.last_used_ms) > timeout_ms) {
            fprintf(stderr, "[SessionPool] Cleaning up inactive session %d for NetworkID %s\n",
                    it->second.session_id, it->second.network_id.c_str());
            close_session_internal(it->second.session_id);
            it = sessions_.erase(it);
        } else {
            ++it;
        }
    }
}

void SessionPool::clear_all_sessions() {
    std::lock_guard<std::mutex> lock(pool_mutex_);

    for (auto& pair : sessions_) {
        if (pair.second.is_active) {
            close_session_internal(pair.second.session_id);
        }
    }
    sessions_.clear();
}

size_t SessionPool::get_session_count() const {
    std::lock_guard<std::mutex> lock(pool_mutex_);
    return sessions_.size();
}

// ============================================================================
// Private Helper Methods
// ============================================================================

uint64_t SessionPool::get_current_time_ms() const {
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

int SessionPool::create_session_internal(const std::string& target_network_id,
                                         const std::string& session_name) {
    if (!g_OpenSession) {
        fprintf(stderr, "[SessionPool] OpenSession not loaded\n");
        return -1;
    }

    // Create session attributes
    SessionAttribute attr;
    std::memset(&attr, 0, sizeof(attr));
    attr.dataType = 1; // TYPE_BYTES
    attr.linkTypeNum = 1;
    attr.linkType[0] = 1; // LINK_TYPE_WIFI_WLAN_5G

    // Open session to remote device
    fprintf(stderr, "[SessionPool] Opening session to NetworkID %s with name '%s'\n",
            target_network_id.c_str(), session_name.c_str());

    int session_id = g_OpenSession(session_name.c_str(), session_name.c_str(),
                                   target_network_id.c_str(), "", &attr);

    if (session_id < 0) {
        fprintf(stderr, "[SessionPool] OpenSession failed: ret=%d\n", session_id);
        return -1;
    }

    fprintf(stderr, "[SessionPool] OpenSession succeeded: session_id=%d\n", session_id);

    // Register session entry
    SessionEntry entry;
    entry.session_id = session_id;
    entry.network_id = target_network_id;
    entry.session_name = session_name;
    entry.created_time_ms = get_current_time_ms();
    entry.last_used_ms = entry.created_time_ms;
    entry.is_active = true;

    sessions_[target_network_id] = entry;

    // Invoke callback
    {
        std::lock_guard<std::mutex> cb_lock(callback_mutex_);
        if (on_session_state_changed_) {
            on_session_state_changed_(session_id, true);
        }
    }

    return session_id;
}

void SessionPool::close_session_internal(int session_id) {
    if (!g_CloseSession) {
        return;
    }

    fprintf(stderr, "[SessionPool] Closing session %d\n", session_id);
    g_CloseSession(session_id);

    // Invoke callback
    {
        std::lock_guard<std::mutex> cb_lock(callback_mutex_);
        if (on_session_state_changed_) {
            on_session_state_changed_(session_id, false);
        }
    }
}

}  // namespace rmw_dsoftbus
