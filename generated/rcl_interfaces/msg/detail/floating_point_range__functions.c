// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from rcl_interfaces:msg/FloatingPointRange.idl
// generated code does not contain a copyright notice
#include "rcl_interfaces/msg/detail/floating_point_range__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
rcl_interfaces__msg__FloatingPointRange__init(rcl_interfaces__msg__FloatingPointRange * msg)
{
  if (!msg) {
    return false;
  }
  // from_value
  // to_value
  // step
  return true;
}

void
rcl_interfaces__msg__FloatingPointRange__fini(rcl_interfaces__msg__FloatingPointRange * msg)
{
  if (!msg) {
    return;
  }
  // from_value
  // to_value
  // step
}

bool
rcl_interfaces__msg__FloatingPointRange__are_equal(const rcl_interfaces__msg__FloatingPointRange * lhs, const rcl_interfaces__msg__FloatingPointRange * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // from_value
  if (lhs->from_value != rhs->from_value) {
    return false;
  }
  // to_value
  if (lhs->to_value != rhs->to_value) {
    return false;
  }
  // step
  if (lhs->step != rhs->step) {
    return false;
  }
  return true;
}

bool
rcl_interfaces__msg__FloatingPointRange__copy(
  const rcl_interfaces__msg__FloatingPointRange * input,
  rcl_interfaces__msg__FloatingPointRange * output)
{
  if (!input || !output) {
    return false;
  }
  // from_value
  output->from_value = input->from_value;
  // to_value
  output->to_value = input->to_value;
  // step
  output->step = input->step;
  return true;
}

rcl_interfaces__msg__FloatingPointRange *
rcl_interfaces__msg__FloatingPointRange__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__msg__FloatingPointRange * msg = (rcl_interfaces__msg__FloatingPointRange *)allocator.allocate(sizeof(rcl_interfaces__msg__FloatingPointRange), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rcl_interfaces__msg__FloatingPointRange));
  bool success = rcl_interfaces__msg__FloatingPointRange__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rcl_interfaces__msg__FloatingPointRange__destroy(rcl_interfaces__msg__FloatingPointRange * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rcl_interfaces__msg__FloatingPointRange__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rcl_interfaces__msg__FloatingPointRange__Sequence__init(rcl_interfaces__msg__FloatingPointRange__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__msg__FloatingPointRange * data = NULL;

  if (size) {
    data = (rcl_interfaces__msg__FloatingPointRange *)allocator.zero_allocate(size, sizeof(rcl_interfaces__msg__FloatingPointRange), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rcl_interfaces__msg__FloatingPointRange__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rcl_interfaces__msg__FloatingPointRange__fini(&data[i - 1]);
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
rcl_interfaces__msg__FloatingPointRange__Sequence__fini(rcl_interfaces__msg__FloatingPointRange__Sequence * array)
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
      rcl_interfaces__msg__FloatingPointRange__fini(&array->data[i]);
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

rcl_interfaces__msg__FloatingPointRange__Sequence *
rcl_interfaces__msg__FloatingPointRange__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__msg__FloatingPointRange__Sequence * array = (rcl_interfaces__msg__FloatingPointRange__Sequence *)allocator.allocate(sizeof(rcl_interfaces__msg__FloatingPointRange__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rcl_interfaces__msg__FloatingPointRange__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rcl_interfaces__msg__FloatingPointRange__Sequence__destroy(rcl_interfaces__msg__FloatingPointRange__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rcl_interfaces__msg__FloatingPointRange__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rcl_interfaces__msg__FloatingPointRange__Sequence__are_equal(const rcl_interfaces__msg__FloatingPointRange__Sequence * lhs, const rcl_interfaces__msg__FloatingPointRange__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rcl_interfaces__msg__FloatingPointRange__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rcl_interfaces__msg__FloatingPointRange__Sequence__copy(
  const rcl_interfaces__msg__FloatingPointRange__Sequence * input,
  rcl_interfaces__msg__FloatingPointRange__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rcl_interfaces__msg__FloatingPointRange);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rcl_interfaces__msg__FloatingPointRange * data =
      (rcl_interfaces__msg__FloatingPointRange *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rcl_interfaces__msg__FloatingPointRange__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rcl_interfaces__msg__FloatingPointRange__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rcl_interfaces__msg__FloatingPointRange__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
