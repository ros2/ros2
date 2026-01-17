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

// Copyright 2026 The rmw_dsoftbus Authors
#include <string.h>  /* C memcpy/memset for OHOS SDK compatibility */
#include <stdlib.h>

// Licensed under the Apache License, Version 2.0
//
// Service TypeSupport Serializer - Phase 3 Service/Client RPC

#include "rmw_dsoftbus/service_typesupport_serializer.h"
#include "rmw_dsoftbus/service_envelope.h"
#include "rmw_dsoftbus/typesupport_helpers.h"
#include "rmw_dsoftbus/types.h"
#include "rmw/rmw.h"  // For RMW_SET_ERROR_MSG

#include <rosidl_typesupport_introspection_c/service_introspection.h>
#include <rosidl_typesupport_introspection_c/identifier.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

// External C API from rmw_typesupport_serializer.cpp
extern "C" {
bool rmw_dsoftbus_serialize_ros_message(
    const void* ros_message,
    const rosidl_message_type_support_t* type_support,
    uint8_t** cdr_buffer,
    size_t* cdr_size);

bool rmw_dsoftbus_deserialize_ros_message(
    const uint8_t* cdr_buffer,
    size_t cdr_size,
    const rosidl_message_type_support_t* type_support,
    void* ros_message);
}

namespace {

// Get introspection service members from service type support
const rosidl_typesupport_introspection_c__ServiceMembers* get_service_members(
    const rosidl_service_type_support_t* service_type_support)
{
    if (!service_type_support) {
        return nullptr;
    }

    // Check if this is an introspection typesupport
    if (!rmw_dsoftbus::is_introspection_typesupport(service_type_support->typesupport_identifier)) {
        fprintf(stderr, "[ServiceSerializer] Unsupported typesupport: %s (only introspection supported)\n",
                service_type_support->typesupport_identifier ? service_type_support->typesupport_identifier : "NULL");
        return nullptr;
    }

    // Cast to service members (safe because we verified it's introspection)
    return static_cast<const rosidl_typesupport_introspection_c__ServiceMembers*>(
        service_type_support->data);
}

// Serialize helper: envelope + CDR
rmw_ret_t serialize_with_envelope(
    const void* ros_message,
    const rosidl_message_type_support_t* msg_type_support,
    uint64_t request_id,
    rmw_dsoftbus::ServiceMessageType msg_type,
    uint8_t** buffer_out,
    size_t* size_out)
{
    if (!ros_message || !msg_type_support || !buffer_out || !size_out) {
        RMW_SET_ERROR_MSG("Invalid arguments to serialize_with_envelope");
        return RMW_RET_INVALID_ARGUMENT;
    }

    // Serialize the ROS message to CDR
    uint8_t* cdr_buffer = nullptr;
    size_t cdr_size = 0;

    if (!rmw_dsoftbus_serialize_ros_message(ros_message, msg_type_support, &cdr_buffer, &cdr_size)) {
        RMW_SET_ERROR_MSG("Failed to serialize ROS message to CDR");
        return RMW_RET_ERROR;
    }

    // Calculate total size
    const size_t total_size = rmw_dsoftbus::SERVICE_ENVELOPE_SIZE + cdr_size;

    // Check size limit
    if (total_size > static_cast<size_t>(RMW_DSOFTBUS_MAX_MESSAGE_SIZE)) {
        free(cdr_buffer);
        RMW_SET_ERROR_MSG("Serialized message exceeds 4MB limit");
        return RMW_RET_ERROR;
    }

    // Allocate output buffer
    uint8_t* output = static_cast<uint8_t*>(malloc(total_size));
    if (!output) {
        free(cdr_buffer);
        RMW_SET_ERROR_MSG("Failed to allocate output buffer");
        return RMW_RET_BAD_ALLOC;
    }

    // Write ServiceEnvelope
    rmw_dsoftbus::ServiceEnvelope envelope(request_id, msg_type);
    rmw_dsoftbus::serialize_envelope(envelope, output);

    // Copy CDR payload
    std::memcpy(output + rmw_dsoftbus::SERVICE_ENVELOPE_SIZE, cdr_buffer, cdr_size);

    // Clean up CDR buffer
    free(cdr_buffer);

    *buffer_out = output;
    *size_out = total_size;

    return RMW_RET_OK;
}

// Deserialize helper: envelope + CDR
rmw_ret_t deserialize_with_envelope(
    const uint8_t* buffer,
    size_t size,
    const rosidl_message_type_support_t* msg_type_support,
    rmw_dsoftbus::ServiceMessageType expected_type,
    uint64_t* request_id_out,
    void* ros_message_out)
{
    if (!buffer || !msg_type_support || !request_id_out || !ros_message_out) {
        RMW_SET_ERROR_MSG("Invalid arguments to deserialize_with_envelope");
        return RMW_RET_INVALID_ARGUMENT;
    }

    // Check minimum size
    if (size < rmw_dsoftbus::SERVICE_ENVELOPE_SIZE) {
        RMW_SET_ERROR_MSG("Buffer too small for ServiceEnvelope");
        return RMW_RET_ERROR;
    }

    // Read ServiceEnvelope
    rmw_dsoftbus::ServiceEnvelope envelope;
    rmw_dsoftbus::deserialize_envelope(buffer, envelope);

    // Verify message type
    if (expected_type == rmw_dsoftbus::ServiceMessageType::REQUEST && !envelope.is_request()) {
        RMW_SET_ERROR_MSG("Expected REQUEST but got RESPONSE");
        return RMW_RET_ERROR;
    }
    if (expected_type == rmw_dsoftbus::ServiceMessageType::RESPONSE && !envelope.is_response()) {
        RMW_SET_ERROR_MSG("Expected RESPONSE but got REQUEST");
        return RMW_RET_ERROR;
    }

    *request_id_out = envelope.request_id;

    // Deserialize CDR payload
    const uint8_t* cdr_buffer = buffer + rmw_dsoftbus::SERVICE_ENVELOPE_SIZE;
    const size_t cdr_size = size - rmw_dsoftbus::SERVICE_ENVELOPE_SIZE;

    if (!rmw_dsoftbus_deserialize_ros_message(cdr_buffer, cdr_size, msg_type_support, ros_message_out)) {
        RMW_SET_ERROR_MSG("Failed to deserialize CDR payload");
        return RMW_RET_ERROR;
    }

    return RMW_RET_OK;
}

}  // anonymous namespace

// ============================================================================
// C API Implementation
// ============================================================================

extern "C" {

const rosidl_message_type_support_t* rmw_dsoftbus_get_request_typesupport(
    const rosidl_service_type_support_t* service_type_support)
{
    const auto* members = get_service_members(service_type_support);
    if (!members) {
        return nullptr;
    }
    return members->request_members_;
}

const rosidl_message_type_support_t* rmw_dsoftbus_get_response_typesupport(
    const rosidl_service_type_support_t* service_type_support)
{
    const auto* members = get_service_members(service_type_support);
    if (!members) {
        return nullptr;
    }
    return members->response_members_;
}

rmw_ret_t rmw_dsoftbus_serialize_request(
    const void* ros_request,
    const rosidl_service_type_support_t* type_support,
    uint64_t request_id,
    uint8_t** buffer_out,
    size_t* size_out)
{
    // Get request message type support
    const rosidl_message_type_support_t* msg_ts = rmw_dsoftbus_get_request_typesupport(type_support);
    if (!msg_ts) {
        RMW_SET_ERROR_MSG("Unsupported service typesupport: only introspection variants supported");
        return RMW_RET_UNSUPPORTED;
    }

    return serialize_with_envelope(
        ros_request, msg_ts, request_id,
        rmw_dsoftbus::ServiceMessageType::REQUEST,
        buffer_out, size_out);
}

rmw_ret_t rmw_dsoftbus_serialize_response(
    const void* ros_response,
    const rosidl_service_type_support_t* type_support,
    uint64_t request_id,
    uint8_t** buffer_out,
    size_t* size_out)
{
    // Get response message type support
    const rosidl_message_type_support_t* msg_ts = rmw_dsoftbus_get_response_typesupport(type_support);
    if (!msg_ts) {
        RMW_SET_ERROR_MSG("Unsupported service typesupport: only introspection variants supported");
        return RMW_RET_UNSUPPORTED;
    }

    return serialize_with_envelope(
        ros_response, msg_ts, request_id,
        rmw_dsoftbus::ServiceMessageType::RESPONSE,
        buffer_out, size_out);
}

rmw_ret_t rmw_dsoftbus_deserialize_request(
    const uint8_t* buffer,
    size_t size,
    const rosidl_service_type_support_t* type_support,
    uint64_t* request_id_out,
    void* ros_request_out)
{
    // Get request message type support
    const rosidl_message_type_support_t* msg_ts = rmw_dsoftbus_get_request_typesupport(type_support);
    if (!msg_ts) {
        RMW_SET_ERROR_MSG("Unsupported service typesupport: only introspection variants supported");
        return RMW_RET_UNSUPPORTED;
    }

    return deserialize_with_envelope(
        buffer, size, msg_ts,
        rmw_dsoftbus::ServiceMessageType::REQUEST,
        request_id_out, ros_request_out);
}

rmw_ret_t rmw_dsoftbus_deserialize_response(
    const uint8_t* buffer,
    size_t size,
    const rosidl_service_type_support_t* type_support,
    uint64_t* request_id_out,
    void* ros_response_out)
{
    // Get response message type support
    const rosidl_message_type_support_t* msg_ts = rmw_dsoftbus_get_response_typesupport(type_support);
    if (!msg_ts) {
        RMW_SET_ERROR_MSG("Unsupported service typesupport: only introspection variants supported");
        return RMW_RET_UNSUPPORTED;
    }

    return deserialize_with_envelope(
        buffer, size, msg_ts,
        rmw_dsoftbus::ServiceMessageType::RESPONSE,
        request_id_out, ros_response_out);
}

}  // extern "C"
