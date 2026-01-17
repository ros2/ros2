// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// action_msgs/msg/GoalStatusArray message type

#ifndef ACTION_MSGS__MSG__GOALSTATUSARRAY_H_
#define ACTION_MSGS__MSG__GOALSTATUSARRAY_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "action_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "action_msgs/msg/goal_status.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct action_msgs__msg__GoalStatusArray
{
  action_msgs__msg__GoalStatus__Sequence status_list;
} action_msgs__msg__GoalStatusArray;

typedef struct action_msgs__msg__GoalStatusArray__Sequence
{
  action_msgs__msg__GoalStatusArray * data;
  size_t size;
  size_t capacity;
} action_msgs__msg__GoalStatusArray__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
bool action_msgs__msg__GoalStatusArray__init(action_msgs__msg__GoalStatusArray * msg);

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
void action_msgs__msg__GoalStatusArray__fini(action_msgs__msg__GoalStatusArray * msg);

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
action_msgs__msg__GoalStatusArray * action_msgs__msg__GoalStatusArray__create(void);

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
void action_msgs__msg__GoalStatusArray__destroy(action_msgs__msg__GoalStatusArray * msg);

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
bool action_msgs__msg__GoalStatusArray__Sequence__init(
  action_msgs__msg__GoalStatusArray__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
void action_msgs__msg__GoalStatusArray__Sequence__fini(
  action_msgs__msg__GoalStatusArray__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // ACTION_MSGS__MSG__GOALSTATUSARRAY_H_
