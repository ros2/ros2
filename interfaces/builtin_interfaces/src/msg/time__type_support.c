// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// builtin_interfaces/msg/Time type support implementation

#include <stddef.h>
#include <string.h>

#include "builtin_interfaces/msg/time.h"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"

// Member field definitions
static rosidl_typesupport_introspection_c__MessageMember
builtin_interfaces__msg__Time__members[2] = {
  {
    "sec",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(builtin_interfaces__msg__Time, sec),  // offset
    NULL,  // default value
    NULL,  // size function pointer
    NULL,  // get const function pointer
    NULL,  // get function pointer
    NULL,  // fetch function pointer
    NULL,  // assign function pointer
    NULL   // resize function pointer
  },
  {
    "nanosec",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(builtin_interfaces__msg__Time, nanosec),  // offset
    NULL,  // default value
    NULL,  // size function pointer
    NULL,  // get const function pointer
    NULL,  // get function pointer
    NULL,  // fetch function pointer
    NULL,  // assign function pointer
    NULL   // resize function pointer
  }
};

// Message introspection struct
static const rosidl_typesupport_introspection_c__MessageMembers
builtin_interfaces__msg__Time__message_members = {
  "builtin_interfaces",  // message namespace
  "Time",  // message name
  2,  // number of fields
  sizeof(builtin_interfaces__msg__Time),
  false,  // has_any_key_member_
  builtin_interfaces__msg__Time__members,  // message members
  (rosidl_typesupport_introspection_c__MessageInitFunction)builtin_interfaces__msg__Time__init,
  (rosidl_typesupport_introspection_c__MessageFiniFunction)builtin_interfaces__msg__Time__fini
};

// Type support struct
static rosidl_message_type_support_t builtin_interfaces__msg__Time__type_support = {
  rosidl_typesupport_introspection_c__identifier,
  &builtin_interfaces__msg__Time__message_members,
  get_message_typesupport_handle_function,
  &builtin_interfaces__msg__Time__type_support
};

// Get type support function
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)()
{
  return &builtin_interfaces__msg__Time__type_support;
}
