// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_msgs/msg/Byte message type

#ifndef STD_MSGS__MSG__BYTE_H_
#define STD_MSGS__MSG__BYTE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "std_msgs/msg/rosidl_generator_c__visibility_control.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct std_msgs__msg__Byte
{
  uint8_t data;
} std_msgs__msg__Byte;

typedef struct std_msgs__msg__Byte__Sequence
{
  std_msgs__msg__Byte * data;
  size_t size;
  size_t capacity;
} std_msgs__msg__Byte__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
bool std_msgs__msg__Byte__init(std_msgs__msg__Byte * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__Byte__fini(std_msgs__msg__Byte * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
std_msgs__msg__Byte * std_msgs__msg__Byte__create(void);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__Byte__destroy(std_msgs__msg__Byte * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
bool std_msgs__msg__Byte__Sequence__init(
  std_msgs__msg__Byte__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__Byte__Sequence__fini(
  std_msgs__msg__Byte__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // STD_MSGS__MSG__BYTE_H_
