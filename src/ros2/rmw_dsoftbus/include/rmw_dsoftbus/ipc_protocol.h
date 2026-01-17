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

#ifndef RMW_DSOFTBUS__IPC_PROTOCOL_H_
#define RMW_DSOFTBUS__IPC_PROTOCOL_H_

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

/**
 * @file ipc_protocol.h
 * @brief Local IPC protocol between librmw processes and rmw_dsoftbus_discoveryd daemon
 *
 * Design principles:
 * - Fixed 64-byte header for efficient parsing
 * - TLV (Type-Length-Value) payload encoding
 * - Aligned with cross-device discovery protocol semantics
 * - Daemon authority model: daemon owns graph state, librmw clients query/register
 * - No C++ exceptions (OpenHarmony -fno-exceptions compatibility)
 */

namespace rmw_dsoftbus {
namespace ipc {

// ============================================================
// Protocol Constants
// ============================================================

#define DISCOVERY_IPC_MAGIC        0x44534D49  // "IMSD" (IPC Msg DSoftbus)
#define DISCOVERY_IPC_VERSION      1
#define DISCOVERY_IPC_HEADER_SIZE  64

#define DISCOVERY_IPC_MAX_FRAME       (64 * 1024)   // Maximum payload size
#define DISCOVERY_IPC_MAX_TLV_VALUE   (16 * 1024)   // Maximum single TLV value
#define DISCOVERY_IPC_MAX_TLVS        256           // Maximum TLVs per message
#define DISCOVERY_IPC_MAX_CLIENTS     64            // Maximum concurrent clients

// ============================================================
// IPC Header (64 bytes, fixed layout)
// ============================================================

#pragma pack(push, 1)
struct DiscoveryIpcHeader {
    uint32_t magic;           // DISCOVERY_IPC_MAGIC
    uint16_t version;         // Protocol version (1)
    uint16_t header_len;      // Header size (64)
    uint16_t msg_type;        // DiscoveryIpcMsgType
    uint16_t flags;           // DiscoveryIpcFlags
    uint32_t payload_len;     // Payload size in bytes
    uint64_t seq;             // Request sequence number
    uint64_t graph_version;   // Daemon authoritative graph version
    uint64_t timestamp_ns;    // CLOCK_MONOTONIC timestamp
    int32_t  status;          // Response status (0=OK, <0=error)
    uint32_t crc32;           // CRC32 checksum (if F_HAS_CRC32 flag set)
    uint8_t  reserved[16];    // Reserved for future use (pad to 64 bytes)
};
#pragma pack(pop)

static_assert(sizeof(DiscoveryIpcHeader) == DISCOVERY_IPC_HEADER_SIZE,
              "IPC header must be exactly 64 bytes");

// ============================================================
// Message Types
// ============================================================

enum DiscoveryIpcMsgType : uint16_t {
    // Register (write operations)
    DISCOVERY_IPC_MSG_REGISTER_NODE       = 0x0101,
    DISCOVERY_IPC_MSG_UNREGISTER_NODE     = 0x0102,
    DISCOVERY_IPC_MSG_REGISTER_ENDPOINT   = 0x0111,
    DISCOVERY_IPC_MSG_UNREGISTER_ENDPOINT = 0x0112,

    // Query (read operations)
    DISCOVERY_IPC_MSG_GET_GRAPH_VERSION   = 0x0201,
    DISCOVERY_IPC_MSG_GET_SNAPSHOT        = 0x0202,
    DISCOVERY_IPC_MSG_COUNT_MATCHED       = 0x0203,

    // Notify (event subscription)
    DISCOVERY_IPC_MSG_SUBSCRIBE_GRAPH     = 0x0301,
    DISCOVERY_IPC_MSG_UNSUBSCRIBE_GRAPH   = 0x0302,
    DISCOVERY_IPC_MSG_EVENT_GRAPH_CHANGED = 0x0381,
};

// ============================================================
// Flags
// ============================================================

enum DiscoveryIpcFlags : uint16_t {
    DISCOVERY_IPC_FLAG_REQ       = 1u << 0,  // Request
    DISCOVERY_IPC_FLAG_RESP      = 1u << 1,  // Response
    DISCOVERY_IPC_FLAG_ONEWAY    = 1u << 2,  // No response expected
    DISCOVERY_IPC_FLAG_ERROR     = 1u << 3,  // Error response
    DISCOVERY_IPC_FLAG_HAS_CRC32 = 1u << 4,  // Payload has CRC32 (future)
};

// ============================================================
// TLV Encoding
// ============================================================

#pragma pack(push, 1)
struct DiscoveryTlv {
    uint16_t type;
    uint16_t reserved;  // Alignment and future extension
    uint32_t length;    // Value length in bytes
};
#pragma pack(pop)

// TLV Types - Node
#define DISCOVERY_TLV_NODE_NAMESPACE   0x0001  // string
#define DISCOVERY_TLV_NODE_NAME        0x0002  // string
#define DISCOVERY_TLV_NODE_ENCLAVE     0x0003  // string

// TLV Types - Endpoint
#define DISCOVERY_TLV_ENTITY_KIND      0x0010  // u32: DiscoveryEntityKind
#define DISCOVERY_TLV_TOPIC_NAME       0x0011  // string
#define DISCOVERY_TLV_TYPE_NAME        0x0012  // string
#define DISCOVERY_TLV_GID              0x0013  // bytes[24]
#define DISCOVERY_TLV_QOS_PROFILE      0x0014  // DiscoveryQosProfile (fixed struct)

// TLV Types - Query/Response
#define DISCOVERY_TLV_DIRECTION        0x0020  // u32: 0=publishers, 1=subscribers
#define DISCOVERY_TLV_COUNT            0x0021  // u32: matched endpoint count

// ============================================================
// Entity Kind (aligned with RMW)
// ============================================================

enum DiscoveryEntityKind : uint32_t {
    DISCOVERY_ENTITY_PUBLISHER    = 1,
    DISCOVERY_ENTITY_SUBSCRIPTION = 2,
    DISCOVERY_ENTITY_SERVICE      = 3,
    DISCOVERY_ENTITY_CLIENT       = 4,
};

// ============================================================
// QoS Profile (fixed binary structure, stable ABI)
// ============================================================

#pragma pack(push, 1)
struct DiscoveryQosProfile {
    uint32_t history;               // RMW_QOS_POLICY_HISTORY_*
    uint32_t depth;
    uint32_t reliability;           // RMW_QOS_POLICY_RELIABILITY_*
    uint32_t durability;            // RMW_QOS_POLICY_DURABILITY_*
    uint64_t deadline_ns;
    uint64_t lifespan_ns;
    uint64_t liveliness_lease_ns;
    uint32_t liveliness;            // RMW_QOS_POLICY_LIVELINESS_*
};
#pragma pack(pop)

// ============================================================
// TLV Helper Functions (no-exception version)
// ============================================================

struct TlvView {
    uint16_t type;
    const uint8_t* value;
    uint32_t length;
};

// Append raw bytes to buffer
inline void append_bytes(std::vector<uint8_t>& out, const void* p, size_t n) {
    const auto* b = static_cast<const uint8_t*>(p);
    out.insert(out.end(), b, b + n);
}

// Append u32 to buffer
inline void append_u32(std::vector<uint8_t>& out, uint32_t v) {
    append_bytes(out, &v, sizeof(v));
}

// Put TLV (generic) - returns false if value too large
inline bool tlv_put(std::vector<uint8_t>& out, uint16_t type, const void* data, uint32_t len) {
    if (len > DISCOVERY_IPC_MAX_TLV_VALUE) {
        return false;  // TLV value too large
    }
    DiscoveryTlv hdr{type, 0, len};
    append_bytes(out, &hdr, sizeof(hdr));
    if (len > 0) {
        append_bytes(out, data, len);
    }
    return true;
}

// Put string TLV
inline bool tlv_put_string(std::vector<uint8_t>& out, uint16_t type, const std::string& s) {
    return tlv_put(out, type, s.data(), static_cast<uint32_t>(s.size()));
}

// Put u32 TLV
inline bool tlv_put_u32(std::vector<uint8_t>& out, uint16_t type, uint32_t value) {
    return tlv_put(out, type, &value, sizeof(value));
}

// Put bytes TLV
inline bool tlv_put_bytes(std::vector<uint8_t>& out, uint16_t type, const void* data, size_t len) {
    return tlv_put(out, type, data, static_cast<uint32_t>(len));
}

// Parse TLV payload - returns false on error, results in out_tlvs
inline bool tlv_parse(const uint8_t* data, uint32_t len, std::vector<TlvView>& out_tlvs) {
    out_tlvs.clear();
    uint32_t offset = 0;

    while (offset + sizeof(DiscoveryTlv) <= len) {
        if (out_tlvs.size() >= DISCOVERY_IPC_MAX_TLVS) {
            return false;  // Too many TLVs
        }

        DiscoveryTlv hdr;
        std::memcpy(&hdr, data + offset, sizeof(hdr));
        offset += sizeof(hdr);

        if (hdr.length > DISCOVERY_IPC_MAX_TLV_VALUE) {
            return false;  // TLV value exceeds maximum size
        }

        if (offset + hdr.length > len) {
            return false;  // TLV length exceeds payload
        }

        out_tlvs.push_back(TlvView{hdr.type, data + offset, hdr.length});
        offset += hdr.length;
    }

    if (offset != len) {
        return false;  // Trailing bytes in TLV payload
    }

    return true;
}

// Legacy wrapper for backward compatibility
inline std::vector<TlvView> tlv_parse(const uint8_t* data, uint32_t len) {
    std::vector<TlvView> result;
    if (!tlv_parse(data, len, result)) {
        result.clear();
    }
    return result;
}

// Extract string from TLV
inline std::string tlv_as_string(const TlvView& tlv) {
    return std::string(reinterpret_cast<const char*>(tlv.value), tlv.length);
}

// Extract u32 from TLV - returns false if size mismatch
inline bool tlv_as_u32(const TlvView& tlv, uint32_t& out_value) {
    if (tlv.length != sizeof(uint32_t)) {
        return false;  // TLV is not u32
    }
    std::memcpy(&out_value, tlv.value, sizeof(out_value));
    return true;
}

// Legacy wrapper (returns 0 on error)
inline uint32_t tlv_as_u32(const TlvView& tlv) {
    uint32_t value = 0;
    tlv_as_u32(tlv, value);
    return value;
}

// Extract bytes from TLV - returns false if size mismatch
inline bool tlv_as_bytes(const TlvView& tlv, void* out, size_t expected_len) {
    if (tlv.length != expected_len) {
        return false;  // TLV size mismatch
    }
    std::memcpy(out, tlv.value, expected_len);
    return true;
}

// Find TLV by type
inline const TlvView* tlv_find(const std::vector<TlvView>& tlvs, uint16_t type) {
    for (const auto& t : tlvs) {
        if (t.type == type) return &t;
    }
    return nullptr;
}

}  // namespace ipc
}  // namespace rmw_dsoftbus

#endif  // RMW_DSOFTBUS__IPC_PROTOCOL_H_
