// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/ChannelFloat32 message type

#ifndef SENSOR_MSGS__MSG__CHANNELFLOAT32_H_
#define SENSOR_MSGS__MSG__CHANNELFLOAT32_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "sensor_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "rosidl_runtime_c/primitives_sequence.h"
#include "rosidl_runtime_c/string.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sensor_msgs__msg__ChannelFloat32
{
  rosidl_runtime_c__String name;
  rosidl_runtime_c__float__Sequence values;
} sensor_msgs__msg__ChannelFloat32;

typedef struct sensor_msgs__msg__ChannelFloat32__Sequence
{
  sensor_msgs__msg__ChannelFloat32 * data;
  size_t size;
  size_t capacity;
} sensor_msgs__msg__ChannelFloat32__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__ChannelFloat32__init(sensor_msgs__msg__ChannelFloat32 * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__ChannelFloat32__fini(sensor_msgs__msg__ChannelFloat32 * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
sensor_msgs__msg__ChannelFloat32 * sensor_msgs__msg__ChannelFloat32__create(void);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__ChannelFloat32__destroy(sensor_msgs__msg__ChannelFloat32 * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__ChannelFloat32__Sequence__init(
  sensor_msgs__msg__ChannelFloat32__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__ChannelFloat32__Sequence__fini(
  sensor_msgs__msg__ChannelFloat32__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // SENSOR_MSGS__MSG__CHANNELFLOAT32_H_
