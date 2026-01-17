// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from action_msgs:msg/GoalInfo.idl
// generated code does not contain a copyright notice
#include "action_msgs/msg/detail/goal_info__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `goal_id`
#include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"

bool
action_msgs__msg__GoalInfo__init(action_msgs__msg__GoalInfo * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    action_msgs__msg__GoalInfo__fini(msg);
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    action_msgs__msg__GoalInfo__fini(msg);
    return false;
  }
  return true;
}

void
action_msgs__msg__GoalInfo__fini(action_msgs__msg__GoalInfo * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
}

bool
action_msgs__msg__GoalInfo__are_equal(const action_msgs__msg__GoalInfo * lhs, const action_msgs__msg__GoalInfo * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->stamp), &(rhs->stamp)))
  {
    return false;
  }
  return true;
}

bool
action_msgs__msg__GoalInfo__copy(
  const action_msgs__msg__GoalInfo * input,
  action_msgs__msg__GoalInfo * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->stamp), &(output->stamp)))
  {
    return false;
  }
  return true;
}

action_msgs__msg__GoalInfo *
action_msgs__msg__GoalInfo__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  action_msgs__msg__GoalInfo * msg = (action_msgs__msg__GoalInfo *)allocator.allocate(sizeof(action_msgs__msg__GoalInfo), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(action_msgs__msg__GoalInfo));
  bool success = action_msgs__msg__GoalInfo__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
action_msgs__msg__GoalInfo__destroy(action_msgs__msg__GoalInfo * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    action_msgs__msg__GoalInfo__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
action_msgs__msg__GoalInfo__Sequence__init(action_msgs__msg__GoalInfo__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  action_msgs__msg__GoalInfo * data = NULL;

  if (size) {
    data = (action_msgs__msg__GoalInfo *)allocator.zero_allocate(size, sizeof(action_msgs__msg__GoalInfo), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = action_msgs__msg__GoalInfo__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        action_msgs__msg__GoalInfo__fini(&data[i - 1]);
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
action_msgs__msg__GoalInfo__Sequence__fini(action_msgs__msg__GoalInfo__Sequence * array)
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
      action_msgs__msg__GoalInfo__fini(&array->data[i]);
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

action_msgs__msg__GoalInfo__Sequence *
action_msgs__msg__GoalInfo__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  action_msgs__msg__GoalInfo__Sequence * array = (action_msgs__msg__GoalInfo__Sequence *)allocator.allocate(sizeof(action_msgs__msg__GoalInfo__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = action_msgs__msg__GoalInfo__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
action_msgs__msg__GoalInfo__Sequence__destroy(action_msgs__msg__GoalInfo__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    action_msgs__msg__GoalInfo__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
action_msgs__msg__GoalInfo__Sequence__are_equal(const action_msgs__msg__GoalInfo__Sequence * lhs, const action_msgs__msg__GoalInfo__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!action_msgs__msg__GoalInfo__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
action_msgs__msg__GoalInfo__Sequence__copy(
  const action_msgs__msg__GoalInfo__Sequence * input,
  action_msgs__msg__GoalInfo__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(action_msgs__msg__GoalInfo);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    action_msgs__msg__GoalInfo * data =
      (action_msgs__msg__GoalInfo *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!action_msgs__msg__GoalInfo__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          action_msgs__msg__GoalInfo__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!action_msgs__msg__GoalInfo__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
