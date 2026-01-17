// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from type_description_interfaces:srv/GetTypeDescription.idl
// generated code does not contain a copyright notice
#include "type_description_interfaces/srv/detail/get_type_description__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `type_name`
// Member `type_hash`
#include "rosidl_runtime_c/string_functions.h"

bool
type_description_interfaces__srv__GetTypeDescription_Request__init(type_description_interfaces__srv__GetTypeDescription_Request * msg)
{
  if (!msg) {
    return false;
  }
  // type_name
  if (!rosidl_runtime_c__String__init(&msg->type_name)) {
    type_description_interfaces__srv__GetTypeDescription_Request__fini(msg);
    return false;
  }
  // type_hash
  if (!rosidl_runtime_c__String__init(&msg->type_hash)) {
    type_description_interfaces__srv__GetTypeDescription_Request__fini(msg);
    return false;
  }
  // include_type_sources
  msg->include_type_sources = true;
  return true;
}

void
type_description_interfaces__srv__GetTypeDescription_Request__fini(type_description_interfaces__srv__GetTypeDescription_Request * msg)
{
  if (!msg) {
    return;
  }
  // type_name
  rosidl_runtime_c__String__fini(&msg->type_name);
  // type_hash
  rosidl_runtime_c__String__fini(&msg->type_hash);
  // include_type_sources
}

bool
type_description_interfaces__srv__GetTypeDescription_Request__are_equal(const type_description_interfaces__srv__GetTypeDescription_Request * lhs, const type_description_interfaces__srv__GetTypeDescription_Request * rhs)
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
  // type_hash
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->type_hash), &(rhs->type_hash)))
  {
    return false;
  }
  // include_type_sources
  if (lhs->include_type_sources != rhs->include_type_sources) {
    return false;
  }
  return true;
}

bool
type_description_interfaces__srv__GetTypeDescription_Request__copy(
  const type_description_interfaces__srv__GetTypeDescription_Request * input,
  type_description_interfaces__srv__GetTypeDescription_Request * output)
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
  // type_hash
  if (!rosidl_runtime_c__String__copy(
      &(input->type_hash), &(output->type_hash)))
  {
    return false;
  }
  // include_type_sources
  output->include_type_sources = input->include_type_sources;
  return true;
}

type_description_interfaces__srv__GetTypeDescription_Request *
type_description_interfaces__srv__GetTypeDescription_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  type_description_interfaces__srv__GetTypeDescription_Request * msg = (type_description_interfaces__srv__GetTypeDescription_Request *)allocator.allocate(sizeof(type_description_interfaces__srv__GetTypeDescription_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(type_description_interfaces__srv__GetTypeDescription_Request));
  bool success = type_description_interfaces__srv__GetTypeDescription_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
type_description_interfaces__srv__GetTypeDescription_Request__destroy(type_description_interfaces__srv__GetTypeDescription_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    type_description_interfaces__srv__GetTypeDescription_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
type_description_interfaces__srv__GetTypeDescription_Request__Sequence__init(type_description_interfaces__srv__GetTypeDescription_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  type_description_interfaces__srv__GetTypeDescription_Request * data = NULL;

  if (size) {
    data = (type_description_interfaces__srv__GetTypeDescription_Request *)allocator.zero_allocate(size, sizeof(type_description_interfaces__srv__GetTypeDescription_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = type_description_interfaces__srv__GetTypeDescription_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        type_description_interfaces__srv__GetTypeDescription_Request__fini(&data[i - 1]);
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
type_description_interfaces__srv__GetTypeDescription_Request__Sequence__fini(type_description_interfaces__srv__GetTypeDescription_Request__Sequence * array)
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
      type_description_interfaces__srv__GetTypeDescription_Request__fini(&array->data[i]);
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

type_description_interfaces__srv__GetTypeDescription_Request__Sequence *
type_description_interfaces__srv__GetTypeDescription_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  type_description_interfaces__srv__GetTypeDescription_Request__Sequence * array = (type_description_interfaces__srv__GetTypeDescription_Request__Sequence *)allocator.allocate(sizeof(type_description_interfaces__srv__GetTypeDescription_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = type_description_interfaces__srv__GetTypeDescription_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
type_description_interfaces__srv__GetTypeDescription_Request__Sequence__destroy(type_description_interfaces__srv__GetTypeDescription_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    type_description_interfaces__srv__GetTypeDescription_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
type_description_interfaces__srv__GetTypeDescription_Request__Sequence__are_equal(const type_description_interfaces__srv__GetTypeDescription_Request__Sequence * lhs, const type_description_interfaces__srv__GetTypeDescription_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!type_description_interfaces__srv__GetTypeDescription_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
type_description_interfaces__srv__GetTypeDescription_Request__Sequence__copy(
  const type_description_interfaces__srv__GetTypeDescription_Request__Sequence * input,
  type_description_interfaces__srv__GetTypeDescription_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(type_description_interfaces__srv__GetTypeDescription_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    type_description_interfaces__srv__GetTypeDescription_Request * data =
      (type_description_interfaces__srv__GetTypeDescription_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!type_description_interfaces__srv__GetTypeDescription_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          type_description_interfaces__srv__GetTypeDescription_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!type_description_interfaces__srv__GetTypeDescription_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `failure_reason`
// already included above
// #include "rosidl_runtime_c/string_functions.h"
// Member `type_description`
#include "type_description_interfaces/msg/detail/type_description__functions.h"
// Member `type_sources`
#include "type_description_interfaces/msg/detail/type_source__functions.h"
// Member `extra_information`
#include "type_description_interfaces/msg/detail/key_value__functions.h"

bool
type_description_interfaces__srv__GetTypeDescription_Response__init(type_description_interfaces__srv__GetTypeDescription_Response * msg)
{
  if (!msg) {
    return false;
  }
  // successful
  // failure_reason
  if (!rosidl_runtime_c__String__init(&msg->failure_reason)) {
    type_description_interfaces__srv__GetTypeDescription_Response__fini(msg);
    return false;
  }
  // type_description
  if (!type_description_interfaces__msg__TypeDescription__init(&msg->type_description)) {
    type_description_interfaces__srv__GetTypeDescription_Response__fini(msg);
    return false;
  }
  // type_sources
  if (!type_description_interfaces__msg__TypeSource__Sequence__init(&msg->type_sources, 0)) {
    type_description_interfaces__srv__GetTypeDescription_Response__fini(msg);
    return false;
  }
  // extra_information
  if (!type_description_interfaces__msg__KeyValue__Sequence__init(&msg->extra_information, 0)) {
    type_description_interfaces__srv__GetTypeDescription_Response__fini(msg);
    return false;
  }
  return true;
}

void
type_description_interfaces__srv__GetTypeDescription_Response__fini(type_description_interfaces__srv__GetTypeDescription_Response * msg)
{
  if (!msg) {
    return;
  }
  // successful
  // failure_reason
  rosidl_runtime_c__String__fini(&msg->failure_reason);
  // type_description
  type_description_interfaces__msg__TypeDescription__fini(&msg->type_description);
  // type_sources
  type_description_interfaces__msg__TypeSource__Sequence__fini(&msg->type_sources);
  // extra_information
  type_description_interfaces__msg__KeyValue__Sequence__fini(&msg->extra_information);
}

bool
type_description_interfaces__srv__GetTypeDescription_Response__are_equal(const type_description_interfaces__srv__GetTypeDescription_Response * lhs, const type_description_interfaces__srv__GetTypeDescription_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // successful
  if (lhs->successful != rhs->successful) {
    return false;
  }
  // failure_reason
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->failure_reason), &(rhs->failure_reason)))
  {
    return false;
  }
  // type_description
  if (!type_description_interfaces__msg__TypeDescription__are_equal(
      &(lhs->type_description), &(rhs->type_description)))
  {
    return false;
  }
  // type_sources
  if (!type_description_interfaces__msg__TypeSource__Sequence__are_equal(
      &(lhs->type_sources), &(rhs->type_sources)))
  {
    return false;
  }
  // extra_information
  if (!type_description_interfaces__msg__KeyValue__Sequence__are_equal(
      &(lhs->extra_information), &(rhs->extra_information)))
  {
    return false;
  }
  return true;
}

bool
type_description_interfaces__srv__GetTypeDescription_Response__copy(
  const type_description_interfaces__srv__GetTypeDescription_Response * input,
  type_description_interfaces__srv__GetTypeDescription_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // successful
  output->successful = input->successful;
  // failure_reason
  if (!rosidl_runtime_c__String__copy(
      &(input->failure_reason), &(output->failure_reason)))
  {
    return false;
  }
  // type_description
  if (!type_description_interfaces__msg__TypeDescription__copy(
      &(input->type_description), &(output->type_description)))
  {
    return false;
  }
  // type_sources
  if (!type_description_interfaces__msg__TypeSource__Sequence__copy(
      &(input->type_sources), &(output->type_sources)))
  {
    return false;
  }
  // extra_information
  if (!type_description_interfaces__msg__KeyValue__Sequence__copy(
      &(input->extra_information), &(output->extra_information)))
  {
    return false;
  }
  return true;
}

type_description_interfaces__srv__GetTypeDescription_Response *
type_description_interfaces__srv__GetTypeDescription_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  type_description_interfaces__srv__GetTypeDescription_Response * msg = (type_description_interfaces__srv__GetTypeDescription_Response *)allocator.allocate(sizeof(type_description_interfaces__srv__GetTypeDescription_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(type_description_interfaces__srv__GetTypeDescription_Response));
  bool success = type_description_interfaces__srv__GetTypeDescription_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
type_description_interfaces__srv__GetTypeDescription_Response__destroy(type_description_interfaces__srv__GetTypeDescription_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    type_description_interfaces__srv__GetTypeDescription_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
type_description_interfaces__srv__GetTypeDescription_Response__Sequence__init(type_description_interfaces__srv__GetTypeDescription_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  type_description_interfaces__srv__GetTypeDescription_Response * data = NULL;

  if (size) {
    data = (type_description_interfaces__srv__GetTypeDescription_Response *)allocator.zero_allocate(size, sizeof(type_description_interfaces__srv__GetTypeDescription_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = type_description_interfaces__srv__GetTypeDescription_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        type_description_interfaces__srv__GetTypeDescription_Response__fini(&data[i - 1]);
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
type_description_interfaces__srv__GetTypeDescription_Response__Sequence__fini(type_description_interfaces__srv__GetTypeDescription_Response__Sequence * array)
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
      type_description_interfaces__srv__GetTypeDescription_Response__fini(&array->data[i]);
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

type_description_interfaces__srv__GetTypeDescription_Response__Sequence *
type_description_interfaces__srv__GetTypeDescription_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  type_description_interfaces__srv__GetTypeDescription_Response__Sequence * array = (type_description_interfaces__srv__GetTypeDescription_Response__Sequence *)allocator.allocate(sizeof(type_description_interfaces__srv__GetTypeDescription_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = type_description_interfaces__srv__GetTypeDescription_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
type_description_interfaces__srv__GetTypeDescription_Response__Sequence__destroy(type_description_interfaces__srv__GetTypeDescription_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    type_description_interfaces__srv__GetTypeDescription_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
type_description_interfaces__srv__GetTypeDescription_Response__Sequence__are_equal(const type_description_interfaces__srv__GetTypeDescription_Response__Sequence * lhs, const type_description_interfaces__srv__GetTypeDescription_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!type_description_interfaces__srv__GetTypeDescription_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
type_description_interfaces__srv__GetTypeDescription_Response__Sequence__copy(
  const type_description_interfaces__srv__GetTypeDescription_Response__Sequence * input,
  type_description_interfaces__srv__GetTypeDescription_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(type_description_interfaces__srv__GetTypeDescription_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    type_description_interfaces__srv__GetTypeDescription_Response * data =
      (type_description_interfaces__srv__GetTypeDescription_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!type_description_interfaces__srv__GetTypeDescription_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          type_description_interfaces__srv__GetTypeDescription_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!type_description_interfaces__srv__GetTypeDescription_Response__copy(
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
// #include "type_description_interfaces/srv/detail/get_type_description__functions.h"

bool
type_description_interfaces__srv__GetTypeDescription_Event__init(type_description_interfaces__srv__GetTypeDescription_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    type_description_interfaces__srv__GetTypeDescription_Event__fini(msg);
    return false;
  }
  // request
  if (!type_description_interfaces__srv__GetTypeDescription_Request__Sequence__init(&msg->request, 0)) {
    type_description_interfaces__srv__GetTypeDescription_Event__fini(msg);
    return false;
  }
  // response
  if (!type_description_interfaces__srv__GetTypeDescription_Response__Sequence__init(&msg->response, 0)) {
    type_description_interfaces__srv__GetTypeDescription_Event__fini(msg);
    return false;
  }
  return true;
}

void
type_description_interfaces__srv__GetTypeDescription_Event__fini(type_description_interfaces__srv__GetTypeDescription_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  type_description_interfaces__srv__GetTypeDescription_Request__Sequence__fini(&msg->request);
  // response
  type_description_interfaces__srv__GetTypeDescription_Response__Sequence__fini(&msg->response);
}

bool
type_description_interfaces__srv__GetTypeDescription_Event__are_equal(const type_description_interfaces__srv__GetTypeDescription_Event * lhs, const type_description_interfaces__srv__GetTypeDescription_Event * rhs)
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
  if (!type_description_interfaces__srv__GetTypeDescription_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!type_description_interfaces__srv__GetTypeDescription_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
type_description_interfaces__srv__GetTypeDescription_Event__copy(
  const type_description_interfaces__srv__GetTypeDescription_Event * input,
  type_description_interfaces__srv__GetTypeDescription_Event * output)
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
  if (!type_description_interfaces__srv__GetTypeDescription_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!type_description_interfaces__srv__GetTypeDescription_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

type_description_interfaces__srv__GetTypeDescription_Event *
type_description_interfaces__srv__GetTypeDescription_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  type_description_interfaces__srv__GetTypeDescription_Event * msg = (type_description_interfaces__srv__GetTypeDescription_Event *)allocator.allocate(sizeof(type_description_interfaces__srv__GetTypeDescription_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(type_description_interfaces__srv__GetTypeDescription_Event));
  bool success = type_description_interfaces__srv__GetTypeDescription_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
type_description_interfaces__srv__GetTypeDescription_Event__destroy(type_description_interfaces__srv__GetTypeDescription_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    type_description_interfaces__srv__GetTypeDescription_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
type_description_interfaces__srv__GetTypeDescription_Event__Sequence__init(type_description_interfaces__srv__GetTypeDescription_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  type_description_interfaces__srv__GetTypeDescription_Event * data = NULL;

  if (size) {
    data = (type_description_interfaces__srv__GetTypeDescription_Event *)allocator.zero_allocate(size, sizeof(type_description_interfaces__srv__GetTypeDescription_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = type_description_interfaces__srv__GetTypeDescription_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        type_description_interfaces__srv__GetTypeDescription_Event__fini(&data[i - 1]);
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
type_description_interfaces__srv__GetTypeDescription_Event__Sequence__fini(type_description_interfaces__srv__GetTypeDescription_Event__Sequence * array)
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
      type_description_interfaces__srv__GetTypeDescription_Event__fini(&array->data[i]);
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

type_description_interfaces__srv__GetTypeDescription_Event__Sequence *
type_description_interfaces__srv__GetTypeDescription_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  type_description_interfaces__srv__GetTypeDescription_Event__Sequence * array = (type_description_interfaces__srv__GetTypeDescription_Event__Sequence *)allocator.allocate(sizeof(type_description_interfaces__srv__GetTypeDescription_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = type_description_interfaces__srv__GetTypeDescription_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
type_description_interfaces__srv__GetTypeDescription_Event__Sequence__destroy(type_description_interfaces__srv__GetTypeDescription_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    type_description_interfaces__srv__GetTypeDescription_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
type_description_interfaces__srv__GetTypeDescription_Event__Sequence__are_equal(const type_description_interfaces__srv__GetTypeDescription_Event__Sequence * lhs, const type_description_interfaces__srv__GetTypeDescription_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!type_description_interfaces__srv__GetTypeDescription_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
type_description_interfaces__srv__GetTypeDescription_Event__Sequence__copy(
  const type_description_interfaces__srv__GetTypeDescription_Event__Sequence * input,
  type_description_interfaces__srv__GetTypeDescription_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(type_description_interfaces__srv__GetTypeDescription_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    type_description_interfaces__srv__GetTypeDescription_Event * data =
      (type_description_interfaces__srv__GetTypeDescription_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!type_description_interfaces__srv__GetTypeDescription_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          type_description_interfaces__srv__GetTypeDescription_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!type_description_interfaces__srv__GetTypeDescription_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
