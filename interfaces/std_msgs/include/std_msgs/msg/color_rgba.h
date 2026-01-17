// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_msgs/msg/ColorRGBA message type

#ifndef STD_MSGS__MSG__COLOR_RGBA_H_
#define STD_MSGS__MSG__COLOR_RGBA_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "std_msgs/msg/rosidl_generator_c__visibility_control.h"

#ifdef __cplusplus
extern "C" {
#endif

/// ColorRGBA message
typedef struct std_msgs__msg__ColorRGBA
{
  float r;
  float g;
  float b;
  float a;
} std_msgs__msg__ColorRGBA;

typedef struct std_msgs__msg__ColorRGBA__Sequence
{
  std_msgs__msg__ColorRGBA * data;
  size_t size;
  size_t capacity;
} std_msgs__msg__ColorRGBA__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
bool std_msgs__msg__ColorRGBA__init(std_msgs__msg__ColorRGBA * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__ColorRGBA__fini(std_msgs__msg__ColorRGBA * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
std_msgs__msg__ColorRGBA * std_msgs__msg__ColorRGBA__create(void);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__ColorRGBA__destroy(std_msgs__msg__ColorRGBA * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
bool std_msgs__msg__ColorRGBA__Sequence__init(
  std_msgs__msg__ColorRGBA__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__ColorRGBA__Sequence__fini(
  std_msgs__msg__ColorRGBA__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // STD_MSGS__MSG__COLOR_RGBA_H_
