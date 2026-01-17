// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/CameraInfo functions implementation

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "sensor_msgs/msg/camera_info.h"
#include "rcutils/allocator.h"
#include "rosidl_runtime_c/string_functions.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool sensor_msgs__msg__CameraInfo__init(sensor_msgs__msg__CameraInfo * msg)
{
  if (!msg) { return false; }
  if (!std_msgs__msg__Header__init(&msg->header)) { return false; }
  msg->height = 0;
  msg->width = 0;
  if (!rosidl_runtime_c__String__init(&msg->distortion_model)) { return false; }
  if (!rosidl_runtime_c__double__Sequence__init(&msg->d, 0)) { return false; }
  memset(msg->k, 0, sizeof(msg->k));
  memset(msg->r, 0, sizeof(msg->r));
  memset(msg->p, 0, sizeof(msg->p));
  msg->binning_x = 0;
  msg->binning_y = 0;
  if (!sensor_msgs__msg__RegionOfInterest__init(&msg->roi)) { return false; }
  return true;
}

void sensor_msgs__msg__CameraInfo__fini(sensor_msgs__msg__CameraInfo * msg)
{
  if (!msg) { return; }
  std_msgs__msg__Header__fini(&msg->header);
  rosidl_runtime_c__String__fini(&msg->distortion_model);
  rosidl_runtime_c__double__Sequence__fini(&msg->d);
  sensor_msgs__msg__RegionOfInterest__fini(&msg->roi);
}

sensor_msgs__msg__CameraInfo * sensor_msgs__msg__CameraInfo__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sensor_msgs__msg__CameraInfo * msg =
    (sensor_msgs__msg__CameraInfo *)allocator.allocate(
      sizeof(sensor_msgs__msg__CameraInfo), allocator.state);
  if (!msg) { return NULL; }
  if (!sensor_msgs__msg__CameraInfo__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void sensor_msgs__msg__CameraInfo__destroy(sensor_msgs__msg__CameraInfo * msg)
{
  if (!msg) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sensor_msgs__msg__CameraInfo__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool sensor_msgs__msg__CameraInfo__Sequence__init(
  sensor_msgs__msg__CameraInfo__Sequence * array, size_t size)
{
  if (!array) { return false; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (size) {
    array->data = (sensor_msgs__msg__CameraInfo *)allocator.zero_allocate(
      size, sizeof(sensor_msgs__msg__CameraInfo), allocator.state);
    if (!array->data) { return false; }
    for (size_t i = 0; i < size; ++i) {
      if (!sensor_msgs__msg__CameraInfo__init(&array->data[i])) {
        for (size_t j = 0; j < i; ++j) {
          sensor_msgs__msg__CameraInfo__fini(&array->data[j]);
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

void sensor_msgs__msg__CameraInfo__Sequence__fini(
  sensor_msgs__msg__CameraInfo__Sequence * array)
{
  if (!array) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array->data) {
    for (size_t i = 0; i < array->size; ++i) {
      sensor_msgs__msg__CameraInfo__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  }
}
