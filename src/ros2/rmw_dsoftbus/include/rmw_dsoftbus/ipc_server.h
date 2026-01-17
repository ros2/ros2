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

#ifndef RMW_DSOFTBUS__IPC_SERVER_H_
#define RMW_DSOFTBUS__IPC_SERVER_H_

#include "rmw_dsoftbus/ipc_protocol.h"
#include <sys/types.h>
#include <map>
#include <functional>
#include <atomic>

namespace rmw_dsoftbus {
namespace ipc {

/**
 * @brief Client context (daemon-side view)
 */
struct ClientContext {
    int fd{-1};
    pid_t pid{0};
    uid_t uid{0};
    gid_t gid{0};
    bool subscribed_graph{false};
};

/**
 * @brief IPC server for rmw_dsoftbus_discoveryd daemon
 *
 * Singleton server for daemon process. Single-threaded poll-based handling of multiple clients.
 * No C++ exceptions (OpenHarmony -fno-exceptions compatibility).
 */
class IpcServer {
public:
    /**
     * @brief Get singleton instance
     */
    static IpcServer& instance();

    /**
     * @brief Handler function type
     * @param ctx Client context
     * @param hdr Request header
     * @param payload Request payload
     * @return (status_code, response_payload)
     */
    using HandlerFn = std::function<std::pair<int32_t, std::vector<uint8_t>>(
        ClientContext& ctx,
        const DiscoveryIpcHeader& hdr,
        const std::vector<uint8_t>& payload)>;

    /**
     * @brief Initialize server with socket path
     * @param sock_path Unix domain socket path
     * @param max_clients Maximum concurrent clients
     */
    void initialize(std::string sock_path, size_t max_clients = DISCOVERY_IPC_MAX_CLIENTS);

    // Disable copy/move
    IpcServer(const IpcServer&) = delete;
    IpcServer& operator=(const IpcServer&) = delete;

    /**
     * @brief Set request handler
     * @param handler Handler function
     */
    void set_handler(HandlerFn handler) { handler_ = std::move(handler); }

    /**
     * @brief Start server (create socket and listen)
     * @return true on success, false on failure
     */
    bool start();

    /**
     * @brief Main event loop (blocking)
     *
     * Runs until shutdown() is called.
     * @return true if exited normally, false on error
     */
    bool run_loop();

    /**
     * @brief Shutdown server
     */
    void shutdown();

    /**
     * @brief Push graph changed event to subscribed clients
     * @param graph_version New graph version
     */
    void notify_graph_changed(uint64_t graph_version);

    /**
     * @brief Get server statistics
     */
    struct Stats {
        uint64_t ipc_rx{0};      // Messages received
        uint64_t ipc_tx{0};      // Messages sent
        uint64_t ipc_errors{0};  // Parse/validation errors
        size_t active_clients{0};
    };

    Stats get_stats() const;

    /**
     * @brief Get last error message
     */
    const char* last_error() const { return last_error_; }

private:
    IpcServer() = default;
    ~IpcServer();

    void accept_one();
    bool handle_one(int fd);
    void drop_client(int fd);
    bool read_all_nothrow(int fd, void* data, size_t len);
    bool write_all_nothrow(int fd, const void* data, size_t len);

private:
    std::string sock_path_;
    size_t max_clients_{DISCOVERY_IPC_MAX_CLIENTS};
    int listen_fd_{-1};
    std::atomic<bool> stop_{false};
    std::map<int, ClientContext> clients_;
    HandlerFn handler_;
    const char* last_error_{nullptr};

    // Statistics
    std::atomic<uint64_t> stat_rx_{0};
    std::atomic<uint64_t> stat_tx_{0};
    std::atomic<uint64_t> stat_errors_{0};
};

// ============================================================
// Default Handler (defined in ipc_handlers.cpp)
// ============================================================

/**
 * @brief Default IPC request handler for daemon
 *
 * Binds IPC requests to GraphCache and DiscoveryManager.
 * Defined in src/ipc_handlers.cpp.
 *
 * @param ctx Client context
 * @param hdr Request header
 * @param payload Request payload
 * @return (status_code, response_payload)
 */
std::pair<int32_t, std::vector<uint8_t>>
handle_ipc_request(
    ClientContext& ctx,
    const DiscoveryIpcHeader& hdr,
    const std::vector<uint8_t>& payload);

}  // namespace ipc
}  // namespace rmw_dsoftbus

#endif  // RMW_DSOFTBUS__IPC_SERVER_H_
