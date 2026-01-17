// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_msgs/msg/Char message type

#ifndef STD_MSGS__MSG__CHAR_H_
#define STD_MSGS__MSG__CHAR_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "std_msgs/msg/rosidl_generator_c__visibility_control.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct std_msgs__msg__Char
{
  uint8_t data;
} std_msgs__msg__Char;

typedef struct std_msgs__msg__Char__Sequence
{
  std_msgs__msg__Char * data;
  size_t size;
  size_t capacity;
} std_msgs__msg__Char__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
bool std_msgs__msg__Char__init(std_msgs__msg__Char * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__Char__fini(std_msgs__msg__Char * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
std_msgs__msg__Char * std_msgs__msg__Char__create(void);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__Char__destroy(std_msgs__msg__Char * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
bool std_msgs__msg__Char__Sequence__init(
  std_msgs__msg__Char__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__Char__Sequence__fini(
  std_msgs__msg__Char__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // STD_MSGS__MSG__CHAR_H_
