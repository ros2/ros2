/**
 * @file transport_controller.cpp
 * @brief 传输层控制器实现
 */

#include "rmw_dsoftbus/transport_controller.hpp"
#include "rmw_dsoftbus/transport_khtrans_backend.hpp"
#include "rmw_dsoftbus/transport_session_backend.hpp"
#include "rmw_dsoftbus/transport_socket_backend.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <sys/time.h>

namespace rmw_dsoftbus {

// ============================================================================
// 辅助函数
// ============================================================================

const char* transport_mode_to_string(TransportMode mode) {
    switch (mode) {
        case TransportMode::AUTO: return "AUTO";
        case TransportMode::KH_TRANS_ONLY: return "KH_TRANS_ONLY";
        case TransportMode::SESSION_ONLY: return "SESSION_ONLY";
        case TransportMode::SOCKET_ONLY: return "SOCKET_ONLY";
        default: return "UNKNOWN";
    }
}

TransportMode string_to_transport_mode(const char* str) {
    if (!str) return TransportMode::AUTO;
    if (strcmp(str, "KH_TRANS") == 0 || strcmp(str, "KH_TRANS_ONLY") == 0) {
        return TransportMode::KH_TRANS_ONLY;
    }
    if (strcmp(str, "SESSION") == 0 || strcmp(str, "SESSION_ONLY") == 0) {
        return TransportMode::SESSION_ONLY;
    }
    if (strcmp(str, "SOCKET") == 0 || strcmp(str, "SOCKET_ONLY") == 0) {
        return TransportMode::SOCKET_ONLY;
    }
    return TransportMode::AUTO;
}

static uint64_t get_timestamp_us() {
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    return static_cast<uint64_t>(tv.tv_sec) * 1000000 + tv.tv_usec;
}

// ============================================================================
// FragmentAssembler 实现
// ============================================================================

bool FragmentAssembler::add_fragment(const FragmentHeader* header, const void* data, size_t len) {
    if (!header || !data || len == 0) return false;

    // 第一个分片 - 初始化
    if (total_frags_ == 0) {
        msg_id_ = header->msg_id;
        total_frags_ = header->total_frags;
        total_len_ = header->total_len;
        fragments_.resize(total_frags_);
        received_count_ = 0;
    }

    // 验证消息ID
    if (header->msg_id != msg_id_) {
        printf("[FragmentAssembler] WARNING: msg_id mismatch: expected %u, got %u\n",
               msg_id_, header->msg_id);
        return false;
    }

    // 验证索引
    if (header->frag_index >= total_frags_) {
        printf("[FragmentAssembler] ERROR: Invalid frag_index %u (total %u)\n",
               header->frag_index, total_frags_);
        return false;
    }

    // 存储分片
    auto& frag = fragments_[header->frag_index];
    if (!frag.received) {
        frag.data.resize(header->frag_len);
        memcpy(frag.data.data(), data, header->frag_len);
        frag.timestamp_us = get_timestamp_us();
        frag.received = true;
        received_count_++;
        last_update_time_ = frag.timestamp_us;
    }

    // 检查是否完整
    return (received_count_ == total_frags_);
}

int FragmentAssembler::get_complete_message(void* buffer, size_t buffer_len) {
    if (received_count_ != total_frags_) {
        return 0;  // 未完成
    }

    if (buffer_len < total_len_) {
        printf("[FragmentAssembler] ERROR: Buffer too small: %zu < %u\n",
               buffer_len, total_len_);
        return -1;
    }

    // 重组数据
    uint8_t* dest = static_cast<uint8_t*>(buffer);
    size_t offset = 0;

    for (size_t i = 0; i < total_frags_; ++i) {
        const auto& frag = fragments_[i];
        if (!frag.received) {
            printf("[FragmentAssembler] ERROR: Fragment %zu missing\n", i);
            return -1;
        }
        memcpy(dest + offset, frag.data.data(), frag.data.size());
        offset += frag.data.size();
    }

    if (offset != total_len_) {
        printf("[FragmentAssembler] WARNING: Size mismatch: assembled %zu, expected %u\n",
               offset, total_len_);
    }

    return static_cast<int>(offset);
}

void FragmentAssembler::reset() {
    msg_id_ = 0;
    total_frags_ = 0;
    received_count_ = 0;
    total_len_ = 0;
    fragments_.clear();
    last_update_time_ = 0;
}

bool FragmentAssembler::is_timeout() {
    if (last_update_time_ == 0) return false;
    uint64_t now = get_timestamp_us();
    return (now - last_update_time_) > 5000000;  // 5秒超时
}

// ============================================================================
// TransportController 实现
// ============================================================================

TransportController& TransportController::instance() {
    static TransportController instance;
    return instance;
}

bool TransportController::initialize(const char* pkg_name) {
    printf("[DEBUG][TransportController::initialize] called, pkg_name=%s, already_init=%d\n",
           pkg_name ? pkg_name : "NULL", initialized_ ? 1 : 0);
    fflush(stdout);

    if (initialized_) {
        printf("[TransportController] Already initialized\n");
        return true;
    }

    if (!pkg_name || strlen(pkg_name) == 0) {
        printf("[TransportController] ERROR: Invalid pkg_name\n");
        return false;
    }

    pkg_name_ = pkg_name;
    printf("[TransportController] Initializing with package: %s\n", pkg_name);

    // 加载配置
    load_config_from_env();

    // 创建后端 (按优先级顺序)
    backends_.emplace_back(std::make_unique<KhTransBackend>());
    backends_.emplace_back(std::make_unique<SessionBackend>());
    backends_.emplace_back(std::make_unique<SocketBackend>());

    // 初始化所有后端
    int available_count = 0;
    for (auto& backend : backends_) {
        if (backend->initialize(pkg_name)) {
            printf("[TransportController] Backend '%s' initialized (priority %d)\n",
                   backend->name(), backend->priority());
            available_count++;
        } else {
            printf("[TransportController] Backend '%s' unavailable\n",
                   backend->name());
        }
    }

    if (available_count == 0) {
        printf("[TransportController] ERROR: No available backends\n");
        return false;
    }

    // 按优先级排序后端
    std::sort(backends_.begin(), backends_.end(),
              [](const std::unique_ptr<TransportBackend>& a,
                 const std::unique_ptr<TransportBackend>& b) {
                  return a->priority() < b->priority();
              });

    initialized_ = true;
    printf("[TransportController] Initialized successfully (%d backends available)\n",
           available_count);

    print_backend_status();
    return true;
}

void TransportController::shutdown() {
    if (!initialized_) return;

    printf("[TransportController] Shutting down...\n");

    // 断开所有连接
    for (auto& [conn_id, info] : active_connections_) {
        if (info.backend) {
            info.backend->disconnect(info.backend_session_id);
        }
    }
    active_connections_.clear();

    // 关闭所有后端
    for (auto& backend : backends_) {
        backend->shutdown();
    }
    backends_.clear();

    initialized_ = false;
    printf("[TransportController] Shutdown complete\n");
}

void TransportController::set_mode(TransportMode mode) {
    mode_ = mode;
    printf("[TransportController] Transport mode set to: %s\n",
           transport_mode_to_string(mode));
}

void TransportController::load_config_from_env() {
    // 传输模式
    const char* mode_str = std::getenv("RMW_DSOFTBUS_TRANSPORT_MODE");
    if (mode_str) {
        mode_ = string_to_transport_mode(mode_str);
        printf("[TransportController] Mode from env: %s\n", transport_mode_to_string(mode_));
    }

    // 分片阈值
    const char* frag_threshold_str = std::getenv("RMW_DSOFTBUS_FRAGMENT_THRESHOLD");
    if (frag_threshold_str) {
        fragment_threshold_ = static_cast<size_t>(atoi(frag_threshold_str));
        printf("[TransportController] Fragment threshold: %zu bytes\n", fragment_threshold_);
    }

    // 启用分片
    const char* enable_frag_str = std::getenv("RMW_DSOFTBUS_ENABLE_FRAGMENTATION");
    if (enable_frag_str) {
        enable_fragmentation_ = (strcmp(enable_frag_str, "1") == 0 ||
                                  strcasecmp(enable_frag_str, "true") == 0);
        printf("[TransportController] Fragmentation: %s\n",
               enable_fragmentation_ ? "enabled" : "disabled");
    }
}

TransportBackend* TransportController::select_backend(size_t data_size, const TransportQoS& qos) {
    // 模式覆盖
    if (mode_ != TransportMode::AUTO) {
        const char* target_name = nullptr;
        switch (mode_) {
            case TransportMode::KH_TRANS_ONLY: target_name = "kh_trans"; break;
            case TransportMode::SESSION_ONLY: target_name = "session"; break;
            case TransportMode::SOCKET_ONLY: target_name = "socket"; break;
            default: break;
        }

        if (target_name) {
            for (auto& backend : backends_) {
                if (strcmp(backend->name(), target_name) == 0 && backend->is_available()) {
                    return backend.get();
                }
            }
            printf("[TransportController] WARNING: Forced mode '%s' but backend unavailable\n",
                   target_name);
            return nullptr;
        }
    }

    // 自动选择逻辑
    TransportBackend* best = nullptr;

    for (auto& backend : backends_) {
        if (!backend->is_available()) continue;

        // 检查载荷限制
        bool can_handle_directly = (data_size <= backend->max_payload_size());
        bool can_handle_fragmented = enable_fragmentation_ && qos.enable_fragmentation;

        if (!can_handle_directly && !can_handle_fragmented) {
            continue;  // 无法处理
        }

        // 优先级比较
        if (!best || backend->priority() < best->priority()) {
            // 特殊规则: 大数据 (>1KB) 倾向于 Session 或 Socket
            if (qos.large_data || data_size > 1024) {
                if (strcmp(backend->name(), "session") == 0 ||
                    strcmp(backend->name(), "socket") == 0) {
                    best = backend.get();
                    continue;
                }
            }

            // 小包优先 KH_TRANS
            if (data_size <= 960 && strcmp(backend->name(), "kh_trans") == 0) {
                best = backend.get();
                break;  // KH_TRANS 最优，直接返回
            }

            best = backend.get();
        }
    }

    if (best) {
        printf("[TransportController] Selected backend '%s' for %zu bytes\n",
               best->name(), data_size);
    } else {
        printf("[TransportController] WARNING: No suitable backend for %zu bytes\n", data_size);
    }

    return best;
}

int TransportController::connect(const char* peer_network_id, const TransportQoS& qos) {
    if (!initialized_) {
        printf("[TransportController] ERROR: Not initialized\n");
        return -1;
    }

    if (!peer_network_id || strlen(peer_network_id) == 0) {
        printf("[TransportController] ERROR: Invalid peer_network_id\n");
        return -2;
    }

    // 选择后端 (基于默认大小估计)
    TransportBackend* backend = select_backend(512, qos);
    if (!backend) {
        printf("[TransportController] ERROR: No available backend\n");
        return -3;
    }

    // 连接
    printf("[TransportController] Connecting via %s to %s\n",
           backend->name(), peer_network_id);

    int backend_session_id = backend->connect(peer_network_id, qos.timeout_ms);
    if (backend_session_id <= 0) {
        printf("[TransportController] ERROR: Connect failed: %d\n", backend_session_id);
        return -4;
    }

    // 分配连接ID
    int connection_id = next_connection_id_++;

    // 记录连接
    ConnectionInfo info;
    info.backend = backend;
    info.backend_session_id = backend_session_id;
    info.assembler = std::make_unique<FragmentAssembler>();
    active_connections_[connection_id] = std::move(info);

    printf("[TransportController] Connected: connection_id=%d, backend_session=%d, backend=%s\n",
           connection_id, backend_session_id, backend->name());

    return connection_id;
}

void TransportController::disconnect(int connection_id) {
    auto it = active_connections_.find(connection_id);
    if (it == active_connections_.end()) {
        printf("[TransportController] WARNING: Invalid connection_id %d\n", connection_id);
        return;
    }

    auto& info = it->second;
    if (info.backend) {
        info.backend->disconnect(info.backend_session_id);
        printf("[TransportController] Disconnected: connection_id=%d, backend=%s\n",
               connection_id, info.backend->name());
    }

    active_connections_.erase(it);
}

bool TransportController::is_connected(int connection_id) {
    auto it = active_connections_.find(connection_id);
    if (it == active_connections_.end()) return false;

    auto& info = it->second;
    if (!info.backend) return false;

    return info.backend->is_connected(info.backend_session_id);
}

int TransportController::send(int connection_id, const void* data, size_t len,
                               const TransportQoS& qos) {
    auto it = active_connections_.find(connection_id);
    if (it == active_connections_.end()) {
        printf("[TransportController] ERROR: Invalid connection_id %d\n", connection_id);
        return -1;
    }

    auto& info = it->second;
    if (!info.backend) {
        printf("[TransportController] ERROR: No backend for connection %d\n", connection_id);
        return -2;
    }

    // 检查是否需要分片
    size_t max_payload = info.backend->max_payload_size();
    bool needs_fragmentation = (len > max_payload) && enable_fragmentation_ &&
                                qos.enable_fragmentation;

    if (needs_fragmentation) {
        printf("[TransportController] Fragmenting %zu bytes (max_payload=%zu)\n",
               len, max_payload);
        return send_fragmented(connection_id, data, len, info.backend);
    } else {
        // 直接发送
        if (len > max_payload) {
            printf("[TransportController] ERROR: Data too large (%zu > %zu) and fragmentation disabled\n",
                   len, max_payload);
            return -3;
        }
        return info.backend->send(info.backend_session_id, data, len);
    }
}

int TransportController::send_fragmented(int connection_id, const void* data, size_t len,
                                          TransportBackend* backend) {
    if (!backend || !data || len == 0) return -1;

    auto it = active_connections_.find(connection_id);
    if (it == active_connections_.end()) return -2;

    int backend_session_id = it->second.backend_session_id;
    const size_t max_payload = backend->max_payload_size();
    const size_t max_frag_data = max_payload - FRAGMENT_HEADER_SIZE;

    if (max_frag_data == 0) {
        printf("[TransportController] ERROR: max_payload too small for fragmentation\n");
        return -3;
    }

    const size_t total_frags = (len + max_frag_data - 1) / max_frag_data;
    const uint32_t msg_id = generate_msg_id();

    printf("[TransportController] Sending %zu bytes in %zu fragments (msg_id=%u)\n",
           len, total_frags, msg_id);

    std::vector<uint8_t> buffer(max_payload);
    const uint8_t* src = static_cast<const uint8_t*>(data);
    size_t offset = 0;

    for (size_t i = 0; i < total_frags; ++i) {
        size_t frag_len = std::min(max_frag_data, len - offset);

        // 填充分片头
        FragmentHeader* hdr = reinterpret_cast<FragmentHeader*>(buffer.data());
        hdr->magic = FRAGMENT_MAGIC;
        hdr->total_frags = static_cast<uint16_t>(total_frags);
        hdr->frag_index = static_cast<uint16_t>(i);
        hdr->frag_len = static_cast<uint16_t>(frag_len);
        hdr->msg_id = msg_id;
        hdr->total_len = static_cast<uint32_t>(len);
        hdr->crc16 = calculate_crc16(src + offset, frag_len);
        memset(hdr->reserved, 0, sizeof(hdr->reserved));

        // 复制数据
        memcpy(buffer.data() + FRAGMENT_HEADER_SIZE, src + offset, frag_len);

        // 发送分片
        int ret = backend->send(backend_session_id, buffer.data(),
                                FRAGMENT_HEADER_SIZE + frag_len);
        if (ret != 0) {
            printf("[TransportController] ERROR: Fragment %zu/%zu send failed: %d\n",
                   i + 1, total_frags, ret);
            return ret;
        }

        offset += frag_len;
    }

    printf("[TransportController] Fragmented send complete: %zu fragments\n", total_frags);
    return 0;
}

int TransportController::recv(int connection_id, void* buffer, size_t buffer_len, int timeout_ms) {
    auto it = active_connections_.find(connection_id);
    if (it == active_connections_.end()) {
        return -1;
    }

    auto& info = it->second;
    if (!info.backend) return -2;

    // 接收数据
    int received = info.backend->recv(info.backend_session_id, buffer, buffer_len, timeout_ms);
    if (received <= 0) return received;

    // 检查是否为分片数据
    if (received < static_cast<int>(FRAGMENT_HEADER_SIZE)) {
        return received;  // 非分片数据
    }

    const FragmentHeader* hdr = static_cast<const FragmentHeader*>(buffer);
    if (hdr->magic != FRAGMENT_MAGIC) {
        return received;  // 非分片数据
    }

    // 处理分片
    const void* frag_data = static_cast<const uint8_t*>(buffer) + FRAGMENT_HEADER_SIZE;
    size_t frag_data_len = received - FRAGMENT_HEADER_SIZE;

    bool complete = info.assembler->add_fragment(hdr, frag_data, frag_data_len);
    if (!complete) {
        // 等待更多分片 (递归接收)
        return recv(connection_id, buffer, buffer_len, timeout_ms);
    }

    // 重组完整消息
    int total_len = info.assembler->get_complete_message(buffer, buffer_len);
    info.assembler->reset();

    return total_len;
}

TransportBackend* TransportController::get_active_backend(int connection_id) {
    auto it = active_connections_.find(connection_id);
    if (it == active_connections_.end()) return nullptr;
    return it->second.backend;
}

std::vector<TransportBackend*> TransportController::get_available_backends() {
    std::vector<TransportBackend*> available;
    for (auto& backend : backends_) {
        if (backend->is_available()) {
            available.push_back(backend.get());
        }
    }
    return available;
}

void TransportController::print_backend_status() {
    printf("\n=== Transport Backend Status ===\n");
    printf("Mode: %s\n", transport_mode_to_string(mode_));
    printf("Fragmentation: %s (threshold: %zu bytes)\n",
           enable_fragmentation_ ? "enabled" : "disabled", fragment_threshold_);
    printf("\nBackends (sorted by priority):\n");

    for (size_t i = 0; i < backends_.size(); ++i) {
        auto& backend = backends_[i];
        printf("  [%zu] %s - Priority %d, Max payload %zu bytes, %s\n",
               i + 1,
               backend->name(),
               backend->priority(),
               backend->max_payload_size(),
               backend->is_available() ? "AVAILABLE" : "unavailable");
    }

    printf("\nActive connections: %zu\n", active_connections_.size());
    printf("================================\n\n");
}

uint32_t TransportController::generate_msg_id() {
    return next_msg_id_++;
}

uint16_t TransportController::calculate_crc16(const void* data, size_t len) {
    const uint8_t* bytes = static_cast<const uint8_t*>(data);
    uint16_t crc = 0xFFFF;

    for (size_t i = 0; i < len; ++i) {
        crc ^= bytes[i];
        for (int j = 0; j < 8; ++j) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0xA001;
            } else {
                crc >>= 1;
            }
        }
    }

    return crc;
}

} // namespace rmw_dsoftbus
