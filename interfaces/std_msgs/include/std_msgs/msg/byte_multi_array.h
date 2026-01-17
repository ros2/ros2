// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_msgs/msg/ByteMultiArray message type

#ifndef STD_MSGS__MSG__BYTE_MULTI_ARRAY_H_
#define STD_MSGS__MSG__BYTE_MULTI_ARRAY_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "rosidl_runtime_c/primitives_sequence.h"
#include "std_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "std_msgs/msg/multi_array_layout.h"

#ifdef __cplusplus
extern "C" {
#endif

/// ByteMultiArray message
/// Please look at the MultiArrayLayout message definition for
/// documentation on all multiarrays.
typedef struct std_msgs__msg__ByteMultiArray
{
  /// specification of data layout
  std_msgs__msg__MultiArrayLayout layout;
  /// array of data
  rosidl_runtime_c__uint8__Sequence data;
} std_msgs__msg__ByteMultiArray;

typedef struct std_msgs__msg__ByteMultiArray__Sequence
{
  std_msgs__msg__ByteMultiArray * data;
  size_t size;
  size_t capacity;
} std_msgs__msg__ByteMultiArray__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
bool std_msgs__msg__ByteMultiArray__init(std_msgs__msg__ByteMultiArray * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__ByteMultiArray__fini(std_msgs__msg__ByteMultiArray * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
std_msgs__msg__ByteMultiArray * std_msgs__msg__ByteMultiArray__create(void);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__ByteMultiArray__destroy(std_msgs__msg__ByteMultiArray * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
bool std_msgs__msg__ByteMultiArray__Sequence__init(
  std_msgs__msg__ByteMultiArray__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__ByteMultiArray__Sequence__fini(
  std_msgs__msg__ByteMultiArray__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // STD_MSGS__MSG__BYTE_MULTI_ARRAY_H_
