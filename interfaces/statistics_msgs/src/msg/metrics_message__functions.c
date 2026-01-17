// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// statistics_msgs/msg/MetricsMessage functions

#include "statistics_msgs/msg/metrics_message.h"
#include "rcutils/allocator.h"
#include <string.h>

bool statistics_msgs__msg__MetricsMessage__init(statistics_msgs__msg__MetricsMessage * msg)
{
  if (!msg) {
    return false;
  }
  rosidl_runtime_c__String__init(&msg->measurement_source_name);
  rosidl_runtime_c__String__init(&msg->metrics_source);
  rosidl_runtime_c__String__init(&msg->unit);
  if (!builtin_interfaces__msg__Time__init(&msg->window_start)) {
    return false;
  }
  if (!builtin_interfaces__msg__Time__init(&msg->window_stop)) {
    builtin_interfaces__msg__Time__fini(&msg->window_start);
    return false;
  }
  msg->statistics.data = NULL;
  msg->statistics.size = 0;
  msg->statistics.capacity = 0;
  return true;
}

void statistics_msgs__msg__MetricsMessage__fini(statistics_msgs__msg__MetricsMessage * msg)
{
  if (!msg) {
    return;
  }
  rosidl_runtime_c__String__fini(&msg->measurement_source_name);
  rosidl_runtime_c__String__fini(&msg->metrics_source);
  rosidl_runtime_c__String__fini(&msg->unit);
  builtin_interfaces__msg__Time__fini(&msg->window_start);
  builtin_interfaces__msg__Time__fini(&msg->window_stop);
  statistics_msgs__msg__StatisticDataPoint__Sequence__fini(&msg->statistics);
}

statistics_msgs__msg__MetricsMessage * statistics_msgs__msg__MetricsMessage__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  statistics_msgs__msg__MetricsMessage * msg = (statistics_msgs__msg__MetricsMessage *)allocator.allocate(
    sizeof(statistics_msgs__msg__MetricsMessage), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!statistics_msgs__msg__MetricsMessage__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void statistics_msgs__msg__MetricsMessage__destroy(statistics_msgs__msg__MetricsMessage * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  statistics_msgs__msg__MetricsMessage__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool statistics_msgs__msg__MetricsMessage__Sequence__init(
  statistics_msgs__msg__MetricsMessage__Sequence * array, size_t size)
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

  array->data = (statistics_msgs__msg__MetricsMessage *)allocator.zero_allocate(
    size, sizeof(statistics_msgs__msg__MetricsMessage), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!statistics_msgs__msg__MetricsMessage__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        statistics_msgs__msg__MetricsMessage__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void statistics_msgs__msg__MetricsMessage__Sequence__fini(
  statistics_msgs__msg__MetricsMessage__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    statistics_msgs__msg__MetricsMessage__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
