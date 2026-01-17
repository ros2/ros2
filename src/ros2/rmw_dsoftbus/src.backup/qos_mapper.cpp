// Copyright (c) 2024 ROS2 KaihongOS Port Project
// Licensed under the Apache License, Version 2.0
//
// QoS Mapper Implementation

#include "rmw_dsoftbus/qos_mapper.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <atomic>

namespace rmw_dsoftbus
{

// ============================================================================
// Global QoS Mode State
// ============================================================================

namespace {

/// Global QoS mode - defaults to RELIABLE_PLAIN for development
std::atomic<QosMode> g_global_qos_mode{QosMode::RELIABLE_PLAIN};

/// Flag to track if QoS was initialized from environment
std::atomic<bool> g_qos_initialized_from_env{false};

}  // anonymous namespace

QosMode get_global_qos_mode()
{
    return g_global_qos_mode.load();
}

void set_global_qos_mode(QosMode mode)
{
    g_global_qos_mode.store(mode);
}

bool is_logging_enabled()
{
    return get_global_qos_mode() == QosMode::RELIABLE_SECURE;
}

// ============================================================================
// Environment Variable Configuration
// ============================================================================

void init_qos_from_environment()
{
    if (g_qos_initialized_from_env.exchange(true)) {
        // Already initialized
        return;
    }

    const char* env_value = getenv(RMW_DSOFTBUS_QOS_MODE_ENV);
    if (env_value == nullptr) {
        return;
    }

    if (strcmp(env_value, "RELIABLE_PLAIN") == 0 ||
        strcmp(env_value, "0") == 0) {
        set_global_qos_mode(QosMode::RELIABLE_PLAIN);
    } else if (strcmp(env_value, "RELIABLE_SECURE") == 0 ||
               strcmp(env_value, "1") == 0) {
        set_global_qos_mode(QosMode::RELIABLE_SECURE);
    }
    // Unknown values are silently ignored, keeping default
}

// ============================================================================
// QoS Mapping Implementation
// ============================================================================

DsoftbusQosConfig map_qos_profile(const rmw_qos_profile_t* rmw_qos)
{
    return map_qos_profile_with_mode(rmw_qos, get_global_qos_mode());
}

DsoftbusQosConfig map_qos_profile_with_mode(
    const rmw_qos_profile_t* rmw_qos,
    QosMode mode)
{
    // Start with mode-based defaults
    DsoftbusQosConfig config = DsoftbusQosConfig::from_mode(mode);

    if (rmw_qos == nullptr) {
        return config;
    }

    // === Map History ===
    config.keep_all = (rmw_qos->history == RMW_QOS_POLICY_HISTORY_KEEP_ALL);
    config.history_depth = get_effective_history_depth(rmw_qos, 10);

    // === Map Reliability ===
    // Note: In current simplified implementation, both modes use RELIABLE
    // This mapping is preserved for future BEST_EFFORT support
    switch (rmw_qos->reliability) {
        case RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT:
            // Future: config.reliability = DSOFTBUS_RELIABILITY_NONE;
            // For now, still use reliable to ensure delivery
            config.reliability = DSOFTBUS_RELIABILITY_FULL;
            break;

        case RMW_QOS_POLICY_RELIABILITY_RELIABLE:
        case RMW_QOS_POLICY_RELIABILITY_SYSTEM_DEFAULT:
        case RMW_QOS_POLICY_RELIABILITY_BEST_AVAILABLE:
        default:
            config.reliability = DSOFTBUS_RELIABILITY_FULL;
            break;
    }

    // === Map Durability ===
    config.transient_local =
        (rmw_qos->durability == RMW_QOS_POLICY_DURABILITY_TRANSIENT_LOCAL);
    if (config.transient_local) {
        config.durability_cache_size = config.history_depth;
    }

    // === Map Time-based policies (stored for future use) ===
    // Deadline
    if (rmw_qos->deadline.sec != 0 || rmw_qos->deadline.nsec != 0) {
        config.deadline_ns = rmw_qos->deadline.sec * 1000000000ULL +
                             rmw_qos->deadline.nsec;
    }

    // Lifespan
    if (rmw_qos->lifespan.sec != 0 || rmw_qos->lifespan.nsec != 0) {
        config.lifespan_ns = rmw_qos->lifespan.sec * 1000000000ULL +
                             rmw_qos->lifespan.nsec;
    }

    // Liveliness lease duration
    if (rmw_qos->liveliness_lease_duration.sec != 0 ||
        rmw_qos->liveliness_lease_duration.nsec != 0) {
        config.liveliness_lease_ns =
            rmw_qos->liveliness_lease_duration.sec * 1000000000ULL +
            rmw_qos->liveliness_lease_duration.nsec;
    }

    // === Map Liveliness ===
    config.liveliness_automatic =
        (rmw_qos->liveliness == RMW_QOS_POLICY_LIVELINESS_AUTOMATIC ||
         rmw_qos->liveliness == RMW_QOS_POLICY_LIVELINESS_SYSTEM_DEFAULT);

    // === Select link types based on reliability requirement ===
    if (config.reliability == DSOFTBUS_RELIABILITY_FULL) {
        // For reliable transport, prefer wired/stable connections
        config.link_types = {
            DSOFTBUS_LINK_ETH,
            DSOFTBUS_LINK_WIFI_5G,
            DSOFTBUS_LINK_WIFI_2G,
            DSOFTBUS_LINK_WIFI_P2P
        };
    } else {
        // For best-effort, allow all link types
        config.link_types = {
            DSOFTBUS_LINK_WIFI_5G,
            DSOFTBUS_LINK_WIFI_2G,
            DSOFTBUS_LINK_ETH,
            DSOFTBUS_LINK_BLE,
            DSOFTBUS_LINK_BR
        };
    }

    return config;
}

DsoftbusQosConfig get_default_qos_config()
{
    return map_qos_profile(&rmw_qos_profile_default);
}

// ============================================================================
// QoS Compatibility Checking
// ============================================================================

QosCompatibilityResult check_qos_compatibility(
    const rmw_qos_profile_t* pub_qos,
    const rmw_qos_profile_t* sub_qos)
{
    QosCompatibilityResult result;
    result.status = QosCompatibility::OK;
    result.reason = nullptr;

    if (pub_qos == nullptr || sub_qos == nullptr) {
        return result;  // Null QoS = system default, always compatible
    }

    // === Reliability compatibility ===
    // BEST_EFFORT publisher cannot satisfy RELIABLE subscriber
    if (pub_qos->reliability == RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT &&
        sub_qos->reliability == RMW_QOS_POLICY_RELIABILITY_RELIABLE) {
        result.status = QosCompatibility::ERROR;
        result.reason = "BEST_EFFORT publisher cannot satisfy RELIABLE subscriber";
        return result;
    }

    // === Durability compatibility ===
    // VOLATILE publisher cannot satisfy TRANSIENT_LOCAL subscriber
    if (pub_qos->durability == RMW_QOS_POLICY_DURABILITY_VOLATILE &&
        sub_qos->durability == RMW_QOS_POLICY_DURABILITY_TRANSIENT_LOCAL) {
        result.status = QosCompatibility::ERROR;
        result.reason = "VOLATILE publisher cannot satisfy TRANSIENT_LOCAL subscriber";
        return result;
    }

    // === Deadline compatibility ===
    // Publisher deadline must be <= subscriber deadline
    // (More frequent publishing satisfies less stringent requirement)
    if (pub_qos->deadline.sec != 0 || pub_qos->deadline.nsec != 0) {
        uint64_t pub_deadline = pub_qos->deadline.sec * 1000000000ULL +
                                pub_qos->deadline.nsec;
        uint64_t sub_deadline = sub_qos->deadline.sec * 1000000000ULL +
                                sub_qos->deadline.nsec;

        if (sub_deadline != 0 && pub_deadline > sub_deadline) {
            result.status = QosCompatibility::WARNING;
            result.reason = "Publisher deadline is longer than subscriber deadline";
        }
    }

    return result;
}

QosCompatibilityResult check_dsoftbus_qos_compatibility(
    const DsoftbusQosConfig& pub_config,
    const DsoftbusQosConfig& sub_config)
{
    QosCompatibilityResult result;
    result.status = QosCompatibility::OK;
    result.reason = nullptr;

    // Currently, dsoftbus configs are always compatible within the same mode
    // Future: Add compatibility checks for different reliability levels

    return result;
}

// ============================================================================
// QoS Profile Utilities
// ============================================================================

size_t get_effective_history_depth(
    const rmw_qos_profile_t* qos,
    size_t default_depth)
{
    if (qos == nullptr) {
        return default_depth;
    }

    // KEEP_ALL uses a large default depth
    if (qos->history == RMW_QOS_POLICY_HISTORY_KEEP_ALL) {
        return (qos->depth > 0) ? qos->depth : 1000;
    }

    // KEEP_LAST uses specified depth or default
    return (qos->depth > 0) ? qos->depth : default_depth;
}

bool is_reliable_qos(const rmw_qos_profile_t* qos)
{
    if (qos == nullptr) {
        return true;  // Default is reliable
    }

    return qos->reliability == RMW_QOS_POLICY_RELIABILITY_RELIABLE ||
           qos->reliability == RMW_QOS_POLICY_RELIABILITY_SYSTEM_DEFAULT ||
           qos->reliability == RMW_QOS_POLICY_RELIABILITY_BEST_AVAILABLE;
}

bool is_transient_local_qos(const rmw_qos_profile_t* qos)
{
    if (qos == nullptr) {
        return false;  // Default is volatile
    }

    return qos->durability == RMW_QOS_POLICY_DURABILITY_TRANSIENT_LOCAL;
}

void qos_profile_to_string(
    const rmw_qos_profile_t* qos,
    char* buffer,
    size_t buffer_size)
{
    if (buffer == nullptr || buffer_size == 0) {
        return;
    }

    if (qos == nullptr) {
        snprintf(buffer, buffer_size, "QoS{null}");
        return;
    }

    const char* reliability_str = "?";
    switch (qos->reliability) {
        case RMW_QOS_POLICY_RELIABILITY_RELIABLE:
            reliability_str = "RELIABLE";
            break;
        case RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT:
            reliability_str = "BEST_EFFORT";
            break;
        case RMW_QOS_POLICY_RELIABILITY_SYSTEM_DEFAULT:
            reliability_str = "SYSTEM_DEFAULT";
            break;
        case RMW_QOS_POLICY_RELIABILITY_BEST_AVAILABLE:
            reliability_str = "BEST_AVAILABLE";
            break;
        default:
            reliability_str = "UNKNOWN";
    }

    const char* durability_str = "?";
    switch (qos->durability) {
        case RMW_QOS_POLICY_DURABILITY_VOLATILE:
            durability_str = "VOLATILE";
            break;
        case RMW_QOS_POLICY_DURABILITY_TRANSIENT_LOCAL:
            durability_str = "TRANSIENT_LOCAL";
            break;
        case RMW_QOS_POLICY_DURABILITY_SYSTEM_DEFAULT:
            durability_str = "SYSTEM_DEFAULT";
            break;
        default:
            durability_str = "UNKNOWN";
    }

    const char* history_str = "?";
    switch (qos->history) {
        case RMW_QOS_POLICY_HISTORY_KEEP_LAST:
            history_str = "KEEP_LAST";
            break;
        case RMW_QOS_POLICY_HISTORY_KEEP_ALL:
            history_str = "KEEP_ALL";
            break;
        case RMW_QOS_POLICY_HISTORY_SYSTEM_DEFAULT:
            history_str = "SYSTEM_DEFAULT";
            break;
        default:
            history_str = "UNKNOWN";
    }

    snprintf(buffer, buffer_size,
             "QoS{rel=%s, dur=%s, hist=%s, depth=%zu}",
             reliability_str, durability_str, history_str, qos->depth);
}

void dsoftbus_qos_to_string(
    const DsoftbusQosConfig& config,
    char* buffer,
    size_t buffer_size)
{
    if (buffer == nullptr || buffer_size == 0) {
        return;
    }

    const char* encrypt_str = (config.encrypt_type == DSOFTBUS_ENCRYPT_NONE) ?
                              "NONE" : "DEFAULT";
    const char* reliability_str = "?";
    switch (config.reliability) {
        case DSOFTBUS_RELIABILITY_FULL:
            reliability_str = "FULL";
            break;
        case DSOFTBUS_RELIABILITY_NONE:
            reliability_str = "NONE";
            break;
        case DSOFTBUS_RELIABILITY_HALF:
            reliability_str = "HALF";
            break;
    }

    snprintf(buffer, buffer_size,
             "DsoftbusQoS{encrypt=%s, rel=%s, depth=%zu, log=%s}",
             encrypt_str, reliability_str, config.history_depth,
             config.logging_enabled ? "ON" : "OFF");
}

}  // namespace rmw_dsoftbus
