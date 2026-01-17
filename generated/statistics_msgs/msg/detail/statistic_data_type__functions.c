// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from statistics_msgs:msg/StatisticDataType.idl
// generated code does not contain a copyright notice
#include "statistics_msgs/msg/detail/statistic_data_type__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
statistics_msgs__msg__StatisticDataType__init(statistics_msgs__msg__StatisticDataType * msg)
{
  if (!msg) {
    return false;
  }
  // structure_needs_at_least_one_member
  return true;
}

void
statistics_msgs__msg__StatisticDataType__fini(statistics_msgs__msg__StatisticDataType * msg)
{
  if (!msg) {
    return;
  }
  // structure_needs_at_least_one_member
}

bool
statistics_msgs__msg__StatisticDataType__are_equal(const statistics_msgs__msg__StatisticDataType * lhs, const statistics_msgs__msg__StatisticDataType * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // structure_needs_at_least_one_member
  if (lhs->structure_needs_at_least_one_member != rhs->structure_needs_at_least_one_member) {
    return false;
  }
  return true;
}

bool
statistics_msgs__msg__StatisticDataType__copy(
  const statistics_msgs__msg__StatisticDataType * input,
  statistics_msgs__msg__StatisticDataType * output)
{
  if (!input || !output) {
    return false;
  }
  // structure_needs_at_least_one_member
  output->structure_needs_at_least_one_member = input->structure_needs_at_least_one_member;
  return true;
}

statistics_msgs__msg__StatisticDataType *
statistics_msgs__msg__StatisticDataType__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  statistics_msgs__msg__StatisticDataType * msg = (statistics_msgs__msg__StatisticDataType *)allocator.allocate(sizeof(statistics_msgs__msg__StatisticDataType), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(statistics_msgs__msg__StatisticDataType));
  bool success = statistics_msgs__msg__StatisticDataType__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
statistics_msgs__msg__StatisticDataType__destroy(statistics_msgs__msg__StatisticDataType * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    statistics_msgs__msg__StatisticDataType__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
statistics_msgs__msg__StatisticDataType__Sequence__init(statistics_msgs__msg__StatisticDataType__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  statistics_msgs__msg__StatisticDataType * data = NULL;

  if (size) {
    data = (statistics_msgs__msg__StatisticDataType *)allocator.zero_allocate(size, sizeof(statistics_msgs__msg__StatisticDataType), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = statistics_msgs__msg__StatisticDataType__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        statistics_msgs__msg__StatisticDataType__fini(&data[i - 1]);
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
statistics_msgs__msg__StatisticDataType__Sequence__fini(statistics_msgs__msg__StatisticDataType__Sequence * array)
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
      statistics_msgs__msg__StatisticDataType__fini(&array->data[i]);
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

statistics_msgs__msg__StatisticDataType__Sequence *
statistics_msgs__msg__StatisticDataType__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  statistics_msgs__msg__StatisticDataType__Sequence * array = (statistics_msgs__msg__StatisticDataType__Sequence *)allocator.allocate(sizeof(statistics_msgs__msg__StatisticDataType__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = statistics_msgs__msg__StatisticDataType__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
statistics_msgs__msg__StatisticDataType__Sequence__destroy(statistics_msgs__msg__StatisticDataType__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    statistics_msgs__msg__StatisticDataType__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
statistics_msgs__msg__StatisticDataType__Sequence__are_equal(const statistics_msgs__msg__StatisticDataType__Sequence * lhs, const statistics_msgs__msg__StatisticDataType__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!statistics_msgs__msg__StatisticDataType__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
statistics_msgs__msg__StatisticDataType__Sequence__copy(
  const statistics_msgs__msg__StatisticDataType__Sequence * input,
  statistics_msgs__msg__StatisticDataType__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(statistics_msgs__msg__StatisticDataType);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    statistics_msgs__msg__StatisticDataType * data =
      (statistics_msgs__msg__StatisticDataType *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!statistics_msgs__msg__StatisticDataType__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          statistics_msgs__msg__StatisticDataType__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!statistics_msgs__msg__StatisticDataType__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
