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

#ifndef RMW_DSOFTBUS__RMW_DSOFTBUS_H_
#define RMW_DSOFTBUS__RMW_DSOFTBUS_H_

#include "rmw_dsoftbus/visibility.h"
#include "rmw/rmw.h"

#ifdef __cplusplus
extern "C" {
#endif

// Implementation identifier
// Use rmw_dsoftbus for native dsoftbus implementation
#define RMW_DSOFTBUS_IDENTIFIER "rmw_dsoftbus"

// rmw_dsoftbus specific configuration options
typedef struct rmw_dsoftbus_options_s {
    const char * package_name;
    const char * session_name_prefix;
    int connection_timeout_ms;
    int discovery_interval_ms;
} rmw_dsoftbus_options_t;

// ============================================================================
// QoS Mode Configuration
// ============================================================================

/// Simplified QoS modes for dsoftbus communication
/// These modes control logging and encryption behavior
typedef enum rmw_dsoftbus_qos_mode_e {
    /// No logging, no encryption - High performance mode
    /// Use for: Development, debugging, performance testing
    RMW_DSOFTBUS_QOS_RELIABLE_PLAIN = 0,

    /// With logging, with encryption - Production mode
    /// Use for: Production deployment, secure communication
    RMW_DSOFTBUS_QOS_RELIABLE_SECURE = 1,
} rmw_dsoftbus_qos_mode_t;

/// Set the global QoS mode for all new connections
/// @param mode The QoS mode to use
RMW_DSOFTBUS_PUBLIC
void rmw_dsoftbus_set_qos_mode(rmw_dsoftbus_qos_mode_t mode);

/// Get the current global QoS mode
/// @return The current QoS mode
RMW_DSOFTBUS_PUBLIC
rmw_dsoftbus_qos_mode_t rmw_dsoftbus_get_qos_mode(void);

// Get default configuration options
RMW_DSOFTBUS_PUBLIC
rmw_dsoftbus_options_t rmw_dsoftbus_get_default_options(void);

// Set configuration options (must be called before rmw_init)
RMW_DSOFTBUS_PUBLIC
int rmw_dsoftbus_set_options(const rmw_dsoftbus_options_t * options);

// Get current options
RMW_DSOFTBUS_PUBLIC
rmw_dsoftbus_options_t rmw_dsoftbus_get_options(void);

#ifdef __cplusplus
}
#endif

#endif  // RMW_DSOFTBUS__RMW_DSOFTBUS_H_
