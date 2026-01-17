// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// tf2_msgs/msg/TF2Error functions

#include "tf2_msgs/msg/t_f2_error.h"
#include "rcutils/allocator.h"
#include <string.h>

bool tf2_msgs__msg__TF2Error__init(tf2_msgs__msg__TF2Error * msg)
{
  if (!msg) {
    return false;
  }
  memset(msg, 0, sizeof(*msg));
  msg->error = 0;
  rosidl_runtime_c__String__init(&msg->error_string);
  return true;
}

void tf2_msgs__msg__TF2Error__fini(tf2_msgs__msg__TF2Error * msg)
{
  if (!msg) {
    return;
  }
  rosidl_runtime_c__String__fini(&msg->error_string);
}

tf2_msgs__msg__TF2Error * tf2_msgs__msg__TF2Error__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  tf2_msgs__msg__TF2Error * msg = (tf2_msgs__msg__TF2Error *)allocator.allocate(
    sizeof(tf2_msgs__msg__TF2Error), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!tf2_msgs__msg__TF2Error__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void tf2_msgs__msg__TF2Error__destroy(tf2_msgs__msg__TF2Error * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  tf2_msgs__msg__TF2Error__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool tf2_msgs__msg__TF2Error__Sequence__init(
  tf2_msgs__msg__TF2Error__Sequence * array, size_t size)
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

  array->data = (tf2_msgs__msg__TF2Error *)allocator.zero_allocate(
    size, sizeof(tf2_msgs__msg__TF2Error), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!tf2_msgs__msg__TF2Error__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        tf2_msgs__msg__TF2Error__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void tf2_msgs__msg__TF2Error__Sequence__fini(
  tf2_msgs__msg__TF2Error__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    tf2_msgs__msg__TF2Error__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
