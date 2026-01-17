// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from rcl_interfaces:msg/ParameterEventDescriptors.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "rcl_interfaces/msg/detail/parameter_event_descriptors__functions.h"
#include "rcl_interfaces/msg/detail/parameter_event_descriptors__struct.hpp"
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

void ParameterEventDescriptors_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) rcl_interfaces::msg::ParameterEventDescriptors(_init);
}

void ParameterEventDescriptors_fini_function(void * message_memory)
{
  auto typed_message = static_cast<rcl_interfaces::msg::ParameterEventDescriptors *>(message_memory);
  typed_message->~ParameterEventDescriptors();
}

size_t size_function__ParameterEventDescriptors__new_parameters(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<rcl_interfaces::msg::ParameterDescriptor> *>(untyped_member);
  return member->size();
}

const void * get_const_function__ParameterEventDescriptors__new_parameters(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<rcl_interfaces::msg::ParameterDescriptor> *>(untyped_member);
  return &member[index];
}

void * get_function__ParameterEventDescriptors__new_parameters(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<rcl_interfaces::msg::ParameterDescriptor> *>(untyped_member);
  return &member[index];
}

void fetch_function__ParameterEventDescriptors__new_parameters(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const rcl_interfaces::msg::ParameterDescriptor *>(
    get_const_function__ParameterEventDescriptors__new_parameters(untyped_member, index));
  auto & value = *reinterpret_cast<rcl_interfaces::msg::ParameterDescriptor *>(untyped_value);
  value = item;
}

void assign_function__ParameterEventDescriptors__new_parameters(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<rcl_interfaces::msg::ParameterDescriptor *>(
    get_function__ParameterEventDescriptors__new_parameters(untyped_member, index));
  const auto & value = *reinterpret_cast<const rcl_interfaces::msg::ParameterDescriptor *>(untyped_value);
  item = value;
}

void resize_function__ParameterEventDescriptors__new_parameters(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<rcl_interfaces::msg::ParameterDescriptor> *>(untyped_member);
  member->resize(size);
}

size_t size_function__ParameterEventDescriptors__changed_parameters(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<rcl_interfaces::msg::ParameterDescriptor> *>(untyped_member);
  return member->size();
}

const void * get_const_function__ParameterEventDescriptors__changed_parameters(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<rcl_interfaces::msg::ParameterDescriptor> *>(untyped_member);
  return &member[index];
}

void * get_function__ParameterEventDescriptors__changed_parameters(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<rcl_interfaces::msg::ParameterDescriptor> *>(untyped_member);
  return &member[index];
}

void fetch_function__ParameterEventDescriptors__changed_parameters(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const rcl_interfaces::msg::ParameterDescriptor *>(
    get_const_function__ParameterEventDescriptors__changed_parameters(untyped_member, index));
  auto & value = *reinterpret_cast<rcl_interfaces::msg::ParameterDescriptor *>(untyped_value);
  value = item;
}

void assign_function__ParameterEventDescriptors__changed_parameters(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<rcl_interfaces::msg::ParameterDescriptor *>(
    get_function__ParameterEventDescriptors__changed_parameters(untyped_member, index));
  const auto & value = *reinterpret_cast<const rcl_interfaces::msg::ParameterDescriptor *>(untyped_value);
  item = value;
}

void resize_function__ParameterEventDescriptors__changed_parameters(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<rcl_interfaces::msg::ParameterDescriptor> *>(untyped_member);
  member->resize(size);
}

size_t size_function__ParameterEventDescriptors__deleted_parameters(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<rcl_interfaces::msg::ParameterDescriptor> *>(untyped_member);
  return member->size();
}

const void * get_const_function__ParameterEventDescriptors__deleted_parameters(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<rcl_interfaces::msg::ParameterDescriptor> *>(untyped_member);
  return &member[index];
}

void * get_function__ParameterEventDescriptors__deleted_parameters(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<rcl_interfaces::msg::ParameterDescriptor> *>(untyped_member);
  return &member[index];
}

void fetch_function__ParameterEventDescriptors__deleted_parameters(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const rcl_interfaces::msg::ParameterDescriptor *>(
    get_const_function__ParameterEventDescriptors__deleted_parameters(untyped_member, index));
  auto & value = *reinterpret_cast<rcl_interfaces::msg::ParameterDescriptor *>(untyped_value);
  value = item;
}

void assign_function__ParameterEventDescriptors__deleted_parameters(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<rcl_interfaces::msg::ParameterDescriptor *>(
    get_function__ParameterEventDescriptors__deleted_parameters(untyped_member, index));
  const auto & value = *reinterpret_cast<const rcl_interfaces::msg::ParameterDescriptor *>(untyped_value);
  item = value;
}

void resize_function__ParameterEventDescriptors__deleted_parameters(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<rcl_interfaces::msg::ParameterDescriptor> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember ParameterEventDescriptors_message_member_array[3] = {
  {
    "new_parameters",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<rcl_interfaces::msg::ParameterDescriptor>(),  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces::msg::ParameterEventDescriptors, new_parameters),  // bytes offset in struct
    nullptr,  // default value
    size_function__ParameterEventDescriptors__new_parameters,  // size() function pointer
    get_const_function__ParameterEventDescriptors__new_parameters,  // get_const(index) function pointer
    get_function__ParameterEventDescriptors__new_parameters,  // get(index) function pointer
    fetch_function__ParameterEventDescriptors__new_parameters,  // fetch(index, &value) function pointer
    assign_function__ParameterEventDescriptors__new_parameters,  // assign(index, value) function pointer
    resize_function__ParameterEventDescriptors__new_parameters  // resize(index) function pointer
  },
  {
    "changed_parameters",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<rcl_interfaces::msg::ParameterDescriptor>(),  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces::msg::ParameterEventDescriptors, changed_parameters),  // bytes offset in struct
    nullptr,  // default value
    size_function__ParameterEventDescriptors__changed_parameters,  // size() function pointer
    get_const_function__ParameterEventDescriptors__changed_parameters,  // get_const(index) function pointer
    get_function__ParameterEventDescriptors__changed_parameters,  // get(index) function pointer
    fetch_function__ParameterEventDescriptors__changed_parameters,  // fetch(index, &value) function pointer
    assign_function__ParameterEventDescriptors__changed_parameters,  // assign(index, value) function pointer
    resize_function__ParameterEventDescriptors__changed_parameters  // resize(index) function pointer
  },
  {
    "deleted_parameters",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<rcl_interfaces::msg::ParameterDescriptor>(),  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces::msg::ParameterEventDescriptors, deleted_parameters),  // bytes offset in struct
    nullptr,  // default value
    size_function__ParameterEventDescriptors__deleted_parameters,  // size() function pointer
    get_const_function__ParameterEventDescriptors__deleted_parameters,  // get_const(index) function pointer
    get_function__ParameterEventDescriptors__deleted_parameters,  // get(index) function pointer
    fetch_function__ParameterEventDescriptors__deleted_parameters,  // fetch(index, &value) function pointer
    assign_function__ParameterEventDescriptors__deleted_parameters,  // assign(index, value) function pointer
    resize_function__ParameterEventDescriptors__deleted_parameters  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers ParameterEventDescriptors_message_members = {
  "rcl_interfaces::msg",  // message namespace
  "ParameterEventDescriptors",  // message name
  3,  // number of fields
  sizeof(rcl_interfaces::msg::ParameterEventDescriptors),
  false,  // has_any_key_member_
  ParameterEventDescriptors_message_member_array,  // message members
  ParameterEventDescriptors_init_function,  // function to initialize message memory (memory has to be allocated)
  ParameterEventDescriptors_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t ParameterEventDescriptors_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &ParameterEventDescriptors_message_members,
  get_message_typesupport_handle_function,
  &rcl_interfaces__msg__ParameterEventDescriptors__get_type_hash,
  &rcl_interfaces__msg__ParameterEventDescriptors__get_type_description,
  &rcl_interfaces__msg__ParameterEventDescriptors__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace rcl_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<rcl_interfaces::msg::ParameterEventDescriptors>()
{
  return &::rcl_interfaces::msg::rosidl_typesupport_introspection_cpp::ParameterEventDescriptors_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, rcl_interfaces, msg, ParameterEventDescriptors)() {
  return &::rcl_interfaces::msg::rosidl_typesupport_introspection_cpp::ParameterEventDescriptors_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
