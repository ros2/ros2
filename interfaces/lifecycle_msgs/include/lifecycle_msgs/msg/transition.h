// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// lifecycle_msgs/msg/Transition type

#ifndef LIFECYCLE_MSGS__MSG__TRANSITION_H_
#define LIFECYCLE_MSGS__MSG__TRANSITION_H_

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

// Transition constants
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_CREATE ((uint8_t)0)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_CONFIGURE ((uint8_t)1)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_CLEANUP ((uint8_t)2)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ACTIVATE ((uint8_t)3)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_DEACTIVATE ((uint8_t)4)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_UNCONFIGURED_SHUTDOWN ((uint8_t)5)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_INACTIVE_SHUTDOWN ((uint8_t)6)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ACTIVE_SHUTDOWN ((uint8_t)7)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_DESTROY ((uint8_t)8)

// Callback return codes
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_CALLBACK_SUCCESS ((uint8_t)97)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_CALLBACK_FAILURE ((uint8_t)98)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_CALLBACK_ERROR ((uint8_t)99)

// On error transitions
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_CONFIGURE_SUCCESS ((uint8_t)10)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_CONFIGURE_FAILURE ((uint8_t)11)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_CONFIGURE_ERROR ((uint8_t)12)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_CLEANUP_SUCCESS ((uint8_t)20)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_CLEANUP_FAILURE ((uint8_t)21)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_CLEANUP_ERROR ((uint8_t)22)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_ACTIVATE_SUCCESS ((uint8_t)30)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_ACTIVATE_FAILURE ((uint8_t)31)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_ACTIVATE_ERROR ((uint8_t)32)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_DEACTIVATE_SUCCESS ((uint8_t)40)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_DEACTIVATE_FAILURE ((uint8_t)41)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_DEACTIVATE_ERROR ((uint8_t)42)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_SHUTDOWN_SUCCESS ((uint8_t)50)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_SHUTDOWN_FAILURE ((uint8_t)51)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_SHUTDOWN_ERROR ((uint8_t)52)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_ERROR_SUCCESS ((uint8_t)60)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_ERROR_FAILURE ((uint8_t)61)
#define LIFECYCLE_MSGS__MSG__TRANSITION__TRANSITION_ON_ERROR_ERROR ((uint8_t)62)

/// Lifecycle transition with id and label
typedef struct lifecycle_msgs__msg__Transition
{
  uint8_t id;
  rosidl_runtime_c__String label;
} lifecycle_msgs__msg__Transition;

typedef struct lifecycle_msgs__msg__Transition__Sequence
{
  lifecycle_msgs__msg__Transition * data;
  size_t size;
  size_t capacity;
} lifecycle_msgs__msg__Transition__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
bool lifecycle_msgs__msg__Transition__init(lifecycle_msgs__msg__Transition * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__msg__Transition__fini(lifecycle_msgs__msg__Transition * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
lifecycle_msgs__msg__Transition * lifecycle_msgs__msg__Transition__create(void);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__msg__Transition__destroy(lifecycle_msgs__msg__Transition * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
bool lifecycle_msgs__msg__Transition__Sequence__init(
  lifecycle_msgs__msg__Transition__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__msg__Transition__Sequence__fini(
  lifecycle_msgs__msg__Transition__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // LIFECYCLE_MSGS__MSG__TRANSITION_H_
