// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_msgs/msg/Bool message type

#ifndef STD_MSGS__MSG__BOOL_H_
#define STD_MSGS__MSG__BOOL_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "std_msgs/msg/rosidl_generator_c__visibility_control.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct std_msgs__msg__Bool
{
  bool data;
} std_msgs__msg__Bool;

typedef struct std_msgs__msg__Bool__Sequence
{
  std_msgs__msg__Bool * data;
  size_t size;
  size_t capacity;
} std_msgs__msg__Bool__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
bool std_msgs__msg__Bool__init(std_msgs__msg__Bool * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__Bool__fini(std_msgs__msg__Bool * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
std_msgs__msg__Bool * std_msgs__msg__Bool__create(void);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__Bool__destroy(std_msgs__msg__Bool * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
bool std_msgs__msg__Bool__Sequence__init(
  std_msgs__msg__Bool__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__Bool__Sequence__fini(
  std_msgs__msg__Bool__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // STD_MSGS__MSG__BOOL_H_
