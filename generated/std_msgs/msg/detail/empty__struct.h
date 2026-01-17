// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from std_msgs:msg/Empty.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "std_msgs/msg/empty.h"


#ifndef STD_MSGS__MSG__DETAIL__EMPTY__STRUCT_H_
#define STD_MSGS__MSG__DETAIL__EMPTY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/Empty in the package std_msgs.
typedef struct std_msgs__msg__Empty
{
  uint8_t structure_needs_at_least_one_member;
} std_msgs__msg__Empty;

// Struct for a sequence of std_msgs__msg__Empty.
typedef struct std_msgs__msg__Empty__Sequence
{
  std_msgs__msg__Empty * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} std_msgs__msg__Empty__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // STD_MSGS__MSG__DETAIL__EMPTY__STRUCT_H_
