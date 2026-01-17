// Copyright (c) 2024 ROS2 KaihongOS Port Project
// Licensed under the Apache License, Version 2.0

// CDR Serializer implementation for rmw_dsoftbus

#include "rmw_dsoftbus/cdr_serializer.h"
#include "rmw_dsoftbus/types.h"
#include "rmw/rmw.h"

#include <cstring>

namespace rmw_dsoftbus {
namespace cdr {

// TypeSupport identifier for our CDR implementation
const char* const CDR_TYPESUPPORT_IDENTIFIER = "rosidl_typesupport_cdr_dsoftbus";

/**
 * Serialize a ROS message to CDR format.
 *
 * This function handles three cases:
 * 1. If type_support has CDR callbacks (FastRTPS style), use them directly
 * 2. If type_support has introspection, use introspection-based serialization
 * 3. If message_size is known, use POD serialization (memcpy)
 *
 * @param ros_message The ROS message to serialize
 * @param type_support The message type support
 * @param serialized_message Output buffer for serialized data
 * @return true on success, false on failure
 */
bool serialize_message(
    const void* ros_message,
    const rosidl_message_type_support_t* type_support,
    rmw_serialized_message_t* serialized_message)
{
    if (!ros_message || !type_support || !serialized_message) {
        return false;
    }

    // Get callbacks from type support
    const auto* callbacks = static_cast<const rosidl_message_type_support_callbacks_t*>(
        type_support->data);

    if (!callbacks) {
        return false;
    }

    // Try to determine serialization method and size
    size_t estimated_size = CDR_ENCAPSULATION_SIZE;

    // Check if we have a CDR serialize callback or custom serialize callback
    if (callbacks->serialize) {
        // Use custom serialize callback
        // This callback may write to serialized_message directly
        return callbacks->serialize(ros_message, serialized_message);
    }

    // If no serialize callback, check for message_size (POD type)
    if (callbacks->message_size > 0) {
        // POD serialization with CDR encapsulation
        estimated_size += callbacks->message_size;

        // Ensure buffer capacity
        if (serialized_message->buffer_capacity < estimated_size) {
            rmw_ret_t ret = rmw_serialized_message_resize(serialized_message, estimated_size);
            if (ret != RMW_RET_OK) {
                return false;
            }
        }

        // Create CDR serializer
        CdrSerializer ser(estimated_size);
        ser.write_encapsulation();
        ser.serialize_pod(ros_message, callbacks->message_size, CDR_ALIGN_1);

        // Copy to output
        auto data = ser.finalize();
        memcpy(serialized_message->buffer, data.data(), data.size());
        serialized_message->buffer_length = data.size();

        return true;
    }

    // No serialization method available
    return false;
}

/**
 * Deserialize a CDR message to a ROS message.
 *
 * @param serialized_message The serialized CDR data
 * @param type_support The message type support
 * @param ros_message Output ROS message (must be pre-allocated)
 * @return true on success, false on failure
 */
bool deserialize_message(
    const rmw_serialized_message_t* serialized_message,
    const rosidl_message_type_support_t* type_support,
    void* ros_message)
{
    if (!serialized_message || !type_support || !ros_message) {
        return false;
    }

    if (serialized_message->buffer_length < CDR_ENCAPSULATION_SIZE) {
        return false;
    }

    // Get callbacks from type support
    const auto* callbacks = static_cast<const rosidl_message_type_support_callbacks_t*>(
        type_support->data);

    if (!callbacks) {
        return false;
    }

    // Try custom deserialize callback first
    if (callbacks->deserialize) {
        return callbacks->deserialize(serialized_message, ros_message);
    }

    // If no deserialize callback, check for message_size (POD type)
    if (callbacks->message_size > 0) {
        // POD deserialization with CDR encapsulation
        CdrDeserializer deser(serialized_message->buffer, serialized_message->buffer_length);

        if (!deser.read_encapsulation()) {
            return false;
        }

        if (!deser.deserialize_pod(ros_message, callbacks->message_size, CDR_ALIGN_1)) {
            return false;
        }

        return true;
    }

    // No deserialization method available
    return false;
}

/**
 * Get the serialized size of a ROS message in CDR format.
 *
 * @param ros_message The ROS message
 * @param type_support The message type support
 * @return The serialized size, or 0 if unknown
 */
size_t get_serialized_size(
    const void* ros_message,
    const rosidl_message_type_support_t* type_support)
{
    if (!type_support) {
        return 0;
    }

    const auto* callbacks = static_cast<const rosidl_message_type_support_callbacks_t*>(
        type_support->data);

    if (!callbacks) {
        return 0;
    }

    // Check for get_serialized_size callback
    if (callbacks->get_serialized_size) {
        return CDR_ENCAPSULATION_SIZE + callbacks->get_serialized_size(ros_message);
    }

    // Check for fixed message size (POD)
    if (callbacks->message_size > 0) {
        return CDR_ENCAPSULATION_SIZE + callbacks->message_size;
    }

    return 0;
}

/**
 * Serialize a message to CDR format with header info.
 *
 * This is used by rmw_publish to create the complete message payload
 * including dsoftbus message header.
 *
 * @param ros_message The ROS message to serialize
 * @param type_support The message type support
 * @param output Output vector for serialized data
 * @return true on success, false on failure
 */
bool serialize_message_to_buffer(
    const void* ros_message,
    const rosidl_message_type_support_t* type_support,
    std::vector<uint8_t>& output)
{
    if (!ros_message || !type_support) {
        return false;
    }

    const auto* callbacks = static_cast<const rosidl_message_type_support_callbacks_t*>(
        type_support->data);

    if (!callbacks) {
        return false;
    }

    // Determine serialized size
    size_t serialized_size = get_serialized_size(ros_message, type_support);
    if (serialized_size == 0) {
        return false;
    }

    // Create CDR serializer
    CdrSerializer ser(serialized_size);
    ser.write_encapsulation();

    // Serialize based on available method
    if (callbacks->message_size > 0) {
        // POD serialization
        ser.serialize_pod(ros_message, callbacks->message_size, CDR_ALIGN_1);
    } else {
        // No method available
        return false;
    }

    output = ser.finalize();
    return true;
}

/**
 * Deserialize a CDR buffer to a ROS message.
 *
 * This is used by rmw_take to decode received message payload.
 *
 * @param data The CDR data buffer
 * @param size The buffer size
 * @param type_support The message type support
 * @param ros_message Output ROS message (must be pre-allocated)
 * @return true on success, false on failure
 */
bool deserialize_buffer_to_message(
    const uint8_t* data,
    size_t size,
    const rosidl_message_type_support_t* type_support,
    void* ros_message)
{
    if (!data || size == 0 || !type_support || !ros_message) {
        return false;
    }

    const auto* callbacks = static_cast<const rosidl_message_type_support_callbacks_t*>(
        type_support->data);

    if (!callbacks) {
        return false;
    }

    // Create deserializer
    CdrDeserializer deser(data, size);

    // Read encapsulation header
    if (!deser.read_encapsulation()) {
        return false;
    }

    // Deserialize based on available method
    if (callbacks->message_size > 0) {
        // POD deserialization
        if (!deser.deserialize_pod(ros_message, callbacks->message_size, CDR_ALIGN_1)) {
            return false;
        }
        return true;
    }

    return false;
}

}  // namespace cdr
}  // namespace rmw_dsoftbus
