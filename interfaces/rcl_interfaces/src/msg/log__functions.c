// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/msg/Log functions

#include "rcl_interfaces/msg/log.h"
#include "rcutils/allocator.h"
#include <string.h>

bool rcl_interfaces__msg__Log__init(rcl_interfaces__msg__Log * msg)
{
  if (!msg) {
    return false;
  }
  builtin_interfaces__msg__Time__init(&msg->stamp);
  msg->level = 0;
  rosidl_runtime_c__String__init(&msg->name);
  rosidl_runtime_c__String__init(&msg->msg);
  rosidl_runtime_c__String__init(&msg->file);
  rosidl_runtime_c__String__init(&msg->function);
  msg->line = 0;
  return true;
}

void rcl_interfaces__msg__Log__fini(rcl_interfaces__msg__Log * msg)
{
  if (!msg) {
    return;
  }
  builtin_interfaces__msg__Time__fini(&msg->stamp);
  rosidl_runtime_c__String__fini(&msg->name);
  rosidl_runtime_c__String__fini(&msg->msg);
  rosidl_runtime_c__String__fini(&msg->file);
  rosidl_runtime_c__String__fini(&msg->function);
}

rcl_interfaces__msg__Log * rcl_interfaces__msg__Log__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__msg__Log * msg = (rcl_interfaces__msg__Log *)allocator.allocate(
    sizeof(rcl_interfaces__msg__Log), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!rcl_interfaces__msg__Log__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void rcl_interfaces__msg__Log__destroy(rcl_interfaces__msg__Log * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__msg__Log__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool rcl_interfaces__msg__Log__Sequence__init(
  rcl_interfaces__msg__Log__Sequence * array, size_t size)
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

  array->data = (rcl_interfaces__msg__Log *)allocator.zero_allocate(
    size, sizeof(rcl_interfaces__msg__Log), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!rcl_interfaces__msg__Log__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        rcl_interfaces__msg__Log__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void rcl_interfaces__msg__Log__Sequence__fini(
  rcl_interfaces__msg__Log__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    rcl_interfaces__msg__Log__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
