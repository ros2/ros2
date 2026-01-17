// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from rcl_interfaces:msg/ParameterDescriptor.idl
// generated code does not contain a copyright notice
#include "rcl_interfaces/msg/detail/parameter_descriptor__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `name`
// Member `description`
// Member `additional_constraints`
#include "rosidl_runtime_c/string_functions.h"
// Member `floating_point_range`
#include "rcl_interfaces/msg/detail/floating_point_range__functions.h"
// Member `integer_range`
#include "rcl_interfaces/msg/detail/integer_range__functions.h"

bool
rcl_interfaces__msg__ParameterDescriptor__init(rcl_interfaces__msg__ParameterDescriptor * msg)
{
  if (!msg) {
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__init(&msg->name)) {
    rcl_interfaces__msg__ParameterDescriptor__fini(msg);
    return false;
  }
  // type
  // description
  if (!rosidl_runtime_c__String__init(&msg->description)) {
    rcl_interfaces__msg__ParameterDescriptor__fini(msg);
    return false;
  }
  // additional_constraints
  if (!rosidl_runtime_c__String__init(&msg->additional_constraints)) {
    rcl_interfaces__msg__ParameterDescriptor__fini(msg);
    return false;
  }
  // read_only
  msg->read_only = false;
  // dynamic_typing
  msg->dynamic_typing = false;
  // floating_point_range
  if (!rcl_interfaces__msg__FloatingPointRange__Sequence__init(&msg->floating_point_range, 0)) {
    rcl_interfaces__msg__ParameterDescriptor__fini(msg);
    return false;
  }
  // integer_range
  if (!rcl_interfaces__msg__IntegerRange__Sequence__init(&msg->integer_range, 0)) {
    rcl_interfaces__msg__ParameterDescriptor__fini(msg);
    return false;
  }
  return true;
}

void
rcl_interfaces__msg__ParameterDescriptor__fini(rcl_interfaces__msg__ParameterDescriptor * msg)
{
  if (!msg) {
    return;
  }
  // name
  rosidl_runtime_c__String__fini(&msg->name);
  // type
  // description
  rosidl_runtime_c__String__fini(&msg->description);
  // additional_constraints
  rosidl_runtime_c__String__fini(&msg->additional_constraints);
  // read_only
  // dynamic_typing
  // floating_point_range
  rcl_interfaces__msg__FloatingPointRange__Sequence__fini(&msg->floating_point_range);
  // integer_range
  rcl_interfaces__msg__IntegerRange__Sequence__fini(&msg->integer_range);
}

bool
rcl_interfaces__msg__ParameterDescriptor__are_equal(const rcl_interfaces__msg__ParameterDescriptor * lhs, const rcl_interfaces__msg__ParameterDescriptor * rhs)
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
  if (lhs->type != rhs->type) {
    return false;
  }
  // description
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->description), &(rhs->description)))
  {
    return false;
  }
  // additional_constraints
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->additional_constraints), &(rhs->additional_constraints)))
  {
    return false;
  }
  // read_only
  if (lhs->read_only != rhs->read_only) {
    return false;
  }
  // dynamic_typing
  if (lhs->dynamic_typing != rhs->dynamic_typing) {
    return false;
  }
  // floating_point_range
  if (!rcl_interfaces__msg__FloatingPointRange__Sequence__are_equal(
      &(lhs->floating_point_range), &(rhs->floating_point_range)))
  {
    return false;
  }
  // integer_range
  if (!rcl_interfaces__msg__IntegerRange__Sequence__are_equal(
      &(lhs->integer_range), &(rhs->integer_range)))
  {
    return false;
  }
  return true;
}

bool
rcl_interfaces__msg__ParameterDescriptor__copy(
  const rcl_interfaces__msg__ParameterDescriptor * input,
  rcl_interfaces__msg__ParameterDescriptor * output)
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
  output->type = input->type;
  // description
  if (!rosidl_runtime_c__String__copy(
      &(input->description), &(output->description)))
  {
    return false;
  }
  // additional_constraints
  if (!rosidl_runtime_c__String__copy(
      &(input->additional_constraints), &(output->additional_constraints)))
  {
    return false;
  }
  // read_only
  output->read_only = input->read_only;
  // dynamic_typing
  output->dynamic_typing = input->dynamic_typing;
  // floating_point_range
  if (!rcl_interfaces__msg__FloatingPointRange__Sequence__copy(
      &(input->floating_point_range), &(output->floating_point_range)))
  {
    return false;
  }
  // integer_range
  if (!rcl_interfaces__msg__IntegerRange__Sequence__copy(
      &(input->integer_range), &(output->integer_range)))
  {
    return false;
  }
  return true;
}

rcl_interfaces__msg__ParameterDescriptor *
rcl_interfaces__msg__ParameterDescriptor__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__msg__ParameterDescriptor * msg = (rcl_interfaces__msg__ParameterDescriptor *)allocator.allocate(sizeof(rcl_interfaces__msg__ParameterDescriptor), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rcl_interfaces__msg__ParameterDescriptor));
  bool success = rcl_interfaces__msg__ParameterDescriptor__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rcl_interfaces__msg__ParameterDescriptor__destroy(rcl_interfaces__msg__ParameterDescriptor * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rcl_interfaces__msg__ParameterDescriptor__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rcl_interfaces__msg__ParameterDescriptor__Sequence__init(rcl_interfaces__msg__ParameterDescriptor__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__msg__ParameterDescriptor * data = NULL;

  if (size) {
    data = (rcl_interfaces__msg__ParameterDescriptor *)allocator.zero_allocate(size, sizeof(rcl_interfaces__msg__ParameterDescriptor), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rcl_interfaces__msg__ParameterDescriptor__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rcl_interfaces__msg__ParameterDescriptor__fini(&data[i - 1]);
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
rcl_interfaces__msg__ParameterDescriptor__Sequence__fini(rcl_interfaces__msg__ParameterDescriptor__Sequence * array)
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
      rcl_interfaces__msg__ParameterDescriptor__fini(&array->data[i]);
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

rcl_interfaces__msg__ParameterDescriptor__Sequence *
rcl_interfaces__msg__ParameterDescriptor__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__msg__ParameterDescriptor__Sequence * array = (rcl_interfaces__msg__ParameterDescriptor__Sequence *)allocator.allocate(sizeof(rcl_interfaces__msg__ParameterDescriptor__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rcl_interfaces__msg__ParameterDescriptor__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rcl_interfaces__msg__ParameterDescriptor__Sequence__destroy(rcl_interfaces__msg__ParameterDescriptor__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rcl_interfaces__msg__ParameterDescriptor__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rcl_interfaces__msg__ParameterDescriptor__Sequence__are_equal(const rcl_interfaces__msg__ParameterDescriptor__Sequence * lhs, const rcl_interfaces__msg__ParameterDescriptor__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rcl_interfaces__msg__ParameterDescriptor__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rcl_interfaces__msg__ParameterDescriptor__Sequence__copy(
  const rcl_interfaces__msg__ParameterDescriptor__Sequence * input,
  rcl_interfaces__msg__ParameterDescriptor__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rcl_interfaces__msg__ParameterDescriptor);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rcl_interfaces__msg__ParameterDescriptor * data =
      (rcl_interfaces__msg__ParameterDescriptor *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rcl_interfaces__msg__ParameterDescriptor__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rcl_interfaces__msg__ParameterDescriptor__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rcl_interfaces__msg__ParameterDescriptor__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
