// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from action_msgs:msg/GoalInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "action_msgs/msg/goal_info.hpp"


#ifndef ACTION_MSGS__MSG__DETAIL__GOAL_INFO__TRAITS_HPP_
#define ACTION_MSGS__MSG__DETAIL__GOAL_INFO__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "action_msgs/msg/detail/goal_info__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace action_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const GoalInfo & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_id
  {
    out << "goal_id: ";
    to_flow_style_yaml(msg.goal_id, out);
    out << ", ";
  }

  // member: stamp
  {
    out << "stamp: ";
    to_flow_style_yaml(msg.stamp, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GoalInfo & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_id:\n";
    to_block_style_yaml(msg.goal_id, out, indentation + 2);
  }

  // member: stamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stamp:\n";
    to_block_style_yaml(msg.stamp, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GoalInfo & msg, bool use_flow_style = false)
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

}  // namespace action_msgs

namespace rosidl_generator_traits
{

[[deprecated("use action_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const action_msgs::msg::GoalInfo & msg,
  std::ostream & out, size_t indentation = 0)
{
  action_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use action_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const action_msgs::msg::GoalInfo & msg)
{
  return action_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<action_msgs::msg::GoalInfo>()
{
  return "action_msgs::msg::GoalInfo";
}

template<>
inline const char * name<action_msgs::msg::GoalInfo>()
{
  return "action_msgs/msg/GoalInfo";
}

template<>
struct has_fixed_size<action_msgs::msg::GoalInfo>
  : std::integral_constant<bool, has_fixed_size<builtin_interfaces::msg::Time>::value && has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<action_msgs::msg::GoalInfo>
  : std::integral_constant<bool, has_bounded_size<builtin_interfaces::msg::Time>::value && has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<action_msgs::msg::GoalInfo>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ACTION_MSGS__MSG__DETAIL__GOAL_INFO__TRAITS_HPP_
