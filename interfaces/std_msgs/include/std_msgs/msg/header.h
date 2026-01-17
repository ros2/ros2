// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_msgs/msg/Header message type

#ifndef STD_MSGS__MSG__HEADER_H_
#define STD_MSGS__MSG__HEADER_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "std_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "builtin_interfaces/msg/time.h"

#ifdef __cplusplus
extern "C" {
#endif

/// Standard metadata for higher-level stamped data types
typedef struct std_msgs__msg__Header
{
  /// Timestamp of the message
  builtin_interfaces__msg__Time stamp;
  /// Frame ID for the message
  rosidl_runtime_c__String frame_id;
} std_msgs__msg__Header;

/// Sequence of Header messages
typedef struct std_msgs__msg__Header__Sequence
{
  std_msgs__msg__Header * data;
  size_t size;
  size_t capacity;
} std_msgs__msg__Header__Sequence;

/// Initialize a Header message
ROSIDL_GENERATOR_C_PUBLIC_std_msgs
bool std_msgs__msg__Header__init(std_msgs__msg__Header * msg);

/// Finalize a Header message
ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__Header__fini(std_msgs__msg__Header * msg);

/// Create a Header message
ROSIDL_GENERATOR_C_PUBLIC_std_msgs
std_msgs__msg__Header * std_msgs__msg__Header__create(void);

/// Destroy a Header message
ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__Header__destroy(std_msgs__msg__Header * msg);

/// Check equality of two Header messages
ROSIDL_GENERATOR_C_PUBLIC_std_msgs
bool std_msgs__msg__Header__are_equal(
  const std_msgs__msg__Header * lhs,
  const std_msgs__msg__Header * rhs);

/// Copy a Header message
ROSIDL_GENERATOR_C_PUBLIC_std_msgs
bool std_msgs__msg__Header__copy(
  const std_msgs__msg__Header * input,
  std_msgs__msg__Header * output);

/// Initialize a Header sequence
ROSIDL_GENERATOR_C_PUBLIC_std_msgs
bool std_msgs__msg__Header__Sequence__init(
  std_msgs__msg__Header__Sequence * array, size_t size);

/// Finalize a Header sequence
ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__Header__Sequence__fini(
  std_msgs__msg__Header__Sequence * array);

/// Create a Header sequence
ROSIDL_GENERATOR_C_PUBLIC_std_msgs
std_msgs__msg__Header__Sequence *
std_msgs__msg__Header__Sequence__create(size_t size);

/// Destroy a Header sequence
ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__Header__Sequence__destroy(
  std_msgs__msg__Header__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // STD_MSGS__MSG__HEADER_H_
