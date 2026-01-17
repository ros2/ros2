// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/JointState functions implementation

#include <stdbool.h>
#include <stdlib.h>

#include "sensor_msgs/msg/joint_state.h"
#include "rcutils/allocator.h"
#include "rosidl_runtime_c/string_functions.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool sensor_msgs__msg__JointState__init(sensor_msgs__msg__JointState * msg)
{
  if (!msg) { return false; }
  if (!std_msgs__msg__Header__init(&msg->header)) { return false; }
  if (!rosidl_runtime_c__String__Sequence__init(&msg->name, 0)) { return false; }
  if (!rosidl_runtime_c__double__Sequence__init(&msg->position, 0)) { return false; }
  if (!rosidl_runtime_c__double__Sequence__init(&msg->velocity, 0)) { return false; }
  if (!rosidl_runtime_c__double__Sequence__init(&msg->effort, 0)) { return false; }
  return true;
}

void sensor_msgs__msg__JointState__fini(sensor_msgs__msg__JointState * msg)
{
  if (!msg) { return; }
  std_msgs__msg__Header__fini(&msg->header);
  rosidl_runtime_c__String__Sequence__fini(&msg->name);
  rosidl_runtime_c__double__Sequence__fini(&msg->position);
  rosidl_runtime_c__double__Sequence__fini(&msg->velocity);
  rosidl_runtime_c__double__Sequence__fini(&msg->effort);
}

sensor_msgs__msg__JointState * sensor_msgs__msg__JointState__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sensor_msgs__msg__JointState * msg =
    (sensor_msgs__msg__JointState *)allocator.allocate(
      sizeof(sensor_msgs__msg__JointState), allocator.state);
  if (!msg) { return NULL; }
  if (!sensor_msgs__msg__JointState__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void sensor_msgs__msg__JointState__destroy(sensor_msgs__msg__JointState * msg)
{
  if (!msg) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sensor_msgs__msg__JointState__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool sensor_msgs__msg__JointState__Sequence__init(
  sensor_msgs__msg__JointState__Sequence * array, size_t size)
{
  if (!array) { return false; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (size) {
    array->data = (sensor_msgs__msg__JointState *)allocator.zero_allocate(
      size, sizeof(sensor_msgs__msg__JointState), allocator.state);
    if (!array->data) { return false; }
    for (size_t i = 0; i < size; ++i) {
      if (!sensor_msgs__msg__JointState__init(&array->data[i])) {
        for (size_t j = 0; j < i; ++j) {
          sensor_msgs__msg__JointState__fini(&array->data[j]);
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

void sensor_msgs__msg__JointState__Sequence__fini(
  sensor_msgs__msg__JointState__Sequence * array)
{
  if (!array) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array->data) {
    for (size_t i = 0; i < array->size; ++i) {
      sensor_msgs__msg__JointState__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  }
}
