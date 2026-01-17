// Copyright (c) 2024 ROS2 KaihongOS Port Project
// Licensed under the Apache License, Version 2.0
//
// Transport Manager Implementation
// Central control layer for transport backend selection and management
// Implements automatic backend selection with priority: KH_TRANS > SOCKET > SESSION

#include "rmw_dsoftbus/transport_manager.h"

#include <rcutils/logging_macros.h>  // Foundation layer logging

#include <string>
#include <algorithm>

namespace rmw_dsoftbus
{

// Forward declarations of backend factory functions
std::unique_ptr<ITransportBackend> create_khtrans_backend();
std::unique_ptr<ITransportBackend> create_socket_backend();
std::unique_ptr<ITransportBackend> create_session_backend();

// ============================================================================
// Helper Functions
// ============================================================================

const char* transport_type_to_string(TransportType type) {
    switch (type) {
        case TransportType::KH_TRANS: return "KH_TRANS";
        case TransportType::SOCKET: return "SOCKET";
        case TransportType::SESSION: return "SESSION";
        case TransportType::AUTO: return "AUTO";
        default: return "UNKNOWN";
    }
}

const char* transport_status_to_string(TransportStatus status) {
    switch (status) {
        case TransportStatus::UNAVAILABLE: return "UNAVAILABLE";
        case TransportStatus::AVAILABLE: return "AVAILABLE";
        case TransportStatus::READY: return "READY";
        case TransportStatus::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

std::unique_ptr<ITransportBackend> create_transport_backend(TransportType type) {
    switch (type) {
        case TransportType::KH_TRANS:
            return create_khtrans_backend();
        case TransportType::SOCKET:
            return create_socket_backend();
        case TransportType::SESSION:
            return create_session_backend();
        default:
            return nullptr;
    }
}

// ============================================================================
// TransportManager Implementation
// ============================================================================

TransportManager& TransportManager::instance() {
    static TransportManager instance;
    return instance;
}

TransportManager::~TransportManager() {
    shutdown();
}

bool TransportManager::init(const char* pkg_name, const TransportManagerConfig& config) {
    std::lock_guard<std::mutex> lock(mutex_);

    if (initialized_) {
        return true;
    }

    if (!pkg_name) {
        set_error(-1, "Package name is null");
        return false;
    }

    pkg_name_ = pkg_name;
    config_ = config;

    RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.transport", "Initializing with package: %s", pkg_name);

    // Build priority string
    std::string priority_str;
    for (size_t i = 0; i < config_.priority_order.size(); ++i) {
        priority_str += transport_type_to_string(config_.priority_order[i]);
        if (i < config_.priority_order.size() - 1) {
            priority_str += " > ";
        }
    }
    RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.transport", "Backend priority: %s", priority_str.c_str());

    // Create all backends
    kh_trans_backend_ = create_khtrans_backend();
    socket_backend_ = create_socket_backend();
    session_backend_ = create_session_backend();

    // Probe all backends
    RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.transport", "Probing backends...");

    if (kh_trans_backend_) {
        TransportStatus status = kh_trans_backend_->probe();
        RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.transport", "  KH_TRANS: %s", transport_status_to_string(status));
    }

    if (socket_backend_) {
        TransportStatus status = socket_backend_->probe();
        RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.transport", "  SOCKET: %s", transport_status_to_string(status));
    }

    if (session_backend_) {
        TransportStatus status = session_backend_->probe();
        RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.transport", "  SESSION: %s", transport_status_to_string(status));
    }

    // Select best backend
    if (config_.preferred_type == TransportType::AUTO) {
        active_type_ = select_best_backend();
    } else {
        active_type_ = config_.preferred_type;
    }

    RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.transport", "Selected backend: %s", transport_type_to_string(active_type_));

    // Initialize the selected backend
    ITransportBackend* backend = active_backend();
    if (!backend) {
        set_error(-1, "No backend available");
        return false;
    }

    if (!backend->init(pkg_name)) {
        RCUTILS_LOG_ERROR_NAMED("rmw_dsoftbus.transport", "Failed to initialize %s backend",
                transport_type_to_string(active_type_));

        // Try fallback if enabled
        if (config_.enable_fallback && try_fallback()) {
            backend = active_backend();
            if (backend && backend->init(pkg_name)) {
                RCUTILS_LOG_WARN_NAMED("rmw_dsoftbus.transport", "Fallback to %s successful",
                        transport_type_to_string(active_type_));
            } else {
                set_error(-1, "All backends failed to initialize");
                return false;
            }
        } else {
            set_error(-1, "Backend initialization failed");
            return false;
        }
    }

    initialized_ = true;
    RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.transport", "Initialization complete, active backend: %s",
            transport_type_to_string(active_type_));
    return true;
}

void TransportManager::shutdown() {
    std::lock_guard<std::mutex> lock(mutex_);

    if (!initialized_) {
        return;
    }

    // Close all connections
    for (auto& pair : connections_) {
        ITransportBackend* backend = get_backend(pair.second.backend_type);
        if (backend) {
            backend->disconnect(pair.second.backend_handle);
        }
    }
    connections_.clear();

    // Remove all servers
    for (auto& pair : servers_) {
        ITransportBackend* backend = get_backend(pair.second);
        if (backend) {
            backend->remove_server(pair.first.c_str());
        }
    }
    servers_.clear();

    // Shutdown all backends
    if (kh_trans_backend_) kh_trans_backend_->shutdown();
    if (socket_backend_) socket_backend_->shutdown();
    if (session_backend_) session_backend_->shutdown();

    initialized_ = false;
    RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.transport", "Shutdown complete");
}

TransportType TransportManager::active_backend_type() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return active_type_;
}

ITransportBackend* TransportManager::active_backend() {
    return get_backend(active_type_);
}

ITransportBackend* TransportManager::get_backend(TransportType type) {
    switch (type) {
        case TransportType::KH_TRANS:
            return kh_trans_backend_.get();
        case TransportType::SOCKET:
            return socket_backend_.get();
        case TransportType::SESSION:
            return session_backend_.get();
        default:
            return nullptr;
    }
}

bool TransportManager::is_backend_available(TransportType type) const {
    std::lock_guard<std::mutex> lock(mutex_);

    ITransportBackend* backend = nullptr;
    switch (type) {
        case TransportType::KH_TRANS:
            backend = kh_trans_backend_.get();
            break;
        case TransportType::SOCKET:
            backend = socket_backend_.get();
            break;
        case TransportType::SESSION:
            backend = session_backend_.get();
            break;
        default:
            return false;
    }

    return backend && backend->probe() != TransportStatus::UNAVAILABLE;
}

bool TransportManager::switch_backend(TransportType type) {
    std::lock_guard<std::mutex> lock(mutex_);

    if (!initialized_) {
        set_error(-1, "Not initialized");
        return false;
    }

    ITransportBackend* backend = get_backend(type);
    if (!backend) {
        set_error(-1, "Backend not found");
        return false;
    }

    if (backend->probe() == TransportStatus::UNAVAILABLE) {
        set_error(-1, "Backend unavailable");
        return false;
    }

    if (backend->status() != TransportStatus::READY) {
        if (!backend->init(pkg_name_.c_str())) {
            set_error(-1, "Backend initialization failed");
            return false;
        }
    }

    active_type_ = type;
    RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.transport", "Switched to backend: %s", transport_type_to_string(type));
    return true;
}

std::vector<std::pair<TransportType, TransportStatus>> TransportManager::get_all_backend_status() const {
    std::lock_guard<std::mutex> lock(mutex_);
    std::vector<std::pair<TransportType, TransportStatus>> result;

    if (kh_trans_backend_) {
        result.emplace_back(TransportType::KH_TRANS, kh_trans_backend_->status());
    }
    if (socket_backend_) {
        result.emplace_back(TransportType::SOCKET, socket_backend_->status());
    }
    if (session_backend_) {
        result.emplace_back(TransportType::SESSION, session_backend_->status());
    }

    return result;
}

int TransportManager::create_server(const char* session_name, const TransportCallbacks& callbacks) {
    std::lock_guard<std::mutex> lock(mutex_);

    if (!initialized_) {
        set_error(-1, "Not initialized");
        return -1;
    }

    ITransportBackend* backend = active_backend();
    if (!backend) {
        set_error(-1, "No active backend");
        return -1;
    }

    int server_id = backend->create_server(session_name, callbacks);
    if (server_id >= 0) {
        servers_[session_name] = active_type_;
    }

    return server_id;
}

void TransportManager::remove_server(const char* session_name) {
    std::lock_guard<std::mutex> lock(mutex_);

    if (!initialized_ || !session_name) return;

    auto it = servers_.find(session_name);
    if (it == servers_.end()) return;

    ITransportBackend* backend = get_backend(it->second);
    if (backend) {
        backend->remove_server(session_name);
    }

    servers_.erase(it);
}

int TransportManager::connect(const char* peer_network_id,
                               const char* my_session_name,
                               const char* peer_session_name,
                               const TransportConfig& config,
                               const TransportCallbacks& callbacks) {
    std::lock_guard<std::mutex> lock(mutex_);

    if (!initialized_) {
        set_error(-1, "Not initialized");
        return -1;
    }

    ITransportBackend* backend = active_backend();
    if (!backend) {
        set_error(-1, "No active backend");
        return -1;
    }

    int backend_handle = backend->connect(peer_network_id, my_session_name,
                                          peer_session_name, config, callbacks);
    if (backend_handle < 0) {
        // Try fallback if enabled
        if (config_.enable_fallback && try_fallback()) {
            backend = active_backend();
            if (backend) {
                backend_handle = backend->connect(peer_network_id, my_session_name,
                                                  peer_session_name, config, callbacks);
            }
        }

        if (backend_handle < 0) {
            return backend_handle;
        }
    }

    // Create managed connection
    int conn_id = next_conn_id_++;

    ManagedConnection conn;
    conn.id = conn_id;
    conn.backend_handle = backend_handle;
    conn.backend_type = active_type_;
    conn.session_name = my_session_name ? my_session_name : "";
    conn.peer_network_id = peer_network_id ? peer_network_id : "";
    conn.state = ConnectionState::CONNECTED;
    conn.config = config;
    conn.callbacks = callbacks;
    conn.send_index = 0;

    connections_[conn_id] = conn;

    if (config_.verbose_logging) {
        RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.transport", "Connected: id=%d, backend=%s, peer=%s",
                conn_id, transport_type_to_string(active_type_), peer_network_id);
    }

    return conn_id;
}

void TransportManager::disconnect(int conn_id) {
    std::lock_guard<std::mutex> lock(mutex_);

    auto it = connections_.find(conn_id);
    if (it == connections_.end()) return;

    ITransportBackend* backend = get_backend(it->second.backend_type);
    if (backend) {
        backend->disconnect(it->second.backend_handle);
    }

    connections_.erase(it);

    if (config_.verbose_logging) {
        RCUTILS_LOG_INFO_NAMED("rmw_dsoftbus.transport", "Disconnected: id=%d", conn_id);
    }
}

bool TransportManager::is_connected(int conn_id) const {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = connections_.find(conn_id);
    return it != connections_.end() && it->second.state == ConnectionState::CONNECTED;
}

bool TransportManager::get_connection_info(int conn_id, ManagedConnection& info) const {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = connections_.find(conn_id);
    if (it == connections_.end()) return false;
    info = it->second;
    return true;
}

int TransportManager::send(int conn_id, const void* data, size_t len) {
    std::lock_guard<std::mutex> lock(mutex_);

    auto it = connections_.find(conn_id);
    if (it == connections_.end()) {
        set_error(-1, "Connection not found");
        return -1;
    }

    ITransportBackend* backend = get_backend(it->second.backend_type);
    if (!backend) {
        set_error(-1, "Backend not available");
        return -1;
    }

    int ret = backend->send(it->second.backend_handle, data, len);
    if (ret == 0) {
        it->second.send_index++;
    }

    return ret;
}

int TransportManager::send_message(int conn_id, const void* data, size_t len) {
    std::lock_guard<std::mutex> lock(mutex_);

    auto it = connections_.find(conn_id);
    if (it == connections_.end()) {
        set_error(-1, "Connection not found");
        return -1;
    }

    ITransportBackend* backend = get_backend(it->second.backend_type);
    if (!backend) {
        set_error(-1, "Backend not available");
        return -1;
    }

    return backend->send_message(it->second.backend_handle, data, len);
}

size_t TransportManager::connection_count() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return connections_.size();
}

size_t TransportManager::server_count() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return servers_.size();
}

std::vector<int> TransportManager::get_all_connections() const {
    std::lock_guard<std::mutex> lock(mutex_);
    std::vector<int> result;
    result.reserve(connections_.size());
    for (const auto& pair : connections_) {
        result.push_back(pair.first);
    }
    return result;
}

void TransportManager::update_config(const TransportManagerConfig& config) {
    std::lock_guard<std::mutex> lock(mutex_);
    config_ = config;
}

TransportType TransportManager::select_best_backend() {
    // Try backends in priority order
    for (TransportType type : config_.priority_order) {
        ITransportBackend* backend = get_backend(type);
        if (backend && backend->probe() != TransportStatus::UNAVAILABLE) {
            return type;
        }
    }

    // Fallback to SESSION as last resort
    return TransportType::SESSION;
}

bool TransportManager::try_fallback() {
    // Find current backend in priority order
    auto current_it = std::find(config_.priority_order.begin(),
                                 config_.priority_order.end(),
                                 active_type_);

    if (current_it == config_.priority_order.end()) {
        return false;
    }

    // Try next backends in priority order
    for (auto it = current_it + 1; it != config_.priority_order.end(); ++it) {
        ITransportBackend* backend = get_backend(*it);
        if (backend && backend->probe() != TransportStatus::UNAVAILABLE) {
            active_type_ = *it;
            RCUTILS_LOG_WARN_NAMED("rmw_dsoftbus.transport", "Fallback to: %s", transport_type_to_string(*it));
            return true;
        }
    }

    return false;
}

void TransportManager::set_error(int code, const char* msg) {
    last_error_ = code;
    last_error_msg_ = msg ? msg : "Unknown error";
}

// ============================================================================
// C-style API
// ============================================================================

bool transport_init(const char* pkg_name) {
    return TransportManager::instance().init(pkg_name);
}

void transport_shutdown() {
    TransportManager::instance().shutdown();
}

int transport_create_server(const char* session_name) {
    TransportCallbacks callbacks;  // Empty callbacks for C API
    return TransportManager::instance().create_server(session_name, callbacks);
}

void transport_remove_server(const char* session_name) {
    TransportManager::instance().remove_server(session_name);
}

int transport_connect(const char* peer_network_id,
                      const char* my_session_name,
                      const char* peer_session_name,
                      int timeout_ms) {
    TransportConfig config;
    config.timeout_ms = timeout_ms;
    TransportCallbacks callbacks;
    return TransportManager::instance().connect(peer_network_id, my_session_name,
                                                 peer_session_name, config, callbacks);
}

void transport_disconnect(int conn_id) {
    TransportManager::instance().disconnect(conn_id);
}

int transport_send(int conn_id, const void* data, size_t len) {
    return TransportManager::instance().send(conn_id, data, len);
}

bool transport_is_connected(int conn_id) {
    return TransportManager::instance().is_connected(conn_id);
}

const char* transport_active_backend() {
    return transport_type_to_string(TransportManager::instance().active_backend_type());
}

}  // namespace rmw_dsoftbus
