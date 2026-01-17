// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// tf2_msgs/srv/FrameGraph_Response functions

#include "tf2_msgs/srv/frame_graph__response.h"
#include "rcutils/allocator.h"
#include <string.h>

bool tf2_msgs__srv__FrameGraph_Response__init(tf2_msgs__srv__FrameGraph_Response * msg)
{
  if (!msg) {
    return false;
  }
  memset(msg, 0, sizeof(*msg));
  rosidl_runtime_c__String__init(&msg->frame_yaml);
  return true;
}

void tf2_msgs__srv__FrameGraph_Response__fini(tf2_msgs__srv__FrameGraph_Response * msg)
{
  if (!msg) {
    return;
  }
  rosidl_runtime_c__String__fini(&msg->frame_yaml);
}

tf2_msgs__srv__FrameGraph_Response * tf2_msgs__srv__FrameGraph_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  tf2_msgs__srv__FrameGraph_Response * msg = (tf2_msgs__srv__FrameGraph_Response *)allocator.allocate(
    sizeof(tf2_msgs__srv__FrameGraph_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!tf2_msgs__srv__FrameGraph_Response__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void tf2_msgs__srv__FrameGraph_Response__destroy(tf2_msgs__srv__FrameGraph_Response * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  tf2_msgs__srv__FrameGraph_Response__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool tf2_msgs__srv__FrameGraph_Response__Sequence__init(
  tf2_msgs__srv__FrameGraph_Response__Sequence * array, size_t size)
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

  array->data = (tf2_msgs__srv__FrameGraph_Response *)allocator.zero_allocate(
    size, sizeof(tf2_msgs__srv__FrameGraph_Response), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!tf2_msgs__srv__FrameGraph_Response__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        tf2_msgs__srv__FrameGraph_Response__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void tf2_msgs__srv__FrameGraph_Response__Sequence__fini(
  tf2_msgs__srv__FrameGraph_Response__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    tf2_msgs__srv__FrameGraph_Response__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
