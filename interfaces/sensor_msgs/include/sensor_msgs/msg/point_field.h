// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/PointField message type

#ifndef SENSOR_MSGS__MSG__POINTFIELD_H_
#define SENSOR_MSGS__MSG__POINTFIELD_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "sensor_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "rosidl_runtime_c/string.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
  sensor_msgs__msg__PointField__INT8 = 1,
  sensor_msgs__msg__PointField__UINT8 = 2,
  sensor_msgs__msg__PointField__INT16 = 3,
  sensor_msgs__msg__PointField__UINT16 = 4,
  sensor_msgs__msg__PointField__INT32 = 5,
  sensor_msgs__msg__PointField__UINT32 = 6,
  sensor_msgs__msg__PointField__FLOAT32 = 7,
  sensor_msgs__msg__PointField__FLOAT64 = 8
}};

typedef struct sensor_msgs__msg__PointField
{
  rosidl_runtime_c__String name;
  uint32_t offset;
  uint8_t datatype;
  uint32_t count;
} sensor_msgs__msg__PointField;

typedef struct sensor_msgs__msg__PointField__Sequence
{
  sensor_msgs__msg__PointField * data;
  size_t size;
  size_t capacity;
} sensor_msgs__msg__PointField__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__PointField__init(sensor_msgs__msg__PointField * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__PointField__fini(sensor_msgs__msg__PointField * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
sensor_msgs__msg__PointField * sensor_msgs__msg__PointField__create(void);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__PointField__destroy(sensor_msgs__msg__PointField * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__PointField__Sequence__init(
  sensor_msgs__msg__PointField__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__PointField__Sequence__fini(
  sensor_msgs__msg__PointField__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // SENSOR_MSGS__MSG__POINTFIELD_H_
