// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from type_description_interfaces:msg/FieldType.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "type_description_interfaces/msg/detail/field_type__functions.h"
#include "type_description_interfaces/msg/detail/field_type__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace type_description_interfaces
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void FieldType_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) type_description_interfaces::msg::FieldType(_init);
}

void FieldType_fini_function(void * message_memory)
{
  auto typed_message = static_cast<type_description_interfaces::msg::FieldType *>(message_memory);
  typed_message->~FieldType();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember FieldType_message_member_array[4] = {
  {
    "type_id",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(type_description_interfaces::msg::FieldType, type_id),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "capacity",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(type_description_interfaces::msg::FieldType, capacity),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "string_capacity",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(type_description_interfaces::msg::FieldType, string_capacity),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "nested_type_name",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    255,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(type_description_interfaces::msg::FieldType, nested_type_name),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers FieldType_message_members = {
  "type_description_interfaces::msg",  // message namespace
  "FieldType",  // message name
  4,  // number of fields
  sizeof(type_description_interfaces::msg::FieldType),
  false,  // has_any_key_member_
  FieldType_message_member_array,  // message members
  FieldType_init_function,  // function to initialize message memory (memory has to be allocated)
  FieldType_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t FieldType_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &FieldType_message_members,
  get_message_typesupport_handle_function,
  &type_description_interfaces__msg__FieldType__get_type_hash,
  &type_description_interfaces__msg__FieldType__get_type_description,
  &type_description_interfaces__msg__FieldType__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace type_description_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<type_description_interfaces::msg::FieldType>()
{
  return &::type_description_interfaces::msg::rosidl_typesupport_introspection_cpp::FieldType_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, type_description_interfaces, msg, FieldType)() {
  return &::type_description_interfaces::msg::rosidl_typesupport_introspection_cpp::FieldType_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
