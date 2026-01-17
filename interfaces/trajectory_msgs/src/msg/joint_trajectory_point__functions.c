// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// trajectory_msgs/msg/JointTrajectoryPoint functions

#include "trajectory_msgs/msg/joint_trajectory_point.h"
#include "rcutils/allocator.h"
#include <string.h>

bool trajectory_msgs__msg__JointTrajectoryPoint__init(trajectory_msgs__msg__JointTrajectoryPoint * msg)
{
  if (!msg) {
    return false;
  }
  memset(msg, 0, sizeof(*msg));
  rosidl_runtime_c__double__Sequence__init(&msg->positions, 0);
  rosidl_runtime_c__double__Sequence__init(&msg->velocities, 0);
  rosidl_runtime_c__double__Sequence__init(&msg->accelerations, 0);
  rosidl_runtime_c__double__Sequence__init(&msg->effort, 0);
  builtin_interfaces__msg__Duration__init(&msg->time_from_start);
  return true;
}

void trajectory_msgs__msg__JointTrajectoryPoint__fini(trajectory_msgs__msg__JointTrajectoryPoint * msg)
{
  if (!msg) {
    return;
  }
  rosidl_runtime_c__double__Sequence__fini(&msg->positions);
  rosidl_runtime_c__double__Sequence__fini(&msg->velocities);
  rosidl_runtime_c__double__Sequence__fini(&msg->accelerations);
  rosidl_runtime_c__double__Sequence__fini(&msg->effort);
  builtin_interfaces__msg__Duration__fini(&msg->time_from_start);
}

trajectory_msgs__msg__JointTrajectoryPoint * trajectory_msgs__msg__JointTrajectoryPoint__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  trajectory_msgs__msg__JointTrajectoryPoint * msg = (trajectory_msgs__msg__JointTrajectoryPoint *)allocator.allocate(
    sizeof(trajectory_msgs__msg__JointTrajectoryPoint), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!trajectory_msgs__msg__JointTrajectoryPoint__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void trajectory_msgs__msg__JointTrajectoryPoint__destroy(trajectory_msgs__msg__JointTrajectoryPoint * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  trajectory_msgs__msg__JointTrajectoryPoint__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool trajectory_msgs__msg__JointTrajectoryPoint__Sequence__init(
  trajectory_msgs__msg__JointTrajectoryPoint__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (size == 0) {
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
    return true;
  }

  array->data = (trajectory_msgs__msg__JointTrajectoryPoint *)allocator.zero_allocate(
    size, sizeof(trajectory_msgs__msg__JointTrajectoryPoint), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!trajectory_msgs__msg__JointTrajectoryPoint__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        trajectory_msgs__msg__JointTrajectoryPoint__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void trajectory_msgs__msg__JointTrajectoryPoint__Sequence__fini(
  trajectory_msgs__msg__JointTrajectoryPoint__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    trajectory_msgs__msg__JointTrajectoryPoint__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
