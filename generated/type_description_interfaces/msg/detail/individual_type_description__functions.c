// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from type_description_interfaces:msg/IndividualTypeDescription.idl
// generated code does not contain a copyright notice
#include "type_description_interfaces/msg/detail/individual_type_description__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `type_name`
#include "rosidl_runtime_c/string_functions.h"
// Member `fields`
#include "type_description_interfaces/msg/detail/field__functions.h"

bool
type_description_interfaces__msg__IndividualTypeDescription__init(type_description_interfaces__msg__IndividualTypeDescription * msg)
{
  if (!msg) {
    return false;
  }
  // type_name
  if (!rosidl_runtime_c__String__init(&msg->type_name)) {
    type_description_interfaces__msg__IndividualTypeDescription__fini(msg);
    return false;
  }
  // fields
  if (!type_description_interfaces__msg__Field__Sequence__init(&msg->fields, 0)) {
    type_description_interfaces__msg__IndividualTypeDescription__fini(msg);
    return false;
  }
  return true;
}

void
type_description_interfaces__msg__IndividualTypeDescription__fini(type_description_interfaces__msg__IndividualTypeDescription * msg)
{
  if (!msg) {
    return;
  }
  // type_name
  rosidl_runtime_c__String__fini(&msg->type_name);
  // fields
  type_description_interfaces__msg__Field__Sequence__fini(&msg->fields);
}

bool
type_description_interfaces__msg__IndividualTypeDescription__are_equal(const type_description_interfaces__msg__IndividualTypeDescription * lhs, const type_description_interfaces__msg__IndividualTypeDescription * rhs)
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
  // fields
  if (!type_description_interfaces__msg__Field__Sequence__are_equal(
      &(lhs->fields), &(rhs->fields)))
  {
    return false;
  }
  return true;
}

bool
type_description_interfaces__msg__IndividualTypeDescription__copy(
  const type_description_interfaces__msg__IndividualTypeDescription * input,
  type_description_interfaces__msg__IndividualTypeDescription * output)
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
  // fields
  if (!type_description_interfaces__msg__Field__Sequence__copy(
      &(input->fields), &(output->fields)))
  {
    return false;
  }
  return true;
}

type_description_interfaces__msg__IndividualTypeDescription *
type_description_interfaces__msg__IndividualTypeDescription__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  type_description_interfaces__msg__IndividualTypeDescription * msg = (type_description_interfaces__msg__IndividualTypeDescription *)allocator.allocate(sizeof(type_description_interfaces__msg__IndividualTypeDescription), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(type_description_interfaces__msg__IndividualTypeDescription));
  bool success = type_description_interfaces__msg__IndividualTypeDescription__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
type_description_interfaces__msg__IndividualTypeDescription__destroy(type_description_interfaces__msg__IndividualTypeDescription * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    type_description_interfaces__msg__IndividualTypeDescription__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
type_description_interfaces__msg__IndividualTypeDescription__Sequence__init(type_description_interfaces__msg__IndividualTypeDescription__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  type_description_interfaces__msg__IndividualTypeDescription * data = NULL;

  if (size) {
    data = (type_description_interfaces__msg__IndividualTypeDescription *)allocator.zero_allocate(size, sizeof(type_description_interfaces__msg__IndividualTypeDescription), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = type_description_interfaces__msg__IndividualTypeDescription__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        type_description_interfaces__msg__IndividualTypeDescription__fini(&data[i - 1]);
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
type_description_interfaces__msg__IndividualTypeDescription__Sequence__fini(type_description_interfaces__msg__IndividualTypeDescription__Sequence * array)
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
      type_description_interfaces__msg__IndividualTypeDescription__fini(&array->data[i]);
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

type_description_interfaces__msg__IndividualTypeDescription__Sequence *
type_description_interfaces__msg__IndividualTypeDescription__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  type_description_interfaces__msg__IndividualTypeDescription__Sequence * array = (type_description_interfaces__msg__IndividualTypeDescription__Sequence *)allocator.allocate(sizeof(type_description_interfaces__msg__IndividualTypeDescription__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = type_description_interfaces__msg__IndividualTypeDescription__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
type_description_interfaces__msg__IndividualTypeDescription__Sequence__destroy(type_description_interfaces__msg__IndividualTypeDescription__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    type_description_interfaces__msg__IndividualTypeDescription__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
type_description_interfaces__msg__IndividualTypeDescription__Sequence__are_equal(const type_description_interfaces__msg__IndividualTypeDescription__Sequence * lhs, const type_description_interfaces__msg__IndividualTypeDescription__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!type_description_interfaces__msg__IndividualTypeDescription__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
type_description_interfaces__msg__IndividualTypeDescription__Sequence__copy(
  const type_description_interfaces__msg__IndividualTypeDescription__Sequence * input,
  type_description_interfaces__msg__IndividualTypeDescription__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(type_description_interfaces__msg__IndividualTypeDescription);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    type_description_interfaces__msg__IndividualTypeDescription * data =
      (type_description_interfaces__msg__IndividualTypeDescription *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!type_description_interfaces__msg__IndividualTypeDescription__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          type_description_interfaces__msg__IndividualTypeDescription__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!type_description_interfaces__msg__IndividualTypeDescription__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
