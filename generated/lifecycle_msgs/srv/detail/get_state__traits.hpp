// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from lifecycle_msgs:srv/GetState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "lifecycle_msgs/srv/get_state.hpp"


#ifndef LIFECYCLE_MSGS__SRV__DETAIL__GET_STATE__TRAITS_HPP_
#define LIFECYCLE_MSGS__SRV__DETAIL__GET_STATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "lifecycle_msgs/srv/detail/get_state__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace lifecycle_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetState_Request & msg,
  std::ostream & out)
{
  (void)msg;
  out << "null";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetState_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  (void)msg;
  (void)indentation;
  out << "null\n";
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetState_Request & msg, bool use_flow_style = false)
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
  const lifecycle_msgs::srv::GetState_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  lifecycle_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use lifecycle_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const lifecycle_msgs::srv::GetState_Request & msg)
{
  return lifecycle_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<lifecycle_msgs::srv::GetState_Request>()
{
  return "lifecycle_msgs::srv::GetState_Request";
}

template<>
inline const char * name<lifecycle_msgs::srv::GetState_Request>()
{
  return "lifecycle_msgs/srv/GetState_Request";
}

template<>
struct has_fixed_size<lifecycle_msgs::srv::GetState_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<lifecycle_msgs::srv::GetState_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<lifecycle_msgs::srv::GetState_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'current_state'
#include "lifecycle_msgs/msg/detail/state__traits.hpp"

namespace lifecycle_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetState_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: current_state
  {
    out << "current_state: ";
    to_flow_style_yaml(msg.current_state, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetState_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: current_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_state:\n";
    to_block_style_yaml(msg.current_state, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetState_Response & msg, bool use_flow_style = false)
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
  const lifecycle_msgs::srv::GetState_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  lifecycle_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use lifecycle_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const lifecycle_msgs::srv::GetState_Response & msg)
{
  return lifecycle_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<lifecycle_msgs::srv::GetState_Response>()
{
  return "lifecycle_msgs::srv::GetState_Response";
}

template<>
inline const char * name<lifecycle_msgs::srv::GetState_Response>()
{
  return "lifecycle_msgs/srv/GetState_Response";
}

template<>
struct has_fixed_size<lifecycle_msgs::srv::GetState_Response>
  : std::integral_constant<bool, has_fixed_size<lifecycle_msgs::msg::State>::value> {};

template<>
struct has_bounded_size<lifecycle_msgs::srv::GetState_Response>
  : std::integral_constant<bool, has_bounded_size<lifecycle_msgs::msg::State>::value> {};

template<>
struct is_message<lifecycle_msgs::srv::GetState_Response>
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
  const GetState_Event & msg,
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
  const GetState_Event & msg,
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

inline std::string to_yaml(const GetState_Event & msg, bool use_flow_style = false)
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
  const lifecycle_msgs::srv::GetState_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  lifecycle_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use lifecycle_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const lifecycle_msgs::srv::GetState_Event & msg)
{
  return lifecycle_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<lifecycle_msgs::srv::GetState_Event>()
{
  return "lifecycle_msgs::srv::GetState_Event";
}

template<>
inline const char * name<lifecycle_msgs::srv::GetState_Event>()
{
  return "lifecycle_msgs/srv/GetState_Event";
}

template<>
struct has_fixed_size<lifecycle_msgs::srv::GetState_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<lifecycle_msgs::srv::GetState_Event>
  : std::integral_constant<bool, has_bounded_size<lifecycle_msgs::srv::GetState_Request>::value && has_bounded_size<lifecycle_msgs::srv::GetState_Response>::value && has_bounded_size<service_msgs::msg::ServiceEventInfo>::value> {};

template<>
struct is_message<lifecycle_msgs::srv::GetState_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<lifecycle_msgs::srv::GetState>()
{
  return "lifecycle_msgs::srv::GetState";
}

template<>
inline const char * name<lifecycle_msgs::srv::GetState>()
{
  return "lifecycle_msgs/srv/GetState";
}

template<>
struct has_fixed_size<lifecycle_msgs::srv::GetState>
  : std::integral_constant<
    bool,
    has_fixed_size<lifecycle_msgs::srv::GetState_Request>::value &&
    has_fixed_size<lifecycle_msgs::srv::GetState_Response>::value
  >
{
};

template<>
struct has_bounded_size<lifecycle_msgs::srv::GetState>
  : std::integral_constant<
    bool,
    has_bounded_size<lifecycle_msgs::srv::GetState_Request>::value &&
    has_bounded_size<lifecycle_msgs::srv::GetState_Response>::value
  >
{
};

template<>
struct is_service<lifecycle_msgs::srv::GetState>
  : std::true_type
{
};

template<>
struct is_service_request<lifecycle_msgs::srv::GetState_Request>
  : std::true_type
{
};

template<>
struct is_service_response<lifecycle_msgs::srv::GetState_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // LIFECYCLE_MSGS__SRV__DETAIL__GET_STATE__TRAITS_HPP_
