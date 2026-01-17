// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from rcl_interfaces:srv/SetParametersAtomically.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "rcl_interfaces/srv/detail/set_parameters_atomically__rosidl_typesupport_introspection_c.h"
#include "rcl_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "rcl_interfaces/srv/detail/set_parameters_atomically__functions.h"
#include "rcl_interfaces/srv/detail/set_parameters_atomically__struct.h"


// Include directives for member types
// Member `parameters`
#include "rcl_interfaces/msg/parameter.h"
// Member `parameters`
#include "rcl_interfaces/msg/detail/parameter__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void rcl_interfaces__srv__SetParametersAtomically_Request__rosidl_typesupport_introspection_c__SetParametersAtomically_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  rcl_interfaces__srv__SetParametersAtomically_Request__init(message_memory);
}

void rcl_interfaces__srv__SetParametersAtomically_Request__rosidl_typesupport_introspection_c__SetParametersAtomically_Request_fini_function(void * message_memory)
{
  rcl_interfaces__srv__SetParametersAtomically_Request__fini(message_memory);
}

size_t rcl_interfaces__srv__SetParametersAtomically_Request__rosidl_typesupport_introspection_c__size_function__SetParametersAtomically_Request__parameters(
  const void * untyped_member)
{
  const rcl_interfaces__msg__Parameter__Sequence * member =
    (const rcl_interfaces__msg__Parameter__Sequence *)(untyped_member);
  return member->size;
}

const void * rcl_interfaces__srv__SetParametersAtomically_Request__rosidl_typesupport_introspection_c__get_const_function__SetParametersAtomically_Request__parameters(
  const void * untyped_member, size_t index)
{
  const rcl_interfaces__msg__Parameter__Sequence * member =
    (const rcl_interfaces__msg__Parameter__Sequence *)(untyped_member);
  return &member->data[index];
}

void * rcl_interfaces__srv__SetParametersAtomically_Request__rosidl_typesupport_introspection_c__get_function__SetParametersAtomically_Request__parameters(
  void * untyped_member, size_t index)
{
  rcl_interfaces__msg__Parameter__Sequence * member =
    (rcl_interfaces__msg__Parameter__Sequence *)(untyped_member);
  return &member->data[index];
}

void rcl_interfaces__srv__SetParametersAtomically_Request__rosidl_typesupport_introspection_c__fetch_function__SetParametersAtomically_Request__parameters(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rcl_interfaces__msg__Parameter * item =
    ((const rcl_interfaces__msg__Parameter *)
    rcl_interfaces__srv__SetParametersAtomically_Request__rosidl_typesupport_introspection_c__get_const_function__SetParametersAtomically_Request__parameters(untyped_member, index));
  rcl_interfaces__msg__Parameter * value =
    (rcl_interfaces__msg__Parameter *)(untyped_value);
  *value = *item;
}

void rcl_interfaces__srv__SetParametersAtomically_Request__rosidl_typesupport_introspection_c__assign_function__SetParametersAtomically_Request__parameters(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rcl_interfaces__msg__Parameter * item =
    ((rcl_interfaces__msg__Parameter *)
    rcl_interfaces__srv__SetParametersAtomically_Request__rosidl_typesupport_introspection_c__get_function__SetParametersAtomically_Request__parameters(untyped_member, index));
  const rcl_interfaces__msg__Parameter * value =
    (const rcl_interfaces__msg__Parameter *)(untyped_value);
  *item = *value;
}

bool rcl_interfaces__srv__SetParametersAtomically_Request__rosidl_typesupport_introspection_c__resize_function__SetParametersAtomically_Request__parameters(
  void * untyped_member, size_t size)
{
  rcl_interfaces__msg__Parameter__Sequence * member =
    (rcl_interfaces__msg__Parameter__Sequence *)(untyped_member);
  rcl_interfaces__msg__Parameter__Sequence__fini(member);
  return rcl_interfaces__msg__Parameter__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember rcl_interfaces__srv__SetParametersAtomically_Request__rosidl_typesupport_introspection_c__SetParametersAtomically_Request_message_member_array[1] = {
  {
    "parameters",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces__srv__SetParametersAtomically_Request, parameters),  // bytes offset in struct
    NULL,  // default value
    rcl_interfaces__srv__SetParametersAtomically_Request__rosidl_typesupport_introspection_c__size_function__SetParametersAtomically_Request__parameters,  // size() function pointer
    rcl_interfaces__srv__SetParametersAtomically_Request__rosidl_typesupport_introspection_c__get_const_function__SetParametersAtomically_Request__parameters,  // get_const(index) function pointer
    rcl_interfaces__srv__SetParametersAtomically_Request__rosidl_typesupport_introspection_c__get_function__SetParametersAtomically_Request__parameters,  // get(index) function pointer
    rcl_interfaces__srv__SetParametersAtomically_Request__rosidl_typesupport_introspection_c__fetch_function__SetParametersAtomically_Request__parameters,  // fetch(index, &value) function pointer
    rcl_interfaces__srv__SetParametersAtomically_Request__rosidl_typesupport_introspection_c__assign_function__SetParametersAtomically_Request__parameters,  // assign(index, value) function pointer
    rcl_interfaces__srv__SetParametersAtomically_Request__rosidl_typesupport_introspection_c__resize_function__SetParametersAtomically_Request__parameters  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers rcl_interfaces__srv__SetParametersAtomically_Request__rosidl_typesupport_introspection_c__SetParametersAtomically_Request_message_members = {
  "rcl_interfaces__srv",  // message namespace
  "SetParametersAtomically_Request",  // message name
  1,  // number of fields
  sizeof(rcl_interfaces__srv__SetParametersAtomically_Request),
  false,  // has_any_key_member_
  rcl_interfaces__srv__SetParametersAtomically_Request__rosidl_typesupport_introspection_c__SetParametersAtomically_Request_message_member_array,  // message members
  rcl_interfaces__srv__SetParametersAtomically_Request__rosidl_typesupport_introspection_c__SetParametersAtomically_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  rcl_interfaces__srv__SetParametersAtomically_Request__rosidl_typesupport_introspection_c__SetParametersAtomically_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t rcl_interfaces__srv__SetParametersAtomically_Request__rosidl_typesupport_introspection_c__SetParametersAtomically_Request_message_type_support_handle = {
  0,
  &rcl_interfaces__srv__SetParametersAtomically_Request__rosidl_typesupport_introspection_c__SetParametersAtomically_Request_message_members,
  get_message_typesupport_handle_function,
  &rcl_interfaces__srv__SetParametersAtomically_Request__get_type_hash,
  &rcl_interfaces__srv__SetParametersAtomically_Request__get_type_description,
  &rcl_interfaces__srv__SetParametersAtomically_Request__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_rcl_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, srv, SetParametersAtomically_Request)() {
  rcl_interfaces__srv__SetParametersAtomically_Request__rosidl_typesupport_introspection_c__SetParametersAtomically_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, msg, Parameter)();
  if (!rcl_interfaces__srv__SetParametersAtomically_Request__rosidl_typesupport_introspection_c__SetParametersAtomically_Request_message_type_support_handle.typesupport_identifier) {
    rcl_interfaces__srv__SetParametersAtomically_Request__rosidl_typesupport_introspection_c__SetParametersAtomically_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &rcl_interfaces__srv__SetParametersAtomically_Request__rosidl_typesupport_introspection_c__SetParametersAtomically_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "rcl_interfaces/srv/detail/set_parameters_atomically__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rcl_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "rcl_interfaces/srv/detail/set_parameters_atomically__functions.h"
// already included above
// #include "rcl_interfaces/srv/detail/set_parameters_atomically__struct.h"


// Include directives for member types
// Member `result`
#include "rcl_interfaces/msg/set_parameters_result.h"
// Member `result`
#include "rcl_interfaces/msg/detail/set_parameters_result__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void rcl_interfaces__srv__SetParametersAtomically_Response__rosidl_typesupport_introspection_c__SetParametersAtomically_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  rcl_interfaces__srv__SetParametersAtomically_Response__init(message_memory);
}

void rcl_interfaces__srv__SetParametersAtomically_Response__rosidl_typesupport_introspection_c__SetParametersAtomically_Response_fini_function(void * message_memory)
{
  rcl_interfaces__srv__SetParametersAtomically_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember rcl_interfaces__srv__SetParametersAtomically_Response__rosidl_typesupport_introspection_c__SetParametersAtomically_Response_message_member_array[1] = {
  {
    "result",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces__srv__SetParametersAtomically_Response, result),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers rcl_interfaces__srv__SetParametersAtomically_Response__rosidl_typesupport_introspection_c__SetParametersAtomically_Response_message_members = {
  "rcl_interfaces__srv",  // message namespace
  "SetParametersAtomically_Response",  // message name
  1,  // number of fields
  sizeof(rcl_interfaces__srv__SetParametersAtomically_Response),
  false,  // has_any_key_member_
  rcl_interfaces__srv__SetParametersAtomically_Response__rosidl_typesupport_introspection_c__SetParametersAtomically_Response_message_member_array,  // message members
  rcl_interfaces__srv__SetParametersAtomically_Response__rosidl_typesupport_introspection_c__SetParametersAtomically_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  rcl_interfaces__srv__SetParametersAtomically_Response__rosidl_typesupport_introspection_c__SetParametersAtomically_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t rcl_interfaces__srv__SetParametersAtomically_Response__rosidl_typesupport_introspection_c__SetParametersAtomically_Response_message_type_support_handle = {
  0,
  &rcl_interfaces__srv__SetParametersAtomically_Response__rosidl_typesupport_introspection_c__SetParametersAtomically_Response_message_members,
  get_message_typesupport_handle_function,
  &rcl_interfaces__srv__SetParametersAtomically_Response__get_type_hash,
  &rcl_interfaces__srv__SetParametersAtomically_Response__get_type_description,
  &rcl_interfaces__srv__SetParametersAtomically_Response__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_rcl_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, srv, SetParametersAtomically_Response)() {
  rcl_interfaces__srv__SetParametersAtomically_Response__rosidl_typesupport_introspection_c__SetParametersAtomically_Response_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, msg, SetParametersResult)();
  if (!rcl_interfaces__srv__SetParametersAtomically_Response__rosidl_typesupport_introspection_c__SetParametersAtomically_Response_message_type_support_handle.typesupport_identifier) {
    rcl_interfaces__srv__SetParametersAtomically_Response__rosidl_typesupport_introspection_c__SetParametersAtomically_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &rcl_interfaces__srv__SetParametersAtomically_Response__rosidl_typesupport_introspection_c__SetParametersAtomically_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "rcl_interfaces/srv/detail/set_parameters_atomically__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rcl_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "rcl_interfaces/srv/detail/set_parameters_atomically__functions.h"
// already included above
// #include "rcl_interfaces/srv/detail/set_parameters_atomically__struct.h"


// Include directives for member types
// Member `info`
#include "service_msgs/msg/service_event_info.h"
// Member `info`
#include "service_msgs/msg/detail/service_event_info__rosidl_typesupport_introspection_c.h"
// Member `request`
// Member `response`
#include "rcl_interfaces/srv/set_parameters_atomically.h"
// Member `request`
// Member `response`
// already included above
// #include "rcl_interfaces/srv/detail/set_parameters_atomically__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__SetParametersAtomically_Event_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  rcl_interfaces__srv__SetParametersAtomically_Event__init(message_memory);
}

void rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__SetParametersAtomically_Event_fini_function(void * message_memory)
{
  rcl_interfaces__srv__SetParametersAtomically_Event__fini(message_memory);
}

size_t rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__size_function__SetParametersAtomically_Event__request(
  const void * untyped_member)
{
  const rcl_interfaces__srv__SetParametersAtomically_Request__Sequence * member =
    (const rcl_interfaces__srv__SetParametersAtomically_Request__Sequence *)(untyped_member);
  return member->size;
}

const void * rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__get_const_function__SetParametersAtomically_Event__request(
  const void * untyped_member, size_t index)
{
  const rcl_interfaces__srv__SetParametersAtomically_Request__Sequence * member =
    (const rcl_interfaces__srv__SetParametersAtomically_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void * rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__get_function__SetParametersAtomically_Event__request(
  void * untyped_member, size_t index)
{
  rcl_interfaces__srv__SetParametersAtomically_Request__Sequence * member =
    (rcl_interfaces__srv__SetParametersAtomically_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__fetch_function__SetParametersAtomically_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rcl_interfaces__srv__SetParametersAtomically_Request * item =
    ((const rcl_interfaces__srv__SetParametersAtomically_Request *)
    rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__get_const_function__SetParametersAtomically_Event__request(untyped_member, index));
  rcl_interfaces__srv__SetParametersAtomically_Request * value =
    (rcl_interfaces__srv__SetParametersAtomically_Request *)(untyped_value);
  *value = *item;
}

void rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__assign_function__SetParametersAtomically_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rcl_interfaces__srv__SetParametersAtomically_Request * item =
    ((rcl_interfaces__srv__SetParametersAtomically_Request *)
    rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__get_function__SetParametersAtomically_Event__request(untyped_member, index));
  const rcl_interfaces__srv__SetParametersAtomically_Request * value =
    (const rcl_interfaces__srv__SetParametersAtomically_Request *)(untyped_value);
  *item = *value;
}

bool rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__resize_function__SetParametersAtomically_Event__request(
  void * untyped_member, size_t size)
{
  rcl_interfaces__srv__SetParametersAtomically_Request__Sequence * member =
    (rcl_interfaces__srv__SetParametersAtomically_Request__Sequence *)(untyped_member);
  rcl_interfaces__srv__SetParametersAtomically_Request__Sequence__fini(member);
  return rcl_interfaces__srv__SetParametersAtomically_Request__Sequence__init(member, size);
}

size_t rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__size_function__SetParametersAtomically_Event__response(
  const void * untyped_member)
{
  const rcl_interfaces__srv__SetParametersAtomically_Response__Sequence * member =
    (const rcl_interfaces__srv__SetParametersAtomically_Response__Sequence *)(untyped_member);
  return member->size;
}

const void * rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__get_const_function__SetParametersAtomically_Event__response(
  const void * untyped_member, size_t index)
{
  const rcl_interfaces__srv__SetParametersAtomically_Response__Sequence * member =
    (const rcl_interfaces__srv__SetParametersAtomically_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void * rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__get_function__SetParametersAtomically_Event__response(
  void * untyped_member, size_t index)
{
  rcl_interfaces__srv__SetParametersAtomically_Response__Sequence * member =
    (rcl_interfaces__srv__SetParametersAtomically_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__fetch_function__SetParametersAtomically_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rcl_interfaces__srv__SetParametersAtomically_Response * item =
    ((const rcl_interfaces__srv__SetParametersAtomically_Response *)
    rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__get_const_function__SetParametersAtomically_Event__response(untyped_member, index));
  rcl_interfaces__srv__SetParametersAtomically_Response * value =
    (rcl_interfaces__srv__SetParametersAtomically_Response *)(untyped_value);
  *value = *item;
}

void rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__assign_function__SetParametersAtomically_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rcl_interfaces__srv__SetParametersAtomically_Response * item =
    ((rcl_interfaces__srv__SetParametersAtomically_Response *)
    rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__get_function__SetParametersAtomically_Event__response(untyped_member, index));
  const rcl_interfaces__srv__SetParametersAtomically_Response * value =
    (const rcl_interfaces__srv__SetParametersAtomically_Response *)(untyped_value);
  *item = *value;
}

bool rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__resize_function__SetParametersAtomically_Event__response(
  void * untyped_member, size_t size)
{
  rcl_interfaces__srv__SetParametersAtomically_Response__Sequence * member =
    (rcl_interfaces__srv__SetParametersAtomically_Response__Sequence *)(untyped_member);
  rcl_interfaces__srv__SetParametersAtomically_Response__Sequence__fini(member);
  return rcl_interfaces__srv__SetParametersAtomically_Response__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__SetParametersAtomically_Event_message_member_array[3] = {
  {
    "info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces__srv__SetParametersAtomically_Event, info),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "request",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(rcl_interfaces__srv__SetParametersAtomically_Event, request),  // bytes offset in struct
    NULL,  // default value
    rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__size_function__SetParametersAtomically_Event__request,  // size() function pointer
    rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__get_const_function__SetParametersAtomically_Event__request,  // get_const(index) function pointer
    rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__get_function__SetParametersAtomically_Event__request,  // get(index) function pointer
    rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__fetch_function__SetParametersAtomically_Event__request,  // fetch(index, &value) function pointer
    rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__assign_function__SetParametersAtomically_Event__request,  // assign(index, value) function pointer
    rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__resize_function__SetParametersAtomically_Event__request  // resize(index) function pointer
  },
  {
    "response",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(rcl_interfaces__srv__SetParametersAtomically_Event, response),  // bytes offset in struct
    NULL,  // default value
    rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__size_function__SetParametersAtomically_Event__response,  // size() function pointer
    rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__get_const_function__SetParametersAtomically_Event__response,  // get_const(index) function pointer
    rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__get_function__SetParametersAtomically_Event__response,  // get(index) function pointer
    rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__fetch_function__SetParametersAtomically_Event__response,  // fetch(index, &value) function pointer
    rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__assign_function__SetParametersAtomically_Event__response,  // assign(index, value) function pointer
    rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__resize_function__SetParametersAtomically_Event__response  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__SetParametersAtomically_Event_message_members = {
  "rcl_interfaces__srv",  // message namespace
  "SetParametersAtomically_Event",  // message name
  3,  // number of fields
  sizeof(rcl_interfaces__srv__SetParametersAtomically_Event),
  false,  // has_any_key_member_
  rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__SetParametersAtomically_Event_message_member_array,  // message members
  rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__SetParametersAtomically_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__SetParametersAtomically_Event_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__SetParametersAtomically_Event_message_type_support_handle = {
  0,
  &rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__SetParametersAtomically_Event_message_members,
  get_message_typesupport_handle_function,
  &rcl_interfaces__srv__SetParametersAtomically_Event__get_type_hash,
  &rcl_interfaces__srv__SetParametersAtomically_Event__get_type_description,
  &rcl_interfaces__srv__SetParametersAtomically_Event__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_rcl_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, srv, SetParametersAtomically_Event)() {
  rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__SetParametersAtomically_Event_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_msgs, msg, ServiceEventInfo)();
  rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__SetParametersAtomically_Event_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, srv, SetParametersAtomically_Request)();
  rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__SetParametersAtomically_Event_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, srv, SetParametersAtomically_Response)();
  if (!rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__SetParametersAtomically_Event_message_type_support_handle.typesupport_identifier) {
    rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__SetParametersAtomically_Event_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__SetParametersAtomically_Event_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "rcl_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rcl_interfaces/srv/detail/set_parameters_atomically__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers rcl_interfaces__srv__detail__set_parameters_atomically__rosidl_typesupport_introspection_c__SetParametersAtomically_service_members = {
  "rcl_interfaces__srv",  // service namespace
  "SetParametersAtomically",  // service name
  // the following fields are initialized below on first access
  NULL,  // request message
  // rcl_interfaces__srv__detail__set_parameters_atomically__rosidl_typesupport_introspection_c__SetParametersAtomically_Request_message_type_support_handle,
  NULL,  // response message
  // rcl_interfaces__srv__detail__set_parameters_atomically__rosidl_typesupport_introspection_c__SetParametersAtomically_Response_message_type_support_handle
  NULL  // event_message
  // rcl_interfaces__srv__detail__set_parameters_atomically__rosidl_typesupport_introspection_c__SetParametersAtomically_Response_message_type_support_handle
};


static rosidl_service_type_support_t rcl_interfaces__srv__detail__set_parameters_atomically__rosidl_typesupport_introspection_c__SetParametersAtomically_service_type_support_handle = {
  0,
  &rcl_interfaces__srv__detail__set_parameters_atomically__rosidl_typesupport_introspection_c__SetParametersAtomically_service_members,
  get_service_typesupport_handle_function,
  &rcl_interfaces__srv__SetParametersAtomically_Request__rosidl_typesupport_introspection_c__SetParametersAtomically_Request_message_type_support_handle,
  &rcl_interfaces__srv__SetParametersAtomically_Response__rosidl_typesupport_introspection_c__SetParametersAtomically_Response_message_type_support_handle,
  &rcl_interfaces__srv__SetParametersAtomically_Event__rosidl_typesupport_introspection_c__SetParametersAtomically_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    rcl_interfaces,
    srv,
    SetParametersAtomically
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    rcl_interfaces,
    srv,
    SetParametersAtomically
  ),
  &rcl_interfaces__srv__SetParametersAtomically__get_type_hash,
  &rcl_interfaces__srv__SetParametersAtomically__get_type_description,
  &rcl_interfaces__srv__SetParametersAtomically__get_type_description_sources,
};

// Forward declaration of message type support functions for service members
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, srv, SetParametersAtomically_Request)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, srv, SetParametersAtomically_Response)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, srv, SetParametersAtomically_Event)(void);

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_rcl_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, srv, SetParametersAtomically)(void) {
  if (!rcl_interfaces__srv__detail__set_parameters_atomically__rosidl_typesupport_introspection_c__SetParametersAtomically_service_type_support_handle.typesupport_identifier) {
    rcl_interfaces__srv__detail__set_parameters_atomically__rosidl_typesupport_introspection_c__SetParametersAtomically_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)rcl_interfaces__srv__detail__set_parameters_atomically__rosidl_typesupport_introspection_c__SetParametersAtomically_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, srv, SetParametersAtomically_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, srv, SetParametersAtomically_Response)()->data;
  }
  if (!service_members->event_members_) {
    service_members->event_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, srv, SetParametersAtomically_Event)()->data;
  }

  return &rcl_interfaces__srv__detail__set_parameters_atomically__rosidl_typesupport_introspection_c__SetParametersAtomically_service_type_support_handle;
}
