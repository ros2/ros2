// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// action_msgs/msg/GoalInfo message type

#ifndef ACTION_MSGS__MSG__GOALINFO_H_
#define ACTION_MSGS__MSG__GOALINFO_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "action_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "builtin_interfaces/msg/time.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct action_msgs__msg__GoalInfo
{
  uint8_t goal_id[16];
  builtin_interfaces__msg__Time stamp;
} action_msgs__msg__GoalInfo;

typedef struct action_msgs__msg__GoalInfo__Sequence
{
  action_msgs__msg__GoalInfo * data;
  size_t size;
  size_t capacity;
} action_msgs__msg__GoalInfo__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
bool action_msgs__msg__GoalInfo__init(action_msgs__msg__GoalInfo * msg);

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
void action_msgs__msg__GoalInfo__fini(action_msgs__msg__GoalInfo * msg);

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
action_msgs__msg__GoalInfo * action_msgs__msg__GoalInfo__create(void);

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
void action_msgs__msg__GoalInfo__destroy(action_msgs__msg__GoalInfo * msg);

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
bool action_msgs__msg__GoalInfo__Sequence__init(
  action_msgs__msg__GoalInfo__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_action_msgs
void action_msgs__msg__GoalInfo__Sequence__fini(
  action_msgs__msg__GoalInfo__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // ACTION_MSGS__MSG__GOALINFO_H_
