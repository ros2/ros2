// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/JoyFeedbackArray message type

#ifndef SENSOR_MSGS__MSG__JOYFEEDBACKARRAY_H_
#define SENSOR_MSGS__MSG__JOYFEEDBACKARRAY_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "sensor_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "sensor_msgs/msg/joy_feedback.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sensor_msgs__msg__JoyFeedbackArray
{
  sensor_msgs__msg__JoyFeedback__Sequence array;
} sensor_msgs__msg__JoyFeedbackArray;

typedef struct sensor_msgs__msg__JoyFeedbackArray__Sequence
{
  sensor_msgs__msg__JoyFeedbackArray * data;
  size_t size;
  size_t capacity;
} sensor_msgs__msg__JoyFeedbackArray__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__JoyFeedbackArray__init(sensor_msgs__msg__JoyFeedbackArray * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__JoyFeedbackArray__fini(sensor_msgs__msg__JoyFeedbackArray * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
sensor_msgs__msg__JoyFeedbackArray * sensor_msgs__msg__JoyFeedbackArray__create(void);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__JoyFeedbackArray__destroy(sensor_msgs__msg__JoyFeedbackArray * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__JoyFeedbackArray__Sequence__init(
  sensor_msgs__msg__JoyFeedbackArray__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__JoyFeedbackArray__Sequence__fini(
  sensor_msgs__msg__JoyFeedbackArray__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // SENSOR_MSGS__MSG__JOYFEEDBACKARRAY_H_
