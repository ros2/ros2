// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// statistics_msgs/msg/StatisticDataType functions

#include "statistics_msgs/msg/statistic_data_type.h"
#include "rcutils/allocator.h"
#include <string.h>

bool statistics_msgs__msg__StatisticDataType__init(statistics_msgs__msg__StatisticDataType * msg)
{
  if (!msg) {
    return false;
  }
  msg->structure_needs_at_least_one_member = 0;
  return true;
}

void statistics_msgs__msg__StatisticDataType__fini(statistics_msgs__msg__StatisticDataType * msg)
{
  (void)msg;
}

statistics_msgs__msg__StatisticDataType * statistics_msgs__msg__StatisticDataType__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  statistics_msgs__msg__StatisticDataType * msg = (statistics_msgs__msg__StatisticDataType *)allocator.allocate(
    sizeof(statistics_msgs__msg__StatisticDataType), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!statistics_msgs__msg__StatisticDataType__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void statistics_msgs__msg__StatisticDataType__destroy(statistics_msgs__msg__StatisticDataType * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  statistics_msgs__msg__StatisticDataType__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool statistics_msgs__msg__StatisticDataType__Sequence__init(
  statistics_msgs__msg__StatisticDataType__Sequence * array, size_t size)
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

  array->data = (statistics_msgs__msg__StatisticDataType *)allocator.zero_allocate(
    size, sizeof(statistics_msgs__msg__StatisticDataType), allocator.state);
  if (!array->data) {
    return false;
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void statistics_msgs__msg__StatisticDataType__Sequence__fini(
  statistics_msgs__msg__StatisticDataType__Sequence * array)
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
