// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rosgraph_msgs:msg/Clock.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rosgraph_msgs/msg/clock.hpp"


#ifndef ROSGRAPH_MSGS__MSG__DETAIL__CLOCK__TRAITS_HPP_
#define ROSGRAPH_MSGS__MSG__DETAIL__CLOCK__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rosgraph_msgs/msg/detail/clock__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'clock'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace rosgraph_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const Clock & msg,
  std::ostream & out)
{
  out << "{";
  // member: clock
  {
    out << "clock: ";
    to_flow_style_yaml(msg.clock, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Clock & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: clock
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "clock:\n";
    to_block_style_yaml(msg.clock, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Clock & msg, bool use_flow_style = false)
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

}  // namespace rosgraph_msgs

namespace rosidl_generator_traits
{

[[deprecated("use rosgraph_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const rosgraph_msgs::msg::Clock & msg,
  std::ostream & out, size_t indentation = 0)
{
  rosgraph_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rosgraph_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const rosgraph_msgs::msg::Clock & msg)
{
  return rosgraph_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<rosgraph_msgs::msg::Clock>()
{
  return "rosgraph_msgs::msg::Clock";
}

template<>
inline const char * name<rosgraph_msgs::msg::Clock>()
{
  return "rosgraph_msgs/msg/Clock";
}

template<>
struct has_fixed_size<rosgraph_msgs::msg::Clock>
  : std::integral_constant<bool, has_fixed_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct has_bounded_size<rosgraph_msgs::msg::Clock>
  : std::integral_constant<bool, has_bounded_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct is_message<rosgraph_msgs::msg::Clock>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ROSGRAPH_MSGS__MSG__DETAIL__CLOCK__TRAITS_HPP_
