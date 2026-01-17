// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from type_description_interfaces:msg/TypeSource.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "type_description_interfaces/msg/type_source.hpp"


#ifndef TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__TYPE_SOURCE__TRAITS_HPP_
#define TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__TYPE_SOURCE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "type_description_interfaces/msg/detail/type_source__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace type_description_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const TypeSource & msg,
  std::ostream & out)
{
  out << "{";
  // member: type_name
  {
    out << "type_name: ";
    rosidl_generator_traits::value_to_yaml(msg.type_name, out);
    out << ", ";
  }

  // member: encoding
  {
    out << "encoding: ";
    rosidl_generator_traits::value_to_yaml(msg.encoding, out);
    out << ", ";
  }

  // member: raw_file_contents
  {
    out << "raw_file_contents: ";
    rosidl_generator_traits::value_to_yaml(msg.raw_file_contents, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const TypeSource & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: type_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "type_name: ";
    rosidl_generator_traits::value_to_yaml(msg.type_name, out);
    out << "\n";
  }

  // member: encoding
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "encoding: ";
    rosidl_generator_traits::value_to_yaml(msg.encoding, out);
    out << "\n";
  }

  // member: raw_file_contents
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "raw_file_contents: ";
    rosidl_generator_traits::value_to_yaml(msg.raw_file_contents, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const TypeSource & msg, bool use_flow_style = false)
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
  const type_description_interfaces::msg::TypeSource & msg,
  std::ostream & out, size_t indentation = 0)
{
  type_description_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use type_description_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const type_description_interfaces::msg::TypeSource & msg)
{
  return type_description_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<type_description_interfaces::msg::TypeSource>()
{
  return "type_description_interfaces::msg::TypeSource";
}

template<>
inline const char * name<type_description_interfaces::msg::TypeSource>()
{
  return "type_description_interfaces/msg/TypeSource";
}

template<>
struct has_fixed_size<type_description_interfaces::msg::TypeSource>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<type_description_interfaces::msg::TypeSource>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<type_description_interfaces::msg::TypeSource>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__TYPE_SOURCE__TRAITS_HPP_
