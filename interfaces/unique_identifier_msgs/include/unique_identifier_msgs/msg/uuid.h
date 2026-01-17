// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// unique_identifier_msgs/msg/UUID type

#ifndef UNIQUE_IDENTIFIER_MSGS__MSG__UUID_H_
#define UNIQUE_IDENTIFIER_MSGS__MSG__UUID_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "unique_identifier_msgs/msg/rosidl_generator_c__visibility_control.h"

#ifdef __cplusplus
extern "C" {
#endif

// UUID size constant
#define UNIQUE_IDENTIFIER_MSGS__MSG__UUID_SIZE 16

/// A universally unique identifier (UUID)
/// 128-bit number represented as 16 bytes
typedef struct unique_identifier_msgs__msg__UUID
{
  uint8_t uuid[16];
} unique_identifier_msgs__msg__UUID;

typedef struct unique_identifier_msgs__msg__UUID__Sequence
{
  unique_identifier_msgs__msg__UUID * data;
  size_t size;
  size_t capacity;
} unique_identifier_msgs__msg__UUID__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_unique_identifier_msgs
bool unique_identifier_msgs__msg__UUID__init(unique_identifier_msgs__msg__UUID * msg);

ROSIDL_GENERATOR_C_PUBLIC_unique_identifier_msgs
void unique_identifier_msgs__msg__UUID__fini(unique_identifier_msgs__msg__UUID * msg);

ROSIDL_GENERATOR_C_PUBLIC_unique_identifier_msgs
unique_identifier_msgs__msg__UUID * unique_identifier_msgs__msg__UUID__create(void);

ROSIDL_GENERATOR_C_PUBLIC_unique_identifier_msgs
void unique_identifier_msgs__msg__UUID__destroy(unique_identifier_msgs__msg__UUID * msg);

ROSIDL_GENERATOR_C_PUBLIC_unique_identifier_msgs
bool unique_identifier_msgs__msg__UUID__Sequence__init(
  unique_identifier_msgs__msg__UUID__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_unique_identifier_msgs
void unique_identifier_msgs__msg__UUID__Sequence__fini(
  unique_identifier_msgs__msg__UUID__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // UNIQUE_IDENTIFIER_MSGS__MSG__UUID_H_
