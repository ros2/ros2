// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/msg/IntegerRange type

#ifndef RCL_INTERFACES__MSG__INTEGERRANGE_H_
#define RCL_INTERFACES__MSG__INTEGERRANGE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "rcl_interfaces/msg/rosidl_generator_c__visibility_control.h"



#ifdef __cplusplus
extern "C" {
#endif



/// Range constraint for integer parameters
typedef struct rcl_interfaces__msg__IntegerRange
{
  int64_t from_value;
  int64_t to_value;
  uint64_t step;
} rcl_interfaces__msg__IntegerRange;

typedef struct rcl_interfaces__msg__IntegerRange__Sequence
{
  rcl_interfaces__msg__IntegerRange * data;
  size_t size;
  size_t capacity;
} rcl_interfaces__msg__IntegerRange__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__msg__IntegerRange__init(rcl_interfaces__msg__IntegerRange * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__IntegerRange__fini(rcl_interfaces__msg__IntegerRange * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
rcl_interfaces__msg__IntegerRange * rcl_interfaces__msg__IntegerRange__create(void);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__IntegerRange__destroy(rcl_interfaces__msg__IntegerRange * msg);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
bool rcl_interfaces__msg__IntegerRange__Sequence__init(
  rcl_interfaces__msg__IntegerRange__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_rcl_interfaces
void rcl_interfaces__msg__IntegerRange__Sequence__fini(
  rcl_interfaces__msg__IntegerRange__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // RCL_INTERFACES__MSG__INTEGERRANGE_H_
