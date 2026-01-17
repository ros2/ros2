// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from lifecycle_msgs:srv/ChangeState.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "lifecycle_msgs/srv/detail/change_state__rosidl_typesupport_introspection_c.h"
#include "lifecycle_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "lifecycle_msgs/srv/detail/change_state__functions.h"
#include "lifecycle_msgs/srv/detail/change_state__struct.h"


// Include directives for member types
// Member `transition`
#include "lifecycle_msgs/msg/transition.h"
// Member `transition`
#include "lifecycle_msgs/msg/detail/transition__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void lifecycle_msgs__srv__ChangeState_Request__rosidl_typesupport_introspection_c__ChangeState_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  lifecycle_msgs__srv__ChangeState_Request__init(message_memory);
}

void lifecycle_msgs__srv__ChangeState_Request__rosidl_typesupport_introspection_c__ChangeState_Request_fini_function(void * message_memory)
{
  lifecycle_msgs__srv__ChangeState_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember lifecycle_msgs__srv__ChangeState_Request__rosidl_typesupport_introspection_c__ChangeState_Request_message_member_array[1] = {
  {
    "transition",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lifecycle_msgs__srv__ChangeState_Request, transition),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers lifecycle_msgs__srv__ChangeState_Request__rosidl_typesupport_introspection_c__ChangeState_Request_message_members = {
  "lifecycle_msgs__srv",  // message namespace
  "ChangeState_Request",  // message name
  1,  // number of fields
  sizeof(lifecycle_msgs__srv__ChangeState_Request),
  false,  // has_any_key_member_
  lifecycle_msgs__srv__ChangeState_Request__rosidl_typesupport_introspection_c__ChangeState_Request_message_member_array,  // message members
  lifecycle_msgs__srv__ChangeState_Request__rosidl_typesupport_introspection_c__ChangeState_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  lifecycle_msgs__srv__ChangeState_Request__rosidl_typesupport_introspection_c__ChangeState_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t lifecycle_msgs__srv__ChangeState_Request__rosidl_typesupport_introspection_c__ChangeState_Request_message_type_support_handle = {
  0,
  &lifecycle_msgs__srv__ChangeState_Request__rosidl_typesupport_introspection_c__ChangeState_Request_message_members,
  get_message_typesupport_handle_function,
  &lifecycle_msgs__srv__ChangeState_Request__get_type_hash,
  &lifecycle_msgs__srv__ChangeState_Request__get_type_description,
  &lifecycle_msgs__srv__ChangeState_Request__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_lifecycle_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, lifecycle_msgs, srv, ChangeState_Request)() {
  lifecycle_msgs__srv__ChangeState_Request__rosidl_typesupport_introspection_c__ChangeState_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, lifecycle_msgs, msg, Transition)();
  if (!lifecycle_msgs__srv__ChangeState_Request__rosidl_typesupport_introspection_c__ChangeState_Request_message_type_support_handle.typesupport_identifier) {
    lifecycle_msgs__srv__ChangeState_Request__rosidl_typesupport_introspection_c__ChangeState_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &lifecycle_msgs__srv__ChangeState_Request__rosidl_typesupport_introspection_c__ChangeState_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "lifecycle_msgs/srv/detail/change_state__rosidl_typesupport_introspection_c.h"
// already included above
// #include "lifecycle_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "lifecycle_msgs/srv/detail/change_state__functions.h"
// already included above
// #include "lifecycle_msgs/srv/detail/change_state__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void lifecycle_msgs__srv__ChangeState_Response__rosidl_typesupport_introspection_c__ChangeState_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  lifecycle_msgs__srv__ChangeState_Response__init(message_memory);
}

void lifecycle_msgs__srv__ChangeState_Response__rosidl_typesupport_introspection_c__ChangeState_Response_fini_function(void * message_memory)
{
  lifecycle_msgs__srv__ChangeState_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember lifecycle_msgs__srv__ChangeState_Response__rosidl_typesupport_introspection_c__ChangeState_Response_message_member_array[1] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lifecycle_msgs__srv__ChangeState_Response, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers lifecycle_msgs__srv__ChangeState_Response__rosidl_typesupport_introspection_c__ChangeState_Response_message_members = {
  "lifecycle_msgs__srv",  // message namespace
  "ChangeState_Response",  // message name
  1,  // number of fields
  sizeof(lifecycle_msgs__srv__ChangeState_Response),
  false,  // has_any_key_member_
  lifecycle_msgs__srv__ChangeState_Response__rosidl_typesupport_introspection_c__ChangeState_Response_message_member_array,  // message members
  lifecycle_msgs__srv__ChangeState_Response__rosidl_typesupport_introspection_c__ChangeState_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  lifecycle_msgs__srv__ChangeState_Response__rosidl_typesupport_introspection_c__ChangeState_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t lifecycle_msgs__srv__ChangeState_Response__rosidl_typesupport_introspection_c__ChangeState_Response_message_type_support_handle = {
  0,
  &lifecycle_msgs__srv__ChangeState_Response__rosidl_typesupport_introspection_c__ChangeState_Response_message_members,
  get_message_typesupport_handle_function,
  &lifecycle_msgs__srv__ChangeState_Response__get_type_hash,
  &lifecycle_msgs__srv__ChangeState_Response__get_type_description,
  &lifecycle_msgs__srv__ChangeState_Response__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_lifecycle_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, lifecycle_msgs, srv, ChangeState_Response)() {
  if (!lifecycle_msgs__srv__ChangeState_Response__rosidl_typesupport_introspection_c__ChangeState_Response_message_type_support_handle.typesupport_identifier) {
    lifecycle_msgs__srv__ChangeState_Response__rosidl_typesupport_introspection_c__ChangeState_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &lifecycle_msgs__srv__ChangeState_Response__rosidl_typesupport_introspection_c__ChangeState_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "lifecycle_msgs/srv/detail/change_state__rosidl_typesupport_introspection_c.h"
// already included above
// #include "lifecycle_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "lifecycle_msgs/srv/detail/change_state__functions.h"
// already included above
// #include "lifecycle_msgs/srv/detail/change_state__struct.h"


// Include directives for member types
// Member `info`
#include "service_msgs/msg/service_event_info.h"
// Member `info`
#include "service_msgs/msg/detail/service_event_info__rosidl_typesupport_introspection_c.h"
// Member `request`
// Member `response`
#include "lifecycle_msgs/srv/change_state.h"
// Member `request`
// Member `response`
// already included above
// #include "lifecycle_msgs/srv/detail/change_state__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__ChangeState_Event_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  lifecycle_msgs__srv__ChangeState_Event__init(message_memory);
}

void lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__ChangeState_Event_fini_function(void * message_memory)
{
  lifecycle_msgs__srv__ChangeState_Event__fini(message_memory);
}

size_t lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__size_function__ChangeState_Event__request(
  const void * untyped_member)
{
  const lifecycle_msgs__srv__ChangeState_Request__Sequence * member =
    (const lifecycle_msgs__srv__ChangeState_Request__Sequence *)(untyped_member);
  return member->size;
}

const void * lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__get_const_function__ChangeState_Event__request(
  const void * untyped_member, size_t index)
{
  const lifecycle_msgs__srv__ChangeState_Request__Sequence * member =
    (const lifecycle_msgs__srv__ChangeState_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void * lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__get_function__ChangeState_Event__request(
  void * untyped_member, size_t index)
{
  lifecycle_msgs__srv__ChangeState_Request__Sequence * member =
    (lifecycle_msgs__srv__ChangeState_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__fetch_function__ChangeState_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const lifecycle_msgs__srv__ChangeState_Request * item =
    ((const lifecycle_msgs__srv__ChangeState_Request *)
    lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__get_const_function__ChangeState_Event__request(untyped_member, index));
  lifecycle_msgs__srv__ChangeState_Request * value =
    (lifecycle_msgs__srv__ChangeState_Request *)(untyped_value);
  *value = *item;
}

void lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__assign_function__ChangeState_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  lifecycle_msgs__srv__ChangeState_Request * item =
    ((lifecycle_msgs__srv__ChangeState_Request *)
    lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__get_function__ChangeState_Event__request(untyped_member, index));
  const lifecycle_msgs__srv__ChangeState_Request * value =
    (const lifecycle_msgs__srv__ChangeState_Request *)(untyped_value);
  *item = *value;
}

bool lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__resize_function__ChangeState_Event__request(
  void * untyped_member, size_t size)
{
  lifecycle_msgs__srv__ChangeState_Request__Sequence * member =
    (lifecycle_msgs__srv__ChangeState_Request__Sequence *)(untyped_member);
  lifecycle_msgs__srv__ChangeState_Request__Sequence__fini(member);
  return lifecycle_msgs__srv__ChangeState_Request__Sequence__init(member, size);
}

size_t lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__size_function__ChangeState_Event__response(
  const void * untyped_member)
{
  const lifecycle_msgs__srv__ChangeState_Response__Sequence * member =
    (const lifecycle_msgs__srv__ChangeState_Response__Sequence *)(untyped_member);
  return member->size;
}

const void * lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__get_const_function__ChangeState_Event__response(
  const void * untyped_member, size_t index)
{
  const lifecycle_msgs__srv__ChangeState_Response__Sequence * member =
    (const lifecycle_msgs__srv__ChangeState_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void * lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__get_function__ChangeState_Event__response(
  void * untyped_member, size_t index)
{
  lifecycle_msgs__srv__ChangeState_Response__Sequence * member =
    (lifecycle_msgs__srv__ChangeState_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__fetch_function__ChangeState_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const lifecycle_msgs__srv__ChangeState_Response * item =
    ((const lifecycle_msgs__srv__ChangeState_Response *)
    lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__get_const_function__ChangeState_Event__response(untyped_member, index));
  lifecycle_msgs__srv__ChangeState_Response * value =
    (lifecycle_msgs__srv__ChangeState_Response *)(untyped_value);
  *value = *item;
}

void lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__assign_function__ChangeState_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  lifecycle_msgs__srv__ChangeState_Response * item =
    ((lifecycle_msgs__srv__ChangeState_Response *)
    lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__get_function__ChangeState_Event__response(untyped_member, index));
  const lifecycle_msgs__srv__ChangeState_Response * value =
    (const lifecycle_msgs__srv__ChangeState_Response *)(untyped_value);
  *item = *value;
}

bool lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__resize_function__ChangeState_Event__response(
  void * untyped_member, size_t size)
{
  lifecycle_msgs__srv__ChangeState_Response__Sequence * member =
    (lifecycle_msgs__srv__ChangeState_Response__Sequence *)(untyped_member);
  lifecycle_msgs__srv__ChangeState_Response__Sequence__fini(member);
  return lifecycle_msgs__srv__ChangeState_Response__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__ChangeState_Event_message_member_array[3] = {
  {
    "info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lifecycle_msgs__srv__ChangeState_Event, info),  // bytes offset in struct
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
    offsetof(lifecycle_msgs__srv__ChangeState_Event, request),  // bytes offset in struct
    NULL,  // default value
    lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__size_function__ChangeState_Event__request,  // size() function pointer
    lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__get_const_function__ChangeState_Event__request,  // get_const(index) function pointer
    lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__get_function__ChangeState_Event__request,  // get(index) function pointer
    lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__fetch_function__ChangeState_Event__request,  // fetch(index, &value) function pointer
    lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__assign_function__ChangeState_Event__request,  // assign(index, value) function pointer
    lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__resize_function__ChangeState_Event__request  // resize(index) function pointer
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
    offsetof(lifecycle_msgs__srv__ChangeState_Event, response),  // bytes offset in struct
    NULL,  // default value
    lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__size_function__ChangeState_Event__response,  // size() function pointer
    lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__get_const_function__ChangeState_Event__response,  // get_const(index) function pointer
    lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__get_function__ChangeState_Event__response,  // get(index) function pointer
    lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__fetch_function__ChangeState_Event__response,  // fetch(index, &value) function pointer
    lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__assign_function__ChangeState_Event__response,  // assign(index, value) function pointer
    lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__resize_function__ChangeState_Event__response  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__ChangeState_Event_message_members = {
  "lifecycle_msgs__srv",  // message namespace
  "ChangeState_Event",  // message name
  3,  // number of fields
  sizeof(lifecycle_msgs__srv__ChangeState_Event),
  false,  // has_any_key_member_
  lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__ChangeState_Event_message_member_array,  // message members
  lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__ChangeState_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__ChangeState_Event_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__ChangeState_Event_message_type_support_handle = {
  0,
  &lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__ChangeState_Event_message_members,
  get_message_typesupport_handle_function,
  &lifecycle_msgs__srv__ChangeState_Event__get_type_hash,
  &lifecycle_msgs__srv__ChangeState_Event__get_type_description,
  &lifecycle_msgs__srv__ChangeState_Event__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_lifecycle_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, lifecycle_msgs, srv, ChangeState_Event)() {
  lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__ChangeState_Event_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_msgs, msg, ServiceEventInfo)();
  lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__ChangeState_Event_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, lifecycle_msgs, srv, ChangeState_Request)();
  lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__ChangeState_Event_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, lifecycle_msgs, srv, ChangeState_Response)();
  if (!lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__ChangeState_Event_message_type_support_handle.typesupport_identifier) {
    lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__ChangeState_Event_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__ChangeState_Event_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "lifecycle_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "lifecycle_msgs/srv/detail/change_state__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers lifecycle_msgs__srv__detail__change_state__rosidl_typesupport_introspection_c__ChangeState_service_members = {
  "lifecycle_msgs__srv",  // service namespace
  "ChangeState",  // service name
  // the following fields are initialized below on first access
  NULL,  // request message
  // lifecycle_msgs__srv__detail__change_state__rosidl_typesupport_introspection_c__ChangeState_Request_message_type_support_handle,
  NULL,  // response message
  // lifecycle_msgs__srv__detail__change_state__rosidl_typesupport_introspection_c__ChangeState_Response_message_type_support_handle
  NULL  // event_message
  // lifecycle_msgs__srv__detail__change_state__rosidl_typesupport_introspection_c__ChangeState_Response_message_type_support_handle
};


static rosidl_service_type_support_t lifecycle_msgs__srv__detail__change_state__rosidl_typesupport_introspection_c__ChangeState_service_type_support_handle = {
  0,
  &lifecycle_msgs__srv__detail__change_state__rosidl_typesupport_introspection_c__ChangeState_service_members,
  get_service_typesupport_handle_function,
  &lifecycle_msgs__srv__ChangeState_Request__rosidl_typesupport_introspection_c__ChangeState_Request_message_type_support_handle,
  &lifecycle_msgs__srv__ChangeState_Response__rosidl_typesupport_introspection_c__ChangeState_Response_message_type_support_handle,
  &lifecycle_msgs__srv__ChangeState_Event__rosidl_typesupport_introspection_c__ChangeState_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    lifecycle_msgs,
    srv,
    ChangeState
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    lifecycle_msgs,
    srv,
    ChangeState
  ),
  &lifecycle_msgs__srv__ChangeState__get_type_hash,
  &lifecycle_msgs__srv__ChangeState__get_type_description,
  &lifecycle_msgs__srv__ChangeState__get_type_description_sources,
};

// Forward declaration of message type support functions for service members
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, lifecycle_msgs, srv, ChangeState_Request)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, lifecycle_msgs, srv, ChangeState_Response)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, lifecycle_msgs, srv, ChangeState_Event)(void);

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_lifecycle_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, lifecycle_msgs, srv, ChangeState)(void) {
  if (!lifecycle_msgs__srv__detail__change_state__rosidl_typesupport_introspection_c__ChangeState_service_type_support_handle.typesupport_identifier) {
    lifecycle_msgs__srv__detail__change_state__rosidl_typesupport_introspection_c__ChangeState_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)lifecycle_msgs__srv__detail__change_state__rosidl_typesupport_introspection_c__ChangeState_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, lifecycle_msgs, srv, ChangeState_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, lifecycle_msgs, srv, ChangeState_Response)()->data;
  }
  if (!service_members->event_members_) {
    service_members->event_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, lifecycle_msgs, srv, ChangeState_Event)()->data;
  }

  return &lifecycle_msgs__srv__detail__change_state__rosidl_typesupport_introspection_c__ChangeState_service_type_support_handle;
}
