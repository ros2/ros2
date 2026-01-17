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
#include "rosidl_runtime_c/sequence_bound.h"

extern "C"
{

// ============================================================================
// Publisher Allocation
// ============================================================================

rmw_ret_t rmw_init_publisher_allocation(
    const rosidl_message_type_support_t * type_support,
    const rosidl_runtime_c__Sequence__bound * message_bounds,
    rmw_publisher_allocation_t * allocation)
{
    // For rmw_dsoftbus, we use dynamic allocation (std::vector) in rmw_publish,
    // so pre-allocation is not strictly necessary. However, we provide a basic
    // implementation to satisfy RMW API requirements.

    (void)type_support;
    (void)message_bounds;

    if (!allocation) {
        RMW_SET_ERROR_MSG("allocation is null");
        return RMW_RET_INVALID_ARGUMENT;
    }

    // For dsoftbus, we don't need to preallocate as we use dynamic buffers.
    // Set impl to nullptr to indicate no preallocation was done.
    allocation->impl = nullptr;

    return RMW_RET_OK;
}

rmw_ret_t rmw_fini_publisher_allocation(
    rmw_publisher_allocation_t * allocation)
{
    if (!allocation) {
        RMW_SET_ERROR_MSG("allocation is null");
        return RMW_RET_INVALID_ARGUMENT;
    }

    // Since we don't actually allocate anything in init, nothing to free
    allocation->impl = nullptr;

    return RMW_RET_OK;
}

// ============================================================================
// Subscription Allocation
// ============================================================================

rmw_ret_t rmw_init_subscription_allocation(
    const rosidl_message_type_support_t * type_support,
    const rosidl_runtime_c__Sequence__bound * message_bounds,
    rmw_subscription_allocation_t * allocation)
{
    // For rmw_dsoftbus, we use dynamic allocation (std::vector) in rmw_take,
    // so pre-allocation is not strictly necessary. However, we provide a basic
    // implementation to satisfy RMW API requirements.

    (void)type_support;
    (void)message_bounds;

    if (!allocation) {
        RMW_SET_ERROR_MSG("allocation is null");
        return RMW_RET_INVALID_ARGUMENT;
    }

    // For dsoftbus, we don't need to preallocate as we use dynamic buffers.
    // Set impl to nullptr to indicate no preallocation was done.
    allocation->impl = nullptr;

    return RMW_RET_OK;
}

rmw_ret_t rmw_fini_subscription_allocation(
    rmw_subscription_allocation_t * allocation)
{
    if (!allocation) {
        RMW_SET_ERROR_MSG("allocation is null");
        return RMW_RET_INVALID_ARGUMENT;
    }

    // Since we don't actually allocate anything in init, nothing to free
    allocation->impl = nullptr;

    return RMW_RET_OK;
}

}  // extern "C"
