// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from action_msgs:msg/GoalInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "action_msgs/msg/goal_info.hpp"


#ifndef ACTION_MSGS__MSG__DETAIL__GOAL_INFO__STRUCT_HPP_
#define ACTION_MSGS__MSG__DETAIL__GOAL_INFO__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__action_msgs__msg__GoalInfo __attribute__((deprecated))
#else
# define DEPRECATED__action_msgs__msg__GoalInfo __declspec(deprecated)
#endif

namespace action_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct GoalInfo_
{
  using Type = GoalInfo_<ContainerAllocator>;

  explicit GoalInfo_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init),
    stamp(_init)
  {
    (void)_init;
  }

  explicit GoalInfo_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init),
    stamp(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;
  using _stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _stamp_type stamp;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }
  Type & set__stamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->stamp = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    action_msgs::msg::GoalInfo_<ContainerAllocator> *;
  using ConstRawPtr =
    const action_msgs::msg::GoalInfo_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<action_msgs::msg::GoalInfo_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<action_msgs::msg::GoalInfo_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      action_msgs::msg::GoalInfo_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<action_msgs::msg::GoalInfo_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      action_msgs::msg::GoalInfo_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<action_msgs::msg::GoalInfo_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<action_msgs::msg::GoalInfo_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<action_msgs::msg::GoalInfo_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__action_msgs__msg__GoalInfo
    std::shared_ptr<action_msgs::msg::GoalInfo_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__action_msgs__msg__GoalInfo
    std::shared_ptr<action_msgs::msg::GoalInfo_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GoalInfo_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    if (this->stamp != other.stamp) {
      return false;
    }
    return true;
  }
  bool operator!=(const GoalInfo_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GoalInfo_

// alias to use template instance with default allocator
using GoalInfo =
  action_msgs::msg::GoalInfo_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace action_msgs

#endif  // ACTION_MSGS__MSG__DETAIL__GOAL_INFO__STRUCT_HPP_
