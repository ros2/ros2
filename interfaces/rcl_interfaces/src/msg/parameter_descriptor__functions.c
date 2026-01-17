// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/msg/ParameterDescriptor functions

#include "rcl_interfaces/msg/parameter_descriptor.h"
#include "rcutils/allocator.h"
#include <string.h>

bool rcl_interfaces__msg__ParameterDescriptor__init(rcl_interfaces__msg__ParameterDescriptor * msg)
{
  if (!msg) {
    return false;
  }
  rosidl_runtime_c__String__init(&msg->name);
  msg->type = 0;
  rosidl_runtime_c__String__init(&msg->description);
  rosidl_runtime_c__String__init(&msg->additional_constraints);
  msg->read_only = 0;
  msg->dynamic_typing = 0;
  // floating_point_range sequence initialized to empty
  // integer_range sequence initialized to empty
  return true;
}

void rcl_interfaces__msg__ParameterDescriptor__fini(rcl_interfaces__msg__ParameterDescriptor * msg)
{
  if (!msg) {
    return;
  }
  rosidl_runtime_c__String__fini(&msg->name);
  rosidl_runtime_c__String__fini(&msg->description);
  rosidl_runtime_c__String__fini(&msg->additional_constraints);
  rcl_interfaces__msg__FloatingPointRange__Sequence__fini(&msg->floating_point_range);
  rcl_interfaces__msg__IntegerRange__Sequence__fini(&msg->integer_range);
}

rcl_interfaces__msg__ParameterDescriptor * rcl_interfaces__msg__ParameterDescriptor__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__msg__ParameterDescriptor * msg = (rcl_interfaces__msg__ParameterDescriptor *)allocator.allocate(
    sizeof(rcl_interfaces__msg__ParameterDescriptor), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!rcl_interfaces__msg__ParameterDescriptor__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void rcl_interfaces__msg__ParameterDescriptor__destroy(rcl_interfaces__msg__ParameterDescriptor * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__msg__ParameterDescriptor__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool rcl_interfaces__msg__ParameterDescriptor__Sequence__init(
  rcl_interfaces__msg__ParameterDescriptor__Sequence * array, size_t size)
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

  array->data = (rcl_interfaces__msg__ParameterDescriptor *)allocator.zero_allocate(
    size, sizeof(rcl_interfaces__msg__ParameterDescriptor), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!rcl_interfaces__msg__ParameterDescriptor__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        rcl_interfaces__msg__ParameterDescriptor__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void rcl_interfaces__msg__ParameterDescriptor__Sequence__fini(
  rcl_interfaces__msg__ParameterDescriptor__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    rcl_interfaces__msg__ParameterDescriptor__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
