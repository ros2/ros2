// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from service_msgs:msg/ServiceEventInfo.idl
// generated code does not contain a copyright notice
#include "service_msgs/msg/detail/service_event_info__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"

bool
service_msgs__msg__ServiceEventInfo__init(service_msgs__msg__ServiceEventInfo * msg)
{
  if (!msg) {
    return false;
  }
  // event_type
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    service_msgs__msg__ServiceEventInfo__fini(msg);
    return false;
  }
  // client_gid
  // sequence_number
  return true;
}

void
service_msgs__msg__ServiceEventInfo__fini(service_msgs__msg__ServiceEventInfo * msg)
{
  if (!msg) {
    return;
  }
  // event_type
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
  // client_gid
  // sequence_number
}

bool
service_msgs__msg__ServiceEventInfo__are_equal(const service_msgs__msg__ServiceEventInfo * lhs, const service_msgs__msg__ServiceEventInfo * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // event_type
  if (lhs->event_type != rhs->event_type) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->stamp), &(rhs->stamp)))
  {
    return false;
  }
  // client_gid
  for (size_t i = 0; i < 16; ++i) {
    if (lhs->client_gid[i] != rhs->client_gid[i]) {
      return false;
    }
  }
  // sequence_number
  if (lhs->sequence_number != rhs->sequence_number) {
    return false;
  }
  return true;
}

bool
service_msgs__msg__ServiceEventInfo__copy(
  const service_msgs__msg__ServiceEventInfo * input,
  service_msgs__msg__ServiceEventInfo * output)
{
  if (!input || !output) {
    return false;
  }
  // event_type
  output->event_type = input->event_type;
  // stamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->stamp), &(output->stamp)))
  {
    return false;
  }
  // client_gid
  for (size_t i = 0; i < 16; ++i) {
    output->client_gid[i] = input->client_gid[i];
  }
  // sequence_number
  output->sequence_number = input->sequence_number;
  return true;
}

service_msgs__msg__ServiceEventInfo *
service_msgs__msg__ServiceEventInfo__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  service_msgs__msg__ServiceEventInfo * msg = (service_msgs__msg__ServiceEventInfo *)allocator.allocate(sizeof(service_msgs__msg__ServiceEventInfo), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(service_msgs__msg__ServiceEventInfo));
  bool success = service_msgs__msg__ServiceEventInfo__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
service_msgs__msg__ServiceEventInfo__destroy(service_msgs__msg__ServiceEventInfo * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    service_msgs__msg__ServiceEventInfo__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
service_msgs__msg__ServiceEventInfo__Sequence__init(service_msgs__msg__ServiceEventInfo__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  service_msgs__msg__ServiceEventInfo * data = NULL;

  if (size) {
    data = (service_msgs__msg__ServiceEventInfo *)allocator.zero_allocate(size, sizeof(service_msgs__msg__ServiceEventInfo), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = service_msgs__msg__ServiceEventInfo__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        service_msgs__msg__ServiceEventInfo__fini(&data[i - 1]);
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
service_msgs__msg__ServiceEventInfo__Sequence__fini(service_msgs__msg__ServiceEventInfo__Sequence * array)
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
      service_msgs__msg__ServiceEventInfo__fini(&array->data[i]);
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

service_msgs__msg__ServiceEventInfo__Sequence *
service_msgs__msg__ServiceEventInfo__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  service_msgs__msg__ServiceEventInfo__Sequence * array = (service_msgs__msg__ServiceEventInfo__Sequence *)allocator.allocate(sizeof(service_msgs__msg__ServiceEventInfo__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = service_msgs__msg__ServiceEventInfo__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
service_msgs__msg__ServiceEventInfo__Sequence__destroy(service_msgs__msg__ServiceEventInfo__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    service_msgs__msg__ServiceEventInfo__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
service_msgs__msg__ServiceEventInfo__Sequence__are_equal(const service_msgs__msg__ServiceEventInfo__Sequence * lhs, const service_msgs__msg__ServiceEventInfo__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!service_msgs__msg__ServiceEventInfo__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
service_msgs__msg__ServiceEventInfo__Sequence__copy(
  const service_msgs__msg__ServiceEventInfo__Sequence * input,
  service_msgs__msg__ServiceEventInfo__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(service_msgs__msg__ServiceEventInfo);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    service_msgs__msg__ServiceEventInfo * data =
      (service_msgs__msg__ServiceEventInfo *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!service_msgs__msg__ServiceEventInfo__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          service_msgs__msg__ServiceEventInfo__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!service_msgs__msg__ServiceEventInfo__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
