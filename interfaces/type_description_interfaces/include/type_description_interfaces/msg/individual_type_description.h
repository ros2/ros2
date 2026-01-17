// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// type_description_interfaces/msg/IndividualTypeDescription type

#ifndef TYPE_DESCRIPTION_INTERFACES__MSG__INDIVIDUAL_TYPE_DESCRIPTION_H_
#define TYPE_DESCRIPTION_INTERFACES__MSG__INDIVIDUAL_TYPE_DESCRIPTION_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "type_description_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "type_description_interfaces/msg/field.h"

#ifdef __cplusplus
extern "C" {
#endif

/// Description of a single type (without dependencies)
typedef struct type_description_interfaces__msg__IndividualTypeDescription
{
  /// Fully qualified type name
  rosidl_runtime_c__String type_name;
  /// Fields of the type
  type_description_interfaces__msg__Field__Sequence fields;
} type_description_interfaces__msg__IndividualTypeDescription;

typedef struct type_description_interfaces__msg__IndividualTypeDescription__Sequence
{
  type_description_interfaces__msg__IndividualTypeDescription * data;
  size_t size;
  size_t capacity;
} type_description_interfaces__msg__IndividualTypeDescription__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
bool type_description_interfaces__msg__IndividualTypeDescription__init(
  type_description_interfaces__msg__IndividualTypeDescription * msg);

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
void type_description_interfaces__msg__IndividualTypeDescription__fini(
  type_description_interfaces__msg__IndividualTypeDescription * msg);

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
type_description_interfaces__msg__IndividualTypeDescription *
type_description_interfaces__msg__IndividualTypeDescription__create(void);

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
void type_description_interfaces__msg__IndividualTypeDescription__destroy(
  type_description_interfaces__msg__IndividualTypeDescription * msg);

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
bool type_description_interfaces__msg__IndividualTypeDescription__Sequence__init(
  type_description_interfaces__msg__IndividualTypeDescription__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
void type_description_interfaces__msg__IndividualTypeDescription__Sequence__fini(
  type_description_interfaces__msg__IndividualTypeDescription__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // TYPE_DESCRIPTION_INTERFACES__MSG__INDIVIDUAL_TYPE_DESCRIPTION_H_
