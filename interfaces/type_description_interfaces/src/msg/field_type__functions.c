// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// type_description_interfaces/msg/FieldType functions

#include "type_description_interfaces/msg/field_type.h"
#include "rcutils/allocator.h"
#include <string.h>

bool type_description_interfaces__msg__FieldType__init(type_description_interfaces__msg__FieldType * msg)
{
  if (!msg) {
    return false;
  }
  msg->type_id = 0;
  msg->capacity = 0;
  msg->string_capacity = 0;
  rosidl_runtime_c__String__init(&msg->nested_type_name);
  return true;
}

void type_description_interfaces__msg__FieldType__fini(type_description_interfaces__msg__FieldType * msg)
{
  if (!msg) {
    return;
  }
  rosidl_runtime_c__String__fini(&msg->nested_type_name);
}

type_description_interfaces__msg__FieldType * type_description_interfaces__msg__FieldType__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  type_description_interfaces__msg__FieldType * msg = (type_description_interfaces__msg__FieldType *)allocator.allocate(
    sizeof(type_description_interfaces__msg__FieldType), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!type_description_interfaces__msg__FieldType__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void type_description_interfaces__msg__FieldType__destroy(type_description_interfaces__msg__FieldType * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  type_description_interfaces__msg__FieldType__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool type_description_interfaces__msg__FieldType__Sequence__init(
  type_description_interfaces__msg__FieldType__Sequence * array, size_t size)
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

  array->data = (type_description_interfaces__msg__FieldType *)allocator.zero_allocate(
    size, sizeof(type_description_interfaces__msg__FieldType), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!type_description_interfaces__msg__FieldType__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        type_description_interfaces__msg__FieldType__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void type_description_interfaces__msg__FieldType__Sequence__fini(
  type_description_interfaces__msg__FieldType__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    type_description_interfaces__msg__FieldType__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
