// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_msgs/msg/Empty message type

#ifndef STD_MSGS__MSG__EMPTY_H_
#define STD_MSGS__MSG__EMPTY_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "std_msgs/msg/rosidl_generator_c__visibility_control.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct std_msgs__msg__Empty
{
  uint8_t structure_needs_at_least_one_member;
} std_msgs__msg__Empty;

typedef struct std_msgs__msg__Empty__Sequence
{
  std_msgs__msg__Empty * data;
  size_t size;
  size_t capacity;
} std_msgs__msg__Empty__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
bool std_msgs__msg__Empty__init(std_msgs__msg__Empty * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__Empty__fini(std_msgs__msg__Empty * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
std_msgs__msg__Empty * std_msgs__msg__Empty__create(void);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__Empty__destroy(std_msgs__msg__Empty * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
bool std_msgs__msg__Empty__Sequence__init(
  std_msgs__msg__Empty__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__Empty__Sequence__fini(
  std_msgs__msg__Empty__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // STD_MSGS__MSG__EMPTY_H_
