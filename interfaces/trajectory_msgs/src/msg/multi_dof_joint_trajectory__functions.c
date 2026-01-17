// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// trajectory_msgs/msg/MultiDOFJointTrajectory functions

#include "trajectory_msgs/msg/multi_dof_joint_trajectory.h"
#include "rcutils/allocator.h"
#include <string.h>

bool trajectory_msgs__msg__MultiDOFJointTrajectory__init(trajectory_msgs__msg__MultiDOFJointTrajectory * msg)
{
  if (!msg) {
    return false;
  }
  memset(msg, 0, sizeof(*msg));
  std_msgs__msg__Header__init(&msg->header);
  rosidl_runtime_c__String__Sequence__init(&msg->joint_names, 0);
  trajectory_msgs__msg__MultiDOFJointTrajectoryPoint__Sequence__init(&msg->points, 0);
  return true;
}

void trajectory_msgs__msg__MultiDOFJointTrajectory__fini(trajectory_msgs__msg__MultiDOFJointTrajectory * msg)
{
  if (!msg) {
    return;
  }
  std_msgs__msg__Header__fini(&msg->header);
  rosidl_runtime_c__String__Sequence__fini(&msg->joint_names);
  trajectory_msgs__msg__MultiDOFJointTrajectoryPoint__Sequence__fini(&msg->points);
}

trajectory_msgs__msg__MultiDOFJointTrajectory * trajectory_msgs__msg__MultiDOFJointTrajectory__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  trajectory_msgs__msg__MultiDOFJointTrajectory * msg = (trajectory_msgs__msg__MultiDOFJointTrajectory *)allocator.allocate(
    sizeof(trajectory_msgs__msg__MultiDOFJointTrajectory), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!trajectory_msgs__msg__MultiDOFJointTrajectory__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void trajectory_msgs__msg__MultiDOFJointTrajectory__destroy(trajectory_msgs__msg__MultiDOFJointTrajectory * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  trajectory_msgs__msg__MultiDOFJointTrajectory__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool trajectory_msgs__msg__MultiDOFJointTrajectory__Sequence__init(
  trajectory_msgs__msg__MultiDOFJointTrajectory__Sequence * array, size_t size)
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

  array->data = (trajectory_msgs__msg__MultiDOFJointTrajectory *)allocator.zero_allocate(
    size, sizeof(trajectory_msgs__msg__MultiDOFJointTrajectory), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!trajectory_msgs__msg__MultiDOFJointTrajectory__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        trajectory_msgs__msg__MultiDOFJointTrajectory__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void trajectory_msgs__msg__MultiDOFJointTrajectory__Sequence__fini(
  trajectory_msgs__msg__MultiDOFJointTrajectory__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    trajectory_msgs__msg__MultiDOFJointTrajectory__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
