// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from service_msgs:msg/ServiceEventInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "service_msgs/msg/service_event_info.hpp"


#ifndef SERVICE_MSGS__MSG__DETAIL__SERVICE_EVENT_INFO__TRAITS_HPP_
#define SERVICE_MSGS__MSG__DETAIL__SERVICE_EVENT_INFO__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "service_msgs/msg/detail/service_event_info__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace service_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const ServiceEventInfo & msg,
  std::ostream & out)
{
  out << "{";
  // member: event_type
  {
    out << "event_type: ";
    rosidl_generator_traits::value_to_yaml(msg.event_type, out);
    out << ", ";
  }

  // member: stamp
  {
    out << "stamp: ";
    to_flow_style_yaml(msg.stamp, out);
    out << ", ";
  }

  // member: client_gid
  {
    if (msg.client_gid.size() == 0) {
      out << "client_gid: []";
    } else {
      out << "client_gid: [";
      size_t pending_items = msg.client_gid.size();
      for (auto item : msg.client_gid) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: sequence_number
  {
    out << "sequence_number: ";
    rosidl_generator_traits::value_to_yaml(msg.sequence_number, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ServiceEventInfo & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: event_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "event_type: ";
    rosidl_generator_traits::value_to_yaml(msg.event_type, out);
    out << "\n";
  }

  // member: stamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stamp:\n";
    to_block_style_yaml(msg.stamp, out, indentation + 2);
  }

  // member: client_gid
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.client_gid.size() == 0) {
      out << "client_gid: []\n";
    } else {
      out << "client_gid:\n";
      for (auto item : msg.client_gid) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: sequence_number
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sequence_number: ";
    rosidl_generator_traits::value_to_yaml(msg.sequence_number, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ServiceEventInfo & msg, bool use_flow_style = false)
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

}  // namespace service_msgs

namespace rosidl_generator_traits
{

[[deprecated("use service_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const service_msgs::msg::ServiceEventInfo & msg,
  std::ostream & out, size_t indentation = 0)
{
  service_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use service_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const service_msgs::msg::ServiceEventInfo & msg)
{
  return service_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<service_msgs::msg::ServiceEventInfo>()
{
  return "service_msgs::msg::ServiceEventInfo";
}

template<>
inline const char * name<service_msgs::msg::ServiceEventInfo>()
{
  return "service_msgs/msg/ServiceEventInfo";
}

template<>
struct has_fixed_size<service_msgs::msg::ServiceEventInfo>
  : std::integral_constant<bool, has_fixed_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct has_bounded_size<service_msgs::msg::ServiceEventInfo>
  : std::integral_constant<bool, has_bounded_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct is_message<service_msgs::msg::ServiceEventInfo>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SERVICE_MSGS__MSG__DETAIL__SERVICE_EVENT_INFO__TRAITS_HPP_
