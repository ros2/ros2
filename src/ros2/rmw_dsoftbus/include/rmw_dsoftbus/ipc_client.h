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

#ifndef RMW_DSOFTBUS__IPC_CLIENT_H_
#define RMW_DSOFTBUS__IPC_CLIENT_H_

#include "rmw_dsoftbus/ipc_protocol.h"
#include <string>
#include <functional>

namespace rmw_dsoftbus {
namespace ipc {

/**
 * @brief IPC client for librmw processes to communicate with rmw_dsoftbus_discoveryd daemon
 *
 * Thread safety: NOT thread-safe. Caller must serialize calls or use per-thread instances.
 * No C++ exceptions (OpenHarmony -fno-exceptions compatibility).
 */
class IpcClient {
public:
    /**
     * @brief Construct client with socket path
     * @param sock_path Unix domain socket path (e.g., "/run/rmw_dsoftbus/discovery.sock")
     */
    explicit IpcClient(std::string sock_path);
    ~IpcClient();

    // Disable copy/move
    IpcClient(const IpcClient&) = delete;
    IpcClient& operator=(const IpcClient&) = delete;

    /**
     * @brief Connect to daemon
     * @return true on success, false on failure
     */
    bool connect();

    /**
     * @brief Check if connected
     */
    bool is_connected() const { return fd_ >= 0; }

    /**
     * @brief Close connection
     */
    void close();

    /**
     * @brief Reply structure
     */
    struct Reply {
        DiscoveryIpcHeader header{};
        std::vector<uint8_t> payload;

        // Convenience: check if successful
        bool ok() const { return header.status == 0; }
        int32_t status() const { return header.status; }
        uint64_t graph_version() const { return header.graph_version; }
    };

    /**
     * @brief Send request and receive reply
     * @param msg_type Message type
     * @param payload Request payload (TLV-encoded)
     * @param out_reply Reply output (may be nullptr if oneway)
     * @param oneway If true, don't wait for response
     * @return true on success, false on communication error
     */
    bool request(
        DiscoveryIpcMsgType msg_type,
        const std::vector<uint8_t>& payload,
        Reply* out_reply,
        bool oneway = false);

    /**
     * @brief Subscribe to graph change events
     * @return true on success
     */
    bool subscribe_graph_changes();

    /**
     * @brief Unsubscribe from graph change events
     * @return true on success
     */
    bool unsubscribe_graph_changes();

    /**
     * @brief Event callback type
     * @param graph_version New graph version
     * @param payload Event payload (may be empty)
     */
    using EventCallback = std::function<void(uint64_t graph_version, const std::vector<uint8_t>&)>;

    /**
     * @brief Set event callback
     * @param cb Callback to invoke when EVENT_GRAPH_CHANGED received
     */
    void set_event_callback(EventCallback cb) { event_callback_ = std::move(cb); }

    /**
     * @brief Poll for events (non-blocking)
     * @param timeout_ms Timeout in milliseconds (0 = non-blocking)
     * @return true if event received and callback invoked
     */
    bool poll_events(int timeout_ms = 0);

    /**
     * @brief Get last error message
     */
    const char* last_error() const { return last_error_; }

private:
    bool write_all(const void* data, size_t len);
    bool read_all(void* data, size_t len);
    bool validate_header(const DiscoveryIpcHeader& hdr);

private:
    std::string sock_path_;
    int fd_{-1};
    uint64_t seq_{0};
    EventCallback event_callback_;
    const char* last_error_{nullptr};
};

}  // namespace ipc
}  // namespace rmw_dsoftbus

#endif  // RMW_DSOFTBUS__IPC_CLIENT_H_
