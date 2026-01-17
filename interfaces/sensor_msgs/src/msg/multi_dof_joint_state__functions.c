// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/MultiDOFJointState functions implementation

#include <stdbool.h>
#include <stdlib.h>

#include "sensor_msgs/msg/multi_dof_joint_state.h"
#include "rcutils/allocator.h"
#include "rosidl_runtime_c/string_functions.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool sensor_msgs__msg__MultiDOFJointState__init(sensor_msgs__msg__MultiDOFJointState * msg)
{
  if (!msg) { return false; }
  if (!std_msgs__msg__Header__init(&msg->header)) { return false; }
  if (!rosidl_runtime_c__String__Sequence__init(&msg->joint_names, 0)) { return false; }
  if (!geometry_msgs__msg__Transform__Sequence__init(&msg->transforms, 0)) { return false; }
  if (!geometry_msgs__msg__Twist__Sequence__init(&msg->twist, 0)) { return false; }
  if (!geometry_msgs__msg__Wrench__Sequence__init(&msg->wrench, 0)) { return false; }
  return true;
}

void sensor_msgs__msg__MultiDOFJointState__fini(sensor_msgs__msg__MultiDOFJointState * msg)
{
  if (!msg) { return; }
  std_msgs__msg__Header__fini(&msg->header);
  rosidl_runtime_c__String__Sequence__fini(&msg->joint_names);
  geometry_msgs__msg__Transform__Sequence__fini(&msg->transforms);
  geometry_msgs__msg__Twist__Sequence__fini(&msg->twist);
  geometry_msgs__msg__Wrench__Sequence__fini(&msg->wrench);
}

sensor_msgs__msg__MultiDOFJointState * sensor_msgs__msg__MultiDOFJointState__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sensor_msgs__msg__MultiDOFJointState * msg =
    (sensor_msgs__msg__MultiDOFJointState *)allocator.allocate(
      sizeof(sensor_msgs__msg__MultiDOFJointState), allocator.state);
  if (!msg) { return NULL; }
  if (!sensor_msgs__msg__MultiDOFJointState__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void sensor_msgs__msg__MultiDOFJointState__destroy(sensor_msgs__msg__MultiDOFJointState * msg)
{
  if (!msg) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sensor_msgs__msg__MultiDOFJointState__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool sensor_msgs__msg__MultiDOFJointState__Sequence__init(
  sensor_msgs__msg__MultiDOFJointState__Sequence * array, size_t size)
{
  if (!array) { return false; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (size) {
    array->data = (sensor_msgs__msg__MultiDOFJointState *)allocator.zero_allocate(
      size, sizeof(sensor_msgs__msg__MultiDOFJointState), allocator.state);
    if (!array->data) { return false; }
    for (size_t i = 0; i < size; ++i) {
      if (!sensor_msgs__msg__MultiDOFJointState__init(&array->data[i])) {
        for (size_t j = 0; j < i; ++j) {
          sensor_msgs__msg__MultiDOFJointState__fini(&array->data[j]);
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

void sensor_msgs__msg__MultiDOFJointState__Sequence__fini(
  sensor_msgs__msg__MultiDOFJointState__Sequence * array)
{
  if (!array) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array->data) {
    for (size_t i = 0; i < array->size; ++i) {
      sensor_msgs__msg__MultiDOFJointState__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  }
}
