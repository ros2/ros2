// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// statistics_msgs/msg/StatisticDataPoint functions

#include "statistics_msgs/msg/statistic_data_point.h"
#include "rcutils/allocator.h"
#include <string.h>

bool statistics_msgs__msg__StatisticDataPoint__init(statistics_msgs__msg__StatisticDataPoint * msg)
{
  if (!msg) {
    return false;
  }
  msg->data_type = 0;
  msg->data = 0.0;
  return true;
}

void statistics_msgs__msg__StatisticDataPoint__fini(statistics_msgs__msg__StatisticDataPoint * msg)
{
  (void)msg;
}

statistics_msgs__msg__StatisticDataPoint * statistics_msgs__msg__StatisticDataPoint__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  statistics_msgs__msg__StatisticDataPoint * msg = (statistics_msgs__msg__StatisticDataPoint *)allocator.allocate(
    sizeof(statistics_msgs__msg__StatisticDataPoint), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!statistics_msgs__msg__StatisticDataPoint__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void statistics_msgs__msg__StatisticDataPoint__destroy(statistics_msgs__msg__StatisticDataPoint * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  statistics_msgs__msg__StatisticDataPoint__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool statistics_msgs__msg__StatisticDataPoint__Sequence__init(
  statistics_msgs__msg__StatisticDataPoint__Sequence * array, size_t size)
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

  array->data = (statistics_msgs__msg__StatisticDataPoint *)allocator.zero_allocate(
    size, sizeof(statistics_msgs__msg__StatisticDataPoint), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!statistics_msgs__msg__StatisticDataPoint__init(&array->data[i])) {
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void statistics_msgs__msg__StatisticDataPoint__Sequence__fini(
  statistics_msgs__msg__StatisticDataPoint__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
