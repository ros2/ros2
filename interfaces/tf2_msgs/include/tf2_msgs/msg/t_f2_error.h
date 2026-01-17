// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// tf2_msgs/msg/TF2Error type

#ifndef TF2_MSGS__MSG__TF2ERROR_H_
#define TF2_MSGS__MSG__TF2ERROR_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "tf2_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "rosidl_runtime_c/string.h"

#ifdef __cplusplus
extern "C" {
#endif

// Constants
#define TF2_MSGS__MSG__TF2Error_NO_ERROR 0
#define TF2_MSGS__MSG__TF2Error_LOOKUP_ERROR 1
#define TF2_MSGS__MSG__TF2Error_CONNECTIVITY_ERROR 2
#define TF2_MSGS__MSG__TF2Error_EXTRAPOLATION_ERROR 3
#define TF2_MSGS__MSG__TF2Error_INVALID_ARGUMENT_ERROR 4
#define TF2_MSGS__MSG__TF2Error_TIMEOUT_ERROR 5
#define TF2_MSGS__MSG__TF2Error_TRANSFORM_ERROR 6

typedef struct tf2_msgs__msg__TF2Error
{
  uint8_t error;
  rosidl_runtime_c__String error_string;
} tf2_msgs__msg__TF2Error;

typedef struct tf2_msgs__msg__TF2Error__Sequence
{
  tf2_msgs__msg__TF2Error * data;
  size_t size;
  size_t capacity;
} tf2_msgs__msg__TF2Error__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
bool tf2_msgs__msg__TF2Error__init(tf2_msgs__msg__TF2Error * msg);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
void tf2_msgs__msg__TF2Error__fini(tf2_msgs__msg__TF2Error * msg);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
tf2_msgs__msg__TF2Error * tf2_msgs__msg__TF2Error__create(void);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
void tf2_msgs__msg__TF2Error__destroy(tf2_msgs__msg__TF2Error * msg);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
bool tf2_msgs__msg__TF2Error__Sequence__init(
  tf2_msgs__msg__TF2Error__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
void tf2_msgs__msg__TF2Error__Sequence__fini(
  tf2_msgs__msg__TF2Error__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // TF2_MSGS__MSG__TF2ERROR_H_
