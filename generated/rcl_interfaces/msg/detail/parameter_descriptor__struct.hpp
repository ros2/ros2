// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rcl_interfaces:msg/ParameterDescriptor.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rcl_interfaces/msg/parameter_descriptor.hpp"


#ifndef RCL_INTERFACES__MSG__DETAIL__PARAMETER_DESCRIPTOR__STRUCT_HPP_
#define RCL_INTERFACES__MSG__DETAIL__PARAMETER_DESCRIPTOR__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'floating_point_range'
#include "rcl_interfaces/msg/detail/floating_point_range__struct.hpp"
// Member 'integer_range'
#include "rcl_interfaces/msg/detail/integer_range__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__rcl_interfaces__msg__ParameterDescriptor __attribute__((deprecated))
#else
# define DEPRECATED__rcl_interfaces__msg__ParameterDescriptor __declspec(deprecated)
#endif

namespace rcl_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ParameterDescriptor_
{
  using Type = ParameterDescriptor_<ContainerAllocator>;

  explicit ParameterDescriptor_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::DEFAULTS_ONLY == _init)
    {
      this->read_only = false;
      this->dynamic_typing = false;
    } else if (rosidl_runtime_cpp::MessageInitialization::ZERO == _init) {
      this->name = "";
      this->type = 0;
      this->description = "";
      this->additional_constraints = "";
      this->read_only = false;
      this->dynamic_typing = false;
    }
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->name = "";
      this->type = 0;
      this->description = "";
      this->additional_constraints = "";
    }
  }

  explicit ParameterDescriptor_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : name(_alloc),
    description(_alloc),
    additional_constraints(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::DEFAULTS_ONLY == _init)
    {
      this->read_only = false;
      this->dynamic_typing = false;
    } else if (rosidl_runtime_cpp::MessageInitialization::ZERO == _init) {
      this->name = "";
      this->type = 0;
      this->description = "";
      this->additional_constraints = "";
      this->read_only = false;
      this->dynamic_typing = false;
    }
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->name = "";
      this->type = 0;
      this->description = "";
      this->additional_constraints = "";
    }
  }

  // field types and members
  using _name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _name_type name;
  using _type_type =
    uint8_t;
  _type_type type;
  using _description_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _description_type description;
  using _additional_constraints_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _additional_constraints_type additional_constraints;
  using _read_only_type =
    bool;
  _read_only_type read_only;
  using _dynamic_typing_type =
    bool;
  _dynamic_typing_type dynamic_typing;
  using _floating_point_range_type =
    rosidl_runtime_cpp::BoundedVector<rcl_interfaces::msg::FloatingPointRange_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<rcl_interfaces::msg::FloatingPointRange_<ContainerAllocator>>>;
  _floating_point_range_type floating_point_range;
  using _integer_range_type =
    rosidl_runtime_cpp::BoundedVector<rcl_interfaces::msg::IntegerRange_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<rcl_interfaces::msg::IntegerRange_<ContainerAllocator>>>;
  _integer_range_type integer_range;

  // setters for named parameter idiom
  Type & set__name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->name = _arg;
    return *this;
  }
  Type & set__type(
    const uint8_t & _arg)
  {
    this->type = _arg;
    return *this;
  }
  Type & set__description(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->description = _arg;
    return *this;
  }
  Type & set__additional_constraints(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->additional_constraints = _arg;
    return *this;
  }
  Type & set__read_only(
    const bool & _arg)
  {
    this->read_only = _arg;
    return *this;
  }
  Type & set__dynamic_typing(
    const bool & _arg)
  {
    this->dynamic_typing = _arg;
    return *this;
  }
  Type & set__floating_point_range(
    const rosidl_runtime_cpp::BoundedVector<rcl_interfaces::msg::FloatingPointRange_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<rcl_interfaces::msg::FloatingPointRange_<ContainerAllocator>>> & _arg)
  {
    this->floating_point_range = _arg;
    return *this;
  }
  Type & set__integer_range(
    const rosidl_runtime_cpp::BoundedVector<rcl_interfaces::msg::IntegerRange_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<rcl_interfaces::msg::IntegerRange_<ContainerAllocator>>> & _arg)
  {
    this->integer_range = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rcl_interfaces::msg::ParameterDescriptor_<ContainerAllocator> *;
  using ConstRawPtr =
    const rcl_interfaces::msg::ParameterDescriptor_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rcl_interfaces::msg::ParameterDescriptor_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rcl_interfaces::msg::ParameterDescriptor_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rcl_interfaces::msg::ParameterDescriptor_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rcl_interfaces::msg::ParameterDescriptor_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rcl_interfaces::msg::ParameterDescriptor_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rcl_interfaces::msg::ParameterDescriptor_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rcl_interfaces::msg::ParameterDescriptor_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rcl_interfaces::msg::ParameterDescriptor_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rcl_interfaces__msg__ParameterDescriptor
    std::shared_ptr<rcl_interfaces::msg::ParameterDescriptor_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rcl_interfaces__msg__ParameterDescriptor
    std::shared_ptr<rcl_interfaces::msg::ParameterDescriptor_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ParameterDescriptor_ & other) const
  {
    if (this->name != other.name) {
      return false;
    }
    if (this->type != other.type) {
      return false;
    }
    if (this->description != other.description) {
      return false;
    }
    if (this->additional_constraints != other.additional_constraints) {
      return false;
    }
    if (this->read_only != other.read_only) {
      return false;
    }
    if (this->dynamic_typing != other.dynamic_typing) {
      return false;
    }
    if (this->floating_point_range != other.floating_point_range) {
      return false;
    }
    if (this->integer_range != other.integer_range) {
      return false;
    }
    return true;
  }
  bool operator!=(const ParameterDescriptor_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ParameterDescriptor_

// alias to use template instance with default allocator
using ParameterDescriptor =
  rcl_interfaces::msg::ParameterDescriptor_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace rcl_interfaces

#endif  // RCL_INTERFACES__MSG__DETAIL__PARAMETER_DESCRIPTOR__STRUCT_HPP_
