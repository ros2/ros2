// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// type_description_interfaces/msg/TypeDescription type

#ifndef TYPE_DESCRIPTION_INTERFACES__MSG__TYPE_DESCRIPTION_H_
#define TYPE_DESCRIPTION_INTERFACES__MSG__TYPE_DESCRIPTION_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "type_description_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "type_description_interfaces/msg/individual_type_description.h"

#ifdef __cplusplus
extern "C" {
#endif

/// Full description of a type including all dependencies
typedef struct type_description_interfaces__msg__TypeDescription
{
  /// The main type being described
  type_description_interfaces__msg__IndividualTypeDescription type_description;
  /// Descriptions of all referenced types (sorted by type name)
  type_description_interfaces__msg__IndividualTypeDescription__Sequence referenced_type_descriptions;
} type_description_interfaces__msg__TypeDescription;

typedef struct type_description_interfaces__msg__TypeDescription__Sequence
{
  type_description_interfaces__msg__TypeDescription * data;
  size_t size;
  size_t capacity;
} type_description_interfaces__msg__TypeDescription__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
bool type_description_interfaces__msg__TypeDescription__init(
  type_description_interfaces__msg__TypeDescription * msg);

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
void type_description_interfaces__msg__TypeDescription__fini(
  type_description_interfaces__msg__TypeDescription * msg);

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
type_description_interfaces__msg__TypeDescription *
type_description_interfaces__msg__TypeDescription__create(void);

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
void type_description_interfaces__msg__TypeDescription__destroy(
  type_description_interfaces__msg__TypeDescription * msg);

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
bool type_description_interfaces__msg__TypeDescription__Sequence__init(
  type_description_interfaces__msg__TypeDescription__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
void type_description_interfaces__msg__TypeDescription__Sequence__fini(
  type_description_interfaces__msg__TypeDescription__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // TYPE_DESCRIPTION_INTERFACES__MSG__TYPE_DESCRIPTION_H_
