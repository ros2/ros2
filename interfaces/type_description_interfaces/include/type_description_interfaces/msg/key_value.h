// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// type_description_interfaces/msg/KeyValue type

#ifndef TYPE_DESCRIPTION_INTERFACES__MSG__KEY_VALUE_H_
#define TYPE_DESCRIPTION_INTERFACES__MSG__KEY_VALUE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "type_description_interfaces/msg/rosidl_generator_c__visibility_control.h"

#ifdef __cplusplus
extern "C" {
#endif

/// Key-value metadata pair
typedef struct type_description_interfaces__msg__KeyValue
{
  rosidl_runtime_c__String key;
  rosidl_runtime_c__String value;
} type_description_interfaces__msg__KeyValue;

typedef struct type_description_interfaces__msg__KeyValue__Sequence
{
  type_description_interfaces__msg__KeyValue * data;
  size_t size;
  size_t capacity;
} type_description_interfaces__msg__KeyValue__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
bool type_description_interfaces__msg__KeyValue__init(
  type_description_interfaces__msg__KeyValue * msg);

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
void type_description_interfaces__msg__KeyValue__fini(
  type_description_interfaces__msg__KeyValue * msg);

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
type_description_interfaces__msg__KeyValue *
type_description_interfaces__msg__KeyValue__create(void);

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
void type_description_interfaces__msg__KeyValue__destroy(
  type_description_interfaces__msg__KeyValue * msg);

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
bool type_description_interfaces__msg__KeyValue__Sequence__init(
  type_description_interfaces__msg__KeyValue__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
void type_description_interfaces__msg__KeyValue__Sequence__fini(
  type_description_interfaces__msg__KeyValue__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // TYPE_DESCRIPTION_INTERFACES__MSG__KEY_VALUE_H_
