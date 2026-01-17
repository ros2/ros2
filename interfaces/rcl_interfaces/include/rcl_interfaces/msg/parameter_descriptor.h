// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/msg/ParameterDescriptor type

#ifndef RCL_INTERFACES__MSG__PARAMETERDESCRIPTOR_H_
#define RCL_INTERFACES__MSG__PARAMETERDESCRIPTOR_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "rcl_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "rosidl_runtime_c/string.h"
#include "rcl_interfaces/msg/floating_point_range.h"
#include "rcl_interfaces/msg/integer_range.h"

#ifdef __cplusplus
extern "C" {
#endif



/// Parameter description with constraints
typedef struct rcl_interfaces__msg__ParameterDescriptor
{
  rosidl_runtime_c__String name;
  uint8_t type;
  rosidl_runtime_c__String description;
  rosidl_runtime_c__String additional_constraints;
  bool read_only;
  bool dynamic_typing;
  rcl_interfaces__msg__FloatingPointRange__Sequence floating_point_range;
  rcl_interfaces__msg__IntegerRange__Sequence integer_range;
} rcl_interfaces__msg__ParameterDescriptor;

typedef struct rcl_interfaces__msg__ParameterDescriptor__Sequence
{
  rcl_interfaces__msg__ParameterDescriptor * data;
  size_t size;
  size_t capacity;
} rcl_interfaces__msg__ParameterDescriptor__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__msg__ParameterDescriptor__init(rcl_interfaces__msg__ParameterDescriptor * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__ParameterDescriptor__fini(rcl_interfaces__msg__ParameterDescriptor * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
rcl_interfaces__msg__ParameterDescriptor * rcl_interfaces__msg__ParameterDescriptor__create(void);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__ParameterDescriptor__destroy(rcl_interfaces__msg__ParameterDescriptor * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__msg__ParameterDescriptor__Sequence__init(
  rcl_interfaces__msg__ParameterDescriptor__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__ParameterDescriptor__Sequence__fini(
  rcl_interfaces__msg__ParameterDescriptor__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // RCL_INTERFACES__MSG__PARAMETERDESCRIPTOR_H_
