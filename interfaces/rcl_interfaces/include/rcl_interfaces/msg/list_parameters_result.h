// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/msg/ListParametersResult type

#ifndef RCL_INTERFACES__MSG__LISTPARAMETERSRESULT_H_
#define RCL_INTERFACES__MSG__LISTPARAMETERSRESULT_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "rcl_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "rosidl_runtime_c/string.h"

#ifdef __cplusplus
extern "C" {
#endif



/// Result of listing parameters
typedef struct rcl_interfaces__msg__ListParametersResult
{
  rosidl_runtime_c__String__Sequence names;
  rosidl_runtime_c__String__Sequence prefixes;
} rcl_interfaces__msg__ListParametersResult;

typedef struct rcl_interfaces__msg__ListParametersResult__Sequence
{
  rcl_interfaces__msg__ListParametersResult * data;
  size_t size;
  size_t capacity;
} rcl_interfaces__msg__ListParametersResult__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__msg__ListParametersResult__init(rcl_interfaces__msg__ListParametersResult * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__ListParametersResult__fini(rcl_interfaces__msg__ListParametersResult * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
rcl_interfaces__msg__ListParametersResult * rcl_interfaces__msg__ListParametersResult__create(void);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__ListParametersResult__destroy(rcl_interfaces__msg__ListParametersResult * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__msg__ListParametersResult__Sequence__init(
  rcl_interfaces__msg__ListParametersResult__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__ListParametersResult__Sequence__fini(
  rcl_interfaces__msg__ListParametersResult__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // RCL_INTERFACES__MSG__LISTPARAMETERSRESULT_H_
