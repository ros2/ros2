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

// Copyright (c) 2024 ROS2 KaihongOS Port Project
#include <string.h>  /* C memcpy/memset for OHOS SDK compatibility */
#include <stdlib.h>
#include <sys/time.h>  /* for struct timeval */

// Licensed under the Apache License, Version 2.0

#include "rmw_dsoftbus/ipc_client.h"

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <poll.h>
#include <cerrno>
#include <cstring>
#include <ctime>

namespace rmw_dsoftbus {
namespace ipc {

IpcClient::IpcClient(std::string sock_path)
    : sock_path_(std::move(sock_path))
{
}

IpcClient::~IpcClient()
{
    close();
}

bool IpcClient::connect()
{
    close();

    fd_ = ::socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd_ < 0) {
        last_error_ = "socket() failed";
        return false;
    }

    sockaddr_un addr{};
    addr.sun_family = AF_UNIX;
    if (sock_path_.size() >= sizeof(addr.sun_path)) {
        ::close(fd_);
        fd_ = -1;
        last_error_ = "Socket path too long";
        return false;
    }
    std::strncpy(addr.sun_path, sock_path_.c_str(), sizeof(addr.sun_path) - 1);

    if (::connect(fd_, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0) {
        ::close(fd_);
        fd_ = -1;
        last_error_ = "connect() failed";
        return false;
    }

    // Set timeouts
    struct timeval tv;
    tv.tv_sec = 2;
    tv.tv_usec = 0;
    ::setsockopt(fd_, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    ::setsockopt(fd_, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));

    return true;
}

void IpcClient::close()
{
    if (fd_ >= 0) {
        ::close(fd_);
        fd_ = -1;
    }
}

bool IpcClient::request(
    DiscoveryIpcMsgType msg_type,
    const std::vector<uint8_t>& payload,
    Reply* out_reply,
    bool oneway)
{
    if (fd_ < 0) {
        last_error_ = "IpcClient not connected";
        return false;
    }

    if (payload.size() > DISCOVERY_IPC_MAX_FRAME) {
        last_error_ = "Payload too large";
        return false;
    }

    // Build request header
    DiscoveryIpcHeader req{};
    req.magic = DISCOVERY_IPC_MAGIC;
    req.version = DISCOVERY_IPC_VERSION;
    req.header_len = DISCOVERY_IPC_HEADER_SIZE;
    req.msg_type = static_cast<uint16_t>(msg_type);
    req.flags = static_cast<uint16_t>(DISCOVERY_IPC_FLAG_REQ);
    if (oneway) {
        req.flags |= DISCOVERY_IPC_FLAG_ONEWAY;
    }
    req.payload_len = static_cast<uint32_t>(payload.size());
    req.seq = ++seq_;
    req.graph_version = 0;

    // Get timestamp
    timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    req.timestamp_ns = static_cast<uint64_t>(ts.tv_sec) * 1000000000ULL +
                       static_cast<uint64_t>(ts.tv_nsec);

    req.status = 0;
    req.crc32 = 0;  // CRC not used in v1
    std::memset(req.reserved, 0, sizeof(req.reserved));

    // Send request
    if (!write_all(&req, sizeof(req))) {
        return false;
    }
    if (!payload.empty()) {
        if (!write_all(payload.data(), payload.size())) {
            return false;
        }
    }

    // If oneway, no reply
    if (oneway) {
        if (out_reply) {
            *out_reply = Reply{};
        }
        return true;
    }

    // Receive reply
    Reply reply;
    if (!read_all(&reply.header, sizeof(reply.header))) {
        return false;
    }
    if (!validate_header(reply.header)) {
        return false;
    }

    if (reply.header.payload_len > DISCOVERY_IPC_MAX_FRAME) {
        last_error_ = "Reply payload too large";
        return false;
    }

    if (reply.header.payload_len > 0) {
        reply.payload.resize(reply.header.payload_len);
        if (!read_all(reply.payload.data(), reply.payload.size())) {
            return false;
        }
    }

    if (out_reply) {
        *out_reply = std::move(reply);
    }
    return true;
}

bool IpcClient::subscribe_graph_changes()
{
    return request(DISCOVERY_IPC_MSG_SUBSCRIBE_GRAPH, {}, nullptr, false);
}

bool IpcClient::unsubscribe_graph_changes()
{
    return request(DISCOVERY_IPC_MSG_UNSUBSCRIBE_GRAPH, {}, nullptr, false);
}

bool IpcClient::poll_events(int timeout_ms)
{
    if (fd_ < 0) {
        last_error_ = "IpcClient not connected";
        return false;
    }

    pollfd pfd{fd_, POLLIN, 0};
    int rc = ::poll(&pfd, 1, timeout_ms);
    if (rc <= 0) {
        return false;
    }

    if (!(pfd.revents & POLLIN)) {
        return false;
    }

    // Read event message
    DiscoveryIpcHeader hdr;
    if (!read_all(&hdr, sizeof(hdr))) {
        return false;
    }
    if (!validate_header(hdr)) {
        return false;
    }

    std::vector<uint8_t> payload;
    if (hdr.payload_len > 0) {
        if (hdr.payload_len > DISCOVERY_IPC_MAX_FRAME) {
            last_error_ = "Event payload too large";
            return false;
        }
        payload.resize(hdr.payload_len);
        if (!read_all(payload.data(), payload.size())) {
            return false;
        }
    }

    // Invoke callback if set
    if (event_callback_) {
        event_callback_(hdr.graph_version, payload);
    }

    return true;
}

bool IpcClient::write_all(const void* data, size_t len)
{
    const auto* p = static_cast<const uint8_t*>(data);
    size_t offset = 0;

    while (offset < len) {
        ssize_t w = ::write(fd_, p + offset, len - offset);
        if (w < 0) {
            if (errno == EINTR) {
                continue;
            }
            last_error_ = "write() failed";
            return false;
        }
        offset += static_cast<size_t>(w);
    }
    return true;
}

bool IpcClient::read_all(void* data, size_t len)
{
    auto* p = static_cast<uint8_t*>(data);
    size_t offset = 0;

    while (offset < len) {
        ssize_t r = ::read(fd_, p + offset, len - offset);
        if (r == 0) {
            last_error_ = "Connection closed by peer";
            return false;
        }
        if (r < 0) {
            if (errno == EINTR) {
                continue;
            }
            last_error_ = "read() failed";
            return false;
        }
        offset += static_cast<size_t>(r);
    }
    return true;
}

bool IpcClient::validate_header(const DiscoveryIpcHeader& hdr)
{
    if (hdr.magic != DISCOVERY_IPC_MAGIC) {
        last_error_ = "Invalid magic number";
        return false;
    }
    if (hdr.version != DISCOVERY_IPC_VERSION) {
        last_error_ = "Unsupported protocol version";
        return false;
    }
    if (hdr.header_len < DISCOVERY_IPC_HEADER_SIZE || hdr.header_len > 256) {
        last_error_ = "Invalid header length";
        return false;
    }
    if (hdr.header_len != DISCOVERY_IPC_HEADER_SIZE) {
        // Future: skip extra header bytes
        last_error_ = "Unsupported header length";
        return false;
    }
    return true;
}

}  // namespace ipc
}  // namespace rmw_dsoftbus
