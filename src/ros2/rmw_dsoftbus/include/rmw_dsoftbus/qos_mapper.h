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
// QoS Mapper - Maps ROS2 QoS profiles to dsoftbus configurations
// Follows the design pattern of rmw_fastrtps_shared_cpp/qos.hpp

#ifndef RMW_DSOFTBUS__QOS_MAPPER_H_
#define RMW_DSOFTBUS__QOS_MAPPER_H_

#include "rmw_dsoftbus/qos_types.h"
#include "rmw/qos_profiles.h"
#include "rmw/types.h"

namespace rmw_dsoftbus {

// ============================================================================
// Global QoS Mode Control
// ============================================================================

/// Get the current global QoS mode
/// This mode affects all new publishers/subscriptions
QosMode get_global_qos_mode();

/// Set the global QoS mode
/// @param mode The QoS mode to use for new connections
void set_global_qos_mode(QosMode mode);

/// Check if logging is enabled for the current QoS mode
bool is_logging_enabled();

// ============================================================================
// QoS Mapping Functions
// ============================================================================

/// Map ROS2 QoS profile to dsoftbus configuration
/// @param rmw_qos The ROS2 QoS profile
/// @return DsoftbusQosConfig with mapped settings
DsoftbusQosConfig map_qos_profile(const rmw_qos_profile_t* rmw_qos);

/// Map ROS2 QoS profile with explicit mode override
/// @param rmw_qos The ROS2 QoS profile
/// @param mode The QoS mode to use (overrides global mode)
/// @return DsoftbusQosConfig with mapped settings
DsoftbusQosConfig map_qos_profile_with_mode(
    const rmw_qos_profile_t* rmw_qos,
    QosMode mode);

/// Get default dsoftbus QoS config
/// Uses global QoS mode settings
DsoftbusQosConfig get_default_qos_config();

// ============================================================================
// QoS Compatibility Checking
// ============================================================================

/// Check if publisher and subscription QoS profiles are compatible
/// @param pub_qos Publisher QoS profile
/// @param sub_qos Subscription QoS profile
/// @return Compatibility result with reason if incompatible
QosCompatibilityResult check_qos_compatibility(
    const rmw_qos_profile_t* pub_qos,
    const rmw_qos_profile_t* sub_qos);

/// Check if publisher and subscription QoS configs are compatible
/// @param pub_config Publisher dsoftbus config
/// @param sub_config Subscription dsoftbus config
/// @return Compatibility result with reason if incompatible
QosCompatibilityResult check_dsoftbus_qos_compatibility(
    const DsoftbusQosConfig& pub_config,
    const DsoftbusQosConfig& sub_config);

// ============================================================================
// QoS Profile Utilities
// ============================================================================

/// Get history depth from QoS profile (with default fallback)
/// @param qos QoS profile
/// @param default_depth Default depth if not specified
/// @return Effective history depth
size_t get_effective_history_depth(
    const rmw_qos_profile_t* qos,
    size_t default_depth = 10);

/// Check if QoS profile requires reliable delivery
/// @param qos QoS profile
/// @return true if reliable delivery is required
bool is_reliable_qos(const rmw_qos_profile_t* qos);

/// Check if QoS profile requires transient local durability
/// @param qos QoS profile
/// @return true if transient local durability is required
bool is_transient_local_qos(const rmw_qos_profile_t* qos);

/// Convert QoS profile to human-readable string for logging
/// @param qos QoS profile
/// @param buffer Output buffer
/// @param buffer_size Size of output buffer
void qos_profile_to_string(
    const rmw_qos_profile_t* qos,
    char* buffer,
    size_t buffer_size);

/// Convert dsoftbus QoS config to human-readable string for logging
/// @param config dsoftbus QoS config
/// @param buffer Output buffer
/// @param buffer_size Size of output buffer
void dsoftbus_qos_to_string(
    const DsoftbusQosConfig& config,
    char* buffer,
    size_t buffer_size);

// ============================================================================
// Environment Variable Configuration (Future)
// ============================================================================

/// Environment variable for global QoS mode
/// Set to "RELIABLE_PLAIN" or "RELIABLE_SECURE"
#define RMW_DSOFTBUS_QOS_MODE_ENV "RMW_DSOFTBUS_QOS_MODE"

/// Initialize QoS settings from environment variables
/// Called during rmw_init
void init_qos_from_environment();

}  // namespace rmw_dsoftbus

#endif  // RMW_DSOFTBUS__QOS_MAPPER_H_
