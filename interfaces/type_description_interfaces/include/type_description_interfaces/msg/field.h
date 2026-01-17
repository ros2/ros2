// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// type_description_interfaces/msg/Field type

#ifndef TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_H_
#define TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "type_description_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "type_description_interfaces/msg/field_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/// A field within a message type
typedef struct type_description_interfaces__msg__Field
{
  /// Name of the field
  rosidl_runtime_c__String name;
  /// Type of the field
  type_description_interfaces__msg__FieldType type;
  /// Default value as string (empty if no default)
  rosidl_runtime_c__String default_value;
} type_description_interfaces__msg__Field;

typedef struct type_description_interfaces__msg__Field__Sequence
{
  type_description_interfaces__msg__Field * data;
  size_t size;
  size_t capacity;
} type_description_interfaces__msg__Field__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
bool type_description_interfaces__msg__Field__init(type_description_interfaces__msg__Field * msg);

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
void type_description_interfaces__msg__Field__fini(type_description_interfaces__msg__Field * msg);

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
type_description_interfaces__msg__Field * type_description_interfaces__msg__Field__create(void);

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
void type_description_interfaces__msg__Field__destroy(type_description_interfaces__msg__Field * msg);

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
bool type_description_interfaces__msg__Field__Sequence__init(
  type_description_interfaces__msg__Field__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
void type_description_interfaces__msg__Field__Sequence__fini(
  type_description_interfaces__msg__Field__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // TYPE_DESCRIPTION_INTERFACES__MSG__FIELD_H_
