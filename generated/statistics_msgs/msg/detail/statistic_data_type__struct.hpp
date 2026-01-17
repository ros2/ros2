// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from statistics_msgs:msg/StatisticDataType.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "statistics_msgs/msg/statistic_data_type.hpp"


#ifndef STATISTICS_MSGS__MSG__DETAIL__STATISTIC_DATA_TYPE__STRUCT_HPP_
#define STATISTICS_MSGS__MSG__DETAIL__STATISTIC_DATA_TYPE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__statistics_msgs__msg__StatisticDataType __attribute__((deprecated))
#else
# define DEPRECATED__statistics_msgs__msg__StatisticDataType __declspec(deprecated)
#endif

namespace statistics_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct StatisticDataType_
{
  using Type = StatisticDataType_<ContainerAllocator>;

  explicit StatisticDataType_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  explicit StatisticDataType_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  // field types and members
  using _structure_needs_at_least_one_member_type =
    uint8_t;
  _structure_needs_at_least_one_member_type structure_needs_at_least_one_member;


  // constant declarations
  static constexpr uint8_t STATISTICS_DATA_TYPE_UNINITIALIZED =
    0u;
  static constexpr uint8_t STATISTICS_DATA_TYPE_AVERAGE =
    1u;
  static constexpr uint8_t STATISTICS_DATA_TYPE_MINIMUM =
    2u;
  static constexpr uint8_t STATISTICS_DATA_TYPE_MAXIMUM =
    3u;
  static constexpr uint8_t STATISTICS_DATA_TYPE_STDDEV =
    4u;
  static constexpr uint8_t STATISTICS_DATA_TYPE_SAMPLE_COUNT =
    5u;

  // pointer types
  using RawPtr =
    statistics_msgs::msg::StatisticDataType_<ContainerAllocator> *;
  using ConstRawPtr =
    const statistics_msgs::msg::StatisticDataType_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<statistics_msgs::msg::StatisticDataType_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<statistics_msgs::msg::StatisticDataType_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      statistics_msgs::msg::StatisticDataType_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<statistics_msgs::msg::StatisticDataType_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      statistics_msgs::msg::StatisticDataType_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<statistics_msgs::msg::StatisticDataType_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<statistics_msgs::msg::StatisticDataType_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<statistics_msgs::msg::StatisticDataType_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__statistics_msgs__msg__StatisticDataType
    std::shared_ptr<statistics_msgs::msg::StatisticDataType_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__statistics_msgs__msg__StatisticDataType
    std::shared_ptr<statistics_msgs::msg::StatisticDataType_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const StatisticDataType_ & other) const
  {
    if (this->structure_needs_at_least_one_member != other.structure_needs_at_least_one_member) {
      return false;
    }
    return true;
  }
  bool operator!=(const StatisticDataType_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct StatisticDataType_

// alias to use template instance with default allocator
using StatisticDataType =
  statistics_msgs::msg::StatisticDataType_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t StatisticDataType_<ContainerAllocator>::STATISTICS_DATA_TYPE_UNINITIALIZED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t StatisticDataType_<ContainerAllocator>::STATISTICS_DATA_TYPE_AVERAGE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t StatisticDataType_<ContainerAllocator>::STATISTICS_DATA_TYPE_MINIMUM;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t StatisticDataType_<ContainerAllocator>::STATISTICS_DATA_TYPE_MAXIMUM;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t StatisticDataType_<ContainerAllocator>::STATISTICS_DATA_TYPE_STDDEV;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t StatisticDataType_<ContainerAllocator>::STATISTICS_DATA_TYPE_SAMPLE_COUNT;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace statistics_msgs

#endif  // STATISTICS_MSGS__MSG__DETAIL__STATISTIC_DATA_TYPE__STRUCT_HPP_
