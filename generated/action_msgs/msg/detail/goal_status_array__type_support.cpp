// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from action_msgs:msg/GoalStatusArray.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "action_msgs/msg/detail/goal_status_array__functions.h"
#include "action_msgs/msg/detail/goal_status_array__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace action_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void GoalStatusArray_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) action_msgs::msg::GoalStatusArray(_init);
}

void GoalStatusArray_fini_function(void * message_memory)
{
  auto typed_message = static_cast<action_msgs::msg::GoalStatusArray *>(message_memory);
  typed_message->~GoalStatusArray();
}

size_t size_function__GoalStatusArray__status_list(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<action_msgs::msg::GoalStatus> *>(untyped_member);
  return member->size();
}

const void * get_const_function__GoalStatusArray__status_list(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<action_msgs::msg::GoalStatus> *>(untyped_member);
  return &member[index];
}

void * get_function__GoalStatusArray__status_list(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<action_msgs::msg::GoalStatus> *>(untyped_member);
  return &member[index];
}

void fetch_function__GoalStatusArray__status_list(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const action_msgs::msg::GoalStatus *>(
    get_const_function__GoalStatusArray__status_list(untyped_member, index));
  auto & value = *reinterpret_cast<action_msgs::msg::GoalStatus *>(untyped_value);
  value = item;
}

void assign_function__GoalStatusArray__status_list(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<action_msgs::msg::GoalStatus *>(
    get_function__GoalStatusArray__status_list(untyped_member, index));
  const auto & value = *reinterpret_cast<const action_msgs::msg::GoalStatus *>(untyped_value);
  item = value;
}

void resize_function__GoalStatusArray__status_list(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<action_msgs::msg::GoalStatus> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember GoalStatusArray_message_member_array[1] = {
  {
    "status_list",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<action_msgs::msg::GoalStatus>(),  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(action_msgs::msg::GoalStatusArray, status_list),  // bytes offset in struct
    nullptr,  // default value
    size_function__GoalStatusArray__status_list,  // size() function pointer
    get_const_function__GoalStatusArray__status_list,  // get_const(index) function pointer
    get_function__GoalStatusArray__status_list,  // get(index) function pointer
    fetch_function__GoalStatusArray__status_list,  // fetch(index, &value) function pointer
    assign_function__GoalStatusArray__status_list,  // assign(index, value) function pointer
    resize_function__GoalStatusArray__status_list  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers GoalStatusArray_message_members = {
  "action_msgs::msg",  // message namespace
  "GoalStatusArray",  // message name
  1,  // number of fields
  sizeof(action_msgs::msg::GoalStatusArray),
  false,  // has_any_key_member_
  GoalStatusArray_message_member_array,  // message members
  GoalStatusArray_init_function,  // function to initialize message memory (memory has to be allocated)
  GoalStatusArray_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t GoalStatusArray_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &GoalStatusArray_message_members,
  get_message_typesupport_handle_function,
  &action_msgs__msg__GoalStatusArray__get_type_hash,
  &action_msgs__msg__GoalStatusArray__get_type_description,
  &action_msgs__msg__GoalStatusArray__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace action_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<action_msgs::msg::GoalStatusArray>()
{
  return &::action_msgs::msg::rosidl_typesupport_introspection_cpp::GoalStatusArray_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, action_msgs, msg, GoalStatusArray)() {
  return &::action_msgs::msg::rosidl_typesupport_introspection_cpp::GoalStatusArray_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
