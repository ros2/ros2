// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rmw_dds_common:msg/ParticipantEntitiesInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rmw_dds_common/msg/participant_entities_info.hpp"


#ifndef RMW_DDS_COMMON__MSG__DETAIL__PARTICIPANT_ENTITIES_INFO__STRUCT_HPP_
#define RMW_DDS_COMMON__MSG__DETAIL__PARTICIPANT_ENTITIES_INFO__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'gid'
#include "rmw_dds_common/msg/detail/gid__struct.hpp"
// Member 'node_entities_info_seq'
#include "rmw_dds_common/msg/detail/node_entities_info__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__rmw_dds_common__msg__ParticipantEntitiesInfo __attribute__((deprecated))
#else
# define DEPRECATED__rmw_dds_common__msg__ParticipantEntitiesInfo __declspec(deprecated)
#endif

namespace rmw_dds_common
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ParticipantEntitiesInfo_
{
  using Type = ParticipantEntitiesInfo_<ContainerAllocator>;

  explicit ParticipantEntitiesInfo_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : gid(_init)
  {
    (void)_init;
  }

  explicit ParticipantEntitiesInfo_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : gid(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _gid_type =
    rmw_dds_common::msg::Gid_<ContainerAllocator>;
  _gid_type gid;
  using _node_entities_info_seq_type =
    std::vector<rmw_dds_common::msg::NodeEntitiesInfo_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<rmw_dds_common::msg::NodeEntitiesInfo_<ContainerAllocator>>>;
  _node_entities_info_seq_type node_entities_info_seq;

  // setters for named parameter idiom
  Type & set__gid(
    const rmw_dds_common::msg::Gid_<ContainerAllocator> & _arg)
  {
    this->gid = _arg;
    return *this;
  }
  Type & set__node_entities_info_seq(
    const std::vector<rmw_dds_common::msg::NodeEntitiesInfo_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<rmw_dds_common::msg::NodeEntitiesInfo_<ContainerAllocator>>> & _arg)
  {
    this->node_entities_info_seq = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rmw_dds_common::msg::ParticipantEntitiesInfo_<ContainerAllocator> *;
  using ConstRawPtr =
    const rmw_dds_common::msg::ParticipantEntitiesInfo_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rmw_dds_common::msg::ParticipantEntitiesInfo_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rmw_dds_common::msg::ParticipantEntitiesInfo_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rmw_dds_common::msg::ParticipantEntitiesInfo_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rmw_dds_common::msg::ParticipantEntitiesInfo_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rmw_dds_common::msg::ParticipantEntitiesInfo_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rmw_dds_common::msg::ParticipantEntitiesInfo_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rmw_dds_common::msg::ParticipantEntitiesInfo_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rmw_dds_common::msg::ParticipantEntitiesInfo_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rmw_dds_common__msg__ParticipantEntitiesInfo
    std::shared_ptr<rmw_dds_common::msg::ParticipantEntitiesInfo_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rmw_dds_common__msg__ParticipantEntitiesInfo
    std::shared_ptr<rmw_dds_common::msg::ParticipantEntitiesInfo_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ParticipantEntitiesInfo_ & other) const
  {
    if (this->gid != other.gid) {
      return false;
    }
    if (this->node_entities_info_seq != other.node_entities_info_seq) {
      return false;
    }
    return true;
  }
  bool operator!=(const ParticipantEntitiesInfo_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ParticipantEntitiesInfo_

// alias to use template instance with default allocator
using ParticipantEntitiesInfo =
  rmw_dds_common::msg::ParticipantEntitiesInfo_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace rmw_dds_common

#endif  // RMW_DDS_COMMON__MSG__DETAIL__PARTICIPANT_ENTITIES_INFO__STRUCT_HPP_
