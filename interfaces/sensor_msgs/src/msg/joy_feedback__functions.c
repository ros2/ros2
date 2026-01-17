// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/JoyFeedback functions implementation

#include <stdbool.h>
#include <stdlib.h>

#include "sensor_msgs/msg/joy_feedback.h"
#include "rcutils/allocator.h"
#include "rosidl_runtime_c/string_functions.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool sensor_msgs__msg__JoyFeedback__init(sensor_msgs__msg__JoyFeedback * msg)
{
  if (!msg) { return false; }
  msg->type = 0;
  msg->id = 0;
  msg->intensity = 0.0;
  return true;
}

void sensor_msgs__msg__JoyFeedback__fini(sensor_msgs__msg__JoyFeedback * msg)
{
  if (!msg) { return; }
  (void)msg;
}

sensor_msgs__msg__JoyFeedback * sensor_msgs__msg__JoyFeedback__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sensor_msgs__msg__JoyFeedback * msg =
    (sensor_msgs__msg__JoyFeedback *)allocator.allocate(
      sizeof(sensor_msgs__msg__JoyFeedback), allocator.state);
  if (!msg) { return NULL; }
  if (!sensor_msgs__msg__JoyFeedback__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void sensor_msgs__msg__JoyFeedback__destroy(sensor_msgs__msg__JoyFeedback * msg)
{
  if (!msg) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sensor_msgs__msg__JoyFeedback__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool sensor_msgs__msg__JoyFeedback__Sequence__init(
  sensor_msgs__msg__JoyFeedback__Sequence * array, size_t size)
{
  if (!array) { return false; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (size) {
    array->data = (sensor_msgs__msg__JoyFeedback *)allocator.zero_allocate(
      size, sizeof(sensor_msgs__msg__JoyFeedback), allocator.state);
    if (!array->data) { return false; }
    for (size_t i = 0; i < size; ++i) {
      if (!sensor_msgs__msg__JoyFeedback__init(&array->data[i])) {
        for (size_t j = 0; j < i; ++j) {
          sensor_msgs__msg__JoyFeedback__fini(&array->data[j]);
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

void sensor_msgs__msg__JoyFeedback__Sequence__fini(
  sensor_msgs__msg__JoyFeedback__Sequence * array)
{
  if (!array) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array->data) {
    for (size_t i = 0; i < array->size; ++i) {
      sensor_msgs__msg__JoyFeedback__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  }
}
