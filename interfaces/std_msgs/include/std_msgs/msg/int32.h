// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_msgs/msg/Int32 message type

#ifndef STD_MSGS__MSG__INT32_H_
#define STD_MSGS__MSG__INT32_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "std_msgs/msg/rosidl_generator_c__visibility_control.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct std_msgs__msg__Int32
{
  int32_t data;
} std_msgs__msg__Int32;

typedef struct std_msgs__msg__Int32__Sequence
{
  std_msgs__msg__Int32 * data;
  size_t size;
  size_t capacity;
} std_msgs__msg__Int32__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
bool std_msgs__msg__Int32__init(std_msgs__msg__Int32 * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__Int32__fini(std_msgs__msg__Int32 * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
std_msgs__msg__Int32 * std_msgs__msg__Int32__create(void);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__Int32__destroy(std_msgs__msg__Int32 * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
bool std_msgs__msg__Int32__Sequence__init(
  std_msgs__msg__Int32__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__Int32__Sequence__fini(
  std_msgs__msg__Int32__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // STD_MSGS__MSG__INT32_H_
