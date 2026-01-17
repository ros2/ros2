// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// trajectory_msgs/msg/MultiDOFJointTrajectoryPoint functions

#include "trajectory_msgs/msg/multi_dof_joint_trajectory_point.h"
#include "rcutils/allocator.h"
#include <string.h>

bool trajectory_msgs__msg__MultiDOFJointTrajectoryPoint__init(trajectory_msgs__msg__MultiDOFJointTrajectoryPoint * msg)
{
  if (!msg) {
    return false;
  }
  memset(msg, 0, sizeof(*msg));
  geometry_msgs__msg__Transform__Sequence__init(&msg->transforms, 0);
  geometry_msgs__msg__Twist__Sequence__init(&msg->velocities, 0);
  geometry_msgs__msg__Twist__Sequence__init(&msg->accelerations, 0);
  builtin_interfaces__msg__Duration__init(&msg->time_from_start);
  return true;
}

void trajectory_msgs__msg__MultiDOFJointTrajectoryPoint__fini(trajectory_msgs__msg__MultiDOFJointTrajectoryPoint * msg)
{
  if (!msg) {
    return;
  }
  geometry_msgs__msg__Transform__Sequence__fini(&msg->transforms);
  geometry_msgs__msg__Twist__Sequence__fini(&msg->velocities);
  geometry_msgs__msg__Twist__Sequence__fini(&msg->accelerations);
  builtin_interfaces__msg__Duration__fini(&msg->time_from_start);
}

trajectory_msgs__msg__MultiDOFJointTrajectoryPoint * trajectory_msgs__msg__MultiDOFJointTrajectoryPoint__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  trajectory_msgs__msg__MultiDOFJointTrajectoryPoint * msg = (trajectory_msgs__msg__MultiDOFJointTrajectoryPoint *)allocator.allocate(
    sizeof(trajectory_msgs__msg__MultiDOFJointTrajectoryPoint), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!trajectory_msgs__msg__MultiDOFJointTrajectoryPoint__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void trajectory_msgs__msg__MultiDOFJointTrajectoryPoint__destroy(trajectory_msgs__msg__MultiDOFJointTrajectoryPoint * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  trajectory_msgs__msg__MultiDOFJointTrajectoryPoint__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool trajectory_msgs__msg__MultiDOFJointTrajectoryPoint__Sequence__init(
  trajectory_msgs__msg__MultiDOFJointTrajectoryPoint__Sequence * array, size_t size)
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

  array->data = (trajectory_msgs__msg__MultiDOFJointTrajectoryPoint *)allocator.zero_allocate(
    size, sizeof(trajectory_msgs__msg__MultiDOFJointTrajectoryPoint), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!trajectory_msgs__msg__MultiDOFJointTrajectoryPoint__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        trajectory_msgs__msg__MultiDOFJointTrajectoryPoint__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void trajectory_msgs__msg__MultiDOFJointTrajectoryPoint__Sequence__fini(
  trajectory_msgs__msg__MultiDOFJointTrajectoryPoint__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    trajectory_msgs__msg__MultiDOFJointTrajectoryPoint__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
