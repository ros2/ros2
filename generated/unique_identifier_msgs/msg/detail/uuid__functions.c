// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from unique_identifier_msgs:msg/UUID.idl
// generated code does not contain a copyright notice
#include "unique_identifier_msgs/msg/detail/uuid__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
unique_identifier_msgs__msg__UUID__init(unique_identifier_msgs__msg__UUID * msg)
{
  if (!msg) {
    return false;
  }
  // uuid
  return true;
}

void
unique_identifier_msgs__msg__UUID__fini(unique_identifier_msgs__msg__UUID * msg)
{
  if (!msg) {
    return;
  }
  // uuid
}

bool
unique_identifier_msgs__msg__UUID__are_equal(const unique_identifier_msgs__msg__UUID * lhs, const unique_identifier_msgs__msg__UUID * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // uuid
  for (size_t i = 0; i < 16; ++i) {
    if (lhs->uuid[i] != rhs->uuid[i]) {
      return false;
    }
  }
  return true;
}

bool
unique_identifier_msgs__msg__UUID__copy(
  const unique_identifier_msgs__msg__UUID * input,
  unique_identifier_msgs__msg__UUID * output)
{
  if (!input || !output) {
    return false;
  }
  // uuid
  for (size_t i = 0; i < 16; ++i) {
    output->uuid[i] = input->uuid[i];
  }
  return true;
}

unique_identifier_msgs__msg__UUID *
unique_identifier_msgs__msg__UUID__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  unique_identifier_msgs__msg__UUID * msg = (unique_identifier_msgs__msg__UUID *)allocator.allocate(sizeof(unique_identifier_msgs__msg__UUID), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(unique_identifier_msgs__msg__UUID));
  bool success = unique_identifier_msgs__msg__UUID__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
unique_identifier_msgs__msg__UUID__destroy(unique_identifier_msgs__msg__UUID * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    unique_identifier_msgs__msg__UUID__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
unique_identifier_msgs__msg__UUID__Sequence__init(unique_identifier_msgs__msg__UUID__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  unique_identifier_msgs__msg__UUID * data = NULL;

  if (size) {
    data = (unique_identifier_msgs__msg__UUID *)allocator.zero_allocate(size, sizeof(unique_identifier_msgs__msg__UUID), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = unique_identifier_msgs__msg__UUID__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        unique_identifier_msgs__msg__UUID__fini(&data[i - 1]);
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
unique_identifier_msgs__msg__UUID__Sequence__fini(unique_identifier_msgs__msg__UUID__Sequence * array)
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
      unique_identifier_msgs__msg__UUID__fini(&array->data[i]);
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

unique_identifier_msgs__msg__UUID__Sequence *
unique_identifier_msgs__msg__UUID__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  unique_identifier_msgs__msg__UUID__Sequence * array = (unique_identifier_msgs__msg__UUID__Sequence *)allocator.allocate(sizeof(unique_identifier_msgs__msg__UUID__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = unique_identifier_msgs__msg__UUID__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
unique_identifier_msgs__msg__UUID__Sequence__destroy(unique_identifier_msgs__msg__UUID__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    unique_identifier_msgs__msg__UUID__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
unique_identifier_msgs__msg__UUID__Sequence__are_equal(const unique_identifier_msgs__msg__UUID__Sequence * lhs, const unique_identifier_msgs__msg__UUID__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!unique_identifier_msgs__msg__UUID__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
unique_identifier_msgs__msg__UUID__Sequence__copy(
  const unique_identifier_msgs__msg__UUID__Sequence * input,
  unique_identifier_msgs__msg__UUID__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(unique_identifier_msgs__msg__UUID);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    unique_identifier_msgs__msg__UUID * data =
      (unique_identifier_msgs__msg__UUID *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!unique_identifier_msgs__msg__UUID__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          unique_identifier_msgs__msg__UUID__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!unique_identifier_msgs__msg__UUID__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
