// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_msgs/msg/UInt16MultiArray message type

#ifndef STD_MSGS__MSG__UINT16_MULTI_ARRAY_H_
#define STD_MSGS__MSG__UINT16_MULTI_ARRAY_H_

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

/// UInt16MultiArray message
/// Please look at the MultiArrayLayout message definition for
/// documentation on all multiarrays.
typedef struct std_msgs__msg__UInt16MultiArray
{
  /// specification of data layout
  std_msgs__msg__MultiArrayLayout layout;
  /// array of data
  rosidl_runtime_c__uint16__Sequence data;
} std_msgs__msg__UInt16MultiArray;

typedef struct std_msgs__msg__UInt16MultiArray__Sequence
{
  std_msgs__msg__UInt16MultiArray * data;
  size_t size;
  size_t capacity;
} std_msgs__msg__UInt16MultiArray__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
bool std_msgs__msg__UInt16MultiArray__init(std_msgs__msg__UInt16MultiArray * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__UInt16MultiArray__fini(std_msgs__msg__UInt16MultiArray * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
std_msgs__msg__UInt16MultiArray * std_msgs__msg__UInt16MultiArray__create(void);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__UInt16MultiArray__destroy(std_msgs__msg__UInt16MultiArray * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
bool std_msgs__msg__UInt16MultiArray__Sequence__init(
  std_msgs__msg__UInt16MultiArray__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__UInt16MultiArray__Sequence__fini(
  std_msgs__msg__UInt16MultiArray__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // STD_MSGS__MSG__UINT16_MULTI_ARRAY_H_
