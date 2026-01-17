// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// nav_msgs/srv/SetMap_Request service type

#ifndef NAV_MSGS__SRV__SETMAP_REQUEST_H_
#define NAV_MSGS__SRV__SETMAP_REQUEST_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "nav_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "nav_msgs/msg/occupancy_grid.h"
#include "geometry_msgs/msg/pose_with_covariance_stamped.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct nav_msgs__srv__SetMap_Request
{
  nav_msgs__msg__OccupancyGrid map;
  geometry_msgs__msg__PoseWithCovarianceStamped initial_pose;
} nav_msgs__srv__SetMap_Request;

typedef struct nav_msgs__srv__SetMap_Request__Sequence
{
  nav_msgs__srv__SetMap_Request * data;
  size_t size;
  size_t capacity;
} nav_msgs__srv__SetMap_Request__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
bool nav_msgs__srv__SetMap_Request__init(nav_msgs__srv__SetMap_Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
void nav_msgs__srv__SetMap_Request__fini(nav_msgs__srv__SetMap_Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
nav_msgs__srv__SetMap_Request * nav_msgs__srv__SetMap_Request__create(void);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
void nav_msgs__srv__SetMap_Request__destroy(nav_msgs__srv__SetMap_Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
bool nav_msgs__srv__SetMap_Request__Sequence__init(
  nav_msgs__srv__SetMap_Request__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
void nav_msgs__srv__SetMap_Request__Sequence__fini(
  nav_msgs__srv__SetMap_Request__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // NAV_MSGS__SRV__SETMAP_REQUEST_H_
