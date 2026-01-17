// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// builtin_interfaces/msg/Duration message type

#ifndef BUILTIN_INTERFACES__MSG__DURATION_H_
#define BUILTIN_INTERFACES__MSG__DURATION_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "builtin_interfaces/msg/rosidl_generator_c__visibility_control.h"

#ifdef __cplusplus
extern "C" {
#endif

/// Duration represents a period of time
typedef struct builtin_interfaces__msg__Duration
{
  /// Seconds component
  int32_t sec;
  /// Nanoseconds component (0-999999999)
  uint32_t nanosec;
} builtin_interfaces__msg__Duration;

/// Sequence of Duration messages
typedef struct builtin_interfaces__msg__Duration__Sequence
{
  builtin_interfaces__msg__Duration * data;
  size_t size;
  size_t capacity;
} builtin_interfaces__msg__Duration__Sequence;

/// Initialize a Duration message
ROSIDL_GENERATOR_C_PUBLIC_builtin_interfaces
bool builtin_interfaces__msg__Duration__init(builtin_interfaces__msg__Duration * msg);

/// Finalize a Duration message
ROSIDL_GENERATOR_C_PUBLIC_builtin_interfaces
void builtin_interfaces__msg__Duration__fini(builtin_interfaces__msg__Duration * msg);

/// Create a Duration message
ROSIDL_GENERATOR_C_PUBLIC_builtin_interfaces
builtin_interfaces__msg__Duration * builtin_interfaces__msg__Duration__create(void);

/// Destroy a Duration message
ROSIDL_GENERATOR_C_PUBLIC_builtin_interfaces
void builtin_interfaces__msg__Duration__destroy(builtin_interfaces__msg__Duration * msg);

/// Check equality of two Duration messages
ROSIDL_GENERATOR_C_PUBLIC_builtin_interfaces
bool builtin_interfaces__msg__Duration__are_equal(
  const builtin_interfaces__msg__Duration * lhs,
  const builtin_interfaces__msg__Duration * rhs);

/// Copy a Duration message
ROSIDL_GENERATOR_C_PUBLIC_builtin_interfaces
bool builtin_interfaces__msg__Duration__copy(
  const builtin_interfaces__msg__Duration * input,
  builtin_interfaces__msg__Duration * output);

/// Initialize a Duration sequence
ROSIDL_GENERATOR_C_PUBLIC_builtin_interfaces
bool builtin_interfaces__msg__Duration__Sequence__init(
  builtin_interfaces__msg__Duration__Sequence * array, size_t size);

/// Finalize a Duration sequence
ROSIDL_GENERATOR_C_PUBLIC_builtin_interfaces
void builtin_interfaces__msg__Duration__Sequence__fini(
  builtin_interfaces__msg__Duration__Sequence * array);

/// Create a Duration sequence
ROSIDL_GENERATOR_C_PUBLIC_builtin_interfaces
builtin_interfaces__msg__Duration__Sequence *
builtin_interfaces__msg__Duration__Sequence__create(size_t size);

/// Destroy a Duration sequence
ROSIDL_GENERATOR_C_PUBLIC_builtin_interfaces
void builtin_interfaces__msg__Duration__Sequence__destroy(
  builtin_interfaces__msg__Duration__Sequence * array);

/// Check equality of two Duration sequences
ROSIDL_GENERATOR_C_PUBLIC_builtin_interfaces
bool builtin_interfaces__msg__Duration__Sequence__are_equal(
  const builtin_interfaces__msg__Duration__Sequence * lhs,
  const builtin_interfaces__msg__Duration__Sequence * rhs);

/// Copy a Duration sequence
ROSIDL_GENERATOR_C_PUBLIC_builtin_interfaces
bool builtin_interfaces__msg__Duration__Sequence__copy(
  const builtin_interfaces__msg__Duration__Sequence * input,
  builtin_interfaces__msg__Duration__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // BUILTIN_INTERFACES__MSG__DURATION_H_
