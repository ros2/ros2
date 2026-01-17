// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from type_description_interfaces:msg/IndividualTypeDescription.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "type_description_interfaces/msg/detail/individual_type_description__functions.h"
#include "type_description_interfaces/msg/detail/individual_type_description__struct.hpp"
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

void IndividualTypeDescription_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) type_description_interfaces::msg::IndividualTypeDescription(_init);
}

void IndividualTypeDescription_fini_function(void * message_memory)
{
  auto typed_message = static_cast<type_description_interfaces::msg::IndividualTypeDescription *>(message_memory);
  typed_message->~IndividualTypeDescription();
}

size_t size_function__IndividualTypeDescription__fields(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<type_description_interfaces::msg::Field> *>(untyped_member);
  return member->size();
}

const void * get_const_function__IndividualTypeDescription__fields(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<type_description_interfaces::msg::Field> *>(untyped_member);
  return &member[index];
}

void * get_function__IndividualTypeDescription__fields(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<type_description_interfaces::msg::Field> *>(untyped_member);
  return &member[index];
}

void fetch_function__IndividualTypeDescription__fields(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const type_description_interfaces::msg::Field *>(
    get_const_function__IndividualTypeDescription__fields(untyped_member, index));
  auto & value = *reinterpret_cast<type_description_interfaces::msg::Field *>(untyped_value);
  value = item;
}

void assign_function__IndividualTypeDescription__fields(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<type_description_interfaces::msg::Field *>(
    get_function__IndividualTypeDescription__fields(untyped_member, index));
  const auto & value = *reinterpret_cast<const type_description_interfaces::msg::Field *>(untyped_value);
  item = value;
}

void resize_function__IndividualTypeDescription__fields(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<type_description_interfaces::msg::Field> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember IndividualTypeDescription_message_member_array[2] = {
  {
    "type_name",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    255,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(type_description_interfaces::msg::IndividualTypeDescription, type_name),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "fields",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<type_description_interfaces::msg::Field>(),  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(type_description_interfaces::msg::IndividualTypeDescription, fields),  // bytes offset in struct
    nullptr,  // default value
    size_function__IndividualTypeDescription__fields,  // size() function pointer
    get_const_function__IndividualTypeDescription__fields,  // get_const(index) function pointer
    get_function__IndividualTypeDescription__fields,  // get(index) function pointer
    fetch_function__IndividualTypeDescription__fields,  // fetch(index, &value) function pointer
    assign_function__IndividualTypeDescription__fields,  // assign(index, value) function pointer
    resize_function__IndividualTypeDescription__fields  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers IndividualTypeDescription_message_members = {
  "type_description_interfaces::msg",  // message namespace
  "IndividualTypeDescription",  // message name
  2,  // number of fields
  sizeof(type_description_interfaces::msg::IndividualTypeDescription),
  false,  // has_any_key_member_
  IndividualTypeDescription_message_member_array,  // message members
  IndividualTypeDescription_init_function,  // function to initialize message memory (memory has to be allocated)
  IndividualTypeDescription_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t IndividualTypeDescription_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &IndividualTypeDescription_message_members,
  get_message_typesupport_handle_function,
  &type_description_interfaces__msg__IndividualTypeDescription__get_type_hash,
  &type_description_interfaces__msg__IndividualTypeDescription__get_type_description,
  &type_description_interfaces__msg__IndividualTypeDescription__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace type_description_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<type_description_interfaces::msg::IndividualTypeDescription>()
{
  return &::type_description_interfaces::msg::rosidl_typesupport_introspection_cpp::IndividualTypeDescription_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, type_description_interfaces, msg, IndividualTypeDescription)() {
  return &::type_description_interfaces::msg::rosidl_typesupport_introspection_cpp::IndividualTypeDescription_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
