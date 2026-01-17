// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// stereo_msgs/msg/DisparityImage functions

#include "stereo_msgs/msg/disparity_image.h"
#include "rcutils/allocator.h"
#include <string.h>

bool stereo_msgs__msg__DisparityImage__init(stereo_msgs__msg__DisparityImage * msg)
{
  if (!msg) {
    return false;
  }
  // Initialize header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    return false;
  }
  // Initialize image
  if (!sensor_msgs__msg__Image__init(&msg->image)) {
    std_msgs__msg__Header__fini(&msg->header);
    return false;
  }
  // Initialize valid_window
  if (!sensor_msgs__msg__RegionOfInterest__init(&msg->valid_window)) {
    sensor_msgs__msg__Image__fini(&msg->image);
    std_msgs__msg__Header__fini(&msg->header);
    return false;
  }
  // Initialize primitive fields
  msg->f = 0.0f;
  msg->t = 0.0f;
  msg->delta_d = 0.0f;
  msg->min_disparity = 0.0f;
  msg->max_disparity = 0.0f;
  return true;
}

void stereo_msgs__msg__DisparityImage__fini(stereo_msgs__msg__DisparityImage * msg)
{
  if (!msg) {
    return;
  }
  std_msgs__msg__Header__fini(&msg->header);
  sensor_msgs__msg__Image__fini(&msg->image);
  sensor_msgs__msg__RegionOfInterest__fini(&msg->valid_window);
}

stereo_msgs__msg__DisparityImage * stereo_msgs__msg__DisparityImage__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  stereo_msgs__msg__DisparityImage * msg = (stereo_msgs__msg__DisparityImage *)allocator.allocate(
    sizeof(stereo_msgs__msg__DisparityImage), allocator.state);
  if (!msg) {
    return NULL;
  }
  if (!stereo_msgs__msg__DisparityImage__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void stereo_msgs__msg__DisparityImage__destroy(stereo_msgs__msg__DisparityImage * msg)
{
  if (!msg) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  stereo_msgs__msg__DisparityImage__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool stereo_msgs__msg__DisparityImage__Sequence__init(
  stereo_msgs__msg__DisparityImage__Sequence * array, size_t size)
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

  array->data = (stereo_msgs__msg__DisparityImage *)allocator.zero_allocate(
    size, sizeof(stereo_msgs__msg__DisparityImage), allocator.state);
  if (!array->data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    if (!stereo_msgs__msg__DisparityImage__init(&array->data[i])) {
      for (size_t j = 0; j < i; ++j) {
        stereo_msgs__msg__DisparityImage__fini(&array->data[j]);
      }
      allocator.deallocate(array->data, allocator.state);
      return false;
    }
  }

  array->size = size;
  array->capacity = size;
  return true;
}

void stereo_msgs__msg__DisparityImage__Sequence__fini(
  stereo_msgs__msg__DisparityImage__Sequence * array)
{
  if (!array || !array->data) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  for (size_t i = 0; i < array->size; ++i) {
    stereo_msgs__msg__DisparityImage__fini(&array->data[i]);
  }
  allocator.deallocate(array->data, allocator.state);
  array->data = NULL;
  array->size = 0;
  array->capacity = 0;
}
