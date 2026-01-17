// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// type_description_interfaces/msg/TypeDescription functions

#include "type_description_interfaces/msg/type_description.h"
#include "rcutils/allocator.h"
#include <string.h>

bool type_description_interfaces__msg__TypeDescription__init(type_description_interfaces__msg__TypeDescription * msg)
{
  if (!msg) {
    return false;
  }
  if (!type_description_interfaces__msg__IndividualTypeDescription__init(&msg->type_description)) {
    return false;
  }
  msg->referenced_type_descriptions.data = NULL;
  msg->referenced_type_descriptions.size = 0;
  msg->referenced_type_descriptions.capacity = 0;
  return true;
}

void type_description_interfaces__msg__TypeDescription__fini(type_description_interfaces__msg__TypeDescription * msg)
{
  if (!msg) {
    return;
  }
  type_description_interfaces__msg__IndividualTypeDescription__fini(&msg->type_description);
  type_description_interfaces__msg__IndividualTypeDescription__Sequence__fini(&msg->referenced_type_descriptions);
}

type_description_interfaces__msg__TypeDescription * type_description_interfaces__msg__TypeDescription__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  type_description_interfaces__msg__TypeDescription * msg = (type_description_interfaces__msg__TypeDescription *)allocator.allocate(
    sizeof(type_description_interfaces__msg__TypeDescription), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!type_description_interfaces__msg__TypeDescription__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void type_description_interfaces__msg__TypeDescription__destroy(type_description_interfaces__msg__TypeDescription * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  type_description_interfaces__msg__TypeDescription__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool type_description_interfaces__msg__TypeDescription__Sequence__init(
  type_description_interfaces__msg__TypeDescription__Sequence * array, size_t size)
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

  array->data = (type_description_interfaces__msg__TypeDescription *)allocator.zero_allocate(
    size, sizeof(type_description_interfaces__msg__TypeDescription), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!type_description_interfaces__msg__TypeDescription__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        type_description_interfaces__msg__TypeDescription__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void type_description_interfaces__msg__TypeDescription__Sequence__fini(
  type_description_interfaces__msg__TypeDescription__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    type_description_interfaces__msg__TypeDescription__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
