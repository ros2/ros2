// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/ChannelFloat32 functions implementation

#include <stdbool.h>
#include <stdlib.h>

#include "sensor_msgs/msg/channel_float32.h"
#include "rcutils/allocator.h"
#include "rosidl_runtime_c/string_functions.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool sensor_msgs__msg__ChannelFloat32__init(sensor_msgs__msg__ChannelFloat32 * msg)
{
  if (!msg) { return false; }
  if (!rosidl_runtime_c__String__init(&msg->name)) { return false; }
  if (!rosidl_runtime_c__float__Sequence__init(&msg->values, 0)) { return false; }
  return true;
}

void sensor_msgs__msg__ChannelFloat32__fini(sensor_msgs__msg__ChannelFloat32 * msg)
{
  if (!msg) { return; }
  rosidl_runtime_c__String__fini(&msg->name);
  rosidl_runtime_c__float__Sequence__fini(&msg->values);
}

sensor_msgs__msg__ChannelFloat32 * sensor_msgs__msg__ChannelFloat32__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sensor_msgs__msg__ChannelFloat32 * msg =
    (sensor_msgs__msg__ChannelFloat32 *)allocator.allocate(
      sizeof(sensor_msgs__msg__ChannelFloat32), allocator.state);
  if (!msg) { return NULL; }
  if (!sensor_msgs__msg__ChannelFloat32__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void sensor_msgs__msg__ChannelFloat32__destroy(sensor_msgs__msg__ChannelFloat32 * msg)
{
  if (!msg) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sensor_msgs__msg__ChannelFloat32__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool sensor_msgs__msg__ChannelFloat32__Sequence__init(
  sensor_msgs__msg__ChannelFloat32__Sequence * array, size_t size)
{
  if (!array) { return false; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (size) {
    array->data = (sensor_msgs__msg__ChannelFloat32 *)allocator.zero_allocate(
      size, sizeof(sensor_msgs__msg__ChannelFloat32), allocator.state);
    if (!array->data) { return false; }
    for (size_t i = 0; i < size; ++i) {
      if (!sensor_msgs__msg__ChannelFloat32__init(&array->data[i])) {
        for (size_t j = 0; j < i; ++j) {
          sensor_msgs__msg__ChannelFloat32__fini(&array->data[j]);
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

void sensor_msgs__msg__ChannelFloat32__Sequence__fini(
  sensor_msgs__msg__ChannelFloat32__Sequence * array)
{
  if (!array) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array->data) {
    for (size_t i = 0; i < array->size; ++i) {
      sensor_msgs__msg__ChannelFloat32__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  }
}
