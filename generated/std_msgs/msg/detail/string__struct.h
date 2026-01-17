// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from std_msgs:msg/String.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "std_msgs/msg/string.h"


#ifndef STD_MSGS__MSG__DETAIL__STRING__STRUCT_H_
#define STD_MSGS__MSG__DETAIL__STRING__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'data'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/String in the package std_msgs.
/**
  * This was originally provided as an example message.
  * It is deprecated as of Foxy
  * It is recommended to create your own semantically meaningful message.
  * However if you would like to continue using this please use the equivalent in example_msgs.
 */
typedef struct std_msgs__msg__String
{
  rosidl_runtime_c__String data;
} std_msgs__msg__String;

// Struct for a sequence of std_msgs__msg__String.
typedef struct std_msgs__msg__String__Sequence
{
  std_msgs__msg__String * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} std_msgs__msg__String__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // STD_MSGS__MSG__DETAIL__STRING__STRUCT_H_
