// Copyright (c) 2024 ROS2 KaihongOS Port Project
// Licensed under the Apache License, Version 2.0
//
// Socket Backend Implementation - dsoftbus Socket API v2.0
// New generation API with better QoS support and synchronous binding

#include "rmw_dsoftbus/transport_backend.h"
#include "rmw_dsoftbus/dsoftbus_session.h"  // Include dsoftbus headers

#include <rcutils/logging_macros.h>  // Foundation layer logging

#include <cstring>
#include <mutex>
#include <unordered_map>
#include <vector>
#include <condition_variable>

#ifdef RMW_DSOFTBUS_USE_REAL_SOFTBUS
#include <dlfcn.h>
#endif

namespace rmw_dsoftbus
{

// ============================================================================
// Socket API v2.0 Type Definitions (from trans_type.h and socket.h)
// ============================================================================

#ifndef RMW_DSOFTBUS_USE_REAL_SOFTBUS
// Stub definitions for compilation without dsoftbus SDK

typedef enum {
    DATA_TYPE_MESSAGE = 1,
    DATA_TYPE_BYTES,
    DATA_TYPE_FILE,
    DATA_TYPE_RAW_STREAM,
    DATA_TYPE_VIDEO_STREAM,
    DATA_TYPE_AUDIO_STREAM,
    DATA_TYPE_SLICE_STREAM,
    DATA_TYPE_BUTT,
} TransDataType;

typedef struct {
    char *name;
    char *peerName;
    char *peerNetworkId;
    char *pkgName;
    TransDataType dataType;
} SocketInfo;

typedef struct {
    char *name;
    char *networkId;
    char *pkgName;
    TransDataType dataType;
} PeerSocketInfo;

typedef enum {
    SHUTDOWN_REASON_UNKNOWN,
    SHUTDOWN_REASON_LOCAL,
    SHUTDOWN_REASON_PEER,
    SHUTDOWN_REASON_LNN_CHANGED,
    SHUTDOWN_REASON_CONN_CHANGED,
    SHUTDOWN_REASON_TIMEOUT,
    SHUTDOWN_REASON_SEND_FILE_ERR,
    SHUTDOWN_REASON_RECV_FILE_ERR,
    SHUTDOWN_REASON_RECV_DATA_ERR,
    SHUTDOWN_REASON_UNEXPECTED,
    SHUTDOWN_REASON_SERVICE_DIED,
    SHUTDOWN_REASON_LNN_OFFLINE,
    SHUTDOWN_REASON_LINK_DOWN,
} ShutdownReason;

typedef enum {
    QOS_TYPE_MIN_BW,
    QOS_TYPE_MAX_LATENCY,
    QOS_TYPE_MIN_LATENCY,
    QOS_TYPE_MAX_WAIT_TIMEOUT,
    QOS_TYPE_MAX_BUFFER,
    QOS_TYPE_FIRST_PACKAGE,
    QOS_TYPE_MAX_IDLE_TIMEOUT,
    QOS_TYPE_TRANS_RELIABILITY,
    QOS_TYPE_IS_USER_ENCRYPT,
    QOS_TYPE_BUTT,
} QosType;

typedef struct {
    QosType qos;
    int32_t value;
} QosTV;

typedef enum {
    QOS_SATISFIED,
    QOS_NOT_SATISFIED,
} QoSEvent;

typedef struct {
    char *buf;
    int bufLen;
} StreamData;

typedef struct {
    int32_t frameType;
    int64_t timeStamp;
    int32_t seqNum;
    int32_t seqSubNum;
    int32_t level;
    int32_t bitMap;
    int32_t tvCount;
    void *tvList;
} StreamFrameInfo;

typedef struct {
    int type;
    const char **files;
    uint32_t fileCnt;
    uint64_t bytesProcessed;
    uint64_t bytesTotal;
    const char *(*UpdateRecvPath)(void);
} FileEvent;

typedef struct {
    void (*OnBind)(int32_t socket, PeerSocketInfo info);
    void (*OnShutdown)(int32_t socket, ShutdownReason reason);
    void (*OnBytes)(int32_t socket, const void *data, uint32_t dataLen);
    void (*OnMessage)(int32_t socket, const void *data, uint32_t dataLen);
    void (*OnStream)(int32_t socket, const StreamData *data, const StreamData *ext, const StreamFrameInfo *param);
    void (*OnFile)(int32_t socket, FileEvent *event);
    void (*OnQos)(int32_t socket, QoSEvent eventId, const QosTV *qos, uint32_t qosCount);
} ISocketListener;

#define SOFTBUS_OK 0

#endif  // !RMW_DSOFTBUS_USE_REAL_SOFTBUS

// ============================================================================
// Socket Backend Implementation
// ============================================================================

class SocketBackend : public ITransportBackend {
public:
    SocketBackend() = default;
    ~SocketBackend() override { shutdown(); }

    // === ITransportBackend Interface ===

    TransportType type() const override { return TransportType::SOCKET; }

    const char* name() const override { return "Socket API v2.0"; }

    TransportStatus probe() override {
#ifdef RMW_DSOFTBUS_USE_REAL_SOFTBUS
        // Try to load dsoftbus library and check for Socket API v2.0 symbols
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

        // Check for Socket API v2.0 symbols (Socket, Listen, Bind are v2.0 specific)
        void* socket_sym = dlsym(handle, "Socket");
        void* listen_sym = dlsym(handle, "Listen");
        void* bind_sym = dlsym(handle, "Bind");
        dlclose(handle);

        // Socket API v2.0 requires all three symbols
        if (socket_sym && listen_sym && bind_sym) {
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
        RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.socket", "Initialized for package: %s", pkg_name);
        return true;
    }

    void shutdown() override {
        std::lock_guard<std::mutex> lock(mutex_);

        // Shutdown all sockets
        for (auto& pair : sockets_) {
#ifdef RMW_DSOFTBUS_USE_REAL_SOFTBUS
            if (shutdown_fn_) {
                shutdown_fn_(pair.first);
            }
#endif
        }
        sockets_.clear();
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
            return it->second.socket_fd;
        }

        int socket_fd = -1;

#ifdef RMW_DSOFTBUS_USE_REAL_SOFTBUS
        if (socket_fn_ && listen_fn_) {
            // Create socket
            SocketInfo info;
            memset(&info, 0, sizeof(info));

            // Need to allocate writable strings (Socket API requires non-const)
            char name_buf[256];
            char pkg_buf[256];
            strncpy(name_buf, session_name, sizeof(name_buf) - 1);
            strncpy(pkg_buf, pkg_name_.c_str(), sizeof(pkg_buf) - 1);

            info.name = name_buf;
            info.peerName = nullptr;
            info.peerNetworkId = nullptr;
            info.pkgName = pkg_buf;
            info.dataType = DATA_TYPE_BYTES;

            socket_fd = socket_fn_(info);
            if (socket_fd < 0) {
                set_error(socket_fd, "Socket() failed");
                // Fall through to stub mode
                RCUTILS_LOG_ERROR_NAMED("rmw_dsoftbus.socket", "Socket() failed: %d, using stub", socket_fd);
                socket_fd = next_socket_id_++;
            } else {
                // Set up QoS requirements
                QosTV qos[3];
                qos[0].qos = QOS_TYPE_TRANS_RELIABILITY;
                qos[0].value = 2;  // QOS_RELIABILITY_FULL
                qos[1].qos = QOS_TYPE_MAX_LATENCY;
                qos[1].value = 5000;  // 5 seconds max latency
                qos[2].qos = QOS_TYPE_MAX_WAIT_TIMEOUT;
                qos[2].value = 10000;  // 10 seconds timeout

                int ret = listen_fn_(socket_fd, qos, 3, &g_socket_listener_);
                if (ret != SOFTBUS_OK) {
                    set_error(ret, "Listen() failed");
                    RCUTILS_LOG_ERROR_NAMED("rmw_dsoftbus.socket", "Listen() failed: %d", ret);
                    shutdown_fn_(socket_fd);
                    socket_fd = next_socket_id_++;  // Fall back to stub
                }
            }
        } else {
            socket_fd = next_socket_id_++;
        }
#else
        socket_fd = next_socket_id_++;
#endif

        ServerInfo server_info;
        server_info.socket_fd = socket_fd;
        server_info.session_name = session_name;
        server_info.callbacks = callbacks;
        servers_[session_name] = server_info;

        RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.socket", "Created server: %s (socket=%d)", session_name, socket_fd);
        return socket_fd;
    }

    void remove_server(const char* session_name) override {
        std::lock_guard<std::mutex> lock(mutex_);

        if (!session_name) return;

        auto it = servers_.find(session_name);
        if (it == servers_.end()) return;

#ifdef RMW_DSOFTBUS_USE_REAL_SOFTBUS
        if (shutdown_fn_ && it->second.socket_fd >= 0) {
            shutdown_fn_(it->second.socket_fd);
        }
#endif

        servers_.erase(it);
        RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.socket", "Removed server: %s", session_name);
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

        int socket_fd = -1;

#ifdef RMW_DSOFTBUS_USE_REAL_SOFTBUS
        if (socket_fn_ && bind_fn_) {
            // Create client socket
            char name_buf[256], peer_name_buf[256], peer_nid_buf[128], pkg_buf[256];
            strncpy(name_buf, my_session_name, sizeof(name_buf) - 1);
            strncpy(peer_name_buf, peer_session_name, sizeof(peer_name_buf) - 1);
            strncpy(peer_nid_buf, peer_network_id, sizeof(peer_nid_buf) - 1);
            strncpy(pkg_buf, pkg_name_.c_str(), sizeof(pkg_buf) - 1);

            SocketInfo info;
            memset(&info, 0, sizeof(info));
            info.name = name_buf;
            info.peerName = peer_name_buf;
            info.peerNetworkId = peer_nid_buf;
            info.pkgName = pkg_buf;
            info.dataType = DATA_TYPE_BYTES;

            socket_fd = socket_fn_(info);
            if (socket_fd < 0) {
                set_error(socket_fd, "Socket() failed for client");
                return socket_fd;
            }

            // Set up QoS based on config
            QosTV qos[4];
            int qos_count = 0;

            qos[qos_count].qos = QOS_TYPE_TRANS_RELIABILITY;
            qos[qos_count].value = (config.reliability == TransportReliability::RELIABLE) ? 2 : 1;
            qos_count++;

            if (config.max_latency_ms > 0) {
                qos[qos_count].qos = QOS_TYPE_MAX_LATENCY;
                qos[qos_count].value = config.max_latency_ms;
                qos_count++;
            }

            qos[qos_count].qos = QOS_TYPE_MAX_WAIT_TIMEOUT;
            qos[qos_count].value = config.timeout_ms > 0 ? config.timeout_ms : 5000;
            qos_count++;

            // Bind (synchronous connect)
            int ret = bind_fn_(socket_fd, qos, qos_count, &g_socket_listener_);
            if (ret != SOFTBUS_OK) {
                set_error(ret, "Bind() failed");
                shutdown_fn_(socket_fd);
                return -1;
            }

            RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.socket", "Bind() successful for socket %d", socket_fd);
        } else {
            socket_fd = next_socket_id_++;
        }
#else
        socket_fd = next_socket_id_++;
#endif

        SocketState state;
        state.socket_fd = socket_fd;
        state.session_name = my_session_name;
        state.peer_network_id = peer_network_id;
        state.state = ConnectionState::CONNECTED;
        state.callbacks = callbacks;
        state.send_index = 0;
        sockets_[socket_fd] = state;

        RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.socket", "Connected to %s (socket=%d)",
                peer_network_id, socket_fd);
        return socket_fd;
    }

    void disconnect(int handle) override {
        std::lock_guard<std::mutex> lock(mutex_);

        auto it = sockets_.find(handle);
        if (it == sockets_.end()) return;

#ifdef RMW_DSOFTBUS_USE_REAL_SOFTBUS
        if (shutdown_fn_) {
            shutdown_fn_(handle);
        }
#endif

        sockets_.erase(it);
        RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.socket", "Disconnected socket %d", handle);
    }

    int send(int handle, const void* data, size_t len) override {
        std::lock_guard<std::mutex> lock(mutex_);

        auto it = sockets_.find(handle);
        if (it == sockets_.end() || it->second.state != ConnectionState::CONNECTED) {
            set_error(-1, "Socket not connected");
            return -1;
        }

        int ret = 0;

#ifdef RMW_DSOFTBUS_USE_REAL_SOFTBUS
        if (send_bytes_fn_) {
            ret = send_bytes_fn_(handle, data, static_cast<uint32_t>(len));
            if (ret != SOFTBUS_OK) {
                set_error(ret, "SendBytes() failed");
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

        auto it = sockets_.find(handle);
        if (it == sockets_.end() || it->second.state != ConnectionState::CONNECTED) {
            set_error(-1, "Socket not connected");
            return -1;
        }

        int ret = 0;

#ifdef RMW_DSOFTBUS_USE_REAL_SOFTBUS
        if (send_message_fn_) {
            ret = send_message_fn_(handle, data, static_cast<uint32_t>(len));
            if (ret != SOFTBUS_OK) {
                set_error(ret, "SendMessage() failed");
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
        auto it = sockets_.find(handle);
        return it != sockets_.end() && it->second.state == ConnectionState::CONNECTED;
    }

    bool get_handle_info(int handle, TransportHandle& info) const override {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = sockets_.find(handle);
        if (it == sockets_.end()) return false;

        info.handle_id = handle;
        info.backend_type = TransportType::SOCKET;
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

    struct SocketState {
        int socket_fd;
        std::string session_name;
        std::string peer_network_id;
        ConnectionState state{ConnectionState::DISCONNECTED};
        TransportCallbacks callbacks;
        uint32_t send_index{0};
    };

    struct ServerInfo {
        int socket_fd;
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
                RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.socket", "Loaded library: %s", lib_paths[i]);
                break;
            }
        }

        if (!lib_handle_) {
            set_error(-1, dlerror());
            return false;
        }

        // Load Socket API v2.0 symbols
        socket_fn_ = (SocketFn)dlsym(lib_handle_, "Socket");
        listen_fn_ = (ListenFn)dlsym(lib_handle_, "Listen");
        bind_fn_ = (BindFn)dlsym(lib_handle_, "Bind");
        shutdown_fn_ = (ShutdownFn)dlsym(lib_handle_, "Shutdown");
        send_bytes_fn_ = (SendBytesFn)dlsym(lib_handle_, "SendBytes");
        send_message_fn_ = (SendMessageFn)dlsym(lib_handle_, "SendMessage");

        RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.socket", "Symbols: Socket=%p, Listen=%p, Bind=%p",
                (void*)socket_fn_, (void*)listen_fn_, (void*)bind_fn_);

        // Socket API v2.0 requires these core functions
        return socket_fn_ != nullptr && listen_fn_ != nullptr && bind_fn_ != nullptr;
    }

    // Function pointer types for Socket API v2.0
    typedef int32_t (*SocketFn)(SocketInfo);
    typedef int32_t (*ListenFn)(int32_t, const QosTV*, uint32_t, const ISocketListener*);
    typedef int32_t (*BindFn)(int32_t, const QosTV*, uint32_t, const ISocketListener*);
    typedef void (*ShutdownFn)(int32_t);
    typedef int32_t (*SendBytesFn)(int32_t, const void*, uint32_t);
    typedef int32_t (*SendMessageFn)(int32_t, const void*, uint32_t);

    // Function pointers
    SocketFn socket_fn_{nullptr};
    ListenFn listen_fn_{nullptr};
    BindFn bind_fn_{nullptr};
    ShutdownFn shutdown_fn_{nullptr};
    SendBytesFn send_bytes_fn_{nullptr};
    SendMessageFn send_message_fn_{nullptr};

    void* lib_handle_{nullptr};

    // Static listener for callbacks
    static ISocketListener g_socket_listener_;
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

    std::unordered_map<int, SocketState> sockets_;
    std::unordered_map<std::string, ServerInfo> servers_;

    int next_socket_id_{1};

    int last_error_{0};
    std::string last_error_msg_;
};

#ifdef RMW_DSOFTBUS_USE_REAL_SOFTBUS
// Static listener initialization
ISocketListener SocketBackend::g_socket_listener_ = {
    .OnBind = nullptr,      // TODO: Implement callback routing
    .OnShutdown = nullptr,
    .OnBytes = nullptr,
    .OnMessage = nullptr,
    .OnStream = nullptr,
    .OnFile = nullptr,
    .OnQos = nullptr,
};
#endif

// ============================================================================
// Factory Function for Socket Backend
// ============================================================================

std::unique_ptr<ITransportBackend> create_socket_backend() {
    return std::make_unique<SocketBackend>();
}

}  // namespace rmw_dsoftbus
