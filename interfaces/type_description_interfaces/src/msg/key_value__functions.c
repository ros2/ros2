// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// type_description_interfaces/msg/KeyValue functions

#include "type_description_interfaces/msg/key_value.h"
#include "rcutils/allocator.h"
#include <string.h>

bool type_description_interfaces__msg__KeyValue__init(type_description_interfaces__msg__KeyValue * msg)
{
  if (!msg) {
    return false;
  }
  rosidl_runtime_c__String__init(&msg->key);
  rosidl_runtime_c__String__init(&msg->value);
  return true;
}

void type_description_interfaces__msg__KeyValue__fini(type_description_interfaces__msg__KeyValue * msg)
{
  if (!msg) {
    return;
  }
  rosidl_runtime_c__String__fini(&msg->key);
  rosidl_runtime_c__String__fini(&msg->value);
}

type_description_interfaces__msg__KeyValue * type_description_interfaces__msg__KeyValue__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  type_description_interfaces__msg__KeyValue * msg = (type_description_interfaces__msg__KeyValue *)allocator.allocate(
    sizeof(type_description_interfaces__msg__KeyValue), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!type_description_interfaces__msg__KeyValue__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void type_description_interfaces__msg__KeyValue__destroy(type_description_interfaces__msg__KeyValue * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  type_description_interfaces__msg__KeyValue__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool type_description_interfaces__msg__KeyValue__Sequence__init(
  type_description_interfaces__msg__KeyValue__Sequence * array, size_t size)
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

  array->data = (type_description_interfaces__msg__KeyValue *)allocator.zero_allocate(
    size, sizeof(type_description_interfaces__msg__KeyValue), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!type_description_interfaces__msg__KeyValue__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        type_description_interfaces__msg__KeyValue__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void type_description_interfaces__msg__KeyValue__Sequence__fini(
  type_description_interfaces__msg__KeyValue__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    type_description_interfaces__msg__KeyValue__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
