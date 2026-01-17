// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from type_description_interfaces:msg/Field.idl
// generated code does not contain a copyright notice
#include "type_description_interfaces/msg/detail/field__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `name`
// Member `default_value`
#include "rosidl_runtime_c/string_functions.h"
// Member `type`
#include "type_description_interfaces/msg/detail/field_type__functions.h"

bool
type_description_interfaces__msg__Field__init(type_description_interfaces__msg__Field * msg)
{
  if (!msg) {
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__init(&msg->name)) {
    type_description_interfaces__msg__Field__fini(msg);
    return false;
  }
  // type
  if (!type_description_interfaces__msg__FieldType__init(&msg->type)) {
    type_description_interfaces__msg__Field__fini(msg);
    return false;
  }
  // default_value
  if (!rosidl_runtime_c__String__init(&msg->default_value)) {
    type_description_interfaces__msg__Field__fini(msg);
    return false;
  }
  return true;
}

void
type_description_interfaces__msg__Field__fini(type_description_interfaces__msg__Field * msg)
{
  if (!msg) {
    return;
  }
  // name
  rosidl_runtime_c__String__fini(&msg->name);
  // type
  type_description_interfaces__msg__FieldType__fini(&msg->type);
  // default_value
  rosidl_runtime_c__String__fini(&msg->default_value);
}

bool
type_description_interfaces__msg__Field__are_equal(const type_description_interfaces__msg__Field * lhs, const type_description_interfaces__msg__Field * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->name), &(rhs->name)))
  {
    return false;
  }
  // type
  if (!type_description_interfaces__msg__FieldType__are_equal(
      &(lhs->type), &(rhs->type)))
  {
    return false;
  }
  // default_value
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->default_value), &(rhs->default_value)))
  {
    return false;
  }
  return true;
}

bool
type_description_interfaces__msg__Field__copy(
  const type_description_interfaces__msg__Field * input,
  type_description_interfaces__msg__Field * output)
{
  if (!input || !output) {
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__copy(
      &(input->name), &(output->name)))
  {
    return false;
  }
  // type
  if (!type_description_interfaces__msg__FieldType__copy(
      &(input->type), &(output->type)))
  {
    return false;
  }
  // default_value
  if (!rosidl_runtime_c__String__copy(
      &(input->default_value), &(output->default_value)))
  {
    return false;
  }
  return true;
}

type_description_interfaces__msg__Field *
type_description_interfaces__msg__Field__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  type_description_interfaces__msg__Field * msg = (type_description_interfaces__msg__Field *)allocator.allocate(sizeof(type_description_interfaces__msg__Field), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(type_description_interfaces__msg__Field));
  bool success = type_description_interfaces__msg__Field__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
type_description_interfaces__msg__Field__destroy(type_description_interfaces__msg__Field * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    type_description_interfaces__msg__Field__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
type_description_interfaces__msg__Field__Sequence__init(type_description_interfaces__msg__Field__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  type_description_interfaces__msg__Field * data = NULL;

  if (size) {
    data = (type_description_interfaces__msg__Field *)allocator.zero_allocate(size, sizeof(type_description_interfaces__msg__Field), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = type_description_interfaces__msg__Field__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        type_description_interfaces__msg__Field__fini(&data[i - 1]);
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
type_description_interfaces__msg__Field__Sequence__fini(type_description_interfaces__msg__Field__Sequence * array)
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
      type_description_interfaces__msg__Field__fini(&array->data[i]);
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

type_description_interfaces__msg__Field__Sequence *
type_description_interfaces__msg__Field__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  type_description_interfaces__msg__Field__Sequence * array = (type_description_interfaces__msg__Field__Sequence *)allocator.allocate(sizeof(type_description_interfaces__msg__Field__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = type_description_interfaces__msg__Field__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
type_description_interfaces__msg__Field__Sequence__destroy(type_description_interfaces__msg__Field__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    type_description_interfaces__msg__Field__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
type_description_interfaces__msg__Field__Sequence__are_equal(const type_description_interfaces__msg__Field__Sequence * lhs, const type_description_interfaces__msg__Field__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!type_description_interfaces__msg__Field__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
type_description_interfaces__msg__Field__Sequence__copy(
  const type_description_interfaces__msg__Field__Sequence * input,
  type_description_interfaces__msg__Field__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(type_description_interfaces__msg__Field);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    type_description_interfaces__msg__Field * data =
      (type_description_interfaces__msg__Field *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!type_description_interfaces__msg__Field__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          type_description_interfaces__msg__Field__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!type_description_interfaces__msg__Field__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
