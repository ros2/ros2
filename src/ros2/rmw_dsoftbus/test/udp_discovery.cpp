#include "udp_discovery.h"
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ifaddrs.h>
#include <cstring>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <cstdio>

// 多播地址
#define MULTICAST_ADDR "239.255.0.1"

UdpDiscovery::UdpDiscovery(uint16_t port)
    : port_(port), socket_(-1), running_(false) {
}

UdpDiscovery::~UdpDiscovery() {
    stop();
}

bool UdpDiscovery::start(const std::string& local_network_id,
                         const std::string& device_name) {
    local_network_id_ = local_network_id;
    local_device_name_ = device_name;
    local_ip_ = get_local_ip();

    fprintf(stderr, "[UdpDiscovery] Starting with network_id: %s\n",
            local_network_id.c_str());
    fprintf(stderr, "[UdpDiscovery] Device name: %s\n", device_name.c_str());
    fprintf(stderr, "[UdpDiscovery] Local IP: %s\n", local_ip_.c_str());

    // 创建 UDP socket
    socket_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_ < 0) {
        fprintf(stderr, "[UdpDiscovery] Failed to create socket\n");
        return false;
    }

    // 允许地址重用
    int reuse = 1;
    setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    // 绑定到端口
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port_);

    if (bind(socket_, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        fprintf(stderr, "[UdpDiscovery] Failed to bind socket\n");
        close(socket_);
        return false;
    }

    // 加入多播组
    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = inet_addr(MULTICAST_ADDR);
    mreq.imr_interface.s_addr = INADDR_ANY;
    if (setsockopt(socket_, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
        fprintf(stderr, "[UdpDiscovery] Failed to join multicast group\n");
        close(socket_);
        return false;
    }

    // 启动线程
    running_ = true;
    thread_ = std::thread(&UdpDiscovery::discovery_thread, this);

    fprintf(stderr, "[UdpDiscovery] Started successfully\n");
    return true;
}

void UdpDiscovery::stop() {
    if (running_) {
        running_ = false;
        if (thread_.joinable()) {
            thread_.join();
        }
        if (socket_ >= 0) {
            close(socket_);
            socket_ = -1;
        }
        fprintf(stderr, "[UdpDiscovery] Stopped\n");
    }
}

void UdpDiscovery::discovery_thread() {
    auto last_broadcast = std::chrono::steady_clock::now();

    while (running_) {
        auto now = std::chrono::steady_clock::now();

        // 每秒发送广播
        if (now - last_broadcast >= std::chrono::milliseconds(BROADCAST_INTERVAL_MS)) {
            send_broadcast();
            last_broadcast = now;
        }

        // 接收消息（超时 100ms）
        receive_messages();

        // 清理超时设备
        std::lock_guard<std::mutex> lock(peers_mutex_);
        auto it = peers_.begin();
        while (it != peers_.end()) {
            auto age = std::chrono::duration_cast<std::chrono::seconds>(
                now - it->second.last_seen).count();
            if (age > PEER_TIMEOUT_SEC) {
                fprintf(stderr, "[UdpDiscovery] Peer timeout: %s (%s)\n",
                        it->second.device_name.c_str(), it->first.c_str());
                it = peers_.erase(it);
            } else {
                ++it;
            }
        }
    }
}

void UdpDiscovery::send_broadcast() {
    // 格式: "DISCOVERY|network_id|device_name|ip|port|timestamp"
    std::ostringstream msg;
    msg << "DISCOVERY|"
        << local_network_id_ << "|"
        << local_device_name_ << "|"
        << local_ip_ << "|"
        << port_ << "|"
        << std::time(nullptr);

    std::string data = msg.str();

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(MULTICAST_ADDR);
    addr.sin_port = htons(port_);

    ssize_t sent = sendto(socket_, data.c_str(), data.length(), 0,
                          (struct sockaddr*)&addr, sizeof(addr));

    if (sent < 0) {
        fprintf(stderr, "[UdpDiscovery] Failed to send broadcast\n");
    }
}

void UdpDiscovery::receive_messages() {
    char buffer[1024];
    struct sockaddr_in from_addr;
    socklen_t from_len = sizeof(from_addr);

    // 设置接收超时
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 100000; // 100ms
    setsockopt(socket_, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    ssize_t n = recvfrom(socket_, buffer, sizeof(buffer) - 1, 0,
                         (struct sockaddr*)&from_addr, &from_len);

    if (n > 0) {
        buffer[n] = '\0';

        // 解析消息: "DISCOVERY|network_id|device_name|ip|port|timestamp"
        std::string msg(buffer);
        std::istringstream iss(msg);
        std::string type, network_id, device_name, ip, port_str, timestamp_str;

        std::getline(iss, type, '|');
        std::getline(iss, network_id, '|');
        std::getline(iss, device_name, '|');
        std::getline(iss, ip, '|');
        std::getline(iss, port_str, '|');
        std::getline(iss, timestamp_str, '|');

        if (type == "DISCOVERY" && network_id != local_network_id_) {
            std::lock_guard<std::mutex> lock(peers_mutex_);

            bool is_new = (peers_.find(network_id) == peers_.end());

            PeerDevice peer;
            peer.network_id = network_id;
            peer.device_name = device_name;
            peer.ip_address = ip;
            peer.port = static_cast<uint16_t>(std::stoi(port_str));
            peer.last_seen = std::chrono::steady_clock::now();

            if (is_new) {
                fprintf(stderr, "[UdpDiscovery] ✓✓✓ New peer discovered: %s (%s) at %s\n",
                        device_name.c_str(), network_id.c_str(), ip.c_str());
            }

            peers_[network_id] = peer;
        }
    }
}

std::vector<PeerDevice> UdpDiscovery::get_peers() {
    std::lock_guard<std::mutex> lock(peers_mutex_);
    std::vector<PeerDevice> result;
    for (const auto& pair : peers_) {
        result.push_back(pair.second);
    }
    return result;
}

bool UdpDiscovery::has_peer(const std::string& network_id) {
    std::lock_guard<std::mutex> lock(peers_mutex_);
    return peers_.find(network_id) != peers_.end();
}

std::string UdpDiscovery::get_local_ip() {
    struct ifaddrs *ifaddr, *ifa;
    if (getifaddrs(&ifaddr) == -1) {
        return "0.0.0.0";
    }

    std::string result = "0.0.0.0";
    for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == nullptr) continue;

        if (ifa->ifa_addr->sa_family == AF_INET) {
            char addr[INET_ADDRSTRLEN];
            struct sockaddr_in *sa = (struct sockaddr_in*)ifa->ifa_addr;
            inet_ntop(AF_INET, &sa->sin_addr, addr, INET_ADDRSTRLEN);

            std::string ip(addr);
            std::string iface(ifa->ifa_name);

            // 优先选择 wlan0 或 eth0，跳过 loopback
            if (ip != "127.0.0.1") {
                if (iface.find("wlan") == 0 || iface.find("eth") == 0) {
                    result = ip;
                    break;
                } else if (result == "0.0.0.0") {
                    // 如果没找到 wlan/eth，使用第一个非 loopback IP
                    result = ip;
                }
            }
        }
    }

    freeifaddrs(ifaddr);
    return result;
}

std::string UdpDiscovery::get_fallback_network_id() {
    // 读取 boot_id 作为 fallback
    std::ifstream f("/proc/sys/kernel/random/boot_id");
    std::string boot_id;
    std::getline(f, boot_id);

    // 移除 '-' 并补足到 64 字符
    boot_id.erase(std::remove(boot_id.begin(), boot_id.end(), '-'),
                  boot_id.end());

    // 移除换行符
    boot_id.erase(std::remove(boot_id.begin(), boot_id.end(), '\n'),
                  boot_id.end());
    boot_id.erase(std::remove(boot_id.begin(), boot_id.end(), '\r'),
                  boot_id.end());

    while (boot_id.length() < 64) {
        boot_id += "0";
    }

    return boot_id;
}
