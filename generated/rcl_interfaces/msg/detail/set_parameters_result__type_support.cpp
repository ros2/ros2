// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from rcl_interfaces:msg/SetParametersResult.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "rcl_interfaces/msg/detail/set_parameters_result__functions.h"
#include "rcl_interfaces/msg/detail/set_parameters_result__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace rcl_interfaces
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void SetParametersResult_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) rcl_interfaces::msg::SetParametersResult(_init);
}

void SetParametersResult_fini_function(void * message_memory)
{
  auto typed_message = static_cast<rcl_interfaces::msg::SetParametersResult *>(message_memory);
  typed_message->~SetParametersResult();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember SetParametersResult_message_member_array[2] = {
  {
    "successful",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces::msg::SetParametersResult, successful),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "reason",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces::msg::SetParametersResult, reason),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers SetParametersResult_message_members = {
  "rcl_interfaces::msg",  // message namespace
  "SetParametersResult",  // message name
  2,  // number of fields
  sizeof(rcl_interfaces::msg::SetParametersResult),
  false,  // has_any_key_member_
  SetParametersResult_message_member_array,  // message members
  SetParametersResult_init_function,  // function to initialize message memory (memory has to be allocated)
  SetParametersResult_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t SetParametersResult_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &SetParametersResult_message_members,
  get_message_typesupport_handle_function,
  &rcl_interfaces__msg__SetParametersResult__get_type_hash,
  &rcl_interfaces__msg__SetParametersResult__get_type_description,
  &rcl_interfaces__msg__SetParametersResult__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace rcl_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<rcl_interfaces::msg::SetParametersResult>()
{
  return &::rcl_interfaces::msg::rosidl_typesupport_introspection_cpp::SetParametersResult_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, rcl_interfaces, msg, SetParametersResult)() {
  return &::rcl_interfaces::msg::rosidl_typesupport_introspection_cpp::SetParametersResult_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
