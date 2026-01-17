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

// Copyright (c) 2024 ROS2 KaihongOS Port Project
#include <string.h>  /* C memcpy/memset for OHOS SDK compatibility */
#include <stdlib.h>

// Licensed under the Apache License, Version 2.0

#include "rmw_dsoftbus/rmw_dsoftbus.h"
#include "rmw_dsoftbus/types.h"

#include <cstring>
#include <cstdio>

extern "C"
{

// Helper function to append reason string
static void append_reason(char* reason, size_t reason_size, size_t& offset, const char* msg)
{
    if (!reason || reason_size == 0) {
        return;
    }

    size_t msg_len = strlen(msg);
    size_t available = (offset < reason_size) ? (reason_size - offset - 1) : 0;

    if (available > 0) {
        size_t to_copy = (msg_len < available) ? msg_len : available;
        memcpy(reason + offset, msg, to_copy);
        offset += to_copy;
        reason[offset] = '\0';
    }
}

rmw_ret_t rmw_qos_profile_check_compatible(
    const rmw_qos_profile_t publisher_profile,
    const rmw_qos_profile_t subscription_profile,
    rmw_qos_compatibility_type_t * compatibility,
    char * reason,
    size_t reason_size)
{
    // Validate arguments
    if (!compatibility) {
        RMW_SET_ERROR_MSG("compatibility is null");
        return RMW_RET_INVALID_ARGUMENT;
    }

    if (!reason && reason_size != 0) {
        RMW_SET_ERROR_MSG("reason is null but reason_size is not zero");
        return RMW_RET_INVALID_ARGUMENT;
    }

    // Initialize output
    *compatibility = RMW_QOS_COMPATIBILITY_OK;
    if (reason && reason_size > 0) {
        reason[0] = '\0';
    }

    size_t offset = 0;
    bool has_error = false;
    bool has_warning = false;

    // ========================================================================
    // Check Reliability Compatibility
    // ========================================================================
    // Rule: Publisher reliability must be >= Subscriber reliability
    // RELIABLE (stronger) can communicate with BEST_EFFORT (weaker)
    // but BEST_EFFORT cannot satisfy RELIABLE requirements

    if (publisher_profile.reliability == RMW_QOS_POLICY_RELIABILITY_UNKNOWN ||
        subscription_profile.reliability == RMW_QOS_POLICY_RELIABILITY_UNKNOWN ||
        publisher_profile.reliability == RMW_QOS_POLICY_RELIABILITY_SYSTEM_DEFAULT ||
        subscription_profile.reliability == RMW_QOS_POLICY_RELIABILITY_SYSTEM_DEFAULT)
    {
        has_warning = true;
        append_reason(reason, reason_size, offset,
                     "Reliability policy contains UNKNOWN or SYSTEM_DEFAULT; ");
    }
    else if (subscription_profile.reliability == RMW_QOS_POLICY_RELIABILITY_RELIABLE &&
             publisher_profile.reliability == RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT)
    {
        has_error = true;
        append_reason(reason, reason_size, offset,
                     "Incompatible reliability: subscriber requires RELIABLE but publisher offers BEST_EFFORT; ");
    }

    // ========================================================================
    // Check Durability Compatibility
    // ========================================================================
    // Rule: Publisher durability must be >= Subscriber durability
    // TRANSIENT_LOCAL (stronger) can satisfy VOLATILE (weaker) requirements
    // but VOLATILE cannot satisfy TRANSIENT_LOCAL requirements

    if (publisher_profile.durability == RMW_QOS_POLICY_DURABILITY_UNKNOWN ||
        subscription_profile.durability == RMW_QOS_POLICY_DURABILITY_UNKNOWN ||
        publisher_profile.durability == RMW_QOS_POLICY_DURABILITY_SYSTEM_DEFAULT ||
        subscription_profile.durability == RMW_QOS_POLICY_DURABILITY_SYSTEM_DEFAULT)
    {
        has_warning = true;
        append_reason(reason, reason_size, offset,
                     "Durability policy contains UNKNOWN or SYSTEM_DEFAULT; ");
    }
    else if (subscription_profile.durability == RMW_QOS_POLICY_DURABILITY_TRANSIENT_LOCAL &&
             publisher_profile.durability == RMW_QOS_POLICY_DURABILITY_VOLATILE)
    {
        has_error = true;
        append_reason(reason, reason_size, offset,
                     "Incompatible durability: subscriber requires TRANSIENT_LOCAL but publisher offers VOLATILE; ");
    }

    // ========================================================================
    // Check History/Depth Compatibility
    // ========================================================================
    // For KEEP_LAST: Publisher depth should ideally be >= Subscriber depth
    // This is a warning, not an error, as some messages can still be delivered

    if (publisher_profile.history == RMW_QOS_POLICY_HISTORY_UNKNOWN ||
        subscription_profile.history == RMW_QOS_POLICY_HISTORY_UNKNOWN ||
        publisher_profile.history == RMW_QOS_POLICY_HISTORY_SYSTEM_DEFAULT ||
        subscription_profile.history == RMW_QOS_POLICY_HISTORY_SYSTEM_DEFAULT)
    {
        has_warning = true;
        append_reason(reason, reason_size, offset,
                     "History policy contains UNKNOWN or SYSTEM_DEFAULT; ");
    }
    else if (publisher_profile.history == RMW_QOS_POLICY_HISTORY_KEEP_LAST &&
             subscription_profile.history == RMW_QOS_POLICY_HISTORY_KEEP_LAST)
    {
        if (publisher_profile.depth < subscription_profile.depth) {
            has_warning = true;
            char depth_msg[256];
            snprintf(depth_msg, sizeof(depth_msg),
                    "History depth mismatch: publisher depth (%zu) < subscriber depth (%zu); ",
                    publisher_profile.depth, subscription_profile.depth);
            append_reason(reason, reason_size, offset, depth_msg);
        }
    }

    // ========================================================================
    // Check Liveliness Compatibility
    // ========================================================================
    // Stronger liveliness policies (MANUAL) can satisfy weaker ones (AUTOMATIC)

    if (publisher_profile.liveliness == RMW_QOS_POLICY_LIVELINESS_UNKNOWN ||
        subscription_profile.liveliness == RMW_QOS_POLICY_LIVELINESS_UNKNOWN ||
        publisher_profile.liveliness == RMW_QOS_POLICY_LIVELINESS_SYSTEM_DEFAULT ||
        subscription_profile.liveliness == RMW_QOS_POLICY_LIVELINESS_SYSTEM_DEFAULT)
    {
        has_warning = true;
        append_reason(reason, reason_size, offset,
                     "Liveliness policy contains UNKNOWN or SYSTEM_DEFAULT; ");
    }

    // ========================================================================
    // Determine Final Compatibility
    // ========================================================================

    if (has_error) {
        *compatibility = RMW_QOS_COMPATIBILITY_ERROR;
    } else if (has_warning) {
        *compatibility = RMW_QOS_COMPATIBILITY_WARNING;
    } else {
        *compatibility = RMW_QOS_COMPATIBILITY_OK;
    }

    return RMW_RET_OK;
}

}  // extern "C"
