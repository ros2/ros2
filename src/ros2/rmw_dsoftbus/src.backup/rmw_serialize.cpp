// Copyright (c) 2024 ROS2 KaihongOS Port Project
// Licensed under the Apache License, Version 2.0

#include "rmw_dsoftbus/rmw_dsoftbus.h"
#include "rmw_dsoftbus/types.h"
#include "rmw_dsoftbus/cdr_serializer.h"

#include <cstring>

extern "C"
{

rmw_ret_t rmw_serialize(
    const void * ros_message,
    const rosidl_message_type_support_t * type_support,
    rmw_serialized_message_t * serialized_message)
{
    if (!ros_message) {
        RMW_SET_ERROR_MSG("ros_message is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!type_support) {
        RMW_SET_ERROR_MSG("type_support is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!serialized_message) {
        RMW_SET_ERROR_MSG("serialized_message is null");
        return RMW_RET_INVALID_ARGUMENT;
    }

    // Use CDR serialization
    if (rmw_dsoftbus::cdr::serialize_message(ros_message, type_support, serialized_message)) {
        return RMW_RET_OK;
    }

    RMW_SET_ERROR_MSG("failed to serialize message to CDR format");
    return RMW_RET_ERROR;
}

rmw_ret_t rmw_deserialize(
    const rmw_serialized_message_t * serialized_message,
    const rosidl_message_type_support_t * type_support,
    void * ros_message)
{
    if (!serialized_message) {
        RMW_SET_ERROR_MSG("serialized_message is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!type_support) {
        RMW_SET_ERROR_MSG("type_support is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!ros_message) {
        RMW_SET_ERROR_MSG("ros_message is null");
        return RMW_RET_INVALID_ARGUMENT;
    }

    // Use CDR deserialization
    if (rmw_dsoftbus::cdr::deserialize_message(serialized_message, type_support, ros_message)) {
        return RMW_RET_OK;
    }

    RMW_SET_ERROR_MSG("failed to deserialize message from CDR format");
    return RMW_RET_ERROR;
}

rmw_ret_t rmw_get_serialized_message_size(
    const rosidl_message_type_support_t * type_support,
    const rosidl_runtime_c__Sequence__bound * message_bounds,
    size_t * size)
{
    if (!type_support) {
        RMW_SET_ERROR_MSG("type_support is null");
        return RMW_RET_INVALID_ARGUMENT;
    }
    if (!size) {
        RMW_SET_ERROR_MSG("size is null");
        return RMW_RET_INVALID_ARGUMENT;
    }

    (void)message_bounds;  // Not used for fixed-size messages

    // Get callbacks from type support
    const auto* callbacks = static_cast<const rosidl_message_type_support_callbacks_t*>(
        type_support->data);

    if (!callbacks) {
        *size = 0;
        return RMW_RET_ERROR;
    }

    // For bounded/fixed-size types, return the message_size + CDR encapsulation
    if (callbacks->message_size > 0) {
        *size = rmw_dsoftbus::cdr::CDR_ENCAPSULATION_SIZE + callbacks->message_size;
        return RMW_RET_OK;
    }

    // For unbounded types, we cannot determine the size without the actual message
    *size = 0;
    return RMW_RET_UNSUPPORTED;
}

}  // extern "C"
