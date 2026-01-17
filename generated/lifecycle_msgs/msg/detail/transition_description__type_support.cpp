// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from lifecycle_msgs:msg/TransitionDescription.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "lifecycle_msgs/msg/detail/transition_description__functions.h"
#include "lifecycle_msgs/msg/detail/transition_description__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace lifecycle_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void TransitionDescription_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) lifecycle_msgs::msg::TransitionDescription(_init);
}

void TransitionDescription_fini_function(void * message_memory)
{
  auto typed_message = static_cast<lifecycle_msgs::msg::TransitionDescription *>(message_memory);
  typed_message->~TransitionDescription();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember TransitionDescription_message_member_array[3] = {
  {
    "transition",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<lifecycle_msgs::msg::Transition>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lifecycle_msgs::msg::TransitionDescription, transition),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "start_state",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<lifecycle_msgs::msg::State>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lifecycle_msgs::msg::TransitionDescription, start_state),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "goal_state",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<lifecycle_msgs::msg::State>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(lifecycle_msgs::msg::TransitionDescription, goal_state),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers TransitionDescription_message_members = {
  "lifecycle_msgs::msg",  // message namespace
  "TransitionDescription",  // message name
  3,  // number of fields
  sizeof(lifecycle_msgs::msg::TransitionDescription),
  false,  // has_any_key_member_
  TransitionDescription_message_member_array,  // message members
  TransitionDescription_init_function,  // function to initialize message memory (memory has to be allocated)
  TransitionDescription_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t TransitionDescription_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &TransitionDescription_message_members,
  get_message_typesupport_handle_function,
  &lifecycle_msgs__msg__TransitionDescription__get_type_hash,
  &lifecycle_msgs__msg__TransitionDescription__get_type_description,
  &lifecycle_msgs__msg__TransitionDescription__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace lifecycle_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<lifecycle_msgs::msg::TransitionDescription>()
{
  return &::lifecycle_msgs::msg::rosidl_typesupport_introspection_cpp::TransitionDescription_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, lifecycle_msgs, msg, TransitionDescription)() {
  return &::lifecycle_msgs::msg::rosidl_typesupport_introspection_cpp::TransitionDescription_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
