// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// nav_msgs/msg/OccupancyGrid message type

#ifndef NAV_MSGS__MSG__OCCUPANCYGRID_H_
#define NAV_MSGS__MSG__OCCUPANCYGRID_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "nav_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "std_msgs/msg/header.h"
#include "nav_msgs/msg/map_meta_data.h"
#include "rosidl_runtime_c/primitives_sequence.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct nav_msgs__msg__OccupancyGrid
{
  std_msgs__msg__Header header;
  nav_msgs__msg__MapMetaData info;
  rosidl_runtime_c__int8__Sequence data;
} nav_msgs__msg__OccupancyGrid;

typedef struct nav_msgs__msg__OccupancyGrid__Sequence
{
  nav_msgs__msg__OccupancyGrid * data;
  size_t size;
  size_t capacity;
} nav_msgs__msg__OccupancyGrid__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
bool nav_msgs__msg__OccupancyGrid__init(nav_msgs__msg__OccupancyGrid * msg);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
void nav_msgs__msg__OccupancyGrid__fini(nav_msgs__msg__OccupancyGrid * msg);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
nav_msgs__msg__OccupancyGrid * nav_msgs__msg__OccupancyGrid__create(void);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
void nav_msgs__msg__OccupancyGrid__destroy(nav_msgs__msg__OccupancyGrid * msg);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
bool nav_msgs__msg__OccupancyGrid__Sequence__init(
  nav_msgs__msg__OccupancyGrid__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
void nav_msgs__msg__OccupancyGrid__Sequence__fini(
  nav_msgs__msg__OccupancyGrid__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // NAV_MSGS__MSG__OCCUPANCYGRID_H_
