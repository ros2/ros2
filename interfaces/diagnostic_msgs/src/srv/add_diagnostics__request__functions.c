// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// diagnostic_msgs/srv/AddDiagnostics_Request functions

#include "diagnostic_msgs/srv/add_diagnostics__request.h"
#include "rcutils/allocator.h"
#include <string.h>

bool diagnostic_msgs__srv__AddDiagnostics_Request__init(diagnostic_msgs__srv__AddDiagnostics_Request * msg)
{
  if (!msg) {
    return false;
  }
  memset(msg, 0, sizeof(*msg));
  rosidl_runtime_c__String__init(&msg->load_namespace);
  return true;
}

void diagnostic_msgs__srv__AddDiagnostics_Request__fini(diagnostic_msgs__srv__AddDiagnostics_Request * msg)
{
  if (!msg) {
    return;
  }
  rosidl_runtime_c__String__fini(&msg->load_namespace);
}

diagnostic_msgs__srv__AddDiagnostics_Request * diagnostic_msgs__srv__AddDiagnostics_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  diagnostic_msgs__srv__AddDiagnostics_Request * msg = (diagnostic_msgs__srv__AddDiagnostics_Request *)allocator.allocate(
    sizeof(diagnostic_msgs__srv__AddDiagnostics_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!diagnostic_msgs__srv__AddDiagnostics_Request__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void diagnostic_msgs__srv__AddDiagnostics_Request__destroy(diagnostic_msgs__srv__AddDiagnostics_Request * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  diagnostic_msgs__srv__AddDiagnostics_Request__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool diagnostic_msgs__srv__AddDiagnostics_Request__Sequence__init(
  diagnostic_msgs__srv__AddDiagnostics_Request__Sequence * array, size_t size)
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

  array->data = (diagnostic_msgs__srv__AddDiagnostics_Request *)allocator.zero_allocate(
    size, sizeof(diagnostic_msgs__srv__AddDiagnostics_Request), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!diagnostic_msgs__srv__AddDiagnostics_Request__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        diagnostic_msgs__srv__AddDiagnostics_Request__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void diagnostic_msgs__srv__AddDiagnostics_Request__Sequence__fini(
  diagnostic_msgs__srv__AddDiagnostics_Request__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    diagnostic_msgs__srv__AddDiagnostics_Request__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
