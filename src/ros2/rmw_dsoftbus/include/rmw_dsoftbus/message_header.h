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
/**
 * @file message_header.h
 *
 * @brief Declares message header structures for ROS2 message protocol.
 *
 * @since 1.0
 * @version 1.0
 */
#ifndef RMW_DSOFTBUS__MESSAGE_HEADER_H_
#define RMW_DSOFTBUS__MESSAGE_HEADER_H_

#include <cstdint>
#include <cstring>
#include <ctime>
#include <string>

namespace rmw_dsoftbus {

// Message types for protocol differentiation
enum class MessageType : uint8_t {
    PUBLISH = 0x01,
    REQUEST = 0x02,
    RESPONSE = 0x03,
    HEARTBEAT = 0x04,
    DISCOVERY = 0x05,
};

// GID size matches RMW_GID_STORAGE_SIZE (24 bytes)
constexpr size_t GID_SIZE = 24;

// Message header for all dsoftbus transmissions
// This header is prepended to all serialized data
// Layout (52 bytes total with pragma pack(1)):
//   magic[4] + version(1) + msg_type(1) + flags(2) + sequence_number(8)
//   + timestamp_ns(8) + publisher_gid[24] + data_length(4) = 52 bytes
#pragma pack(push, 1)
struct MessageHeader {
    uint8_t magic[4];           // "RMW2" magic bytes (4)
    uint8_t version;            // Protocol version (1) (1)
    MessageType msg_type;       // Message type (1)
    uint16_t flags;             // Reserved flags (2)
    uint64_t sequence_number;   // Publisher sequence number (8)
    uint64_t timestamp_ns;      // Source timestamp (nanoseconds since epoch) (8)
    uint8_t publisher_gid[GID_SIZE];  // Publisher GID (24)
    uint32_t data_length;       // Length of payload after header (4)
    // Total: 4+1+1+2+8+8+24+4 = 52 bytes

    MessageHeader()
        : magic{'R', 'M', 'W', '2'}
        , version(1)
        , msg_type(MessageType::PUBLISH)
        , flags(0)
        , sequence_number(0)
        , timestamp_ns(0)
        , data_length(0)
    {
        memset(publisher_gid, 0, sizeof(publisher_gid));
    }

    bool is_valid() const {
        return magic[0] == 'R' && magic[1] == 'M' && magic[2] == 'W' &&
               magic[3] == '2' && version == 1;
    }
};
#pragma pack(pop)

static_assert(sizeof(MessageHeader) == 52, "MessageHeader size mismatch");

// Service request/response header
#pragma pack(push, 1)
struct ServiceHeader {
    MessageHeader base;
    int64_t request_id;         // Request sequence ID for matching
    uint8_t client_gid[GID_SIZE];  // Client GID for routing response

    ServiceHeader() : base(), request_id(0) {
        base.msg_type = MessageType::REQUEST;
        memset(client_gid, 0, sizeof(client_gid));
    }
};
#pragma pack(pop)

// Topic name encoding/decoding
// Format: ros2/<namespace>/<topic_name>
// Example: ros2/robot1/cmd_vel

inline std::string encode_topic_name(
    const char* namespace_,
    const char* topic_name)
{
    std::string result = "ros2";
    if (namespace_ && namespace_[0] != '\0') {
        if (namespace_[0] != '/') {
            result += "/";
        }
        result += namespace_;
    }
    if (topic_name) {
        if (topic_name[0] != '/') {
            result += "/";
        }
        result += topic_name;
    }
    return result;
}

inline std::string encode_service_name(
    const char* namespace_,
    const char* service_name)
{
    std::string result = "ros2_srv";
    if (namespace_ && namespace_[0] != '\0') {
        if (namespace_[0] != '/') {
            result += "/";
        }
        result += namespace_;
    }
    if (service_name) {
        if (service_name[0] != '/') {
            result += "/";
        }
        result += service_name;
    }
    return result;
}

// Get current timestamp in nanoseconds
inline uint64_t get_timestamp_ns()
{
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return static_cast<uint64_t>(ts.tv_sec) * 1000000000ULL +
           static_cast<uint64_t>(ts.tv_nsec);
}

}  // namespace rmw_dsoftbus

#endif  // RMW_DSOFTBUS__MESSAGE_HEADER_H_
