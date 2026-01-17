// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// nav_msgs/srv/LoadMap_Response service type

#ifndef NAV_MSGS__SRV__LOADMAP_RESPONSE_H_
#define NAV_MSGS__SRV__LOADMAP_RESPONSE_H_

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

// Constants
#define NAV_MSGS__SRV__LoadMap_Response_RESULT_SUCCESS 0
#define NAV_MSGS__SRV__LoadMap_Response_RESULT_MAP_DOES_NOT_EXIST 1
#define NAV_MSGS__SRV__LoadMap_Response_RESULT_INVALID_MAP_DATA 2
#define NAV_MSGS__SRV__LoadMap_Response_RESULT_INVALID_MAP_METADATA 3
#define NAV_MSGS__SRV__LoadMap_Response_RESULT_UNDEFINED_FAILURE 255

typedef struct nav_msgs__srv__LoadMap_Response
{
  nav_msgs__msg__OccupancyGrid map;
  uint8_t result;
} nav_msgs__srv__LoadMap_Response;

typedef struct nav_msgs__srv__LoadMap_Response__Sequence
{
  nav_msgs__srv__LoadMap_Response * data;
  size_t size;
  size_t capacity;
} nav_msgs__srv__LoadMap_Response__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
bool nav_msgs__srv__LoadMap_Response__init(nav_msgs__srv__LoadMap_Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
void nav_msgs__srv__LoadMap_Response__fini(nav_msgs__srv__LoadMap_Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
nav_msgs__srv__LoadMap_Response * nav_msgs__srv__LoadMap_Response__create(void);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
void nav_msgs__srv__LoadMap_Response__destroy(nav_msgs__srv__LoadMap_Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
bool nav_msgs__srv__LoadMap_Response__Sequence__init(
  nav_msgs__srv__LoadMap_Response__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
void nav_msgs__srv__LoadMap_Response__Sequence__fini(
  nav_msgs__srv__LoadMap_Response__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // NAV_MSGS__SRV__LOADMAP_RESPONSE_H_
