// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from rosgraph_msgs:msg/Clock.idl
// generated code does not contain a copyright notice
#include "rosgraph_msgs/msg/detail/clock__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `clock`
#include "builtin_interfaces/msg/detail/time__functions.h"

bool
rosgraph_msgs__msg__Clock__init(rosgraph_msgs__msg__Clock * msg)
{
  if (!msg) {
    return false;
  }
  // clock
  if (!builtin_interfaces__msg__Time__init(&msg->clock)) {
    rosgraph_msgs__msg__Clock__fini(msg);
    return false;
  }
  return true;
}

void
rosgraph_msgs__msg__Clock__fini(rosgraph_msgs__msg__Clock * msg)
{
  if (!msg) {
    return;
  }
  // clock
  builtin_interfaces__msg__Time__fini(&msg->clock);
}

bool
rosgraph_msgs__msg__Clock__are_equal(const rosgraph_msgs__msg__Clock * lhs, const rosgraph_msgs__msg__Clock * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // clock
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->clock), &(rhs->clock)))
  {
    return false;
  }
  return true;
}

bool
rosgraph_msgs__msg__Clock__copy(
  const rosgraph_msgs__msg__Clock * input,
  rosgraph_msgs__msg__Clock * output)
{
  if (!input || !output) {
    return false;
  }
  // clock
  if (!builtin_interfaces__msg__Time__copy(
      &(input->clock), &(output->clock)))
  {
    return false;
  }
  return true;
}

rosgraph_msgs__msg__Clock *
rosgraph_msgs__msg__Clock__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rosgraph_msgs__msg__Clock * msg = (rosgraph_msgs__msg__Clock *)allocator.allocate(sizeof(rosgraph_msgs__msg__Clock), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rosgraph_msgs__msg__Clock));
  bool success = rosgraph_msgs__msg__Clock__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rosgraph_msgs__msg__Clock__destroy(rosgraph_msgs__msg__Clock * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rosgraph_msgs__msg__Clock__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rosgraph_msgs__msg__Clock__Sequence__init(rosgraph_msgs__msg__Clock__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rosgraph_msgs__msg__Clock * data = NULL;

  if (size) {
    data = (rosgraph_msgs__msg__Clock *)allocator.zero_allocate(size, sizeof(rosgraph_msgs__msg__Clock), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rosgraph_msgs__msg__Clock__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rosgraph_msgs__msg__Clock__fini(&data[i - 1]);
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
rosgraph_msgs__msg__Clock__Sequence__fini(rosgraph_msgs__msg__Clock__Sequence * array)
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
      rosgraph_msgs__msg__Clock__fini(&array->data[i]);
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

rosgraph_msgs__msg__Clock__Sequence *
rosgraph_msgs__msg__Clock__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rosgraph_msgs__msg__Clock__Sequence * array = (rosgraph_msgs__msg__Clock__Sequence *)allocator.allocate(sizeof(rosgraph_msgs__msg__Clock__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rosgraph_msgs__msg__Clock__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rosgraph_msgs__msg__Clock__Sequence__destroy(rosgraph_msgs__msg__Clock__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rosgraph_msgs__msg__Clock__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rosgraph_msgs__msg__Clock__Sequence__are_equal(const rosgraph_msgs__msg__Clock__Sequence * lhs, const rosgraph_msgs__msg__Clock__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rosgraph_msgs__msg__Clock__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rosgraph_msgs__msg__Clock__Sequence__copy(
  const rosgraph_msgs__msg__Clock__Sequence * input,
  rosgraph_msgs__msg__Clock__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rosgraph_msgs__msg__Clock);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rosgraph_msgs__msg__Clock * data =
      (rosgraph_msgs__msg__Clock *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rosgraph_msgs__msg__Clock__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rosgraph_msgs__msg__Clock__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rosgraph_msgs__msg__Clock__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
