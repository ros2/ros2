// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/PointCloud2 message type

#ifndef SENSOR_MSGS__MSG__POINTCLOUD2_H_
#define SENSOR_MSGS__MSG__POINTCLOUD2_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "sensor_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "rosidl_runtime_c/primitives_sequence.h"
#include "sensor_msgs/msg/point_field.h"
#include "std_msgs/msg/header.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sensor_msgs__msg__PointCloud2
{
  std_msgs__msg__Header header;
  uint32_t height;
  uint32_t width;
  sensor_msgs__msg__PointField__Sequence fields;
  bool is_bigendian;
  uint32_t point_step;
  uint32_t row_step;
  rosidl_runtime_c__uint8__Sequence data;
  bool is_dense;
} sensor_msgs__msg__PointCloud2;

typedef struct sensor_msgs__msg__PointCloud2__Sequence
{
  sensor_msgs__msg__PointCloud2 * data;
  size_t size;
  size_t capacity;
} sensor_msgs__msg__PointCloud2__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__PointCloud2__init(sensor_msgs__msg__PointCloud2 * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__PointCloud2__fini(sensor_msgs__msg__PointCloud2 * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
sensor_msgs__msg__PointCloud2 * sensor_msgs__msg__PointCloud2__create(void);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__PointCloud2__destroy(sensor_msgs__msg__PointCloud2 * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__PointCloud2__Sequence__init(
  sensor_msgs__msg__PointCloud2__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__PointCloud2__Sequence__fini(
  sensor_msgs__msg__PointCloud2__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // SENSOR_MSGS__MSG__POINTCLOUD2_H_
