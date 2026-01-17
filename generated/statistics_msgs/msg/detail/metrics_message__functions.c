// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from statistics_msgs:msg/MetricsMessage.idl
// generated code does not contain a copyright notice
#include "statistics_msgs/msg/detail/metrics_message__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `measurement_source_name`
// Member `metrics_source`
// Member `unit`
#include "rosidl_runtime_c/string_functions.h"
// Member `window_start`
// Member `window_stop`
#include "builtin_interfaces/msg/detail/time__functions.h"
// Member `statistics`
#include "statistics_msgs/msg/detail/statistic_data_point__functions.h"

bool
statistics_msgs__msg__MetricsMessage__init(statistics_msgs__msg__MetricsMessage * msg)
{
  if (!msg) {
    return false;
  }
  // measurement_source_name
  if (!rosidl_runtime_c__String__init(&msg->measurement_source_name)) {
    statistics_msgs__msg__MetricsMessage__fini(msg);
    return false;
  }
  // metrics_source
  if (!rosidl_runtime_c__String__init(&msg->metrics_source)) {
    statistics_msgs__msg__MetricsMessage__fini(msg);
    return false;
  }
  // unit
  if (!rosidl_runtime_c__String__init(&msg->unit)) {
    statistics_msgs__msg__MetricsMessage__fini(msg);
    return false;
  }
  // window_start
  if (!builtin_interfaces__msg__Time__init(&msg->window_start)) {
    statistics_msgs__msg__MetricsMessage__fini(msg);
    return false;
  }
  // window_stop
  if (!builtin_interfaces__msg__Time__init(&msg->window_stop)) {
    statistics_msgs__msg__MetricsMessage__fini(msg);
    return false;
  }
  // statistics
  if (!statistics_msgs__msg__StatisticDataPoint__Sequence__init(&msg->statistics, 0)) {
    statistics_msgs__msg__MetricsMessage__fini(msg);
    return false;
  }
  return true;
}

void
statistics_msgs__msg__MetricsMessage__fini(statistics_msgs__msg__MetricsMessage * msg)
{
  if (!msg) {
    return;
  }
  // measurement_source_name
  rosidl_runtime_c__String__fini(&msg->measurement_source_name);
  // metrics_source
  rosidl_runtime_c__String__fini(&msg->metrics_source);
  // unit
  rosidl_runtime_c__String__fini(&msg->unit);
  // window_start
  builtin_interfaces__msg__Time__fini(&msg->window_start);
  // window_stop
  builtin_interfaces__msg__Time__fini(&msg->window_stop);
  // statistics
  statistics_msgs__msg__StatisticDataPoint__Sequence__fini(&msg->statistics);
}

bool
statistics_msgs__msg__MetricsMessage__are_equal(const statistics_msgs__msg__MetricsMessage * lhs, const statistics_msgs__msg__MetricsMessage * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // measurement_source_name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->measurement_source_name), &(rhs->measurement_source_name)))
  {
    return false;
  }
  // metrics_source
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->metrics_source), &(rhs->metrics_source)))
  {
    return false;
  }
  // unit
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->unit), &(rhs->unit)))
  {
    return false;
  }
  // window_start
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->window_start), &(rhs->window_start)))
  {
    return false;
  }
  // window_stop
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->window_stop), &(rhs->window_stop)))
  {
    return false;
  }
  // statistics
  if (!statistics_msgs__msg__StatisticDataPoint__Sequence__are_equal(
      &(lhs->statistics), &(rhs->statistics)))
  {
    return false;
  }
  return true;
}

bool
statistics_msgs__msg__MetricsMessage__copy(
  const statistics_msgs__msg__MetricsMessage * input,
  statistics_msgs__msg__MetricsMessage * output)
{
  if (!input || !output) {
    return false;
  }
  // measurement_source_name
  if (!rosidl_runtime_c__String__copy(
      &(input->measurement_source_name), &(output->measurement_source_name)))
  {
    return false;
  }
  // metrics_source
  if (!rosidl_runtime_c__String__copy(
      &(input->metrics_source), &(output->metrics_source)))
  {
    return false;
  }
  // unit
  if (!rosidl_runtime_c__String__copy(
      &(input->unit), &(output->unit)))
  {
    return false;
  }
  // window_start
  if (!builtin_interfaces__msg__Time__copy(
      &(input->window_start), &(output->window_start)))
  {
    return false;
  }
  // window_stop
  if (!builtin_interfaces__msg__Time__copy(
      &(input->window_stop), &(output->window_stop)))
  {
    return false;
  }
  // statistics
  if (!statistics_msgs__msg__StatisticDataPoint__Sequence__copy(
      &(input->statistics), &(output->statistics)))
  {
    return false;
  }
  return true;
}

statistics_msgs__msg__MetricsMessage *
statistics_msgs__msg__MetricsMessage__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  statistics_msgs__msg__MetricsMessage * msg = (statistics_msgs__msg__MetricsMessage *)allocator.allocate(sizeof(statistics_msgs__msg__MetricsMessage), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(statistics_msgs__msg__MetricsMessage));
  bool success = statistics_msgs__msg__MetricsMessage__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
statistics_msgs__msg__MetricsMessage__destroy(statistics_msgs__msg__MetricsMessage * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    statistics_msgs__msg__MetricsMessage__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
statistics_msgs__msg__MetricsMessage__Sequence__init(statistics_msgs__msg__MetricsMessage__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  statistics_msgs__msg__MetricsMessage * data = NULL;

  if (size) {
    data = (statistics_msgs__msg__MetricsMessage *)allocator.zero_allocate(size, sizeof(statistics_msgs__msg__MetricsMessage), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = statistics_msgs__msg__MetricsMessage__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        statistics_msgs__msg__MetricsMessage__fini(&data[i - 1]);
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
statistics_msgs__msg__MetricsMessage__Sequence__fini(statistics_msgs__msg__MetricsMessage__Sequence * array)
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
      statistics_msgs__msg__MetricsMessage__fini(&array->data[i]);
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

statistics_msgs__msg__MetricsMessage__Sequence *
statistics_msgs__msg__MetricsMessage__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  statistics_msgs__msg__MetricsMessage__Sequence * array = (statistics_msgs__msg__MetricsMessage__Sequence *)allocator.allocate(sizeof(statistics_msgs__msg__MetricsMessage__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = statistics_msgs__msg__MetricsMessage__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
statistics_msgs__msg__MetricsMessage__Sequence__destroy(statistics_msgs__msg__MetricsMessage__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    statistics_msgs__msg__MetricsMessage__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
statistics_msgs__msg__MetricsMessage__Sequence__are_equal(const statistics_msgs__msg__MetricsMessage__Sequence * lhs, const statistics_msgs__msg__MetricsMessage__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!statistics_msgs__msg__MetricsMessage__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
statistics_msgs__msg__MetricsMessage__Sequence__copy(
  const statistics_msgs__msg__MetricsMessage__Sequence * input,
  statistics_msgs__msg__MetricsMessage__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(statistics_msgs__msg__MetricsMessage);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    statistics_msgs__msg__MetricsMessage * data =
      (statistics_msgs__msg__MetricsMessage *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!statistics_msgs__msg__MetricsMessage__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          statistics_msgs__msg__MetricsMessage__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!statistics_msgs__msg__MetricsMessage__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
