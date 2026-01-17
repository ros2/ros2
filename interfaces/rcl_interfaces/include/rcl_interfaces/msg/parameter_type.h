// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/msg/ParameterType type

#ifndef RCL_INTERFACES__MSG__PARAMETERTYPE_H_
#define RCL_INTERFACES__MSG__PARAMETERTYPE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "rcl_interfaces/msg/rosidl_generator_c__visibility_control.h"



#ifdef __cplusplus
extern "C" {
#endif

#define RCL_INTERFACES__MSG__PARAMETERTYPE__PARAMETER_NOT_SET ((uint8_t)0)
#define RCL_INTERFACES__MSG__PARAMETERTYPE__PARAMETER_BOOL ((uint8_t)1)
#define RCL_INTERFACES__MSG__PARAMETERTYPE__PARAMETER_INTEGER ((uint8_t)2)
#define RCL_INTERFACES__MSG__PARAMETERTYPE__PARAMETER_DOUBLE ((uint8_t)3)
#define RCL_INTERFACES__MSG__PARAMETERTYPE__PARAMETER_STRING ((uint8_t)4)
#define RCL_INTERFACES__MSG__PARAMETERTYPE__PARAMETER_BYTE_ARRAY ((uint8_t)5)
#define RCL_INTERFACES__MSG__PARAMETERTYPE__PARAMETER_BOOL_ARRAY ((uint8_t)6)
#define RCL_INTERFACES__MSG__PARAMETERTYPE__PARAMETER_INTEGER_ARRAY ((uint8_t)7)
#define RCL_INTERFACES__MSG__PARAMETERTYPE__PARAMETER_DOUBLE_ARRAY ((uint8_t)8)
#define RCL_INTERFACES__MSG__PARAMETERTYPE__PARAMETER_STRING_ARRAY ((uint8_t)9)

/// Constants for parameter types
typedef struct rcl_interfaces__msg__ParameterType
{
  uint8_t structure_needs_at_least_one_member;
} rcl_interfaces__msg__ParameterType;

typedef struct rcl_interfaces__msg__ParameterType__Sequence
{
  rcl_interfaces__msg__ParameterType * data;
  size_t size;
  size_t capacity;
} rcl_interfaces__msg__ParameterType__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__msg__ParameterType__init(rcl_interfaces__msg__ParameterType * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__ParameterType__fini(rcl_interfaces__msg__ParameterType * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
rcl_interfaces__msg__ParameterType * rcl_interfaces__msg__ParameterType__create(void);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__ParameterType__destroy(rcl_interfaces__msg__ParameterType * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__msg__ParameterType__Sequence__init(
  rcl_interfaces__msg__ParameterType__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__ParameterType__Sequence__fini(
  rcl_interfaces__msg__ParameterType__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // RCL_INTERFACES__MSG__PARAMETERTYPE_H_
