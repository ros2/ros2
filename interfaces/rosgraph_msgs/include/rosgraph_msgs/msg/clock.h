// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rosgraph_msgs/msg/Clock type

#ifndef ROSGRAPH_MSGS__MSG__CLOCK_H_
#define ROSGRAPH_MSGS__MSG__CLOCK_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "rosgraph_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "builtin_interfaces/msg/time.h"

#ifdef __cplusplus
extern "C" {
#endif

/// Clock message for simulation time
/// Published on /clock topic when use_sim_time is enabled
typedef struct rosgraph_msgs__msg__Clock
{
  /// The current time
  builtin_interfaces__msg__Time clock;
} rosgraph_msgs__msg__Clock;

typedef struct rosgraph_msgs__msg__Clock__Sequence
{
  rosgraph_msgs__msg__Clock * data;
  size_t size;
  size_t capacity;
} rosgraph_msgs__msg__Clock__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_rosgraph_msgs
bool rosgraph_msgs__msg__Clock__init(rosgraph_msgs__msg__Clock * msg);

ROSIDL_GENERATOR_C_PUBLIC_rosgraph_msgs
void rosgraph_msgs__msg__Clock__fini(rosgraph_msgs__msg__Clock * msg);

ROSIDL_GENERATOR_C_PUBLIC_rosgraph_msgs
rosgraph_msgs__msg__Clock * rosgraph_msgs__msg__Clock__create(void);

ROSIDL_GENERATOR_C_PUBLIC_rosgraph_msgs
void rosgraph_msgs__msg__Clock__destroy(rosgraph_msgs__msg__Clock * msg);

ROSIDL_GENERATOR_C_PUBLIC_rosgraph_msgs
bool rosgraph_msgs__msg__Clock__Sequence__init(
  rosgraph_msgs__msg__Clock__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_rosgraph_msgs
void rosgraph_msgs__msg__Clock__Sequence__fini(
  rosgraph_msgs__msg__Clock__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // ROSGRAPH_MSGS__MSG__CLOCK_H_
