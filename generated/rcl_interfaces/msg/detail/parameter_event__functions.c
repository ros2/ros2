// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from rcl_interfaces:msg/ParameterEvent.idl
// generated code does not contain a copyright notice
#include "rcl_interfaces/msg/detail/parameter_event__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"
// Member `node`
#include "rosidl_runtime_c/string_functions.h"
// Member `new_parameters`
// Member `changed_parameters`
// Member `deleted_parameters`
#include "rcl_interfaces/msg/detail/parameter__functions.h"

bool
rcl_interfaces__msg__ParameterEvent__init(rcl_interfaces__msg__ParameterEvent * msg)
{
  if (!msg) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    rcl_interfaces__msg__ParameterEvent__fini(msg);
    return false;
  }
  // node
  if (!rosidl_runtime_c__String__init(&msg->node)) {
    rcl_interfaces__msg__ParameterEvent__fini(msg);
    return false;
  }
  // new_parameters
  if (!rcl_interfaces__msg__Parameter__Sequence__init(&msg->new_parameters, 0)) {
    rcl_interfaces__msg__ParameterEvent__fini(msg);
    return false;
  }
  // changed_parameters
  if (!rcl_interfaces__msg__Parameter__Sequence__init(&msg->changed_parameters, 0)) {
    rcl_interfaces__msg__ParameterEvent__fini(msg);
    return false;
  }
  // deleted_parameters
  if (!rcl_interfaces__msg__Parameter__Sequence__init(&msg->deleted_parameters, 0)) {
    rcl_interfaces__msg__ParameterEvent__fini(msg);
    return false;
  }
  return true;
}

void
rcl_interfaces__msg__ParameterEvent__fini(rcl_interfaces__msg__ParameterEvent * msg)
{
  if (!msg) {
    return;
  }
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
  // node
  rosidl_runtime_c__String__fini(&msg->node);
  // new_parameters
  rcl_interfaces__msg__Parameter__Sequence__fini(&msg->new_parameters);
  // changed_parameters
  rcl_interfaces__msg__Parameter__Sequence__fini(&msg->changed_parameters);
  // deleted_parameters
  rcl_interfaces__msg__Parameter__Sequence__fini(&msg->deleted_parameters);
}

bool
rcl_interfaces__msg__ParameterEvent__are_equal(const rcl_interfaces__msg__ParameterEvent * lhs, const rcl_interfaces__msg__ParameterEvent * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->stamp), &(rhs->stamp)))
  {
    return false;
  }
  // node
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->node), &(rhs->node)))
  {
    return false;
  }
  // new_parameters
  if (!rcl_interfaces__msg__Parameter__Sequence__are_equal(
      &(lhs->new_parameters), &(rhs->new_parameters)))
  {
    return false;
  }
  // changed_parameters
  if (!rcl_interfaces__msg__Parameter__Sequence__are_equal(
      &(lhs->changed_parameters), &(rhs->changed_parameters)))
  {
    return false;
  }
  // deleted_parameters
  if (!rcl_interfaces__msg__Parameter__Sequence__are_equal(
      &(lhs->deleted_parameters), &(rhs->deleted_parameters)))
  {
    return false;
  }
  return true;
}

bool
rcl_interfaces__msg__ParameterEvent__copy(
  const rcl_interfaces__msg__ParameterEvent * input,
  rcl_interfaces__msg__ParameterEvent * output)
{
  if (!input || !output) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->stamp), &(output->stamp)))
  {
    return false;
  }
  // node
  if (!rosidl_runtime_c__String__copy(
      &(input->node), &(output->node)))
  {
    return false;
  }
  // new_parameters
  if (!rcl_interfaces__msg__Parameter__Sequence__copy(
      &(input->new_parameters), &(output->new_parameters)))
  {
    return false;
  }
  // changed_parameters
  if (!rcl_interfaces__msg__Parameter__Sequence__copy(
      &(input->changed_parameters), &(output->changed_parameters)))
  {
    return false;
  }
  // deleted_parameters
  if (!rcl_interfaces__msg__Parameter__Sequence__copy(
      &(input->deleted_parameters), &(output->deleted_parameters)))
  {
    return false;
  }
  return true;
}

rcl_interfaces__msg__ParameterEvent *
rcl_interfaces__msg__ParameterEvent__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__msg__ParameterEvent * msg = (rcl_interfaces__msg__ParameterEvent *)allocator.allocate(sizeof(rcl_interfaces__msg__ParameterEvent), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rcl_interfaces__msg__ParameterEvent));
  bool success = rcl_interfaces__msg__ParameterEvent__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rcl_interfaces__msg__ParameterEvent__destroy(rcl_interfaces__msg__ParameterEvent * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rcl_interfaces__msg__ParameterEvent__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rcl_interfaces__msg__ParameterEvent__Sequence__init(rcl_interfaces__msg__ParameterEvent__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__msg__ParameterEvent * data = NULL;

  if (size) {
    data = (rcl_interfaces__msg__ParameterEvent *)allocator.zero_allocate(size, sizeof(rcl_interfaces__msg__ParameterEvent), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rcl_interfaces__msg__ParameterEvent__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rcl_interfaces__msg__ParameterEvent__fini(&data[i - 1]);
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
rcl_interfaces__msg__ParameterEvent__Sequence__fini(rcl_interfaces__msg__ParameterEvent__Sequence * array)
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
      rcl_interfaces__msg__ParameterEvent__fini(&array->data[i]);
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

rcl_interfaces__msg__ParameterEvent__Sequence *
rcl_interfaces__msg__ParameterEvent__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcl_interfaces__msg__ParameterEvent__Sequence * array = (rcl_interfaces__msg__ParameterEvent__Sequence *)allocator.allocate(sizeof(rcl_interfaces__msg__ParameterEvent__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rcl_interfaces__msg__ParameterEvent__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rcl_interfaces__msg__ParameterEvent__Sequence__destroy(rcl_interfaces__msg__ParameterEvent__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rcl_interfaces__msg__ParameterEvent__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rcl_interfaces__msg__ParameterEvent__Sequence__are_equal(const rcl_interfaces__msg__ParameterEvent__Sequence * lhs, const rcl_interfaces__msg__ParameterEvent__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rcl_interfaces__msg__ParameterEvent__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rcl_interfaces__msg__ParameterEvent__Sequence__copy(
  const rcl_interfaces__msg__ParameterEvent__Sequence * input,
  rcl_interfaces__msg__ParameterEvent__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rcl_interfaces__msg__ParameterEvent);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rcl_interfaces__msg__ParameterEvent * data =
      (rcl_interfaces__msg__ParameterEvent *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rcl_interfaces__msg__ParameterEvent__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rcl_interfaces__msg__ParameterEvent__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rcl_interfaces__msg__ParameterEvent__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
