// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rcl_interfaces:msg/Parameter.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/msg/parameter.hpp"


#ifndef RCL_INTERFACES__MSG__DETAIL__PARAMETER__TRAITS_HPP_
#define RCL_INTERFACES__MSG__DETAIL__PARAMETER__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rcl_interfaces/msg/detail/parameter__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'value'
#include "rcl_interfaces/msg/detail/parameter_value__traits.hpp"

namespace rcl_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const Parameter & msg,
  std::ostream & out)
{
  out << "{";
  // member: name
  {
    out << "name: ";
    rosidl_generator_traits::value_to_yaml(msg.name, out);
    out << ", ";
  }

  // member: value
  {
    out << "value: ";
    to_flow_style_yaml(msg.value, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Parameter & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "name: ";
    rosidl_generator_traits::value_to_yaml(msg.name, out);
    out << "\n";
  }

  // member: value
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "value:\n";
    to_block_style_yaml(msg.value, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Parameter & msg, bool use_flow_style = false)
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
  const rcl_interfaces::msg::Parameter & msg,
  std::ostream & out, size_t indentation = 0)
{
  rcl_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rcl_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const rcl_interfaces::msg::Parameter & msg)
{
  return rcl_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<rcl_interfaces::msg::Parameter>()
{
  return "rcl_interfaces::msg::Parameter";
}

template<>
inline const char * name<rcl_interfaces::msg::Parameter>()
{
  return "rcl_interfaces/msg/Parameter";
}

template<>
struct has_fixed_size<rcl_interfaces::msg::Parameter>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<rcl_interfaces::msg::Parameter>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<rcl_interfaces::msg::Parameter>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // RCL_INTERFACES__MSG__DETAIL__PARAMETER__TRAITS_HPP_
