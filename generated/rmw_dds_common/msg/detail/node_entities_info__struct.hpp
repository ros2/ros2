// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rmw_dds_common:msg/NodeEntitiesInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rmw_dds_common/msg/node_entities_info.hpp"


#ifndef RMW_DDS_COMMON__MSG__DETAIL__NODE_ENTITIES_INFO__STRUCT_HPP_
#define RMW_DDS_COMMON__MSG__DETAIL__NODE_ENTITIES_INFO__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'reader_gid_seq'
// Member 'writer_gid_seq'
#include "rmw_dds_common/msg/detail/gid__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__rmw_dds_common__msg__NodeEntitiesInfo __attribute__((deprecated))
#else
# define DEPRECATED__rmw_dds_common__msg__NodeEntitiesInfo __declspec(deprecated)
#endif

namespace rmw_dds_common
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct NodeEntitiesInfo_
{
  using Type = NodeEntitiesInfo_<ContainerAllocator>;

  explicit NodeEntitiesInfo_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->node_namespace = "";
      this->node_name = "";
    }
  }

  explicit NodeEntitiesInfo_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : node_namespace(_alloc),
    node_name(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->node_namespace = "";
      this->node_name = "";
    }
  }

  // field types and members
  using _node_namespace_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _node_namespace_type node_namespace;
  using _node_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _node_name_type node_name;
  using _reader_gid_seq_type =
    std::vector<rmw_dds_common::msg::Gid_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<rmw_dds_common::msg::Gid_<ContainerAllocator>>>;
  _reader_gid_seq_type reader_gid_seq;
  using _writer_gid_seq_type =
    std::vector<rmw_dds_common::msg::Gid_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<rmw_dds_common::msg::Gid_<ContainerAllocator>>>;
  _writer_gid_seq_type writer_gid_seq;

  // setters for named parameter idiom
  Type & set__node_namespace(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->node_namespace = _arg;
    return *this;
  }
  Type & set__node_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->node_name = _arg;
    return *this;
  }
  Type & set__reader_gid_seq(
    const std::vector<rmw_dds_common::msg::Gid_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<rmw_dds_common::msg::Gid_<ContainerAllocator>>> & _arg)
  {
    this->reader_gid_seq = _arg;
    return *this;
  }
  Type & set__writer_gid_seq(
    const std::vector<rmw_dds_common::msg::Gid_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<rmw_dds_common::msg::Gid_<ContainerAllocator>>> & _arg)
  {
    this->writer_gid_seq = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rmw_dds_common::msg::NodeEntitiesInfo_<ContainerAllocator> *;
  using ConstRawPtr =
    const rmw_dds_common::msg::NodeEntitiesInfo_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rmw_dds_common::msg::NodeEntitiesInfo_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rmw_dds_common::msg::NodeEntitiesInfo_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rmw_dds_common::msg::NodeEntitiesInfo_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rmw_dds_common::msg::NodeEntitiesInfo_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rmw_dds_common::msg::NodeEntitiesInfo_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rmw_dds_common::msg::NodeEntitiesInfo_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rmw_dds_common::msg::NodeEntitiesInfo_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rmw_dds_common::msg::NodeEntitiesInfo_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rmw_dds_common__msg__NodeEntitiesInfo
    std::shared_ptr<rmw_dds_common::msg::NodeEntitiesInfo_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rmw_dds_common__msg__NodeEntitiesInfo
    std::shared_ptr<rmw_dds_common::msg::NodeEntitiesInfo_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const NodeEntitiesInfo_ & other) const
  {
    if (this->node_namespace != other.node_namespace) {
      return false;
    }
    if (this->node_name != other.node_name) {
      return false;
    }
    if (this->reader_gid_seq != other.reader_gid_seq) {
      return false;
    }
    if (this->writer_gid_seq != other.writer_gid_seq) {
      return false;
    }
    return true;
  }
  bool operator!=(const NodeEntitiesInfo_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct NodeEntitiesInfo_

// alias to use template instance with default allocator
using NodeEntitiesInfo =
  rmw_dds_common::msg::NodeEntitiesInfo_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace rmw_dds_common

#endif  // RMW_DDS_COMMON__MSG__DETAIL__NODE_ENTITIES_INFO__STRUCT_HPP_
