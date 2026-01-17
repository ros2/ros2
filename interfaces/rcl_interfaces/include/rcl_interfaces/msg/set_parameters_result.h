// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/msg/SetParametersResult type

#ifndef RCL_INTERFACES__MSG__SETPARAMETERSRESULT_H_
#define RCL_INTERFACES__MSG__SETPARAMETERSRESULT_H_

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



/// Result of setting a parameter
typedef struct rcl_interfaces__msg__SetParametersResult
{
  bool successful;
  rosidl_runtime_c__String reason;
} rcl_interfaces__msg__SetParametersResult;

typedef struct rcl_interfaces__msg__SetParametersResult__Sequence
{
  rcl_interfaces__msg__SetParametersResult * data;
  size_t size;
  size_t capacity;
} rcl_interfaces__msg__SetParametersResult__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__msg__SetParametersResult__init(rcl_interfaces__msg__SetParametersResult * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__SetParametersResult__fini(rcl_interfaces__msg__SetParametersResult * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
rcl_interfaces__msg__SetParametersResult * rcl_interfaces__msg__SetParametersResult__create(void);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__SetParametersResult__destroy(rcl_interfaces__msg__SetParametersResult * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__msg__SetParametersResult__Sequence__init(
  rcl_interfaces__msg__SetParametersResult__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__SetParametersResult__Sequence__fini(
  rcl_interfaces__msg__SetParametersResult__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // RCL_INTERFACES__MSG__SETPARAMETERSRESULT_H_
