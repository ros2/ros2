// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/JoyFeedback message type

#ifndef SENSOR_MSGS__MSG__JOYFEEDBACK_H_
#define SENSOR_MSGS__MSG__JOYFEEDBACK_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "sensor_msgs/msg/rosidl_generator_c__visibility_control.h"


#ifdef __cplusplus
extern "C" {
#endif

enum {
  sensor_msgs__msg__JoyFeedback__TYPE_LED = 0,
  sensor_msgs__msg__JoyFeedback__TYPE_RUMBLE = 1,
  sensor_msgs__msg__JoyFeedback__TYPE_BUZZER = 2
}};

typedef struct sensor_msgs__msg__JoyFeedback
{
  uint8_t type;
  uint8_t id;
  float intensity;
} sensor_msgs__msg__JoyFeedback;

typedef struct sensor_msgs__msg__JoyFeedback__Sequence
{
  sensor_msgs__msg__JoyFeedback * data;
  size_t size;
  size_t capacity;
} sensor_msgs__msg__JoyFeedback__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__JoyFeedback__init(sensor_msgs__msg__JoyFeedback * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__JoyFeedback__fini(sensor_msgs__msg__JoyFeedback * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
sensor_msgs__msg__JoyFeedback * sensor_msgs__msg__JoyFeedback__create(void);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__JoyFeedback__destroy(sensor_msgs__msg__JoyFeedback * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__JoyFeedback__Sequence__init(
  sensor_msgs__msg__JoyFeedback__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__JoyFeedback__Sequence__fini(
  sensor_msgs__msg__JoyFeedback__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // SENSOR_MSGS__MSG__JOYFEEDBACK_H_
