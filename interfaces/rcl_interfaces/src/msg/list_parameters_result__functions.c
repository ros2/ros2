// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/msg/ListParametersResult functions

#include "rcl_interfaces/msg/list_parameters_result.h"
#include "rcutils/allocator.h"
#include <string.h>

bool rcl_interfaces__msg__ListParametersResult__init(rcl_interfaces__msg__ListParametersResult * msg)
{
  if (!msg) {
    return false;
  }
  // names sequence initialized to empty
  // prefixes sequence initialized to empty
  return true;
}

void rcl_interfaces__msg__ListParametersResult__fini(rcl_interfaces__msg__ListParametersResult * msg)
{
  if (!msg) {
    return;
  }
  rosidl_runtime_c__String__Sequence__fini(&msg->names);
  rosidl_runtime_c__String__Sequence__fini(&msg->prefixes);
}

rcl_interfaces__msg__ListParametersResult * rcl_interfaces__msg__ListParametersResult__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__msg__ListParametersResult * msg = (rcl_interfaces__msg__ListParametersResult *)allocator.allocate(
    sizeof(rcl_interfaces__msg__ListParametersResult), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!rcl_interfaces__msg__ListParametersResult__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void rcl_interfaces__msg__ListParametersResult__destroy(rcl_interfaces__msg__ListParametersResult * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__msg__ListParametersResult__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool rcl_interfaces__msg__ListParametersResult__Sequence__init(
  rcl_interfaces__msg__ListParametersResult__Sequence * array, size_t size)
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

  array->data = (rcl_interfaces__msg__ListParametersResult *)allocator.zero_allocate(
    size, sizeof(rcl_interfaces__msg__ListParametersResult), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!rcl_interfaces__msg__ListParametersResult__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        rcl_interfaces__msg__ListParametersResult__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void rcl_interfaces__msg__ListParametersResult__Sequence__fini(
  rcl_interfaces__msg__ListParametersResult__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    rcl_interfaces__msg__ListParametersResult__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
