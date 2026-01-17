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

// Copyright 2026 The rmw_dsoftbus Authors
// Licensed under the Apache License, Version 2.0

#ifndef RMW_DSOFTBUS__SERVICE_ENVELOPE_H_
#define RMW_DSOFTBUS__SERVICE_ENVELOPE_H_

#include <cstdint>
#include <atomic>
#include <cstring>

namespace rmw_dsoftbus {

/// Service message types
enum class ServiceMessageType : uint8_t {
    REQUEST = 0x02,
    RESPONSE = 0x03
};

/// ServiceEnvelope - Wire format header for Service request/response
///
/// Wire format:
/// [ServiceEnvelope: 16 bytes][CDR payload: N bytes]
///
/// This envelope provides:
/// 1. request_id: Correlation between request and response
/// 2. msg_type: Distinguish REQUEST from RESPONSE
/// 3. reserved: Future expansion (e.g., client_gid for 1:N routing in Phase 4)
///
#pragma pack(push, 1)
struct ServiceEnvelope {
    uint64_t request_id;     ///< Client-generated, echoed back in response
    uint8_t  msg_type;       ///< REQUEST=0x02, RESPONSE=0x03
    uint8_t  reserved[7];    ///< Alignment + future expansion

    /// Default constructor
    ServiceEnvelope()
        : request_id(0)
        , msg_type(static_cast<uint8_t>(ServiceMessageType::REQUEST))
    {
        std::memset(reserved, 0, sizeof(reserved));
    }

    /// Construct with specific values
    ServiceEnvelope(uint64_t req_id, ServiceMessageType type)
        : request_id(req_id)
        , msg_type(static_cast<uint8_t>(type))
    {
        std::memset(reserved, 0, sizeof(reserved));
    }

    /// Check if this is a request message
    bool is_request() const {
        return msg_type == static_cast<uint8_t>(ServiceMessageType::REQUEST);
    }

    /// Check if this is a response message
    bool is_response() const {
        return msg_type == static_cast<uint8_t>(ServiceMessageType::RESPONSE);
    }
};
#pragma pack(pop)

static_assert(sizeof(ServiceEnvelope) == 16, "ServiceEnvelope must be 16 bytes");

/// Generate a unique request ID (monotonically increasing)
///
/// Thread-safe. Starts from 1 (0 reserved for invalid).
/// At 1M requests/sec, overflow takes ~584 years.
inline uint64_t generate_request_id() {
    static std::atomic<uint64_t> counter{1};
    return counter.fetch_add(1, std::memory_order_relaxed);
}

/// Serialize ServiceEnvelope to buffer
///
/// @param envelope The envelope to serialize
/// @param buffer Output buffer (must have at least 16 bytes)
/// @return Number of bytes written (always 16)
inline size_t serialize_envelope(const ServiceEnvelope& envelope, uint8_t* buffer) {
    std::memcpy(buffer, &envelope, sizeof(ServiceEnvelope));
    return sizeof(ServiceEnvelope);
}

/// Deserialize ServiceEnvelope from buffer
///
/// @param buffer Input buffer (must have at least 16 bytes)
/// @param envelope Output envelope
/// @return Number of bytes read (always 16)
inline size_t deserialize_envelope(const uint8_t* buffer, ServiceEnvelope& envelope) {
    std::memcpy(&envelope, buffer, sizeof(ServiceEnvelope));
    return sizeof(ServiceEnvelope);
}

/// Minimum wire message size (envelope only, no payload)
constexpr size_t SERVICE_ENVELOPE_SIZE = sizeof(ServiceEnvelope);

}  // namespace rmw_dsoftbus

#endif  // RMW_DSOFTBUS__SERVICE_ENVELOPE_H_
