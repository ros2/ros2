// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from rcl_interfaces:msg/ParameterEventDescriptors.idl
// generated code does not contain a copyright notice
#include "rcl_interfaces/msg/detail/parameter_event_descriptors__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `new_parameters`
// Member `changed_parameters`
// Member `deleted_parameters`
#include "rcl_interfaces/msg/detail/parameter_descriptor__functions.h"

bool
rcl_interfaces__msg__ParameterEventDescriptors__init(rcl_interfaces__msg__ParameterEventDescriptors * msg)
{
  if (!msg) {
    return false;
  }
  // new_parameters
  if (!rcl_interfaces__msg__ParameterDescriptor__Sequence__init(&msg->new_parameters, 0)) {
    rcl_interfaces__msg__ParameterEventDescriptors__fini(msg);
    return false;
  }
  // changed_parameters
  if (!rcl_interfaces__msg__ParameterDescriptor__Sequence__init(&msg->changed_parameters, 0)) {
    rcl_interfaces__msg__ParameterEventDescriptors__fini(msg);
    return false;
  }
  // deleted_parameters
  if (!rcl_interfaces__msg__ParameterDescriptor__Sequence__init(&msg->deleted_parameters, 0)) {
    rcl_interfaces__msg__ParameterEventDescriptors__fini(msg);
    return false;
  }
  return true;
}

void
rcl_interfaces__msg__ParameterEventDescriptors__fini(rcl_interfaces__msg__ParameterEventDescriptors * msg)
{
  if (!msg) {
    return;
  }
  // new_parameters
  rcl_interfaces__msg__ParameterDescriptor__Sequence__fini(&msg->new_parameters);
  // changed_parameters
  rcl_interfaces__msg__ParameterDescriptor__Sequence__fini(&msg->changed_parameters);
  // deleted_parameters
  rcl_interfaces__msg__ParameterDescriptor__Sequence__fini(&msg->deleted_parameters);
}

bool
rcl_interfaces__msg__ParameterEventDescriptors__are_equal(const rcl_interfaces__msg__ParameterEventDescriptors * lhs, const rcl_interfaces__msg__ParameterEventDescriptors * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // new_parameters
  if (!rcl_interfaces__msg__ParameterDescriptor__Sequence__are_equal(
      &(lhs->new_parameters), &(rhs->new_parameters)))
  {
    return false;
  }
  // changed_parameters
  if (!rcl_interfaces__msg__ParameterDescriptor__Sequence__are_equal(
      &(lhs->changed_parameters), &(rhs->changed_parameters)))
  {
    return false;
  }
  // deleted_parameters
  if (!rcl_interfaces__msg__ParameterDescriptor__Sequence__are_equal(
      &(lhs->deleted_parameters), &(rhs->deleted_parameters)))
  {
    return false;
  }
  return true;
}

bool
rcl_interfaces__msg__ParameterEventDescriptors__copy(
  const rcl_interfaces__msg__ParameterEventDescriptors * input,
  rcl_interfaces__msg__ParameterEventDescriptors * output)
{
  if (!input || !output) {
    return false;
  }
  // new_parameters
  if (!rcl_interfaces__msg__ParameterDescriptor__Sequence__copy(
      &(input->new_parameters), &(output->new_parameters)))
  {
    return false;
  }
  // changed_parameters
  if (!rcl_interfaces__msg__ParameterDescriptor__Sequence__copy(
      &(input->changed_parameters), &(output->changed_parameters)))
  {
    return false;
  }
  // deleted_parameters
  if (!rcl_interfaces__msg__ParameterDescriptor__Sequence__copy(
      &(input->deleted_parameters), &(output->deleted_parameters)))
  {
    return false;
  }
  return true;
}

rcl_interfaces__msg__ParameterEventDescriptors *
rcl_interfaces__msg__ParameterEventDescriptors__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__msg__ParameterEventDescriptors * msg = (rcl_interfaces__msg__ParameterEventDescriptors *)allocator.allocate(sizeof(rcl_interfaces__msg__ParameterEventDescriptors), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rcl_interfaces__msg__ParameterEventDescriptors));
  bool success = rcl_interfaces__msg__ParameterEventDescriptors__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rcl_interfaces__msg__ParameterEventDescriptors__destroy(rcl_interfaces__msg__ParameterEventDescriptors * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rcl_interfaces__msg__ParameterEventDescriptors__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rcl_interfaces__msg__ParameterEventDescriptors__Sequence__init(rcl_interfaces__msg__ParameterEventDescriptors__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__msg__ParameterEventDescriptors * data = NULL;

  if (size) {
    data = (rcl_interfaces__msg__ParameterEventDescriptors *)allocator.zero_allocate(size, sizeof(rcl_interfaces__msg__ParameterEventDescriptors), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rcl_interfaces__msg__ParameterEventDescriptors__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rcl_interfaces__msg__ParameterEventDescriptors__fini(&data[i - 1]);
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
rcl_interfaces__msg__ParameterEventDescriptors__Sequence__fini(rcl_interfaces__msg__ParameterEventDescriptors__Sequence * array)
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
      rcl_interfaces__msg__ParameterEventDescriptors__fini(&array->data[i]);
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

rcl_interfaces__msg__ParameterEventDescriptors__Sequence *
rcl_interfaces__msg__ParameterEventDescriptors__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__msg__ParameterEventDescriptors__Sequence * array = (rcl_interfaces__msg__ParameterEventDescriptors__Sequence *)allocator.allocate(sizeof(rcl_interfaces__msg__ParameterEventDescriptors__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rcl_interfaces__msg__ParameterEventDescriptors__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rcl_interfaces__msg__ParameterEventDescriptors__Sequence__destroy(rcl_interfaces__msg__ParameterEventDescriptors__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rcl_interfaces__msg__ParameterEventDescriptors__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rcl_interfaces__msg__ParameterEventDescriptors__Sequence__are_equal(const rcl_interfaces__msg__ParameterEventDescriptors__Sequence * lhs, const rcl_interfaces__msg__ParameterEventDescriptors__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rcl_interfaces__msg__ParameterEventDescriptors__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rcl_interfaces__msg__ParameterEventDescriptors__Sequence__copy(
  const rcl_interfaces__msg__ParameterEventDescriptors__Sequence * input,
  rcl_interfaces__msg__ParameterEventDescriptors__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rcl_interfaces__msg__ParameterEventDescriptors);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rcl_interfaces__msg__ParameterEventDescriptors * data =
      (rcl_interfaces__msg__ParameterEventDescriptors *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rcl_interfaces__msg__ParameterEventDescriptors__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rcl_interfaces__msg__ParameterEventDescriptors__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rcl_interfaces__msg__ParameterEventDescriptors__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
