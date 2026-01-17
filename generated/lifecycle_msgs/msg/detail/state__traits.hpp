// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from lifecycle_msgs:msg/State.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "lifecycle_msgs/msg/state.hpp"


#ifndef LIFECYCLE_MSGS__MSG__DETAIL__STATE__TRAITS_HPP_
#define LIFECYCLE_MSGS__MSG__DETAIL__STATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "lifecycle_msgs/msg/detail/state__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace lifecycle_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const State & msg,
  std::ostream & out)
{
  out << "{";
  // member: id
  {
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << ", ";
  }

  // member: label
  {
    out << "label: ";
    rosidl_generator_traits::value_to_yaml(msg.label, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const State & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << "\n";
  }

  // member: label
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "label: ";
    rosidl_generator_traits::value_to_yaml(msg.label, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const State & msg, bool use_flow_style = false)
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
  const lifecycle_msgs::msg::State & msg,
  std::ostream & out, size_t indentation = 0)
{
  lifecycle_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use lifecycle_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const lifecycle_msgs::msg::State & msg)
{
  return lifecycle_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<lifecycle_msgs::msg::State>()
{
  return "lifecycle_msgs::msg::State";
}

template<>
inline const char * name<lifecycle_msgs::msg::State>()
{
  return "lifecycle_msgs/msg/State";
}

template<>
struct has_fixed_size<lifecycle_msgs::msg::State>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<lifecycle_msgs::msg::State>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<lifecycle_msgs::msg::State>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // LIFECYCLE_MSGS__MSG__DETAIL__STATE__TRAITS_HPP_
