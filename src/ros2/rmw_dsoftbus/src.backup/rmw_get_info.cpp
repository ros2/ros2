// Copyright (c) 2024 ROS2 KaihongOS Port Project
// Licensed under the Apache License, Version 2.0

#include "rmw_dsoftbus/rmw_dsoftbus.h"
#include "rmw_dsoftbus/types.h"

extern "C"
{

rmw_ret_t rmw_get_node_names(
    const rmw_node_t * node,
    rcutils_string_array_t * node_names,
    rcutils_string_array_t * node_namespaces)
{
    if (!node) {
        RMW_SET_ERROR_MSG("node is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!node_names) {
        RMW_SET_ERROR_MSG("node_names is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!node_namespaces) {
        RMW_SET_ERROR_MSG("node_namespaces is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (node->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    // TODO: Implement node discovery via dsoftbus
    // For now, return empty arrays
    node_names->size = 0;
    node_namespaces->size = 0;

    return RMW_RET_OK;
}

rmw_ret_t rmw_get_node_names_with_enclaves(
    const rmw_node_t * node,
    rcutils_string_array_t * node_names,
    rcutils_string_array_t * node_namespaces,
    rcutils_string_array_t * enclaves)
{
    if (!enclaves) {
        RMW_SET_ERROR_MSG("enclaves is null");
        return RMW_RET_INVALID_ARGUMENT;
    }

    rmw_ret_t ret = rmw_get_node_names(node, node_names, node_namespaces);
    if (ret != RMW_RET_OK) {
        return ret;
    }

    enclaves->size = 0;

    return RMW_RET_OK;
}

rmw_ret_t rmw_get_topic_names_and_types(
    const rmw_node_t * node,
    rcutils_allocator_t * allocator,
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
    if (!topic_names_and_types) {
        RMW_SET_ERROR_MSG("topic_names_and_types is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (node->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    (void)no_demangle;

    // TODO: Implement topic discovery
    topic_names_and_types->names.size = 0;
    topic_names_and_types->names.data = nullptr;
    topic_names_and_types->types = nullptr;

    return RMW_RET_OK;
}

rmw_ret_t rmw_get_service_names_and_types(
    const rmw_node_t * node,
    rcutils_allocator_t * allocator,
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
    if (!service_names_and_types) {
        RMW_SET_ERROR_MSG("service_names_and_types is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (node->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    // TODO: Implement service discovery
    service_names_and_types->names.size = 0;
    service_names_and_types->names.data = nullptr;
    service_names_and_types->types = nullptr;

    return RMW_RET_OK;
}

rmw_ret_t rmw_get_publishers_info_by_topic(
    const rmw_node_t * node,
    rcutils_allocator_t * allocator,
    const char * topic_name,
    bool no_mangle,
    rmw_topic_endpoint_info_array_t * publishers_info)
{
    if (!node) {
        RMW_SET_ERROR_MSG("node is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!allocator) {
        RMW_SET_ERROR_MSG("allocator is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!topic_name) {
        RMW_SET_ERROR_MSG("topic_name is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!publishers_info) {
        RMW_SET_ERROR_MSG("publishers_info is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (node->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    (void)no_mangle;

    // TODO: Implement publisher info query
    publishers_info->count = 0;

    return RMW_RET_OK;
}

rmw_ret_t rmw_get_subscriptions_info_by_topic(
    const rmw_node_t * node,
    rcutils_allocator_t * allocator,
    const char * topic_name,
    bool no_mangle,
    rmw_topic_endpoint_info_array_t * subscriptions_info)
{
    if (!node) {
        RMW_SET_ERROR_MSG("node is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!allocator) {
        RMW_SET_ERROR_MSG("allocator is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!topic_name) {
        RMW_SET_ERROR_MSG("topic_name is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!subscriptions_info) {
        RMW_SET_ERROR_MSG("subscriptions_info is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (node->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    (void)no_mangle;

    // TODO: Implement subscription info query
    subscriptions_info->count = 0;

    return RMW_RET_OK;
}

rmw_ret_t rmw_count_publishers(
    const rmw_node_t * node,
    const char * topic_name,
    size_t * count)
{
    if (!node) {
        RMW_SET_ERROR_MSG("node is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!topic_name) {
        RMW_SET_ERROR_MSG("topic_name is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!count) {
        RMW_SET_ERROR_MSG("count is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (node->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    // TODO: Implement publisher counting
    *count = 0;

    return RMW_RET_OK;
}

rmw_ret_t rmw_count_subscribers(
    const rmw_node_t * node,
    const char * topic_name,
    size_t * count)
{
    if (!node) {
        RMW_SET_ERROR_MSG("node is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!topic_name) {
        RMW_SET_ERROR_MSG("topic_name is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!count) {
        RMW_SET_ERROR_MSG("count is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (node->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    // TODO: Implement subscriber counting
    *count = 0;

    return RMW_RET_OK;
}

rmw_ret_t rmw_get_gid_for_publisher(
    const rmw_publisher_t * publisher,
    rmw_gid_t * gid)
{
    if (!publisher) {
        RMW_SET_ERROR_MSG("publisher is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!gid) {
        RMW_SET_ERROR_MSG("gid is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (publisher->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    auto pub_impl = static_cast<rmw_dsoftbus::PublisherImpl*>(publisher->data);
    if (!pub_impl) {
        RMW_SET_ERROR_MSG("publisher impl is null");
        return RMW_RET_ERROR;
    }

    gid->implementation_identifier = rmw_get_implementation_identifier();
    memcpy(gid->data, pub_impl->gid.data, RMW_GID_STORAGE_SIZE);

    return RMW_RET_OK;
}

rmw_ret_t rmw_get_gid_for_client(
    const rmw_client_t * client,
    rmw_gid_t * gid)
{
    if (!client) {
        RMW_SET_ERROR_MSG("client is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!gid) {
        RMW_SET_ERROR_MSG("gid is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (client->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    auto cli_impl = static_cast<rmw_dsoftbus::ClientImpl*>(client->data);
    if (!cli_impl) {
        RMW_SET_ERROR_MSG("client impl is null");
        return RMW_RET_ERROR;
    }

    gid->implementation_identifier = rmw_get_implementation_identifier();
    memcpy(gid->data, cli_impl->gid.data, RMW_GID_STORAGE_SIZE);

    return RMW_RET_OK;
}

rmw_ret_t rmw_compare_gids_equal(
    const rmw_gid_t * gid1,
    const rmw_gid_t * gid2,
    bool * result)
{
    if (!gid1) {
        RMW_SET_ERROR_MSG("gid1 is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!gid2) {
        RMW_SET_ERROR_MSG("gid2 is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!result) {
        RMW_SET_ERROR_MSG("result is null");
        return RMW_RET_INVALID_ARGUMENT;
    }

    *result = (memcmp(gid1->data, gid2->data, RMW_GID_STORAGE_SIZE) == 0);

    return RMW_RET_OK;
}

rmw_ret_t rmw_count_clients(
    const rmw_node_t * node,
    const char * service_name,
    size_t * count)
{
    if (!node) {
        RMW_SET_ERROR_MSG("node is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!service_name) {
        RMW_SET_ERROR_MSG("service_name is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!count) {
        RMW_SET_ERROR_MSG("count is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (node->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    // TODO: Implement client counting via dsoftbus discovery
    // For now, return 0 (no clients discovered)
    *count = 0;

    return RMW_RET_OK;
}

rmw_ret_t rmw_count_services(
    const rmw_node_t * node,
    const char * service_name,
    size_t * count)
{
    if (!node) {
        RMW_SET_ERROR_MSG("node is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!service_name) {
        RMW_SET_ERROR_MSG("service_name is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!count) {
        RMW_SET_ERROR_MSG("count is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (node->implementation_identifier != rmw_get_implementation_identifier()) {
        RMW_SET_ERROR_MSG("implementation identifier mismatch");
        return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
    }

    // TODO: Implement service counting via dsoftbus discovery
    // For now, return 0 (no services discovered)
    *count = 0;

    return RMW_RET_OK;
}

}  // extern "C"
