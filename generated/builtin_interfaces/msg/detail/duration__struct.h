// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from builtin_interfaces:msg/Duration.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "builtin_interfaces/msg/duration.h"


#ifndef BUILTIN_INTERFACES__MSG__DETAIL__DURATION__STRUCT_H_
#define BUILTIN_INTERFACES__MSG__DETAIL__DURATION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/Duration in the package builtin_interfaces.
/**
  * Duration defines a period between two time points.
  * Messages of this datatype are of ROS Time following this design:
  * https://design.ros2.org/articles/clock_and_time.html
 */
typedef struct builtin_interfaces__msg__Duration
{
  /// The seconds component, valid over all int32 values.
  int32_t sec;
  /// The nanoseconds component, valid in the range [0, 1e9), to be added to the seconds component.
  /// e.g.
  /// The duration -1.7 seconds is represented as {sec: -2, nanosec: 3e8}
  /// The duration 1.7 seconds is represented as {sec: 1, nanosec: 7e8}
  uint32_t nanosec;
} builtin_interfaces__msg__Duration;

// Struct for a sequence of builtin_interfaces__msg__Duration.
typedef struct builtin_interfaces__msg__Duration__Sequence
{
  builtin_interfaces__msg__Duration * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} builtin_interfaces__msg__Duration__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // BUILTIN_INTERFACES__MSG__DETAIL__DURATION__STRUCT_H_
