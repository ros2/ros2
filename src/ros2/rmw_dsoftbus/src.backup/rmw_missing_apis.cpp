// Copyright (c) 2024 ROS2 KaihongOS Port Project
// Licensed under the Apache License, Version 2.0
//
// Missing RMW API stubs required by RCL

#include "rmw_dsoftbus/rmw_dsoftbus.h"
#include "rmw_dsoftbus/types.h"

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
// Node Graph Query APIs (minimal implementation)
// ============================================================================

rmw_ret_t rmw_get_publisher_names_and_types_by_node(
    const rmw_node_t * node,
    rcutils_allocator_t * allocator,
    const char * node_name,
    const char * node_namespace,
    bool no_demangle,
    rmw_names_and_types_t * topic_names_and_types)
{
    (void)node;
    (void)allocator;
    (void)node_name;
    (void)node_namespace;
    (void)no_demangle;
    if (!topic_names_and_types) {
        RMW_SET_ERROR_MSG("topic_names_and_types is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    // Return empty list - discovery not implemented for graph queries
    topic_names_and_types->names.size = 0;
    topic_names_and_types->names.data = nullptr;
    topic_names_and_types->types = nullptr;
    return RMW_RET_OK;
}

rmw_ret_t rmw_get_subscriber_names_and_types_by_node(
    const rmw_node_t * node,
    rcutils_allocator_t * allocator,
    const char * node_name,
    const char * node_namespace,
    bool no_demangle,
    rmw_names_and_types_t * topic_names_and_types)
{
    (void)node;
    (void)allocator;
    (void)node_name;
    (void)node_namespace;
    (void)no_demangle;
    if (!topic_names_and_types) {
        RMW_SET_ERROR_MSG("topic_names_and_types is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    topic_names_and_types->names.size = 0;
    topic_names_and_types->names.data = nullptr;
    topic_names_and_types->types = nullptr;
    return RMW_RET_OK;
}

rmw_ret_t rmw_get_service_names_and_types_by_node(
    const rmw_node_t * node,
    rcutils_allocator_t * allocator,
    const char * node_name,
    const char * node_namespace,
    rmw_names_and_types_t * service_names_and_types)
{
    (void)node;
    (void)allocator;
    (void)node_name;
    (void)node_namespace;
    if (!service_names_and_types) {
        RMW_SET_ERROR_MSG("service_names_and_types is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    service_names_and_types->names.size = 0;
    service_names_and_types->names.data = nullptr;
    service_names_and_types->types = nullptr;
    return RMW_RET_OK;
}

rmw_ret_t rmw_get_client_names_and_types_by_node(
    const rmw_node_t * node,
    rcutils_allocator_t * allocator,
    const char * node_name,
    const char * node_namespace,
    rmw_names_and_types_t * service_names_and_types)
{
    (void)node;
    (void)allocator;
    (void)node_name;
    (void)node_namespace;
    if (!service_names_and_types) {
        RMW_SET_ERROR_MSG("service_names_and_types is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    service_names_and_types->names.size = 0;
    service_names_and_types->names.data = nullptr;
    service_names_and_types->types = nullptr;
    return RMW_RET_OK;
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
