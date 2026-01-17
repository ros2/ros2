// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from lifecycle_msgs:srv/ChangeState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "lifecycle_msgs/srv/change_state.hpp"


#ifndef LIFECYCLE_MSGS__SRV__DETAIL__CHANGE_STATE__TRAITS_HPP_
#define LIFECYCLE_MSGS__SRV__DETAIL__CHANGE_STATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "lifecycle_msgs/srv/detail/change_state__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'transition'
#include "lifecycle_msgs/msg/detail/transition__traits.hpp"

namespace lifecycle_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const ChangeState_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: transition
  {
    out << "transition: ";
    to_flow_style_yaml(msg.transition, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ChangeState_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: transition
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "transition:\n";
    to_block_style_yaml(msg.transition, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ChangeState_Request & msg, bool use_flow_style = false)
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
  const lifecycle_msgs::srv::ChangeState_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  lifecycle_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use lifecycle_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const lifecycle_msgs::srv::ChangeState_Request & msg)
{
  return lifecycle_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<lifecycle_msgs::srv::ChangeState_Request>()
{
  return "lifecycle_msgs::srv::ChangeState_Request";
}

template<>
inline const char * name<lifecycle_msgs::srv::ChangeState_Request>()
{
  return "lifecycle_msgs/srv/ChangeState_Request";
}

template<>
struct has_fixed_size<lifecycle_msgs::srv::ChangeState_Request>
  : std::integral_constant<bool, has_fixed_size<lifecycle_msgs::msg::Transition>::value> {};

template<>
struct has_bounded_size<lifecycle_msgs::srv::ChangeState_Request>
  : std::integral_constant<bool, has_bounded_size<lifecycle_msgs::msg::Transition>::value> {};

template<>
struct is_message<lifecycle_msgs::srv::ChangeState_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace lifecycle_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const ChangeState_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ChangeState_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ChangeState_Response & msg, bool use_flow_style = false)
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
  const lifecycle_msgs::srv::ChangeState_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  lifecycle_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use lifecycle_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const lifecycle_msgs::srv::ChangeState_Response & msg)
{
  return lifecycle_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<lifecycle_msgs::srv::ChangeState_Response>()
{
  return "lifecycle_msgs::srv::ChangeState_Response";
}

template<>
inline const char * name<lifecycle_msgs::srv::ChangeState_Response>()
{
  return "lifecycle_msgs/srv/ChangeState_Response";
}

template<>
struct has_fixed_size<lifecycle_msgs::srv::ChangeState_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<lifecycle_msgs::srv::ChangeState_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<lifecycle_msgs::srv::ChangeState_Response>
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
  const ChangeState_Event & msg,
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
  const ChangeState_Event & msg,
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

inline std::string to_yaml(const ChangeState_Event & msg, bool use_flow_style = false)
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
  const lifecycle_msgs::srv::ChangeState_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  lifecycle_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use lifecycle_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const lifecycle_msgs::srv::ChangeState_Event & msg)
{
  return lifecycle_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<lifecycle_msgs::srv::ChangeState_Event>()
{
  return "lifecycle_msgs::srv::ChangeState_Event";
}

template<>
inline const char * name<lifecycle_msgs::srv::ChangeState_Event>()
{
  return "lifecycle_msgs/srv/ChangeState_Event";
}

template<>
struct has_fixed_size<lifecycle_msgs::srv::ChangeState_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<lifecycle_msgs::srv::ChangeState_Event>
  : std::integral_constant<bool, has_bounded_size<lifecycle_msgs::srv::ChangeState_Request>::value && has_bounded_size<lifecycle_msgs::srv::ChangeState_Response>::value && has_bounded_size<service_msgs::msg::ServiceEventInfo>::value> {};

template<>
struct is_message<lifecycle_msgs::srv::ChangeState_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<lifecycle_msgs::srv::ChangeState>()
{
  return "lifecycle_msgs::srv::ChangeState";
}

template<>
inline const char * name<lifecycle_msgs::srv::ChangeState>()
{
  return "lifecycle_msgs/srv/ChangeState";
}

template<>
struct has_fixed_size<lifecycle_msgs::srv::ChangeState>
  : std::integral_constant<
    bool,
    has_fixed_size<lifecycle_msgs::srv::ChangeState_Request>::value &&
    has_fixed_size<lifecycle_msgs::srv::ChangeState_Response>::value
  >
{
};

template<>
struct has_bounded_size<lifecycle_msgs::srv::ChangeState>
  : std::integral_constant<
    bool,
    has_bounded_size<lifecycle_msgs::srv::ChangeState_Request>::value &&
    has_bounded_size<lifecycle_msgs::srv::ChangeState_Response>::value
  >
{
};

template<>
struct is_service<lifecycle_msgs::srv::ChangeState>
  : std::true_type
{
};

template<>
struct is_service_request<lifecycle_msgs::srv::ChangeState_Request>
  : std::true_type
{
};

template<>
struct is_service_response<lifecycle_msgs::srv::ChangeState_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // LIFECYCLE_MSGS__SRV__DETAIL__CHANGE_STATE__TRAITS_HPP_
