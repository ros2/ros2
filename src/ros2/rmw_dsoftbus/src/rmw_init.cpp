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

#include "rmw_dsoftbus/discovery_manager.h"
#include "rmw_dsoftbus/graph_cache.h"
#include "rmw_dsoftbus/native_token.h"
#include "rmw_dsoftbus/publisher_discovery_handler.h"
#include "rmw_dsoftbus/qos_mapper.h"
#include "rmw_dsoftbus/rmw_dsoftbus.h"
#include "rmw_dsoftbus/session_manager.h"
#include "rmw_dsoftbus/types.h"

#include <cstdlib>
#include <cstring>
#include <memory>

// Global context for internal access
namespace rmw_dsoftbus {
static ContextImpl *g_context_impl = nullptr;
} // namespace rmw_dsoftbus

// Global options (outside namespace for extern "C" access)
static rmw_dsoftbus_options_t g_options = {
    RMW_DSOFTBUS_PACKAGE_NAME,
    RMW_DSOFTBUS_SESSION_PREFIX,
    5000,
    1000,
};

extern "C" {

const char *rmw_get_implementation_identifier(void) {
  return RMW_DSOFTBUS_IDENTIFIER;
}

const char *rmw_get_serialization_format(void) { return "cdr"; }

rmw_ret_t rmw_init_options_init(rmw_init_options_t *init_options,
                                rcutils_allocator_t allocator) {
  if (!init_options) {
    RMW_SET_ERROR_MSG("init_options is null");
    return RMW_RET_INVALID_ARGUMENT;
  }

  init_options->allocator = allocator;
  init_options->implementation_identifier = rmw_get_implementation_identifier();
  init_options->impl = nullptr;
  init_options->enclave = nullptr;
  init_options->domain_id = RMW_DEFAULT_DOMAIN_ID;
  init_options->security_options = rmw_get_zero_initialized_security_options();

  return RMW_RET_OK;
}

rmw_ret_t rmw_init_options_copy(const rmw_init_options_t *src,
                                rmw_init_options_t *dst) {
  if (!src || !dst) {
    RMW_SET_ERROR_MSG("src or dst is null");
    return RMW_RET_INVALID_ARGUMENT;
  }

  if (src->implementation_identifier != rmw_get_implementation_identifier()) {
    RMW_SET_ERROR_MSG("implementation identifier mismatch");
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
  }

  dst->allocator = src->allocator;
  dst->implementation_identifier = src->implementation_identifier;
  dst->domain_id = src->domain_id;
  dst->security_options = src->security_options;
  dst->impl = nullptr; // Don't copy impl

  if (src->enclave) {
    dst->enclave = rcutils_strdup(src->enclave, dst->allocator);
    if (!dst->enclave) {
      RMW_SET_ERROR_MSG("failed to copy enclave");
      return RMW_RET_BAD_ALLOC;
    }
  } else {
    dst->enclave = nullptr;
  }

  return RMW_RET_OK;
}

rmw_ret_t rmw_init_options_fini(rmw_init_options_t *init_options) {
  if (!init_options) {
    RMW_SET_ERROR_MSG("init_options is null");
    return RMW_RET_INVALID_ARGUMENT;
  }

  if (init_options->implementation_identifier !=
      rmw_get_implementation_identifier()) {
    RMW_SET_ERROR_MSG("implementation identifier mismatch");
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
  }

  if (init_options->enclave) {
    init_options->allocator.deallocate(
        const_cast<char *>(init_options->enclave),
        init_options->allocator.state);
    init_options->enclave = nullptr;
  }

  rmw_init_options_t zero_init = rmw_get_zero_initialized_init_options();
  *init_options = zero_init;

  return RMW_RET_OK;
}

rmw_ret_t rmw_init(const rmw_init_options_t *options, rmw_context_t *context) {
  fprintf(stderr, "[DEBUG][rmw_init] called: options=%p, context=%p\n",
          (void *)options, (void *)context);
  fflush(stderr);

  if (!options) {
    RMW_SET_ERROR_MSG("options is null");
    return RMW_RET_INVALID_ARGUMENT;
  }
  if (!context) {
    RMW_SET_ERROR_MSG("context is null");
    return RMW_RET_INVALID_ARGUMENT;
  }
  if (options->implementation_identifier !=
      rmw_get_implementation_identifier()) {
    RMW_SET_ERROR_MSG("implementation identifier mismatch");
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
  }

  (void)rmw_dsoftbus::try_init_native_token();

  // Initialize QoS settings from environment variables
  rmw_dsoftbus::init_qos_from_environment();

  // Allocate context implementation
  auto context_impl = new (std::nothrow) rmw_dsoftbus::ContextImpl();
  if (!context_impl) {
    RMW_SET_ERROR_MSG("failed to allocate context impl");
    return RMW_RET_BAD_ALLOC;
  }

  // Read peer network ID from environment: RMW_DSOFTBUS_PEER_ID
  const char *peer_id = std::getenv("RMW_DSOFTBUS_PEER_ID");
  if (peer_id && peer_id[0] != '\0') {
    context_impl->peer_network_id = peer_id;
    fprintf(stderr, "[INFO][rmw_dsoftbus] Peer network ID: %s\n", peer_id);
  } else {
    fprintf(
        stderr,
        "[INFO][rmw_dsoftbus] No peer network ID configured (local only)\n");
  }

  // Initialize SessionManager
  if (!rmw_dsoftbus::SessionManager::instance().initialize()) {
    delete context_impl;
    RMW_SET_ERROR_MSG("failed to initialize SessionManager");
    return RMW_RET_ERROR;
  }

  // Initialize GraphCache (Phase 2.2+)
  if (!rmw_dsoftbus::GraphCache::instance().initialize()) {
    rmw_dsoftbus::SessionManager::instance().shutdown();
    delete context_impl;
    RMW_SET_ERROR_MSG("failed to initialize GraphCache");
    return RMW_RET_ERROR;
  }

  // Initialize DiscoveryManager (Phase 2.3)
  if (!rmw_dsoftbus::DiscoveryManager::instance().initialize()) {
    // Discovery is optional - log warning but continue
    fprintf(stderr, "[WARN][rmw_dsoftbus] DiscoveryManager initialization "
                    "failed (cross-device discovery disabled)\n");
  }

  // Phase 4: Initialize Publisher Discovery Handler for 1:N auto-routing
  rmw_dsoftbus::init_publisher_discovery_handler();

  // Phase 4: Register subscriber discovery callbacks with GraphCache
  rmw_dsoftbus::GraphCache::instance().set_subscriber_callbacks(
      rmw_dsoftbus::on_subscriber_discovered,
      rmw_dsoftbus::on_subscriber_removed);

  fprintf(stderr, "[INFO][rmw_dsoftbus] Phase 4: 1:N auto-routing enabled\n");

  // Store global reference for publisher/subscription access
  rmw_dsoftbus::g_context_impl = context_impl;

  context_impl->is_initialized = true;
  context->implementation_identifier = rmw_get_implementation_identifier();
  context->impl = context_impl;

  fprintf(stderr, "[INFO][rmw_dsoftbus] Initialized with dsoftbus Session "
                  "backend (GraphCache + Discovery enabled)\n");
  fflush(stderr);

  return RMW_RET_OK;
}

rmw_ret_t rmw_shutdown(rmw_context_t *context) {
  fprintf(stderr, "[DEBUG][rmw_shutdown] called: context=%p\n",
          (void *)context);
  fflush(stderr);

  if (!context) {
    RMW_SET_ERROR_MSG("context is null");
    return RMW_RET_INVALID_ARGUMENT;
  }
  if (context->implementation_identifier !=
      rmw_get_implementation_identifier()) {
    RMW_SET_ERROR_MSG("implementation identifier mismatch");
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
  }

  auto context_impl = static_cast<rmw_dsoftbus::ContextImpl *>(context->impl);
  if (context_impl && context_impl->is_initialized) {
    // Shutdown in reverse order of initialization

    // 1. Phase 4: Clear subscriber callbacks before shutting down GraphCache
    rmw_dsoftbus::GraphCache::instance().set_subscriber_callbacks(nullptr, nullptr);

    // 2. Phase 4: Shutdown Publisher Discovery Handler
    rmw_dsoftbus::shutdown_publisher_discovery_handler();

    // 3. Shutdown DiscoveryManager (Phase 2.3)
    rmw_dsoftbus::DiscoveryManager::instance().shutdown();

    // 4. Shutdown GraphCache (Phase 2.2+)
    rmw_dsoftbus::GraphCache::instance().shutdown();

    // 5. Shutdown SessionManager
    rmw_dsoftbus::SessionManager::instance().shutdown();

    context_impl->is_initialized = false;
    rmw_dsoftbus::g_context_impl = nullptr;
  }

  return RMW_RET_OK;
}

rmw_ret_t rmw_context_fini(rmw_context_t *context) {
  if (!context) {
    RMW_SET_ERROR_MSG("context is null");
    return RMW_RET_INVALID_ARGUMENT;
  }
  if (context->implementation_identifier !=
      rmw_get_implementation_identifier()) {
    RMW_SET_ERROR_MSG("implementation identifier mismatch");
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
  }

  auto context_impl = static_cast<rmw_dsoftbus::ContextImpl *>(context->impl);
  if (context_impl) {
    if (context_impl->is_initialized) {
      rmw_shutdown(context);
    }
    delete context_impl;
    context->impl = nullptr;
  }

  rmw_context_t zero_context = rmw_get_zero_initialized_context();
  *context = zero_context;

  return RMW_RET_OK;
}

// rmw_dsoftbus specific API implementation
rmw_dsoftbus_options_t rmw_dsoftbus_get_default_options(void) {
  return {
      .package_name = RMW_DSOFTBUS_PACKAGE_NAME,
      .session_name_prefix = RMW_DSOFTBUS_SESSION_PREFIX,
      .connection_timeout_ms = 5000,
      .discovery_interval_ms = 1000,
  };
}

int rmw_dsoftbus_set_options(const rmw_dsoftbus_options_t *options) {
  if (!options) {
    return -1;
  }
  g_options = *options;
  return 0;
}

rmw_dsoftbus_options_t rmw_dsoftbus_get_options(void) { return g_options; }

} // extern "C"

// === Context Access API (for internal use by publisher/subscription) ===
namespace rmw_dsoftbus {

ContextImpl *get_context_impl() { return g_context_impl; }

} // namespace rmw_dsoftbus
