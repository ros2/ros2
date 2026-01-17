// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// type_description_interfaces/msg/TypeSource functions

#include "type_description_interfaces/msg/type_source.h"
#include "rcutils/allocator.h"
#include <string.h>

bool type_description_interfaces__msg__TypeSource__init(type_description_interfaces__msg__TypeSource * msg)
{
  if (!msg) {
    return false;
  }
  rosidl_runtime_c__String__init(&msg->type_name);
  rosidl_runtime_c__String__init(&msg->encoding);
  rosidl_runtime_c__String__init(&msg->raw_source);
  return true;
}

void type_description_interfaces__msg__TypeSource__fini(type_description_interfaces__msg__TypeSource * msg)
{
  if (!msg) {
    return;
  }
  rosidl_runtime_c__String__fini(&msg->type_name);
  rosidl_runtime_c__String__fini(&msg->encoding);
  rosidl_runtime_c__String__fini(&msg->raw_source);
}

type_description_interfaces__msg__TypeSource * type_description_interfaces__msg__TypeSource__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  type_description_interfaces__msg__TypeSource * msg = (type_description_interfaces__msg__TypeSource *)allocator.allocate(
    sizeof(type_description_interfaces__msg__TypeSource), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!type_description_interfaces__msg__TypeSource__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void type_description_interfaces__msg__TypeSource__destroy(type_description_interfaces__msg__TypeSource * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  type_description_interfaces__msg__TypeSource__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool type_description_interfaces__msg__TypeSource__Sequence__init(
  type_description_interfaces__msg__TypeSource__Sequence * array, size_t size)
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

  array->data = (type_description_interfaces__msg__TypeSource *)allocator.zero_allocate(
    size, sizeof(type_description_interfaces__msg__TypeSource), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!type_description_interfaces__msg__TypeSource__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        type_description_interfaces__msg__TypeSource__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void type_description_interfaces__msg__TypeSource__Sequence__fini(
  type_description_interfaces__msg__TypeSource__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    type_description_interfaces__msg__TypeSource__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
