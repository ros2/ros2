// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/NavSatFix functions implementation

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "sensor_msgs/msg/nav_sat_fix.h"
#include "rcutils/allocator.h"
#include "rosidl_runtime_c/string_functions.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool sensor_msgs__msg__NavSatFix__init(sensor_msgs__msg__NavSatFix * msg)
{
  if (!msg) { return false; }
  if (!std_msgs__msg__Header__init(&msg->header)) { return false; }
  if (!sensor_msgs__msg__NavSatStatus__init(&msg->status)) { return false; }
  msg->latitude = 0.0;
  msg->longitude = 0.0;
  msg->altitude = 0.0;
  memset(msg->position_covariance, 0, sizeof(msg->position_covariance));
  msg->position_covariance_type = 0;
  return true;
}

void sensor_msgs__msg__NavSatFix__fini(sensor_msgs__msg__NavSatFix * msg)
{
  if (!msg) { return; }
  std_msgs__msg__Header__fini(&msg->header);
  sensor_msgs__msg__NavSatStatus__fini(&msg->status);
}

sensor_msgs__msg__NavSatFix * sensor_msgs__msg__NavSatFix__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sensor_msgs__msg__NavSatFix * msg =
    (sensor_msgs__msg__NavSatFix *)allocator.allocate(
      sizeof(sensor_msgs__msg__NavSatFix), allocator.state);
  if (!msg) { return NULL; }
  if (!sensor_msgs__msg__NavSatFix__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void sensor_msgs__msg__NavSatFix__destroy(sensor_msgs__msg__NavSatFix * msg)
{
  if (!msg) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sensor_msgs__msg__NavSatFix__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool sensor_msgs__msg__NavSatFix__Sequence__init(
  sensor_msgs__msg__NavSatFix__Sequence * array, size_t size)
{
  if (!array) { return false; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (size) {
    array->data = (sensor_msgs__msg__NavSatFix *)allocator.zero_allocate(
      size, sizeof(sensor_msgs__msg__NavSatFix), allocator.state);
    if (!array->data) { return false; }
    for (size_t i = 0; i < size; ++i) {
      if (!sensor_msgs__msg__NavSatFix__init(&array->data[i])) {
        for (size_t j = 0; j < i; ++j) {
          sensor_msgs__msg__NavSatFix__fini(&array->data[j]);
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

void sensor_msgs__msg__NavSatFix__Sequence__fini(
  sensor_msgs__msg__NavSatFix__Sequence * array)
{
  if (!array) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array->data) {
    for (size_t i = 0; i < array->size; ++i) {
      sensor_msgs__msg__NavSatFix__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  }
}
