// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rcl_interfaces:msg/IntegerRange.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/msg/integer_range.h"


#ifndef RCL_INTERFACES__MSG__DETAIL__INTEGER_RANGE__STRUCT_H_
#define RCL_INTERFACES__MSG__DETAIL__INTEGER_RANGE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/IntegerRange in the package rcl_interfaces.
/**
  * Represents bounds and a step value for an integer typed parameter.
 */
typedef struct rcl_interfaces__msg__IntegerRange
{
  /// Start value for valid values, inclusive.
  int64_t from_value;
  /// End value for valid values, inclusive.
  int64_t to_value;
  /// Size of valid steps between the from and to bound.
  ///
  /// A step value of zero implies a continuous range of values. Ideally, the step
  /// would be less than or equal to the distance between the bounds, as well as an
  /// even multiple of the distance between the bounds, but neither are required.
  ///
  /// If the absolute value of the step is larger than or equal to the distance
  /// between the two bounds, then the bounds will be the only valid values. e.g. if
  /// the range is defined as {from_value: 1, to_value: 2, step: 5} then the valid
  /// values will be 1 and 2.
  ///
  /// If the step is less than the distance between the bounds, but the distance is
  /// not a multiple of the step, then the "to" bound will always be a valid value,
  /// e.g. if the range is defined as {from_value: 2, to_value: 5, step: 2} then
  /// the valid values will be 2, 4, and 5.
  uint64_t step;
} rcl_interfaces__msg__IntegerRange;

// Struct for a sequence of rcl_interfaces__msg__IntegerRange.
typedef struct rcl_interfaces__msg__IntegerRange__Sequence
{
  rcl_interfaces__msg__IntegerRange * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rcl_interfaces__msg__IntegerRange__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RCL_INTERFACES__MSG__DETAIL__INTEGER_RANGE__STRUCT_H_
