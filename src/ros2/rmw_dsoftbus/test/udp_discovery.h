#ifndef UDP_DISCOVERY_H
#define UDP_DISCOVERY_H

#include <string>
#include <vector>
#include <map>
#include <thread>
#include <mutex>
#include <chrono>

struct PeerDevice {
    std::string network_id;
    std::string device_name;
    std::string ip_address;
    uint16_t port;
    std::chrono::steady_clock::time_point last_seen;
};

class UdpDiscovery {
public:
    UdpDiscovery(uint16_t port = 8888);
    ~UdpDiscovery();

    // 启动/停止发现
    bool start(const std::string& local_network_id,
               const std::string& device_name);
    void stop();

    // 获取发现的设备
    std::vector<PeerDevice> get_peers();
    bool has_peer(const std::string& network_id);

    // 获取 fallback network ID (public for external use)
    std::string get_fallback_network_id();

private:
    void discovery_thread();
    void send_broadcast();
    void receive_messages();

    std::string get_local_ip();

    uint16_t port_;
    int socket_;
    bool running_;
    std::thread thread_;

    std::string local_network_id_;
    std::string local_device_name_;
    std::string local_ip_;

    std::mutex peers_mutex_;
    std::map<std::string, PeerDevice> peers_;

    static constexpr int PEER_TIMEOUT_SEC = 10;
    static constexpr int BROADCAST_INTERVAL_MS = 1000;
};

#endif // UDP_DISCOVERY_H
