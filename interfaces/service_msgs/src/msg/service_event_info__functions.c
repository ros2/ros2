// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// service_msgs/msg/ServiceEventInfo functions

#include "service_msgs/msg/service_event_info.h"
#include "rcutils/allocator.h"
#include <string.h>

bool service_msgs__msg__ServiceEventInfo__init(service_msgs__msg__ServiceEventInfo * msg)
{
  if (!msg) {
    return false;
  }
  msg->event_type = 0;
  builtin_interfaces__msg__Time__init(&msg->stamp);
  memset(msg->client_gid, 0, sizeof(msg->client_gid));
  msg->sequence_number = 0;
  return true;
}

void service_msgs__msg__ServiceEventInfo__fini(service_msgs__msg__ServiceEventInfo * msg)
{
  if (!msg) {
    return;
  }
  builtin_interfaces__msg__Time__fini(&msg->stamp);
}

service_msgs__msg__ServiceEventInfo * service_msgs__msg__ServiceEventInfo__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  service_msgs__msg__ServiceEventInfo * msg = (service_msgs__msg__ServiceEventInfo *)allocator.allocate(
    sizeof(service_msgs__msg__ServiceEventInfo), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!service_msgs__msg__ServiceEventInfo__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void service_msgs__msg__ServiceEventInfo__destroy(service_msgs__msg__ServiceEventInfo * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  service_msgs__msg__ServiceEventInfo__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool service_msgs__msg__ServiceEventInfo__Sequence__init(
  service_msgs__msg__ServiceEventInfo__Sequence * array, size_t size)
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

  array->data = (service_msgs__msg__ServiceEventInfo *)allocator.zero_allocate(
    size, sizeof(service_msgs__msg__ServiceEventInfo), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!service_msgs__msg__ServiceEventInfo__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        service_msgs__msg__ServiceEventInfo__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void service_msgs__msg__ServiceEventInfo__Sequence__fini(
  service_msgs__msg__ServiceEventInfo__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    service_msgs__msg__ServiceEventInfo__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
