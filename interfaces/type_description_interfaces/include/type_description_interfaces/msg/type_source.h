// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// type_description_interfaces/msg/TypeSource type

#ifndef TYPE_DESCRIPTION_INTERFACES__MSG__TYPE_SOURCE_H_
#define TYPE_DESCRIPTION_INTERFACES__MSG__TYPE_SOURCE_H_

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

/// Source definition of a type
typedef struct type_description_interfaces__msg__TypeSource
{
  /// Fully qualified type name
  rosidl_runtime_c__String type_name;
  /// Encoding of the source (e.g., "msg", "idl", "dds")
  rosidl_runtime_c__String encoding;
  /// Raw source definition
  rosidl_runtime_c__String raw_source;
} type_description_interfaces__msg__TypeSource;

typedef struct type_description_interfaces__msg__TypeSource__Sequence
{
  type_description_interfaces__msg__TypeSource * data;
  size_t size;
  size_t capacity;
} type_description_interfaces__msg__TypeSource__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
bool type_description_interfaces__msg__TypeSource__init(
  type_description_interfaces__msg__TypeSource * msg);

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
void type_description_interfaces__msg__TypeSource__fini(
  type_description_interfaces__msg__TypeSource * msg);

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
type_description_interfaces__msg__TypeSource *
type_description_interfaces__msg__TypeSource__create(void);

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
void type_description_interfaces__msg__TypeSource__destroy(
  type_description_interfaces__msg__TypeSource * msg);

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
bool type_description_interfaces__msg__TypeSource__Sequence__init(
  type_description_interfaces__msg__TypeSource__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
void type_description_interfaces__msg__TypeSource__Sequence__fini(
  type_description_interfaces__msg__TypeSource__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // TYPE_DESCRIPTION_INTERFACES__MSG__TYPE_SOURCE_H_
