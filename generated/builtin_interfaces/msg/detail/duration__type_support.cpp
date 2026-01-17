// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from builtin_interfaces:msg/Duration.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "builtin_interfaces/msg/detail/duration__functions.h"
#include "builtin_interfaces/msg/detail/duration__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace builtin_interfaces
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void Duration_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) builtin_interfaces::msg::Duration(_init);
}

void Duration_fini_function(void * message_memory)
{
  auto typed_message = static_cast<builtin_interfaces::msg::Duration *>(message_memory);
  typed_message->~Duration();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember Duration_message_member_array[2] = {
  {
    "sec",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(builtin_interfaces::msg::Duration, sec),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "nanosec",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(builtin_interfaces::msg::Duration, nanosec),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers Duration_message_members = {
  "builtin_interfaces::msg",  // message namespace
  "Duration",  // message name
  2,  // number of fields
  sizeof(builtin_interfaces::msg::Duration),
  false,  // has_any_key_member_
  Duration_message_member_array,  // message members
  Duration_init_function,  // function to initialize message memory (memory has to be allocated)
  Duration_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t Duration_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &Duration_message_members,
  get_message_typesupport_handle_function,
  &builtin_interfaces__msg__Duration__get_type_hash,
  &builtin_interfaces__msg__Duration__get_type_description,
  &builtin_interfaces__msg__Duration__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace builtin_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<builtin_interfaces::msg::Duration>()
{
  return &::builtin_interfaces::msg::rosidl_typesupport_introspection_cpp::Duration_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, builtin_interfaces, msg, Duration)() {
  return &::builtin_interfaces::msg::rosidl_typesupport_introspection_cpp::Duration_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
