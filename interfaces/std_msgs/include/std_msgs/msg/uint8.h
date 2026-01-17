// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_msgs/msg/UInt8 message type

#ifndef STD_MSGS__MSG__UINT8_H_
#define STD_MSGS__MSG__UINT8_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "std_msgs/msg/rosidl_generator_c__visibility_control.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct std_msgs__msg__UInt8
{
  uint8_t data;
} std_msgs__msg__UInt8;

typedef struct std_msgs__msg__UInt8__Sequence
{
  std_msgs__msg__UInt8 * data;
  size_t size;
  size_t capacity;
} std_msgs__msg__UInt8__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
bool std_msgs__msg__UInt8__init(std_msgs__msg__UInt8 * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__UInt8__fini(std_msgs__msg__UInt8 * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
std_msgs__msg__UInt8 * std_msgs__msg__UInt8__create(void);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__UInt8__destroy(std_msgs__msg__UInt8 * msg);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
bool std_msgs__msg__UInt8__Sequence__init(
  std_msgs__msg__UInt8__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_std_msgs
void std_msgs__msg__UInt8__Sequence__fini(
  std_msgs__msg__UInt8__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // STD_MSGS__MSG__UINT8_H_
