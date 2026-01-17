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

#include "rmw_dsoftbus/ipc_server.h"

#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <unistd.h>
#include <poll.h>
#include <cerrno>
#include <cstring>
#include <ctime>
#include <vector>

namespace rmw_dsoftbus {
namespace ipc {

// ============================================================
// Singleton Instance
// ============================================================

IpcServer& IpcServer::instance()
{
    static IpcServer instance;
    return instance;
}

IpcServer::~IpcServer()
{
    shutdown();
}

void IpcServer::initialize(std::string sock_path, size_t max_clients)
{
    sock_path_ = std::move(sock_path);
    max_clients_ = max_clients;
}

bool IpcServer::start()
{
    if (!handler_) {
        last_error_ = "Handler not set";
        return false;
    }

    // Create directory if needed
    auto slash = sock_path_.find_last_of('/');
    if (slash != std::string::npos) {
        std::string dir = sock_path_.substr(0, slash);
        ::mkdir(dir.c_str(), 0755);
    }

    // Remove old socket file
    ::unlink(sock_path_.c_str());

    // Create socket
    listen_fd_ = ::socket(AF_UNIX, SOCK_STREAM, 0);
    if (listen_fd_ < 0) {
        last_error_ = "socket() failed";
        return false;
    }

    // Bind
    sockaddr_un addr{};
    addr.sun_family = AF_UNIX;
    if (sock_path_.size() >= sizeof(addr.sun_path)) {
        ::close(listen_fd_);
        listen_fd_ = -1;
        last_error_ = "Socket path too long";
        return false;
    }
    std::strncpy(addr.sun_path, sock_path_.c_str(), sizeof(addr.sun_path) - 1);

    if (::bind(listen_fd_, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0) {
        ::close(listen_fd_);
        listen_fd_ = -1;
        last_error_ = "bind() failed";
        return false;
    }

    // Set permissions (daemon-only writable, group readable)
    ::chmod(sock_path_.c_str(), 0660);

    // Listen
    if (::listen(listen_fd_, 16) < 0) {
        ::close(listen_fd_);
        listen_fd_ = -1;
        last_error_ = "listen() failed";
        return false;
    }

    return true;
}

bool IpcServer::run_loop()
{
    std::vector<pollfd> pfds;
    pfds.reserve(1 + max_clients_);

    while (!stop_.load(std::memory_order_relaxed)) {
        // Build poll set: listen_fd + clients
        pfds.clear();
        pfds.push_back(pollfd{listen_fd_, POLLIN, 0});
        for (const auto& [fd, ctx] : clients_) {
            (void)ctx;
            pfds.push_back(pollfd{fd, POLLIN, 0});
        }

        int rc = ::poll(pfds.data(), pfds.size(), 500);  // 500ms timeout
        if (rc < 0) {
            if (errno == EINTR) {
                continue;
            }
            last_error_ = "poll() failed";
            return false;
        }

        if (rc == 0) {
            continue;  // Timeout
        }

        // Check for new connections
        if (pfds[0].revents & POLLIN) {
            accept_one();
        }

        // Check client sockets
        for (size_t i = 1; i < pfds.size(); ++i) {
            int fd = pfds[i].fd;
            if (pfds[i].revents & (POLLERR | POLLHUP | POLLNVAL)) {
                drop_client(fd);
                continue;
            }
            if (pfds[i].revents & POLLIN) {
                if (!handle_one(fd)) {
                    drop_client(fd);
                }
            }
        }
    }

    return true;
}

void IpcServer::shutdown()
{
    stop_.store(true, std::memory_order_relaxed);

    for (auto& [fd, ctx] : clients_) {
        (void)ctx;
        ::close(fd);
    }
    clients_.clear();

    if (listen_fd_ >= 0) {
        ::close(listen_fd_);
        listen_fd_ = -1;
    }

    if (!sock_path_.empty()) {
        ::unlink(sock_path_.c_str());
    }
}

void IpcServer::notify_graph_changed(uint64_t graph_version)
{
    DiscoveryIpcHeader event{};
    event.magic = DISCOVERY_IPC_MAGIC;
    event.version = DISCOVERY_IPC_VERSION;
    event.header_len = DISCOVERY_IPC_HEADER_SIZE;
    event.msg_type = static_cast<uint16_t>(DISCOVERY_IPC_MSG_EVENT_GRAPH_CHANGED);
    event.flags = 0;
    event.payload_len = 0;
    event.seq = 0;
    event.graph_version = graph_version;

    timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    event.timestamp_ns = static_cast<uint64_t>(ts.tv_sec) * 1000000000ULL +
                         static_cast<uint64_t>(ts.tv_nsec);

    event.status = 0;
    event.crc32 = 0;
    std::memset(event.reserved, 0, sizeof(event.reserved));

    // Send to all subscribed clients
    for (auto& [fd, ctx] : clients_) {
        if (!ctx.subscribed_graph) {
            continue;
        }

        if (!write_all_nothrow(fd, &event, sizeof(event))) {
            // Client died; will be cleaned up in poll loop
        } else {
            stat_tx_.fetch_add(1, std::memory_order_relaxed);
        }
    }
}

IpcServer::Stats IpcServer::get_stats() const
{
    Stats s;
    s.ipc_rx = stat_rx_.load(std::memory_order_relaxed);
    s.ipc_tx = stat_tx_.load(std::memory_order_relaxed);
    s.ipc_errors = stat_errors_.load(std::memory_order_relaxed);
    s.active_clients = clients_.size();
    return s;
}

void IpcServer::accept_one()
{
    if (clients_.size() >= max_clients_) {
        // Reject connection (accept and close immediately)
        int tmp = ::accept(listen_fd_, nullptr, nullptr);
        if (tmp >= 0) {
            ::close(tmp);
        }
        return;
    }

    int cfd = ::accept(listen_fd_, nullptr, nullptr);
    if (cfd < 0) {
        return;
    }

    // Get peer credentials
    ucred cred{};
    socklen_t len = sizeof(cred);
    if (::getsockopt(cfd, SOL_SOCKET, SO_PEERCRED, &cred, &len) < 0) {
        ::close(cfd);
        return;
    }

    // Set timeouts
    struct timeval tv;
    tv.tv_sec = 2;
    tv.tv_usec = 0;
    ::setsockopt(cfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    ::setsockopt(cfd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));

    // TODO: Permission policy check (uid/gid allowlist)
    // if (!is_allowed(cred)) { ::close(cfd); return; }

    ClientContext ctx;
    ctx.fd = cfd;
    ctx.pid = cred.pid;
    ctx.uid = cred.uid;
    ctx.gid = cred.gid;
    ctx.subscribed_graph = false;

    clients_.emplace(cfd, ctx);
}

bool IpcServer::handle_one(int fd)
{
    auto it = clients_.find(fd);
    if (it == clients_.end()) {
        return false;
    }
    ClientContext& ctx = it->second;

    // Read header
    DiscoveryIpcHeader hdr;
    if (!read_all_nothrow(fd, &hdr, sizeof(hdr))) {
        return false;
    }

    stat_rx_.fetch_add(1, std::memory_order_relaxed);

    // Validate header
    if (hdr.magic != DISCOVERY_IPC_MAGIC) {
        stat_errors_.fetch_add(1, std::memory_order_relaxed);
        return false;
    }
    if (hdr.version != DISCOVERY_IPC_VERSION) {
        stat_errors_.fetch_add(1, std::memory_order_relaxed);
        return false;
    }
    if (hdr.header_len != DISCOVERY_IPC_HEADER_SIZE) {
        stat_errors_.fetch_add(1, std::memory_order_relaxed);
        return false;
    }
    if (hdr.payload_len > DISCOVERY_IPC_MAX_FRAME) {
        stat_errors_.fetch_add(1, std::memory_order_relaxed);
        return false;
    }

    // Read payload
    std::vector<uint8_t> payload;
    if (hdr.payload_len > 0) {
        payload.resize(hdr.payload_len);
        if (!read_all_nothrow(fd, payload.data(), payload.size())) {
            return false;
        }
    }

    // Dispatch to handler
    auto [status, resp_payload] = handler_(ctx, hdr, payload);

    // If oneway, don't send response
    if (hdr.flags & DISCOVERY_IPC_FLAG_ONEWAY) {
        return true;
    }

    // Build response
    DiscoveryIpcHeader resp{};
    resp.magic = DISCOVERY_IPC_MAGIC;
    resp.version = DISCOVERY_IPC_VERSION;
    resp.header_len = DISCOVERY_IPC_HEADER_SIZE;
    resp.msg_type = hdr.msg_type;
    resp.flags = static_cast<uint16_t>(DISCOVERY_IPC_FLAG_RESP);
    if (status != 0) {
        resp.flags |= DISCOVERY_IPC_FLAG_ERROR;
    }
    resp.payload_len = static_cast<uint32_t>(resp_payload.size());
    resp.seq = hdr.seq;
    resp.graph_version = 0;  // Handler can set via TLV if needed

    timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    resp.timestamp_ns = static_cast<uint64_t>(ts.tv_sec) * 1000000000ULL +
                        static_cast<uint64_t>(ts.tv_nsec);

    resp.status = status;
    resp.crc32 = 0;
    std::memset(resp.reserved, 0, sizeof(resp.reserved));

    // Check response size
    if (resp.payload_len > DISCOVERY_IPC_MAX_FRAME) {
        resp_payload.clear();
        resp.payload_len = 0;
        resp.status = -EMSGSIZE;
        resp.flags |= DISCOVERY_IPC_FLAG_ERROR;
    }

    // Send response
    if (!write_all_nothrow(fd, &resp, sizeof(resp))) {
        return false;
    }
    if (resp.payload_len > 0) {
        if (!write_all_nothrow(fd, resp_payload.data(), resp_payload.size())) {
            return false;
        }
    }

    stat_tx_.fetch_add(1, std::memory_order_relaxed);
    return true;
}

void IpcServer::drop_client(int fd)
{
    auto it = clients_.find(fd);
    if (it != clients_.end()) {
        ::close(it->second.fd);
        clients_.erase(it);
    }
}

bool IpcServer::read_all_nothrow(int fd, void* data, size_t len)
{
    auto* p = static_cast<uint8_t*>(data);
    size_t offset = 0;

    while (offset < len) {
        ssize_t r = ::read(fd, p + offset, len - offset);
        if (r == 0) {
            return false;  // Connection closed
        }
        if (r < 0) {
            if (errno == EINTR) {
                continue;
            }
            return false;
        }
        offset += static_cast<size_t>(r);
    }
    return true;
}

bool IpcServer::write_all_nothrow(int fd, const void* data, size_t len)
{
    const auto* p = static_cast<const uint8_t*>(data);
    size_t offset = 0;

    while (offset < len) {
        ssize_t w = ::write(fd, p + offset, len - offset);
        if (w < 0) {
            if (errno == EINTR) {
                continue;
            }
            return false;
        }
        offset += static_cast<size_t>(w);
    }
    return true;
}

}  // namespace ipc
}  // namespace rmw_dsoftbus
