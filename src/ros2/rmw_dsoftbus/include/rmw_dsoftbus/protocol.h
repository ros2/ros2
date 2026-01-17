#ifndef RMW_DSOFTBUS_PROTOCOL_H_
#define RMW_DSOFTBUS_PROTOCOL_H_

#include <cstdint>
#include <string>
#include <vector>
#include <rmw/qos_profiles.h>

namespace rmw_dsoftbus {

/**
 * Protocol definition and constants for rmw_dsoftbus
 */

// ============================================================================
// Message Type Constants
// ============================================================================

constexpr uint32_t MAGIC_NUMBER = 0x524D5744;  // "RMWD"
constexpr uint16_t PROTOCOL_VERSION = 1;

enum MessageType {
    MSG_TYPE_DISCOVERY = 0x00,
    MSG_TYPE_DATA = 0x01,
    MSG_TYPE_SERVICE_REQUEST = 0x02,
    MSG_TYPE_SERVICE_REPLY = 0x03,
};

// ============================================================================
// Discovery Protocol
// ============================================================================

/**
 * Session name for discovery messages
 */
constexpr const char* DISCOVERY_SESSION_NAME = "rmw_dsoftbus_discovery";

/**
 * Session name for data messages
 */
constexpr const char* DATA_SESSION_NAME = "rmw_dsoftbus_data";

/**
 * Discovery broadcast interval in milliseconds
 */
constexpr uint32_t DISCOVERY_BROADCAST_INTERVAL_MS = 5000;

/**
 * Node timeout in milliseconds (node is removed from cache if not updated)
 */
constexpr uint32_t NODE_TIMEOUT_MS = 15000;

// ============================================================================
// Data Structures for Discovery
// ============================================================================

/**
 * Node information in discovery message
 */
struct NodeInfo {
    std::string node_name;      // e.g., "/talker"
    std::string namespace_;     // e.g., "/"
    std::string network_id;     // 64-char hex string from DSoftBus
    uint64_t timestamp_ms;      // When this info was created/updated
    std::string gid;            // Global ID (24 bytes hex encoded)
};

/**
 * Endpoint type enumeration
 */
enum class EndpointType {
    PUBLISHER = 0,
    SUBSCRIBER = 1,
    SERVICE = 2,
    CLIENT = 3,
};

/**
 * Endpoint information in discovery message
 */
struct EndpointInfo {
    EndpointType type;
    std::string topic_name;     // e.g., "/chatter"
    std::string type_name;      // e.g., "std_msgs::msg::String"
    std::string node_name;      // e.g., "/talker"
    std::string network_id;
    rmw_qos_profile_t qos;
    uint64_t timestamp_ms;
};

/**
 * Discovery message structure
 */
struct DiscoveryMessage {
    enum Type {
        NODE_ANNOUNCE,      // Local node announcement
        ENDPOINT_ANNOUNCE,  // New endpoint announcement
        GRAPH_SNAPSHOT,     // Complete graph snapshot
    };

    Type type;
    std::string source_network_id;
    uint64_t timestamp_ms;
    std::vector<NodeInfo> nodes;
    std::vector<EndpointInfo> endpoints;
};

// ============================================================================
// Data Message Header
// ============================================================================

/**
 * Data message header structure (1024 bytes total)
 *
 * Layout:
 *   Offset  Size  Field
 *   0       4     Magic (RMWD)
 *   4       2     Version
 *   6       2     Flags
 *   8       256   Topic Name (null-terminated)
 *   264     256   Type Name (null-terminated)
 *   520     8     Sequence Number
 *   528     4     Payload Size
 *   532     4     Checksum (CRC32)
 *   536     488   Reserved
 */
struct DataMessageHeader {
    uint32_t magic;             // MAGIC_NUMBER
    uint16_t version;           // PROTOCOL_VERSION
    uint16_t flags;             // Bit 0: fragmented, others reserved
    char topic_name[256];       // Null-terminated
    char type_name[256];        // Null-terminated
    uint64_t sequence_number;
    uint32_t payload_size;
    uint32_t checksum;          // CRC32 of payload
    uint8_t reserved[488];      // Total header = 1024 bytes

    DataMessageHeader() : magic(MAGIC_NUMBER), version(PROTOCOL_VERSION), flags(0),
                          sequence_number(0), payload_size(0), checksum(0) {
        memset(topic_name, 0, sizeof(topic_name));
        memset(type_name, 0, sizeof(type_name));
        memset(reserved, 0, sizeof(reserved));
    }
};

/**
 * Data message (header + payload)
 */
struct DataMessage {
    DataMessageHeader header;
    std::vector<uint8_t> payload;
    std::string source_network_id;  // For routing
};

// ============================================================================
// Service Request/Reply Messages
// ============================================================================

/**
 * Service request message header (512 bytes)
 */
struct ServiceRequestHeader {
    uint32_t magic;             // MAGIC_NUMBER
    uint16_t version;           // PROTOCOL_VERSION
    uint16_t type;              // MSG_TYPE_SERVICE_REQUEST
    char service_name[256];     // Null-terminated
    uint64_t request_id;        // Unique request ID
    char client_gid[24];        // Client global ID (hex encoded)
    uint32_t timeout_ms;        // Request timeout
    uint32_t payload_size;      // Request payload size
    uint8_t reserved[156];      // Total header = 512 bytes
};

/**
 * Service reply message header (512 bytes)
 */
struct ServiceReplyHeader {
    uint32_t magic;             // MAGIC_NUMBER
    uint16_t version;           // PROTOCOL_VERSION
    uint16_t type;              // MSG_TYPE_SERVICE_REPLY
    uint64_t request_id;        // Match to request
    uint16_t status_code;       // 0 = success, others = error
    uint16_t reserved1;
    uint32_t payload_size;      // Reply payload size
    uint8_t reserved[482];      // Total header = 512 bytes
};

// ============================================================================
// Utility Functions
// ============================================================================

/**
 * Calculate CRC32 checksum
 */
uint32_t calculate_crc32(const uint8_t* data, size_t length);

/**
 * Encode NodeInfo to JSON string (for Discovery protocol)
 */
std::string encode_node_info_json(const NodeInfo& node);

/**
 * Decode NodeInfo from JSON string
 */
bool decode_node_info_json(const std::string& json_str, NodeInfo& out_node);

/**
 * Encode DiscoveryMessage to JSON string
 */
std::string encode_discovery_message_json(const DiscoveryMessage& msg);

/**
 * Decode DiscoveryMessage from JSON string
 */
bool decode_discovery_message_json(const std::string& json_str, DiscoveryMessage& out_msg);

}  // namespace rmw_dsoftbus

#endif  // RMW_DSOFTBUS_PROTOCOL_H_
