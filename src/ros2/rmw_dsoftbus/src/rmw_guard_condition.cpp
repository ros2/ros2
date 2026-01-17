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
#include <rcutils/allocator.h>  // Foundation layer memory management

#include <fcntl.h>
#include <cstring>
#include <memory>

extern "C"
{

rmw_guard_condition_t * rmw_create_guard_condition(rmw_context_t * context)
{
    if (!context) {
        RMW_SET_ERROR_MSG("context is null");
        return nullptr;
    }
    if (context->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return nullptr;
    }

    // Allocate guard condition implementation
    auto gc_impl = new (std::nothrow) rmw_dsoftbus::GuardConditionImpl();
    if (!gc_impl) {
        RMW_SET_ERROR_MSG("failed to allocate guard condition impl");
        return nullptr;
    }

    // Create pipe for wait notification
    if (pipe(gc_impl->pipe_fd) < 0) {
        delete gc_impl;
        RMW_SET_ERROR_MSG("failed to create pipe for guard condition");
        return nullptr;
    }

    // Set pipe to non-blocking
    int flags = fcntl(gc_impl->pipe_fd[0], F_GETFL, 0);
    fcntl(gc_impl->pipe_fd[0], F_SETFL, flags | O_NONBLOCK);
    flags = fcntl(gc_impl->pipe_fd[1], F_GETFL, 0);
    fcntl(gc_impl->pipe_fd[1], F_SETFL, flags | O_NONBLOCK);

    // Allocate rmw_guard_condition_t
    auto guard_condition = static_cast<rmw_guard_condition_t*>(
        malloc(sizeof(rmw_guard_condition_t)));
    if (!guard_condition) {
        close(gc_impl->pipe_fd[0]);
        close(gc_impl->pipe_fd[1]);
        gc_impl->pipe_fd[0] = -1;
        gc_impl->pipe_fd[1] = -1;
        delete gc_impl;
        RMW_SET_ERROR_MSG("failed to allocate rmw_guard_condition_t");
        return nullptr;
    }

    guard_condition->implementation_identifier = rmw_get_implementation_identifier();
    guard_condition->data = gc_impl;
    guard_condition->context = context;

    return guard_condition;
}

rmw_ret_t rmw_destroy_guard_condition(rmw_guard_condition_t * guard_condition)
{
    if (!guard_condition) {
        RMW_SET_ERROR_MSG("guard_condition is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (guard_condition->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    auto gc_impl = static_cast<rmw_dsoftbus::GuardConditionImpl*>(guard_condition->data);
    if (gc_impl) {
        // Destructor will close pipe fds
        delete gc_impl;
    }

    // Deallocate using Foundation layer allocator
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    allocator.deallocate(guard_condition, allocator.state);

    return RMW_RET_OK;
}

rmw_ret_t rmw_trigger_guard_condition(const rmw_guard_condition_t * guard_condition)
{
    if (!guard_condition) {
        RMW_SET_ERROR_MSG("guard_condition is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (guard_condition->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    auto gc_impl = static_cast<rmw_dsoftbus::GuardConditionImpl*>(guard_condition->data);
    if (!gc_impl) {
        RMW_SET_ERROR_MSG("guard condition impl is null");
        return RMW_RET_ERROR;
    }

    // Set triggered flag
    gc_impl->triggered.store(true);

    // Write to pipe to wake up any waiting select()
    if (gc_impl->pipe_fd[1] >= 0) {
        char c = 'x';
        // Ignore write errors (pipe might be full if triggered multiple times)
        write(gc_impl->pipe_fd[1], &c, 1);
    }

    // Notify condition variable waiters
    gc_impl->cv.notify_all();

    return RMW_RET_OK;
}

}  // extern "C"
