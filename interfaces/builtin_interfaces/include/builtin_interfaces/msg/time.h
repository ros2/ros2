// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// builtin_interfaces/msg/Time message type

#ifndef BUILTIN_INTERFACES__MSG__TIME_H_
#define BUILTIN_INTERFACES__MSG__TIME_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "builtin_interfaces/msg/rosidl_generator_c__visibility_control.h"

#ifdef __cplusplus
extern "C" {
#endif

/// Time represents a specific point in time
typedef struct builtin_interfaces__msg__Time
{
  /// Seconds since epoch
  int32_t sec;
  /// Nanoseconds component (0-999999999)
  uint32_t nanosec;
} builtin_interfaces__msg__Time;

/// Sequence of Time messages
typedef struct builtin_interfaces__msg__Time__Sequence
{
  builtin_interfaces__msg__Time * data;
  size_t size;
  size_t capacity;
} builtin_interfaces__msg__Time__Sequence;

/// Initialize a Time message
ROSIDL_GENERATOR_C_PUBLIC_builtin_interfaces
bool builtin_interfaces__msg__Time__init(builtin_interfaces__msg__Time * msg);

/// Finalize a Time message
ROSIDL_GENERATOR_C_PUBLIC_builtin_interfaces
void builtin_interfaces__msg__Time__fini(builtin_interfaces__msg__Time * msg);

/// Create a Time message
ROSIDL_GENERATOR_C_PUBLIC_builtin_interfaces
builtin_interfaces__msg__Time * builtin_interfaces__msg__Time__create(void);

/// Destroy a Time message
ROSIDL_GENERATOR_C_PUBLIC_builtin_interfaces
void builtin_interfaces__msg__Time__destroy(builtin_interfaces__msg__Time * msg);

/// Check equality of two Time messages
ROSIDL_GENERATOR_C_PUBLIC_builtin_interfaces
bool builtin_interfaces__msg__Time__are_equal(
  const builtin_interfaces__msg__Time * lhs,
  const builtin_interfaces__msg__Time * rhs);

/// Copy a Time message
ROSIDL_GENERATOR_C_PUBLIC_builtin_interfaces
bool builtin_interfaces__msg__Time__copy(
  const builtin_interfaces__msg__Time * input,
  builtin_interfaces__msg__Time * output);

/// Initialize a Time sequence
ROSIDL_GENERATOR_C_PUBLIC_builtin_interfaces
bool builtin_interfaces__msg__Time__Sequence__init(
  builtin_interfaces__msg__Time__Sequence * array, size_t size);

/// Finalize a Time sequence
ROSIDL_GENERATOR_C_PUBLIC_builtin_interfaces
void builtin_interfaces__msg__Time__Sequence__fini(
  builtin_interfaces__msg__Time__Sequence * array);

/// Create a Time sequence
ROSIDL_GENERATOR_C_PUBLIC_builtin_interfaces
builtin_interfaces__msg__Time__Sequence *
builtin_interfaces__msg__Time__Sequence__create(size_t size);

/// Destroy a Time sequence
ROSIDL_GENERATOR_C_PUBLIC_builtin_interfaces
void builtin_interfaces__msg__Time__Sequence__destroy(
  builtin_interfaces__msg__Time__Sequence * array);

/// Check equality of two Time sequences
ROSIDL_GENERATOR_C_PUBLIC_builtin_interfaces
bool builtin_interfaces__msg__Time__Sequence__are_equal(
  const builtin_interfaces__msg__Time__Sequence * lhs,
  const builtin_interfaces__msg__Time__Sequence * rhs);

/// Copy a Time sequence
ROSIDL_GENERATOR_C_PUBLIC_builtin_interfaces
bool builtin_interfaces__msg__Time__Sequence__copy(
  const builtin_interfaces__msg__Time__Sequence * input,
  builtin_interfaces__msg__Time__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // BUILTIN_INTERFACES__MSG__TIME_H_
