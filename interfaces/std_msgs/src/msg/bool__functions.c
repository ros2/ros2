// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// std_msgs/msg/Bool functions implementation

#include <stdbool.h>
#include <stdlib.h>
#include "std_msgs/msg/bool.h"
#include "rcutils/allocator.h"

bool std_msgs__msg__Bool__init(std_msgs__msg__Bool * msg)
{
  if (!msg) { return false; }
  msg->data = false;
  return true;
}

void std_msgs__msg__Bool__fini(std_msgs__msg__Bool * msg)
{
  (void)msg;
}

std_msgs__msg__Bool * std_msgs__msg__Bool__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_msgs__msg__Bool * msg = (std_msgs__msg__Bool *)allocator.allocate(
    sizeof(std_msgs__msg__Bool), allocator.state);
  if (!msg) { return NULL; }
  if (!std_msgs__msg__Bool__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void std_msgs__msg__Bool__destroy(std_msgs__msg__Bool * msg)
{
  if (!msg) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_msgs__msg__Bool__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool std_msgs__msg__Bool__Sequence__init(
  std_msgs__msg__Bool__Sequence * array, size_t size)
{
  if (!array) { return false; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (size) {
    array->data = (std_msgs__msg__Bool *)allocator.zero_allocate(
      size, sizeof(std_msgs__msg__Bool), allocator.state);
    if (!array->data) { return false; }
  } else {
    array->data = NULL;
  }
  array->size = size;
  array->capacity = size;
  return true;
}

void std_msgs__msg__Bool__Sequence__fini(
  std_msgs__msg__Bool__Sequence * array)
{
  if (!array || !array->data) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
