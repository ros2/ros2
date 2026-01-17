// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from lifecycle_msgs:msg/TransitionDescription.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "lifecycle_msgs/msg/transition_description.hpp"


#ifndef LIFECYCLE_MSGS__MSG__DETAIL__TRANSITION_DESCRIPTION__TRAITS_HPP_
#define LIFECYCLE_MSGS__MSG__DETAIL__TRANSITION_DESCRIPTION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "lifecycle_msgs/msg/detail/transition_description__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'transition'
#include "lifecycle_msgs/msg/detail/transition__traits.hpp"
// Member 'start_state'
// Member 'goal_state'
#include "lifecycle_msgs/msg/detail/state__traits.hpp"

namespace lifecycle_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const TransitionDescription & msg,
  std::ostream & out)
{
  out << "{";
  // member: transition
  {
    out << "transition: ";
    to_flow_style_yaml(msg.transition, out);
    out << ", ";
  }

  // member: start_state
  {
    out << "start_state: ";
    to_flow_style_yaml(msg.start_state, out);
    out << ", ";
  }

  // member: goal_state
  {
    out << "goal_state: ";
    to_flow_style_yaml(msg.goal_state, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const TransitionDescription & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: transition
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "transition:\n";
    to_block_style_yaml(msg.transition, out, indentation + 2);
  }

  // member: start_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "start_state:\n";
    to_block_style_yaml(msg.start_state, out, indentation + 2);
  }

  // member: goal_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_state:\n";
    to_block_style_yaml(msg.goal_state, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const TransitionDescription & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace lifecycle_msgs

namespace rosidl_generator_traits
{

[[deprecated("use lifecycle_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const lifecycle_msgs::msg::TransitionDescription & msg,
  std::ostream & out, size_t indentation = 0)
{
  lifecycle_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use lifecycle_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const lifecycle_msgs::msg::TransitionDescription & msg)
{
  return lifecycle_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<lifecycle_msgs::msg::TransitionDescription>()
{
  return "lifecycle_msgs::msg::TransitionDescription";
}

template<>
inline const char * name<lifecycle_msgs::msg::TransitionDescription>()
{
  return "lifecycle_msgs/msg/TransitionDescription";
}

template<>
struct has_fixed_size<lifecycle_msgs::msg::TransitionDescription>
  : std::integral_constant<bool, has_fixed_size<lifecycle_msgs::msg::State>::value && has_fixed_size<lifecycle_msgs::msg::Transition>::value> {};

template<>
struct has_bounded_size<lifecycle_msgs::msg::TransitionDescription>
  : std::integral_constant<bool, has_bounded_size<lifecycle_msgs::msg::State>::value && has_bounded_size<lifecycle_msgs::msg::Transition>::value> {};

template<>
struct is_message<lifecycle_msgs::msg::TransitionDescription>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // LIFECYCLE_MSGS__MSG__DETAIL__TRANSITION_DESCRIPTION__TRAITS_HPP_
