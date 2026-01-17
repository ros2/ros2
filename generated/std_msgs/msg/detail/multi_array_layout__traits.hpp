// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from std_msgs:msg/MultiArrayLayout.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "std_msgs/msg/multi_array_layout.hpp"


#ifndef STD_MSGS__MSG__DETAIL__MULTI_ARRAY_LAYOUT__TRAITS_HPP_
#define STD_MSGS__MSG__DETAIL__MULTI_ARRAY_LAYOUT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "std_msgs/msg/detail/multi_array_layout__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'dim'
#include "std_msgs/msg/detail/multi_array_dimension__traits.hpp"

namespace std_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const MultiArrayLayout & msg,
  std::ostream & out)
{
  out << "{";
  // member: dim
  {
    if (msg.dim.size() == 0) {
      out << "dim: []";
    } else {
      out << "dim: [";
      size_t pending_items = msg.dim.size();
      for (auto item : msg.dim) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: data_offset
  {
    out << "data_offset: ";
    rosidl_generator_traits::value_to_yaml(msg.data_offset, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MultiArrayLayout & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: dim
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.dim.size() == 0) {
      out << "dim: []\n";
    } else {
      out << "dim:\n";
      for (auto item : msg.dim) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: data_offset
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "data_offset: ";
    rosidl_generator_traits::value_to_yaml(msg.data_offset, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MultiArrayLayout & msg, bool use_flow_style = false)
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

}  // namespace std_msgs

namespace rosidl_generator_traits
{

[[deprecated("use std_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const std_msgs::msg::MultiArrayLayout & msg,
  std::ostream & out, size_t indentation = 0)
{
  std_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use std_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const std_msgs::msg::MultiArrayLayout & msg)
{
  return std_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<std_msgs::msg::MultiArrayLayout>()
{
  return "std_msgs::msg::MultiArrayLayout";
}

template<>
inline const char * name<std_msgs::msg::MultiArrayLayout>()
{
  return "std_msgs/msg/MultiArrayLayout";
}

template<>
struct has_fixed_size<std_msgs::msg::MultiArrayLayout>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<std_msgs::msg::MultiArrayLayout>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<std_msgs::msg::MultiArrayLayout>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // STD_MSGS__MSG__DETAIL__MULTI_ARRAY_LAYOUT__TRAITS_HPP_
