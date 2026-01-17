// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from rcl_interfaces:msg/ParameterDescriptor.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "rcl_interfaces/msg/detail/parameter_descriptor__functions.h"
#include "rcl_interfaces/msg/detail/parameter_descriptor__struct.hpp"
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

void ParameterDescriptor_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) rcl_interfaces::msg::ParameterDescriptor(_init);
}

void ParameterDescriptor_fini_function(void * message_memory)
{
  auto typed_message = static_cast<rcl_interfaces::msg::ParameterDescriptor *>(message_memory);
  typed_message->~ParameterDescriptor();
}

size_t size_function__ParameterDescriptor__floating_point_range(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<rcl_interfaces::msg::FloatingPointRange> *>(untyped_member);
  return member->size();
}

const void * get_const_function__ParameterDescriptor__floating_point_range(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<rcl_interfaces::msg::FloatingPointRange> *>(untyped_member);
  return &member[index];
}

void * get_function__ParameterDescriptor__floating_point_range(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<rcl_interfaces::msg::FloatingPointRange> *>(untyped_member);
  return &member[index];
}

void fetch_function__ParameterDescriptor__floating_point_range(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const rcl_interfaces::msg::FloatingPointRange *>(
    get_const_function__ParameterDescriptor__floating_point_range(untyped_member, index));
  auto & value = *reinterpret_cast<rcl_interfaces::msg::FloatingPointRange *>(untyped_value);
  value = item;
}

void assign_function__ParameterDescriptor__floating_point_range(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<rcl_interfaces::msg::FloatingPointRange *>(
    get_function__ParameterDescriptor__floating_point_range(untyped_member, index));
  const auto & value = *reinterpret_cast<const rcl_interfaces::msg::FloatingPointRange *>(untyped_value);
  item = value;
}

void resize_function__ParameterDescriptor__floating_point_range(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<rcl_interfaces::msg::FloatingPointRange> *>(untyped_member);
  member->resize(size);
}

size_t size_function__ParameterDescriptor__integer_range(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<rcl_interfaces::msg::IntegerRange> *>(untyped_member);
  return member->size();
}

const void * get_const_function__ParameterDescriptor__integer_range(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<rcl_interfaces::msg::IntegerRange> *>(untyped_member);
  return &member[index];
}

void * get_function__ParameterDescriptor__integer_range(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<rcl_interfaces::msg::IntegerRange> *>(untyped_member);
  return &member[index];
}

void fetch_function__ParameterDescriptor__integer_range(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const rcl_interfaces::msg::IntegerRange *>(
    get_const_function__ParameterDescriptor__integer_range(untyped_member, index));
  auto & value = *reinterpret_cast<rcl_interfaces::msg::IntegerRange *>(untyped_value);
  value = item;
}

void assign_function__ParameterDescriptor__integer_range(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<rcl_interfaces::msg::IntegerRange *>(
    get_function__ParameterDescriptor__integer_range(untyped_member, index));
  const auto & value = *reinterpret_cast<const rcl_interfaces::msg::IntegerRange *>(untyped_value);
  item = value;
}

void resize_function__ParameterDescriptor__integer_range(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<rcl_interfaces::msg::IntegerRange> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember ParameterDescriptor_message_member_array[8] = {
  {
    "name",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces::msg::ParameterDescriptor, name),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "type",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces::msg::ParameterDescriptor, type),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "description",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces::msg::ParameterDescriptor, description),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "additional_constraints",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces::msg::ParameterDescriptor, additional_constraints),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "read_only",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces::msg::ParameterDescriptor, read_only),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "dynamic_typing",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces::msg::ParameterDescriptor, dynamic_typing),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "floating_point_range",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<rcl_interfaces::msg::FloatingPointRange>(),  // members of sub message
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(rcl_interfaces::msg::ParameterDescriptor, floating_point_range),  // bytes offset in struct
    nullptr,  // default value
    size_function__ParameterDescriptor__floating_point_range,  // size() function pointer
    get_const_function__ParameterDescriptor__floating_point_range,  // get_const(index) function pointer
    get_function__ParameterDescriptor__floating_point_range,  // get(index) function pointer
    fetch_function__ParameterDescriptor__floating_point_range,  // fetch(index, &value) function pointer
    assign_function__ParameterDescriptor__floating_point_range,  // assign(index, value) function pointer
    resize_function__ParameterDescriptor__floating_point_range  // resize(index) function pointer
  },
  {
    "integer_range",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<rcl_interfaces::msg::IntegerRange>(),  // members of sub message
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(rcl_interfaces::msg::ParameterDescriptor, integer_range),  // bytes offset in struct
    nullptr,  // default value
    size_function__ParameterDescriptor__integer_range,  // size() function pointer
    get_const_function__ParameterDescriptor__integer_range,  // get_const(index) function pointer
    get_function__ParameterDescriptor__integer_range,  // get(index) function pointer
    fetch_function__ParameterDescriptor__integer_range,  // fetch(index, &value) function pointer
    assign_function__ParameterDescriptor__integer_range,  // assign(index, value) function pointer
    resize_function__ParameterDescriptor__integer_range  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers ParameterDescriptor_message_members = {
  "rcl_interfaces::msg",  // message namespace
  "ParameterDescriptor",  // message name
  8,  // number of fields
  sizeof(rcl_interfaces::msg::ParameterDescriptor),
  false,  // has_any_key_member_
  ParameterDescriptor_message_member_array,  // message members
  ParameterDescriptor_init_function,  // function to initialize message memory (memory has to be allocated)
  ParameterDescriptor_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t ParameterDescriptor_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &ParameterDescriptor_message_members,
  get_message_typesupport_handle_function,
  &rcl_interfaces__msg__ParameterDescriptor__get_type_hash,
  &rcl_interfaces__msg__ParameterDescriptor__get_type_description,
  &rcl_interfaces__msg__ParameterDescriptor__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace rcl_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<rcl_interfaces::msg::ParameterDescriptor>()
{
  return &::rcl_interfaces::msg::rosidl_typesupport_introspection_cpp::ParameterDescriptor_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, rcl_interfaces, msg, ParameterDescriptor)() {
  return &::rcl_interfaces::msg::rosidl_typesupport_introspection_cpp::ParameterDescriptor_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
