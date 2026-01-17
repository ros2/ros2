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

#include "rmw_dsoftbus/protocol.h"

#include <cinttypes>
#include <cstdint>
#include <cstring>

namespace rmw_dsoftbus {

// ============================================================================
// CRC32 Checksum Calculation
// ============================================================================

// CRC32 lookup table
static const uint32_t g_crc32_table[256] = {
    0x00000000L, 0x77073096L, 0xee0e612cL, 0x990951baL, 0x076dc419L, 0x706af48fL,
    0xe963a535L, 0x9e6495a3L, 0x0edb8832L, 0x79dcb8a4L, 0xe0d5e91eL, 0x97d2d988L,
    0x09b64c2bL, 0x7eb17cbdL, 0xe7b82d07L, 0x90bf1d91L, 0x1db71642L, 0x6ab020f2L,
    0xf3b97148L, 0x84be41deL, 0x1adad47dL, 0x6ddde4ebL, 0xf4d4b551L, 0x83d385c7L,
    0x136c9856L, 0x646ba8c0L, 0xfd62f97aL, 0x8a65c9ecL, 0x14015c4fL, 0x63066cd9L,
    0xfa44e5d6L, 0x8d079fd5L, 0x3b6e20c8L, 0x4c69105eL, 0xd56041e4L, 0xa2677172L,
    0x3c03e4d1L, 0x4b04d447L, 0xd20d85fdL, 0xa50ab56bL, 0x35b5a8faL, 0x42b2986cL,
    0xdbbbc9d6L, 0xacbcf940L, 0x32d86ce3L, 0x45df5c75L, 0xdcd60dcfL, 0xabd13d59L,
    0x26d930acL, 0x51de003aL, 0xc8d75180L, 0xbfd06116L, 0x21b4f4b5L, 0x56b3c423L,
    0xcfba9599L, 0xb8bda50fL, 0x2802b89eL, 0x5f058808L, 0xc60cd9b2L, 0xb10be924L,
    0x2f6f7c87L, 0x58684c11L, 0xc1611dabL, 0xb6662d3dL, 0x76dc4190L, 0x01db7106L,
    0x98d220bcL, 0xefd5102aL, 0x71b18589L, 0x06b6b51fL, 0x9fbfe4a5L, 0xe8b8d433L,
    0x7807c9a2L, 0x0f00f934L, 0x9609a88eL, 0xe10e9818L, 0x7f6a0dbbL, 0x086d3d2dL,
    0x91646c97L, 0xe6635c01L, 0x6b6b51f4L, 0x1c6c6162L, 0x856534d8L, 0xf262004eL,
    0x6c0695edL, 0x1b01a57bL, 0x8208f4c1L, 0xf50fc457L, 0x65b0d9c6L, 0x12b7e950L,
    0x8bbeb8eaL, 0xfcb9887cL, 0x62dd1ddfL, 0x15da2d49L, 0x8cd37cf3L, 0xfbd44c65L,
    0x4db26158L, 0x3ab551ceL, 0xa3bc0074L, 0xd4bb30e2L, 0x4adfa541L, 0x3dd895d7L,
    0xa4d1c46dL, 0xd3d6f4fbL, 0x4369e96aL, 0x346ed9fcL, 0xad678846L, 0xda60b8d0L,
    0x44042d73L, 0x33031de5L, 0xaa0a4c5fL, 0xdd0d7cc9L, 0x5005713cL, 0x270241aaL,
    0xbe0b1010L, 0xc90c2086L, 0x5a6bdf25L, 0x2d6d02b3L, 0xb405d309L, 0xc35e8f9fL,
    0x4a048feeL, 0x3d759ff8L, 0xa4dc2b02L, 0xd3c21b94L, 0x4d20c717L, 0x3adc00a1L,
    0xa3bc001bL, 0xd4bb30adL, 0x44042d7cL, 0x33031deaL, 0xaa0a4c50L, 0xdd0d7cc6L,
    0x5005713cL, 0x270241aaL, 0xbe0b1010L, 0xc90c2086L, 0x5a6bdf25L, 0x2d6d02b3L,
    0xb405d309L, 0xc35e8f9fL, 0x4a048feeL, 0x3d759ff8L, 0xa4dc2b02L, 0xd3c21b94L,
    0x4d20c717L, 0x3adc00a1L, 0xa3bc001bL, 0xd4bb30adL, 0x44042d7cL, 0x33031deaL,
    0xaa0a4c50L, 0xdd0d7cc6L, 0x5005713cL, 0x270241aaL, 0xbe0b1010L, 0xc90c2086L,
    0x5a6bdf25L, 0x2d6d02b3L, 0xb405d309L, 0xc35e8f9fL, 0x4a048feeL, 0x3d759ff8L,
    0xa4dc2b02L, 0xd3c21b94L, 0x4d20c717L, 0x3adc00a1L, 0xa3bc001bL, 0xd4bb30adL,
    0x44042d7cL, 0x33031deaL, 0xaa0a4c50L, 0xdd0d7cc6L, 0x5005713cL, 0x270241aaL,
    0xbe0b1010L, 0xc90c2086L, 0x5a6bdf25L, 0x2d6d02b3L, 0xb405d309L, 0xc35e8f9fL
};

uint32_t calculate_crc32(const uint8_t* data, size_t length) {
    uint32_t crc = 0xffffffffL;

    for (size_t i = 0; i < length; ++i) {
        uint32_t index = (crc ^ data[i]) & 0xff;
        crc = (crc >> 8) ^ g_crc32_table[index];
    }

    return crc ^ 0xffffffffL;
}

// ============================================================================
// Node Information Encoding/Decoding
// ============================================================================

// ============================================================================
// JSON Helper Functions (minimal implementation, no external library)
// ============================================================================

static std::string json_escape(const std::string& str) {
    std::string result;
    result.reserve(str.size());

    for (char c : str) {
        switch (c) {
            case '"':  result += "\\\""; break;
            case '\\': result += "\\\\"; break;
            case '\b': result += "\\b"; break;
            case '\f': result += "\\f"; break;
            case '\n': result += "\\n"; break;
            case '\r': result += "\\r"; break;
            case '\t': result += "\\t"; break;
            default:
                if (c < 32) {
                    char buf[8];
                    snprintf(buf, sizeof(buf), "\\u%04x", (unsigned char)c);
                    result += buf;
                } else {
                    result += c;
                }
        }
    }
    return result;
}

static bool json_find_string(const std::string& json, const std::string& key, std::string& value) {
    // Find key in JSON (simple parser)
    std::string search = "\"" + key + "\":\"";
    size_t pos = json.find(search);
    if (pos == std::string::npos) {
        return false;
    }

    size_t start = pos + search.length();
    size_t end = json.find("\"", start);
    if (end == std::string::npos) {
        return false;
    }

    value = json.substr(start, end - start);
    return true;
}

static bool json_find_uint64(const std::string& json, const std::string& key, uint64_t& value) {
    std::string search = "\"" + key + "\":";
    size_t pos = json.find(search);
    if (pos == std::string::npos) {
        return false;
    }

    size_t start = pos + search.length();
    size_t end = start;
    while (end < json.size() && (json[end] >= '0' && json[end] <= '9')) {
        ++end;
    }

    if (end == start) {
        return false;
    }

    std::string num_str = json.substr(start, end - start);
    value = strtoull(num_str.c_str(), nullptr, 10);
    return true;
}

// ============================================================================
// Node Information Encoding/Decoding
// ============================================================================

std::string encode_node_info_json(const NodeInfo& node) {
    char buffer[2048];
    snprintf(buffer, sizeof(buffer),
             "{"
             "\"node_name\":\"%s\","
             "\"namespace_\":\"%s\","
             "\"network_id\":\"%s\","
             "\"timestamp_ms\":%" PRIu64 ","
             "\"gid\":\"%s\""
             "}",
             json_escape(node.node_name).c_str(),
             json_escape(node.namespace_).c_str(),
             json_escape(node.network_id).c_str(),
             node.timestamp_ms,
             json_escape(node.gid).c_str());
    return std::string(buffer);
}

bool decode_node_info_json(const std::string& json_str, NodeInfo& out_node) {
    if (!json_find_string(json_str, "node_name", out_node.node_name)) {
        return false;
    }
    if (!json_find_string(json_str, "namespace_", out_node.namespace_)) {
        return false;
    }
    if (!json_find_string(json_str, "network_id", out_node.network_id)) {
        return false;
    }
    if (!json_find_uint64(json_str, "timestamp_ms", out_node.timestamp_ms)) {
        return false;
    }
    if (!json_find_string(json_str, "gid", out_node.gid)) {
        return false;
    }
    return true;
}

// ============================================================================
// Endpoint Information Encoding/Decoding
// ============================================================================

static std::string encode_endpoint_type(EndpointType type) {
    switch (type) {
        case EndpointType::PUBLISHER: return "PUBLISHER";
        case EndpointType::SUBSCRIBER: return "SUBSCRIBER";
        case EndpointType::SERVICE: return "SERVICE";
        case EndpointType::CLIENT: return "CLIENT";
        default: return "UNKNOWN";
    }
}

static bool decode_endpoint_type(const std::string& str, EndpointType& type) {
    if (str == "PUBLISHER") { type = EndpointType::PUBLISHER; return true; }
    if (str == "SUBSCRIBER") { type = EndpointType::SUBSCRIBER; return true; }
    if (str == "SERVICE") { type = EndpointType::SERVICE; return true; }
    if (str == "CLIENT") { type = EndpointType::CLIENT; return true; }
    return false;
}

static std::string encode_endpoint_info_json(const EndpointInfo& endpoint) {
    char buffer[2048];
    snprintf(buffer, sizeof(buffer),
             "{"
             "\"type\":\"%s\","
             "\"topic_name\":\"%s\","
             "\"type_name\":\"%s\","
             "\"node_name\":\"%s\","
             "\"network_id\":\"%s\","
             "\"timestamp_ms\":%" PRIu64
             "}",
             encode_endpoint_type(endpoint.type).c_str(),
             json_escape(endpoint.topic_name).c_str(),
             json_escape(endpoint.type_name).c_str(),
             json_escape(endpoint.node_name).c_str(),
             json_escape(endpoint.network_id).c_str(),
             endpoint.timestamp_ms);
    return std::string(buffer);
}

static bool decode_endpoint_info_json(const std::string& json_str, EndpointInfo& out_endpoint) {
    std::string type_str;
    if (!json_find_string(json_str, "type", type_str)) {
        return false;
    }
    if (!decode_endpoint_type(type_str, out_endpoint.type)) {
        return false;
    }
    if (!json_find_string(json_str, "topic_name", out_endpoint.topic_name)) {
        return false;
    }
    if (!json_find_string(json_str, "type_name", out_endpoint.type_name)) {
        return false;
    }
    if (!json_find_string(json_str, "node_name", out_endpoint.node_name)) {
        return false;
    }
    if (!json_find_string(json_str, "network_id", out_endpoint.network_id)) {
        return false;
    }
    if (!json_find_uint64(json_str, "timestamp_ms", out_endpoint.timestamp_ms)) {
        return false;
    }
    return true;
}

// ============================================================================
// Discovery Message Encoding/Decoding
// ============================================================================

std::string encode_discovery_message_json(const DiscoveryMessage& msg) {
    std::string result = "{";

    // Type
    result += "\"type\":";
    switch (msg.type) {
        case DiscoveryMessage::NODE_ANNOUNCE:
            result += "\"NODE_ANNOUNCE\"";
            break;
        case DiscoveryMessage::ENDPOINT_ANNOUNCE:
            result += "\"ENDPOINT_ANNOUNCE\"";
            break;
        case DiscoveryMessage::GRAPH_SNAPSHOT:
            result += "\"GRAPH_SNAPSHOT\"";
            break;
        default:
            result += "\"UNKNOWN\"";
    }

    // Source network ID
    result += ",\"source_network_id\":\"";
    result += json_escape(msg.source_network_id);
    result += "\"";

    // Timestamp
    char ts_buf[32];
    snprintf(ts_buf, sizeof(ts_buf), ",\"timestamp_ms\":%" PRIu64, msg.timestamp_ms);
    result += ts_buf;

    // Nodes
    result += ",\"nodes\":[";
    for (size_t i = 0; i < msg.nodes.size(); ++i) {
        if (i > 0) result += ",";
        result += encode_node_info_json(msg.nodes[i]);
    }
    result += "]";

    // Endpoints
    result += ",\"endpoints\":[";
    for (size_t i = 0; i < msg.endpoints.size(); ++i) {
        if (i > 0) result += ",";
        result += encode_endpoint_info_json(msg.endpoints[i]);
    }
    result += "]";

    result += "}";
    return result;
}

bool decode_discovery_message_json(const std::string& json_str, DiscoveryMessage& out_msg) {
    // Parse type
    std::string type_str;
    if (!json_find_string(json_str, "type", type_str)) {
        return false;
    }

    if (type_str == "NODE_ANNOUNCE") {
        out_msg.type = DiscoveryMessage::NODE_ANNOUNCE;
    } else if (type_str == "ENDPOINT_ANNOUNCE") {
        out_msg.type = DiscoveryMessage::ENDPOINT_ANNOUNCE;
    } else if (type_str == "GRAPH_SNAPSHOT") {
        out_msg.type = DiscoveryMessage::GRAPH_SNAPSHOT;
    } else {
        return false;
    }

    // Parse source_network_id
    if (!json_find_string(json_str, "source_network_id", out_msg.source_network_id)) {
        return false;
    }

    // Parse timestamp
    if (!json_find_uint64(json_str, "timestamp_ms", out_msg.timestamp_ms)) {
        return false;
    }

    // Parse nodes array (simple implementation - parse each object)
    // Note: This is a simplified parser that works for our specific format
    size_t nodes_start = json_str.find("\"nodes\":[");
    if (nodes_start != std::string::npos) {
        nodes_start += 9; // Skip "nodes":[
        size_t nodes_end = json_str.find("]", nodes_start);
        if (nodes_end != std::string::npos) {
            std::string nodes_str = json_str.substr(nodes_start, nodes_end - nodes_start);
            // Split by objects (simplified - assumes well-formed JSON)
            size_t pos = 0;
            while (pos < nodes_str.size()) {
                size_t obj_start = nodes_str.find("{", pos);
                if (obj_start == std::string::npos) break;
                size_t obj_end = nodes_str.find("}", obj_start);
                if (obj_end == std::string::npos) break;

                std::string node_json = nodes_str.substr(obj_start, obj_end - obj_start + 1);
                NodeInfo node;
                if (decode_node_info_json(node_json, node)) {
                    out_msg.nodes.push_back(node);
                }

                pos = obj_end + 1;
            }
        }
    }

    // Parse endpoints array (similar to nodes)
    size_t endpoints_start = json_str.find("\"endpoints\":[");
    if (endpoints_start != std::string::npos) {
        endpoints_start += 13; // Skip "endpoints":[
        size_t endpoints_end = json_str.find("]", endpoints_start);
        if (endpoints_end != std::string::npos) {
            std::string endpoints_str = json_str.substr(endpoints_start, endpoints_end - endpoints_start);
            size_t pos = 0;
            while (pos < endpoints_str.size()) {
                size_t obj_start = endpoints_str.find("{", pos);
                if (obj_start == std::string::npos) break;
                size_t obj_end = endpoints_str.find("}", obj_start);
                if (obj_end == std::string::npos) break;

                std::string endpoint_json = endpoints_str.substr(obj_start, obj_end - obj_start + 1);
                EndpointInfo endpoint;
                if (decode_endpoint_info_json(endpoint_json, endpoint)) {
                    out_msg.endpoints.push_back(endpoint);
                }

                pos = obj_end + 1;
            }
        }
    }

    return true;
}

}  // namespace rmw_dsoftbus
