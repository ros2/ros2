// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rosgraph_msgs:msg/Clock.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rosgraph_msgs/msg/clock.h"


#ifndef ROSGRAPH_MSGS__MSG__DETAIL__CLOCK__STRUCT_H_
#define ROSGRAPH_MSGS__MSG__DETAIL__CLOCK__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'clock'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in msg/Clock in the package rosgraph_msgs.
/**
  * This message communicates the current time.
  *
  * For more information, see https://design.ros2.org/articles/clock_and_time.html.
 */
typedef struct rosgraph_msgs__msg__Clock
{
  builtin_interfaces__msg__Time clock;
} rosgraph_msgs__msg__Clock;

// Struct for a sequence of rosgraph_msgs__msg__Clock.
typedef struct rosgraph_msgs__msg__Clock__Sequence
{
  rosgraph_msgs__msg__Clock * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rosgraph_msgs__msg__Clock__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROSGRAPH_MSGS__MSG__DETAIL__CLOCK__STRUCT_H_
