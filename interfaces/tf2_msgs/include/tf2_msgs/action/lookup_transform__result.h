// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// tf2_msgs/action/LookupTransform_Result type

#ifndef TF2_MSGS__ACTION__LOOKUPTRANSFORM_RESULT_H_
#define TF2_MSGS__ACTION__LOOKUPTRANSFORM_RESULT_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "tf2_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "geometry_msgs/msg/transform_stamped.h"
#include "tf2_msgs/msg/tf2_error.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tf2_msgs__action__LookupTransform_Result
{
  geometry_msgs__msg__TransformStamped transform;
  tf2_msgs__msg__TF2Error error;
} tf2_msgs__action__LookupTransform_Result;

typedef struct tf2_msgs__action__LookupTransform_Result__Sequence
{
  tf2_msgs__action__LookupTransform_Result * data;
  size_t size;
  size_t capacity;
} tf2_msgs__action__LookupTransform_Result__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
bool tf2_msgs__action__LookupTransform_Result__init(tf2_msgs__action__LookupTransform_Result * msg);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
void tf2_msgs__action__LookupTransform_Result__fini(tf2_msgs__action__LookupTransform_Result * msg);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
tf2_msgs__action__LookupTransform_Result * tf2_msgs__action__LookupTransform_Result__create(void);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
void tf2_msgs__action__LookupTransform_Result__destroy(tf2_msgs__action__LookupTransform_Result * msg);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
bool tf2_msgs__action__LookupTransform_Result__Sequence__init(
  tf2_msgs__action__LookupTransform_Result__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
void tf2_msgs__action__LookupTransform_Result__Sequence__fini(
  tf2_msgs__action__LookupTransform_Result__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // TF2_MSGS__ACTION__LOOKUPTRANSFORM_RESULT_H_
