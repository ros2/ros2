// Copyright (c) 2024 ROS2 KaihongOS Port Project
// Licensed under the Apache License, Version 2.0
//
// Socket Direct Backend Implementation
// Simple UDP transport for cross-device ROS2 communication without dsoftbus discovery

#include "rmw_dsoftbus/socket_direct.h"

#include <rcutils/logging_macros.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <ifaddrs.h>
#include <net/if.h>

#include <mutex>
#include <unordered_map>
#include <vector>
#include <string>
#include <thread>
#include <atomic>
#include <algorithm>

namespace {

// === Internal State ===

struct ListenerInfo {
    int socket_fd;
    int port;
    std::string topic_name;
    std::atomic<bool> running{true};
};

struct PeerInfo {
    std::string ip;
    int port;
    struct sockaddr_in addr;
};

struct TopicPeers {
    std::vector<PeerInfo> peers;
    int sender_socket;  // Shared sender socket for this topic
};

static socket_direct_config_t g_config;
static bool g_initialized = false;
static std::mutex g_mutex;

static std::unordered_map<int, ListenerInfo*> g_listeners;
static int g_next_listener_id = 1;

static std::unordered_map<std::string, TopicPeers> g_topic_peers;
static std::string g_local_ip;

// === Helper Functions ===

static std::string detect_local_ip() {
    struct ifaddrs* ifaddr = nullptr;
    if (getifaddrs(&ifaddr) == -1) {
        return "0.0.0.0";
    }

    std::string result = "0.0.0.0";

    // Prefer wlan0 > eth0 > any other interface
    std::string wlan_ip, eth_ip, other_ip;

    for (struct ifaddrs* ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == nullptr || ifa->ifa_addr->sa_family != AF_INET) {
            continue;
        }

        // Skip loopback
        if (ifa->ifa_flags & IFF_LOOPBACK) {
            continue;
        }

        char ip[INET_ADDRSTRLEN];
        struct sockaddr_in* addr = (struct sockaddr_in*)ifa->ifa_addr;
        inet_ntop(AF_INET, &addr->sin_addr, ip, sizeof(ip));

        if (strncmp(ifa->ifa_name, "wlan", 4) == 0) {
            wlan_ip = ip;
        } else if (strncmp(ifa->ifa_name, "eth", 3) == 0) {
            eth_ip = ip;
        } else if (other_ip.empty()) {
            other_ip = ip;
        }
    }

    freeifaddrs(ifaddr);

    if (!wlan_ip.empty()) return wlan_ip;
    if (!eth_ip.empty()) return eth_ip;
    if (!other_ip.empty()) return other_ip;
    return "0.0.0.0";
}

static int create_udp_socket(bool nonblocking = false) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        RCUTILS_LOG_ERROR_NAMED("socket_direct", "Failed to create UDP socket: %s", strerror(errno));
        return -1;
    }

    // Allow address reuse
    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if (nonblocking) {
        int flags = fcntl(sock, F_GETFL, 0);
        fcntl(sock, F_SETFL, flags | O_NONBLOCK);
    }

    return sock;
}

static bool set_socket_timeout(int sock, int recv_ms, int send_ms) {
    struct timeval tv;

    if (recv_ms > 0) {
        tv.tv_sec = recv_ms / 1000;
        tv.tv_usec = (recv_ms % 1000) * 1000;
        if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0) {
            return false;
        }
    }

    if (send_ms > 0) {
        tv.tv_sec = send_ms / 1000;
        tv.tv_usec = (send_ms % 1000) * 1000;
        if (setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv)) < 0) {
            return false;
        }
    }

    return true;
}

}  // namespace

// === Public API Implementation ===

extern "C" {

socket_direct_config_t socket_direct_get_default_config(void) {
    socket_direct_config_t config;
    config.local_ip = nullptr;  // Bind to all interfaces
    config.base_port = SOCKET_DIRECT_BASE_PORT;
    config.recv_timeout_ms = 100;
    config.send_timeout_ms = 1000;
    config.use_multicast = false;
    return config;
}

int socket_direct_init(const socket_direct_config_t* config) {
    std::lock_guard<std::mutex> lock(g_mutex);

    if (g_initialized) {
        return 0;
    }

    if (config) {
        g_config = *config;
    } else {
        g_config = socket_direct_get_default_config();
    }

    // Detect local IP
    g_local_ip = detect_local_ip();

    RCUTILS_LOG_INFO_NAMED("socket_direct",
        "Initialized: local_ip=%s, base_port=%d",
        g_local_ip.c_str(), g_config.base_port);

    g_initialized = true;
    return 0;
}

void socket_direct_shutdown(void) {
    std::lock_guard<std::mutex> lock(g_mutex);

    if (!g_initialized) {
        return;
    }

    // Close all listeners
    for (auto& pair : g_listeners) {
        ListenerInfo* info = pair.second;
        info->running = false;
        if (info->socket_fd >= 0) {
            close(info->socket_fd);
        }
        delete info;
    }
    g_listeners.clear();

    // Close all sender sockets
    for (auto& pair : g_topic_peers) {
        if (pair.second.sender_socket >= 0) {
            close(pair.second.sender_socket);
        }
    }
    g_topic_peers.clear();

    g_initialized = false;
    RCUTILS_LOG_INFO_NAMED("socket_direct", "Shutdown complete");
}

int socket_direct_topic_to_port(const char* topic_name) {
    if (!topic_name) {
        return g_config.base_port;
    }

    // Simple hash function for topic name
    uint32_t hash = 5381;
    for (const char* p = topic_name; *p; p++) {
        hash = ((hash << 5) + hash) + *p;
    }

    return g_config.base_port + (hash % SOCKET_DIRECT_PORT_RANGE);
}

const char* socket_direct_get_local_ip(void) {
    return g_local_ip.c_str();
}

// === Listener API ===

int socket_direct_create_listener(const char* topic_name) {
    std::lock_guard<std::mutex> lock(g_mutex);

    if (!g_initialized) {
        socket_direct_init(nullptr);
    }

    int port = socket_direct_topic_to_port(topic_name);

    int sock = create_udp_socket(false);
    if (sock < 0) {
        return -1;
    }

    // Set receive timeout
    set_socket_timeout(sock, g_config.recv_timeout_ms, 0);

    // Bind to port
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (g_config.local_ip) {
        inet_pton(AF_INET, g_config.local_ip, &addr.sin_addr);
    } else {
        addr.sin_addr.s_addr = INADDR_ANY;
    }

    if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        RCUTILS_LOG_ERROR_NAMED("socket_direct",
            "Failed to bind to port %d: %s", port, strerror(errno));
        close(sock);
        return -1;
    }

    // Create listener info
    ListenerInfo* info = new ListenerInfo();
    info->socket_fd = sock;
    info->port = port;
    info->topic_name = topic_name ? topic_name : "";
    info->running = true;

    int listener_id = g_next_listener_id++;
    g_listeners[listener_id] = info;

    RCUTILS_LOG_INFO_NAMED("socket_direct",
        "Created listener: id=%d, topic=%s, port=%d, local_ip=%s",
        listener_id, topic_name, port, g_local_ip.c_str());

    return listener_id;
}

void socket_direct_destroy_listener(int listener_id) {
    std::lock_guard<std::mutex> lock(g_mutex);

    auto it = g_listeners.find(listener_id);
    if (it == g_listeners.end()) {
        return;
    }

    ListenerInfo* info = it->second;
    info->running = false;

    if (info->socket_fd >= 0) {
        close(info->socket_fd);
    }

    RCUTILS_LOG_INFO_NAMED("socket_direct",
        "Destroyed listener: id=%d, topic=%s",
        listener_id, info->topic_name.c_str());

    delete info;
    g_listeners.erase(it);
}

int socket_direct_recv(int listener_id, void* buffer, int buffer_size,
                       char* sender_ip, int sender_ip_size) {
    ListenerInfo* info = nullptr;
    {
        std::lock_guard<std::mutex> lock(g_mutex);
        auto it = g_listeners.find(listener_id);
        if (it == g_listeners.end()) {
            return -1;
        }
        info = it->second;
    }

    if (!info->running || info->socket_fd < 0) {
        return -1;
    }

    struct sockaddr_in sender_addr;
    socklen_t addr_len = sizeof(sender_addr);

    ssize_t received = recvfrom(info->socket_fd, buffer, buffer_size, 0,
                                (struct sockaddr*)&sender_addr, &addr_len);

    if (received < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK || errno == ETIMEDOUT) {
            return 0;  // Timeout
        }
        return -1;  // Error
    }

    // Copy sender IP if requested
    if (sender_ip && sender_ip_size > 0) {
        inet_ntop(AF_INET, &sender_addr.sin_addr, sender_ip, sender_ip_size);
    }

    return (int)received;
}

int socket_direct_get_listener_port(int listener_id) {
    std::lock_guard<std::mutex> lock(g_mutex);

    auto it = g_listeners.find(listener_id);
    if (it == g_listeners.end()) {
        return -1;
    }

    return it->second->port;
}

// === Publisher API ===

int socket_direct_add_peer(const char* topic_name, const char* peer_ip, int peer_port) {
    std::lock_guard<std::mutex> lock(g_mutex);

    if (!g_initialized) {
        socket_direct_init(nullptr);
    }

    std::string topic = topic_name ? topic_name : "";

    // If port not specified, compute from topic
    if (peer_port <= 0) {
        peer_port = socket_direct_topic_to_port(topic_name);
    }

    // Get or create topic entry
    TopicPeers& tp = g_topic_peers[topic];

    // Create sender socket if needed
    if (tp.sender_socket <= 0) {
        tp.sender_socket = create_udp_socket(false);
        if (tp.sender_socket < 0) {
            return -1;
        }
        set_socket_timeout(tp.sender_socket, 0, g_config.send_timeout_ms);
    }

    // Check if peer already exists
    for (const auto& p : tp.peers) {
        if (p.ip == peer_ip && p.port == peer_port) {
            return 0;  // Already exists
        }
    }

    // Add peer
    PeerInfo peer;
    peer.ip = peer_ip;
    peer.port = peer_port;
    memset(&peer.addr, 0, sizeof(peer.addr));
    peer.addr.sin_family = AF_INET;
    peer.addr.sin_port = htons(peer_port);
    inet_pton(AF_INET, peer_ip, &peer.addr.sin_addr);

    tp.peers.push_back(peer);

    RCUTILS_LOG_INFO_NAMED("socket_direct",
        "Added peer: topic=%s, peer=%s:%d",
        topic_name, peer_ip, peer_port);

    return 0;
}

void socket_direct_remove_peer(const char* topic_name, const char* peer_ip, int peer_port) {
    std::lock_guard<std::mutex> lock(g_mutex);

    std::string topic = topic_name ? topic_name : "";

    auto it = g_topic_peers.find(topic);
    if (it == g_topic_peers.end()) {
        return;
    }

    auto& peers = it->second.peers;
    peers.erase(
        std::remove_if(peers.begin(), peers.end(),
            [peer_ip, peer_port](const PeerInfo& p) {
                return p.ip == peer_ip && p.port == peer_port;
            }),
        peers.end());

    RCUTILS_LOG_INFO_NAMED("socket_direct",
        "Removed peer: topic=%s, peer=%s:%d",
        topic_name, peer_ip, peer_port);
}

int socket_direct_send(const char* topic_name, const void* data, int data_len) {
    std::lock_guard<std::mutex> lock(g_mutex);

    std::string topic = topic_name ? topic_name : "";

    auto it = g_topic_peers.find(topic);
    if (it == g_topic_peers.end() || it->second.peers.empty()) {
        // No peers configured - this is expected in some cases
        return 0;
    }

    TopicPeers& tp = it->second;
    int success_count = 0;

    for (const auto& peer : tp.peers) {
        ssize_t sent = sendto(tp.sender_socket, data, data_len, 0,
                              (struct sockaddr*)&peer.addr, sizeof(peer.addr));
        if (sent == data_len) {
            success_count++;
        } else {
            RCUTILS_LOG_WARN_NAMED("socket_direct",
                "Send failed to %s:%d: %s",
                peer.ip.c_str(), peer.port, strerror(errno));
        }
    }

    return success_count;
}

int socket_direct_send_to(const char* peer_ip, int peer_port, const void* data, int data_len) {
    // Create a temporary socket for one-shot send
    int sock = create_udp_socket(false);
    if (sock < 0) {
        return -1;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(peer_port);
    inet_pton(AF_INET, peer_ip, &addr.sin_addr);

    ssize_t sent = sendto(sock, data, data_len, 0,
                          (struct sockaddr*)&addr, sizeof(addr));

    close(sock);

    if (sent == data_len) {
        return 0;
    }

    return -1;
}

}  // extern "C"
