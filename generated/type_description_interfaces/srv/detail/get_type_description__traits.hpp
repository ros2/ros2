// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from type_description_interfaces:srv/GetTypeDescription.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "type_description_interfaces/srv/get_type_description.hpp"


#ifndef TYPE_DESCRIPTION_INTERFACES__SRV__DETAIL__GET_TYPE_DESCRIPTION__TRAITS_HPP_
#define TYPE_DESCRIPTION_INTERFACES__SRV__DETAIL__GET_TYPE_DESCRIPTION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "type_description_interfaces/srv/detail/get_type_description__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace type_description_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetTypeDescription_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: type_name
  {
    out << "type_name: ";
    rosidl_generator_traits::value_to_yaml(msg.type_name, out);
    out << ", ";
  }

  // member: type_hash
  {
    out << "type_hash: ";
    rosidl_generator_traits::value_to_yaml(msg.type_hash, out);
    out << ", ";
  }

  // member: include_type_sources
  {
    out << "include_type_sources: ";
    rosidl_generator_traits::value_to_yaml(msg.include_type_sources, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetTypeDescription_Request & msg,
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

  // member: type_hash
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "type_hash: ";
    rosidl_generator_traits::value_to_yaml(msg.type_hash, out);
    out << "\n";
  }

  // member: include_type_sources
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "include_type_sources: ";
    rosidl_generator_traits::value_to_yaml(msg.include_type_sources, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetTypeDescription_Request & msg, bool use_flow_style = false)
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

}  // namespace type_description_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use type_description_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const type_description_interfaces::srv::GetTypeDescription_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  type_description_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use type_description_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const type_description_interfaces::srv::GetTypeDescription_Request & msg)
{
  return type_description_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<type_description_interfaces::srv::GetTypeDescription_Request>()
{
  return "type_description_interfaces::srv::GetTypeDescription_Request";
}

template<>
inline const char * name<type_description_interfaces::srv::GetTypeDescription_Request>()
{
  return "type_description_interfaces/srv/GetTypeDescription_Request";
}

template<>
struct has_fixed_size<type_description_interfaces::srv::GetTypeDescription_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<type_description_interfaces::srv::GetTypeDescription_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<type_description_interfaces::srv::GetTypeDescription_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'type_description'
#include "type_description_interfaces/msg/detail/type_description__traits.hpp"
// Member 'type_sources'
#include "type_description_interfaces/msg/detail/type_source__traits.hpp"
// Member 'extra_information'
#include "type_description_interfaces/msg/detail/key_value__traits.hpp"

namespace type_description_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetTypeDescription_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: successful
  {
    out << "successful: ";
    rosidl_generator_traits::value_to_yaml(msg.successful, out);
    out << ", ";
  }

  // member: failure_reason
  {
    out << "failure_reason: ";
    rosidl_generator_traits::value_to_yaml(msg.failure_reason, out);
    out << ", ";
  }

  // member: type_description
  {
    out << "type_description: ";
    to_flow_style_yaml(msg.type_description, out);
    out << ", ";
  }

  // member: type_sources
  {
    if (msg.type_sources.size() == 0) {
      out << "type_sources: []";
    } else {
      out << "type_sources: [";
      size_t pending_items = msg.type_sources.size();
      for (auto item : msg.type_sources) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: extra_information
  {
    if (msg.extra_information.size() == 0) {
      out << "extra_information: []";
    } else {
      out << "extra_information: [";
      size_t pending_items = msg.extra_information.size();
      for (auto item : msg.extra_information) {
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
  const GetTypeDescription_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: successful
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "successful: ";
    rosidl_generator_traits::value_to_yaml(msg.successful, out);
    out << "\n";
  }

  // member: failure_reason
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "failure_reason: ";
    rosidl_generator_traits::value_to_yaml(msg.failure_reason, out);
    out << "\n";
  }

  // member: type_description
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "type_description:\n";
    to_block_style_yaml(msg.type_description, out, indentation + 2);
  }

  // member: type_sources
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.type_sources.size() == 0) {
      out << "type_sources: []\n";
    } else {
      out << "type_sources:\n";
      for (auto item : msg.type_sources) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: extra_information
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.extra_information.size() == 0) {
      out << "extra_information: []\n";
    } else {
      out << "extra_information:\n";
      for (auto item : msg.extra_information) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetTypeDescription_Response & msg, bool use_flow_style = false)
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

}  // namespace type_description_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use type_description_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const type_description_interfaces::srv::GetTypeDescription_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  type_description_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use type_description_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const type_description_interfaces::srv::GetTypeDescription_Response & msg)
{
  return type_description_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<type_description_interfaces::srv::GetTypeDescription_Response>()
{
  return "type_description_interfaces::srv::GetTypeDescription_Response";
}

template<>
inline const char * name<type_description_interfaces::srv::GetTypeDescription_Response>()
{
  return "type_description_interfaces/srv/GetTypeDescription_Response";
}

template<>
struct has_fixed_size<type_description_interfaces::srv::GetTypeDescription_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<type_description_interfaces::srv::GetTypeDescription_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<type_description_interfaces::srv::GetTypeDescription_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__traits.hpp"

namespace type_description_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetTypeDescription_Event & msg,
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
  const GetTypeDescription_Event & msg,
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

inline std::string to_yaml(const GetTypeDescription_Event & msg, bool use_flow_style = false)
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

}  // namespace type_description_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use type_description_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const type_description_interfaces::srv::GetTypeDescription_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  type_description_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use type_description_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const type_description_interfaces::srv::GetTypeDescription_Event & msg)
{
  return type_description_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<type_description_interfaces::srv::GetTypeDescription_Event>()
{
  return "type_description_interfaces::srv::GetTypeDescription_Event";
}

template<>
inline const char * name<type_description_interfaces::srv::GetTypeDescription_Event>()
{
  return "type_description_interfaces/srv/GetTypeDescription_Event";
}

template<>
struct has_fixed_size<type_description_interfaces::srv::GetTypeDescription_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<type_description_interfaces::srv::GetTypeDescription_Event>
  : std::integral_constant<bool, has_bounded_size<service_msgs::msg::ServiceEventInfo>::value && has_bounded_size<type_description_interfaces::srv::GetTypeDescription_Request>::value && has_bounded_size<type_description_interfaces::srv::GetTypeDescription_Response>::value> {};

template<>
struct is_message<type_description_interfaces::srv::GetTypeDescription_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<type_description_interfaces::srv::GetTypeDescription>()
{
  return "type_description_interfaces::srv::GetTypeDescription";
}

template<>
inline const char * name<type_description_interfaces::srv::GetTypeDescription>()
{
  return "type_description_interfaces/srv/GetTypeDescription";
}

template<>
struct has_fixed_size<type_description_interfaces::srv::GetTypeDescription>
  : std::integral_constant<
    bool,
    has_fixed_size<type_description_interfaces::srv::GetTypeDescription_Request>::value &&
    has_fixed_size<type_description_interfaces::srv::GetTypeDescription_Response>::value
  >
{
};

template<>
struct has_bounded_size<type_description_interfaces::srv::GetTypeDescription>
  : std::integral_constant<
    bool,
    has_bounded_size<type_description_interfaces::srv::GetTypeDescription_Request>::value &&
    has_bounded_size<type_description_interfaces::srv::GetTypeDescription_Response>::value
  >
{
};

template<>
struct is_service<type_description_interfaces::srv::GetTypeDescription>
  : std::true_type
{
};

template<>
struct is_service_request<type_description_interfaces::srv::GetTypeDescription_Request>
  : std::true_type
{
};

template<>
struct is_service_response<type_description_interfaces::srv::GetTypeDescription_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // TYPE_DESCRIPTION_INTERFACES__SRV__DETAIL__GET_TYPE_DESCRIPTION__TRAITS_HPP_
