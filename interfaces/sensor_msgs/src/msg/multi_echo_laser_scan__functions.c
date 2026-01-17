// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/MultiEchoLaserScan functions implementation

#include <stdbool.h>
#include <stdlib.h>

#include "sensor_msgs/msg/multi_echo_laser_scan.h"
#include "rcutils/allocator.h"
#include "rosidl_runtime_c/string_functions.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool sensor_msgs__msg__MultiEchoLaserScan__init(sensor_msgs__msg__MultiEchoLaserScan * msg)
{
  if (!msg) { return false; }
  if (!std_msgs__msg__Header__init(&msg->header)) { return false; }
  msg->angle_min = 0.0;
  msg->angle_max = 0.0;
  msg->angle_increment = 0.0;
  msg->time_increment = 0.0;
  msg->scan_time = 0.0;
  msg->range_min = 0.0;
  msg->range_max = 0.0;
  if (!sensor_msgs__msg__LaserEcho__Sequence__init(&msg->ranges, 0)) { return false; }
  if (!sensor_msgs__msg__LaserEcho__Sequence__init(&msg->intensities, 0)) { return false; }
  return true;
}

void sensor_msgs__msg__MultiEchoLaserScan__fini(sensor_msgs__msg__MultiEchoLaserScan * msg)
{
  if (!msg) { return; }
  std_msgs__msg__Header__fini(&msg->header);
  sensor_msgs__msg__LaserEcho__Sequence__fini(&msg->ranges);
  sensor_msgs__msg__LaserEcho__Sequence__fini(&msg->intensities);
}

sensor_msgs__msg__MultiEchoLaserScan * sensor_msgs__msg__MultiEchoLaserScan__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sensor_msgs__msg__MultiEchoLaserScan * msg =
    (sensor_msgs__msg__MultiEchoLaserScan *)allocator.allocate(
      sizeof(sensor_msgs__msg__MultiEchoLaserScan), allocator.state);
  if (!msg) { return NULL; }
  if (!sensor_msgs__msg__MultiEchoLaserScan__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void sensor_msgs__msg__MultiEchoLaserScan__destroy(sensor_msgs__msg__MultiEchoLaserScan * msg)
{
  if (!msg) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sensor_msgs__msg__MultiEchoLaserScan__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool sensor_msgs__msg__MultiEchoLaserScan__Sequence__init(
  sensor_msgs__msg__MultiEchoLaserScan__Sequence * array, size_t size)
{
  if (!array) { return false; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (size) {
    array->data = (sensor_msgs__msg__MultiEchoLaserScan *)allocator.zero_allocate(
      size, sizeof(sensor_msgs__msg__MultiEchoLaserScan), allocator.state);
    if (!array->data) { return false; }
    for (size_t i = 0; i < size; ++i) {
      if (!sensor_msgs__msg__MultiEchoLaserScan__init(&array->data[i])) {
        for (size_t j = 0; j < i; ++j) {
          sensor_msgs__msg__MultiEchoLaserScan__fini(&array->data[j]);
        }
        allocator.deallocate(array->data, allocator.state);
        return false;
      }
    }
  } else {
    array->data = NULL;
  }
  array->size = size;
  array->capacity = size;
  return true;
}

void sensor_msgs__msg__MultiEchoLaserScan__Sequence__fini(
  sensor_msgs__msg__MultiEchoLaserScan__Sequence * array)
{
  if (!array) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array->data) {
    for (size_t i = 0; i < array->size; ++i) {
      sensor_msgs__msg__MultiEchoLaserScan__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  }
}
