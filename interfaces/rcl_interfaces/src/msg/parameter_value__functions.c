// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/msg/ParameterValue functions

#include "rcl_interfaces/msg/parameter_value.h"
#include "rcutils/allocator.h"
#include <string.h>

bool rcl_interfaces__msg__ParameterValue__init(rcl_interfaces__msg__ParameterValue * msg)
{
  if (!msg) {
    return false;
  }
  msg->type = 0;
  msg->bool_value = 0;
  msg->integer_value = 0;
  msg->double_value = 0;
  rosidl_runtime_c__String__init(&msg->string_value);
  // byte_array_value sequence initialized to empty
  // bool_array_value sequence initialized to empty
  // integer_array_value sequence initialized to empty
  // double_array_value sequence initialized to empty
  // string_array_value sequence initialized to empty
  return true;
}

void rcl_interfaces__msg__ParameterValue__fini(rcl_interfaces__msg__ParameterValue * msg)
{
  if (!msg) {
    return;
  }
  rosidl_runtime_c__String__fini(&msg->string_value);
  rosidl_runtime_c__octet__Sequence__fini(&msg->byte_array_value);
  rosidl_runtime_c__boolean__Sequence__fini(&msg->bool_array_value);
  rosidl_runtime_c__int64__Sequence__fini(&msg->integer_array_value);
  rosidl_runtime_c__double__Sequence__fini(&msg->double_array_value);
  rosidl_runtime_c__String__Sequence__fini(&msg->string_array_value);
}

rcl_interfaces__msg__ParameterValue * rcl_interfaces__msg__ParameterValue__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__msg__ParameterValue * msg = (rcl_interfaces__msg__ParameterValue *)allocator.allocate(
    sizeof(rcl_interfaces__msg__ParameterValue), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!rcl_interfaces__msg__ParameterValue__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void rcl_interfaces__msg__ParameterValue__destroy(rcl_interfaces__msg__ParameterValue * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__msg__ParameterValue__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool rcl_interfaces__msg__ParameterValue__Sequence__init(
  rcl_interfaces__msg__ParameterValue__Sequence * array, size_t size)
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

  array->data = (rcl_interfaces__msg__ParameterValue *)allocator.zero_allocate(
    size, sizeof(rcl_interfaces__msg__ParameterValue), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!rcl_interfaces__msg__ParameterValue__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        rcl_interfaces__msg__ParameterValue__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void rcl_interfaces__msg__ParameterValue__Sequence__fini(
  rcl_interfaces__msg__ParameterValue__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    rcl_interfaces__msg__ParameterValue__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
