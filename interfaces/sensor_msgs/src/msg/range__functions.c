// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/Range functions implementation

#include <stdbool.h>
#include <stdlib.h>

#include "sensor_msgs/msg/range.h"
#include "rcutils/allocator.h"
#include "rosidl_runtime_c/string_functions.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool sensor_msgs__msg__Range__init(sensor_msgs__msg__Range * msg)
{
  if (!msg) { return false; }
  if (!std_msgs__msg__Header__init(&msg->header)) { return false; }
  msg->radiation_type = 0;
  msg->field_of_view = 0.0;
  msg->min_range = 0.0;
  msg->max_range = 0.0;
  msg->range = 0.0;
  return true;
}

void sensor_msgs__msg__Range__fini(sensor_msgs__msg__Range * msg)
{
  if (!msg) { return; }
  std_msgs__msg__Header__fini(&msg->header);
}

sensor_msgs__msg__Range * sensor_msgs__msg__Range__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sensor_msgs__msg__Range * msg =
    (sensor_msgs__msg__Range *)allocator.allocate(
      sizeof(sensor_msgs__msg__Range), allocator.state);
  if (!msg) { return NULL; }
  if (!sensor_msgs__msg__Range__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void sensor_msgs__msg__Range__destroy(sensor_msgs__msg__Range * msg)
{
  if (!msg) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sensor_msgs__msg__Range__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool sensor_msgs__msg__Range__Sequence__init(
  sensor_msgs__msg__Range__Sequence * array, size_t size)
{
  if (!array) { return false; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (size) {
    array->data = (sensor_msgs__msg__Range *)allocator.zero_allocate(
      size, sizeof(sensor_msgs__msg__Range), allocator.state);
    if (!array->data) { return false; }
    for (size_t i = 0; i < size; ++i) {
      if (!sensor_msgs__msg__Range__init(&array->data[i])) {
        for (size_t j = 0; j < i; ++j) {
          sensor_msgs__msg__Range__fini(&array->data[j]);
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

void sensor_msgs__msg__Range__Sequence__fini(
  sensor_msgs__msg__Range__Sequence * array)
{
  if (!array) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array->data) {
    for (size_t i = 0; i < array->size; ++i) {
      sensor_msgs__msg__Range__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  }
}
