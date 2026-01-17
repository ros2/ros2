/**
 * @file transport_backends.cpp
 * @brief 传输后端实现 (KH_TRANS/Session/Socket)
 *
 * 基于 test_trans 中的实现，整合到 rmw_dsoftbus
 */

#include "rmw_dsoftbus/transport_khtrans_backend.hpp"
#include "rmw_dsoftbus/transport_session_backend.hpp"
#include "rmw_dsoftbus/transport_socket_backend.hpp"

#include <rcutils/logging_macros.h>  // Foundation layer logging

#include <dlfcn.h>
#include <cstring>
#include <unistd.h>
#include <chrono>

// ============================================================================
// dsoftbus 类型定义 (来自 session.h 和 kh_trans_data_type.h)
// ============================================================================

enum SessionType {
    TYPE_MESSAGE = 1,
    TYPE_BYTES = 2,
    TYPE_FILE = 4,
    TYPE_STREAM = 8,
};

enum KhTransType_t {
    KH_TRANS_NORMAL = 0,
    KH_TRANS_REDUNDANCY,
    KH_TRANS_FAST_SWITCH,
};

enum KhLaneDelayType_t {
    KH_NO_LIMIT_LANE_DELAY = 0,
    KH_LOW_LANE_DELAY,
    KH_NORMAL_LANE_DELAY,
    KH_HIGH_LANE_DELAY,
};

enum KhLanePacketLossType_t {
    KH_NO_LIMIT_PACKET_LOSS = 0,
    KH_LOW_LANE_PACKET_LOSS,
    KH_NORMAL_LANE_PACKET_LOSS,
    KH_HIGH_LANE_PACKET_LOSS,
};

struct KhTransParam {
    int32_t khTransType;
    int32_t expectDelayType;
    int32_t expectPacketLossType;
};

struct ISessionListener {
    int (*OnSessionOpened)(int sessionId, int result);
    void (*OnSessionClosed)(int sessionId);
    void (*OnBytesReceived)(int sessionId, const void* data, unsigned int dataLen);
    void (*OnMessageReceived)(int sessionId, const void* data, unsigned int dataLen);
    void (*OnStreamReceived)(int sessionId, const void* data, const void* ext, const void* param);
    void (*OnQosEvent)(int sessionId, int eventId, int tvCount, const void* tvList);
};

enum LinkType {
    LINK_TYPE_WIFI_WLAN_5G = 1,
    LINK_TYPE_WIFI_WLAN_2G = 2,
    LINK_TYPE_WIFI_P2P = 3,
    LINK_TYPE_BR = 4,
};

struct BytesAttr {
    int32_t encryptType;
    int32_t padding;
};

union SessionAttrUnion {
    BytesAttr bytesAttr;
};

struct SessionAttribute {
    int32_t dataType;
    int32_t linkTypeNum;
    int32_t linkType[4];
    SessionAttrUnion attr;
};

namespace rmw_dsoftbus {

// ============================================================================
// 全局回调映射 (静态回调 -> 实例方法)
// ============================================================================

// Session ID -> Backend 实例映射
static std::unordered_map<int, KhTransBackend*> g_kh_session_map;
static std::mutex g_kh_map_mutex;

static std::unordered_map<int, SessionBackend*> g_session_map;
static std::mutex g_session_map_mutex;

// ============================================================================
// KhTransBackend 实现
// ============================================================================

KhTransBackend::KhTransBackend() = default;
KhTransBackend::~KhTransBackend() {
    shutdown();
}

bool KhTransBackend::initialize(const char* pkg_name) {
    if (initialized_) return true;

    pkg_name_ = pkg_name ? pkg_name : "";
    if (pkg_name_.empty()) {
        RCUTILS_LOG_ERROR_NAMED("rmw_dsoftbus.khtrans", "ERROR: Invalid pkg_name");
        return false;
    }

    // 加载符号
    if (!load_symbols()) {
        RCUTILS_LOG_ERROR_NAMED("rmw_dsoftbus.khtrans", "Symbol loading failed - backend unavailable");
        return false;
    }

    initialized_ = true;
    RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.khtrans", "Initialized successfully");
    return true;
}

void KhTransBackend::shutdown() {
    if (!initialized_) return;

    // 移除 session server
    if (RemoveKhSessionServer_) {
        RemoveKhSessionServer_(pkg_name_.c_str(), "rmw_transport");
    }

    // 关闭所有会话
    std::lock_guard<std::mutex> lock(sessions_mutex_);
    for (auto& [session_id, state] : session_states_) {
        if (CloseKhSession_) {
            CloseKhSession_(session_id);
        }
    }
    session_states_.clear();

    if (dsoftbus_handle_) {
        dlclose(dsoftbus_handle_);
        dsoftbus_handle_ = nullptr;
    }

    initialized_ = false;
    RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.khtrans", "Shutdown complete");
}

bool KhTransBackend::load_symbols() {
    // 尝试加载 dsoftbus 库
    const char* lib_paths[] = {
        "/system/lib64/libsoftbus_client.z.so",
        "/system/lib64/libsoftbus_server.z.so",
        "libsoftbus_client.z.so",
        nullptr
    };

    for (const char** path = lib_paths; *path != nullptr; ++path) {
        dsoftbus_handle_ = dlopen(*path, RTLD_NOW | RTLD_GLOBAL);
        if (dsoftbus_handle_) {
            RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.khtrans", "Loaded: %s", *path);
            break;
        }
    }

    if (!dsoftbus_handle_) {
        RCUTILS_LOG_ERROR_NAMED("rmw_dsoftbus.khtrans", "ERROR: Failed to load dsoftbus library");
        return false;
    }

    // 加载 KH_TRANS 符号
    CreateKhSessionServer_ = (CreateKhSessionServerFunc)dlsym(dsoftbus_handle_, "CreateKhSessionServer");
    RemoveKhSessionServer_ = (RemoveKhSessionServerFunc)dlsym(dsoftbus_handle_, "RemoveKhSessionServer");
    OpenKhSession_ = (OpenKhSessionFunc)dlsym(dsoftbus_handle_, "OpenKhSession");
    CloseKhSession_ = (CloseKhSessionFunc)dlsym(dsoftbus_handle_, "CloseKhSession");
    KhSendBytes_ = (KhSendBytesFunc)dlsym(dsoftbus_handle_, "KhSendBytes");
    KhGetPeerNetworkId_ = (KhGetPeerNetworkIdFunc)dlsym(dsoftbus_handle_, "KhGetPeerNetworkId");
    GetLocalNodeDeviceInfo_ = (GetLocalNodeDeviceInfoFunc)dlsym(dsoftbus_handle_, "GetLocalNodeDeviceInfo");

    if (!KhSendBytes_) {
        RCUTILS_LOG_WARN_NAMED("rmw_dsoftbus.khtrans", "WARNING: KhSendBytes not found");
        return false;  // KhSendBytes 是关键
    }

    RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.khtrans", "KH_TRANS symbols loaded successfully");
    return true;
}

// ============================================================================
// KhTransBackend 静态回调实现
// ============================================================================

int on_kh_session_opened(int sessionId, int result) {
    std::lock_guard<std::mutex> lock(g_kh_map_mutex);
    auto it = g_kh_session_map.find(sessionId);
    if (it != g_kh_session_map.end() && it->second) {
        it->second->on_session_opened(sessionId, result);
    }
    return 0;  // 接受会话
}

void on_kh_session_closed(int sessionId) {
    std::lock_guard<std::mutex> lock(g_kh_map_mutex);
    auto it = g_kh_session_map.find(sessionId);
    if (it != g_kh_session_map.end() && it->second) {
        it->second->on_session_closed(sessionId);
        g_kh_session_map.erase(it);  // 清理映射
    }
}

void on_kh_bytes_received(int sessionId, const void* data, unsigned int dataLen) {
    std::lock_guard<std::mutex> lock(g_kh_map_mutex);
    auto it = g_kh_session_map.find(sessionId);
    if (it != g_kh_session_map.end() && it->second) {
        it->second->on_bytes_received(sessionId, data, dataLen);
    }
}

static ISessionListener g_kh_listener = {
    .OnSessionOpened = on_kh_session_opened,
    .OnSessionClosed = on_kh_session_closed,
    .OnBytesReceived = on_kh_bytes_received,
    .OnMessageReceived = nullptr,
    .OnStreamReceived = nullptr,
    .OnQosEvent = nullptr,
};

// ============================================================================
// KhTransBackend 实例方法回调
// ============================================================================

void KhTransBackend::on_session_opened(int sessionId, int result) {
    RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.khtrans", "OnSessionOpened: session=%d, result=%d", sessionId, result);

    std::lock_guard<std::mutex> lock(sessions_mutex_);
    auto& state = session_states_[sessionId];
    {
        std::lock_guard<std::mutex> state_lock(state.mutex);
        state.connected = (result == 0);
        state.connect_result = result;
    }
    state.cv.notify_all();
}

void KhTransBackend::on_session_closed(int sessionId) {
    RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.khtrans", "OnSessionClosed: session=%d", sessionId);

    std::lock_guard<std::mutex> lock(sessions_mutex_);
    auto it = session_states_.find(sessionId);
    if (it != session_states_.end()) {
        std::lock_guard<std::mutex> state_lock(it->second.mutex);
        it->second.connected = false;
        it->second.cv.notify_all();
        it->second.recv_cv.notify_all();
    }
}

void KhTransBackend::on_bytes_received(int sessionId, const void* data, unsigned int dataLen) {
    RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.khtrans", "OnBytesReceived: session=%d, len=%u", sessionId, dataLen);

    std::lock_guard<std::mutex> lock(sessions_mutex_);
    auto it = session_states_.find(sessionId);
    if (it != session_states_.end()) {
        std::lock_guard<std::mutex> recv_lock(it->second.recv_mutex);
        // 复制数据到接收缓冲区
        it->second.recv_buffer.assign(static_cast<const uint8_t*>(data),
                                      static_cast<const uint8_t*>(data) + dataLen);
        it->second.recv_cv.notify_all();
    }
}

int KhTransBackend::connect(const char* peer_network_id, int timeout_ms) {
    if (!initialized_ || !OpenKhSession_) {
        RCUTILS_LOG_ERROR_NAMED("rmw_dsoftbus.khtrans", "ERROR: Backend not initialized");
        return -1;
    }

    if (!peer_network_id || strlen(peer_network_id) == 0) {
        RCUTILS_LOG_ERROR_NAMED("rmw_dsoftbus.khtrans", "ERROR: Invalid peer_network_id");
        return -1;
    }

    // 1. 创建本地 session server (如果未创建)
    if (CreateKhSessionServer_) {
        const char* session_name = "rmw_transport";
        int ret = CreateKhSessionServer_(pkg_name_.c_str(), session_name, &g_kh_listener);
        if (ret != 0 && ret != -426442715) {  // -426442715 = 已存在
            RCUTILS_LOG_ERROR_NAMED("rmw_dsoftbus.khtrans", "CreateKhSessionServer failed: %d", ret);
        } else if (ret == 0) {
            RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.khtrans", "Session server created: %s/%s", pkg_name_.c_str(), session_name);
        }
    }

    // 2. 配置 KH_TRANS 参数
    KhTransParam param;
    param.khTransType = KH_TRANS_NORMAL;
    param.expectDelayType = KH_LOW_LANE_DELAY;
    param.expectPacketLossType = KH_NO_LIMIT_PACKET_LOSS;

    RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.khtrans", "Opening session to: %.32s...", peer_network_id);

    // 3. OpenKhSession (异步)
    char network_id_copy[68];
    strncpy(network_id_copy, peer_network_id, sizeof(network_id_copy) - 1);
    network_id_copy[67] = '\0';

    int session_id = OpenKhSession_(
        "rmw_transport",
        "rmw_transport",
        network_id_copy,
        "",  // groupId
        TYPE_BYTES,
        &param
    );

    if (session_id <= 0) {
        RCUTILS_LOG_ERROR_NAMED("rmw_dsoftbus.khtrans", "OpenKhSession failed: %d", session_id);
        return -1;
    }

    RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.khtrans", "OpenKhSession returned session_id=%d, waiting for callback...", session_id);

    // 4. 注册到全局映射
    {
        std::lock_guard<std::mutex> lock(g_kh_map_mutex);
        g_kh_session_map[session_id] = this;
    }

    // 5. 等待 OnSessionOpened 回调
    std::unique_lock<std::mutex> lock(sessions_mutex_);
    auto& state = session_states_[session_id];
    lock.unlock();

    std::unique_lock<std::mutex> state_lock(state.mutex);
    auto deadline = std::chrono::steady_clock::now() + std::chrono::milliseconds(timeout_ms);

    if (!state.cv.wait_until(state_lock, deadline, [&state]() {
        return state.connect_result != -1;
    })) {
        RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.khtrans", "Session open timeout");
        return -1;
    }

    if (state.connect_result == 0) {
        RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.khtrans", "Session connected successfully");
        return session_id;
    } else {
        RCUTILS_LOG_ERROR_NAMED("rmw_dsoftbus.khtrans", "Session open failed with result=%d", state.connect_result);
        return -1;
    }
}

void KhTransBackend::disconnect(int session_id) {
    if (!CloseKhSession_) return;
    CloseKhSession_(session_id);
}

bool KhTransBackend::is_connected(int session_id) {
    std::lock_guard<std::mutex> lock(sessions_mutex_);
    auto it = session_states_.find(session_id);
    if (it == session_states_.end()) return false;
    return it->second.connected;
}

int KhTransBackend::send(int session_id, const void* data, size_t len) {
    if (!KhSendBytes_) return -1;
    if (len > 984) {
        RCUTILS_LOG_ERROR_NAMED("rmw_dsoftbus.khtrans", "ERROR: Data too large %zu > 984", len);
        return -2;
    }
    return KhSendBytes_(session_id, data, static_cast<unsigned int>(len));
}

int KhTransBackend::recv(int session_id, void* buffer, size_t buffer_len, int timeout_ms) {
    std::lock_guard<std::mutex> lock(sessions_mutex_);
    auto it = session_states_.find(session_id);
    if (it == session_states_.end()) {
        RCUTILS_LOG_ERROR_NAMED("rmw_dsoftbus.khtrans", "ERROR: Invalid session_id %d", session_id);
        return -1;
    }

    auto& state = it->second;
    std::unique_lock<std::mutex> recv_lock(state.recv_mutex);

    // 等待数据到达
    auto deadline = std::chrono::steady_clock::now() + std::chrono::milliseconds(timeout_ms);

    if (!state.recv_cv.wait_until(recv_lock, deadline, [&state]() {
        return !state.recv_buffer.empty();
    })) {
        // 超时
        return 0;  // 无数据
    }

    // 复制数据
    size_t copy_len = std::min(buffer_len, state.recv_buffer.size());
    memcpy(buffer, state.recv_buffer.data(), copy_len);

    // 清空缓冲区
    state.recv_buffer.clear();

    return static_cast<int>(copy_len);
}

bool KhTransBackend::is_available() {
    return initialized_ && (KhSendBytes_ != nullptr);
}

// ============================================================================
// SessionBackend 实现
// ============================================================================

SessionBackend::SessionBackend() = default;
SessionBackend::~SessionBackend() {
    shutdown();
}

bool SessionBackend::initialize(const char* pkg_name) {
    if (initialized_) return true;

    pkg_name_ = pkg_name ? pkg_name : "";
    if (pkg_name_.empty()) return false;

    if (!load_symbols()) {
        return false;
    }

    initialized_ = true;
    RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.session", "Initialized successfully");
    return true;
}

void SessionBackend::shutdown() {
    if (!initialized_) return;

    if (RemoveSessionServer_) {
        RemoveSessionServer_(pkg_name_.c_str(), "rmw_transport_session");
    }

    std::lock_guard<std::mutex> lock(sessions_mutex_);
    for (auto& [session_id, state] : session_states_) {
        if (CloseSession_) {
            CloseSession_(session_id);
        }
    }
    session_states_.clear();

    if (dsoftbus_handle_) {
        dlclose(dsoftbus_handle_);
        dsoftbus_handle_ = nullptr;
    }

    initialized_ = false;
    RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.session", "Shutdown complete");
}

bool SessionBackend::load_symbols() {
    const char* lib_paths[] = {
        "/system/lib64/libsoftbus_client.z.so",
        "/system/lib64/libsoftbus_server.z.so",
        "libsoftbus_client.z.so",
        nullptr
    };

    for (const char** path = lib_paths; *path != nullptr; ++path) {
        dsoftbus_handle_ = dlopen(*path, RTLD_NOW | RTLD_GLOBAL);
        if (dsoftbus_handle_) break;
    }

    if (!dsoftbus_handle_) return false;

    CreateSessionServer_ = (CreateSessionServerFunc)dlsym(dsoftbus_handle_, "CreateSessionServer");
    RemoveSessionServer_ = (RemoveSessionServerFunc)dlsym(dsoftbus_handle_, "RemoveSessionServer");
    OpenSession_ = (OpenSessionFunc)dlsym(dsoftbus_handle_, "OpenSession");
    CloseSession_ = (CloseSessionFunc)dlsym(dsoftbus_handle_, "CloseSession");
    SendBytes_ = (SendBytesFunc)dlsym(dsoftbus_handle_, "SendBytes");

    if (!SendBytes_) {
        RCUTILS_LOG_WARN_NAMED("rmw_dsoftbus.session", "WARNING: SendBytes not found");
        return false;
    }

    RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.session", "Session symbols loaded successfully");
    return true;
}

uint16_t SessionBackend::calculate_crc16(const void* data, size_t len) {
    const uint8_t* bytes = static_cast<const uint8_t*>(data);
    uint16_t crc = 0xFFFF;

    for (size_t i = 0; i < len; ++i) {
        crc ^= bytes[i];
        for (int j = 0; j < 8; ++j) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0xA001;
            } else {
                crc >>= 1;
            }
        }
    }
    return crc;
}

// ============================================================================
// SessionBackend 静态回调实现
// ============================================================================

int on_session_opened(int sessionId, int result) {
    std::lock_guard<std::mutex> lock(g_session_map_mutex);
    auto it = g_session_map.find(sessionId);
    if (it != g_session_map.end() && it->second) {
        it->second->on_session_opened(sessionId, result);
    }
    return 0;  // 接受会话
}

void on_session_closed(int sessionId) {
    std::lock_guard<std::mutex> lock(g_session_map_mutex);
    auto it = g_session_map.find(sessionId);
    if (it != g_session_map.end() && it->second) {
        it->second->on_session_closed(sessionId);
        g_session_map.erase(it);
    }
}

void on_bytes_received(int sessionId, const void* data, unsigned int dataLen) {
    std::lock_guard<std::mutex> lock(g_session_map_mutex);
    auto it = g_session_map.find(sessionId);
    if (it != g_session_map.end() && it->second) {
        it->second->on_bytes_received(sessionId, data, dataLen);
    }
}

static ISessionListener g_session_listener = {
    .OnSessionOpened = on_session_opened,
    .OnSessionClosed = on_session_closed,
    .OnBytesReceived = on_bytes_received,
    .OnMessageReceived = nullptr,
    .OnStreamReceived = nullptr,
    .OnQosEvent = nullptr,
};

// ============================================================================
// SessionBackend 实例方法回调
// ============================================================================

void SessionBackend::on_session_opened(int sessionId, int result) {
    RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.session", "OnSessionOpened: session=%d, result=%d", sessionId, result);

    std::lock_guard<std::mutex> lock(sessions_mutex_);
    auto& state = session_states_[sessionId];
    {
        std::lock_guard<std::mutex> state_lock(state.mutex);
        state.connected = (result == 0);
        state.connect_result = result;
    }
    state.cv.notify_all();
}

void SessionBackend::on_session_closed(int sessionId) {
    RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.session", "OnSessionClosed: session=%d", sessionId);

    std::lock_guard<std::mutex> lock(sessions_mutex_);
    auto it = session_states_.find(sessionId);
    if (it != session_states_.end()) {
        std::lock_guard<std::mutex> state_lock(it->second.mutex);
        it->second.connected = false;
        it->second.cv.notify_all();
        it->second.recv_cv.notify_all();
    }
}

void SessionBackend::on_bytes_received(int sessionId, const void* data, unsigned int dataLen) {
    RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.session", "OnBytesReceived: session=%d, len=%u", sessionId, dataLen);

    std::lock_guard<std::mutex> lock(sessions_mutex_);
    auto it = session_states_.find(sessionId);
    if (it != session_states_.end()) {
        std::lock_guard<std::mutex> recv_lock(it->second.recv_mutex);

        // 检测并剥离 KhDataHead
        const void* actual_data = data;
        unsigned int actual_len = dataLen;

        if (dataLen > KH_DATA_HEAD_SIZE + 1) {
            const KhDataHead* head = reinterpret_cast<const KhDataHead*>(data);
            uint32_t expected_len = dataLen - KH_DATA_HEAD_SIZE - 1;

            // 检查是否为带 KhDataHead 的数据
            if (head->dataType == KH_DATA_TYPE_NORMAL &&
                (head->len == expected_len || head->len == expected_len + 1)) {
                actual_data = static_cast<const uint8_t*>(data) + KH_DATA_HEAD_SIZE;
                actual_len = head->len;
                RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.session", "Stripped KhDataHead: index=%u, payload_len=%u",
                       head->index, actual_len);
            }
        }

        // 复制数据到接收缓冲区
        it->second.recv_buffer.assign(static_cast<const uint8_t*>(actual_data),
                                      static_cast<const uint8_t*>(actual_data) + actual_len);
        it->second.recv_cv.notify_all();
    }
}

int SessionBackend::connect(const char* peer_network_id, int timeout_ms) {
    if (!initialized_ || !OpenSession_) {
        RCUTILS_LOG_ERROR_NAMED("rmw_dsoftbus.session", "ERROR: Backend not initialized");
        return -1;
    }

    if (!peer_network_id || strlen(peer_network_id) == 0) {
        RCUTILS_LOG_ERROR_NAMED("rmw_dsoftbus.session", "ERROR: Invalid peer_network_id");
        return -1;
    }

    // 1. 创建本地 session server (如果未创建)
    if (CreateSessionServer_) {
        const char* session_name = "rmw_transport_session";
        int ret = CreateSessionServer_(pkg_name_.c_str(), session_name, &g_session_listener);
        if (ret != 0 && ret != -426442715) {  // -426442715 = 已存在
            RCUTILS_LOG_ERROR_NAMED("rmw_dsoftbus.session", "CreateSessionServer failed: %d", ret);
        } else if (ret == 0) {
            RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.session", "Session server created: %s/%s", pkg_name_.c_str(), session_name);
        }
    }

    // 2. 配置会话属性
    SessionAttribute attr;
    memset(&attr, 0, sizeof(attr));
    attr.dataType = TYPE_BYTES;
    attr.linkTypeNum = 2;
    attr.linkType[0] = LINK_TYPE_WIFI_WLAN_5G;
    attr.linkType[1] = LINK_TYPE_WIFI_WLAN_2G;
    attr.attr.bytesAttr.encryptType = 0;  // 默认加密

    RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.session", "Opening session to: %.32s...", peer_network_id);

    // 3. OpenSession (异步)
    int session_id = OpenSession_(
        "rmw_transport_session",
        "rmw_transport_session",
        peer_network_id,
        "",  // groupId
        &attr
    );

    if (session_id <= 0) {
        RCUTILS_LOG_ERROR_NAMED("rmw_dsoftbus.session", "OpenSession failed: %d", session_id);
        return -1;
    }

    RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.session", "OpenSession returned session_id=%d, waiting for callback...", session_id);

    // 4. 注册到全局映射
    {
        std::lock_guard<std::mutex> lock(g_session_map_mutex);
        g_session_map[session_id] = this;
    }

    // 5. 等待 OnSessionOpened 回调
    std::unique_lock<std::mutex> lock(sessions_mutex_);
    auto& state = session_states_[session_id];
    lock.unlock();

    std::unique_lock<std::mutex> state_lock(state.mutex);
    auto deadline = std::chrono::steady_clock::now() + std::chrono::milliseconds(timeout_ms);

    if (!state.cv.wait_until(state_lock, deadline, [&state]() {
        return state.connect_result != -1;
    })) {
        RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.session", "Session open timeout");
        return -1;
    }

    if (state.connect_result == 0) {
        RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.session", "Session connected successfully");
        return session_id;
    } else {
        RCUTILS_LOG_ERROR_NAMED("rmw_dsoftbus.session", "Session open failed with result=%d", state.connect_result);
        return -1;
    }
}

void SessionBackend::disconnect(int session_id) {
    if (!CloseSession_) return;
    CloseSession_(session_id);
}

bool SessionBackend::is_connected(int session_id) {
    std::lock_guard<std::mutex> lock(sessions_mutex_);
    auto it = session_states_.find(session_id);
    if (it == session_states_.end()) return false;
    return it->second.connected;
}

int SessionBackend::send(int session_id, const void* data, size_t len) {
    if (!SendBytes_) return -1;

    // 添加 KhDataHead
    std::lock_guard<std::mutex> lock(sessions_mutex_);
    auto& state = session_states_[session_id];

    const size_t total_len = KH_DATA_HEAD_SIZE + len + 1;
    std::vector<uint8_t> buffer(total_len);

    // 填充头
    KhDataHead* head = reinterpret_cast<KhDataHead*>(buffer.data());
    head->index = ++state.send_index;
    head->dataType = KH_DATA_TYPE_NORMAL;
    head->crc = calculate_crc16(data, len);
    head->channelTotalPackageNum = state.send_index;
    head->version = 0;
    head->len = static_cast<uint32_t>(len);

    // 复制数据
    memcpy(buffer.data() + KH_DATA_HEAD_SIZE, data, len);
    buffer[total_len - 1] = 0;  // padding

    return SendBytes_(session_id, buffer.data(), static_cast<unsigned int>(total_len));
}

int SessionBackend::recv(int session_id, void* buffer, size_t buffer_len, int timeout_ms) {
    std::lock_guard<std::mutex> lock(sessions_mutex_);
    auto it = session_states_.find(session_id);
    if (it == session_states_.end()) {
        RCUTILS_LOG_ERROR_NAMED("rmw_dsoftbus.session", "ERROR: Invalid session_id %d", session_id);
        return -1;
    }

    auto& state = it->second;
    std::unique_lock<std::mutex> recv_lock(state.recv_mutex);

    // 等待数据到达
    auto deadline = std::chrono::steady_clock::now() + std::chrono::milliseconds(timeout_ms);

    if (!state.recv_cv.wait_until(recv_lock, deadline, [&state]() {
        return !state.recv_buffer.empty();
    })) {
        // 超时
        return 0;  // 无数据
    }

    // 复制数据
    size_t copy_len = std::min(buffer_len, state.recv_buffer.size());
    memcpy(buffer, state.recv_buffer.data(), copy_len);

    // 清空缓冲区
    state.recv_buffer.clear();

    return static_cast<int>(copy_len);
}

bool SessionBackend::is_available() {
    return initialized_ && (SendBytes_ != nullptr);
}

// ============================================================================
// SocketBackend 实现
// ============================================================================

SocketBackend::SocketBackend() = default;
SocketBackend::~SocketBackend() {
    shutdown();
}

bool SocketBackend::initialize(const char* pkg_name) {
    (void)pkg_name;  // Socket 不需要 pkg_name
    initialized_ = true;
    RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.socket", "Initialized (always available)");
    return true;
}

void SocketBackend::shutdown() {
    stop_server();
    initialized_ = false;
}

int SocketBackend::connect(const char* peer_ip, int timeout_ms) {
    // TODO: 实现 TCP 连接 (参考 test_trans/trans_test_socket.c)
    RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.socket", "Connect to %s (timeout %dms)", peer_ip, timeout_ms);
    return 3;  // 临时
}

void SocketBackend::disconnect(int socket_fd) {
    if (socket_fd >= 0) {
        close(socket_fd);
    }
}

bool SocketBackend::is_connected(int socket_fd) {
    std::lock_guard<std::mutex> lock(sockets_mutex_);
    auto it = socket_states_.find(socket_fd);
    if (it == socket_states_.end()) return false;
    return it->second.connected;
}

int SocketBackend::send(int socket_fd, const void* data, size_t len) {
    // TODO: 实现 TCP send
    (void)socket_fd;
    (void)data;
    (void)len;
    return 0;
}

int SocketBackend::recv(int socket_fd, void* buffer, size_t buffer_len, int timeout_ms) {
    // TODO: 实现 TCP recv
    (void)socket_fd;
    (void)buffer;
    (void)buffer_len;
    (void)timeout_ms;
    return 0;
}

int SocketBackend::start_server() {
    // TODO: 实现 TCP 服务器
    return -1;
}

void SocketBackend::stop_server() {
    if (server_fd_ >= 0) {
        close(server_fd_);
        server_fd_ = -1;
    }
}

int SocketBackend::accept_client(int timeout_ms) {
    // TODO: 实现 accept
    (void)timeout_ms;
    return -1;
}

} // namespace rmw_dsoftbus
