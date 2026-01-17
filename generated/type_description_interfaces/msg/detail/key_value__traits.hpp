// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from type_description_interfaces:msg/KeyValue.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "type_description_interfaces/msg/key_value.hpp"


#ifndef TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__KEY_VALUE__TRAITS_HPP_
#define TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__KEY_VALUE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "type_description_interfaces/msg/detail/key_value__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace type_description_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const KeyValue & msg,
  std::ostream & out)
{
  out << "{";
  // member: key
  {
    out << "key: ";
    rosidl_generator_traits::value_to_yaml(msg.key, out);
    out << ", ";
  }

  // member: value
  {
    out << "value: ";
    rosidl_generator_traits::value_to_yaml(msg.value, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const KeyValue & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: key
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "key: ";
    rosidl_generator_traits::value_to_yaml(msg.key, out);
    out << "\n";
  }

  // member: value
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "value: ";
    rosidl_generator_traits::value_to_yaml(msg.value, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const KeyValue & msg, bool use_flow_style = false)
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

}  // namespace type_description_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use type_description_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const type_description_interfaces::msg::KeyValue & msg,
  std::ostream & out, size_t indentation = 0)
{
  type_description_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use type_description_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const type_description_interfaces::msg::KeyValue & msg)
{
  return type_description_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<type_description_interfaces::msg::KeyValue>()
{
  return "type_description_interfaces::msg::KeyValue";
}

template<>
inline const char * name<type_description_interfaces::msg::KeyValue>()
{
  return "type_description_interfaces/msg/KeyValue";
}

template<>
struct has_fixed_size<type_description_interfaces::msg::KeyValue>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<type_description_interfaces::msg::KeyValue>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<type_description_interfaces::msg::KeyValue>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__KEY_VALUE__TRAITS_HPP_
