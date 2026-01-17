// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// action_msgs/msg/GoalStatus message type

#ifndef ACTION_MSGS__MSG__GOALSTATUS_H_
#define ACTION_MSGS__MSG__GOALSTATUS_H_

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
#define ACTION_MSGS__MSG__GoalStatus_STATUS_UNKNOWN 0
#define ACTION_MSGS__MSG__GoalStatus_STATUS_ACCEPTED 1
#define ACTION_MSGS__MSG__GoalStatus_STATUS_EXECUTING 2
#define ACTION_MSGS__MSG__GoalStatus_STATUS_CANCELING 3
#define ACTION_MSGS__MSG__GoalStatus_STATUS_SUCCEEDED 4
#define ACTION_MSGS__MSG__GoalStatus_STATUS_CANCELED 5
#define ACTION_MSGS__MSG__GoalStatus_STATUS_ABORTED 6

typedef struct action_msgs__msg__GoalStatus
{
  action_msgs__msg__GoalInfo goal_info;
  int8_t status;
} action_msgs__msg__GoalStatus;

typedef struct action_msgs__msg__GoalStatus__Sequence
{
  action_msgs__msg__GoalStatus * data;
  size_t size;
  size_t capacity;
} action_msgs__msg__GoalStatus__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
bool action_msgs__msg__GoalStatus__init(action_msgs__msg__GoalStatus * msg);

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
void action_msgs__msg__GoalStatus__fini(action_msgs__msg__GoalStatus * msg);

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
action_msgs__msg__GoalStatus * action_msgs__msg__GoalStatus__create(void);

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
void action_msgs__msg__GoalStatus__destroy(action_msgs__msg__GoalStatus * msg);

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
bool action_msgs__msg__GoalStatus__Sequence__init(
  action_msgs__msg__GoalStatus__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
void action_msgs__msg__GoalStatus__Sequence__fini(
  action_msgs__msg__GoalStatus__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // ACTION_MSGS__MSG__GOALSTATUS_H_
