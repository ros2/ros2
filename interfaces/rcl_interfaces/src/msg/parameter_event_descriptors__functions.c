// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// rcl_interfaces/msg/ParameterEventDescriptors functions

#include "rcl_interfaces/msg/parameter_event_descriptors.h"
#include "rcutils/allocator.h"
#include <string.h>

bool rcl_interfaces__msg__ParameterEventDescriptors__init(rcl_interfaces__msg__ParameterEventDescriptors * msg)
{
  if (!msg) {
    return false;
  }
  // new_parameters sequence initialized to empty
  // changed_parameters sequence initialized to empty
  // deleted_parameters sequence initialized to empty
  return true;
}

void rcl_interfaces__msg__ParameterEventDescriptors__fini(rcl_interfaces__msg__ParameterEventDescriptors * msg)
{
  if (!msg) {
    return;
  }
  rcl_interfaces__msg__ParameterDescriptor__Sequence__fini(&msg->new_parameters);
  rcl_interfaces__msg__ParameterDescriptor__Sequence__fini(&msg->changed_parameters);
  rcl_interfaces__msg__ParameterDescriptor__Sequence__fini(&msg->deleted_parameters);
}

rcl_interfaces__msg__ParameterEventDescriptors * rcl_interfaces__msg__ParameterEventDescriptors__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__msg__ParameterEventDescriptors * msg = (rcl_interfaces__msg__ParameterEventDescriptors *)allocator.allocate(
    sizeof(rcl_interfaces__msg__ParameterEventDescriptors), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!rcl_interfaces__msg__ParameterEventDescriptors__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void rcl_interfaces__msg__ParameterEventDescriptors__destroy(rcl_interfaces__msg__ParameterEventDescriptors * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__msg__ParameterEventDescriptors__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool rcl_interfaces__msg__ParameterEventDescriptors__Sequence__init(
  rcl_interfaces__msg__ParameterEventDescriptors__Sequence * array, size_t size)
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

  array->data = (rcl_interfaces__msg__ParameterEventDescriptors *)allocator.zero_allocate(
    size, sizeof(rcl_interfaces__msg__ParameterEventDescriptors), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!rcl_interfaces__msg__ParameterEventDescriptors__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        rcl_interfaces__msg__ParameterEventDescriptors__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void rcl_interfaces__msg__ParameterEventDescriptors__Sequence__fini(
  rcl_interfaces__msg__ParameterEventDescriptors__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    rcl_interfaces__msg__ParameterEventDescriptors__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
