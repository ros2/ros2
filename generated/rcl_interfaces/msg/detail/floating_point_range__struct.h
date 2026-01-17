// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rcl_interfaces:msg/FloatingPointRange.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/msg/floating_point_range.h"


#ifndef RCL_INTERFACES__MSG__DETAIL__FLOATING_POINT_RANGE__STRUCT_H_
#define RCL_INTERFACES__MSG__DETAIL__FLOATING_POINT_RANGE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/FloatingPointRange in the package rcl_interfaces.
/**
  * Represents bounds and a step value for a floating point typed parameter.
 */
typedef struct rcl_interfaces__msg__FloatingPointRange
{
  /// Start value for valid values, inclusive.
  double from_value;
  /// End value for valid values, inclusive.
  double to_value;
  /// Size of valid steps between the from and to bound.
  ///
  /// Step is considered to be a magnitude, therefore negative values are treated
  /// the same as positive values, and a step value of zero implies a continuous
  /// range of values.
  ///
  /// Ideally, the step would be less than or equal to the distance between the
  /// bounds, as well as an even multiple of the distance between the bounds, but
  /// neither are required.
  ///
  /// If the absolute value of the step is larger than or equal to the distance
  /// between the two bounds, then the bounds will be the only valid values. e.g. if
  /// the range is defined as {from_value: 1.0, to_value: 2.0, step: 5.0} then the
  /// valid values will be 1.0 and 2.0.
  ///
  /// If the step is less than the distance between the bounds, but the distance is
  /// not a multiple of the step, then the "to" bound will always be a valid value,
  /// e.g. if the range is defined as {from_value: 2.0, to_value: 5.0, step: 2.0}
  /// then the valid values will be 2.0, 4.0, and 5.0.
  double step;
} rcl_interfaces__msg__FloatingPointRange;

// Struct for a sequence of rcl_interfaces__msg__FloatingPointRange.
typedef struct rcl_interfaces__msg__FloatingPointRange__Sequence
{
  rcl_interfaces__msg__FloatingPointRange * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rcl_interfaces__msg__FloatingPointRange__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RCL_INTERFACES__MSG__DETAIL__FLOATING_POINT_RANGE__STRUCT_H_
