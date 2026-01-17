// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// lifecycle_msgs/msg/TransitionEvent type

#ifndef LIFECYCLE_MSGS__MSG__TRANSITION_EVENT_H_
#define LIFECYCLE_MSGS__MSG__TRANSITION_EVENT_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "lifecycle_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "builtin_interfaces/msg/time.h"
#include "lifecycle_msgs/msg/state.h"
#include "lifecycle_msgs/msg/transition.h"

#ifdef __cplusplus
extern "C" {
#endif

/// Event when a lifecycle transition occurs
typedef struct lifecycle_msgs__msg__TransitionEvent
{
  builtin_interfaces__msg__Time timestamp;
  lifecycle_msgs__msg__Transition transition;
  lifecycle_msgs__msg__State start_state;
  lifecycle_msgs__msg__State goal_state;
} lifecycle_msgs__msg__TransitionEvent;

typedef struct lifecycle_msgs__msg__TransitionEvent__Sequence
{
  lifecycle_msgs__msg__TransitionEvent * data;
  size_t size;
  size_t capacity;
} lifecycle_msgs__msg__TransitionEvent__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
bool lifecycle_msgs__msg__TransitionEvent__init(lifecycle_msgs__msg__TransitionEvent * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__msg__TransitionEvent__fini(lifecycle_msgs__msg__TransitionEvent * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
lifecycle_msgs__msg__TransitionEvent * lifecycle_msgs__msg__TransitionEvent__create(void);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__msg__TransitionEvent__destroy(lifecycle_msgs__msg__TransitionEvent * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
bool lifecycle_msgs__msg__TransitionEvent__Sequence__init(
  lifecycle_msgs__msg__TransitionEvent__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__msg__TransitionEvent__Sequence__fini(
  lifecycle_msgs__msg__TransitionEvent__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // LIFECYCLE_MSGS__MSG__TRANSITION_EVENT_H_
