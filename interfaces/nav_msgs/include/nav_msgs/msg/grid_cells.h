// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// nav_msgs/msg/GridCells message type

#ifndef NAV_MSGS__MSG__GRIDCELLS_H_
#define NAV_MSGS__MSG__GRIDCELLS_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "nav_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "std_msgs/msg/header.h"
#include "geometry_msgs/msg/point.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct nav_msgs__msg__GridCells
{
  std_msgs__msg__Header header;
  float cell_width;
  float cell_height;
  geometry_msgs__msg__Point__Sequence cells;
} nav_msgs__msg__GridCells;

typedef struct nav_msgs__msg__GridCells__Sequence
{
  nav_msgs__msg__GridCells * data;
  size_t size;
  size_t capacity;
} nav_msgs__msg__GridCells__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
bool nav_msgs__msg__GridCells__init(nav_msgs__msg__GridCells * msg);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
void nav_msgs__msg__GridCells__fini(nav_msgs__msg__GridCells * msg);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
nav_msgs__msg__GridCells * nav_msgs__msg__GridCells__create(void);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
void nav_msgs__msg__GridCells__destroy(nav_msgs__msg__GridCells * msg);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
bool nav_msgs__msg__GridCells__Sequence__init(
  nav_msgs__msg__GridCells__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
void nav_msgs__msg__GridCells__Sequence__fini(
  nav_msgs__msg__GridCells__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // NAV_MSGS__MSG__GRIDCELLS_H_
