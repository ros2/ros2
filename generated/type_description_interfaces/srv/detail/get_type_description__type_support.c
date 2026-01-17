// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from type_description_interfaces:srv/GetTypeDescription.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "type_description_interfaces/srv/detail/get_type_description__rosidl_typesupport_introspection_c.h"
#include "type_description_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "type_description_interfaces/srv/detail/get_type_description__functions.h"
#include "type_description_interfaces/srv/detail/get_type_description__struct.h"


// Include directives for member types
// Member `type_name`
// Member `type_hash`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void type_description_interfaces__srv__GetTypeDescription_Request__rosidl_typesupport_introspection_c__GetTypeDescription_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  type_description_interfaces__srv__GetTypeDescription_Request__init(message_memory);
}

void type_description_interfaces__srv__GetTypeDescription_Request__rosidl_typesupport_introspection_c__GetTypeDescription_Request_fini_function(void * message_memory)
{
  type_description_interfaces__srv__GetTypeDescription_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember type_description_interfaces__srv__GetTypeDescription_Request__rosidl_typesupport_introspection_c__GetTypeDescription_Request_message_member_array[3] = {
  {
    "type_name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(type_description_interfaces__srv__GetTypeDescription_Request, type_name),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "type_hash",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(type_description_interfaces__srv__GetTypeDescription_Request, type_hash),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "include_type_sources",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(type_description_interfaces__srv__GetTypeDescription_Request, include_type_sources),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers type_description_interfaces__srv__GetTypeDescription_Request__rosidl_typesupport_introspection_c__GetTypeDescription_Request_message_members = {
  "type_description_interfaces__srv",  // message namespace
  "GetTypeDescription_Request",  // message name
  3,  // number of fields
  sizeof(type_description_interfaces__srv__GetTypeDescription_Request),
  false,  // has_any_key_member_
  type_description_interfaces__srv__GetTypeDescription_Request__rosidl_typesupport_introspection_c__GetTypeDescription_Request_message_member_array,  // message members
  type_description_interfaces__srv__GetTypeDescription_Request__rosidl_typesupport_introspection_c__GetTypeDescription_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  type_description_interfaces__srv__GetTypeDescription_Request__rosidl_typesupport_introspection_c__GetTypeDescription_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t type_description_interfaces__srv__GetTypeDescription_Request__rosidl_typesupport_introspection_c__GetTypeDescription_Request_message_type_support_handle = {
  0,
  &type_description_interfaces__srv__GetTypeDescription_Request__rosidl_typesupport_introspection_c__GetTypeDescription_Request_message_members,
  get_message_typesupport_handle_function,
  &type_description_interfaces__srv__GetTypeDescription_Request__get_type_hash,
  &type_description_interfaces__srv__GetTypeDescription_Request__get_type_description,
  &type_description_interfaces__srv__GetTypeDescription_Request__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_type_description_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, type_description_interfaces, srv, GetTypeDescription_Request)() {
  if (!type_description_interfaces__srv__GetTypeDescription_Request__rosidl_typesupport_introspection_c__GetTypeDescription_Request_message_type_support_handle.typesupport_identifier) {
    type_description_interfaces__srv__GetTypeDescription_Request__rosidl_typesupport_introspection_c__GetTypeDescription_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &type_description_interfaces__srv__GetTypeDescription_Request__rosidl_typesupport_introspection_c__GetTypeDescription_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "type_description_interfaces/srv/detail/get_type_description__rosidl_typesupport_introspection_c.h"
// already included above
// #include "type_description_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "type_description_interfaces/srv/detail/get_type_description__functions.h"
// already included above
// #include "type_description_interfaces/srv/detail/get_type_description__struct.h"


// Include directives for member types
// Member `failure_reason`
// already included above
// #include "rosidl_runtime_c/string_functions.h"
// Member `type_description`
#include "type_description_interfaces/msg/type_description.h"
// Member `type_description`
#include "type_description_interfaces/msg/detail/type_description__rosidl_typesupport_introspection_c.h"
// Member `type_sources`
#include "type_description_interfaces/msg/type_source.h"
// Member `type_sources`
#include "type_description_interfaces/msg/detail/type_source__rosidl_typesupport_introspection_c.h"
// Member `extra_information`
#include "type_description_interfaces/msg/key_value.h"
// Member `extra_information`
#include "type_description_interfaces/msg/detail/key_value__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__GetTypeDescription_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  type_description_interfaces__srv__GetTypeDescription_Response__init(message_memory);
}

void type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__GetTypeDescription_Response_fini_function(void * message_memory)
{
  type_description_interfaces__srv__GetTypeDescription_Response__fini(message_memory);
}

size_t type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__size_function__GetTypeDescription_Response__type_sources(
  const void * untyped_member)
{
  const type_description_interfaces__msg__TypeSource__Sequence * member =
    (const type_description_interfaces__msg__TypeSource__Sequence *)(untyped_member);
  return member->size;
}

const void * type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__get_const_function__GetTypeDescription_Response__type_sources(
  const void * untyped_member, size_t index)
{
  const type_description_interfaces__msg__TypeSource__Sequence * member =
    (const type_description_interfaces__msg__TypeSource__Sequence *)(untyped_member);
  return &member->data[index];
}

void * type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__get_function__GetTypeDescription_Response__type_sources(
  void * untyped_member, size_t index)
{
  type_description_interfaces__msg__TypeSource__Sequence * member =
    (type_description_interfaces__msg__TypeSource__Sequence *)(untyped_member);
  return &member->data[index];
}

void type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__fetch_function__GetTypeDescription_Response__type_sources(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const type_description_interfaces__msg__TypeSource * item =
    ((const type_description_interfaces__msg__TypeSource *)
    type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__get_const_function__GetTypeDescription_Response__type_sources(untyped_member, index));
  type_description_interfaces__msg__TypeSource * value =
    (type_description_interfaces__msg__TypeSource *)(untyped_value);
  *value = *item;
}

void type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__assign_function__GetTypeDescription_Response__type_sources(
  void * untyped_member, size_t index, const void * untyped_value)
{
  type_description_interfaces__msg__TypeSource * item =
    ((type_description_interfaces__msg__TypeSource *)
    type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__get_function__GetTypeDescription_Response__type_sources(untyped_member, index));
  const type_description_interfaces__msg__TypeSource * value =
    (const type_description_interfaces__msg__TypeSource *)(untyped_value);
  *item = *value;
}

bool type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__resize_function__GetTypeDescription_Response__type_sources(
  void * untyped_member, size_t size)
{
  type_description_interfaces__msg__TypeSource__Sequence * member =
    (type_description_interfaces__msg__TypeSource__Sequence *)(untyped_member);
  type_description_interfaces__msg__TypeSource__Sequence__fini(member);
  return type_description_interfaces__msg__TypeSource__Sequence__init(member, size);
}

size_t type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__size_function__GetTypeDescription_Response__extra_information(
  const void * untyped_member)
{
  const type_description_interfaces__msg__KeyValue__Sequence * member =
    (const type_description_interfaces__msg__KeyValue__Sequence *)(untyped_member);
  return member->size;
}

const void * type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__get_const_function__GetTypeDescription_Response__extra_information(
  const void * untyped_member, size_t index)
{
  const type_description_interfaces__msg__KeyValue__Sequence * member =
    (const type_description_interfaces__msg__KeyValue__Sequence *)(untyped_member);
  return &member->data[index];
}

void * type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__get_function__GetTypeDescription_Response__extra_information(
  void * untyped_member, size_t index)
{
  type_description_interfaces__msg__KeyValue__Sequence * member =
    (type_description_interfaces__msg__KeyValue__Sequence *)(untyped_member);
  return &member->data[index];
}

void type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__fetch_function__GetTypeDescription_Response__extra_information(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const type_description_interfaces__msg__KeyValue * item =
    ((const type_description_interfaces__msg__KeyValue *)
    type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__get_const_function__GetTypeDescription_Response__extra_information(untyped_member, index));
  type_description_interfaces__msg__KeyValue * value =
    (type_description_interfaces__msg__KeyValue *)(untyped_value);
  *value = *item;
}

void type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__assign_function__GetTypeDescription_Response__extra_information(
  void * untyped_member, size_t index, const void * untyped_value)
{
  type_description_interfaces__msg__KeyValue * item =
    ((type_description_interfaces__msg__KeyValue *)
    type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__get_function__GetTypeDescription_Response__extra_information(untyped_member, index));
  const type_description_interfaces__msg__KeyValue * value =
    (const type_description_interfaces__msg__KeyValue *)(untyped_value);
  *item = *value;
}

bool type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__resize_function__GetTypeDescription_Response__extra_information(
  void * untyped_member, size_t size)
{
  type_description_interfaces__msg__KeyValue__Sequence * member =
    (type_description_interfaces__msg__KeyValue__Sequence *)(untyped_member);
  type_description_interfaces__msg__KeyValue__Sequence__fini(member);
  return type_description_interfaces__msg__KeyValue__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__GetTypeDescription_Response_message_member_array[5] = {
  {
    "successful",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(type_description_interfaces__srv__GetTypeDescription_Response, successful),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "failure_reason",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(type_description_interfaces__srv__GetTypeDescription_Response, failure_reason),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "type_description",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(type_description_interfaces__srv__GetTypeDescription_Response, type_description),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "type_sources",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(type_description_interfaces__srv__GetTypeDescription_Response, type_sources),  // bytes offset in struct
    NULL,  // default value
    type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__size_function__GetTypeDescription_Response__type_sources,  // size() function pointer
    type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__get_const_function__GetTypeDescription_Response__type_sources,  // get_const(index) function pointer
    type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__get_function__GetTypeDescription_Response__type_sources,  // get(index) function pointer
    type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__fetch_function__GetTypeDescription_Response__type_sources,  // fetch(index, &value) function pointer
    type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__assign_function__GetTypeDescription_Response__type_sources,  // assign(index, value) function pointer
    type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__resize_function__GetTypeDescription_Response__type_sources  // resize(index) function pointer
  },
  {
    "extra_information",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(type_description_interfaces__srv__GetTypeDescription_Response, extra_information),  // bytes offset in struct
    NULL,  // default value
    type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__size_function__GetTypeDescription_Response__extra_information,  // size() function pointer
    type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__get_const_function__GetTypeDescription_Response__extra_information,  // get_const(index) function pointer
    type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__get_function__GetTypeDescription_Response__extra_information,  // get(index) function pointer
    type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__fetch_function__GetTypeDescription_Response__extra_information,  // fetch(index, &value) function pointer
    type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__assign_function__GetTypeDescription_Response__extra_information,  // assign(index, value) function pointer
    type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__resize_function__GetTypeDescription_Response__extra_information  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__GetTypeDescription_Response_message_members = {
  "type_description_interfaces__srv",  // message namespace
  "GetTypeDescription_Response",  // message name
  5,  // number of fields
  sizeof(type_description_interfaces__srv__GetTypeDescription_Response),
  false,  // has_any_key_member_
  type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__GetTypeDescription_Response_message_member_array,  // message members
  type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__GetTypeDescription_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__GetTypeDescription_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__GetTypeDescription_Response_message_type_support_handle = {
  0,
  &type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__GetTypeDescription_Response_message_members,
  get_message_typesupport_handle_function,
  &type_description_interfaces__srv__GetTypeDescription_Response__get_type_hash,
  &type_description_interfaces__srv__GetTypeDescription_Response__get_type_description,
  &type_description_interfaces__srv__GetTypeDescription_Response__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_type_description_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, type_description_interfaces, srv, GetTypeDescription_Response)() {
  type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__GetTypeDescription_Response_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, type_description_interfaces, msg, TypeDescription)();
  type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__GetTypeDescription_Response_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, type_description_interfaces, msg, TypeSource)();
  type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__GetTypeDescription_Response_message_member_array[4].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, type_description_interfaces, msg, KeyValue)();
  if (!type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__GetTypeDescription_Response_message_type_support_handle.typesupport_identifier) {
    type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__GetTypeDescription_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__GetTypeDescription_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "type_description_interfaces/srv/detail/get_type_description__rosidl_typesupport_introspection_c.h"
// already included above
// #include "type_description_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "type_description_interfaces/srv/detail/get_type_description__functions.h"
// already included above
// #include "type_description_interfaces/srv/detail/get_type_description__struct.h"


// Include directives for member types
// Member `info`
#include "service_msgs/msg/service_event_info.h"
// Member `info`
#include "service_msgs/msg/detail/service_event_info__rosidl_typesupport_introspection_c.h"
// Member `request`
// Member `response`
#include "type_description_interfaces/srv/get_type_description.h"
// Member `request`
// Member `response`
// already included above
// #include "type_description_interfaces/srv/detail/get_type_description__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__GetTypeDescription_Event_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  type_description_interfaces__srv__GetTypeDescription_Event__init(message_memory);
}

void type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__GetTypeDescription_Event_fini_function(void * message_memory)
{
  type_description_interfaces__srv__GetTypeDescription_Event__fini(message_memory);
}

size_t type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__size_function__GetTypeDescription_Event__request(
  const void * untyped_member)
{
  const type_description_interfaces__srv__GetTypeDescription_Request__Sequence * member =
    (const type_description_interfaces__srv__GetTypeDescription_Request__Sequence *)(untyped_member);
  return member->size;
}

const void * type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__get_const_function__GetTypeDescription_Event__request(
  const void * untyped_member, size_t index)
{
  const type_description_interfaces__srv__GetTypeDescription_Request__Sequence * member =
    (const type_description_interfaces__srv__GetTypeDescription_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void * type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__get_function__GetTypeDescription_Event__request(
  void * untyped_member, size_t index)
{
  type_description_interfaces__srv__GetTypeDescription_Request__Sequence * member =
    (type_description_interfaces__srv__GetTypeDescription_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__fetch_function__GetTypeDescription_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const type_description_interfaces__srv__GetTypeDescription_Request * item =
    ((const type_description_interfaces__srv__GetTypeDescription_Request *)
    type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__get_const_function__GetTypeDescription_Event__request(untyped_member, index));
  type_description_interfaces__srv__GetTypeDescription_Request * value =
    (type_description_interfaces__srv__GetTypeDescription_Request *)(untyped_value);
  *value = *item;
}

void type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__assign_function__GetTypeDescription_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  type_description_interfaces__srv__GetTypeDescription_Request * item =
    ((type_description_interfaces__srv__GetTypeDescription_Request *)
    type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__get_function__GetTypeDescription_Event__request(untyped_member, index));
  const type_description_interfaces__srv__GetTypeDescription_Request * value =
    (const type_description_interfaces__srv__GetTypeDescription_Request *)(untyped_value);
  *item = *value;
}

bool type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__resize_function__GetTypeDescription_Event__request(
  void * untyped_member, size_t size)
{
  type_description_interfaces__srv__GetTypeDescription_Request__Sequence * member =
    (type_description_interfaces__srv__GetTypeDescription_Request__Sequence *)(untyped_member);
  type_description_interfaces__srv__GetTypeDescription_Request__Sequence__fini(member);
  return type_description_interfaces__srv__GetTypeDescription_Request__Sequence__init(member, size);
}

size_t type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__size_function__GetTypeDescription_Event__response(
  const void * untyped_member)
{
  const type_description_interfaces__srv__GetTypeDescription_Response__Sequence * member =
    (const type_description_interfaces__srv__GetTypeDescription_Response__Sequence *)(untyped_member);
  return member->size;
}

const void * type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__get_const_function__GetTypeDescription_Event__response(
  const void * untyped_member, size_t index)
{
  const type_description_interfaces__srv__GetTypeDescription_Response__Sequence * member =
    (const type_description_interfaces__srv__GetTypeDescription_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void * type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__get_function__GetTypeDescription_Event__response(
  void * untyped_member, size_t index)
{
  type_description_interfaces__srv__GetTypeDescription_Response__Sequence * member =
    (type_description_interfaces__srv__GetTypeDescription_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__fetch_function__GetTypeDescription_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const type_description_interfaces__srv__GetTypeDescription_Response * item =
    ((const type_description_interfaces__srv__GetTypeDescription_Response *)
    type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__get_const_function__GetTypeDescription_Event__response(untyped_member, index));
  type_description_interfaces__srv__GetTypeDescription_Response * value =
    (type_description_interfaces__srv__GetTypeDescription_Response *)(untyped_value);
  *value = *item;
}

void type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__assign_function__GetTypeDescription_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  type_description_interfaces__srv__GetTypeDescription_Response * item =
    ((type_description_interfaces__srv__GetTypeDescription_Response *)
    type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__get_function__GetTypeDescription_Event__response(untyped_member, index));
  const type_description_interfaces__srv__GetTypeDescription_Response * value =
    (const type_description_interfaces__srv__GetTypeDescription_Response *)(untyped_value);
  *item = *value;
}

bool type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__resize_function__GetTypeDescription_Event__response(
  void * untyped_member, size_t size)
{
  type_description_interfaces__srv__GetTypeDescription_Response__Sequence * member =
    (type_description_interfaces__srv__GetTypeDescription_Response__Sequence *)(untyped_member);
  type_description_interfaces__srv__GetTypeDescription_Response__Sequence__fini(member);
  return type_description_interfaces__srv__GetTypeDescription_Response__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__GetTypeDescription_Event_message_member_array[3] = {
  {
    "info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(type_description_interfaces__srv__GetTypeDescription_Event, info),  // bytes offset in struct
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
    offsetof(type_description_interfaces__srv__GetTypeDescription_Event, request),  // bytes offset in struct
    NULL,  // default value
    type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__size_function__GetTypeDescription_Event__request,  // size() function pointer
    type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__get_const_function__GetTypeDescription_Event__request,  // get_const(index) function pointer
    type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__get_function__GetTypeDescription_Event__request,  // get(index) function pointer
    type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__fetch_function__GetTypeDescription_Event__request,  // fetch(index, &value) function pointer
    type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__assign_function__GetTypeDescription_Event__request,  // assign(index, value) function pointer
    type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__resize_function__GetTypeDescription_Event__request  // resize(index) function pointer
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
    offsetof(type_description_interfaces__srv__GetTypeDescription_Event, response),  // bytes offset in struct
    NULL,  // default value
    type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__size_function__GetTypeDescription_Event__response,  // size() function pointer
    type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__get_const_function__GetTypeDescription_Event__response,  // get_const(index) function pointer
    type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__get_function__GetTypeDescription_Event__response,  // get(index) function pointer
    type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__fetch_function__GetTypeDescription_Event__response,  // fetch(index, &value) function pointer
    type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__assign_function__GetTypeDescription_Event__response,  // assign(index, value) function pointer
    type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__resize_function__GetTypeDescription_Event__response  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__GetTypeDescription_Event_message_members = {
  "type_description_interfaces__srv",  // message namespace
  "GetTypeDescription_Event",  // message name
  3,  // number of fields
  sizeof(type_description_interfaces__srv__GetTypeDescription_Event),
  false,  // has_any_key_member_
  type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__GetTypeDescription_Event_message_member_array,  // message members
  type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__GetTypeDescription_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__GetTypeDescription_Event_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__GetTypeDescription_Event_message_type_support_handle = {
  0,
  &type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__GetTypeDescription_Event_message_members,
  get_message_typesupport_handle_function,
  &type_description_interfaces__srv__GetTypeDescription_Event__get_type_hash,
  &type_description_interfaces__srv__GetTypeDescription_Event__get_type_description,
  &type_description_interfaces__srv__GetTypeDescription_Event__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_type_description_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, type_description_interfaces, srv, GetTypeDescription_Event)() {
  type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__GetTypeDescription_Event_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_msgs, msg, ServiceEventInfo)();
  type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__GetTypeDescription_Event_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, type_description_interfaces, srv, GetTypeDescription_Request)();
  type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__GetTypeDescription_Event_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, type_description_interfaces, srv, GetTypeDescription_Response)();
  if (!type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__GetTypeDescription_Event_message_type_support_handle.typesupport_identifier) {
    type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__GetTypeDescription_Event_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__GetTypeDescription_Event_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "type_description_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "type_description_interfaces/srv/detail/get_type_description__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers type_description_interfaces__srv__detail__get_type_description__rosidl_typesupport_introspection_c__GetTypeDescription_service_members = {
  "type_description_interfaces__srv",  // service namespace
  "GetTypeDescription",  // service name
  // the following fields are initialized below on first access
  NULL,  // request message
  // type_description_interfaces__srv__detail__get_type_description__rosidl_typesupport_introspection_c__GetTypeDescription_Request_message_type_support_handle,
  NULL,  // response message
  // type_description_interfaces__srv__detail__get_type_description__rosidl_typesupport_introspection_c__GetTypeDescription_Response_message_type_support_handle
  NULL  // event_message
  // type_description_interfaces__srv__detail__get_type_description__rosidl_typesupport_introspection_c__GetTypeDescription_Response_message_type_support_handle
};


static rosidl_service_type_support_t type_description_interfaces__srv__detail__get_type_description__rosidl_typesupport_introspection_c__GetTypeDescription_service_type_support_handle = {
  0,
  &type_description_interfaces__srv__detail__get_type_description__rosidl_typesupport_introspection_c__GetTypeDescription_service_members,
  get_service_typesupport_handle_function,
  &type_description_interfaces__srv__GetTypeDescription_Request__rosidl_typesupport_introspection_c__GetTypeDescription_Request_message_type_support_handle,
  &type_description_interfaces__srv__GetTypeDescription_Response__rosidl_typesupport_introspection_c__GetTypeDescription_Response_message_type_support_handle,
  &type_description_interfaces__srv__GetTypeDescription_Event__rosidl_typesupport_introspection_c__GetTypeDescription_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    type_description_interfaces,
    srv,
    GetTypeDescription
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    type_description_interfaces,
    srv,
    GetTypeDescription
  ),
  &type_description_interfaces__srv__GetTypeDescription__get_type_hash,
  &type_description_interfaces__srv__GetTypeDescription__get_type_description,
  &type_description_interfaces__srv__GetTypeDescription__get_type_description_sources,
};

// Forward declaration of message type support functions for service members
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, type_description_interfaces, srv, GetTypeDescription_Request)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, type_description_interfaces, srv, GetTypeDescription_Response)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, type_description_interfaces, srv, GetTypeDescription_Event)(void);

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_type_description_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, type_description_interfaces, srv, GetTypeDescription)(void) {
  if (!type_description_interfaces__srv__detail__get_type_description__rosidl_typesupport_introspection_c__GetTypeDescription_service_type_support_handle.typesupport_identifier) {
    type_description_interfaces__srv__detail__get_type_description__rosidl_typesupport_introspection_c__GetTypeDescription_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)type_description_interfaces__srv__detail__get_type_description__rosidl_typesupport_introspection_c__GetTypeDescription_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, type_description_interfaces, srv, GetTypeDescription_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, type_description_interfaces, srv, GetTypeDescription_Response)()->data;
  }
  if (!service_members->event_members_) {
    service_members->event_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, type_description_interfaces, srv, GetTypeDescription_Event)()->data;
  }

  return &type_description_interfaces__srv__detail__get_type_description__rosidl_typesupport_introspection_c__GetTypeDescription_service_type_support_handle;
}
