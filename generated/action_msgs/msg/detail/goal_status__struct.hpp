// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from action_msgs:msg/GoalStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "action_msgs/msg/goal_status.hpp"


#ifndef ACTION_MSGS__MSG__DETAIL__GOAL_STATUS__STRUCT_HPP_
#define ACTION_MSGS__MSG__DETAIL__GOAL_STATUS__STRUCT_HPP_

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
# define DEPRECATED__action_msgs__msg__GoalStatus __attribute__((deprecated))
#else
# define DEPRECATED__action_msgs__msg__GoalStatus __declspec(deprecated)
#endif

namespace action_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct GoalStatus_
{
  using Type = GoalStatus_<ContainerAllocator>;

  explicit GoalStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_info(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0;
    }
  }

  explicit GoalStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_info(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0;
    }
  }

  // field types and members
  using _goal_info_type =
    action_msgs::msg::GoalInfo_<ContainerAllocator>;
  _goal_info_type goal_info;
  using _status_type =
    int8_t;
  _status_type status;

  // setters for named parameter idiom
  Type & set__goal_info(
    const action_msgs::msg::GoalInfo_<ContainerAllocator> & _arg)
  {
    this->goal_info = _arg;
    return *this;
  }
  Type & set__status(
    const int8_t & _arg)
  {
    this->status = _arg;
    return *this;
  }

  // constant declarations
  static constexpr int8_t STATUS_UNKNOWN =
    0;
  static constexpr int8_t STATUS_ACCEPTED =
    1;
  static constexpr int8_t STATUS_EXECUTING =
    2;
  static constexpr int8_t STATUS_CANCELING =
    3;
  static constexpr int8_t STATUS_SUCCEEDED =
    4;
  static constexpr int8_t STATUS_CANCELED =
    5;
  static constexpr int8_t STATUS_ABORTED =
    6;

  // pointer types
  using RawPtr =
    action_msgs::msg::GoalStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const action_msgs::msg::GoalStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<action_msgs::msg::GoalStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<action_msgs::msg::GoalStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      action_msgs::msg::GoalStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<action_msgs::msg::GoalStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      action_msgs::msg::GoalStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<action_msgs::msg::GoalStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<action_msgs::msg::GoalStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<action_msgs::msg::GoalStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__action_msgs__msg__GoalStatus
    std::shared_ptr<action_msgs::msg::GoalStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__action_msgs__msg__GoalStatus
    std::shared_ptr<action_msgs::msg::GoalStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GoalStatus_ & other) const
  {
    if (this->goal_info != other.goal_info) {
      return false;
    }
    if (this->status != other.status) {
      return false;
    }
    return true;
  }
  bool operator!=(const GoalStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GoalStatus_

// alias to use template instance with default allocator
using GoalStatus =
  action_msgs::msg::GoalStatus_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int8_t GoalStatus_<ContainerAllocator>::STATUS_UNKNOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int8_t GoalStatus_<ContainerAllocator>::STATUS_ACCEPTED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int8_t GoalStatus_<ContainerAllocator>::STATUS_EXECUTING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int8_t GoalStatus_<ContainerAllocator>::STATUS_CANCELING;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int8_t GoalStatus_<ContainerAllocator>::STATUS_SUCCEEDED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int8_t GoalStatus_<ContainerAllocator>::STATUS_CANCELED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int8_t GoalStatus_<ContainerAllocator>::STATUS_ABORTED;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace action_msgs

#endif  // ACTION_MSGS__MSG__DETAIL__GOAL_STATUS__STRUCT_HPP_
