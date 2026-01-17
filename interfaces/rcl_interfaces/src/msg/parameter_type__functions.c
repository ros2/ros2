// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/msg/ParameterType functions

#include "rcl_interfaces/msg/parameter_type.h"
#include "rcutils/allocator.h"
#include <string.h>

bool rcl_interfaces__msg__ParameterType__init(rcl_interfaces__msg__ParameterType * msg)
{
  if (!msg) {
    return false;
  }
  (void)msg;
  return true;
}

void rcl_interfaces__msg__ParameterType__fini(rcl_interfaces__msg__ParameterType * msg)
{
  if (!msg) {
    return;
  }
  (void)msg;
}

rcl_interfaces__msg__ParameterType * rcl_interfaces__msg__ParameterType__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__msg__ParameterType * msg = (rcl_interfaces__msg__ParameterType *)allocator.allocate(
    sizeof(rcl_interfaces__msg__ParameterType), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!rcl_interfaces__msg__ParameterType__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void rcl_interfaces__msg__ParameterType__destroy(rcl_interfaces__msg__ParameterType * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__msg__ParameterType__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool rcl_interfaces__msg__ParameterType__Sequence__init(
  rcl_interfaces__msg__ParameterType__Sequence * array, size_t size)
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

  array->data = (rcl_interfaces__msg__ParameterType *)allocator.zero_allocate(
    size, sizeof(rcl_interfaces__msg__ParameterType), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!rcl_interfaces__msg__ParameterType__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        rcl_interfaces__msg__ParameterType__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void rcl_interfaces__msg__ParameterType__Sequence__fini(
  rcl_interfaces__msg__ParameterType__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    rcl_interfaces__msg__ParameterType__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
