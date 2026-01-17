// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// builtin_interfaces/msg/Duration functions implementation

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "builtin_interfaces/msg/duration.h"
#include "rcutils/allocator.h"

bool builtin_interfaces__msg__Duration__init(builtin_interfaces__msg__Duration * msg)
{
  if (!msg) {
    return false;
  }
  msg->sec = 0;
  msg->nanosec = 0;
  return true;
}

void builtin_interfaces__msg__Duration__fini(builtin_interfaces__msg__Duration * msg)
{
  if (!msg) {
    return;
  }
  // No dynamic memory to free for primitive types
}

builtin_interfaces__msg__Duration * builtin_interfaces__msg__Duration__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  builtin_interfaces__msg__Duration * msg =
    (builtin_interfaces__msg__Duration *)allocator.allocate(
      sizeof(builtin_interfaces__msg__Duration), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!builtin_interfaces__msg__Duration__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void builtin_interfaces__msg__Duration__destroy(builtin_interfaces__msg__Duration * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  builtin_interfaces__msg__Duration__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool builtin_interfaces__msg__Duration__are_equal(
  const builtin_interfaces__msg__Duration * lhs,
  const builtin_interfaces__msg__Duration * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->sec != rhs->sec) {
    return false;
  }
  if (lhs->nanosec != rhs->nanosec) {
    return false;
  }
  return true;
}

bool builtin_interfaces__msg__Duration__copy(
  const builtin_interfaces__msg__Duration * input,
  builtin_interfaces__msg__Duration * output)
{
  if (!input || !output) {
    return false;
  }
  output->sec = input->sec;
  output->nanosec = input->nanosec;
  return true;
}

bool builtin_interfaces__msg__Duration__Sequence__init(
  builtin_interfaces__msg__Duration__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  builtin_interfaces__msg__Duration * data = NULL;

  if (size) {
    data = (builtin_interfaces__msg__Duration *)allocator.zero_allocate(
      size, sizeof(builtin_interfaces__msg__Duration), allocator.state);
    if (!data) {
      return false;
    }
    for (size_t i = 0; i < size; ++i) {
      if (!builtin_interfaces__msg__Duration__init(&data[i])) {
        for (size_t j = 0; j < i; ++j) {
          builtin_interfaces__msg__Duration__fini(&data[j]);
        }
        allocator.deallocate(data, allocator.state);
        return false;
      }
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void builtin_interfaces__msg__Duration__Sequence__fini(
  builtin_interfaces__msg__Duration__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array->data) {
    for (size_t i = 0; i < array->size; ++i) {
      builtin_interfaces__msg__Duration__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  }
}

builtin_interfaces__msg__Duration__Sequence *
builtin_interfaces__msg__Duration__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  builtin_interfaces__msg__Duration__Sequence * array =
    (builtin_interfaces__msg__Duration__Sequence *)allocator.allocate(
      sizeof(builtin_interfaces__msg__Duration__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  if (!builtin_interfaces__msg__Duration__Sequence__init(array, size)) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void builtin_interfaces__msg__Duration__Sequence__destroy(
  builtin_interfaces__msg__Duration__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  builtin_interfaces__msg__Duration__Sequence__fini(array);
  allocator.deallocate(array, allocator.state);
}

bool builtin_interfaces__msg__Duration__Sequence__are_equal(
  const builtin_interfaces__msg__Duration__Sequence * lhs,
  const builtin_interfaces__msg__Duration__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!builtin_interfaces__msg__Duration__are_equal(&lhs->data[i], &rhs->data[i])) {
      return false;
    }
  }
  return true;
}

bool builtin_interfaces__msg__Duration__Sequence__copy(
  const builtin_interfaces__msg__Duration__Sequence * input,
  builtin_interfaces__msg__Duration__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    builtin_interfaces__msg__Duration__Sequence__fini(output);
    if (!builtin_interfaces__msg__Duration__Sequence__init(output, input->size)) {
      return false;
    }
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!builtin_interfaces__msg__Duration__copy(&input->data[i], &output->data[i])) {
      return false;
    }
  }
  return true;
}
