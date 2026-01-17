// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from type_description_interfaces:msg/TypeSource.idl
// generated code does not contain a copyright notice
#include "type_description_interfaces/msg/detail/type_source__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `type_name`
// Member `encoding`
// Member `raw_file_contents`
#include "rosidl_runtime_c/string_functions.h"

bool
type_description_interfaces__msg__TypeSource__init(type_description_interfaces__msg__TypeSource * msg)
{
  if (!msg) {
    return false;
  }
  // type_name
  if (!rosidl_runtime_c__String__init(&msg->type_name)) {
    type_description_interfaces__msg__TypeSource__fini(msg);
    return false;
  }
  // encoding
  if (!rosidl_runtime_c__String__init(&msg->encoding)) {
    type_description_interfaces__msg__TypeSource__fini(msg);
    return false;
  }
  // raw_file_contents
  if (!rosidl_runtime_c__String__init(&msg->raw_file_contents)) {
    type_description_interfaces__msg__TypeSource__fini(msg);
    return false;
  }
  return true;
}

void
type_description_interfaces__msg__TypeSource__fini(type_description_interfaces__msg__TypeSource * msg)
{
  if (!msg) {
    return;
  }
  // type_name
  rosidl_runtime_c__String__fini(&msg->type_name);
  // encoding
  rosidl_runtime_c__String__fini(&msg->encoding);
  // raw_file_contents
  rosidl_runtime_c__String__fini(&msg->raw_file_contents);
}

bool
type_description_interfaces__msg__TypeSource__are_equal(const type_description_interfaces__msg__TypeSource * lhs, const type_description_interfaces__msg__TypeSource * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // type_name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->type_name), &(rhs->type_name)))
  {
    return false;
  }
  // encoding
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->encoding), &(rhs->encoding)))
  {
    return false;
  }
  // raw_file_contents
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->raw_file_contents), &(rhs->raw_file_contents)))
  {
    return false;
  }
  return true;
}

bool
type_description_interfaces__msg__TypeSource__copy(
  const type_description_interfaces__msg__TypeSource * input,
  type_description_interfaces__msg__TypeSource * output)
{
  if (!input || !output) {
    return false;
  }
  // type_name
  if (!rosidl_runtime_c__String__copy(
      &(input->type_name), &(output->type_name)))
  {
    return false;
  }
  // encoding
  if (!rosidl_runtime_c__String__copy(
      &(input->encoding), &(output->encoding)))
  {
    return false;
  }
  // raw_file_contents
  if (!rosidl_runtime_c__String__copy(
      &(input->raw_file_contents), &(output->raw_file_contents)))
  {
    return false;
  }
  return true;
}

type_description_interfaces__msg__TypeSource *
type_description_interfaces__msg__TypeSource__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  type_description_interfaces__msg__TypeSource * msg = (type_description_interfaces__msg__TypeSource *)allocator.allocate(sizeof(type_description_interfaces__msg__TypeSource), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(type_description_interfaces__msg__TypeSource));
  bool success = type_description_interfaces__msg__TypeSource__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
type_description_interfaces__msg__TypeSource__destroy(type_description_interfaces__msg__TypeSource * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    type_description_interfaces__msg__TypeSource__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
type_description_interfaces__msg__TypeSource__Sequence__init(type_description_interfaces__msg__TypeSource__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  type_description_interfaces__msg__TypeSource * data = NULL;

  if (size) {
    data = (type_description_interfaces__msg__TypeSource *)allocator.zero_allocate(size, sizeof(type_description_interfaces__msg__TypeSource), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = type_description_interfaces__msg__TypeSource__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        type_description_interfaces__msg__TypeSource__fini(&data[i - 1]);
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
type_description_interfaces__msg__TypeSource__Sequence__fini(type_description_interfaces__msg__TypeSource__Sequence * array)
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
      type_description_interfaces__msg__TypeSource__fini(&array->data[i]);
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

type_description_interfaces__msg__TypeSource__Sequence *
type_description_interfaces__msg__TypeSource__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  type_description_interfaces__msg__TypeSource__Sequence * array = (type_description_interfaces__msg__TypeSource__Sequence *)allocator.allocate(sizeof(type_description_interfaces__msg__TypeSource__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = type_description_interfaces__msg__TypeSource__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
type_description_interfaces__msg__TypeSource__Sequence__destroy(type_description_interfaces__msg__TypeSource__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    type_description_interfaces__msg__TypeSource__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
type_description_interfaces__msg__TypeSource__Sequence__are_equal(const type_description_interfaces__msg__TypeSource__Sequence * lhs, const type_description_interfaces__msg__TypeSource__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!type_description_interfaces__msg__TypeSource__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
type_description_interfaces__msg__TypeSource__Sequence__copy(
  const type_description_interfaces__msg__TypeSource__Sequence * input,
  type_description_interfaces__msg__TypeSource__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(type_description_interfaces__msg__TypeSource);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    type_description_interfaces__msg__TypeSource * data =
      (type_description_interfaces__msg__TypeSource *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!type_description_interfaces__msg__TypeSource__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          type_description_interfaces__msg__TypeSource__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!type_description_interfaces__msg__TypeSource__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
