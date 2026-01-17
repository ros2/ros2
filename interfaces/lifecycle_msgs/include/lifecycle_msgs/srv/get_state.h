// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// lifecycle_msgs/srv/GetState type

#ifndef LIFECYCLE_MSGS__SRV__GET_STATE_H_
#define LIFECYCLE_MSGS__SRV__GET_STATE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "lifecycle_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "lifecycle_msgs/msg/state.h"

#ifdef __cplusplus
extern "C" {
#endif

// Request (empty)
typedef struct lifecycle_msgs__srv__GetState__Request
{
  uint8_t structure_needs_at_least_one_member;
} lifecycle_msgs__srv__GetState__Request;

typedef struct lifecycle_msgs__srv__GetState__Request__Sequence
{
  lifecycle_msgs__srv__GetState__Request * data;
  size_t size;
  size_t capacity;
} lifecycle_msgs__srv__GetState__Request__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
bool lifecycle_msgs__srv__GetState__Request__init(lifecycle_msgs__srv__GetState__Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__srv__GetState__Request__fini(lifecycle_msgs__srv__GetState__Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
lifecycle_msgs__srv__GetState__Request * lifecycle_msgs__srv__GetState__Request__create(void);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__srv__GetState__Request__destroy(lifecycle_msgs__srv__GetState__Request * msg);

// Response
typedef struct lifecycle_msgs__srv__GetState__Response
{
  lifecycle_msgs__msg__State current_state;
} lifecycle_msgs__srv__GetState__Response;

typedef struct lifecycle_msgs__srv__GetState__Response__Sequence
{
  lifecycle_msgs__srv__GetState__Response * data;
  size_t size;
  size_t capacity;
} lifecycle_msgs__srv__GetState__Response__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
bool lifecycle_msgs__srv__GetState__Response__init(lifecycle_msgs__srv__GetState__Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__srv__GetState__Response__fini(lifecycle_msgs__srv__GetState__Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
lifecycle_msgs__srv__GetState__Response * lifecycle_msgs__srv__GetState__Response__create(void);

ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
void lifecycle_msgs__srv__GetState__Response__destroy(lifecycle_msgs__srv__GetState__Response * msg);

#ifdef __cplusplus
}
#endif

#endif  // LIFECYCLE_MSGS__SRV__GET_STATE_H_
