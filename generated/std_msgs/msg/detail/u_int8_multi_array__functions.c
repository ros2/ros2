// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from std_msgs:msg/UInt8MultiArray.idl
// generated code does not contain a copyright notice
#include "std_msgs/msg/detail/u_int8_multi_array__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `layout`
#include "std_msgs/msg/detail/multi_array_layout__functions.h"
// Member `data`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
std_msgs__msg__UInt8MultiArray__init(std_msgs__msg__UInt8MultiArray * msg)
{
  if (!msg) {
    return false;
  }
  // layout
  if (!std_msgs__msg__MultiArrayLayout__init(&msg->layout)) {
    std_msgs__msg__UInt8MultiArray__fini(msg);
    return false;
  }
  // data
  if (!rosidl_runtime_c__uint8__Sequence__init(&msg->data, 0)) {
    std_msgs__msg__UInt8MultiArray__fini(msg);
    return false;
  }
  return true;
}

void
std_msgs__msg__UInt8MultiArray__fini(std_msgs__msg__UInt8MultiArray * msg)
{
  if (!msg) {
    return;
  }
  // layout
  std_msgs__msg__MultiArrayLayout__fini(&msg->layout);
  // data
  rosidl_runtime_c__uint8__Sequence__fini(&msg->data);
}

bool
std_msgs__msg__UInt8MultiArray__are_equal(const std_msgs__msg__UInt8MultiArray * lhs, const std_msgs__msg__UInt8MultiArray * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // layout
  if (!std_msgs__msg__MultiArrayLayout__are_equal(
      &(lhs->layout), &(rhs->layout)))
  {
    return false;
  }
  // data
  if (!rosidl_runtime_c__uint8__Sequence__are_equal(
      &(lhs->data), &(rhs->data)))
  {
    return false;
  }
  return true;
}

bool
std_msgs__msg__UInt8MultiArray__copy(
  const std_msgs__msg__UInt8MultiArray * input,
  std_msgs__msg__UInt8MultiArray * output)
{
  if (!input || !output) {
    return false;
  }
  // layout
  if (!std_msgs__msg__MultiArrayLayout__copy(
      &(input->layout), &(output->layout)))
  {
    return false;
  }
  // data
  if (!rosidl_runtime_c__uint8__Sequence__copy(
      &(input->data), &(output->data)))
  {
    return false;
  }
  return true;
}

std_msgs__msg__UInt8MultiArray *
std_msgs__msg__UInt8MultiArray__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_msgs__msg__UInt8MultiArray * msg = (std_msgs__msg__UInt8MultiArray *)allocator.allocate(sizeof(std_msgs__msg__UInt8MultiArray), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(std_msgs__msg__UInt8MultiArray));
  bool success = std_msgs__msg__UInt8MultiArray__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
std_msgs__msg__UInt8MultiArray__destroy(std_msgs__msg__UInt8MultiArray * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    std_msgs__msg__UInt8MultiArray__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
std_msgs__msg__UInt8MultiArray__Sequence__init(std_msgs__msg__UInt8MultiArray__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_msgs__msg__UInt8MultiArray * data = NULL;

  if (size) {
    data = (std_msgs__msg__UInt8MultiArray *)allocator.zero_allocate(size, sizeof(std_msgs__msg__UInt8MultiArray), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = std_msgs__msg__UInt8MultiArray__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        std_msgs__msg__UInt8MultiArray__fini(&data[i - 1]);
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
std_msgs__msg__UInt8MultiArray__Sequence__fini(std_msgs__msg__UInt8MultiArray__Sequence * array)
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
      std_msgs__msg__UInt8MultiArray__fini(&array->data[i]);
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

std_msgs__msg__UInt8MultiArray__Sequence *
std_msgs__msg__UInt8MultiArray__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  std_msgs__msg__UInt8MultiArray__Sequence * array = (std_msgs__msg__UInt8MultiArray__Sequence *)allocator.allocate(sizeof(std_msgs__msg__UInt8MultiArray__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = std_msgs__msg__UInt8MultiArray__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
std_msgs__msg__UInt8MultiArray__Sequence__destroy(std_msgs__msg__UInt8MultiArray__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    std_msgs__msg__UInt8MultiArray__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
std_msgs__msg__UInt8MultiArray__Sequence__are_equal(const std_msgs__msg__UInt8MultiArray__Sequence * lhs, const std_msgs__msg__UInt8MultiArray__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!std_msgs__msg__UInt8MultiArray__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
std_msgs__msg__UInt8MultiArray__Sequence__copy(
  const std_msgs__msg__UInt8MultiArray__Sequence * input,
  std_msgs__msg__UInt8MultiArray__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(std_msgs__msg__UInt8MultiArray);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    std_msgs__msg__UInt8MultiArray * data =
      (std_msgs__msg__UInt8MultiArray *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!std_msgs__msg__UInt8MultiArray__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          std_msgs__msg__UInt8MultiArray__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!std_msgs__msg__UInt8MultiArray__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
