// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/msg/ParameterEvent functions

#include "rcl_interfaces/msg/parameter_event.h"
#include "rcutils/allocator.h"
#include <string.h>

bool rcl_interfaces__msg__ParameterEvent__init(rcl_interfaces__msg__ParameterEvent * msg)
{
  if (!msg) {
    return false;
  }
  builtin_interfaces__msg__Time__init(&msg->stamp);
  rosidl_runtime_c__String__init(&msg->node);
  // new_parameters sequence initialized to empty
  // changed_parameters sequence initialized to empty
  // deleted_parameters sequence initialized to empty
  return true;
}

void rcl_interfaces__msg__ParameterEvent__fini(rcl_interfaces__msg__ParameterEvent * msg)
{
  if (!msg) {
    return;
  }
  builtin_interfaces__msg__Time__fini(&msg->stamp);
  rosidl_runtime_c__String__fini(&msg->node);
  rcl_interfaces__msg__Parameter__Sequence__fini(&msg->new_parameters);
  rcl_interfaces__msg__Parameter__Sequence__fini(&msg->changed_parameters);
  rcl_interfaces__msg__Parameter__Sequence__fini(&msg->deleted_parameters);
}

rcl_interfaces__msg__ParameterEvent * rcl_interfaces__msg__ParameterEvent__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__msg__ParameterEvent * msg = (rcl_interfaces__msg__ParameterEvent *)allocator.allocate(
    sizeof(rcl_interfaces__msg__ParameterEvent), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!rcl_interfaces__msg__ParameterEvent__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void rcl_interfaces__msg__ParameterEvent__destroy(rcl_interfaces__msg__ParameterEvent * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__msg__ParameterEvent__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool rcl_interfaces__msg__ParameterEvent__Sequence__init(
  rcl_interfaces__msg__ParameterEvent__Sequence * array, size_t size)
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

  array->data = (rcl_interfaces__msg__ParameterEvent *)allocator.zero_allocate(
    size, sizeof(rcl_interfaces__msg__ParameterEvent), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!rcl_interfaces__msg__ParameterEvent__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        rcl_interfaces__msg__ParameterEvent__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void rcl_interfaces__msg__ParameterEvent__Sequence__fini(
  rcl_interfaces__msg__ParameterEvent__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    rcl_interfaces__msg__ParameterEvent__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
