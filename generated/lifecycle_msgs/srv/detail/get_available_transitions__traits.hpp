// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from lifecycle_msgs:srv/GetAvailableTransitions.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "lifecycle_msgs/srv/get_available_transitions.hpp"


#ifndef LIFECYCLE_MSGS__SRV__DETAIL__GET_AVAILABLE_TRANSITIONS__TRAITS_HPP_
#define LIFECYCLE_MSGS__SRV__DETAIL__GET_AVAILABLE_TRANSITIONS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "lifecycle_msgs/srv/detail/get_available_transitions__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace lifecycle_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetAvailableTransitions_Request & msg,
  std::ostream & out)
{
  (void)msg;
  out << "null";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetAvailableTransitions_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  (void)msg;
  (void)indentation;
  out << "null\n";
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetAvailableTransitions_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace lifecycle_msgs

namespace rosidl_generator_traits
{

[[deprecated("use lifecycle_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const lifecycle_msgs::srv::GetAvailableTransitions_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  lifecycle_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use lifecycle_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const lifecycle_msgs::srv::GetAvailableTransitions_Request & msg)
{
  return lifecycle_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<lifecycle_msgs::srv::GetAvailableTransitions_Request>()
{
  return "lifecycle_msgs::srv::GetAvailableTransitions_Request";
}

template<>
inline const char * name<lifecycle_msgs::srv::GetAvailableTransitions_Request>()
{
  return "lifecycle_msgs/srv/GetAvailableTransitions_Request";
}

template<>
struct has_fixed_size<lifecycle_msgs::srv::GetAvailableTransitions_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<lifecycle_msgs::srv::GetAvailableTransitions_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<lifecycle_msgs::srv::GetAvailableTransitions_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'available_transitions'
#include "lifecycle_msgs/msg/detail/transition_description__traits.hpp"

namespace lifecycle_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetAvailableTransitions_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: available_transitions
  {
    if (msg.available_transitions.size() == 0) {
      out << "available_transitions: []";
    } else {
      out << "available_transitions: [";
      size_t pending_items = msg.available_transitions.size();
      for (auto item : msg.available_transitions) {
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
  const GetAvailableTransitions_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: available_transitions
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.available_transitions.size() == 0) {
      out << "available_transitions: []\n";
    } else {
      out << "available_transitions:\n";
      for (auto item : msg.available_transitions) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetAvailableTransitions_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace lifecycle_msgs

namespace rosidl_generator_traits
{

[[deprecated("use lifecycle_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const lifecycle_msgs::srv::GetAvailableTransitions_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  lifecycle_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use lifecycle_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const lifecycle_msgs::srv::GetAvailableTransitions_Response & msg)
{
  return lifecycle_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<lifecycle_msgs::srv::GetAvailableTransitions_Response>()
{
  return "lifecycle_msgs::srv::GetAvailableTransitions_Response";
}

template<>
inline const char * name<lifecycle_msgs::srv::GetAvailableTransitions_Response>()
{
  return "lifecycle_msgs/srv/GetAvailableTransitions_Response";
}

template<>
struct has_fixed_size<lifecycle_msgs::srv::GetAvailableTransitions_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<lifecycle_msgs::srv::GetAvailableTransitions_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<lifecycle_msgs::srv::GetAvailableTransitions_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__traits.hpp"

namespace lifecycle_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetAvailableTransitions_Event & msg,
  std::ostream & out)
{
  out << "{";
  // member: info
  {
    out << "info: ";
    to_flow_style_yaml(msg.info, out);
    out << ", ";
  }

  // member: request
  {
    if (msg.request.size() == 0) {
      out << "request: []";
    } else {
      out << "request: [";
      size_t pending_items = msg.request.size();
      for (auto item : msg.request) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: response
  {
    if (msg.response.size() == 0) {
      out << "response: []";
    } else {
      out << "response: [";
      size_t pending_items = msg.response.size();
      for (auto item : msg.response) {
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
  const GetAvailableTransitions_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: info
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "info:\n";
    to_block_style_yaml(msg.info, out, indentation + 2);
  }

  // member: request
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.request.size() == 0) {
      out << "request: []\n";
    } else {
      out << "request:\n";
      for (auto item : msg.request) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: response
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.response.size() == 0) {
      out << "response: []\n";
    } else {
      out << "response:\n";
      for (auto item : msg.response) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetAvailableTransitions_Event & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace lifecycle_msgs

namespace rosidl_generator_traits
{

[[deprecated("use lifecycle_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const lifecycle_msgs::srv::GetAvailableTransitions_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  lifecycle_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use lifecycle_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const lifecycle_msgs::srv::GetAvailableTransitions_Event & msg)
{
  return lifecycle_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<lifecycle_msgs::srv::GetAvailableTransitions_Event>()
{
  return "lifecycle_msgs::srv::GetAvailableTransitions_Event";
}

template<>
inline const char * name<lifecycle_msgs::srv::GetAvailableTransitions_Event>()
{
  return "lifecycle_msgs/srv/GetAvailableTransitions_Event";
}

template<>
struct has_fixed_size<lifecycle_msgs::srv::GetAvailableTransitions_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<lifecycle_msgs::srv::GetAvailableTransitions_Event>
  : std::integral_constant<bool, has_bounded_size<lifecycle_msgs::srv::GetAvailableTransitions_Request>::value && has_bounded_size<lifecycle_msgs::srv::GetAvailableTransitions_Response>::value && has_bounded_size<service_msgs::msg::ServiceEventInfo>::value> {};

template<>
struct is_message<lifecycle_msgs::srv::GetAvailableTransitions_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<lifecycle_msgs::srv::GetAvailableTransitions>()
{
  return "lifecycle_msgs::srv::GetAvailableTransitions";
}

template<>
inline const char * name<lifecycle_msgs::srv::GetAvailableTransitions>()
{
  return "lifecycle_msgs/srv/GetAvailableTransitions";
}

template<>
struct has_fixed_size<lifecycle_msgs::srv::GetAvailableTransitions>
  : std::integral_constant<
    bool,
    has_fixed_size<lifecycle_msgs::srv::GetAvailableTransitions_Request>::value &&
    has_fixed_size<lifecycle_msgs::srv::GetAvailableTransitions_Response>::value
  >
{
};

template<>
struct has_bounded_size<lifecycle_msgs::srv::GetAvailableTransitions>
  : std::integral_constant<
    bool,
    has_bounded_size<lifecycle_msgs::srv::GetAvailableTransitions_Request>::value &&
    has_bounded_size<lifecycle_msgs::srv::GetAvailableTransitions_Response>::value
  >
{
};

template<>
struct is_service<lifecycle_msgs::srv::GetAvailableTransitions>
  : std::true_type
{
};

template<>
struct is_service_request<lifecycle_msgs::srv::GetAvailableTransitions_Request>
  : std::true_type
{
};

template<>
struct is_service_response<lifecycle_msgs::srv::GetAvailableTransitions_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // LIFECYCLE_MSGS__SRV__DETAIL__GET_AVAILABLE_TRANSITIONS__TRAITS_HPP_
