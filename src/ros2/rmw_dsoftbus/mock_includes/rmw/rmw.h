// Minimal mock for rmw/rmw.h (for cross-compilation only)
#ifndef RMW__RMW_H_
#define RMW__RMW_H_

#include "rmw/types.h"

#ifdef __cplusplus
extern "C" {
#endif

// RMW identifier
#define RMW_DSOFTBUS_IDENTIFIER "rmw_dsoftbus"

// Implementation identifier (defined in rmw_init.cpp)
const char * rmw_get_implementation_identifier(void);

// Error handling macros
#define RMW_SET_ERROR_MSG(msg) ((void)msg)
#define RMW_SET_ERROR_MSG_WITH_FORMAT_STRING(fmt, ...) ((void)fmt)
#define RMW_CHECK_ARGUMENT_FOR_NULL(arg, ret) \
  if (!arg) { RMW_SET_ERROR_MSG(#arg " is null"); return ret; }
#define RMW_CHECK_FOR_NULL_WITH_MSG(arg, msg, ret) \
  if (!arg) { RMW_SET_ERROR_MSG(msg); return ret; }
#define RMW_CHECK_TYPE_IDENTIFIERS_MATCH(id1, id2, ret) \
  if (id1 != id2) { return ret; }

// Default domain ID
#define RMW_DEFAULT_DOMAIN_ID 0

// Security options is defined in types.h

static inline rmw_security_options_t rmw_get_zero_initialized_security_options(void) {
    rmw_security_options_t options = {0, NULL};
    return options;
}

static inline rmw_context_t rmw_get_zero_initialized_context(void) {
    rmw_context_t context = {0, NULL, NULL, NULL};
    return context;
}

static inline rmw_init_options_t rmw_get_zero_initialized_init_options(void) {
    rmw_init_options_t options;
    options.instance_id = 0;
    options.implementation_identifier = NULL;
    options.domain_id = 0;
    options.security_options = rmw_get_zero_initialized_security_options();
    options.allocator = rcutils_get_default_allocator();
    options.impl = NULL;
    options.enclave = NULL;
    return options;
}

// QoS profiles are defined in rmw/qos_profiles.h
#include "rmw/qos_profiles.h"

// ============================================================================
// Topic Endpoint Info Functions (stubs for cross-compilation)
// ============================================================================

/**
 * Initialize a topic endpoint info array with a given size.
 */
static inline rmw_ret_t rmw_topic_endpoint_info_array_init_with_size(
    rmw_topic_endpoint_info_array_t * array,
    size_t size,
    rcutils_allocator_t * allocator)
{
    if (!array || !allocator) {
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (size == 0) {
        array->size = 0;
        array->info_array = NULL;
        return RMW_RET_OK;
    }
    array->info_array = (rmw_topic_endpoint_info_t *)allocator->allocate(
        size * sizeof(rmw_topic_endpoint_info_t), allocator->state);
    if (!array->info_array) {
        return RMW_RET_BAD_ALLOC;
    }
    array->size = size;
    // Zero-initialize all entries
    for (size_t i = 0; i < size; ++i) {
        array->info_array[i].node_name = NULL;
        array->info_array[i].node_namespace = NULL;
        array->info_array[i].topic_type = NULL;
        array->info_array[i].endpoint_type = RMW_ENDPOINT_INVALID;
        for (size_t j = 0; j < RMW_GID_STORAGE_SIZE; ++j) {
            array->info_array[i].endpoint_gid[j] = 0;
        }
    }
    return RMW_RET_OK;
}

/**
 * Finalize a topic endpoint info array.
 */
static inline rmw_ret_t rmw_topic_endpoint_info_array_fini(
    rmw_topic_endpoint_info_array_t * array,
    rcutils_allocator_t * allocator)
{
    if (!array || !allocator) {
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (array->info_array) {
        // Free string members
        for (size_t i = 0; i < array->size; ++i) {
            if (array->info_array[i].node_name) {
                allocator->deallocate((char*)array->info_array[i].node_name, allocator->state);
            }
            if (array->info_array[i].node_namespace) {
                allocator->deallocate((char*)array->info_array[i].node_namespace, allocator->state);
            }
            if (array->info_array[i].topic_type) {
                allocator->deallocate((char*)array->info_array[i].topic_type, allocator->state);
            }
        }
        allocator->deallocate(array->info_array, allocator->state);
    }
    array->info_array = NULL;
    array->size = 0;
    return RMW_RET_OK;
}

/**
 * Set the node name in a topic endpoint info.
 */
static inline rmw_ret_t rmw_topic_endpoint_info_set_node_name(
    rmw_topic_endpoint_info_t * info,
    const char * node_name,
    rcutils_allocator_t * allocator)
{
    if (!info || !node_name || !allocator) {
        return RMW_RET_INVALID_ARGUMENT;
    }
    size_t len = 0;
    while (node_name[len] != '\0') ++len;
    char * copy = (char *)allocator->allocate(len + 1, allocator->state);
    if (!copy) {
        return RMW_RET_BAD_ALLOC;
    }
    for (size_t i = 0; i <= len; ++i) {
        copy[i] = node_name[i];
    }
    info->node_name = copy;
    return RMW_RET_OK;
}

/**
 * Set the node namespace in a topic endpoint info.
 */
static inline rmw_ret_t rmw_topic_endpoint_info_set_node_namespace(
    rmw_topic_endpoint_info_t * info,
    const char * node_namespace,
    rcutils_allocator_t * allocator)
{
    if (!info || !node_namespace || !allocator) {
        return RMW_RET_INVALID_ARGUMENT;
    }
    size_t len = 0;
    while (node_namespace[len] != '\0') ++len;
    char * copy = (char *)allocator->allocate(len + 1, allocator->state);
    if (!copy) {
        return RMW_RET_BAD_ALLOC;
    }
    for (size_t i = 0; i <= len; ++i) {
        copy[i] = node_namespace[i];
    }
    info->node_namespace = copy;
    return RMW_RET_OK;
}

/**
 * Set the topic type in a topic endpoint info.
 */
static inline rmw_ret_t rmw_topic_endpoint_info_set_topic_type(
    rmw_topic_endpoint_info_t * info,
    const char * topic_type,
    rcutils_allocator_t * allocator)
{
    if (!info || !topic_type || !allocator) {
        return RMW_RET_INVALID_ARGUMENT;
    }
    size_t len = 0;
    while (topic_type[len] != '\0') ++len;
    char * copy = (char *)allocator->allocate(len + 1, allocator->state);
    if (!copy) {
        return RMW_RET_BAD_ALLOC;
    }
    for (size_t i = 0; i <= len; ++i) {
        copy[i] = topic_type[i];
    }
    info->topic_type = copy;
    return RMW_RET_OK;
}

/**
 * Set the endpoint type in a topic endpoint info.
 */
static inline rmw_ret_t rmw_topic_endpoint_info_set_endpoint_type(
    rmw_topic_endpoint_info_t * info,
    rmw_endpoint_type_t endpoint_type)
{
    if (!info) {
        return RMW_RET_INVALID_ARGUMENT;
    }
    info->endpoint_type = endpoint_type;
    return RMW_RET_OK;
}

/**
 * Set the GID in a topic endpoint info.
 */
static inline rmw_ret_t rmw_topic_endpoint_info_set_gid(
    rmw_topic_endpoint_info_t * info,
    const uint8_t * gid,
    size_t size)
{
    if (!info || !gid) {
        return RMW_RET_INVALID_ARGUMENT;
    }
    size_t copy_size = size < RMW_GID_STORAGE_SIZE ? size : RMW_GID_STORAGE_SIZE;
    for (size_t i = 0; i < copy_size; ++i) {
        info->endpoint_gid[i] = gid[i];
    }
    for (size_t i = copy_size; i < RMW_GID_STORAGE_SIZE; ++i) {
        info->endpoint_gid[i] = 0;
    }
    return RMW_RET_OK;
}

/**
 * Set the QoS profile in a topic endpoint info.
 */
static inline rmw_ret_t rmw_topic_endpoint_info_set_qos_profile(
    rmw_topic_endpoint_info_t * info,
    const rmw_qos_profile_t * qos_profile)
{
    if (!info || !qos_profile) {
        return RMW_RET_INVALID_ARGUMENT;
    }
    info->qos_profile = *qos_profile;
    return RMW_RET_OK;
}

// ============================================================================
// Topic Endpoint Info Initialization
// ============================================================================

/**
 * Get a zero-initialized topic endpoint info.
 */
static inline rmw_topic_endpoint_info_t rmw_get_zero_initialized_topic_endpoint_info(void) {
    rmw_topic_endpoint_info_t info;
    info.node_name = NULL;
    info.node_namespace = NULL;
    info.topic_type = NULL;
    info.endpoint_type = RMW_ENDPOINT_INVALID;
    for (size_t i = 0; i < RMW_GID_STORAGE_SIZE; ++i) {
        info.endpoint_gid[i] = 0;
    }
    // Zero-initialize qos_profile
    info.qos_profile.history = RMW_QOS_POLICY_HISTORY_SYSTEM_DEFAULT;
    info.qos_profile.depth = 0;
    info.qos_profile.reliability = RMW_QOS_POLICY_RELIABILITY_SYSTEM_DEFAULT;
    info.qos_profile.durability = RMW_QOS_POLICY_DURABILITY_SYSTEM_DEFAULT;
    info.qos_profile.deadline.sec = 0;
    info.qos_profile.deadline.nsec = 0;
    info.qos_profile.lifespan.sec = 0;
    info.qos_profile.lifespan.nsec = 0;
    info.qos_profile.liveliness = RMW_QOS_POLICY_LIVELINESS_SYSTEM_DEFAULT;
    info.qos_profile.liveliness_lease_duration.sec = 0;
    info.qos_profile.liveliness_lease_duration.nsec = 0;
    info.qos_profile.avoid_ros_namespace_conventions = false;
    return info;
}

// ============================================================================
// Names and Types Functions (stubs for cross-compilation)
// ============================================================================

/**
 * Initialize a names and types structure.
 * Note: types is an array of rcutils_string_array_t (one per name).
 */
static inline rmw_ret_t rmw_names_and_types_init(
    rmw_names_and_types_t * names_and_types,
    size_t size,
    rcutils_allocator_t * allocator)
{
    if (!names_and_types || !allocator) {
        return RMW_RET_INVALID_ARGUMENT;
    }
    // Initialize names string array
    rcutils_ret_t rcret = rcutils_string_array_init(&names_and_types->names, size, allocator);
    if (rcret != RCUTILS_RET_OK) {
        return RMW_RET_BAD_ALLOC;
    }

    names_and_types->types = NULL;
    if (size > 0) {
        // Allocate array of string arrays for types
        names_and_types->types = (rcutils_string_array_t *)allocator->allocate(
            size * sizeof(rcutils_string_array_t), allocator->state);
        if (!names_and_types->types) {
            rcutils_string_array_fini(&names_and_types->names);
            return RMW_RET_BAD_ALLOC;
        }
        // Initialize each types entry to zero
        for (size_t i = 0; i < size; ++i) {
            names_and_types->types[i].size = 0;
            names_and_types->types[i].data = NULL;
        }
    }
    return RMW_RET_OK;
}

/**
 * Finalize a names and types structure.
 */
static inline rmw_ret_t rmw_names_and_types_fini(
    rmw_names_and_types_t * names_and_types)
{
    if (!names_and_types) {
        return RMW_RET_INVALID_ARGUMENT;
    }
    // Get allocator from names
    rcutils_allocator_t allocator = names_and_types->names.allocator;

    // Finalize each types entry
    if (names_and_types->types) {
        for (size_t i = 0; i < names_and_types->names.size; ++i) {
            rcutils_string_array_fini(&names_and_types->types[i]);
        }
        allocator.deallocate(names_and_types->types, allocator.state);
    }

    // Finalize names
    rcutils_string_array_fini(&names_and_types->names);

    names_and_types->types = NULL;
    return RMW_RET_OK;
}

/**
 * Get a zero-initialized names and types structure.
 */
static inline rmw_names_and_types_t rmw_get_zero_initialized_names_and_types(void) {
    rmw_names_and_types_t names_and_types;
    names_and_types.names.size = 0;
    names_and_types.names.data = NULL;
    names_and_types.types = NULL;
    return names_and_types;
}

#ifdef __cplusplus
}
#endif

#endif  // RMW__RMW_H_
