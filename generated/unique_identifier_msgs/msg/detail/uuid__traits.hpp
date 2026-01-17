// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from unique_identifier_msgs:msg/UUID.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "unique_identifier_msgs/msg/uuid.hpp"


#ifndef UNIQUE_IDENTIFIER_MSGS__MSG__DETAIL__UUID__TRAITS_HPP_
#define UNIQUE_IDENTIFIER_MSGS__MSG__DETAIL__UUID__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace unique_identifier_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const UUID & msg,
  std::ostream & out)
{
  out << "{";
  // member: uuid
  {
    if (msg.uuid.size() == 0) {
      out << "uuid: []";
    } else {
      out << "uuid: [";
      size_t pending_items = msg.uuid.size();
      for (auto item : msg.uuid) {
        rosidl_generator_traits::value_to_yaml(item, out);
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
  const UUID & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: uuid
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.uuid.size() == 0) {
      out << "uuid: []\n";
    } else {
      out << "uuid:\n";
      for (auto item : msg.uuid) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const UUID & msg, bool use_flow_style = false)
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

}  // namespace unique_identifier_msgs

namespace rosidl_generator_traits
{

[[deprecated("use unique_identifier_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const unique_identifier_msgs::msg::UUID & msg,
  std::ostream & out, size_t indentation = 0)
{
  unique_identifier_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use unique_identifier_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const unique_identifier_msgs::msg::UUID & msg)
{
  return unique_identifier_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<unique_identifier_msgs::msg::UUID>()
{
  return "unique_identifier_msgs::msg::UUID";
}

template<>
inline const char * name<unique_identifier_msgs::msg::UUID>()
{
  return "unique_identifier_msgs/msg/UUID";
}

template<>
struct has_fixed_size<unique_identifier_msgs::msg::UUID>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<unique_identifier_msgs::msg::UUID>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<unique_identifier_msgs::msg::UUID>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // UNIQUE_IDENTIFIER_MSGS__MSG__DETAIL__UUID__TRAITS_HPP_
