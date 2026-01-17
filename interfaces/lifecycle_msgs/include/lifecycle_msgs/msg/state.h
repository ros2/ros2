// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// lifecycle_msgs/msg/State type

#ifndef LIFECYCLE_MSGS__MSG__STATE_H_
#define LIFECYCLE_MSGS__MSG__STATE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "lifecycle_msgs/msg/rosidl_generator_c__visibility_control.h"

#ifdef __cplusplus
extern "C" {
#endif

// Primary states
#define LIFECYCLE_MSGS__MSG__STATE__PRIMARY_STATE_UNKNOWN ((uint8_t)0)
#define LIFECYCLE_MSGS__MSG__STATE__PRIMARY_STATE_UNCONFIGURED ((uint8_t)1)
#define LIFECYCLE_MSGS__MSG__STATE__PRIMARY_STATE_INACTIVE ((uint8_t)2)
#define LIFECYCLE_MSGS__MSG__STATE__PRIMARY_STATE_ACTIVE ((uint8_t)3)
#define LIFECYCLE_MSGS__MSG__STATE__PRIMARY_STATE_FINALIZED ((uint8_t)4)

// Transition states
#define LIFECYCLE_MSGS__MSG__STATE__TRANSITION_STATE_CONFIGURING ((uint8_t)10)
#define LIFECYCLE_MSGS__MSG__STATE__TRANSITION_STATE_CLEANINGUP ((uint8_t)11)
#define LIFECYCLE_MSGS__MSG__STATE__TRANSITION_STATE_SHUTTINGDOWN ((uint8_t)12)
#define LIFECYCLE_MSGS__MSG__STATE__TRANSITION_STATE_ACTIVATING ((uint8_t)13)
#define LIFECYCLE_MSGS__MSG__STATE__TRANSITION_STATE_DEACTIVATING ((uint8_t)14)
#define LIFECYCLE_MSGS__MSG__STATE__TRANSITION_STATE_ERRORPROCESSING ((uint8_t)15)

/// Lifecycle state with id and label
typedef struct lifecycle_msgs__msg__State
{
  uint8_t id;
  rosidl_runtime_c__String label;
} lifecycle_msgs__msg__State;

typedef struct lifecycle_msgs__msg__State__Sequence
{
  lifecycle_msgs__msg__State * data;
  size_t size;
  size_t capacity;
} lifecycle_msgs__msg__State__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
bool lifecycle_msgs__msg__State__init(lifecycle_msgs__msg__State * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__msg__State__fini(lifecycle_msgs__msg__State * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
lifecycle_msgs__msg__State * lifecycle_msgs__msg__State__create(void);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__msg__State__destroy(lifecycle_msgs__msg__State * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
bool lifecycle_msgs__msg__State__Sequence__init(
  lifecycle_msgs__msg__State__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__msg__State__Sequence__fini(
  lifecycle_msgs__msg__State__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // LIFECYCLE_MSGS__MSG__STATE_H_
