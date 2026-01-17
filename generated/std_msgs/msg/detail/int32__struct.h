// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from std_msgs:msg/Int32.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "std_msgs/msg/int32.h"


#ifndef STD_MSGS__MSG__DETAIL__INT32__STRUCT_H_
#define STD_MSGS__MSG__DETAIL__INT32__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/Int32 in the package std_msgs.
/**
  * This was originally provided as an example message.
  * It is deprecated as of Foxy
  * It is recommended to create your own semantically meaningful message.
  * However if you would like to continue using this please use the equivalent in example_msgs.
 */
typedef struct std_msgs__msg__Int32
{
  int32_t data;
} std_msgs__msg__Int32;

// Struct for a sequence of std_msgs__msg__Int32.
typedef struct std_msgs__msg__Int32__Sequence
{
  std_msgs__msg__Int32 * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} std_msgs__msg__Int32__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // STD_MSGS__MSG__DETAIL__INT32__STRUCT_H_
