// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from statistics_msgs:msg/StatisticDataType.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "statistics_msgs/msg/statistic_data_type.hpp"


#ifndef STATISTICS_MSGS__MSG__DETAIL__STATISTIC_DATA_TYPE__TRAITS_HPP_
#define STATISTICS_MSGS__MSG__DETAIL__STATISTIC_DATA_TYPE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "statistics_msgs/msg/detail/statistic_data_type__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace statistics_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const StatisticDataType & msg,
  std::ostream & out)
{
  (void)msg;
  out << "null";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const StatisticDataType & msg,
  std::ostream & out, size_t indentation = 0)
{
  (void)msg;
  (void)indentation;
  out << "null\n";
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const StatisticDataType & msg, bool use_flow_style = false)
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
  const statistics_msgs::msg::StatisticDataType & msg,
  std::ostream & out, size_t indentation = 0)
{
  statistics_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use statistics_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const statistics_msgs::msg::StatisticDataType & msg)
{
  return statistics_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<statistics_msgs::msg::StatisticDataType>()
{
  return "statistics_msgs::msg::StatisticDataType";
}

template<>
inline const char * name<statistics_msgs::msg::StatisticDataType>()
{
  return "statistics_msgs/msg/StatisticDataType";
}

template<>
struct has_fixed_size<statistics_msgs::msg::StatisticDataType>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<statistics_msgs::msg::StatisticDataType>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<statistics_msgs::msg::StatisticDataType>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // STATISTICS_MSGS__MSG__DETAIL__STATISTIC_DATA_TYPE__TRAITS_HPP_
