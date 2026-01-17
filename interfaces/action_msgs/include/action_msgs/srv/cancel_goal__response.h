// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// action_msgs/srv/CancelGoal_Response service type

#ifndef ACTION_MSGS__SRV__CANCELGOAL_RESPONSE_H_
#define ACTION_MSGS__SRV__CANCELGOAL_RESPONSE_H_

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

// Constants
#define ACTION_MSGS__SRV__CancelGoal_Response_ERROR_NONE 0
#define ACTION_MSGS__SRV__CancelGoal_Response_ERROR_REJECTED 1
#define ACTION_MSGS__SRV__CancelGoal_Response_ERROR_UNKNOWN_GOAL_ID 2
#define ACTION_MSGS__SRV__CancelGoal_Response_ERROR_GOAL_TERMINATED 3

typedef struct action_msgs__srv__CancelGoal_Response
{
  int8_t return_code;
  action_msgs__msg__GoalInfo__Sequence goals_canceling;
} action_msgs__srv__CancelGoal_Response;

typedef struct action_msgs__srv__CancelGoal_Response__Sequence
{
  action_msgs__srv__CancelGoal_Response * data;
  size_t size;
  size_t capacity;
} action_msgs__srv__CancelGoal_Response__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
bool action_msgs__srv__CancelGoal_Response__init(action_msgs__srv__CancelGoal_Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
void action_msgs__srv__CancelGoal_Response__fini(action_msgs__srv__CancelGoal_Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
action_msgs__srv__CancelGoal_Response * action_msgs__srv__CancelGoal_Response__create(void);

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
void action_msgs__srv__CancelGoal_Response__destroy(action_msgs__srv__CancelGoal_Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
bool action_msgs__srv__CancelGoal_Response__Sequence__init(
  action_msgs__srv__CancelGoal_Response__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
void action_msgs__srv__CancelGoal_Response__Sequence__fini(
  action_msgs__srv__CancelGoal_Response__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // ACTION_MSGS__SRV__CANCELGOAL_RESPONSE_H_
