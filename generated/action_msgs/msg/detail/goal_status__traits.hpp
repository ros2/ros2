// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from action_msgs:msg/GoalStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "action_msgs/msg/goal_status.hpp"


#ifndef ACTION_MSGS__MSG__DETAIL__GOAL_STATUS__TRAITS_HPP_
#define ACTION_MSGS__MSG__DETAIL__GOAL_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "action_msgs/msg/detail/goal_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'goal_info'
#include "action_msgs/msg/detail/goal_info__traits.hpp"

namespace action_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const GoalStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_info
  {
    out << "goal_info: ";
    to_flow_style_yaml(msg.goal_info, out);
    out << ", ";
  }

  // member: status
  {
    out << "status: ";
    rosidl_generator_traits::value_to_yaml(msg.status, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GoalStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_info
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_info:\n";
    to_block_style_yaml(msg.goal_info, out, indentation + 2);
  }

  // member: status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "status: ";
    rosidl_generator_traits::value_to_yaml(msg.status, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GoalStatus & msg, bool use_flow_style = false)
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
  const action_msgs::msg::GoalStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  action_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use action_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const action_msgs::msg::GoalStatus & msg)
{
  return action_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<action_msgs::msg::GoalStatus>()
{
  return "action_msgs::msg::GoalStatus";
}

template<>
inline const char * name<action_msgs::msg::GoalStatus>()
{
  return "action_msgs/msg/GoalStatus";
}

template<>
struct has_fixed_size<action_msgs::msg::GoalStatus>
  : std::integral_constant<bool, has_fixed_size<action_msgs::msg::GoalInfo>::value> {};

template<>
struct has_bounded_size<action_msgs::msg::GoalStatus>
  : std::integral_constant<bool, has_bounded_size<action_msgs::msg::GoalInfo>::value> {};

template<>
struct is_message<action_msgs::msg::GoalStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ACTION_MSGS__MSG__DETAIL__GOAL_STATUS__TRAITS_HPP_
