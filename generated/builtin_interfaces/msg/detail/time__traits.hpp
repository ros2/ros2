// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from builtin_interfaces:msg/Time.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "builtin_interfaces/msg/time.hpp"


#ifndef BUILTIN_INTERFACES__MSG__DETAIL__TIME__TRAITS_HPP_
#define BUILTIN_INTERFACES__MSG__DETAIL__TIME__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "builtin_interfaces/msg/detail/time__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace builtin_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const Time & msg,
  std::ostream & out)
{
  out << "{";
  // member: sec
  {
    out << "sec: ";
    rosidl_generator_traits::value_to_yaml(msg.sec, out);
    out << ", ";
  }

  // member: nanosec
  {
    out << "nanosec: ";
    rosidl_generator_traits::value_to_yaml(msg.nanosec, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Time & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: sec
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sec: ";
    rosidl_generator_traits::value_to_yaml(msg.sec, out);
    out << "\n";
  }

  // member: nanosec
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "nanosec: ";
    rosidl_generator_traits::value_to_yaml(msg.nanosec, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Time & msg, bool use_flow_style = false)
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

}  // namespace builtin_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use builtin_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const builtin_interfaces::msg::Time & msg,
  std::ostream & out, size_t indentation = 0)
{
  builtin_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use builtin_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const builtin_interfaces::msg::Time & msg)
{
  return builtin_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<builtin_interfaces::msg::Time>()
{
  return "builtin_interfaces::msg::Time";
}

template<>
inline const char * name<builtin_interfaces::msg::Time>()
{
  return "builtin_interfaces/msg/Time";
}

template<>
struct has_fixed_size<builtin_interfaces::msg::Time>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<builtin_interfaces::msg::Time>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<builtin_interfaces::msg::Time>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // BUILTIN_INTERFACES__MSG__DETAIL__TIME__TRAITS_HPP_
