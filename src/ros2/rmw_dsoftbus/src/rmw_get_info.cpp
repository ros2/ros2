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

// Phase 2.2: Graph Discovery - Query APIs using GraphCache

#include "rmw_dsoftbus/rmw_dsoftbus.h"
#include "rmw_dsoftbus/types.h"
#include "rmw_dsoftbus/graph_cache.h"

#include <cstdio>
#include <cstring>

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

    // Phase 2.2: Query GraphCache for all registered nodes
    auto nodes = rmw_dsoftbus::GraphCache::instance().get_all_nodes();

    if (nodes.empty()) {
        node_names->size = 0;
        node_names->data = nullptr;
        node_namespaces->size = 0;
        node_namespaces->data = nullptr;
        return RMW_RET_OK;
    }

    // Allocate arrays
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rcutils_ret_t ret = rcutils_string_array_init(node_names, nodes.size(), &allocator);
    if (ret != RCUTILS_RET_OK) {
        RMW_SET_ERROR_MSG("failed to allocate node_names array");
        return RMW_RET_BAD_ALLOC;
    }

    ret = rcutils_string_array_init(node_namespaces, nodes.size(), &allocator);
    if (ret != RCUTILS_RET_OK) {
        rcutils_string_array_fini(node_names);
        RMW_SET_ERROR_MSG("failed to allocate node_namespaces array");
        return RMW_RET_BAD_ALLOC;
    }

    // Copy node info
    for (size_t i = 0; i < nodes.size(); ++i) {
        node_names->data[i] = rcutils_strdup(nodes[i].node_name.c_str(), allocator);
        node_namespaces->data[i] = rcutils_strdup(nodes[i].node_namespace.c_str(), allocator);

        if (!node_names->data[i] || !node_namespaces->data[i]) {
            rcutils_string_array_fini(node_names);
            rcutils_string_array_fini(node_namespaces);
            RMW_SET_ERROR_MSG("failed to allocate string");
            return RMW_RET_BAD_ALLOC;
        }
    }

    fprintf(stderr, "[DEBUG][rmw_get_node_names] Returning %zu nodes from GraphCache\n", nodes.size());
    fflush(stderr);

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

    // Get nodes first
    auto nodes = rmw_dsoftbus::GraphCache::instance().get_all_nodes();

    rmw_ret_t ret = rmw_get_node_names(node, node_names, node_namespaces);
    if (ret != RMW_RET_OK) {
        return ret;
    }

    // Allocate enclaves array
    if (nodes.empty()) {
        enclaves->size = 0;
        enclaves->data = nullptr;
        return RMW_RET_OK;
    }

    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rcutils_ret_t rcret = rcutils_string_array_init(enclaves, nodes.size(), &allocator);
    if (rcret != RCUTILS_RET_OK) {
        rcutils_string_array_fini(node_names);
        rcutils_string_array_fini(node_namespaces);
        RMW_SET_ERROR_MSG("failed to allocate enclaves array");
        return RMW_RET_BAD_ALLOC;
    }

    // Copy enclave info
    for (size_t i = 0; i < nodes.size(); ++i) {
        enclaves->data[i] = rcutils_strdup(nodes[i].enclave.c_str(), allocator);
        if (!enclaves->data[i]) {
            rcutils_string_array_fini(node_names);
            rcutils_string_array_fini(node_namespaces);
            rcutils_string_array_fini(enclaves);
            RMW_SET_ERROR_MSG("failed to allocate enclave string");
            return RMW_RET_BAD_ALLOC;
        }
    }

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

    // Phase 2.2: Query GraphCache for all topics
    auto topics = rmw_dsoftbus::GraphCache::instance().get_topic_names_and_types();

    if (topics.empty()) {
        topic_names_and_types->names.size = 0;
        topic_names_and_types->names.data = nullptr;
        topic_names_and_types->types = nullptr;
        return RMW_RET_OK;
    }

    // Initialize names_and_types structure
    rmw_ret_t ret = rmw_names_and_types_init(topic_names_and_types, topics.size(), allocator);
    if (ret != RMW_RET_OK) {
        RMW_SET_ERROR_MSG("failed to initialize names_and_types");
        return ret;
    }

    // Fill in topics and types
    size_t i = 0;
    for (const auto& [topic_name, type_set] : topics) {
        // Allocate topic name
        topic_names_and_types->names.data[i] = rcutils_strdup(topic_name.c_str(), *allocator);
        if (!topic_names_and_types->names.data[i]) {
            rmw_names_and_types_fini(topic_names_and_types);
            RMW_SET_ERROR_MSG("failed to allocate topic name");
            return RMW_RET_BAD_ALLOC;
        }

        // Allocate types array for this topic
        rcutils_ret_t rcret = rcutils_string_array_init(
            &topic_names_and_types->types[i], type_set.size(), allocator);
        if (rcret != RCUTILS_RET_OK) {
            rmw_names_and_types_fini(topic_names_and_types);
            RMW_SET_ERROR_MSG("failed to allocate types array");
            return RMW_RET_BAD_ALLOC;
        }

        // Copy type names
        size_t j = 0;
        for (const auto& type_name : type_set) {
            topic_names_and_types->types[i].data[j] = rcutils_strdup(type_name.c_str(), *allocator);
            if (!topic_names_and_types->types[i].data[j]) {
                rmw_names_and_types_fini(topic_names_and_types);
                RMW_SET_ERROR_MSG("failed to allocate type name");
                return RMW_RET_BAD_ALLOC;
            }
            j++;
        }

        i++;
    }

    fprintf(stderr, "[DEBUG][rmw_get_topic_names_and_types] Returning %zu topics from GraphCache\n",
            topics.size());
    fflush(stderr);

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

    // Phase 2.2: Query GraphCache for all services
    auto services = rmw_dsoftbus::GraphCache::instance().get_service_names_and_types();

    if (services.empty()) {
        service_names_and_types->names.size = 0;
        service_names_and_types->names.data = nullptr;
        service_names_and_types->types = nullptr;
        return RMW_RET_OK;
    }

    // Initialize names_and_types structure
    rmw_ret_t ret = rmw_names_and_types_init(service_names_and_types, services.size(), allocator);
    if (ret != RMW_RET_OK) {
        RMW_SET_ERROR_MSG("failed to initialize names_and_types");
        return ret;
    }

    // Fill in services and types
    size_t i = 0;
    for (const auto& [service_name, type_set] : services) {
        // Allocate service name
        service_names_and_types->names.data[i] = rcutils_strdup(service_name.c_str(), *allocator);
        if (!service_names_and_types->names.data[i]) {
            rmw_names_and_types_fini(service_names_and_types);
            RMW_SET_ERROR_MSG("failed to allocate service name");
            return RMW_RET_BAD_ALLOC;
        }

        // Allocate types array for this service
        rcutils_ret_t rcret = rcutils_string_array_init(
            &service_names_and_types->types[i], type_set.size(), allocator);
        if (rcret != RCUTILS_RET_OK) {
            rmw_names_and_types_fini(service_names_and_types);
            RMW_SET_ERROR_MSG("failed to allocate types array");
            return RMW_RET_BAD_ALLOC;
        }

        // Copy type names
        size_t j = 0;
        for (const auto& type_name : type_set) {
            service_names_and_types->types[i].data[j] = rcutils_strdup(type_name.c_str(), *allocator);
            if (!service_names_and_types->types[i].data[j]) {
                rmw_names_and_types_fini(service_names_and_types);
                RMW_SET_ERROR_MSG("failed to allocate type name");
                return RMW_RET_BAD_ALLOC;
            }
            j++;
        }

        i++;
    }

    fprintf(stderr, "[DEBUG][rmw_get_service_names_and_types] Returning %zu services from GraphCache\n",
            services.size());
    fflush(stderr);

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

    // Phase 2.2: Query GraphCache for publishers on this topic
    auto publishers = rmw_dsoftbus::GraphCache::instance().get_publishers_for_topic(topic_name);

    if (publishers.empty()) {
        publishers_info->size = 0;
        publishers_info->info_array = nullptr;
        return RMW_RET_OK;
    }

    // Allocate info array
    rmw_ret_t ret = rmw_topic_endpoint_info_array_init_with_size(
        publishers_info, publishers.size(), allocator);
    if (ret != RMW_RET_OK) {
        RMW_SET_ERROR_MSG("failed to allocate publishers_info array");
        return ret;
    }

    // Fill in publisher info
    for (size_t i = 0; i < publishers.size(); ++i) {
        const auto& pub = publishers[i];
        rmw_topic_endpoint_info_t* info = &publishers_info->info_array[i];

        // Initialize the info structure
        *info = rmw_get_zero_initialized_topic_endpoint_info();

        // Set node name and namespace
        ret = rmw_topic_endpoint_info_set_node_name(info, pub.node_name.c_str(), allocator);
        if (ret != RMW_RET_OK) {
            rmw_topic_endpoint_info_array_fini(publishers_info, allocator);
            return ret;
        }

        ret = rmw_topic_endpoint_info_set_node_namespace(info, pub.node_namespace.c_str(), allocator);
        if (ret != RMW_RET_OK) {
            rmw_topic_endpoint_info_array_fini(publishers_info, allocator);
            return ret;
        }

        // Set topic type
        ret = rmw_topic_endpoint_info_set_topic_type(info, pub.type_name.c_str(), allocator);
        if (ret != RMW_RET_OK) {
            rmw_topic_endpoint_info_array_fini(publishers_info, allocator);
            return ret;
        }

        // Set endpoint type
        ret = rmw_topic_endpoint_info_set_endpoint_type(info, RMW_ENDPOINT_PUBLISHER);
        if (ret != RMW_RET_OK) {
            rmw_topic_endpoint_info_array_fini(publishers_info, allocator);
            return ret;
        }

        // Set GID
        ret = rmw_topic_endpoint_info_set_gid(info, pub.gid.data, RMW_GID_STORAGE_SIZE);
        if (ret != RMW_RET_OK) {
            rmw_topic_endpoint_info_array_fini(publishers_info, allocator);
            return ret;
        }

        // Set QoS profile
        ret = rmw_topic_endpoint_info_set_qos_profile(info, &pub.qos);
        if (ret != RMW_RET_OK) {
            rmw_topic_endpoint_info_array_fini(publishers_info, allocator);
            return ret;
        }
    }

    fprintf(stderr, "[DEBUG][rmw_get_publishers_info_by_topic] Returning %zu publishers for %s\n",
            publishers.size(), topic_name);
    fflush(stderr);

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

    // Phase 2.2: Query GraphCache for subscribers on this topic
    auto subscribers = rmw_dsoftbus::GraphCache::instance().get_subscribers_for_topic(topic_name);

    if (subscribers.empty()) {
        subscriptions_info->size = 0;
        subscriptions_info->info_array = nullptr;
        return RMW_RET_OK;
    }

    // Allocate info array
    rmw_ret_t ret = rmw_topic_endpoint_info_array_init_with_size(
        subscriptions_info, subscribers.size(), allocator);
    if (ret != RMW_RET_OK) {
        RMW_SET_ERROR_MSG("failed to allocate subscriptions_info array");
        return ret;
    }

    // Fill in subscriber info
    for (size_t i = 0; i < subscribers.size(); ++i) {
        const auto& sub = subscribers[i];
        rmw_topic_endpoint_info_t* info = &subscriptions_info->info_array[i];

        // Initialize the info structure
        *info = rmw_get_zero_initialized_topic_endpoint_info();

        // Set node name and namespace
        ret = rmw_topic_endpoint_info_set_node_name(info, sub.node_name.c_str(), allocator);
        if (ret != RMW_RET_OK) {
            rmw_topic_endpoint_info_array_fini(subscriptions_info, allocator);
            return ret;
        }

        ret = rmw_topic_endpoint_info_set_node_namespace(info, sub.node_namespace.c_str(), allocator);
        if (ret != RMW_RET_OK) {
            rmw_topic_endpoint_info_array_fini(subscriptions_info, allocator);
            return ret;
        }

        // Set topic type
        ret = rmw_topic_endpoint_info_set_topic_type(info, sub.type_name.c_str(), allocator);
        if (ret != RMW_RET_OK) {
            rmw_topic_endpoint_info_array_fini(subscriptions_info, allocator);
            return ret;
        }

        // Set endpoint type
        ret = rmw_topic_endpoint_info_set_endpoint_type(info, RMW_ENDPOINT_SUBSCRIPTION);
        if (ret != RMW_RET_OK) {
            rmw_topic_endpoint_info_array_fini(subscriptions_info, allocator);
            return ret;
        }

        // Set GID
        ret = rmw_topic_endpoint_info_set_gid(info, sub.gid.data, RMW_GID_STORAGE_SIZE);
        if (ret != RMW_RET_OK) {
            rmw_topic_endpoint_info_array_fini(subscriptions_info, allocator);
            return ret;
        }

        // Set QoS profile
        ret = rmw_topic_endpoint_info_set_qos_profile(info, &sub.qos);
        if (ret != RMW_RET_OK) {
            rmw_topic_endpoint_info_array_fini(subscriptions_info, allocator);
            return ret;
        }
    }

    fprintf(stderr, "[DEBUG][rmw_get_subscriptions_info_by_topic] Returning %zu subscribers for %s\n",
            subscribers.size(), topic_name);
    fflush(stderr);

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

    // Phase 2.2: Query GraphCache for publisher count
    *count = rmw_dsoftbus::GraphCache::instance().count_publishers(topic_name);

    fprintf(stderr, "[DEBUG][rmw_count_publishers] %zu publishers for %s\n", *count, topic_name);
    fflush(stderr);

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

    // Phase 2.2: Query GraphCache for subscriber count
    *count = rmw_dsoftbus::GraphCache::instance().count_subscribers(topic_name);

    fprintf(stderr, "[DEBUG][rmw_count_subscribers] %zu subscribers for %s\n", *count, topic_name);
    fflush(stderr);

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

    // Phase 2.2: Query GraphCache for client count
    *count = rmw_dsoftbus::GraphCache::instance().count_clients(service_name);

    fprintf(stderr, "[DEBUG][rmw_count_clients] %zu clients for %s\n", *count, service_name);
    fflush(stderr);

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

    // Phase 2.2: Query GraphCache for service count
    *count = rmw_dsoftbus::GraphCache::instance().count_services(service_name);

    fprintf(stderr, "[DEBUG][rmw_count_services] %zu services for %s\n", *count, service_name);
    fflush(stderr);

    return RMW_RET_OK;
}

}  // extern "C"
