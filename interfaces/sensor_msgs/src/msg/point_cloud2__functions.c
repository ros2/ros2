// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/PointCloud2 functions implementation

#include <stdbool.h>
#include <stdlib.h>

#include "sensor_msgs/msg/point_cloud2.h"
#include "rcutils/allocator.h"
#include "rosidl_runtime_c/string_functions.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool sensor_msgs__msg__PointCloud2__init(sensor_msgs__msg__PointCloud2 * msg)
{
  if (!msg) { return false; }
  if (!std_msgs__msg__Header__init(&msg->header)) { return false; }
  msg->height = 0;
  msg->width = 0;
  if (!sensor_msgs__msg__PointField__Sequence__init(&msg->fields, 0)) { return false; }
  msg->is_bigendian = false;
  msg->point_step = 0;
  msg->row_step = 0;
  if (!rosidl_runtime_c__uint8__Sequence__init(&msg->data, 0)) { return false; }
  msg->is_dense = false;
  return true;
}

void sensor_msgs__msg__PointCloud2__fini(sensor_msgs__msg__PointCloud2 * msg)
{
  if (!msg) { return; }
  std_msgs__msg__Header__fini(&msg->header);
  sensor_msgs__msg__PointField__Sequence__fini(&msg->fields);
  rosidl_runtime_c__uint8__Sequence__fini(&msg->data);
}

sensor_msgs__msg__PointCloud2 * sensor_msgs__msg__PointCloud2__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sensor_msgs__msg__PointCloud2 * msg =
    (sensor_msgs__msg__PointCloud2 *)allocator.allocate(
      sizeof(sensor_msgs__msg__PointCloud2), allocator.state);
  if (!msg) { return NULL; }
  if (!sensor_msgs__msg__PointCloud2__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void sensor_msgs__msg__PointCloud2__destroy(sensor_msgs__msg__PointCloud2 * msg)
{
  if (!msg) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sensor_msgs__msg__PointCloud2__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool sensor_msgs__msg__PointCloud2__Sequence__init(
  sensor_msgs__msg__PointCloud2__Sequence * array, size_t size)
{
  if (!array) { return false; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (size) {
    array->data = (sensor_msgs__msg__PointCloud2 *)allocator.zero_allocate(
      size, sizeof(sensor_msgs__msg__PointCloud2), allocator.state);
    if (!array->data) { return false; }
    for (size_t i = 0; i < size; ++i) {
      if (!sensor_msgs__msg__PointCloud2__init(&array->data[i])) {
        for (size_t j = 0; j < i; ++j) {
          sensor_msgs__msg__PointCloud2__fini(&array->data[j]);
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

void sensor_msgs__msg__PointCloud2__Sequence__fini(
  sensor_msgs__msg__PointCloud2__Sequence * array)
{
  if (!array) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array->data) {
    for (size_t i = 0; i < array->size; ++i) {
      sensor_msgs__msg__PointCloud2__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  }
}
