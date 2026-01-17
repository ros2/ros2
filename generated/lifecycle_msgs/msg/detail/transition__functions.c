// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from lifecycle_msgs:msg/Transition.idl
// generated code does not contain a copyright notice
#include "lifecycle_msgs/msg/detail/transition__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `label`
#include "rosidl_runtime_c/string_functions.h"

bool
lifecycle_msgs__msg__Transition__init(lifecycle_msgs__msg__Transition * msg)
{
  if (!msg) {
    return false;
  }
  // id
  // label
  if (!rosidl_runtime_c__String__init(&msg->label)) {
    lifecycle_msgs__msg__Transition__fini(msg);
    return false;
  }
  return true;
}

void
lifecycle_msgs__msg__Transition__fini(lifecycle_msgs__msg__Transition * msg)
{
  if (!msg) {
    return;
  }
  // id
  // label
  rosidl_runtime_c__String__fini(&msg->label);
}

bool
lifecycle_msgs__msg__Transition__are_equal(const lifecycle_msgs__msg__Transition * lhs, const lifecycle_msgs__msg__Transition * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // id
  if (lhs->id != rhs->id) {
    return false;
  }
  // label
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->label), &(rhs->label)))
  {
    return false;
  }
  return true;
}

bool
lifecycle_msgs__msg__Transition__copy(
  const lifecycle_msgs__msg__Transition * input,
  lifecycle_msgs__msg__Transition * output)
{
  if (!input || !output) {
    return false;
  }
  // id
  output->id = input->id;
  // label
  if (!rosidl_runtime_c__String__copy(
      &(input->label), &(output->label)))
  {
    return false;
  }
  return true;
}

lifecycle_msgs__msg__Transition *
lifecycle_msgs__msg__Transition__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__msg__Transition * msg = (lifecycle_msgs__msg__Transition *)allocator.allocate(sizeof(lifecycle_msgs__msg__Transition), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(lifecycle_msgs__msg__Transition));
  bool success = lifecycle_msgs__msg__Transition__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
lifecycle_msgs__msg__Transition__destroy(lifecycle_msgs__msg__Transition * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    lifecycle_msgs__msg__Transition__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
lifecycle_msgs__msg__Transition__Sequence__init(lifecycle_msgs__msg__Transition__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__msg__Transition * data = NULL;

  if (size) {
    data = (lifecycle_msgs__msg__Transition *)allocator.zero_allocate(size, sizeof(lifecycle_msgs__msg__Transition), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = lifecycle_msgs__msg__Transition__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        lifecycle_msgs__msg__Transition__fini(&data[i - 1]);
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
lifecycle_msgs__msg__Transition__Sequence__fini(lifecycle_msgs__msg__Transition__Sequence * array)
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
      lifecycle_msgs__msg__Transition__fini(&array->data[i]);
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

lifecycle_msgs__msg__Transition__Sequence *
lifecycle_msgs__msg__Transition__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__msg__Transition__Sequence * array = (lifecycle_msgs__msg__Transition__Sequence *)allocator.allocate(sizeof(lifecycle_msgs__msg__Transition__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = lifecycle_msgs__msg__Transition__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
lifecycle_msgs__msg__Transition__Sequence__destroy(lifecycle_msgs__msg__Transition__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    lifecycle_msgs__msg__Transition__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
lifecycle_msgs__msg__Transition__Sequence__are_equal(const lifecycle_msgs__msg__Transition__Sequence * lhs, const lifecycle_msgs__msg__Transition__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!lifecycle_msgs__msg__Transition__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
lifecycle_msgs__msg__Transition__Sequence__copy(
  const lifecycle_msgs__msg__Transition__Sequence * input,
  lifecycle_msgs__msg__Transition__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(lifecycle_msgs__msg__Transition);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    lifecycle_msgs__msg__Transition * data =
      (lifecycle_msgs__msg__Transition *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!lifecycle_msgs__msg__Transition__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          lifecycle_msgs__msg__Transition__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!lifecycle_msgs__msg__Transition__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
