// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from builtin_interfaces:msg/Duration.idl
// generated code does not contain a copyright notice
#include "builtin_interfaces/msg/detail/duration__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
builtin_interfaces__msg__Duration__init(builtin_interfaces__msg__Duration * msg)
{
  if (!msg) {
    return false;
  }
  // sec
  // nanosec
  return true;
}

void
builtin_interfaces__msg__Duration__fini(builtin_interfaces__msg__Duration * msg)
{
  if (!msg) {
    return;
  }
  // sec
  // nanosec
}

bool
builtin_interfaces__msg__Duration__are_equal(const builtin_interfaces__msg__Duration * lhs, const builtin_interfaces__msg__Duration * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // sec
  if (lhs->sec != rhs->sec) {
    return false;
  }
  // nanosec
  if (lhs->nanosec != rhs->nanosec) {
    return false;
  }
  return true;
}

bool
builtin_interfaces__msg__Duration__copy(
  const builtin_interfaces__msg__Duration * input,
  builtin_interfaces__msg__Duration * output)
{
  if (!input || !output) {
    return false;
  }
  // sec
  output->sec = input->sec;
  // nanosec
  output->nanosec = input->nanosec;
  return true;
}

builtin_interfaces__msg__Duration *
builtin_interfaces__msg__Duration__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  builtin_interfaces__msg__Duration * msg = (builtin_interfaces__msg__Duration *)allocator.allocate(sizeof(builtin_interfaces__msg__Duration), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(builtin_interfaces__msg__Duration));
  bool success = builtin_interfaces__msg__Duration__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
builtin_interfaces__msg__Duration__destroy(builtin_interfaces__msg__Duration * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    builtin_interfaces__msg__Duration__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
builtin_interfaces__msg__Duration__Sequence__init(builtin_interfaces__msg__Duration__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  builtin_interfaces__msg__Duration * data = NULL;

  if (size) {
    data = (builtin_interfaces__msg__Duration *)allocator.zero_allocate(size, sizeof(builtin_interfaces__msg__Duration), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = builtin_interfaces__msg__Duration__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        builtin_interfaces__msg__Duration__fini(&data[i - 1]);
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
builtin_interfaces__msg__Duration__Sequence__fini(builtin_interfaces__msg__Duration__Sequence * array)
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
      builtin_interfaces__msg__Duration__fini(&array->data[i]);
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

builtin_interfaces__msg__Duration__Sequence *
builtin_interfaces__msg__Duration__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  builtin_interfaces__msg__Duration__Sequence * array = (builtin_interfaces__msg__Duration__Sequence *)allocator.allocate(sizeof(builtin_interfaces__msg__Duration__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = builtin_interfaces__msg__Duration__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
builtin_interfaces__msg__Duration__Sequence__destroy(builtin_interfaces__msg__Duration__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    builtin_interfaces__msg__Duration__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
builtin_interfaces__msg__Duration__Sequence__are_equal(const builtin_interfaces__msg__Duration__Sequence * lhs, const builtin_interfaces__msg__Duration__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!builtin_interfaces__msg__Duration__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
builtin_interfaces__msg__Duration__Sequence__copy(
  const builtin_interfaces__msg__Duration__Sequence * input,
  builtin_interfaces__msg__Duration__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(builtin_interfaces__msg__Duration);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    builtin_interfaces__msg__Duration * data =
      (builtin_interfaces__msg__Duration *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!builtin_interfaces__msg__Duration__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          builtin_interfaces__msg__Duration__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!builtin_interfaces__msg__Duration__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
