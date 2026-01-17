// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// diagnostic_msgs/msg/DiagnosticArray functions

#include "diagnostic_msgs/msg/diagnostic_array.h"
#include "rcutils/allocator.h"
#include <string.h>

bool diagnostic_msgs__msg__DiagnosticArray__init(diagnostic_msgs__msg__DiagnosticArray * msg)
{
  if (!msg) {
    return false;
  }
  memset(msg, 0, sizeof(*msg));
  std_msgs__msg__Header__init(&msg->header);
  diagnostic_msgs__msg__DiagnosticStatus__Sequence__init(&msg->status, 0);
  return true;
}

void diagnostic_msgs__msg__DiagnosticArray__fini(diagnostic_msgs__msg__DiagnosticArray * msg)
{
  if (!msg) {
    return;
  }
  std_msgs__msg__Header__fini(&msg->header);
  diagnostic_msgs__msg__DiagnosticStatus__Sequence__fini(&msg->status);
}

diagnostic_msgs__msg__DiagnosticArray * diagnostic_msgs__msg__DiagnosticArray__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  diagnostic_msgs__msg__DiagnosticArray * msg = (diagnostic_msgs__msg__DiagnosticArray *)allocator.allocate(
    sizeof(diagnostic_msgs__msg__DiagnosticArray), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!diagnostic_msgs__msg__DiagnosticArray__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void diagnostic_msgs__msg__DiagnosticArray__destroy(diagnostic_msgs__msg__DiagnosticArray * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  diagnostic_msgs__msg__DiagnosticArray__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool diagnostic_msgs__msg__DiagnosticArray__Sequence__init(
  diagnostic_msgs__msg__DiagnosticArray__Sequence * array, size_t size)
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

  array->data = (diagnostic_msgs__msg__DiagnosticArray *)allocator.zero_allocate(
    size, sizeof(diagnostic_msgs__msg__DiagnosticArray), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!diagnostic_msgs__msg__DiagnosticArray__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        diagnostic_msgs__msg__DiagnosticArray__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void diagnostic_msgs__msg__DiagnosticArray__Sequence__fini(
  diagnostic_msgs__msg__DiagnosticArray__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    diagnostic_msgs__msg__DiagnosticArray__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
