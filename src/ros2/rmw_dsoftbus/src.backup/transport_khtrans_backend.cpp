// Copyright (c) 2024 ROS2 KaihongOS Port Project
// Licensed under the Apache License, Version 2.0
//
// KH_TRANS Backend Implementation - KaihongOS Fusion Communication
// Highest priority backend with multi-channel support and fast switching
// Features:
// - KH_TRANS_FAST_SWITCH: Automatic channel switching for best performance
// - Built-in message index tracking (prevents deduplication issues)
// - Low-latency/packet-loss tolerance configuration

#include "rmw_dsoftbus/transport_backend.h"
#include "rmw_dsoftbus/dsoftbus_session.h"

#include <cstdio>
#include <cstring>
#include <mutex>
#include <unordered_map>
#include <vector>
#include <condition_variable>
#include <unistd.h>

#ifdef RMW_DSOFTBUS_USE_REAL_SOFTBUS
#include <dlfcn.h>
#include "kh_trans/kh_trans_data_type.h"
#endif

namespace rmw_dsoftbus
{

// ============================================================================
// KH_TRANS Type Definitions (from kh_trans_data_type.h)
// ============================================================================

#ifndef RMW_DSOFTBUS_USE_REAL_SOFTBUS

// KH_TRANS transmission type
typedef enum {
    KH_TRANS_NORMAL = 0,      // Single channel transmission
    KH_TRANS_REDUNDANCY = 1,  // Multi-channel redundant (not supported yet)
    KH_TRANS_FAST_SWITCH = 2, // Multi-channel with automatic switching
    KH_TRANS_BUTT,
} KhTransType;

// KH_TRANS session side
typedef enum {
    INVALID_SIDE = -1,
    KH_SERVER_SIDE = 0,
    KH_CLIENT_SIDE = 1,
} KhSessionSide;

// KH_TRANS delay type
typedef enum {
    KH_NO_LIMIT_LANE_DELAY = 0,
    KH_LOW_LANE_DELAY = 1,
    KH_NORMAL_LANE_DELAY = 2,
    KH_HIGH_LANE_DELAY = 3,
} KhLaneDelayType;

// KH_TRANS packet loss type
typedef enum {
    KH_NO_LIMIT_PACKET_LOSS = 0,
    KH_LOW_LANE_PACKET_LOSS = 1,
    KH_NORMAL_LANE_PACKET_LOSS = 2,
    KH_HIGH_LANE_PACKET_LOSS = 3,
} KhLanePacketLossType;

// KH_TRANS session option
typedef enum {
    KH_SESSION_OPTION_DELAY_TYPE = 0,
    KH_SESSION_OPTION_RELIABILITY_TYPE = 1,
    KH_SESSION_OPTION_BUTT,
} KhSessionOption;

// KH_TRANS parameters
typedef struct {
    int32_t khTransType;           // KhTransType
    int32_t expectDelayType;       // KhLaneDelayType
    int32_t expectPacketLossType;  // KhLanePacketLossType
} KhTransParam;

#define SOFTBUS_OK 0

#endif  // !RMW_DSOFTBUS_USE_REAL_SOFTBUS

// ============================================================================
// KH_TRANS Backend Implementation
// ============================================================================

class KhTransBackend : public ITransportBackend {
public:
    KhTransBackend() = default;
    ~KhTransBackend() override { shutdown(); }

    // === ITransportBackend Interface ===

    TransportType type() const override { return TransportType::KH_TRANS; }

    const char* name() const override { return "KH_TRANS (KaihongOS Fusion)"; }

    TransportStatus probe() override {
#ifdef RMW_DSOFTBUS_USE_REAL_SOFTBUS
        // Try to load dsoftbus library and check for KH_TRANS API symbols
        void* handle = dlopen("libsoftbus_client.z.so", RTLD_LAZY);
        if (!handle) {
            handle = dlopen("/system/lib64/platformsdk/libsoftbus_client.z.so", RTLD_LAZY);
        }
        if (!handle) {
            handle = dlopen("/system/lib64/libsoftbus_server.z.so", RTLD_LAZY);
        }

        if (!handle) {
            return TransportStatus::UNAVAILABLE;
        }

        // Check for KH_TRANS specific symbols
        void* create_kh = dlsym(handle, "CreateKhSessionServer");
        void* open_kh = dlsym(handle, "OpenKhSession");
        void* send_kh = dlsym(handle, "KhSendBytes");
        dlclose(handle);

        // KH_TRANS requires all three core functions
        if (create_kh && open_kh && send_kh) {
            return TransportStatus::AVAILABLE;
        }

        return TransportStatus::UNAVAILABLE;
#else
        // Stub mode - mark as available for testing
        return TransportStatus::AVAILABLE;
#endif
    }

    bool init(const char* pkg_name) override {
        std::lock_guard<std::mutex> lock(mutex_);

        if (status_ == TransportStatus::READY) {
            return true;
        }

        if (!pkg_name) {
            set_error(-1, "Package name is null");
            return false;
        }

        pkg_name_ = pkg_name;

#ifdef RMW_DSOFTBUS_USE_REAL_SOFTBUS
        if (!load_symbols()) {
            status_ = TransportStatus::UNAVAILABLE;
            return false;
        }
#endif

        status_ = TransportStatus::READY;
        fprintf(stderr, "[KhTransBackend] Initialized for package: %s\n", pkg_name);
        return true;
    }

    void shutdown() override {
        std::lock_guard<std::mutex> lock(mutex_);

        // Close all sessions
        for (auto& pair : sessions_) {
#ifdef RMW_DSOFTBUS_USE_REAL_SOFTBUS
            if (close_kh_session_fn_) {
                close_kh_session_fn_(pair.first);
            }
#endif
        }
        sessions_.clear();

        // Remove all servers
        for (auto& pair : servers_) {
#ifdef RMW_DSOFTBUS_USE_REAL_SOFTBUS
            if (remove_kh_server_fn_) {
                remove_kh_server_fn_(pkg_name_.c_str(), pair.first.c_str());
            }
#endif
        }
        servers_.clear();

#ifdef RMW_DSOFTBUS_USE_REAL_SOFTBUS
        if (lib_handle_) {
            dlclose(lib_handle_);
            lib_handle_ = nullptr;
        }
#endif

        status_ = TransportStatus::UNAVAILABLE;
    }

    TransportStatus status() const override { return status_; }

    int create_server(const char* session_name,
                      const TransportCallbacks& callbacks) override {
        std::lock_guard<std::mutex> lock(mutex_);

        if (status_ != TransportStatus::READY) {
            set_error(-1, "Backend not ready");
            return -1;
        }

        if (!session_name) {
            set_error(-1, "Session name is null");
            return -1;
        }

        // Check if already exists
        auto it = servers_.find(session_name);
        if (it != servers_.end()) {
            return it->second.server_id;
        }

        int server_id = next_server_id_++;

#ifdef RMW_DSOFTBUS_USE_REAL_SOFTBUS
        if (create_kh_server_fn_) {
            int ret = create_kh_server_fn_(pkg_name_.c_str(), session_name, &g_kh_listener_);
            if (ret != 0) {
                // Handle "already exists" error
                if (ret == -426442715 && remove_kh_server_fn_) {
                    remove_kh_server_fn_(pkg_name_.c_str(), session_name);
                    usleep(100000);
                    ret = create_kh_server_fn_(pkg_name_.c_str(), session_name, &g_kh_listener_);
                }

                if (ret != 0) {
                    set_error(ret, "CreateKhSessionServer failed");
                    fprintf(stderr, "[KhTransBackend] CreateKhSessionServer failed: %d, using stub\n", ret);
                }
            } else {
                fprintf(stderr, "[KhTransBackend] CreateKhSessionServer succeeded for: %s\n", session_name);
            }
        }
#endif

        ServerInfo info;
        info.server_id = server_id;
        info.session_name = session_name;
        info.callbacks = callbacks;
        servers_[session_name] = info;

        fprintf(stderr, "[KhTransBackend] Created server: %s (id=%d)\n", session_name, server_id);
        return server_id;
    }

    void remove_server(const char* session_name) override {
        std::lock_guard<std::mutex> lock(mutex_);

        if (!session_name) return;

        auto it = servers_.find(session_name);
        if (it == servers_.end()) return;

#ifdef RMW_DSOFTBUS_USE_REAL_SOFTBUS
        if (remove_kh_server_fn_) {
            remove_kh_server_fn_(pkg_name_.c_str(), session_name);
        }
#endif

        servers_.erase(it);
        fprintf(stderr, "[KhTransBackend] Removed server: %s\n", session_name);
    }

    int connect(const char* peer_network_id,
                const char* my_session_name,
                const char* peer_session_name,
                const TransportConfig& config,
                const TransportCallbacks& callbacks) override {
        std::lock_guard<std::mutex> lock(mutex_);

        if (status_ != TransportStatus::READY) {
            set_error(-1, "Backend not ready");
            return -1;
        }

        if (!peer_network_id || !my_session_name) {
            set_error(-1, "Invalid parameters");
            return -1;
        }

        if (!peer_session_name) {
            peer_session_name = my_session_name;
        }

        int session_id = -1;

#ifdef RMW_DSOFTBUS_USE_REAL_SOFTBUS
        if (open_kh_session_fn_) {
            // Set up KH_TRANS parameters based on config
            KhTransParam kh_param;
            memset(&kh_param, 0, sizeof(kh_param));

            // Map TransportConfig to KhTransParam
            switch (config.kh_mode) {
                case KhTransMode::NORMAL:
                    kh_param.khTransType = KH_TRANS_NORMAL;
                    break;
                case KhTransMode::REDUNDANCY:
                    kh_param.khTransType = KH_TRANS_REDUNDANCY;
                    break;
                case KhTransMode::FAST_SWITCH:
                default:
                    kh_param.khTransType = KH_TRANS_FAST_SWITCH;
                    break;
            }

            kh_param.expectDelayType = config.kh_delay_type;
            kh_param.expectPacketLossType = config.kh_packet_loss_type;

            // OpenKhSession uses non-const char* for networkId and groupId
            char network_id_buf[128];
            char group_id_buf[64] = "";
            strncpy(network_id_buf, peer_network_id, sizeof(network_id_buf) - 1);

            // OpenKhSession is synchronous
            session_id = open_kh_session_fn_(
                my_session_name,
                peer_session_name,
                network_id_buf,
                group_id_buf,
                TYPE_BYTES,  // SessionType from session.h
                &kh_param
            );

            if (session_id <= 0) {
                set_error(session_id, "OpenKhSession failed");
                fprintf(stderr, "[KhTransBackend] OpenKhSession failed: %d\n", session_id);
                return session_id;
            }

            fprintf(stderr, "[KhTransBackend] OpenKhSession succeeded: session=%d, mode=%d\n",
                    session_id, kh_param.khTransType);

            // Set KH_TRANS type if we have the setter
            if (set_kh_trans_type_fn_ && kh_param.khTransType != KH_TRANS_NORMAL) {
                set_kh_trans_type_fn_(session_id, static_cast<KhTransType>(kh_param.khTransType));
            }
        } else {
            session_id = next_session_id_++;
        }
#else
        session_id = next_session_id_++;
#endif

        SessionInfo info;
        info.session_id = session_id;
        info.session_name = my_session_name;
        info.peer_network_id = peer_network_id;
        info.state = ConnectionState::CONNECTED;
        info.callbacks = callbacks;
        info.send_index = 0;
        info.kh_mode = config.kh_mode;
        sessions_[session_id] = info;

        fprintf(stderr, "[KhTransBackend] Connected to %s (session=%d, mode=%d)\n",
                peer_network_id, session_id, static_cast<int>(config.kh_mode));
        return session_id;
    }

    void disconnect(int handle) override {
        std::lock_guard<std::mutex> lock(mutex_);

        auto it = sessions_.find(handle);
        if (it == sessions_.end()) return;

#ifdef RMW_DSOFTBUS_USE_REAL_SOFTBUS
        if (close_kh_session_fn_) {
            close_kh_session_fn_(handle);
        }
#endif

        sessions_.erase(it);
        fprintf(stderr, "[KhTransBackend] Disconnected session %d\n", handle);
    }

    int send(int handle, const void* data, size_t len) override {
        std::lock_guard<std::mutex> lock(mutex_);

        auto it = sessions_.find(handle);
        if (it == sessions_.end() || it->second.state != ConnectionState::CONNECTED) {
            set_error(-1, "Session not connected");
            return -1;
        }

        int ret = 0;

#ifdef RMW_DSOFTBUS_USE_REAL_SOFTBUS
        if (kh_send_bytes_fn_) {
            // KhSendBytes has built-in index tracking for deduplication
            // No need for manual KhDataHead prefix like with SendBytes
            ret = kh_send_bytes_fn_(handle, data, static_cast<unsigned int>(len));
            if (ret != SOFTBUS_OK) {
                set_error(ret, "KhSendBytes failed");
                fprintf(stderr, "[KhTransBackend] KhSendBytes failed: session=%d, ret=%d\n", handle, ret);
            } else {
                it->second.send_index++;  // Track locally for debugging
            }
        }
#else
        (void)data;
        (void)len;
#endif

        return ret;
    }

    int send_message(int handle, const void* data, size_t len) override {
        std::lock_guard<std::mutex> lock(mutex_);

        auto it = sessions_.find(handle);
        if (it == sessions_.end() || it->second.state != ConnectionState::CONNECTED) {
            set_error(-1, "Session not connected");
            return -1;
        }

        int ret = 0;

#ifdef RMW_DSOFTBUS_USE_REAL_SOFTBUS
        if (kh_send_message_fn_) {
            ret = kh_send_message_fn_(handle, data, static_cast<unsigned int>(len));
            if (ret != SOFTBUS_OK) {
                set_error(ret, "KhSendMessage failed");
            }
        }
#else
        (void)data;
        (void)len;
#endif

        return ret;
    }

    bool is_connected(int handle) const override {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = sessions_.find(handle);
        return it != sessions_.end() && it->second.state == ConnectionState::CONNECTED;
    }

    bool get_handle_info(int handle, TransportHandle& info) const override {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = sessions_.find(handle);
        if (it == sessions_.end()) return false;

        info.handle_id = handle;
        info.backend_type = TransportType::KH_TRANS;
        info.state = it->second.state;
        info.session_name = it->second.session_name;
        info.peer_network_id = it->second.peer_network_id;
        info.send_index = it->second.send_index;
        return true;
    }

    int last_error() const override { return last_error_; }
    const char* last_error_msg() const override { return last_error_msg_.c_str(); }

private:
    // === Internal Types ===

    struct SessionInfo {
        int session_id;
        std::string session_name;
        std::string peer_network_id;
        ConnectionState state{ConnectionState::DISCONNECTED};
        TransportCallbacks callbacks;
        uint32_t send_index{0};
        KhTransMode kh_mode{KhTransMode::FAST_SWITCH};
    };

    struct ServerInfo {
        int server_id;
        std::string session_name;
        TransportCallbacks callbacks;
    };

    // === Symbol Loading ===

#ifdef RMW_DSOFTBUS_USE_REAL_SOFTBUS
    bool load_symbols() {
        const char* lib_paths[] = {
            "/system/lib64/platformsdk/libsoftbus_client.z.so",
            "/system/lib64/libsoftbus_client.z.so",
            "/system/lib64/libsoftbus_server.z.so",
            "libsoftbus_client.z.so",
            nullptr
        };

        for (int i = 0; lib_paths[i]; ++i) {
            lib_handle_ = dlopen(lib_paths[i], RTLD_LAZY | RTLD_GLOBAL);
            if (lib_handle_) {
                fprintf(stderr, "[KhTransBackend] Loaded library: %s\n", lib_paths[i]);
                break;
            }
        }

        if (!lib_handle_) {
            set_error(-1, dlerror());
            return false;
        }

        // Load KH_TRANS API symbols
        create_kh_server_fn_ = (CreateKhServerFn)dlsym(lib_handle_, "CreateKhSessionServer");
        remove_kh_server_fn_ = (RemoveKhServerFn)dlsym(lib_handle_, "RemoveKhSessionServer");
        open_kh_session_fn_ = (OpenKhSessionFn)dlsym(lib_handle_, "OpenKhSession");
        close_kh_session_fn_ = (CloseKhSessionFn)dlsym(lib_handle_, "CloseKhSession");
        kh_send_bytes_fn_ = (KhSendBytesFn)dlsym(lib_handle_, "KhSendBytes");
        kh_send_message_fn_ = (KhSendMessageFn)dlsym(lib_handle_, "KhSendMessage");
        get_kh_trans_type_fn_ = (GetKhTransTypeFn)dlsym(lib_handle_, "GetKhTransType");
        set_kh_trans_type_fn_ = (SetKhTransTypeFn)dlsym(lib_handle_, "SetKhTransType");

        fprintf(stderr, "[KhTransBackend] Symbols: CreateKhSessionServer=%p, OpenKhSession=%p, KhSendBytes=%p\n",
                (void*)create_kh_server_fn_, (void*)open_kh_session_fn_, (void*)kh_send_bytes_fn_);

        // Core KH_TRANS functions are required
        bool available = (create_kh_server_fn_ != nullptr &&
                         open_kh_session_fn_ != nullptr &&
                         kh_send_bytes_fn_ != nullptr);

        if (!available) {
            fprintf(stderr, "[KhTransBackend] KH_TRANS API not available, falling back\n");
        }

        return available;
    }

    // Function pointer types for KH_TRANS API
    typedef int32_t (*CreateKhServerFn)(const char*, const char*, const ISessionListener*);
    typedef int32_t (*RemoveKhServerFn)(const char*, const char*);
    typedef int32_t (*OpenKhSessionFn)(const char*, const char*, char*, char*, int, KhTransParam*);
    typedef int32_t (*CloseKhSessionFn)(int32_t);
    typedef int32_t (*KhSendBytesFn)(int32_t, const void*, unsigned int);
    typedef int32_t (*KhSendMessageFn)(int32_t, const void*, unsigned int);
    typedef int32_t (*GetKhTransTypeFn)(int32_t, KhTransType*);
    typedef int32_t (*SetKhTransTypeFn)(int32_t, KhTransType);

    // Function pointers
    CreateKhServerFn create_kh_server_fn_{nullptr};
    RemoveKhServerFn remove_kh_server_fn_{nullptr};
    OpenKhSessionFn open_kh_session_fn_{nullptr};
    CloseKhSessionFn close_kh_session_fn_{nullptr};
    KhSendBytesFn kh_send_bytes_fn_{nullptr};
    KhSendMessageFn kh_send_message_fn_{nullptr};
    GetKhTransTypeFn get_kh_trans_type_fn_{nullptr};
    SetKhTransTypeFn set_kh_trans_type_fn_{nullptr};

    void* lib_handle_{nullptr};

    // Static listener for callbacks (uses same ISessionListener as Session API)
    static ISessionListener g_kh_listener_;
#endif

    // === Helper Functions ===

    void set_error(int code, const char* msg) {
        last_error_ = code;
        last_error_msg_ = msg ? msg : "Unknown error";
    }

    // === State ===

    mutable std::mutex mutex_;
    TransportStatus status_{TransportStatus::UNAVAILABLE};
    std::string pkg_name_;

    std::unordered_map<int, SessionInfo> sessions_;
    std::unordered_map<std::string, ServerInfo> servers_;

    int next_session_id_{1};
    int next_server_id_{1};

    int last_error_{0};
    std::string last_error_msg_;
};

#ifdef RMW_DSOFTBUS_USE_REAL_SOFTBUS
// Static listener initialization
ISessionListener KhTransBackend::g_kh_listener_ = {
    .OnSessionOpened = nullptr,  // TODO: Implement callback routing
    .OnSessionClosed = nullptr,
    .OnBytesReceived = nullptr,
    .OnMessageReceived = nullptr,
    .OnStreamReceived = nullptr,
    .OnQosEvent = nullptr,
};
#endif

// ============================================================================
// Factory Function for KH_TRANS Backend
// ============================================================================

std::unique_ptr<ITransportBackend> create_khtrans_backend() {
    return std::make_unique<KhTransBackend>();
}

}  // namespace rmw_dsoftbus
