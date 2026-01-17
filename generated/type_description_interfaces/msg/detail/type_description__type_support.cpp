// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from type_description_interfaces:msg/TypeDescription.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "type_description_interfaces/msg/detail/type_description__functions.h"
#include "type_description_interfaces/msg/detail/type_description__struct.hpp"
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

void TypeDescription_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) type_description_interfaces::msg::TypeDescription(_init);
}

void TypeDescription_fini_function(void * message_memory)
{
  auto typed_message = static_cast<type_description_interfaces::msg::TypeDescription *>(message_memory);
  typed_message->~TypeDescription();
}

size_t size_function__TypeDescription__referenced_type_descriptions(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<type_description_interfaces::msg::IndividualTypeDescription> *>(untyped_member);
  return member->size();
}

const void * get_const_function__TypeDescription__referenced_type_descriptions(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<type_description_interfaces::msg::IndividualTypeDescription> *>(untyped_member);
  return &member[index];
}

void * get_function__TypeDescription__referenced_type_descriptions(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<type_description_interfaces::msg::IndividualTypeDescription> *>(untyped_member);
  return &member[index];
}

void fetch_function__TypeDescription__referenced_type_descriptions(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const type_description_interfaces::msg::IndividualTypeDescription *>(
    get_const_function__TypeDescription__referenced_type_descriptions(untyped_member, index));
  auto & value = *reinterpret_cast<type_description_interfaces::msg::IndividualTypeDescription *>(untyped_value);
  value = item;
}

void assign_function__TypeDescription__referenced_type_descriptions(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<type_description_interfaces::msg::IndividualTypeDescription *>(
    get_function__TypeDescription__referenced_type_descriptions(untyped_member, index));
  const auto & value = *reinterpret_cast<const type_description_interfaces::msg::IndividualTypeDescription *>(untyped_value);
  item = value;
}

void resize_function__TypeDescription__referenced_type_descriptions(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<type_description_interfaces::msg::IndividualTypeDescription> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember TypeDescription_message_member_array[2] = {
  {
    "type_description",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<type_description_interfaces::msg::IndividualTypeDescription>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(type_description_interfaces::msg::TypeDescription, type_description),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "referenced_type_descriptions",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<type_description_interfaces::msg::IndividualTypeDescription>(),  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(type_description_interfaces::msg::TypeDescription, referenced_type_descriptions),  // bytes offset in struct
    nullptr,  // default value
    size_function__TypeDescription__referenced_type_descriptions,  // size() function pointer
    get_const_function__TypeDescription__referenced_type_descriptions,  // get_const(index) function pointer
    get_function__TypeDescription__referenced_type_descriptions,  // get(index) function pointer
    fetch_function__TypeDescription__referenced_type_descriptions,  // fetch(index, &value) function pointer
    assign_function__TypeDescription__referenced_type_descriptions,  // assign(index, value) function pointer
    resize_function__TypeDescription__referenced_type_descriptions  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers TypeDescription_message_members = {
  "type_description_interfaces::msg",  // message namespace
  "TypeDescription",  // message name
  2,  // number of fields
  sizeof(type_description_interfaces::msg::TypeDescription),
  false,  // has_any_key_member_
  TypeDescription_message_member_array,  // message members
  TypeDescription_init_function,  // function to initialize message memory (memory has to be allocated)
  TypeDescription_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t TypeDescription_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &TypeDescription_message_members,
  get_message_typesupport_handle_function,
  &type_description_interfaces__msg__TypeDescription__get_type_hash,
  &type_description_interfaces__msg__TypeDescription__get_type_description,
  &type_description_interfaces__msg__TypeDescription__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace type_description_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<type_description_interfaces::msg::TypeDescription>()
{
  return &::type_description_interfaces::msg::rosidl_typesupport_introspection_cpp::TypeDescription_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, type_description_interfaces, msg, TypeDescription)() {
  return &::type_description_interfaces::msg::rosidl_typesupport_introspection_cpp::TypeDescription_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
