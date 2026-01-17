// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from std_msgs:msg/ColorRGBA.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "std_msgs/msg/color_rgba.h"


#ifndef STD_MSGS__MSG__DETAIL__COLOR_RGBA__STRUCT_H_
#define STD_MSGS__MSG__DETAIL__COLOR_RGBA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/ColorRGBA in the package std_msgs.
typedef struct std_msgs__msg__ColorRGBA
{
  float r;
  float g;
  float b;
  float a;
} std_msgs__msg__ColorRGBA;

// Struct for a sequence of std_msgs__msg__ColorRGBA.
typedef struct std_msgs__msg__ColorRGBA__Sequence
{
  std_msgs__msg__ColorRGBA * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} std_msgs__msg__ColorRGBA__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // STD_MSGS__MSG__DETAIL__COLOR_RGBA__STRUCT_H_
