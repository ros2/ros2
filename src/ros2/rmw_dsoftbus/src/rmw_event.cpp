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
#include <memory>

extern "C"
{

rmw_ret_t rmw_publisher_event_init(
    rmw_event_t * rmw_event,
    const rmw_publisher_t * publisher,
    rmw_event_type_t event_type)
{
    if (!rmw_event) {
        RMW_SET_ERROR_MSG("rmw_event is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!publisher) {
        RMW_SET_ERROR_MSG("publisher is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (publisher->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    // Allocate event implementation
    auto event_impl = new (std::nothrow) rmw_dsoftbus::EventImpl();
    if (!event_impl) {
        RMW_SET_ERROR_MSG("failed to allocate event impl");
        return RMW_RET_BAD_ALLOC;
    }

    event_impl->parent = const_cast<rmw_publisher_t*>(publisher);
    event_impl->event_type = static_cast<int>(event_type);

    rmw_event->implementation_identifier = rmw_get_implementation_identifier();
    rmw_event->data = event_impl;
    rmw_event->event_type = event_type;

    return RMW_RET_OK;
}

rmw_ret_t rmw_subscription_event_init(
    rmw_event_t * rmw_event,
    const rmw_subscription_t * subscription,
    rmw_event_type_t event_type)
{
    if (!rmw_event) {
        RMW_SET_ERROR_MSG("rmw_event is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!subscription) {
        RMW_SET_ERROR_MSG("subscription is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (subscription->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    // Allocate event implementation
    auto event_impl = new (std::nothrow) rmw_dsoftbus::EventImpl();
    if (!event_impl) {
        RMW_SET_ERROR_MSG("failed to allocate event impl");
        return RMW_RET_BAD_ALLOC;
    }

    event_impl->parent = const_cast<rmw_subscription_t*>(subscription);
    event_impl->event_type = static_cast<int>(event_type);

    rmw_event->implementation_identifier = rmw_get_implementation_identifier();
    rmw_event->data = event_impl;
    rmw_event->event_type = event_type;

    return RMW_RET_OK;
}

rmw_ret_t rmw_event_fini(rmw_event_t * rmw_event)
{
    if (!rmw_event) {
        RMW_SET_ERROR_MSG("rmw_event is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (rmw_event->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    auto event_impl = static_cast<rmw_dsoftbus::EventImpl*>(rmw_event->data);
    if (event_impl) {
        delete event_impl;
    }

    rmw_event->data = nullptr;

    return RMW_RET_OK;
}

rmw_ret_t rmw_take_event(
    const rmw_event_t * event_handle,
    void * event_info,
    bool * taken)
{
    if (!event_handle) {
        RMW_SET_ERROR_MSG("event_handle is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!event_info) {
        RMW_SET_ERROR_MSG("event_info is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!taken) {
        RMW_SET_ERROR_MSG("taken is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (event_handle->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    auto event_impl = static_cast<rmw_dsoftbus::EventImpl*>(event_handle->data);
    if (!event_impl) {
        RMW_SET_ERROR_MSG("event impl is null");
        return RMW_RET_ERROR;
    }

    if (event_impl->triggered) {
        event_impl->triggered = false;
        *taken = true;
        // TODO: Fill event_info based on event type
    } else {
        *taken = false;
    }

    return RMW_RET_OK;
}

rmw_ret_t rmw_event_set_callback(
    rmw_event_t * rmw_event,
    rmw_event_callback_t callback,
    const void * user_data)
{
    (void)rmw_event;
    (void)callback;
    (void)user_data;
    // Event callbacks not yet supported
    return RMW_RET_UNSUPPORTED;
}

}  // extern "C"
