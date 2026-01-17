// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// action_msgs/srv/CancelGoal_Request service type

#ifndef ACTION_MSGS__SRV__CANCELGOAL_REQUEST_H_
#define ACTION_MSGS__SRV__CANCELGOAL_REQUEST_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "action_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "action_msgs/msg/goal_info.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct action_msgs__srv__CancelGoal_Request
{
  action_msgs__msg__GoalInfo goal_info;
} action_msgs__srv__CancelGoal_Request;

typedef struct action_msgs__srv__CancelGoal_Request__Sequence
{
  action_msgs__srv__CancelGoal_Request * data;
  size_t size;
  size_t capacity;
} action_msgs__srv__CancelGoal_Request__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
bool action_msgs__srv__CancelGoal_Request__init(action_msgs__srv__CancelGoal_Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
void action_msgs__srv__CancelGoal_Request__fini(action_msgs__srv__CancelGoal_Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
action_msgs__srv__CancelGoal_Request * action_msgs__srv__CancelGoal_Request__create(void);

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
void action_msgs__srv__CancelGoal_Request__destroy(action_msgs__srv__CancelGoal_Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
bool action_msgs__srv__CancelGoal_Request__Sequence__init(
  action_msgs__srv__CancelGoal_Request__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
void action_msgs__srv__CancelGoal_Request__Sequence__fini(
  action_msgs__srv__CancelGoal_Request__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // ACTION_MSGS__SRV__CANCELGOAL_REQUEST_H_
