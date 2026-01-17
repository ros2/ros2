// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// tf2_msgs/action/LookupTransform_Goal type

#ifndef TF2_MSGS__ACTION__LOOKUPTRANSFORM_GOAL_H_
#define TF2_MSGS__ACTION__LOOKUPTRANSFORM_GOAL_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "tf2_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "rosidl_runtime_c/string.h"
#include "builtin_interfaces/msg/time.h"
#include "builtin_interfaces/msg/duration.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tf2_msgs__action__LookupTransform_Goal
{
  rosidl_runtime_c__String target_frame;
  rosidl_runtime_c__String source_frame;
  builtin_interfaces__msg__Time source_time;
  builtin_interfaces__msg__Duration timeout;
  builtin_interfaces__msg__Time target_time;
  rosidl_runtime_c__String fixed_frame;
  bool advanced;
} tf2_msgs__action__LookupTransform_Goal;

typedef struct tf2_msgs__action__LookupTransform_Goal__Sequence
{
  tf2_msgs__action__LookupTransform_Goal * data;
  size_t size;
  size_t capacity;
} tf2_msgs__action__LookupTransform_Goal__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
bool tf2_msgs__action__LookupTransform_Goal__init(tf2_msgs__action__LookupTransform_Goal * msg);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
void tf2_msgs__action__LookupTransform_Goal__fini(tf2_msgs__action__LookupTransform_Goal * msg);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
tf2_msgs__action__LookupTransform_Goal * tf2_msgs__action__LookupTransform_Goal__create(void);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
void tf2_msgs__action__LookupTransform_Goal__destroy(tf2_msgs__action__LookupTransform_Goal * msg);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
bool tf2_msgs__action__LookupTransform_Goal__Sequence__init(
  tf2_msgs__action__LookupTransform_Goal__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
void tf2_msgs__action__LookupTransform_Goal__Sequence__fini(
  tf2_msgs__action__LookupTransform_Goal__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // TF2_MSGS__ACTION__LOOKUPTRANSFORM_GOAL_H_
