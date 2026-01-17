// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rcl_interfaces:msg/IntegerRange.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/msg/integer_range.hpp"


#ifndef RCL_INTERFACES__MSG__DETAIL__INTEGER_RANGE__TRAITS_HPP_
#define RCL_INTERFACES__MSG__DETAIL__INTEGER_RANGE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rcl_interfaces/msg/detail/integer_range__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace rcl_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const IntegerRange & msg,
  std::ostream & out)
{
  out << "{";
  // member: from_value
  {
    out << "from_value: ";
    rosidl_generator_traits::value_to_yaml(msg.from_value, out);
    out << ", ";
  }

  // member: to_value
  {
    out << "to_value: ";
    rosidl_generator_traits::value_to_yaml(msg.to_value, out);
    out << ", ";
  }

  // member: step
  {
    out << "step: ";
    rosidl_generator_traits::value_to_yaml(msg.step, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const IntegerRange & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: from_value
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "from_value: ";
    rosidl_generator_traits::value_to_yaml(msg.from_value, out);
    out << "\n";
  }

  // member: to_value
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "to_value: ";
    rosidl_generator_traits::value_to_yaml(msg.to_value, out);
    out << "\n";
  }

  // member: step
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "step: ";
    rosidl_generator_traits::value_to_yaml(msg.step, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const IntegerRange & msg, bool use_flow_style = false)
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
  const rcl_interfaces::msg::IntegerRange & msg,
  std::ostream & out, size_t indentation = 0)
{
  rcl_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rcl_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const rcl_interfaces::msg::IntegerRange & msg)
{
  return rcl_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<rcl_interfaces::msg::IntegerRange>()
{
  return "rcl_interfaces::msg::IntegerRange";
}

template<>
inline const char * name<rcl_interfaces::msg::IntegerRange>()
{
  return "rcl_interfaces/msg/IntegerRange";
}

template<>
struct has_fixed_size<rcl_interfaces::msg::IntegerRange>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<rcl_interfaces::msg::IntegerRange>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<rcl_interfaces::msg::IntegerRange>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // RCL_INTERFACES__MSG__DETAIL__INTEGER_RANGE__TRAITS_HPP_
