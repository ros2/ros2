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

//
// Generic ROS2 Message Serializer using rosidl_typesupport_introspection_c
// Header file

#ifndef RMW_DSOFTBUS__TYPESUPPORT_SERIALIZER_H_
#define RMW_DSOFTBUS__TYPESUPPORT_SERIALIZER_H_

#include <rosidl_runtime_c/message_type_support_struct.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Serialize a ROS2 message to CDR format using typesupport introspection.
 *
 * @param ros_message Pointer to the ROS2 message to serialize
 * @param type_support Pointer to the message type support
 * @param cdr_buffer Output pointer to allocated CDR buffer (caller must free)
 * @param cdr_size Output size of the CDR buffer
 * @return true on success, false on failure
 */
bool rmw_dsoftbus_serialize_ros_message(
    const void* ros_message,
    const rosidl_message_type_support_t* type_support,
    uint8_t** cdr_buffer,
    size_t* cdr_size);

/**
 * @brief Deserialize a CDR buffer to a ROS2 message using typesupport introspection.
 *
 * @param cdr_buffer Pointer to the CDR buffer
 * @param cdr_size Size of the CDR buffer
 * @param type_support Pointer to the message type support
 * @param ros_message Pointer to the ROS2 message to populate
 * @return true on success, false on failure
 */
bool rmw_dsoftbus_deserialize_ros_message(
    const uint8_t* cdr_buffer,
    size_t cdr_size,
    const rosidl_message_type_support_t* type_support,
    void* ros_message);

#ifdef __cplusplus
}
#endif

#endif  // RMW_DSOFTBUS__TYPESUPPORT_SERIALIZER_H_
