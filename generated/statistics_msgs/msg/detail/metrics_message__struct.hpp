// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from statistics_msgs:msg/MetricsMessage.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "statistics_msgs/msg/metrics_message.hpp"


#ifndef STATISTICS_MSGS__MSG__DETAIL__METRICS_MESSAGE__STRUCT_HPP_
#define STATISTICS_MSGS__MSG__DETAIL__METRICS_MESSAGE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'window_start'
// Member 'window_stop'
#include "builtin_interfaces/msg/detail/time__struct.hpp"
// Member 'statistics'
#include "statistics_msgs/msg/detail/statistic_data_point__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__statistics_msgs__msg__MetricsMessage __attribute__((deprecated))
#else
# define DEPRECATED__statistics_msgs__msg__MetricsMessage __declspec(deprecated)
#endif

namespace statistics_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MetricsMessage_
{
  using Type = MetricsMessage_<ContainerAllocator>;

  explicit MetricsMessage_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : window_start(_init),
    window_stop(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->measurement_source_name = "";
      this->metrics_source = "";
      this->unit = "";
    }
  }

  explicit MetricsMessage_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : measurement_source_name(_alloc),
    metrics_source(_alloc),
    unit(_alloc),
    window_start(_alloc, _init),
    window_stop(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->measurement_source_name = "";
      this->metrics_source = "";
      this->unit = "";
    }
  }

  // field types and members
  using _measurement_source_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _measurement_source_name_type measurement_source_name;
  using _metrics_source_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _metrics_source_type metrics_source;
  using _unit_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _unit_type unit;
  using _window_start_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _window_start_type window_start;
  using _window_stop_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _window_stop_type window_stop;
  using _statistics_type =
    std::vector<statistics_msgs::msg::StatisticDataPoint_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<statistics_msgs::msg::StatisticDataPoint_<ContainerAllocator>>>;
  _statistics_type statistics;

  // setters for named parameter idiom
  Type & set__measurement_source_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->measurement_source_name = _arg;
    return *this;
  }
  Type & set__metrics_source(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->metrics_source = _arg;
    return *this;
  }
  Type & set__unit(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->unit = _arg;
    return *this;
  }
  Type & set__window_start(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->window_start = _arg;
    return *this;
  }
  Type & set__window_stop(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->window_stop = _arg;
    return *this;
  }
  Type & set__statistics(
    const std::vector<statistics_msgs::msg::StatisticDataPoint_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<statistics_msgs::msg::StatisticDataPoint_<ContainerAllocator>>> & _arg)
  {
    this->statistics = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    statistics_msgs::msg::MetricsMessage_<ContainerAllocator> *;
  using ConstRawPtr =
    const statistics_msgs::msg::MetricsMessage_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<statistics_msgs::msg::MetricsMessage_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<statistics_msgs::msg::MetricsMessage_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      statistics_msgs::msg::MetricsMessage_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<statistics_msgs::msg::MetricsMessage_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      statistics_msgs::msg::MetricsMessage_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<statistics_msgs::msg::MetricsMessage_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<statistics_msgs::msg::MetricsMessage_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<statistics_msgs::msg::MetricsMessage_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__statistics_msgs__msg__MetricsMessage
    std::shared_ptr<statistics_msgs::msg::MetricsMessage_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__statistics_msgs__msg__MetricsMessage
    std::shared_ptr<statistics_msgs::msg::MetricsMessage_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MetricsMessage_ & other) const
  {
    if (this->measurement_source_name != other.measurement_source_name) {
      return false;
    }
    if (this->metrics_source != other.metrics_source) {
      return false;
    }
    if (this->unit != other.unit) {
      return false;
    }
    if (this->window_start != other.window_start) {
      return false;
    }
    if (this->window_stop != other.window_stop) {
      return false;
    }
    if (this->statistics != other.statistics) {
      return false;
    }
    return true;
  }
  bool operator!=(const MetricsMessage_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MetricsMessage_

// alias to use template instance with default allocator
using MetricsMessage =
  statistics_msgs::msg::MetricsMessage_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace statistics_msgs

#endif  // STATISTICS_MSGS__MSG__DETAIL__METRICS_MESSAGE__STRUCT_HPP_
