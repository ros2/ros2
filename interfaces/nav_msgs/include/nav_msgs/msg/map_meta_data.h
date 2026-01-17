// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// nav_msgs/msg/MapMetaData message type

#ifndef NAV_MSGS__MSG__MAPMETADATA_H_
#define NAV_MSGS__MSG__MAPMETADATA_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "nav_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "builtin_interfaces/msg/time.h"
#include "geometry_msgs/msg/pose.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct nav_msgs__msg__MapMetaData
{
  builtin_interfaces__msg__Time map_load_time;
  float resolution;
  uint32_t width;
  uint32_t height;
  geometry_msgs__msg__Pose origin;
} nav_msgs__msg__MapMetaData;

typedef struct nav_msgs__msg__MapMetaData__Sequence
{
  nav_msgs__msg__MapMetaData * data;
  size_t size;
  size_t capacity;
} nav_msgs__msg__MapMetaData__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
bool nav_msgs__msg__MapMetaData__init(nav_msgs__msg__MapMetaData * msg);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
void nav_msgs__msg__MapMetaData__fini(nav_msgs__msg__MapMetaData * msg);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
nav_msgs__msg__MapMetaData * nav_msgs__msg__MapMetaData__create(void);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
void nav_msgs__msg__MapMetaData__destroy(nav_msgs__msg__MapMetaData * msg);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
bool nav_msgs__msg__MapMetaData__Sequence__init(
  nav_msgs__msg__MapMetaData__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
void nav_msgs__msg__MapMetaData__Sequence__fini(
  nav_msgs__msg__MapMetaData__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // NAV_MSGS__MSG__MAPMETADATA_H_
