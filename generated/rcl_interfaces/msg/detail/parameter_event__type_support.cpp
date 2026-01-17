// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from rcl_interfaces:msg/ParameterEvent.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "rcl_interfaces/msg/detail/parameter_event__functions.h"
#include "rcl_interfaces/msg/detail/parameter_event__struct.hpp"
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

void ParameterEvent_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) rcl_interfaces::msg::ParameterEvent(_init);
}

void ParameterEvent_fini_function(void * message_memory)
{
  auto typed_message = static_cast<rcl_interfaces::msg::ParameterEvent *>(message_memory);
  typed_message->~ParameterEvent();
}

size_t size_function__ParameterEvent__new_parameters(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<rcl_interfaces::msg::Parameter> *>(untyped_member);
  return member->size();
}

const void * get_const_function__ParameterEvent__new_parameters(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<rcl_interfaces::msg::Parameter> *>(untyped_member);
  return &member[index];
}

void * get_function__ParameterEvent__new_parameters(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<rcl_interfaces::msg::Parameter> *>(untyped_member);
  return &member[index];
}

void fetch_function__ParameterEvent__new_parameters(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const rcl_interfaces::msg::Parameter *>(
    get_const_function__ParameterEvent__new_parameters(untyped_member, index));
  auto & value = *reinterpret_cast<rcl_interfaces::msg::Parameter *>(untyped_value);
  value = item;
}

void assign_function__ParameterEvent__new_parameters(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<rcl_interfaces::msg::Parameter *>(
    get_function__ParameterEvent__new_parameters(untyped_member, index));
  const auto & value = *reinterpret_cast<const rcl_interfaces::msg::Parameter *>(untyped_value);
  item = value;
}

void resize_function__ParameterEvent__new_parameters(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<rcl_interfaces::msg::Parameter> *>(untyped_member);
  member->resize(size);
}

size_t size_function__ParameterEvent__changed_parameters(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<rcl_interfaces::msg::Parameter> *>(untyped_member);
  return member->size();
}

const void * get_const_function__ParameterEvent__changed_parameters(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<rcl_interfaces::msg::Parameter> *>(untyped_member);
  return &member[index];
}

void * get_function__ParameterEvent__changed_parameters(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<rcl_interfaces::msg::Parameter> *>(untyped_member);
  return &member[index];
}

void fetch_function__ParameterEvent__changed_parameters(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const rcl_interfaces::msg::Parameter *>(
    get_const_function__ParameterEvent__changed_parameters(untyped_member, index));
  auto & value = *reinterpret_cast<rcl_interfaces::msg::Parameter *>(untyped_value);
  value = item;
}

void assign_function__ParameterEvent__changed_parameters(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<rcl_interfaces::msg::Parameter *>(
    get_function__ParameterEvent__changed_parameters(untyped_member, index));
  const auto & value = *reinterpret_cast<const rcl_interfaces::msg::Parameter *>(untyped_value);
  item = value;
}

void resize_function__ParameterEvent__changed_parameters(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<rcl_interfaces::msg::Parameter> *>(untyped_member);
  member->resize(size);
}

size_t size_function__ParameterEvent__deleted_parameters(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<rcl_interfaces::msg::Parameter> *>(untyped_member);
  return member->size();
}

const void * get_const_function__ParameterEvent__deleted_parameters(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<rcl_interfaces::msg::Parameter> *>(untyped_member);
  return &member[index];
}

void * get_function__ParameterEvent__deleted_parameters(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<rcl_interfaces::msg::Parameter> *>(untyped_member);
  return &member[index];
}

void fetch_function__ParameterEvent__deleted_parameters(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const rcl_interfaces::msg::Parameter *>(
    get_const_function__ParameterEvent__deleted_parameters(untyped_member, index));
  auto & value = *reinterpret_cast<rcl_interfaces::msg::Parameter *>(untyped_value);
  value = item;
}

void assign_function__ParameterEvent__deleted_parameters(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<rcl_interfaces::msg::Parameter *>(
    get_function__ParameterEvent__deleted_parameters(untyped_member, index));
  const auto & value = *reinterpret_cast<const rcl_interfaces::msg::Parameter *>(untyped_value);
  item = value;
}

void resize_function__ParameterEvent__deleted_parameters(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<rcl_interfaces::msg::Parameter> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember ParameterEvent_message_member_array[5] = {
  {
    "stamp",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<builtin_interfaces::msg::Time>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces::msg::ParameterEvent, stamp),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "node",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces::msg::ParameterEvent, node),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "new_parameters",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<rcl_interfaces::msg::Parameter>(),  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces::msg::ParameterEvent, new_parameters),  // bytes offset in struct
    nullptr,  // default value
    size_function__ParameterEvent__new_parameters,  // size() function pointer
    get_const_function__ParameterEvent__new_parameters,  // get_const(index) function pointer
    get_function__ParameterEvent__new_parameters,  // get(index) function pointer
    fetch_function__ParameterEvent__new_parameters,  // fetch(index, &value) function pointer
    assign_function__ParameterEvent__new_parameters,  // assign(index, value) function pointer
    resize_function__ParameterEvent__new_parameters  // resize(index) function pointer
  },
  {
    "changed_parameters",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<rcl_interfaces::msg::Parameter>(),  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces::msg::ParameterEvent, changed_parameters),  // bytes offset in struct
    nullptr,  // default value
    size_function__ParameterEvent__changed_parameters,  // size() function pointer
    get_const_function__ParameterEvent__changed_parameters,  // get_const(index) function pointer
    get_function__ParameterEvent__changed_parameters,  // get(index) function pointer
    fetch_function__ParameterEvent__changed_parameters,  // fetch(index, &value) function pointer
    assign_function__ParameterEvent__changed_parameters,  // assign(index, value) function pointer
    resize_function__ParameterEvent__changed_parameters  // resize(index) function pointer
  },
  {
    "deleted_parameters",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<rcl_interfaces::msg::Parameter>(),  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rcl_interfaces::msg::ParameterEvent, deleted_parameters),  // bytes offset in struct
    nullptr,  // default value
    size_function__ParameterEvent__deleted_parameters,  // size() function pointer
    get_const_function__ParameterEvent__deleted_parameters,  // get_const(index) function pointer
    get_function__ParameterEvent__deleted_parameters,  // get(index) function pointer
    fetch_function__ParameterEvent__deleted_parameters,  // fetch(index, &value) function pointer
    assign_function__ParameterEvent__deleted_parameters,  // assign(index, value) function pointer
    resize_function__ParameterEvent__deleted_parameters  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers ParameterEvent_message_members = {
  "rcl_interfaces::msg",  // message namespace
  "ParameterEvent",  // message name
  5,  // number of fields
  sizeof(rcl_interfaces::msg::ParameterEvent),
  false,  // has_any_key_member_
  ParameterEvent_message_member_array,  // message members
  ParameterEvent_init_function,  // function to initialize message memory (memory has to be allocated)
  ParameterEvent_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t ParameterEvent_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &ParameterEvent_message_members,
  get_message_typesupport_handle_function,
  &rcl_interfaces__msg__ParameterEvent__get_type_hash,
  &rcl_interfaces__msg__ParameterEvent__get_type_description,
  &rcl_interfaces__msg__ParameterEvent__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace rcl_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<rcl_interfaces::msg::ParameterEvent>()
{
  return &::rcl_interfaces::msg::rosidl_typesupport_introspection_cpp::ParameterEvent_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, rcl_interfaces, msg, ParameterEvent)() {
  return &::rcl_interfaces::msg::rosidl_typesupport_introspection_cpp::ParameterEvent_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
