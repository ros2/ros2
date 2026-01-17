// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rcl_interfaces:srv/SetParametersAtomically.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/srv/set_parameters_atomically.hpp"


#ifndef RCL_INTERFACES__SRV__DETAIL__SET_PARAMETERS_ATOMICALLY__TRAITS_HPP_
#define RCL_INTERFACES__SRV__DETAIL__SET_PARAMETERS_ATOMICALLY__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rcl_interfaces/srv/detail/set_parameters_atomically__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'parameters'
#include "rcl_interfaces/msg/detail/parameter__traits.hpp"

namespace rcl_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetParametersAtomically_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: parameters
  {
    if (msg.parameters.size() == 0) {
      out << "parameters: []";
    } else {
      out << "parameters: [";
      size_t pending_items = msg.parameters.size();
      for (auto item : msg.parameters) {
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
  const SetParametersAtomically_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: parameters
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.parameters.size() == 0) {
      out << "parameters: []\n";
    } else {
      out << "parameters:\n";
      for (auto item : msg.parameters) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetParametersAtomically_Request & msg, bool use_flow_style = false)
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

}  // namespace rcl_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use rcl_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const rcl_interfaces::srv::SetParametersAtomically_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  rcl_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rcl_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const rcl_interfaces::srv::SetParametersAtomically_Request & msg)
{
  return rcl_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<rcl_interfaces::srv::SetParametersAtomically_Request>()
{
  return "rcl_interfaces::srv::SetParametersAtomically_Request";
}

template<>
inline const char * name<rcl_interfaces::srv::SetParametersAtomically_Request>()
{
  return "rcl_interfaces/srv/SetParametersAtomically_Request";
}

template<>
struct has_fixed_size<rcl_interfaces::srv::SetParametersAtomically_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<rcl_interfaces::srv::SetParametersAtomically_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<rcl_interfaces::srv::SetParametersAtomically_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'result'
#include "rcl_interfaces/msg/detail/set_parameters_result__traits.hpp"

namespace rcl_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetParametersAtomically_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: result
  {
    out << "result: ";
    to_flow_style_yaml(msg.result, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetParametersAtomically_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: result
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "result:\n";
    to_block_style_yaml(msg.result, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetParametersAtomically_Response & msg, bool use_flow_style = false)
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

}  // namespace rcl_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use rcl_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const rcl_interfaces::srv::SetParametersAtomically_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  rcl_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rcl_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const rcl_interfaces::srv::SetParametersAtomically_Response & msg)
{
  return rcl_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<rcl_interfaces::srv::SetParametersAtomically_Response>()
{
  return "rcl_interfaces::srv::SetParametersAtomically_Response";
}

template<>
inline const char * name<rcl_interfaces::srv::SetParametersAtomically_Response>()
{
  return "rcl_interfaces/srv/SetParametersAtomically_Response";
}

template<>
struct has_fixed_size<rcl_interfaces::srv::SetParametersAtomically_Response>
  : std::integral_constant<bool, has_fixed_size<rcl_interfaces::msg::SetParametersResult>::value> {};

template<>
struct has_bounded_size<rcl_interfaces::srv::SetParametersAtomically_Response>
  : std::integral_constant<bool, has_bounded_size<rcl_interfaces::msg::SetParametersResult>::value> {};

template<>
struct is_message<rcl_interfaces::srv::SetParametersAtomically_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__traits.hpp"

namespace rcl_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetParametersAtomically_Event & msg,
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
  const SetParametersAtomically_Event & msg,
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

inline std::string to_yaml(const SetParametersAtomically_Event & msg, bool use_flow_style = false)
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

}  // namespace rcl_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use rcl_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const rcl_interfaces::srv::SetParametersAtomically_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  rcl_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rcl_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const rcl_interfaces::srv::SetParametersAtomically_Event & msg)
{
  return rcl_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<rcl_interfaces::srv::SetParametersAtomically_Event>()
{
  return "rcl_interfaces::srv::SetParametersAtomically_Event";
}

template<>
inline const char * name<rcl_interfaces::srv::SetParametersAtomically_Event>()
{
  return "rcl_interfaces/srv/SetParametersAtomically_Event";
}

template<>
struct has_fixed_size<rcl_interfaces::srv::SetParametersAtomically_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<rcl_interfaces::srv::SetParametersAtomically_Event>
  : std::integral_constant<bool, has_bounded_size<rcl_interfaces::srv::SetParametersAtomically_Request>::value && has_bounded_size<rcl_interfaces::srv::SetParametersAtomically_Response>::value && has_bounded_size<service_msgs::msg::ServiceEventInfo>::value> {};

template<>
struct is_message<rcl_interfaces::srv::SetParametersAtomically_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<rcl_interfaces::srv::SetParametersAtomically>()
{
  return "rcl_interfaces::srv::SetParametersAtomically";
}

template<>
inline const char * name<rcl_interfaces::srv::SetParametersAtomically>()
{
  return "rcl_interfaces/srv/SetParametersAtomically";
}

template<>
struct has_fixed_size<rcl_interfaces::srv::SetParametersAtomically>
  : std::integral_constant<
    bool,
    has_fixed_size<rcl_interfaces::srv::SetParametersAtomically_Request>::value &&
    has_fixed_size<rcl_interfaces::srv::SetParametersAtomically_Response>::value
  >
{
};

template<>
struct has_bounded_size<rcl_interfaces::srv::SetParametersAtomically>
  : std::integral_constant<
    bool,
    has_bounded_size<rcl_interfaces::srv::SetParametersAtomically_Request>::value &&
    has_bounded_size<rcl_interfaces::srv::SetParametersAtomically_Response>::value
  >
{
};

template<>
struct is_service<rcl_interfaces::srv::SetParametersAtomically>
  : std::true_type
{
};

template<>
struct is_service_request<rcl_interfaces::srv::SetParametersAtomically_Request>
  : std::true_type
{
};

template<>
struct is_service_response<rcl_interfaces::srv::SetParametersAtomically_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // RCL_INTERFACES__SRV__DETAIL__SET_PARAMETERS_ATOMICALLY__TRAITS_HPP_
