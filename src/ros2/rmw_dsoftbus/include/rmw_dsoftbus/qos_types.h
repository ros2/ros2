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

//
// QoS Types - Extensible QoS definitions for rmw_dsoftbus
// Design pattern follows FastRTPS/FastDDS QoS mapping approach

#ifndef RMW_DSOFTBUS__QOS_TYPES_H_
#define RMW_DSOFTBUS__QOS_TYPES_H_

#include <cstdint>
#include <cstddef>
#include <vector>

namespace rmw_dsoftbus {

// ============================================================================
// dsoftbus Native Types (from dsoftbus headers)
// ============================================================================

/// dsoftbus data types
enum DsoftbusDataType {
    DSOFTBUS_TYPE_MESSAGE = 1,  // Lightweight message
    DSOFTBUS_TYPE_BYTES = 2,    // Reliable byte stream
    DSOFTBUS_TYPE_FILE = 4,     // File transfer
    DSOFTBUS_TYPE_STREAM = 5,   // Stream data
};

/// dsoftbus encryption types
enum DsoftbusEncryptType {
    DSOFTBUS_ENCRYPT_DEFAULT = 0,  // dsoftbus default encryption
    DSOFTBUS_ENCRYPT_NONE = 1,     // No encryption
};

/// dsoftbus link types (priority order)
enum DsoftbusLinkType {
    DSOFTBUS_LINK_WIFI_5G = 1,    // 5GHz WiFi
    DSOFTBUS_LINK_WIFI_2G = 2,    // 2.4GHz WiFi
    DSOFTBUS_LINK_WIFI_P2P = 3,   // WiFi P2P
    DSOFTBUS_LINK_BR = 4,         // Bluetooth BR/EDR
    DSOFTBUS_LINK_BLE = 5,        // Bluetooth Low Energy
    DSOFTBUS_LINK_ETH = 10,       // Ethernet
    DSOFTBUS_LINK_KHPLC = 12,     // KaihongOS PLC
};

/// dsoftbus reliability level
enum DsoftbusReliability {
    DSOFTBUS_RELIABILITY_NONE = 1,  // Best effort
    DSOFTBUS_RELIABILITY_FULL = 2,  // Guaranteed delivery
    DSOFTBUS_RELIABILITY_HALF = 3,  // Partial reliability
};

// ============================================================================
// Simplified QoS Mode (Current Implementation)
// ============================================================================

/// Simplified QoS modes for dsoftbus communication
/// Maps common ROS2 QoS scenarios to practical dsoftbus configurations
enum class QosMode {
    /// High performance mode - No logging, no encryption
    /// - Encryption: DSOFTBUS_ENCRYPT_NONE
    /// - Reliability: DSOFTBUS_RELIABILITY_FULL
    /// - DataType: DSOFTBUS_TYPE_BYTES
    /// - Logging: Disabled
    /// - Use case: Development, debugging, performance testing
    RELIABLE_PLAIN = 0,

    /// Production mode - With logging, with encryption
    /// - Encryption: DSOFTBUS_ENCRYPT_DEFAULT
    /// - Reliability: DSOFTBUS_RELIABILITY_FULL
    /// - DataType: DSOFTBUS_TYPE_BYTES
    /// - Logging: Enabled
    /// - Use case: Production deployment, secure communication
    RELIABLE_SECURE = 1,

    // === Future extensible modes ===

    /// Best effort mode (planned)
    /// - Reliability: DSOFTBUS_RELIABILITY_NONE
    /// - Use case: Sensor data, video streaming
    // BEST_EFFORT_PLAIN = 2,

    /// Best effort with encryption (planned)
    // BEST_EFFORT_SECURE = 3,

    /// Low latency mode (planned)
    /// - Optimized for minimal delay
    // LOW_LATENCY = 4,

    /// High throughput mode (planned)
    /// - Optimized for bulk data transfer
    // HIGH_THROUGHPUT = 5,
};

/// Get string name for QoS mode
inline const char* qos_mode_to_string(QosMode mode) {
    switch (mode) {
        case QosMode::RELIABLE_PLAIN: return "RELIABLE_PLAIN";
        case QosMode::RELIABLE_SECURE: return "RELIABLE_SECURE";
        default: return "UNKNOWN";
    }
}

// ============================================================================
// Extended QoS Configuration (Extensible Design)
// ============================================================================

/// Complete dsoftbus QoS configuration
/// Designed to be extensible for future QoS policies
struct DsoftbusQosConfig {
    // === dsoftbus native parameters ===
    DsoftbusDataType data_type{DSOFTBUS_TYPE_BYTES};
    DsoftbusEncryptType encrypt_type{DSOFTBUS_ENCRYPT_DEFAULT};
    DsoftbusReliability reliability{DSOFTBUS_RELIABILITY_FULL};

    /// Link types in priority order
    std::vector<DsoftbusLinkType> link_types{
        DSOFTBUS_LINK_ETH,
        DSOFTBUS_LINK_WIFI_5G,
        DSOFTBUS_LINK_WIFI_2G
    };

    // === Local queue management (RMW layer) ===
    size_t history_depth{10};      // Message queue depth
    bool keep_all{false};          // KEEP_ALL history mode

    // === Durability simulation (RMW layer) ===
    bool transient_local{false};   // Cache messages for late joiners
    size_t durability_cache_size{100};

    // === Time-based policies (RMW layer, future) ===
    uint64_t deadline_ns{0};       // 0 = no deadline
    uint64_t lifespan_ns{0};       // 0 = infinite lifespan
    uint64_t liveliness_lease_ns{0};

    // === Liveliness (RMW layer, future) ===
    bool liveliness_automatic{true};

    // === Logging control ===
    bool logging_enabled{true};

    /// Create config from simplified QoS mode
    static DsoftbusQosConfig from_mode(QosMode mode) {
        DsoftbusQosConfig config;

        switch (mode) {
            case QosMode::RELIABLE_PLAIN:
                config.encrypt_type = DSOFTBUS_ENCRYPT_NONE;
                config.reliability = DSOFTBUS_RELIABILITY_FULL;
                config.data_type = DSOFTBUS_TYPE_BYTES;
                config.logging_enabled = false;
                break;

            case QosMode::RELIABLE_SECURE:
                config.encrypt_type = DSOFTBUS_ENCRYPT_DEFAULT;
                config.reliability = DSOFTBUS_RELIABILITY_FULL;
                config.data_type = DSOFTBUS_TYPE_BYTES;
                config.logging_enabled = true;
                break;

            default:
                // Default to secure mode
                config.encrypt_type = DSOFTBUS_ENCRYPT_DEFAULT;
                config.reliability = DSOFTBUS_RELIABILITY_FULL;
                config.logging_enabled = true;
        }

        return config;
    }

    /// Check if logging should be enabled
    bool should_log() const { return logging_enabled; }

    /// Get encryption type for dsoftbus SessionAttribute
    int get_dsoftbus_encrypt_type() const {
        return static_cast<int>(encrypt_type);
    }

    /// Get data type for dsoftbus SessionAttribute
    int get_dsoftbus_data_type() const {
        return static_cast<int>(data_type);
    }
};

// ============================================================================
// QoS Compatibility
// ============================================================================

/// QoS compatibility result
enum class QosCompatibility {
    OK = 0,                    // Fully compatible
    WARNING = 1,               // Compatible with warnings
    ERROR = 2,                 // Incompatible
};

/// QoS compatibility check result
struct QosCompatibilityResult {
    QosCompatibility status{QosCompatibility::OK};
    const char* reason{nullptr};
};

}  // namespace rmw_dsoftbus

#endif  // RMW_DSOFTBUS__QOS_TYPES_H_
