// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rmw_dds_common:msg/NodeEntitiesInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rmw_dds_common/msg/node_entities_info.h"


#ifndef RMW_DDS_COMMON__MSG__DETAIL__NODE_ENTITIES_INFO__STRUCT_H_
#define RMW_DDS_COMMON__MSG__DETAIL__NODE_ENTITIES_INFO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'node_namespace'
// Member 'node_name'
#include "rosidl_runtime_c/string.h"
// Member 'reader_gid_seq'
// Member 'writer_gid_seq'
#include "rmw_dds_common/msg/detail/gid__struct.h"

// constants for array fields with an upper bound
// node_namespace
enum
{
  rmw_dds_common__msg__NodeEntitiesInfo__node_namespace__MAX_STRING_SIZE = 256
};
// node_name
enum
{
  rmw_dds_common__msg__NodeEntitiesInfo__node_name__MAX_STRING_SIZE = 256
};

/// Struct defined in msg/NodeEntitiesInfo in the package rmw_dds_common.
typedef struct rmw_dds_common__msg__NodeEntitiesInfo
{
  rosidl_runtime_c__String node_namespace;
  rosidl_runtime_c__String node_name;
  rmw_dds_common__msg__Gid__Sequence reader_gid_seq;
  rmw_dds_common__msg__Gid__Sequence writer_gid_seq;
} rmw_dds_common__msg__NodeEntitiesInfo;

// Struct for a sequence of rmw_dds_common__msg__NodeEntitiesInfo.
typedef struct rmw_dds_common__msg__NodeEntitiesInfo__Sequence
{
  rmw_dds_common__msg__NodeEntitiesInfo * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rmw_dds_common__msg__NodeEntitiesInfo__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RMW_DDS_COMMON__MSG__DETAIL__NODE_ENTITIES_INFO__STRUCT_H_
