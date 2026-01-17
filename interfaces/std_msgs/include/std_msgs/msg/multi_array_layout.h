// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_msgs/msg/MultiArrayLayout message type

#ifndef STD_MSGS__MSG__MULTI_ARRAY_LAYOUT_H_
#define STD_MSGS__MSG__MULTI_ARRAY_LAYOUT_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "std_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "std_msgs/msg/multi_array_dimension.h"

#ifdef __cplusplus
extern "C" {
#endif

/// MultiArrayLayout message
/// The multiarray declares a generic multi-dimensional array of a
/// particular data type. Dimensions are ordered from outer most
/// to inner most.
typedef struct std_msgs__msg__MultiArrayLayout
{
  /// Array of dimension properties
  std_msgs__msg__MultiArrayDimension__Sequence dim;
  /// padding bytes at front of data
  uint32_t data_offset;
} std_msgs__msg__MultiArrayLayout;

typedef struct std_msgs__msg__MultiArrayLayout__Sequence
{
  std_msgs__msg__MultiArrayLayout * data;
  size_t size;
  size_t capacity;
} std_msgs__msg__MultiArrayLayout__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
bool std_msgs__msg__MultiArrayLayout__init(std_msgs__msg__MultiArrayLayout * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__MultiArrayLayout__fini(std_msgs__msg__MultiArrayLayout * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
std_msgs__msg__MultiArrayLayout * std_msgs__msg__MultiArrayLayout__create(void);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__MultiArrayLayout__destroy(std_msgs__msg__MultiArrayLayout * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
bool std_msgs__msg__MultiArrayLayout__Sequence__init(
  std_msgs__msg__MultiArrayLayout__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__MultiArrayLayout__Sequence__fini(
  std_msgs__msg__MultiArrayLayout__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // STD_MSGS__MSG__MULTI_ARRAY_LAYOUT_H_
