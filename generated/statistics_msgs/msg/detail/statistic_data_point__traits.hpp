// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from statistics_msgs:msg/StatisticDataPoint.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "statistics_msgs/msg/statistic_data_point.hpp"


#ifndef STATISTICS_MSGS__MSG__DETAIL__STATISTIC_DATA_POINT__TRAITS_HPP_
#define STATISTICS_MSGS__MSG__DETAIL__STATISTIC_DATA_POINT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "statistics_msgs/msg/detail/statistic_data_point__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace statistics_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const StatisticDataPoint & msg,
  std::ostream & out)
{
  out << "{";
  // member: data_type
  {
    out << "data_type: ";
    rosidl_generator_traits::value_to_yaml(msg.data_type, out);
    out << ", ";
  }

  // member: data
  {
    out << "data: ";
    rosidl_generator_traits::value_to_yaml(msg.data, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const StatisticDataPoint & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: data_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "data_type: ";
    rosidl_generator_traits::value_to_yaml(msg.data_type, out);
    out << "\n";
  }

  // member: data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "data: ";
    rosidl_generator_traits::value_to_yaml(msg.data, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const StatisticDataPoint & msg, bool use_flow_style = false)
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

}  // namespace statistics_msgs

namespace rosidl_generator_traits
{

[[deprecated("use statistics_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const statistics_msgs::msg::StatisticDataPoint & msg,
  std::ostream & out, size_t indentation = 0)
{
  statistics_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use statistics_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const statistics_msgs::msg::StatisticDataPoint & msg)
{
  return statistics_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<statistics_msgs::msg::StatisticDataPoint>()
{
  return "statistics_msgs::msg::StatisticDataPoint";
}

template<>
inline const char * name<statistics_msgs::msg::StatisticDataPoint>()
{
  return "statistics_msgs/msg/StatisticDataPoint";
}

template<>
struct has_fixed_size<statistics_msgs::msg::StatisticDataPoint>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<statistics_msgs::msg::StatisticDataPoint>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<statistics_msgs::msg::StatisticDataPoint>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // STATISTICS_MSGS__MSG__DETAIL__STATISTIC_DATA_POINT__TRAITS_HPP_
