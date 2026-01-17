// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from action_msgs:srv/CancelGoal.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "action_msgs/srv/cancel_goal.hpp"


#ifndef ACTION_MSGS__SRV__DETAIL__CANCEL_GOAL__TRAITS_HPP_
#define ACTION_MSGS__SRV__DETAIL__CANCEL_GOAL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "action_msgs/srv/detail/cancel_goal__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'goal_info'
#include "action_msgs/msg/detail/goal_info__traits.hpp"

namespace action_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const CancelGoal_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_info
  {
    out << "goal_info: ";
    to_flow_style_yaml(msg.goal_info, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const CancelGoal_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_info
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_info:\n";
    to_block_style_yaml(msg.goal_info, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const CancelGoal_Request & msg, bool use_flow_style = false)
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

}  // namespace action_msgs

namespace rosidl_generator_traits
{

[[deprecated("use action_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const action_msgs::srv::CancelGoal_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  action_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use action_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const action_msgs::srv::CancelGoal_Request & msg)
{
  return action_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<action_msgs::srv::CancelGoal_Request>()
{
  return "action_msgs::srv::CancelGoal_Request";
}

template<>
inline const char * name<action_msgs::srv::CancelGoal_Request>()
{
  return "action_msgs/srv/CancelGoal_Request";
}

template<>
struct has_fixed_size<action_msgs::srv::CancelGoal_Request>
  : std::integral_constant<bool, has_fixed_size<action_msgs::msg::GoalInfo>::value> {};

template<>
struct has_bounded_size<action_msgs::srv::CancelGoal_Request>
  : std::integral_constant<bool, has_bounded_size<action_msgs::msg::GoalInfo>::value> {};

template<>
struct is_message<action_msgs::srv::CancelGoal_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goals_canceling'
// already included above
// #include "action_msgs/msg/detail/goal_info__traits.hpp"

namespace action_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const CancelGoal_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: return_code
  {
    out << "return_code: ";
    rosidl_generator_traits::value_to_yaml(msg.return_code, out);
    out << ", ";
  }

  // member: goals_canceling
  {
    if (msg.goals_canceling.size() == 0) {
      out << "goals_canceling: []";
    } else {
      out << "goals_canceling: [";
      size_t pending_items = msg.goals_canceling.size();
      for (auto item : msg.goals_canceling) {
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
  const CancelGoal_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: return_code
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "return_code: ";
    rosidl_generator_traits::value_to_yaml(msg.return_code, out);
    out << "\n";
  }

  // member: goals_canceling
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.goals_canceling.size() == 0) {
      out << "goals_canceling: []\n";
    } else {
      out << "goals_canceling:\n";
      for (auto item : msg.goals_canceling) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const CancelGoal_Response & msg, bool use_flow_style = false)
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

}  // namespace action_msgs

namespace rosidl_generator_traits
{

[[deprecated("use action_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const action_msgs::srv::CancelGoal_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  action_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use action_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const action_msgs::srv::CancelGoal_Response & msg)
{
  return action_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<action_msgs::srv::CancelGoal_Response>()
{
  return "action_msgs::srv::CancelGoal_Response";
}

template<>
inline const char * name<action_msgs::srv::CancelGoal_Response>()
{
  return "action_msgs/srv/CancelGoal_Response";
}

template<>
struct has_fixed_size<action_msgs::srv::CancelGoal_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<action_msgs::srv::CancelGoal_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<action_msgs::srv::CancelGoal_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__traits.hpp"

namespace action_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const CancelGoal_Event & msg,
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
  const CancelGoal_Event & msg,
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

inline std::string to_yaml(const CancelGoal_Event & msg, bool use_flow_style = false)
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

}  // namespace action_msgs

namespace rosidl_generator_traits
{

[[deprecated("use action_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const action_msgs::srv::CancelGoal_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  action_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use action_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const action_msgs::srv::CancelGoal_Event & msg)
{
  return action_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<action_msgs::srv::CancelGoal_Event>()
{
  return "action_msgs::srv::CancelGoal_Event";
}

template<>
inline const char * name<action_msgs::srv::CancelGoal_Event>()
{
  return "action_msgs/srv/CancelGoal_Event";
}

template<>
struct has_fixed_size<action_msgs::srv::CancelGoal_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<action_msgs::srv::CancelGoal_Event>
  : std::integral_constant<bool, has_bounded_size<action_msgs::srv::CancelGoal_Request>::value && has_bounded_size<action_msgs::srv::CancelGoal_Response>::value && has_bounded_size<service_msgs::msg::ServiceEventInfo>::value> {};

template<>
struct is_message<action_msgs::srv::CancelGoal_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<action_msgs::srv::CancelGoal>()
{
  return "action_msgs::srv::CancelGoal";
}

template<>
inline const char * name<action_msgs::srv::CancelGoal>()
{
  return "action_msgs/srv/CancelGoal";
}

template<>
struct has_fixed_size<action_msgs::srv::CancelGoal>
  : std::integral_constant<
    bool,
    has_fixed_size<action_msgs::srv::CancelGoal_Request>::value &&
    has_fixed_size<action_msgs::srv::CancelGoal_Response>::value
  >
{
};

template<>
struct has_bounded_size<action_msgs::srv::CancelGoal>
  : std::integral_constant<
    bool,
    has_bounded_size<action_msgs::srv::CancelGoal_Request>::value &&
    has_bounded_size<action_msgs::srv::CancelGoal_Response>::value
  >
{
};

template<>
struct is_service<action_msgs::srv::CancelGoal>
  : std::true_type
{
};

template<>
struct is_service_request<action_msgs::srv::CancelGoal_Request>
  : std::true_type
{
};

template<>
struct is_service_response<action_msgs::srv::CancelGoal_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // ACTION_MSGS__SRV__DETAIL__CANCEL_GOAL__TRAITS_HPP_
