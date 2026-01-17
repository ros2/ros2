// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/msg/FloatingPointRange type

#ifndef RCL_INTERFACES__MSG__FLOATINGPOINTRANGE_H_
#define RCL_INTERFACES__MSG__FLOATINGPOINTRANGE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "rcl_interfaces/msg/rosidl_generator_c__visibility_control.h"



#ifdef __cplusplus
extern "C" {
#endif



/// Range constraint for floating point parameters
typedef struct rcl_interfaces__msg__FloatingPointRange
{
  double from_value;
  double to_value;
  double step;
} rcl_interfaces__msg__FloatingPointRange;

typedef struct rcl_interfaces__msg__FloatingPointRange__Sequence
{
  rcl_interfaces__msg__FloatingPointRange * data;
  size_t size;
  size_t capacity;
} rcl_interfaces__msg__FloatingPointRange__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__msg__FloatingPointRange__init(rcl_interfaces__msg__FloatingPointRange * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__FloatingPointRange__fini(rcl_interfaces__msg__FloatingPointRange * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
rcl_interfaces__msg__FloatingPointRange * rcl_interfaces__msg__FloatingPointRange__create(void);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__FloatingPointRange__destroy(rcl_interfaces__msg__FloatingPointRange * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__msg__FloatingPointRange__Sequence__init(
  rcl_interfaces__msg__FloatingPointRange__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__FloatingPointRange__Sequence__fini(
  rcl_interfaces__msg__FloatingPointRange__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // RCL_INTERFACES__MSG__FLOATINGPOINTRANGE_H_
