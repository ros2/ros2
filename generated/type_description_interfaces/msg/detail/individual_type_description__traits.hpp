// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from type_description_interfaces:msg/IndividualTypeDescription.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "type_description_interfaces/msg/individual_type_description.hpp"


#ifndef TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__INDIVIDUAL_TYPE_DESCRIPTION__TRAITS_HPP_
#define TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__INDIVIDUAL_TYPE_DESCRIPTION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "type_description_interfaces/msg/detail/individual_type_description__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'fields'
#include "type_description_interfaces/msg/detail/field__traits.hpp"

namespace type_description_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const IndividualTypeDescription & msg,
  std::ostream & out)
{
  out << "{";
  // member: type_name
  {
    out << "type_name: ";
    rosidl_generator_traits::value_to_yaml(msg.type_name, out);
    out << ", ";
  }

  // member: fields
  {
    if (msg.fields.size() == 0) {
      out << "fields: []";
    } else {
      out << "fields: [";
      size_t pending_items = msg.fields.size();
      for (auto item : msg.fields) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const IndividualTypeDescription & msg,
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

  // member: fields
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.fields.size() == 0) {
      out << "fields: []\n";
    } else {
      out << "fields:\n";
      for (auto item : msg.fields) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const IndividualTypeDescription & msg, bool use_flow_style = false)
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
  const type_description_interfaces::msg::IndividualTypeDescription & msg,
  std::ostream & out, size_t indentation = 0)
{
  type_description_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use type_description_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const type_description_interfaces::msg::IndividualTypeDescription & msg)
{
  return type_description_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<type_description_interfaces::msg::IndividualTypeDescription>()
{
  return "type_description_interfaces::msg::IndividualTypeDescription";
}

template<>
inline const char * name<type_description_interfaces::msg::IndividualTypeDescription>()
{
  return "type_description_interfaces/msg/IndividualTypeDescription";
}

template<>
struct has_fixed_size<type_description_interfaces::msg::IndividualTypeDescription>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<type_description_interfaces::msg::IndividualTypeDescription>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<type_description_interfaces::msg::IndividualTypeDescription>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // TYPE_DESCRIPTION_INTERFACES__MSG__DETAIL__INDIVIDUAL_TYPE_DESCRIPTION__TRAITS_HPP_
