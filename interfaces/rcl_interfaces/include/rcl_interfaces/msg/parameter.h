// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/msg/Parameter type

#ifndef RCL_INTERFACES__MSG__PARAMETER_H_
#define RCL_INTERFACES__MSG__PARAMETER_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "rcl_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "rosidl_runtime_c/string.h"
#include "rcl_interfaces/msg/parameter_value.h"

#ifdef __cplusplus
extern "C" {
#endif



/// Named parameter with value
typedef struct rcl_interfaces__msg__Parameter
{
  rosidl_runtime_c__String name;
  rcl_interfaces__msg__ParameterValue value;
} rcl_interfaces__msg__Parameter;

typedef struct rcl_interfaces__msg__Parameter__Sequence
{
  rcl_interfaces__msg__Parameter * data;
  size_t size;
  size_t capacity;
} rcl_interfaces__msg__Parameter__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__msg__Parameter__init(rcl_interfaces__msg__Parameter * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__Parameter__fini(rcl_interfaces__msg__Parameter * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
rcl_interfaces__msg__Parameter * rcl_interfaces__msg__Parameter__create(void);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__Parameter__destroy(rcl_interfaces__msg__Parameter * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__msg__Parameter__Sequence__init(
  rcl_interfaces__msg__Parameter__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__Parameter__Sequence__fini(
  rcl_interfaces__msg__Parameter__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // RCL_INTERFACES__MSG__PARAMETER_H_
