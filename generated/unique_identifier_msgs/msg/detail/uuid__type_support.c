// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from unique_identifier_msgs:msg/UUID.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"
#include "unique_identifier_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "unique_identifier_msgs/msg/detail/uuid__functions.h"
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void unique_identifier_msgs__msg__UUID__rosidl_typesupport_introspection_c__UUID_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  unique_identifier_msgs__msg__UUID__init(message_memory);
}

void unique_identifier_msgs__msg__UUID__rosidl_typesupport_introspection_c__UUID_fini_function(void * message_memory)
{
  unique_identifier_msgs__msg__UUID__fini(message_memory);
}

size_t unique_identifier_msgs__msg__UUID__rosidl_typesupport_introspection_c__size_function__UUID__uuid(
  const void * untyped_member)
{
  (void)untyped_member;
  return 16;
}

const void * unique_identifier_msgs__msg__UUID__rosidl_typesupport_introspection_c__get_const_function__UUID__uuid(
  const void * untyped_member, size_t index)
{
  const uint8_t * member =
    (const uint8_t *)(untyped_member);
  return &member[index];
}

void * unique_identifier_msgs__msg__UUID__rosidl_typesupport_introspection_c__get_function__UUID__uuid(
  void * untyped_member, size_t index)
{
  uint8_t * member =
    (uint8_t *)(untyped_member);
  return &member[index];
}

void unique_identifier_msgs__msg__UUID__rosidl_typesupport_introspection_c__fetch_function__UUID__uuid(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const uint8_t * item =
    ((const uint8_t *)
    unique_identifier_msgs__msg__UUID__rosidl_typesupport_introspection_c__get_const_function__UUID__uuid(untyped_member, index));
  uint8_t * value =
    (uint8_t *)(untyped_value);
  *value = *item;
}

void unique_identifier_msgs__msg__UUID__rosidl_typesupport_introspection_c__assign_function__UUID__uuid(
  void * untyped_member, size_t index, const void * untyped_value)
{
  uint8_t * item =
    ((uint8_t *)
    unique_identifier_msgs__msg__UUID__rosidl_typesupport_introspection_c__get_function__UUID__uuid(untyped_member, index));
  const uint8_t * value =
    (const uint8_t *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember unique_identifier_msgs__msg__UUID__rosidl_typesupport_introspection_c__UUID_message_member_array[1] = {
  {
    "uuid",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    16,  // array size
    false,  // is upper bound
    offsetof(unique_identifier_msgs__msg__UUID, uuid),  // bytes offset in struct
    NULL,  // default value
    unique_identifier_msgs__msg__UUID__rosidl_typesupport_introspection_c__size_function__UUID__uuid,  // size() function pointer
    unique_identifier_msgs__msg__UUID__rosidl_typesupport_introspection_c__get_const_function__UUID__uuid,  // get_const(index) function pointer
    unique_identifier_msgs__msg__UUID__rosidl_typesupport_introspection_c__get_function__UUID__uuid,  // get(index) function pointer
    unique_identifier_msgs__msg__UUID__rosidl_typesupport_introspection_c__fetch_function__UUID__uuid,  // fetch(index, &value) function pointer
    unique_identifier_msgs__msg__UUID__rosidl_typesupport_introspection_c__assign_function__UUID__uuid,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers unique_identifier_msgs__msg__UUID__rosidl_typesupport_introspection_c__UUID_message_members = {
  "unique_identifier_msgs__msg",  // message namespace
  "UUID",  // message name
  1,  // number of fields
  sizeof(unique_identifier_msgs__msg__UUID),
  false,  // has_any_key_member_
  unique_identifier_msgs__msg__UUID__rosidl_typesupport_introspection_c__UUID_message_member_array,  // message members
  unique_identifier_msgs__msg__UUID__rosidl_typesupport_introspection_c__UUID_init_function,  // function to initialize message memory (memory has to be allocated)
  unique_identifier_msgs__msg__UUID__rosidl_typesupport_introspection_c__UUID_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t unique_identifier_msgs__msg__UUID__rosidl_typesupport_introspection_c__UUID_message_type_support_handle = {
  0,
  &unique_identifier_msgs__msg__UUID__rosidl_typesupport_introspection_c__UUID_message_members,
  get_message_typesupport_handle_function,
  &unique_identifier_msgs__msg__UUID__get_type_hash,
  &unique_identifier_msgs__msg__UUID__get_type_description,
  &unique_identifier_msgs__msg__UUID__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_unique_identifier_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)() {
  if (!unique_identifier_msgs__msg__UUID__rosidl_typesupport_introspection_c__UUID_message_type_support_handle.typesupport_identifier) {
    unique_identifier_msgs__msg__UUID__rosidl_typesupport_introspection_c__UUID_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &unique_identifier_msgs__msg__UUID__rosidl_typesupport_introspection_c__UUID_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
