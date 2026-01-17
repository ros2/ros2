// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rcl_interfaces:msg/SetParametersResult.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/msg/set_parameters_result.hpp"


#ifndef RCL_INTERFACES__MSG__DETAIL__SET_PARAMETERS_RESULT__TRAITS_HPP_
#define RCL_INTERFACES__MSG__DETAIL__SET_PARAMETERS_RESULT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rcl_interfaces/msg/detail/set_parameters_result__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace rcl_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const SetParametersResult & msg,
  std::ostream & out)
{
  out << "{";
  // member: successful
  {
    out << "successful: ";
    rosidl_generator_traits::value_to_yaml(msg.successful, out);
    out << ", ";
  }

  // member: reason
  {
    out << "reason: ";
    rosidl_generator_traits::value_to_yaml(msg.reason, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetParametersResult & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: successful
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "successful: ";
    rosidl_generator_traits::value_to_yaml(msg.successful, out);
    out << "\n";
  }

  // member: reason
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "reason: ";
    rosidl_generator_traits::value_to_yaml(msg.reason, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetParametersResult & msg, bool use_flow_style = false)
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
  const rcl_interfaces::msg::SetParametersResult & msg,
  std::ostream & out, size_t indentation = 0)
{
  rcl_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rcl_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const rcl_interfaces::msg::SetParametersResult & msg)
{
  return rcl_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<rcl_interfaces::msg::SetParametersResult>()
{
  return "rcl_interfaces::msg::SetParametersResult";
}

template<>
inline const char * name<rcl_interfaces::msg::SetParametersResult>()
{
  return "rcl_interfaces/msg/SetParametersResult";
}

template<>
struct has_fixed_size<rcl_interfaces::msg::SetParametersResult>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<rcl_interfaces::msg::SetParametersResult>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<rcl_interfaces::msg::SetParametersResult>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // RCL_INTERFACES__MSG__DETAIL__SET_PARAMETERS_RESULT__TRAITS_HPP_
