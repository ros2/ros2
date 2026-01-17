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
//
// Missing RMW API stubs required by RCL

#include "rmw_dsoftbus/rmw_dsoftbus.h"
#include "rmw_dsoftbus/types.h"
#include "rmw_dsoftbus/graph_cache.h"

#include <map>
#include <set>
#include <string>

extern "C"
{

// ============================================================================
// Loaned Message APIs (not supported - dsoftbus uses copy semantics)
// ============================================================================

rmw_ret_t rmw_publish_loaned_message(
    const rmw_publisher_t * publisher,
    void * ros_message,
    rmw_publisher_allocation_t * allocation)
{
    (void)publisher;
    (void)ros_message;
    (void)allocation;
    RMW_SET_ERROR_MSG("rmw_dsoftbus does not support loaned messages");
    return RMW_RET_UNSUPPORTED;
}

// ============================================================================
// Publisher Liveliness APIs
// ============================================================================

rmw_ret_t rmw_publisher_assert_liveliness(
    const rmw_publisher_t * publisher)
{
    if (!publisher) {
        RMW_SET_ERROR_MSG("publisher is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    // dsoftbus doesn't have explicit liveliness, always return OK
    return RMW_RET_OK;
}

// ============================================================================
// Node Liveliness API (deprecated in ROS2 Humble)
// ============================================================================

rmw_ret_t rmw_node_assert_liveliness(
    const rmw_node_t * node)
{
    // This function is deprecated in ROS2 Humble.
    // Per ROS2 documentation: "rmw_node_assert_liveliness implementation was removed.
    // If manual liveliness assertion is needed, use MANUAL_BY_TOPIC."
    if (!node) {
        RMW_SET_ERROR_MSG("node is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    // dsoftbus doesn't have explicit node-level liveliness
    // Return OK for backward compatibility
    return RMW_RET_OK;
}

rmw_ret_t rmw_publisher_wait_for_all_acked(
    const rmw_publisher_t * publisher,
    rmw_time_t wait_timeout)
{
    (void)publisher;
    (void)wait_timeout;
    // dsoftbus uses reliable transport, consider all messages acked
    return RMW_RET_OK;
}

// ============================================================================
// Content Filter APIs (not supported)
// ============================================================================

rmw_ret_t rmw_subscription_set_content_filter(
    rmw_subscription_t * subscription,
    const rmw_subscription_content_filter_options_t * options)
{
    (void)subscription;
    (void)options;
    RMW_SET_ERROR_MSG("rmw_dsoftbus does not support content filtering");
    return RMW_RET_UNSUPPORTED;
}

rmw_ret_t rmw_subscription_get_content_filter(
    const rmw_subscription_t * subscription,
    rcutils_allocator_t * allocator,
    rmw_subscription_content_filter_options_t * options)
{
    (void)subscription;
    (void)allocator;
    (void)options;
    RMW_SET_ERROR_MSG("rmw_dsoftbus does not support content filtering");
    return RMW_RET_UNSUPPORTED;
}

// ============================================================================
// Dynamic Message APIs (not supported)
// ============================================================================

rmw_ret_t rmw_take_dynamic_message_with_info(
    const rmw_subscription_t * subscription,
    rmw_dynamic_message_t * dynamic_message,
    bool * taken,
    rmw_message_info_t * message_info,
    rmw_subscription_allocation_t * allocation)
{
    (void)subscription;
    (void)dynamic_message;
    (void)taken;
    (void)message_info;
    (void)allocation;
    RMW_SET_ERROR_MSG("rmw_dsoftbus does not support dynamic messages");
    return RMW_RET_UNSUPPORTED;
}

// ============================================================================
// Callback APIs (stub implementations)
// ============================================================================

rmw_ret_t rmw_subscription_set_on_new_message_callback(
    rmw_subscription_t * subscription,
    rmw_event_callback_t callback,
    const void * user_data)
{
    (void)subscription;
    (void)callback;
    (void)user_data;
    // Not implemented, but return OK to allow operation
    return RMW_RET_OK;
}

rmw_ret_t rmw_service_set_on_new_request_callback(
    rmw_service_t * service,
    rmw_event_callback_t callback,
    const void * user_data)
{
    (void)service;
    (void)callback;
    (void)user_data;
    return RMW_RET_OK;
}

rmw_ret_t rmw_client_set_on_new_response_callback(
    rmw_client_t * client,
    rmw_event_callback_t callback,
    const void * user_data)
{
    (void)client;
    (void)callback;
    (void)user_data;
    return RMW_RET_OK;
}

// ============================================================================
// Service/Client QoS APIs
// ============================================================================

rmw_ret_t rmw_service_request_subscription_get_actual_qos(
    const rmw_service_t * service,
    rmw_qos_profile_t * qos)
{
    if (!service || !qos) {
        RMW_SET_ERROR_MSG("service or qos is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    // Return default reliable QoS for services
    qos->history = RMW_QOS_POLICY_HISTORY_KEEP_LAST;
    qos->depth = 10;
    qos->reliability = RMW_QOS_POLICY_RELIABILITY_RELIABLE;
    qos->durability = RMW_QOS_POLICY_DURABILITY_VOLATILE;
    return RMW_RET_OK;
}

rmw_ret_t rmw_service_response_publisher_get_actual_qos(
    const rmw_service_t * service,
    rmw_qos_profile_t * qos)
{
    if (!service || !qos) {
        RMW_SET_ERROR_MSG("service or qos is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    qos->history = RMW_QOS_POLICY_HISTORY_KEEP_LAST;
    qos->depth = 10;
    qos->reliability = RMW_QOS_POLICY_RELIABILITY_RELIABLE;
    qos->durability = RMW_QOS_POLICY_DURABILITY_VOLATILE;
    return RMW_RET_OK;
}

rmw_ret_t rmw_client_request_publisher_get_actual_qos(
    const rmw_client_t * client,
    rmw_qos_profile_t * qos)
{
    if (!client || !qos) {
        RMW_SET_ERROR_MSG("client or qos is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    qos->history = RMW_QOS_POLICY_HISTORY_KEEP_LAST;
    qos->depth = 10;
    qos->reliability = RMW_QOS_POLICY_RELIABILITY_RELIABLE;
    qos->durability = RMW_QOS_POLICY_DURABILITY_VOLATILE;
    return RMW_RET_OK;
}

rmw_ret_t rmw_client_response_subscription_get_actual_qos(
    const rmw_client_t * client,
    rmw_qos_profile_t * qos)
{
    if (!client || !qos) {
        RMW_SET_ERROR_MSG("client or qos is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    qos->history = RMW_QOS_POLICY_HISTORY_KEEP_LAST;
    qos->depth = 10;
    qos->reliability = RMW_QOS_POLICY_RELIABILITY_RELIABLE;
    qos->durability = RMW_QOS_POLICY_DURABILITY_VOLATILE;
    return RMW_RET_OK;
}

// ============================================================================
// Node Graph Query APIs (Phase 5 - Using GraphCache)
// ============================================================================

// Helper function to fill names_and_types from map
static rmw_ret_t fill_names_and_types(
    const std::map<std::string, std::set<std::string>>& data,
    rcutils_allocator_t* allocator,
    rmw_names_and_types_t* names_and_types)
{
    if (data.empty()) {
        names_and_types->names.size = 0;
        names_and_types->names.data = nullptr;
        names_and_types->types = nullptr;
        return RMW_RET_OK;
    }

    // Initialize names_and_types structure
    rmw_ret_t ret = rmw_names_and_types_init(names_and_types, data.size(), allocator);
    if (ret != RMW_RET_OK) {
        RMW_SET_ERROR_MSG("failed to initialize names_and_types");
        return ret;
    }

    // Fill in names and types
    size_t i = 0;
    for (const auto& [name, types] : data) {
        // Allocate name
        names_and_types->names.data[i] = rcutils_strdup(name.c_str(), *allocator);
        if (!names_and_types->names.data[i]) {
            rmw_names_and_types_fini(names_and_types);
            RMW_SET_ERROR_MSG("failed to allocate name");
            return RMW_RET_BAD_ALLOC;
        }

        // Allocate types array
        rcutils_ret_t rcret = rcutils_string_array_init(
            &names_and_types->types[i], types.size(), allocator);
        if (rcret != RCUTILS_RET_OK) {
            rmw_names_and_types_fini(names_and_types);
            RMW_SET_ERROR_MSG("failed to allocate types array");
            return RMW_RET_BAD_ALLOC;
        }

        // Copy type names
        size_t j = 0;
        for (const auto& type_name : types) {
            names_and_types->types[i].data[j] = rcutils_strdup(type_name.c_str(), *allocator);
            if (!names_and_types->types[i].data[j]) {
                rmw_names_and_types_fini(names_and_types);
                RMW_SET_ERROR_MSG("failed to allocate type name");
                return RMW_RET_BAD_ALLOC;
            }
            j++;
        }
        i++;
    }

    return RMW_RET_OK;
}

rmw_ret_t rmw_get_publisher_names_and_types_by_node(
    const rmw_node_t * node,
    rcutils_allocator_t * allocator,
    const char * node_name,
    const char * node_namespace,
    bool no_demangle,
    rmw_names_and_types_t * topic_names_and_types)
{
    if (!node) {
        RMW_SET_ERROR_MSG("node is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!allocator) {
        RMW_SET_ERROR_MSG("allocator is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!node_name) {
        RMW_SET_ERROR_MSG("node_name is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!node_namespace) {
        RMW_SET_ERROR_MSG("node_namespace is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!topic_names_and_types) {
        RMW_SET_ERROR_MSG("topic_names_and_types is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (node->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    (void)no_demangle;

    // Query GraphCache for publishers of this node
    auto data = rmw_dsoftbus::GraphCache::instance().get_publisher_names_and_types_by_node(
        node_name, node_namespace);

    return fill_names_and_types(data, allocator, topic_names_and_types);
}

rmw_ret_t rmw_get_subscriber_names_and_types_by_node(
    const rmw_node_t * node,
    rcutils_allocator_t * allocator,
    const char * node_name,
    const char * node_namespace,
    bool no_demangle,
    rmw_names_and_types_t * topic_names_and_types)
{
    if (!node) {
        RMW_SET_ERROR_MSG("node is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!allocator) {
        RMW_SET_ERROR_MSG("allocator is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!node_name) {
        RMW_SET_ERROR_MSG("node_name is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!node_namespace) {
        RMW_SET_ERROR_MSG("node_namespace is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!topic_names_and_types) {
        RMW_SET_ERROR_MSG("topic_names_and_types is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (node->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    (void)no_demangle;

    // Query GraphCache for subscribers of this node
    auto data = rmw_dsoftbus::GraphCache::instance().get_subscriber_names_and_types_by_node(
        node_name, node_namespace);

    return fill_names_and_types(data, allocator, topic_names_and_types);
}

rmw_ret_t rmw_get_service_names_and_types_by_node(
    const rmw_node_t * node,
    rcutils_allocator_t * allocator,
    const char * node_name,
    const char * node_namespace,
    rmw_names_and_types_t * service_names_and_types)
{
    if (!node) {
        RMW_SET_ERROR_MSG("node is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!allocator) {
        RMW_SET_ERROR_MSG("allocator is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!node_name) {
        RMW_SET_ERROR_MSG("node_name is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!node_namespace) {
        RMW_SET_ERROR_MSG("node_namespace is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!service_names_and_types) {
        RMW_SET_ERROR_MSG("service_names_and_types is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (node->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    // Query GraphCache for services of this node
    auto data = rmw_dsoftbus::GraphCache::instance().get_service_names_and_types_by_node(
        node_name, node_namespace);

    return fill_names_and_types(data, allocator, service_names_and_types);
}

rmw_ret_t rmw_get_client_names_and_types_by_node(
    const rmw_node_t * node,
    rcutils_allocator_t * allocator,
    const char * node_name,
    const char * node_namespace,
    rmw_names_and_types_t * service_names_and_types)
{
    if (!node) {
        RMW_SET_ERROR_MSG("node is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!allocator) {
        RMW_SET_ERROR_MSG("allocator is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!node_name) {
        RMW_SET_ERROR_MSG("node_name is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!node_namespace) {
        RMW_SET_ERROR_MSG("node_namespace is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!service_names_and_types) {
        RMW_SET_ERROR_MSG("service_names_and_types is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (node->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    // Query GraphCache for clients of this node
    auto data = rmw_dsoftbus::GraphCache::instance().get_client_names_and_types_by_node(
        node_name, node_namespace);

    return fill_names_and_types(data, allocator, service_names_and_types);
}

// ============================================================================
// Network Flow Endpoints (not supported)
// ============================================================================

rmw_ret_t rmw_publisher_get_network_flow_endpoints(
    const rmw_publisher_t * publisher,
    rcutils_allocator_t * allocator,
    rmw_network_flow_endpoint_array_t * network_flow_endpoint_array)
{
    (void)publisher;
    (void)allocator;
    if (!network_flow_endpoint_array) {
        RMW_SET_ERROR_MSG("network_flow_endpoint_array is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    network_flow_endpoint_array->size = 0;
    network_flow_endpoint_array->network_flow_endpoint = nullptr;
    return RMW_RET_OK;
}

rmw_ret_t rmw_subscription_get_network_flow_endpoints(
    const rmw_subscription_t * subscription,
    rcutils_allocator_t * allocator,
    rmw_network_flow_endpoint_array_t * network_flow_endpoint_array)
{
    (void)subscription;
    (void)allocator;
    if (!network_flow_endpoint_array) {
        RMW_SET_ERROR_MSG("network_flow_endpoint_array is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    network_flow_endpoint_array->size = 0;
    network_flow_endpoint_array->network_flow_endpoint = nullptr;
    return RMW_RET_OK;
}

// ============================================================================
// Feature Support Query
// ============================================================================

bool rmw_feature_supported(rmw_feature_t feature)
{
    switch (feature) {
        // dsoftbus supports basic pub/sub and service/client
        case RMW_FEATURE_MESSAGE_INFO_PUBLICATION_SEQUENCE_NUMBER:
        case RMW_FEATURE_MESSAGE_INFO_RECEPTION_SEQUENCE_NUMBER:
            return false;
        default:
            return false;
    }
}

// ============================================================================
// Serialization Support
// ============================================================================

rmw_ret_t rmw_serialization_support_init(
    const char * serialization_lib_name,
    rcutils_allocator_t * allocator,
    rosidl_dynamic_typesupport_serialization_support_t * serialization_support)
{
    (void)serialization_lib_name;
    (void)allocator;
    (void)serialization_support;
    // rmw_dsoftbus uses built-in CDR serialization
    RMW_SET_ERROR_MSG("rmw_dsoftbus uses built-in CDR serialization");
    return RMW_RET_UNSUPPORTED;
}

}  // extern "C"
