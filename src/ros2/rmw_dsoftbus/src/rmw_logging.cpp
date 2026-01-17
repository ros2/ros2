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

extern "C"
{

// Global log severity level (static storage)
static rmw_log_severity_t g_rmw_log_severity = RMW_LOG_SEVERITY_INFO;

rmw_ret_t rmw_set_log_severity(rmw_log_severity_t severity)
{
    // Validate severity value
    if (severity < RMW_LOG_SEVERITY_DEBUG || severity > RMW_LOG_SEVERITY_FATAL) {
        RMW_SET_ERROR_MSG("invalid log severity value");
        return RMW_RET_INVALID_ARGUMENT;
    }

    // Set the global log severity
    g_rmw_log_severity = severity;

    // Note: In a full implementation, this would also propagate to rcutils logging
    // via rcutils_logging_set_default_logger_level(severity)
    // For now, we just store it for rmw_dsoftbus internal use

    return RMW_RET_OK;
}

}  // extern "C"
