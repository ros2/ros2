// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rcl_interfaces:msg/Log.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/msg/log.hpp"


#ifndef RCL_INTERFACES__MSG__DETAIL__LOG__TRAITS_HPP_
#define RCL_INTERFACES__MSG__DETAIL__LOG__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rcl_interfaces/msg/detail/log__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace rcl_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const Log & msg,
  std::ostream & out)
{
  out << "{";
  // member: stamp
  {
    out << "stamp: ";
    to_flow_style_yaml(msg.stamp, out);
    out << ", ";
  }

  // member: level
  {
    out << "level: ";
    rosidl_generator_traits::value_to_yaml(msg.level, out);
    out << ", ";
  }

  // member: name
  {
    out << "name: ";
    rosidl_generator_traits::value_to_yaml(msg.name, out);
    out << ", ";
  }

  // member: msg
  {
    out << "msg: ";
    rosidl_generator_traits::value_to_yaml(msg.msg, out);
    out << ", ";
  }

  // member: file
  {
    out << "file: ";
    rosidl_generator_traits::value_to_yaml(msg.file, out);
    out << ", ";
  }

  // member: function
  {
    out << "function: ";
    rosidl_generator_traits::value_to_yaml(msg.function, out);
    out << ", ";
  }

  // member: line
  {
    out << "line: ";
    rosidl_generator_traits::value_to_yaml(msg.line, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Log & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: stamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stamp:\n";
    to_block_style_yaml(msg.stamp, out, indentation + 2);
  }

  // member: level
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "level: ";
    rosidl_generator_traits::value_to_yaml(msg.level, out);
    out << "\n";
  }

  // member: name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "name: ";
    rosidl_generator_traits::value_to_yaml(msg.name, out);
    out << "\n";
  }

  // member: msg
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "msg: ";
    rosidl_generator_traits::value_to_yaml(msg.msg, out);
    out << "\n";
  }

  // member: file
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "file: ";
    rosidl_generator_traits::value_to_yaml(msg.file, out);
    out << "\n";
  }

  // member: function
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "function: ";
    rosidl_generator_traits::value_to_yaml(msg.function, out);
    out << "\n";
  }

  // member: line
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "line: ";
    rosidl_generator_traits::value_to_yaml(msg.line, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Log & msg, bool use_flow_style = false)
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

}  // namespace rcl_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use rcl_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const rcl_interfaces::msg::Log & msg,
  std::ostream & out, size_t indentation = 0)
{
  rcl_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rcl_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const rcl_interfaces::msg::Log & msg)
{
  return rcl_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<rcl_interfaces::msg::Log>()
{
  return "rcl_interfaces::msg::Log";
}

template<>
inline const char * name<rcl_interfaces::msg::Log>()
{
  return "rcl_interfaces/msg/Log";
}

template<>
struct has_fixed_size<rcl_interfaces::msg::Log>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<rcl_interfaces::msg::Log>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<rcl_interfaces::msg::Log>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // RCL_INTERFACES__MSG__DETAIL__LOG__TRAITS_HPP_
