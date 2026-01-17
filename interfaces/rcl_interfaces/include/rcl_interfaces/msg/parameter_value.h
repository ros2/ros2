// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/msg/ParameterValue type

#ifndef RCL_INTERFACES__MSG__PARAMETERVALUE_H_
#define RCL_INTERFACES__MSG__PARAMETERVALUE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "rcl_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/primitives_sequence.h"

#ifdef __cplusplus
extern "C" {
#endif



/// Parameter value with type discriminator
typedef struct rcl_interfaces__msg__ParameterValue
{
  uint8_t type;
  bool bool_value;
  int64_t integer_value;
  double double_value;
  rosidl_runtime_c__String string_value;
  rosidl_runtime_c__octet__Sequence byte_array_value;
  rosidl_runtime_c__boolean__Sequence bool_array_value;
  rosidl_runtime_c__int64__Sequence integer_array_value;
  rosidl_runtime_c__double__Sequence double_array_value;
  rosidl_runtime_c__String__Sequence string_array_value;
} rcl_interfaces__msg__ParameterValue;

typedef struct rcl_interfaces__msg__ParameterValue__Sequence
{
  rcl_interfaces__msg__ParameterValue * data;
  size_t size;
  size_t capacity;
} rcl_interfaces__msg__ParameterValue__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__msg__ParameterValue__init(rcl_interfaces__msg__ParameterValue * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__ParameterValue__fini(rcl_interfaces__msg__ParameterValue * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
rcl_interfaces__msg__ParameterValue * rcl_interfaces__msg__ParameterValue__create(void);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__ParameterValue__destroy(rcl_interfaces__msg__ParameterValue * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__msg__ParameterValue__Sequence__init(
  rcl_interfaces__msg__ParameterValue__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__ParameterValue__Sequence__fini(
  rcl_interfaces__msg__ParameterValue__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // RCL_INTERFACES__MSG__PARAMETERVALUE_H_
