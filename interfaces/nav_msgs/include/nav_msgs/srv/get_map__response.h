// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// nav_msgs/srv/GetMap_Response service type

#ifndef NAV_MSGS__SRV__GETMAP_RESPONSE_H_
#define NAV_MSGS__SRV__GETMAP_RESPONSE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "nav_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "nav_msgs/msg/occupancy_grid.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct nav_msgs__srv__GetMap_Response
{
  nav_msgs__msg__OccupancyGrid map;
} nav_msgs__srv__GetMap_Response;

typedef struct nav_msgs__srv__GetMap_Response__Sequence
{
  nav_msgs__srv__GetMap_Response * data;
  size_t size;
  size_t capacity;
} nav_msgs__srv__GetMap_Response__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
bool nav_msgs__srv__GetMap_Response__init(nav_msgs__srv__GetMap_Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
void nav_msgs__srv__GetMap_Response__fini(nav_msgs__srv__GetMap_Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
nav_msgs__srv__GetMap_Response * nav_msgs__srv__GetMap_Response__create(void);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
void nav_msgs__srv__GetMap_Response__destroy(nav_msgs__srv__GetMap_Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
bool nav_msgs__srv__GetMap_Response__Sequence__init(
  nav_msgs__srv__GetMap_Response__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
void nav_msgs__srv__GetMap_Response__Sequence__fini(
  nav_msgs__srv__GetMap_Response__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // NAV_MSGS__SRV__GETMAP_RESPONSE_H_
