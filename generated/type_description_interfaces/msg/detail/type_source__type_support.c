// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from type_description_interfaces:msg/TypeSource.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "type_description_interfaces/msg/detail/type_source__rosidl_typesupport_introspection_c.h"
#include "type_description_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "type_description_interfaces/msg/detail/type_source__functions.h"
#include "type_description_interfaces/msg/detail/type_source__struct.h"


// Include directives for member types
// Member `type_name`
// Member `encoding`
// Member `raw_file_contents`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void type_description_interfaces__msg__TypeSource__rosidl_typesupport_introspection_c__TypeSource_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  type_description_interfaces__msg__TypeSource__init(message_memory);
}

void type_description_interfaces__msg__TypeSource__rosidl_typesupport_introspection_c__TypeSource_fini_function(void * message_memory)
{
  type_description_interfaces__msg__TypeSource__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember type_description_interfaces__msg__TypeSource__rosidl_typesupport_introspection_c__TypeSource_message_member_array[3] = {
  {
    "type_name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(type_description_interfaces__msg__TypeSource, type_name),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "encoding",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(type_description_interfaces__msg__TypeSource, encoding),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "raw_file_contents",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(type_description_interfaces__msg__TypeSource, raw_file_contents),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers type_description_interfaces__msg__TypeSource__rosidl_typesupport_introspection_c__TypeSource_message_members = {
  "type_description_interfaces__msg",  // message namespace
  "TypeSource",  // message name
  3,  // number of fields
  sizeof(type_description_interfaces__msg__TypeSource),
  false,  // has_any_key_member_
  type_description_interfaces__msg__TypeSource__rosidl_typesupport_introspection_c__TypeSource_message_member_array,  // message members
  type_description_interfaces__msg__TypeSource__rosidl_typesupport_introspection_c__TypeSource_init_function,  // function to initialize message memory (memory has to be allocated)
  type_description_interfaces__msg__TypeSource__rosidl_typesupport_introspection_c__TypeSource_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t type_description_interfaces__msg__TypeSource__rosidl_typesupport_introspection_c__TypeSource_message_type_support_handle = {
  0,
  &type_description_interfaces__msg__TypeSource__rosidl_typesupport_introspection_c__TypeSource_message_members,
  get_message_typesupport_handle_function,
  &type_description_interfaces__msg__TypeSource__get_type_hash,
  &type_description_interfaces__msg__TypeSource__get_type_description,
  &type_description_interfaces__msg__TypeSource__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_type_description_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, type_description_interfaces, msg, TypeSource)() {
  if (!type_description_interfaces__msg__TypeSource__rosidl_typesupport_introspection_c__TypeSource_message_type_support_handle.typesupport_identifier) {
    type_description_interfaces__msg__TypeSource__rosidl_typesupport_introspection_c__TypeSource_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &type_description_interfaces__msg__TypeSource__rosidl_typesupport_introspection_c__TypeSource_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
