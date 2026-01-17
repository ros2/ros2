// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from statistics_msgs:msg/StatisticDataPoint.idl
// generated code does not contain a copyright notice
#include "statistics_msgs/msg/detail/statistic_data_point__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
statistics_msgs__msg__StatisticDataPoint__init(statistics_msgs__msg__StatisticDataPoint * msg)
{
  if (!msg) {
    return false;
  }
  // data_type
  // data
  return true;
}

void
statistics_msgs__msg__StatisticDataPoint__fini(statistics_msgs__msg__StatisticDataPoint * msg)
{
  if (!msg) {
    return;
  }
  // data_type
  // data
}

bool
statistics_msgs__msg__StatisticDataPoint__are_equal(const statistics_msgs__msg__StatisticDataPoint * lhs, const statistics_msgs__msg__StatisticDataPoint * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // data_type
  if (lhs->data_type != rhs->data_type) {
    return false;
  }
  // data
  if (lhs->data != rhs->data) {
    return false;
  }
  return true;
}

bool
statistics_msgs__msg__StatisticDataPoint__copy(
  const statistics_msgs__msg__StatisticDataPoint * input,
  statistics_msgs__msg__StatisticDataPoint * output)
{
  if (!input || !output) {
    return false;
  }
  // data_type
  output->data_type = input->data_type;
  // data
  output->data = input->data;
  return true;
}

statistics_msgs__msg__StatisticDataPoint *
statistics_msgs__msg__StatisticDataPoint__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  statistics_msgs__msg__StatisticDataPoint * msg = (statistics_msgs__msg__StatisticDataPoint *)allocator.allocate(sizeof(statistics_msgs__msg__StatisticDataPoint), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(statistics_msgs__msg__StatisticDataPoint));
  bool success = statistics_msgs__msg__StatisticDataPoint__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
statistics_msgs__msg__StatisticDataPoint__destroy(statistics_msgs__msg__StatisticDataPoint * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    statistics_msgs__msg__StatisticDataPoint__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
statistics_msgs__msg__StatisticDataPoint__Sequence__init(statistics_msgs__msg__StatisticDataPoint__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  statistics_msgs__msg__StatisticDataPoint * data = NULL;

  if (size) {
    data = (statistics_msgs__msg__StatisticDataPoint *)allocator.zero_allocate(size, sizeof(statistics_msgs__msg__StatisticDataPoint), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = statistics_msgs__msg__StatisticDataPoint__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        statistics_msgs__msg__StatisticDataPoint__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
statistics_msgs__msg__StatisticDataPoint__Sequence__fini(statistics_msgs__msg__StatisticDataPoint__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      statistics_msgs__msg__StatisticDataPoint__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

statistics_msgs__msg__StatisticDataPoint__Sequence *
statistics_msgs__msg__StatisticDataPoint__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  statistics_msgs__msg__StatisticDataPoint__Sequence * array = (statistics_msgs__msg__StatisticDataPoint__Sequence *)allocator.allocate(sizeof(statistics_msgs__msg__StatisticDataPoint__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = statistics_msgs__msg__StatisticDataPoint__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
statistics_msgs__msg__StatisticDataPoint__Sequence__destroy(statistics_msgs__msg__StatisticDataPoint__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    statistics_msgs__msg__StatisticDataPoint__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
statistics_msgs__msg__StatisticDataPoint__Sequence__are_equal(const statistics_msgs__msg__StatisticDataPoint__Sequence * lhs, const statistics_msgs__msg__StatisticDataPoint__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!statistics_msgs__msg__StatisticDataPoint__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
statistics_msgs__msg__StatisticDataPoint__Sequence__copy(
  const statistics_msgs__msg__StatisticDataPoint__Sequence * input,
  statistics_msgs__msg__StatisticDataPoint__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(statistics_msgs__msg__StatisticDataPoint);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    statistics_msgs__msg__StatisticDataPoint * data =
      (statistics_msgs__msg__StatisticDataPoint *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!statistics_msgs__msg__StatisticDataPoint__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          statistics_msgs__msg__StatisticDataPoint__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!statistics_msgs__msg__StatisticDataPoint__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
