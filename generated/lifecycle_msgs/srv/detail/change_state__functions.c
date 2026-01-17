// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from lifecycle_msgs:srv/ChangeState.idl
// generated code does not contain a copyright notice
#include "lifecycle_msgs/srv/detail/change_state__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `transition`
#include "lifecycle_msgs/msg/detail/transition__functions.h"

bool
lifecycle_msgs__srv__ChangeState_Request__init(lifecycle_msgs__srv__ChangeState_Request * msg)
{
  if (!msg) {
    return false;
  }
  // transition
  if (!lifecycle_msgs__msg__Transition__init(&msg->transition)) {
    lifecycle_msgs__srv__ChangeState_Request__fini(msg);
    return false;
  }
  return true;
}

void
lifecycle_msgs__srv__ChangeState_Request__fini(lifecycle_msgs__srv__ChangeState_Request * msg)
{
  if (!msg) {
    return;
  }
  // transition
  lifecycle_msgs__msg__Transition__fini(&msg->transition);
}

bool
lifecycle_msgs__srv__ChangeState_Request__are_equal(const lifecycle_msgs__srv__ChangeState_Request * lhs, const lifecycle_msgs__srv__ChangeState_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // transition
  if (!lifecycle_msgs__msg__Transition__are_equal(
      &(lhs->transition), &(rhs->transition)))
  {
    return false;
  }
  return true;
}

bool
lifecycle_msgs__srv__ChangeState_Request__copy(
  const lifecycle_msgs__srv__ChangeState_Request * input,
  lifecycle_msgs__srv__ChangeState_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // transition
  if (!lifecycle_msgs__msg__Transition__copy(
      &(input->transition), &(output->transition)))
  {
    return false;
  }
  return true;
}

lifecycle_msgs__srv__ChangeState_Request *
lifecycle_msgs__srv__ChangeState_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__srv__ChangeState_Request * msg = (lifecycle_msgs__srv__ChangeState_Request *)allocator.allocate(sizeof(lifecycle_msgs__srv__ChangeState_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(lifecycle_msgs__srv__ChangeState_Request));
  bool success = lifecycle_msgs__srv__ChangeState_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
lifecycle_msgs__srv__ChangeState_Request__destroy(lifecycle_msgs__srv__ChangeState_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    lifecycle_msgs__srv__ChangeState_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
lifecycle_msgs__srv__ChangeState_Request__Sequence__init(lifecycle_msgs__srv__ChangeState_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__srv__ChangeState_Request * data = NULL;

  if (size) {
    data = (lifecycle_msgs__srv__ChangeState_Request *)allocator.zero_allocate(size, sizeof(lifecycle_msgs__srv__ChangeState_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = lifecycle_msgs__srv__ChangeState_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        lifecycle_msgs__srv__ChangeState_Request__fini(&data[i - 1]);
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
lifecycle_msgs__srv__ChangeState_Request__Sequence__fini(lifecycle_msgs__srv__ChangeState_Request__Sequence * array)
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
      lifecycle_msgs__srv__ChangeState_Request__fini(&array->data[i]);
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

lifecycle_msgs__srv__ChangeState_Request__Sequence *
lifecycle_msgs__srv__ChangeState_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__srv__ChangeState_Request__Sequence * array = (lifecycle_msgs__srv__ChangeState_Request__Sequence *)allocator.allocate(sizeof(lifecycle_msgs__srv__ChangeState_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = lifecycle_msgs__srv__ChangeState_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
lifecycle_msgs__srv__ChangeState_Request__Sequence__destroy(lifecycle_msgs__srv__ChangeState_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    lifecycle_msgs__srv__ChangeState_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
lifecycle_msgs__srv__ChangeState_Request__Sequence__are_equal(const lifecycle_msgs__srv__ChangeState_Request__Sequence * lhs, const lifecycle_msgs__srv__ChangeState_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!lifecycle_msgs__srv__ChangeState_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
lifecycle_msgs__srv__ChangeState_Request__Sequence__copy(
  const lifecycle_msgs__srv__ChangeState_Request__Sequence * input,
  lifecycle_msgs__srv__ChangeState_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(lifecycle_msgs__srv__ChangeState_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    lifecycle_msgs__srv__ChangeState_Request * data =
      (lifecycle_msgs__srv__ChangeState_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!lifecycle_msgs__srv__ChangeState_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          lifecycle_msgs__srv__ChangeState_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!lifecycle_msgs__srv__ChangeState_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


bool
lifecycle_msgs__srv__ChangeState_Response__init(lifecycle_msgs__srv__ChangeState_Response * msg)
{
  if (!msg) {
    return false;
  }
  // success
  return true;
}

void
lifecycle_msgs__srv__ChangeState_Response__fini(lifecycle_msgs__srv__ChangeState_Response * msg)
{
  if (!msg) {
    return;
  }
  // success
}

bool
lifecycle_msgs__srv__ChangeState_Response__are_equal(const lifecycle_msgs__srv__ChangeState_Response * lhs, const lifecycle_msgs__srv__ChangeState_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  return true;
}

bool
lifecycle_msgs__srv__ChangeState_Response__copy(
  const lifecycle_msgs__srv__ChangeState_Response * input,
  lifecycle_msgs__srv__ChangeState_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  return true;
}

lifecycle_msgs__srv__ChangeState_Response *
lifecycle_msgs__srv__ChangeState_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__srv__ChangeState_Response * msg = (lifecycle_msgs__srv__ChangeState_Response *)allocator.allocate(sizeof(lifecycle_msgs__srv__ChangeState_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(lifecycle_msgs__srv__ChangeState_Response));
  bool success = lifecycle_msgs__srv__ChangeState_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
lifecycle_msgs__srv__ChangeState_Response__destroy(lifecycle_msgs__srv__ChangeState_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    lifecycle_msgs__srv__ChangeState_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
lifecycle_msgs__srv__ChangeState_Response__Sequence__init(lifecycle_msgs__srv__ChangeState_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__srv__ChangeState_Response * data = NULL;

  if (size) {
    data = (lifecycle_msgs__srv__ChangeState_Response *)allocator.zero_allocate(size, sizeof(lifecycle_msgs__srv__ChangeState_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = lifecycle_msgs__srv__ChangeState_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        lifecycle_msgs__srv__ChangeState_Response__fini(&data[i - 1]);
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
lifecycle_msgs__srv__ChangeState_Response__Sequence__fini(lifecycle_msgs__srv__ChangeState_Response__Sequence * array)
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
      lifecycle_msgs__srv__ChangeState_Response__fini(&array->data[i]);
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

lifecycle_msgs__srv__ChangeState_Response__Sequence *
lifecycle_msgs__srv__ChangeState_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__srv__ChangeState_Response__Sequence * array = (lifecycle_msgs__srv__ChangeState_Response__Sequence *)allocator.allocate(sizeof(lifecycle_msgs__srv__ChangeState_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = lifecycle_msgs__srv__ChangeState_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
lifecycle_msgs__srv__ChangeState_Response__Sequence__destroy(lifecycle_msgs__srv__ChangeState_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    lifecycle_msgs__srv__ChangeState_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
lifecycle_msgs__srv__ChangeState_Response__Sequence__are_equal(const lifecycle_msgs__srv__ChangeState_Response__Sequence * lhs, const lifecycle_msgs__srv__ChangeState_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!lifecycle_msgs__srv__ChangeState_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
lifecycle_msgs__srv__ChangeState_Response__Sequence__copy(
  const lifecycle_msgs__srv__ChangeState_Response__Sequence * input,
  lifecycle_msgs__srv__ChangeState_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(lifecycle_msgs__srv__ChangeState_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    lifecycle_msgs__srv__ChangeState_Response * data =
      (lifecycle_msgs__srv__ChangeState_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!lifecycle_msgs__srv__ChangeState_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          lifecycle_msgs__srv__ChangeState_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!lifecycle_msgs__srv__ChangeState_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `info`
#include "service_msgs/msg/detail/service_event_info__functions.h"
// Member `request`
// Member `response`
// already included above
// #include "lifecycle_msgs/srv/detail/change_state__functions.h"

bool
lifecycle_msgs__srv__ChangeState_Event__init(lifecycle_msgs__srv__ChangeState_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    lifecycle_msgs__srv__ChangeState_Event__fini(msg);
    return false;
  }
  // request
  if (!lifecycle_msgs__srv__ChangeState_Request__Sequence__init(&msg->request, 0)) {
    lifecycle_msgs__srv__ChangeState_Event__fini(msg);
    return false;
  }
  // response
  if (!lifecycle_msgs__srv__ChangeState_Response__Sequence__init(&msg->response, 0)) {
    lifecycle_msgs__srv__ChangeState_Event__fini(msg);
    return false;
  }
  return true;
}

void
lifecycle_msgs__srv__ChangeState_Event__fini(lifecycle_msgs__srv__ChangeState_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  lifecycle_msgs__srv__ChangeState_Request__Sequence__fini(&msg->request);
  // response
  lifecycle_msgs__srv__ChangeState_Response__Sequence__fini(&msg->response);
}

bool
lifecycle_msgs__srv__ChangeState_Event__are_equal(const lifecycle_msgs__srv__ChangeState_Event * lhs, const lifecycle_msgs__srv__ChangeState_Event * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__are_equal(
      &(lhs->info), &(rhs->info)))
  {
    return false;
  }
  // request
  if (!lifecycle_msgs__srv__ChangeState_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!lifecycle_msgs__srv__ChangeState_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
lifecycle_msgs__srv__ChangeState_Event__copy(
  const lifecycle_msgs__srv__ChangeState_Event * input,
  lifecycle_msgs__srv__ChangeState_Event * output)
{
  if (!input || !output) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__copy(
      &(input->info), &(output->info)))
  {
    return false;
  }
  // request
  if (!lifecycle_msgs__srv__ChangeState_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!lifecycle_msgs__srv__ChangeState_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

lifecycle_msgs__srv__ChangeState_Event *
lifecycle_msgs__srv__ChangeState_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__srv__ChangeState_Event * msg = (lifecycle_msgs__srv__ChangeState_Event *)allocator.allocate(sizeof(lifecycle_msgs__srv__ChangeState_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(lifecycle_msgs__srv__ChangeState_Event));
  bool success = lifecycle_msgs__srv__ChangeState_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
lifecycle_msgs__srv__ChangeState_Event__destroy(lifecycle_msgs__srv__ChangeState_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    lifecycle_msgs__srv__ChangeState_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
lifecycle_msgs__srv__ChangeState_Event__Sequence__init(lifecycle_msgs__srv__ChangeState_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__srv__ChangeState_Event * data = NULL;

  if (size) {
    data = (lifecycle_msgs__srv__ChangeState_Event *)allocator.zero_allocate(size, sizeof(lifecycle_msgs__srv__ChangeState_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = lifecycle_msgs__srv__ChangeState_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        lifecycle_msgs__srv__ChangeState_Event__fini(&data[i - 1]);
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
lifecycle_msgs__srv__ChangeState_Event__Sequence__fini(lifecycle_msgs__srv__ChangeState_Event__Sequence * array)
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
      lifecycle_msgs__srv__ChangeState_Event__fini(&array->data[i]);
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

lifecycle_msgs__srv__ChangeState_Event__Sequence *
lifecycle_msgs__srv__ChangeState_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  lifecycle_msgs__srv__ChangeState_Event__Sequence * array = (lifecycle_msgs__srv__ChangeState_Event__Sequence *)allocator.allocate(sizeof(lifecycle_msgs__srv__ChangeState_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = lifecycle_msgs__srv__ChangeState_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
lifecycle_msgs__srv__ChangeState_Event__Sequence__destroy(lifecycle_msgs__srv__ChangeState_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    lifecycle_msgs__srv__ChangeState_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
lifecycle_msgs__srv__ChangeState_Event__Sequence__are_equal(const lifecycle_msgs__srv__ChangeState_Event__Sequence * lhs, const lifecycle_msgs__srv__ChangeState_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!lifecycle_msgs__srv__ChangeState_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
lifecycle_msgs__srv__ChangeState_Event__Sequence__copy(
  const lifecycle_msgs__srv__ChangeState_Event__Sequence * input,
  lifecycle_msgs__srv__ChangeState_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(lifecycle_msgs__srv__ChangeState_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    lifecycle_msgs__srv__ChangeState_Event * data =
      (lifecycle_msgs__srv__ChangeState_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!lifecycle_msgs__srv__ChangeState_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          lifecycle_msgs__srv__ChangeState_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!lifecycle_msgs__srv__ChangeState_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
