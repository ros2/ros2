// Copyright (c) 2024 ROS2 KaihongOS Port Project
// Licensed under the Apache License, Version 2.0
//
// Session Backend Implementation - dsoftbus Session API v1.0
// This is the classic/legacy backend, used as fallback when other backends unavailable

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
#endif

namespace rmw_dsoftbus
{

// ============================================================================
// Session Backend Implementation
// ============================================================================

class SessionBackend : public ITransportBackend {
public:
    SessionBackend() = default;
    ~SessionBackend() override { shutdown(); }

    // === ITransportBackend Interface ===

    TransportType type() const override { return TransportType::SESSION; }

    const char* name() const override { return "Session API v1.0"; }

    TransportStatus probe() override {
#ifdef RMW_DSOFTBUS_USE_REAL_SOFTBUS
        // Try to load dsoftbus library and check for Session API symbols
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

        // Check for required symbols
        void* sym = dlsym(handle, "CreateSessionServer");
        dlclose(handle);

        return sym ? TransportStatus::AVAILABLE : TransportStatus::UNAVAILABLE;
#else
        // Stub mode always available for testing
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
        fprintf(stderr, "[SessionBackend] Initialized for package: %s\n", pkg_name);
        return true;
    }

    void shutdown() override {
        std::lock_guard<std::mutex> lock(mutex_);

        // Close all sessions
        for (auto& pair : sessions_) {
#ifdef RMW_DSOFTBUS_USE_REAL_SOFTBUS
            if (close_session_fn_) {
                close_session_fn_(pair.first);
            }
#endif
        }
        sessions_.clear();

        // Remove all servers
        for (auto& pair : servers_) {
#ifdef RMW_DSOFTBUS_USE_REAL_SOFTBUS
            if (remove_server_fn_) {
                remove_server_fn_(pkg_name_.c_str(), pair.first.c_str());
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
        if (create_server_fn_) {
            // Set up our static listener that routes to callbacks
            int ret = create_server_fn_(pkg_name_.c_str(), session_name, &g_session_listener_);
            if (ret != 0) {
                // Handle "already exists" error
                if (ret == -426442715 && remove_server_fn_) {
                    remove_server_fn_(pkg_name_.c_str(), session_name);
                    usleep(100000);
                    ret = create_server_fn_(pkg_name_.c_str(), session_name, &g_session_listener_);
                }

                if (ret != 0) {
                    set_error(ret, "CreateSessionServer failed");
                    // Still succeed with stub mode
                    fprintf(stderr, "[SessionBackend] CreateSessionServer failed (%d), using stub\n", ret);
                }
            }
        }
#endif

        ServerInfo info;
        info.server_id = server_id;
        info.session_name = session_name;
        info.callbacks = callbacks;
        servers_[session_name] = info;

        fprintf(stderr, "[SessionBackend] Created server: %s (id=%d)\n", session_name, server_id);
        return server_id;
    }

    void remove_server(const char* session_name) override {
        std::lock_guard<std::mutex> lock(mutex_);

        if (!session_name) return;

        auto it = servers_.find(session_name);
        if (it == servers_.end()) return;

#ifdef RMW_DSOFTBUS_USE_REAL_SOFTBUS
        if (remove_server_fn_) {
            remove_server_fn_(pkg_name_.c_str(), session_name);
        }
#endif

        servers_.erase(it);
        fprintf(stderr, "[SessionBackend] Removed server: %s\n", session_name);
    }

    int connect(const char* peer_network_id,
                const char* my_session_name,
                const char* peer_session_name,
                const TransportConfig& config,
                const TransportCallbacks& callbacks) override {
        std::unique_lock<std::mutex> lock(mutex_);

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
        if (open_session_fn_) {
            SessionAttribute attr;
            memset(&attr, 0, sizeof(attr));
            attr.dataType = TYPE_BYTES;
            attr.linkTypeNum = 4;
            attr.linkType[0] = LINK_TYPE_WIFI_WLAN_5G;
            attr.linkType[1] = LINK_TYPE_WIFI_WLAN_2G;
            attr.linkType[2] = LINK_TYPE_WIFI_P2P;
            attr.linkType[3] = LINK_TYPE_BR;

            session_id = open_session_fn_(my_session_name, peer_session_name,
                                          peer_network_id, "", &attr);

            if (session_id <= 0) {
                set_error(session_id, "OpenSession failed");
                return session_id;
            }

            // Wait for OnSessionOpened callback
            PendingConnect pending;
            pending.session_id = session_id;
            pending_connects_[session_id] = &pending;

            bool wait_result = pending.cv.wait_for(
                lock,  // Use the unique_lock object
                std::chrono::milliseconds(config.timeout_ms > 0 ? config.timeout_ms : 5000),
                [&pending]() { return pending.completed; });

            pending_connects_.erase(session_id);

            if (!wait_result || pending.result != 0) {
                if (close_session_fn_) {
                    close_session_fn_(session_id);
                }
                set_error(pending.result, "Session open failed or timed out");
                return -1;
            }
        } else {
            // Stub mode
            session_id = next_session_id_++;
        }
#else
        // Stub mode
        session_id = next_session_id_++;
#endif

        SessionInfo info;
        info.session_id = session_id;
        info.session_name = my_session_name;
        info.peer_network_id = peer_network_id;
        info.state = ConnectionState::CONNECTED;
        info.callbacks = callbacks;
        info.send_index = 0;
        sessions_[session_id] = info;

        fprintf(stderr, "[SessionBackend] Connected to %s (session=%d)\n",
                peer_network_id, session_id);
        return session_id;
    }

    void disconnect(int handle) override {
        std::lock_guard<std::mutex> lock(mutex_);

        auto it = sessions_.find(handle);
        if (it == sessions_.end()) return;

#ifdef RMW_DSOFTBUS_USE_REAL_SOFTBUS
        if (close_session_fn_) {
            close_session_fn_(handle);
        }
#endif

        sessions_.erase(it);
        fprintf(stderr, "[SessionBackend] Disconnected session %d\n", handle);
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
        if (send_bytes_fn_) {
            ret = send_bytes_fn_(handle, data, static_cast<unsigned int>(len));
            if (ret != 0) {
                set_error(ret, "SendBytes failed");
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
        if (send_message_fn_) {
            ret = send_message_fn_(handle, data, static_cast<unsigned int>(len));
            if (ret != 0) {
                set_error(ret, "SendMessage failed");
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
        info.backend_type = TransportType::SESSION;
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
    };

    struct ServerInfo {
        int server_id;
        std::string session_name;
        TransportCallbacks callbacks;
    };

    struct PendingConnect {
        int session_id{-1};
        int result{-1};
        bool completed{false};
        std::condition_variable cv;
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
                fprintf(stderr, "[SessionBackend] Loaded library: %s\n", lib_paths[i]);
                break;
            }
        }

        if (!lib_handle_) {
            set_error(-1, dlerror());
            return false;
        }

        create_server_fn_ = (CreateServerFn)dlsym(lib_handle_, "CreateSessionServer");
        remove_server_fn_ = (RemoveServerFn)dlsym(lib_handle_, "RemoveSessionServer");
        open_session_fn_ = (OpenSessionFn)dlsym(lib_handle_, "OpenSession");
        close_session_fn_ = (CloseSessionFn)dlsym(lib_handle_, "CloseSession");
        send_bytes_fn_ = (SendBytesFn)dlsym(lib_handle_, "SendBytes");
        send_message_fn_ = (SendMessageFn)dlsym(lib_handle_, "SendMessage");

        return create_server_fn_ != nullptr;
    }

    // Function pointer types
    typedef int (*CreateServerFn)(const char*, const char*, const ISessionListener*);
    typedef int (*RemoveServerFn)(const char*, const char*);
    typedef int (*OpenSessionFn)(const char*, const char*, const char*, const char*, const SessionAttribute*);
    typedef void (*CloseSessionFn)(int);
    typedef int (*SendBytesFn)(int, const void*, unsigned int);
    typedef int (*SendMessageFn)(int, const void*, unsigned int);

    // Function pointers
    CreateServerFn create_server_fn_{nullptr};
    RemoveServerFn remove_server_fn_{nullptr};
    OpenSessionFn open_session_fn_{nullptr};
    CloseSessionFn close_session_fn_{nullptr};
    SendBytesFn send_bytes_fn_{nullptr};
    SendMessageFn send_message_fn_{nullptr};

    void* lib_handle_{nullptr};

    // Static listener for callbacks
    static ISessionListener g_session_listener_;
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
    std::unordered_map<int, PendingConnect*> pending_connects_;

    int next_session_id_{1};
    int next_server_id_{1};

    int last_error_{0};
    std::string last_error_msg_;
};

#ifdef RMW_DSOFTBUS_USE_REAL_SOFTBUS
// Static listener - will be initialized in implementation
ISessionListener SessionBackend::g_session_listener_ = {
    .OnSessionOpened = nullptr,  // TODO: Implement callback routing
    .OnSessionClosed = nullptr,
    .OnBytesReceived = nullptr,
    .OnMessageReceived = nullptr,
    .OnStreamReceived = nullptr,
    .OnQosEvent = nullptr,
};
#endif

// ============================================================================
// Factory Function for Session Backend
// ============================================================================

std::unique_ptr<ITransportBackend> create_session_backend() {
    return std::make_unique<SessionBackend>();
}

}  // namespace rmw_dsoftbus
