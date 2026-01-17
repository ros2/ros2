// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from statistics_msgs:msg/StatisticDataPoint.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "statistics_msgs/msg/statistic_data_point.hpp"


#ifndef STATISTICS_MSGS__MSG__DETAIL__STATISTIC_DATA_POINT__STRUCT_HPP_
#define STATISTICS_MSGS__MSG__DETAIL__STATISTIC_DATA_POINT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__statistics_msgs__msg__StatisticDataPoint __attribute__((deprecated))
#else
# define DEPRECATED__statistics_msgs__msg__StatisticDataPoint __declspec(deprecated)
#endif

namespace statistics_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct StatisticDataPoint_
{
  using Type = StatisticDataPoint_<ContainerAllocator>;

  explicit StatisticDataPoint_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->data_type = 0;
      this->data = 0.0;
    }
  }

  explicit StatisticDataPoint_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->data_type = 0;
      this->data = 0.0;
    }
  }

  // field types and members
  using _data_type_type =
    uint8_t;
  _data_type_type data_type;
  using _data_type =
    double;
  _data_type data;

  // setters for named parameter idiom
  Type & set__data_type(
    const uint8_t & _arg)
  {
    this->data_type = _arg;
    return *this;
  }
  Type & set__data(
    const double & _arg)
  {
    this->data = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    statistics_msgs::msg::StatisticDataPoint_<ContainerAllocator> *;
  using ConstRawPtr =
    const statistics_msgs::msg::StatisticDataPoint_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<statistics_msgs::msg::StatisticDataPoint_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<statistics_msgs::msg::StatisticDataPoint_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      statistics_msgs::msg::StatisticDataPoint_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<statistics_msgs::msg::StatisticDataPoint_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      statistics_msgs::msg::StatisticDataPoint_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<statistics_msgs::msg::StatisticDataPoint_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<statistics_msgs::msg::StatisticDataPoint_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<statistics_msgs::msg::StatisticDataPoint_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__statistics_msgs__msg__StatisticDataPoint
    std::shared_ptr<statistics_msgs::msg::StatisticDataPoint_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__statistics_msgs__msg__StatisticDataPoint
    std::shared_ptr<statistics_msgs::msg::StatisticDataPoint_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const StatisticDataPoint_ & other) const
  {
    if (this->data_type != other.data_type) {
      return false;
    }
    if (this->data != other.data) {
      return false;
    }
    return true;
  }
  bool operator!=(const StatisticDataPoint_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct StatisticDataPoint_

// alias to use template instance with default allocator
using StatisticDataPoint =
  statistics_msgs::msg::StatisticDataPoint_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace statistics_msgs

#endif  // STATISTICS_MSGS__MSG__DETAIL__STATISTIC_DATA_POINT__STRUCT_HPP_
