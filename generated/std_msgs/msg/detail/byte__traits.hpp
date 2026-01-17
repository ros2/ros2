// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from std_msgs:msg/Byte.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "std_msgs/msg/byte.hpp"


#ifndef STD_MSGS__MSG__DETAIL__BYTE__TRAITS_HPP_
#define STD_MSGS__MSG__DETAIL__BYTE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "std_msgs/msg/detail/byte__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace std_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const Byte & msg,
  std::ostream & out)
{
  out << "{";
  // member: data
  {
    out << "data: ";
    rosidl_generator_traits::character_value_to_yaml(msg.data, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Byte & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "data: ";
    rosidl_generator_traits::character_value_to_yaml(msg.data, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Byte & msg, bool use_flow_style = false)
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

}  // namespace std_msgs

namespace rosidl_generator_traits
{

[[deprecated("use std_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const std_msgs::msg::Byte & msg,
  std::ostream & out, size_t indentation = 0)
{
  std_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use std_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const std_msgs::msg::Byte & msg)
{
  return std_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<std_msgs::msg::Byte>()
{
  return "std_msgs::msg::Byte";
}

template<>
inline const char * name<std_msgs::msg::Byte>()
{
  return "std_msgs/msg/Byte";
}

template<>
struct has_fixed_size<std_msgs::msg::Byte>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<std_msgs::msg::Byte>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<std_msgs::msg::Byte>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // STD_MSGS__MSG__DETAIL__BYTE__TRAITS_HPP_
