// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from action_msgs:srv/CancelGoal.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "action_msgs/srv/cancel_goal.hpp"


#ifndef ACTION_MSGS__SRV__DETAIL__CANCEL_GOAL__STRUCT_HPP_
#define ACTION_MSGS__SRV__DETAIL__CANCEL_GOAL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'goal_info'
#include "action_msgs/msg/detail/goal_info__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__action_msgs__srv__CancelGoal_Request __attribute__((deprecated))
#else
# define DEPRECATED__action_msgs__srv__CancelGoal_Request __declspec(deprecated)
#endif

namespace action_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct CancelGoal_Request_
{
  using Type = CancelGoal_Request_<ContainerAllocator>;

  explicit CancelGoal_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_info(_init)
  {
    (void)_init;
  }

  explicit CancelGoal_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_info(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_info_type =
    action_msgs::msg::GoalInfo_<ContainerAllocator>;
  _goal_info_type goal_info;

  // setters for named parameter idiom
  Type & set__goal_info(
    const action_msgs::msg::GoalInfo_<ContainerAllocator> & _arg)
  {
    this->goal_info = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    action_msgs::srv::CancelGoal_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const action_msgs::srv::CancelGoal_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<action_msgs::srv::CancelGoal_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<action_msgs::srv::CancelGoal_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      action_msgs::srv::CancelGoal_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<action_msgs::srv::CancelGoal_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      action_msgs::srv::CancelGoal_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<action_msgs::srv::CancelGoal_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<action_msgs::srv::CancelGoal_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<action_msgs::srv::CancelGoal_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__action_msgs__srv__CancelGoal_Request
    std::shared_ptr<action_msgs::srv::CancelGoal_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__action_msgs__srv__CancelGoal_Request
    std::shared_ptr<action_msgs::srv::CancelGoal_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CancelGoal_Request_ & other) const
  {
    if (this->goal_info != other.goal_info) {
      return false;
    }
    return true;
  }
  bool operator!=(const CancelGoal_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CancelGoal_Request_

// alias to use template instance with default allocator
using CancelGoal_Request =
  action_msgs::srv::CancelGoal_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace action_msgs


// Include directives for member types
// Member 'goals_canceling'
// already included above
// #include "action_msgs/msg/detail/goal_info__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__action_msgs__srv__CancelGoal_Response __attribute__((deprecated))
#else
# define DEPRECATED__action_msgs__srv__CancelGoal_Response __declspec(deprecated)
#endif

namespace action_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct CancelGoal_Response_
{
  using Type = CancelGoal_Response_<ContainerAllocator>;

  explicit CancelGoal_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->return_code = 0;
    }
  }

  explicit CancelGoal_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->return_code = 0;
    }
  }

  // field types and members
  using _return_code_type =
    int8_t;
  _return_code_type return_code;
  using _goals_canceling_type =
    std::vector<action_msgs::msg::GoalInfo_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<action_msgs::msg::GoalInfo_<ContainerAllocator>>>;
  _goals_canceling_type goals_canceling;

  // setters for named parameter idiom
  Type & set__return_code(
    const int8_t & _arg)
  {
    this->return_code = _arg;
    return *this;
  }
  Type & set__goals_canceling(
    const std::vector<action_msgs::msg::GoalInfo_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<action_msgs::msg::GoalInfo_<ContainerAllocator>>> & _arg)
  {
    this->goals_canceling = _arg;
    return *this;
  }

  // constant declarations
  static constexpr int8_t ERROR_NONE =
    0;
  static constexpr int8_t ERROR_REJECTED =
    1;
  static constexpr int8_t ERROR_UNKNOWN_GOAL_ID =
    2;
  static constexpr int8_t ERROR_GOAL_TERMINATED =
    3;

  // pointer types
  using RawPtr =
    action_msgs::srv::CancelGoal_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const action_msgs::srv::CancelGoal_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<action_msgs::srv::CancelGoal_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<action_msgs::srv::CancelGoal_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      action_msgs::srv::CancelGoal_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<action_msgs::srv::CancelGoal_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      action_msgs::srv::CancelGoal_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<action_msgs::srv::CancelGoal_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<action_msgs::srv::CancelGoal_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<action_msgs::srv::CancelGoal_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__action_msgs__srv__CancelGoal_Response
    std::shared_ptr<action_msgs::srv::CancelGoal_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__action_msgs__srv__CancelGoal_Response
    std::shared_ptr<action_msgs::srv::CancelGoal_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CancelGoal_Response_ & other) const
  {
    if (this->return_code != other.return_code) {
      return false;
    }
    if (this->goals_canceling != other.goals_canceling) {
      return false;
    }
    return true;
  }
  bool operator!=(const CancelGoal_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CancelGoal_Response_

// alias to use template instance with default allocator
using CancelGoal_Response =
  action_msgs::srv::CancelGoal_Response_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int8_t CancelGoal_Response_<ContainerAllocator>::ERROR_NONE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int8_t CancelGoal_Response_<ContainerAllocator>::ERROR_REJECTED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int8_t CancelGoal_Response_<ContainerAllocator>::ERROR_UNKNOWN_GOAL_ID;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int8_t CancelGoal_Response_<ContainerAllocator>::ERROR_GOAL_TERMINATED;
#endif  // __cplusplus < 201703L

}  // namespace srv

}  // namespace action_msgs


// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__action_msgs__srv__CancelGoal_Event __attribute__((deprecated))
#else
# define DEPRECATED__action_msgs__srv__CancelGoal_Event __declspec(deprecated)
#endif

namespace action_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct CancelGoal_Event_
{
  using Type = CancelGoal_Event_<ContainerAllocator>;

  explicit CancelGoal_Event_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_init)
  {
    (void)_init;
  }

  explicit CancelGoal_Event_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _info_type =
    service_msgs::msg::ServiceEventInfo_<ContainerAllocator>;
  _info_type info;
  using _request_type =
    rosidl_runtime_cpp::BoundedVector<action_msgs::srv::CancelGoal_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<action_msgs::srv::CancelGoal_Request_<ContainerAllocator>>>;
  _request_type request;
  using _response_type =
    rosidl_runtime_cpp::BoundedVector<action_msgs::srv::CancelGoal_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<action_msgs::srv::CancelGoal_Response_<ContainerAllocator>>>;
  _response_type response;

  // setters for named parameter idiom
  Type & set__info(
    const service_msgs::msg::ServiceEventInfo_<ContainerAllocator> & _arg)
  {
    this->info = _arg;
    return *this;
  }
  Type & set__request(
    const rosidl_runtime_cpp::BoundedVector<action_msgs::srv::CancelGoal_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<action_msgs::srv::CancelGoal_Request_<ContainerAllocator>>> & _arg)
  {
    this->request = _arg;
    return *this;
  }
  Type & set__response(
    const rosidl_runtime_cpp::BoundedVector<action_msgs::srv::CancelGoal_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<action_msgs::srv::CancelGoal_Response_<ContainerAllocator>>> & _arg)
  {
    this->response = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    action_msgs::srv::CancelGoal_Event_<ContainerAllocator> *;
  using ConstRawPtr =
    const action_msgs::srv::CancelGoal_Event_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<action_msgs::srv::CancelGoal_Event_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<action_msgs::srv::CancelGoal_Event_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      action_msgs::srv::CancelGoal_Event_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<action_msgs::srv::CancelGoal_Event_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      action_msgs::srv::CancelGoal_Event_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<action_msgs::srv::CancelGoal_Event_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<action_msgs::srv::CancelGoal_Event_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<action_msgs::srv::CancelGoal_Event_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__action_msgs__srv__CancelGoal_Event
    std::shared_ptr<action_msgs::srv::CancelGoal_Event_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__action_msgs__srv__CancelGoal_Event
    std::shared_ptr<action_msgs::srv::CancelGoal_Event_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CancelGoal_Event_ & other) const
  {
    if (this->info != other.info) {
      return false;
    }
    if (this->request != other.request) {
      return false;
    }
    if (this->response != other.response) {
      return false;
    }
    return true;
  }
  bool operator!=(const CancelGoal_Event_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CancelGoal_Event_

// alias to use template instance with default allocator
using CancelGoal_Event =
  action_msgs::srv::CancelGoal_Event_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace action_msgs

namespace action_msgs
{

namespace srv
{

struct CancelGoal
{
  using Request = action_msgs::srv::CancelGoal_Request;
  using Response = action_msgs::srv::CancelGoal_Response;
  using Event = action_msgs::srv::CancelGoal_Event;
};

}  // namespace srv

}  // namespace action_msgs

#endif  // ACTION_MSGS__SRV__DETAIL__CANCEL_GOAL__STRUCT_HPP_
