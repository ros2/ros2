// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from rcl_interfaces:msg/ListParametersResult.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "rcl_interfaces/msg/detail/list_parameters_result__functions.h"
#include "rcl_interfaces/msg/detail/list_parameters_result__struct.hpp"
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

void ListParametersResult_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) rcl_interfaces::msg::ListParametersResult(_init);
}

void ListParametersResult_fini_function(void * message_memory)
{
  auto typed_message = static_cast<rcl_interfaces::msg::ListParametersResult *>(message_memory);
  typed_message->~ListParametersResult();
}

size_t size_function__ListParametersResult__names(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<std::string> *>(untyped_member);
  return member->size();
}

const void * get_const_function__ListParametersResult__names(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<std::string> *>(untyped_member);
  return &member[index];
}

void * get_function__ListParametersResult__names(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<std::string> *>(untyped_member);
  return &member[index];
}

void fetch_function__ListParametersResult__names(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const std::string *>(
    get_const_function__ListParametersResult__names(untyped_member, index));
  auto & value = *reinterpret_cast<std::string *>(untyped_value);
  value = item;
}

void assign_function__ListParametersResult__names(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<std::string *>(
    get_function__ListParametersResult__names(untyped_member, index));
  const auto & value = *reinterpret_cast<const std::string *>(untyped_value);
  item = value;
}

void resize_function__ListParametersResult__names(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<std::string> *>(untyped_member);
  member->resize(size);
}

size_t size_function__ListParametersResult__prefixes(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<std::string> *>(untyped_member);
  return member->size();
}

const void * get_const_function__ListParametersResult__prefixes(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<std::string> *>(untyped_member);
  return &member[index];
}

void * get_function__ListParametersResult__prefixes(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<std::string> *>(untyped_member);
  return &member[index];
}

void fetch_function__ListParametersResult__prefixes(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const std::string *>(
    get_const_function__ListParametersResult__prefixes(untyped_member, index));
  auto & value = *reinterpret_cast<std::string *>(untyped_value);
  value = item;
}

void assign_function__ListParametersResult__prefixes(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<std::string *>(
    get_function__ListParametersResult__prefixes(untyped_member, index));
  const auto & value = *reinterpret_cast<const std::string *>(untyped_value);
  item = value;
}

void resize_function__ListParametersResult__prefixes(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<std::string> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember ListParametersResult_message_member_array[2] = {
  {
    "names",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces::msg::ListParametersResult, names),  // bytes offset in struct
    nullptr,  // default value
    size_function__ListParametersResult__names,  // size() function pointer
    get_const_function__ListParametersResult__names,  // get_const(index) function pointer
    get_function__ListParametersResult__names,  // get(index) function pointer
    fetch_function__ListParametersResult__names,  // fetch(index, &value) function pointer
    assign_function__ListParametersResult__names,  // assign(index, value) function pointer
    resize_function__ListParametersResult__names  // resize(index) function pointer
  },
  {
    "prefixes",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces::msg::ListParametersResult, prefixes),  // bytes offset in struct
    nullptr,  // default value
    size_function__ListParametersResult__prefixes,  // size() function pointer
    get_const_function__ListParametersResult__prefixes,  // get_const(index) function pointer
    get_function__ListParametersResult__prefixes,  // get(index) function pointer
    fetch_function__ListParametersResult__prefixes,  // fetch(index, &value) function pointer
    assign_function__ListParametersResult__prefixes,  // assign(index, value) function pointer
    resize_function__ListParametersResult__prefixes  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers ListParametersResult_message_members = {
  "rcl_interfaces::msg",  // message namespace
  "ListParametersResult",  // message name
  2,  // number of fields
  sizeof(rcl_interfaces::msg::ListParametersResult),
  false,  // has_any_key_member_
  ListParametersResult_message_member_array,  // message members
  ListParametersResult_init_function,  // function to initialize message memory (memory has to be allocated)
  ListParametersResult_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t ListParametersResult_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &ListParametersResult_message_members,
  get_message_typesupport_handle_function,
  &rcl_interfaces__msg__ListParametersResult__get_type_hash,
  &rcl_interfaces__msg__ListParametersResult__get_type_description,
  &rcl_interfaces__msg__ListParametersResult__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace rcl_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<rcl_interfaces::msg::ListParametersResult>()
{
  return &::rcl_interfaces::msg::rosidl_typesupport_introspection_cpp::ListParametersResult_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, rcl_interfaces, msg, ListParametersResult)() {
  return &::rcl_interfaces::msg::rosidl_typesupport_introspection_cpp::ListParametersResult_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
