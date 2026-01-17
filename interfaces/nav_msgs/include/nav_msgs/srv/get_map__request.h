// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// nav_msgs/srv/GetMap_Request service type

#ifndef NAV_MSGS__SRV__GETMAP_REQUEST_H_
#define NAV_MSGS__SRV__GETMAP_REQUEST_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "nav_msgs/msg/rosidl_generator_c__visibility_control.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct nav_msgs__srv__GetMap_Request
{
  uint8_t structure_needs_at_least_one_member;
} nav_msgs__srv__GetMap_Request;

typedef struct nav_msgs__srv__GetMap_Request__Sequence
{
  nav_msgs__srv__GetMap_Request * data;
  size_t size;
  size_t capacity;
} nav_msgs__srv__GetMap_Request__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
bool nav_msgs__srv__GetMap_Request__init(nav_msgs__srv__GetMap_Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
void nav_msgs__srv__GetMap_Request__fini(nav_msgs__srv__GetMap_Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
nav_msgs__srv__GetMap_Request * nav_msgs__srv__GetMap_Request__create(void);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
void nav_msgs__srv__GetMap_Request__destroy(nav_msgs__srv__GetMap_Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
bool nav_msgs__srv__GetMap_Request__Sequence__init(
  nav_msgs__srv__GetMap_Request__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_nav_msgs
void nav_msgs__srv__GetMap_Request__Sequence__fini(
  nav_msgs__srv__GetMap_Request__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // NAV_MSGS__SRV__GETMAP_REQUEST_H_
