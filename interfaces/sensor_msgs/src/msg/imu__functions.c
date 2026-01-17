// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/Imu functions implementation

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "sensor_msgs/msg/imu.h"
#include "rcutils/allocator.h"
#include "rosidl_runtime_c/string_functions.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool sensor_msgs__msg__Imu__init(sensor_msgs__msg__Imu * msg)
{
  if (!msg) { return false; }
  if (!std_msgs__msg__Header__init(&msg->header)) { return false; }
  if (!geometry_msgs__msg__Quaternion__init(&msg->orientation)) { return false; }
  memset(msg->orientation_covariance, 0, sizeof(msg->orientation_covariance));
  if (!geometry_msgs__msg__Vector3__init(&msg->angular_velocity)) { return false; }
  memset(msg->angular_velocity_covariance, 0, sizeof(msg->angular_velocity_covariance));
  if (!geometry_msgs__msg__Vector3__init(&msg->linear_acceleration)) { return false; }
  memset(msg->linear_acceleration_covariance, 0, sizeof(msg->linear_acceleration_covariance));
  return true;
}

void sensor_msgs__msg__Imu__fini(sensor_msgs__msg__Imu * msg)
{
  if (!msg) { return; }
  std_msgs__msg__Header__fini(&msg->header);
  geometry_msgs__msg__Quaternion__fini(&msg->orientation);
  geometry_msgs__msg__Vector3__fini(&msg->angular_velocity);
  geometry_msgs__msg__Vector3__fini(&msg->linear_acceleration);
}

sensor_msgs__msg__Imu * sensor_msgs__msg__Imu__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sensor_msgs__msg__Imu * msg =
    (sensor_msgs__msg__Imu *)allocator.allocate(
      sizeof(sensor_msgs__msg__Imu), allocator.state);
  if (!msg) { return NULL; }
  if (!sensor_msgs__msg__Imu__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void sensor_msgs__msg__Imu__destroy(sensor_msgs__msg__Imu * msg)
{
  if (!msg) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sensor_msgs__msg__Imu__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool sensor_msgs__msg__Imu__Sequence__init(
  sensor_msgs__msg__Imu__Sequence * array, size_t size)
{
  if (!array) { return false; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (size) {
    array->data = (sensor_msgs__msg__Imu *)allocator.zero_allocate(
      size, sizeof(sensor_msgs__msg__Imu), allocator.state);
    if (!array->data) { return false; }
    for (size_t i = 0; i < size; ++i) {
      if (!sensor_msgs__msg__Imu__init(&array->data[i])) {
        for (size_t j = 0; j < i; ++j) {
          sensor_msgs__msg__Imu__fini(&array->data[j]);
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

void sensor_msgs__msg__Imu__Sequence__fini(
  sensor_msgs__msg__Imu__Sequence * array)
{
  if (!array) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array->data) {
    for (size_t i = 0; i < array->size; ++i) {
      sensor_msgs__msg__Imu__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  }
}
