// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_msgs/msg/MultiArrayDimension message type

#ifndef STD_MSGS__MSG__MULTI_ARRAY_DIMENSION_H_
#define STD_MSGS__MSG__MULTI_ARRAY_DIMENSION_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "rosidl_runtime_c/string.h"
#include "std_msgs/msg/rosidl_generator_c__visibility_control.h"

#ifdef __cplusplus
extern "C" {
#endif

/// MultiArrayDimension message
/// This describes the dimension of a multi-array
typedef struct std_msgs__msg__MultiArrayDimension
{
  /// label of given dimension
  rosidl_runtime_c__String label;
  /// size of given dimension (in type units)
  uint32_t size;
  /// stride of given dimension
  uint32_t stride;
} std_msgs__msg__MultiArrayDimension;

typedef struct std_msgs__msg__MultiArrayDimension__Sequence
{
  std_msgs__msg__MultiArrayDimension * data;
  size_t size;
  size_t capacity;
} std_msgs__msg__MultiArrayDimension__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
bool std_msgs__msg__MultiArrayDimension__init(std_msgs__msg__MultiArrayDimension * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__MultiArrayDimension__fini(std_msgs__msg__MultiArrayDimension * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
std_msgs__msg__MultiArrayDimension * std_msgs__msg__MultiArrayDimension__create(void);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__MultiArrayDimension__destroy(std_msgs__msg__MultiArrayDimension * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
bool std_msgs__msg__MultiArrayDimension__Sequence__init(
  std_msgs__msg__MultiArrayDimension__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__MultiArrayDimension__Sequence__fini(
  std_msgs__msg__MultiArrayDimension__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // STD_MSGS__MSG__MULTI_ARRAY_DIMENSION_H_
