// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from rcl_interfaces:msg/ParameterValue.idl
// generated code does not contain a copyright notice
#include "rcl_interfaces/msg/detail/parameter_value__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `string_value`
// Member `string_array_value`
#include "rosidl_runtime_c/string_functions.h"
// Member `byte_array_value`
// Member `bool_array_value`
// Member `integer_array_value`
// Member `double_array_value`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
rcl_interfaces__msg__ParameterValue__init(rcl_interfaces__msg__ParameterValue * msg)
{
  if (!msg) {
    return false;
  }
  // type
  // bool_value
  // integer_value
  // double_value
  // string_value
  if (!rosidl_runtime_c__String__init(&msg->string_value)) {
    rcl_interfaces__msg__ParameterValue__fini(msg);
    return false;
  }
  // byte_array_value
  if (!rosidl_runtime_c__octet__Sequence__init(&msg->byte_array_value, 0)) {
    rcl_interfaces__msg__ParameterValue__fini(msg);
    return false;
  }
  // bool_array_value
  if (!rosidl_runtime_c__boolean__Sequence__init(&msg->bool_array_value, 0)) {
    rcl_interfaces__msg__ParameterValue__fini(msg);
    return false;
  }
  // integer_array_value
  if (!rosidl_runtime_c__int64__Sequence__init(&msg->integer_array_value, 0)) {
    rcl_interfaces__msg__ParameterValue__fini(msg);
    return false;
  }
  // double_array_value
  if (!rosidl_runtime_c__double__Sequence__init(&msg->double_array_value, 0)) {
    rcl_interfaces__msg__ParameterValue__fini(msg);
    return false;
  }
  // string_array_value
  if (!rosidl_runtime_c__String__Sequence__init(&msg->string_array_value, 0)) {
    rcl_interfaces__msg__ParameterValue__fini(msg);
    return false;
  }
  return true;
}

void
rcl_interfaces__msg__ParameterValue__fini(rcl_interfaces__msg__ParameterValue * msg)
{
  if (!msg) {
    return;
  }
  // type
  // bool_value
  // integer_value
  // double_value
  // string_value
  rosidl_runtime_c__String__fini(&msg->string_value);
  // byte_array_value
  rosidl_runtime_c__octet__Sequence__fini(&msg->byte_array_value);
  // bool_array_value
  rosidl_runtime_c__boolean__Sequence__fini(&msg->bool_array_value);
  // integer_array_value
  rosidl_runtime_c__int64__Sequence__fini(&msg->integer_array_value);
  // double_array_value
  rosidl_runtime_c__double__Sequence__fini(&msg->double_array_value);
  // string_array_value
  rosidl_runtime_c__String__Sequence__fini(&msg->string_array_value);
}

bool
rcl_interfaces__msg__ParameterValue__are_equal(const rcl_interfaces__msg__ParameterValue * lhs, const rcl_interfaces__msg__ParameterValue * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // type
  if (lhs->type != rhs->type) {
    return false;
  }
  // bool_value
  if (lhs->bool_value != rhs->bool_value) {
    return false;
  }
  // integer_value
  if (lhs->integer_value != rhs->integer_value) {
    return false;
  }
  // double_value
  if (lhs->double_value != rhs->double_value) {
    return false;
  }
  // string_value
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->string_value), &(rhs->string_value)))
  {
    return false;
  }
  // byte_array_value
  if (!rosidl_runtime_c__octet__Sequence__are_equal(
      &(lhs->byte_array_value), &(rhs->byte_array_value)))
  {
    return false;
  }
  // bool_array_value
  if (!rosidl_runtime_c__boolean__Sequence__are_equal(
      &(lhs->bool_array_value), &(rhs->bool_array_value)))
  {
    return false;
  }
  // integer_array_value
  if (!rosidl_runtime_c__int64__Sequence__are_equal(
      &(lhs->integer_array_value), &(rhs->integer_array_value)))
  {
    return false;
  }
  // double_array_value
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->double_array_value), &(rhs->double_array_value)))
  {
    return false;
  }
  // string_array_value
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->string_array_value), &(rhs->string_array_value)))
  {
    return false;
  }
  return true;
}

bool
rcl_interfaces__msg__ParameterValue__copy(
  const rcl_interfaces__msg__ParameterValue * input,
  rcl_interfaces__msg__ParameterValue * output)
{
  if (!input || !output) {
    return false;
  }
  // type
  output->type = input->type;
  // bool_value
  output->bool_value = input->bool_value;
  // integer_value
  output->integer_value = input->integer_value;
  // double_value
  output->double_value = input->double_value;
  // string_value
  if (!rosidl_runtime_c__String__copy(
      &(input->string_value), &(output->string_value)))
  {
    return false;
  }
  // byte_array_value
  if (!rosidl_runtime_c__octet__Sequence__copy(
      &(input->byte_array_value), &(output->byte_array_value)))
  {
    return false;
  }
  // bool_array_value
  if (!rosidl_runtime_c__boolean__Sequence__copy(
      &(input->bool_array_value), &(output->bool_array_value)))
  {
    return false;
  }
  // integer_array_value
  if (!rosidl_runtime_c__int64__Sequence__copy(
      &(input->integer_array_value), &(output->integer_array_value)))
  {
    return false;
  }
  // double_array_value
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->double_array_value), &(output->double_array_value)))
  {
    return false;
  }
  // string_array_value
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->string_array_value), &(output->string_array_value)))
  {
    return false;
  }
  return true;
}

rcl_interfaces__msg__ParameterValue *
rcl_interfaces__msg__ParameterValue__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__msg__ParameterValue * msg = (rcl_interfaces__msg__ParameterValue *)allocator.allocate(sizeof(rcl_interfaces__msg__ParameterValue), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rcl_interfaces__msg__ParameterValue));
  bool success = rcl_interfaces__msg__ParameterValue__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rcl_interfaces__msg__ParameterValue__destroy(rcl_interfaces__msg__ParameterValue * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rcl_interfaces__msg__ParameterValue__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rcl_interfaces__msg__ParameterValue__Sequence__init(rcl_interfaces__msg__ParameterValue__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__msg__ParameterValue * data = NULL;

  if (size) {
    data = (rcl_interfaces__msg__ParameterValue *)allocator.zero_allocate(size, sizeof(rcl_interfaces__msg__ParameterValue), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rcl_interfaces__msg__ParameterValue__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rcl_interfaces__msg__ParameterValue__fini(&data[i - 1]);
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
rcl_interfaces__msg__ParameterValue__Sequence__fini(rcl_interfaces__msg__ParameterValue__Sequence * array)
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
      rcl_interfaces__msg__ParameterValue__fini(&array->data[i]);
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

rcl_interfaces__msg__ParameterValue__Sequence *
rcl_interfaces__msg__ParameterValue__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__msg__ParameterValue__Sequence * array = (rcl_interfaces__msg__ParameterValue__Sequence *)allocator.allocate(sizeof(rcl_interfaces__msg__ParameterValue__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rcl_interfaces__msg__ParameterValue__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rcl_interfaces__msg__ParameterValue__Sequence__destroy(rcl_interfaces__msg__ParameterValue__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rcl_interfaces__msg__ParameterValue__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rcl_interfaces__msg__ParameterValue__Sequence__are_equal(const rcl_interfaces__msg__ParameterValue__Sequence * lhs, const rcl_interfaces__msg__ParameterValue__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rcl_interfaces__msg__ParameterValue__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rcl_interfaces__msg__ParameterValue__Sequence__copy(
  const rcl_interfaces__msg__ParameterValue__Sequence * input,
  rcl_interfaces__msg__ParameterValue__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rcl_interfaces__msg__ParameterValue);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rcl_interfaces__msg__ParameterValue * data =
      (rcl_interfaces__msg__ParameterValue *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rcl_interfaces__msg__ParameterValue__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rcl_interfaces__msg__ParameterValue__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rcl_interfaces__msg__ParameterValue__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
