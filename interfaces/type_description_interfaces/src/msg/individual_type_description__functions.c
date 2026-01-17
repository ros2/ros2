// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// type_description_interfaces/msg/IndividualTypeDescription functions

#include "type_description_interfaces/msg/individual_type_description.h"
#include "rcutils/allocator.h"
#include <string.h>

bool type_description_interfaces__msg__IndividualTypeDescription__init(type_description_interfaces__msg__IndividualTypeDescription * msg)
{
  if (!msg) {
    return false;
  }
  rosidl_runtime_c__String__init(&msg->type_name);
  msg->fields.data = NULL;
  msg->fields.size = 0;
  msg->fields.capacity = 0;
  return true;
}

void type_description_interfaces__msg__IndividualTypeDescription__fini(type_description_interfaces__msg__IndividualTypeDescription * msg)
{
  if (!msg) {
    return;
  }
  rosidl_runtime_c__String__fini(&msg->type_name);
  type_description_interfaces__msg__Field__Sequence__fini(&msg->fields);
}

type_description_interfaces__msg__IndividualTypeDescription * type_description_interfaces__msg__IndividualTypeDescription__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  type_description_interfaces__msg__IndividualTypeDescription * msg = (type_description_interfaces__msg__IndividualTypeDescription *)allocator.allocate(
    sizeof(type_description_interfaces__msg__IndividualTypeDescription), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!type_description_interfaces__msg__IndividualTypeDescription__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void type_description_interfaces__msg__IndividualTypeDescription__destroy(type_description_interfaces__msg__IndividualTypeDescription * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  type_description_interfaces__msg__IndividualTypeDescription__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool type_description_interfaces__msg__IndividualTypeDescription__Sequence__init(
  type_description_interfaces__msg__IndividualTypeDescription__Sequence * array, size_t size)
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

  array->data = (type_description_interfaces__msg__IndividualTypeDescription *)allocator.zero_allocate(
    size, sizeof(type_description_interfaces__msg__IndividualTypeDescription), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!type_description_interfaces__msg__IndividualTypeDescription__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        type_description_interfaces__msg__IndividualTypeDescription__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void type_description_interfaces__msg__IndividualTypeDescription__Sequence__fini(
  type_description_interfaces__msg__IndividualTypeDescription__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    type_description_interfaces__msg__IndividualTypeDescription__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
