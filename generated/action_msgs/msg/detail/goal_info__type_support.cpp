// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from action_msgs:msg/GoalInfo.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "action_msgs/msg/detail/goal_info__functions.h"
#include "action_msgs/msg/detail/goal_info__struct.hpp"
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

void GoalInfo_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) action_msgs::msg::GoalInfo(_init);
}

void GoalInfo_fini_function(void * message_memory)
{
  auto typed_message = static_cast<action_msgs::msg::GoalInfo *>(message_memory);
  typed_message->~GoalInfo();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember GoalInfo_message_member_array[2] = {
  {
    "goal_id",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<unique_identifier_msgs::msg::UUID>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(action_msgs::msg::GoalInfo, goal_id),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "stamp",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<builtin_interfaces::msg::Time>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(action_msgs::msg::GoalInfo, stamp),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers GoalInfo_message_members = {
  "action_msgs::msg",  // message namespace
  "GoalInfo",  // message name
  2,  // number of fields
  sizeof(action_msgs::msg::GoalInfo),
  false,  // has_any_key_member_
  GoalInfo_message_member_array,  // message members
  GoalInfo_init_function,  // function to initialize message memory (memory has to be allocated)
  GoalInfo_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t GoalInfo_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &GoalInfo_message_members,
  get_message_typesupport_handle_function,
  &action_msgs__msg__GoalInfo__get_type_hash,
  &action_msgs__msg__GoalInfo__get_type_description,
  &action_msgs__msg__GoalInfo__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace action_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<action_msgs::msg::GoalInfo>()
{
  return &::action_msgs::msg::rosidl_typesupport_introspection_cpp::GoalInfo_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, action_msgs, msg, GoalInfo)() {
  return &::action_msgs::msg::rosidl_typesupport_introspection_cpp::GoalInfo_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
