// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_msgs/msg/String message type

#ifndef STD_MSGS__MSG__STRING_H_
#define STD_MSGS__MSG__STRING_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "std_msgs/msg/rosidl_generator_c__visibility_control.h"

#ifdef __cplusplus
extern "C" {
#endif

/// String message containing a single string field
typedef struct std_msgs__msg__String
{
  rosidl_runtime_c__String data;
} std_msgs__msg__String;

/// Sequence of String messages
typedef struct std_msgs__msg__String__Sequence
{
  std_msgs__msg__String * data;
  size_t size;
  size_t capacity;
} std_msgs__msg__String__Sequence;

/// Initialize a String message
ROSIDL_GENERATOR_C_PUBLIC_std_msgs
bool std_msgs__msg__String__init(std_msgs__msg__String * msg);

/// Finalize a String message
ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__String__fini(std_msgs__msg__String * msg);

/// Create a String message
ROSIDL_GENERATOR_C_PUBLIC_std_msgs
std_msgs__msg__String * std_msgs__msg__String__create(void);

/// Destroy a String message
ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__String__destroy(std_msgs__msg__String * msg);

/// Check equality of two String messages
ROSIDL_GENERATOR_C_PUBLIC_std_msgs
bool std_msgs__msg__String__are_equal(
  const std_msgs__msg__String * lhs,
  const std_msgs__msg__String * rhs);

/// Copy a String message
ROSIDL_GENERATOR_C_PUBLIC_std_msgs
bool std_msgs__msg__String__copy(
  const std_msgs__msg__String * input,
  std_msgs__msg__String * output);

/// Initialize a String sequence
ROSIDL_GENERATOR_C_PUBLIC_std_msgs
bool std_msgs__msg__String__Sequence__init(
  std_msgs__msg__String__Sequence * array, size_t size);

/// Finalize a String sequence
ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__String__Sequence__fini(
  std_msgs__msg__String__Sequence * array);

/// Create a String sequence
ROSIDL_GENERATOR_C_PUBLIC_std_msgs
std_msgs__msg__String__Sequence *
std_msgs__msg__String__Sequence__create(size_t size);

/// Destroy a String sequence
ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__String__Sequence__destroy(
  std_msgs__msg__String__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // STD_MSGS__MSG__STRING_H_
