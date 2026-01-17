// Minimal mock for rmw/qos_profiles.h (for cross-compilation only)
#ifndef RMW__QOS_PROFILES_H_
#define RMW__QOS_PROFILES_H_

#include "rmw/types.h"

#ifdef __cplusplus
extern "C" {
#endif

// ============================================================================
// QoS Profiles
// ============================================================================

static const rmw_qos_profile_t rmw_qos_profile_sensor_data = {
    RMW_QOS_POLICY_HISTORY_KEEP_LAST, 5,
    RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT,
    RMW_QOS_POLICY_DURABILITY_VOLATILE,
    {0, 0}, {0, 0},
    RMW_QOS_POLICY_LIVELINESS_SYSTEM_DEFAULT,
    {0, 0}, false
};

static const rmw_qos_profile_t rmw_qos_profile_default = {
    RMW_QOS_POLICY_HISTORY_KEEP_LAST, 10,
    RMW_QOS_POLICY_RELIABILITY_RELIABLE,
    RMW_QOS_POLICY_DURABILITY_VOLATILE,
    {0, 0}, {0, 0},
    RMW_QOS_POLICY_LIVELINESS_SYSTEM_DEFAULT,
    {0, 0}, false
};

static const rmw_qos_profile_t rmw_qos_profile_services_default = {
    RMW_QOS_POLICY_HISTORY_KEEP_LAST, 10,
    RMW_QOS_POLICY_RELIABILITY_RELIABLE,
    RMW_QOS_POLICY_DURABILITY_VOLATILE,
    {0, 0}, {0, 0},
    RMW_QOS_POLICY_LIVELINESS_SYSTEM_DEFAULT,
    {0, 0}, false
};

static const rmw_qos_profile_t rmw_qos_profile_parameters = {
    RMW_QOS_POLICY_HISTORY_KEEP_LAST, 1000,
    RMW_QOS_POLICY_RELIABILITY_RELIABLE,
    RMW_QOS_POLICY_DURABILITY_VOLATILE,
    {0, 0}, {0, 0},
    RMW_QOS_POLICY_LIVELINESS_SYSTEM_DEFAULT,
    {0, 0}, false
};

static const rmw_qos_profile_t rmw_qos_profile_parameter_events = {
    RMW_QOS_POLICY_HISTORY_KEEP_LAST, 1000,
    RMW_QOS_POLICY_RELIABILITY_RELIABLE,
    RMW_QOS_POLICY_DURABILITY_VOLATILE,
    {0, 0}, {0, 0},
    RMW_QOS_POLICY_LIVELINESS_SYSTEM_DEFAULT,
    {0, 0}, false
};

static const rmw_qos_profile_t rmw_qos_profile_system_default = {
    RMW_QOS_POLICY_HISTORY_SYSTEM_DEFAULT, 0,
    RMW_QOS_POLICY_RELIABILITY_SYSTEM_DEFAULT,
    RMW_QOS_POLICY_DURABILITY_SYSTEM_DEFAULT,
    {0, 0}, {0, 0},
    RMW_QOS_POLICY_LIVELINESS_SYSTEM_DEFAULT,
    {0, 0}, false
};

static const rmw_qos_profile_t rmw_qos_profile_unknown = {
    RMW_QOS_POLICY_HISTORY_UNKNOWN, 0,
    RMW_QOS_POLICY_RELIABILITY_UNKNOWN,
    RMW_QOS_POLICY_DURABILITY_UNKNOWN,
    {0, 0}, {0, 0},
    RMW_QOS_POLICY_LIVELINESS_UNKNOWN,
    {0, 0}, false
};

#ifdef __cplusplus
}
#endif

#endif  // RMW__QOS_PROFILES_H_
