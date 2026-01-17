// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from rcl_interfaces:msg/ListParametersResult.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "rcl_interfaces/msg/detail/list_parameters_result__rosidl_typesupport_introspection_c.h"
#include "rcl_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "rcl_interfaces/msg/detail/list_parameters_result__functions.h"
#include "rcl_interfaces/msg/detail/list_parameters_result__struct.h"


// Include directives for member types
// Member `names`
// Member `prefixes`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__ListParametersResult_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  rcl_interfaces__msg__ListParametersResult__init(message_memory);
}

void rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__ListParametersResult_fini_function(void * message_memory)
{
  rcl_interfaces__msg__ListParametersResult__fini(message_memory);
}

size_t rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__size_function__ListParametersResult__names(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__get_const_function__ListParametersResult__names(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__get_function__ListParametersResult__names(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__fetch_function__ListParametersResult__names(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__get_const_function__ListParametersResult__names(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__assign_function__ListParametersResult__names(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__get_function__ListParametersResult__names(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__resize_function__ListParametersResult__names(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

size_t rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__size_function__ListParametersResult__prefixes(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__get_const_function__ListParametersResult__prefixes(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__get_function__ListParametersResult__prefixes(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__fetch_function__ListParametersResult__prefixes(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__get_const_function__ListParametersResult__prefixes(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__assign_function__ListParametersResult__prefixes(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__get_function__ListParametersResult__prefixes(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__resize_function__ListParametersResult__prefixes(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__ListParametersResult_message_member_array[2] = {
  {
    "names",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces__msg__ListParametersResult, names),  // bytes offset in struct
    NULL,  // default value
    rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__size_function__ListParametersResult__names,  // size() function pointer
    rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__get_const_function__ListParametersResult__names,  // get_const(index) function pointer
    rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__get_function__ListParametersResult__names,  // get(index) function pointer
    rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__fetch_function__ListParametersResult__names,  // fetch(index, &value) function pointer
    rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__assign_function__ListParametersResult__names,  // assign(index, value) function pointer
    rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__resize_function__ListParametersResult__names  // resize(index) function pointer
  },
  {
    "prefixes",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces__msg__ListParametersResult, prefixes),  // bytes offset in struct
    NULL,  // default value
    rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__size_function__ListParametersResult__prefixes,  // size() function pointer
    rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__get_const_function__ListParametersResult__prefixes,  // get_const(index) function pointer
    rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__get_function__ListParametersResult__prefixes,  // get(index) function pointer
    rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__fetch_function__ListParametersResult__prefixes,  // fetch(index, &value) function pointer
    rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__assign_function__ListParametersResult__prefixes,  // assign(index, value) function pointer
    rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__resize_function__ListParametersResult__prefixes  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__ListParametersResult_message_members = {
  "rcl_interfaces__msg",  // message namespace
  "ListParametersResult",  // message name
  2,  // number of fields
  sizeof(rcl_interfaces__msg__ListParametersResult),
  false,  // has_any_key_member_
  rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__ListParametersResult_message_member_array,  // message members
  rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__ListParametersResult_init_function,  // function to initialize message memory (memory has to be allocated)
  rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__ListParametersResult_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__ListParametersResult_message_type_support_handle = {
  0,
  &rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__ListParametersResult_message_members,
  get_message_typesupport_handle_function,
  &rcl_interfaces__msg__ListParametersResult__get_type_hash,
  &rcl_interfaces__msg__ListParametersResult__get_type_description,
  &rcl_interfaces__msg__ListParametersResult__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_rcl_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rcl_interfaces, msg, ListParametersResult)() {
  if (!rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__ListParametersResult_message_type_support_handle.typesupport_identifier) {
    rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__ListParametersResult_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &rcl_interfaces__msg__ListParametersResult__rosidl_typesupport_introspection_c__ListParametersResult_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
