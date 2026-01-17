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

/**
 * @file publisher_discovery_handler.h
 *
 * @brief Publisher 1:N Auto-Discovery Handler
 *
 * Integrates with GraphCache to automatically establish sessions
 * from Publishers to newly discovered Subscribers.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef RMW_DSOFTBUS__PUBLISHER_DISCOVERY_HANDLER_H_
#define RMW_DSOFTBUS__PUBLISHER_DISCOVERY_HANDLER_H_

#include <string>
#include "rmw/types.h"

namespace rmw_dsoftbus {

// Forward declaration
struct PublisherImpl;

/**
 * @brief Handle subscriber discovery event
 *
 * @param topic_name Topic name
 * @param peer_network_id Remote device network ID
 * @param subscriber_gid Subscriber GID
 */
void on_subscriber_discovered(const std::string& topic_name,
                                const std::string& peer_network_id,
                                const rmw_gid_t& subscriber_gid);

/**
 * @brief Handle subscriber removal event
 *
 * @param topic_name Topic name
 * @param peer_network_id Remote device network ID
 * @param subscriber_gid Subscriber GID
 */
void on_subscriber_removed(const std::string& topic_name,
                             const std::string& peer_network_id,
                             const rmw_gid_t& subscriber_gid);

/**
 * @brief Register Publisher for auto-discovery
 *
 * @param topic_name Topic name
 * @param pub_impl Publisher implementation
 */
void register_publisher_for_discovery(const std::string& topic_name,
                                        PublisherImpl* pub_impl);

/**
 * @brief Unregister Publisher from auto-discovery
 *
 * @param topic_name Topic name
 * @param pub_impl Publisher implementation
 */
void unregister_publisher_from_discovery(const std::string& topic_name,
                                          PublisherImpl* pub_impl);

/**
 * @brief Initialize discovery handler
 */
void init_publisher_discovery_handler();

/**
 * @brief Shutdown discovery handler
 */
void shutdown_publisher_discovery_handler();

} // namespace rmw_dsoftbus

#endif  // RMW_DSOFTBUS__PUBLISHER_DISCOVERY_HANDLER_H_
