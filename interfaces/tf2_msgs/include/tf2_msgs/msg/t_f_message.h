// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// tf2_msgs/msg/TFMessage type

#ifndef TF2_MSGS__MSG__TFMESSAGE_H_
#define TF2_MSGS__MSG__TFMESSAGE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "tf2_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "geometry_msgs/msg/transform_stamped.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tf2_msgs__msg__TFMessage
{
  geometry_msgs__msg__TransformStamped__Sequence transforms;
} tf2_msgs__msg__TFMessage;

typedef struct tf2_msgs__msg__TFMessage__Sequence
{
  tf2_msgs__msg__TFMessage * data;
  size_t size;
  size_t capacity;
} tf2_msgs__msg__TFMessage__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
bool tf2_msgs__msg__TFMessage__init(tf2_msgs__msg__TFMessage * msg);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
void tf2_msgs__msg__TFMessage__fini(tf2_msgs__msg__TFMessage * msg);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
tf2_msgs__msg__TFMessage * tf2_msgs__msg__TFMessage__create(void);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
void tf2_msgs__msg__TFMessage__destroy(tf2_msgs__msg__TFMessage * msg);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
bool tf2_msgs__msg__TFMessage__Sequence__init(
  tf2_msgs__msg__TFMessage__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
void tf2_msgs__msg__TFMessage__Sequence__fini(
  tf2_msgs__msg__TFMessage__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // TF2_MSGS__MSG__TFMESSAGE_H_
