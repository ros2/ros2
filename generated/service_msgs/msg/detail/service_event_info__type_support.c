// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from service_msgs:msg/ServiceEventInfo.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "service_msgs/msg/detail/service_event_info__rosidl_typesupport_introspection_c.h"
#include "service_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "service_msgs/msg/detail/service_event_info__functions.h"
#include "service_msgs/msg/detail/service_event_info__struct.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/time.h"
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void service_msgs__msg__ServiceEventInfo__rosidl_typesupport_introspection_c__ServiceEventInfo_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  service_msgs__msg__ServiceEventInfo__init(message_memory);
}

void service_msgs__msg__ServiceEventInfo__rosidl_typesupport_introspection_c__ServiceEventInfo_fini_function(void * message_memory)
{
  service_msgs__msg__ServiceEventInfo__fini(message_memory);
}

size_t service_msgs__msg__ServiceEventInfo__rosidl_typesupport_introspection_c__size_function__ServiceEventInfo__client_gid(
  const void * untyped_member)
{
  (void)untyped_member;
  return 16;
}

const void * service_msgs__msg__ServiceEventInfo__rosidl_typesupport_introspection_c__get_const_function__ServiceEventInfo__client_gid(
  const void * untyped_member, size_t index)
{
  const uint8_t * member =
    (const uint8_t *)(untyped_member);
  return &member[index];
}

void * service_msgs__msg__ServiceEventInfo__rosidl_typesupport_introspection_c__get_function__ServiceEventInfo__client_gid(
  void * untyped_member, size_t index)
{
  uint8_t * member =
    (uint8_t *)(untyped_member);
  return &member[index];
}

void service_msgs__msg__ServiceEventInfo__rosidl_typesupport_introspection_c__fetch_function__ServiceEventInfo__client_gid(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const uint8_t * item =
    ((const uint8_t *)
    service_msgs__msg__ServiceEventInfo__rosidl_typesupport_introspection_c__get_const_function__ServiceEventInfo__client_gid(untyped_member, index));
  uint8_t * value =
    (uint8_t *)(untyped_value);
  *value = *item;
}

void service_msgs__msg__ServiceEventInfo__rosidl_typesupport_introspection_c__assign_function__ServiceEventInfo__client_gid(
  void * untyped_member, size_t index, const void * untyped_value)
{
  uint8_t * item =
    ((uint8_t *)
    service_msgs__msg__ServiceEventInfo__rosidl_typesupport_introspection_c__get_function__ServiceEventInfo__client_gid(untyped_member, index));
  const uint8_t * value =
    (const uint8_t *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember service_msgs__msg__ServiceEventInfo__rosidl_typesupport_introspection_c__ServiceEventInfo_message_member_array[4] = {
  {
    "event_type",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(service_msgs__msg__ServiceEventInfo, event_type),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "stamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(service_msgs__msg__ServiceEventInfo, stamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "client_gid",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    16,  // array size
    false,  // is upper bound
    offsetof(service_msgs__msg__ServiceEventInfo, client_gid),  // bytes offset in struct
    NULL,  // default value
    service_msgs__msg__ServiceEventInfo__rosidl_typesupport_introspection_c__size_function__ServiceEventInfo__client_gid,  // size() function pointer
    service_msgs__msg__ServiceEventInfo__rosidl_typesupport_introspection_c__get_const_function__ServiceEventInfo__client_gid,  // get_const(index) function pointer
    service_msgs__msg__ServiceEventInfo__rosidl_typesupport_introspection_c__get_function__ServiceEventInfo__client_gid,  // get(index) function pointer
    service_msgs__msg__ServiceEventInfo__rosidl_typesupport_introspection_c__fetch_function__ServiceEventInfo__client_gid,  // fetch(index, &value) function pointer
    service_msgs__msg__ServiceEventInfo__rosidl_typesupport_introspection_c__assign_function__ServiceEventInfo__client_gid,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "sequence_number",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(service_msgs__msg__ServiceEventInfo, sequence_number),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers service_msgs__msg__ServiceEventInfo__rosidl_typesupport_introspection_c__ServiceEventInfo_message_members = {
  "service_msgs__msg",  // message namespace
  "ServiceEventInfo",  // message name
  4,  // number of fields
  sizeof(service_msgs__msg__ServiceEventInfo),
  false,  // has_any_key_member_
  service_msgs__msg__ServiceEventInfo__rosidl_typesupport_introspection_c__ServiceEventInfo_message_member_array,  // message members
  service_msgs__msg__ServiceEventInfo__rosidl_typesupport_introspection_c__ServiceEventInfo_init_function,  // function to initialize message memory (memory has to be allocated)
  service_msgs__msg__ServiceEventInfo__rosidl_typesupport_introspection_c__ServiceEventInfo_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t service_msgs__msg__ServiceEventInfo__rosidl_typesupport_introspection_c__ServiceEventInfo_message_type_support_handle = {
  0,
  &service_msgs__msg__ServiceEventInfo__rosidl_typesupport_introspection_c__ServiceEventInfo_message_members,
  get_message_typesupport_handle_function,
  &service_msgs__msg__ServiceEventInfo__get_type_hash,
  &service_msgs__msg__ServiceEventInfo__get_type_description,
  &service_msgs__msg__ServiceEventInfo__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_service_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_msgs, msg, ServiceEventInfo)() {
  service_msgs__msg__ServiceEventInfo__rosidl_typesupport_introspection_c__ServiceEventInfo_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  if (!service_msgs__msg__ServiceEventInfo__rosidl_typesupport_introspection_c__ServiceEventInfo_message_type_support_handle.typesupport_identifier) {
    service_msgs__msg__ServiceEventInfo__rosidl_typesupport_introspection_c__ServiceEventInfo_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &service_msgs__msg__ServiceEventInfo__rosidl_typesupport_introspection_c__ServiceEventInfo_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
