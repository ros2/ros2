// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// unique_identifier_msgs/msg/UUID functions

#include "unique_identifier_msgs/msg/uuid.h"
#include "rcutils/allocator.h"
#include <string.h>

bool unique_identifier_msgs__msg__UUID__init(unique_identifier_msgs__msg__UUID * msg)
{
  if (!msg) {
    return false;
  }
  memset(msg->uuid, 0, sizeof(msg->uuid));
  return true;
}

void unique_identifier_msgs__msg__UUID__fini(unique_identifier_msgs__msg__UUID * msg)
{
  if (!msg) {
    return;
  }
  // Nothing to finalize for fixed-size array
}

unique_identifier_msgs__msg__UUID * unique_identifier_msgs__msg__UUID__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  unique_identifier_msgs__msg__UUID * msg = (unique_identifier_msgs__msg__UUID *)allocator.allocate(
    sizeof(unique_identifier_msgs__msg__UUID), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!unique_identifier_msgs__msg__UUID__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void unique_identifier_msgs__msg__UUID__destroy(unique_identifier_msgs__msg__UUID * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  unique_identifier_msgs__msg__UUID__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool unique_identifier_msgs__msg__UUID__Sequence__init(
  unique_identifier_msgs__msg__UUID__Sequence * array, size_t size)
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

  array->data = (unique_identifier_msgs__msg__UUID *)allocator.zero_allocate(
    size, sizeof(unique_identifier_msgs__msg__UUID), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!unique_identifier_msgs__msg__UUID__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        unique_identifier_msgs__msg__UUID__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void unique_identifier_msgs__msg__UUID__Sequence__fini(
  unique_identifier_msgs__msg__UUID__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    unique_identifier_msgs__msg__UUID__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
