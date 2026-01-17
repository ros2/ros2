// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rmw_dds_common:msg/ParticipantEntitiesInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rmw_dds_common/msg/participant_entities_info.h"


#ifndef RMW_DDS_COMMON__MSG__DETAIL__PARTICIPANT_ENTITIES_INFO__STRUCT_H_
#define RMW_DDS_COMMON__MSG__DETAIL__PARTICIPANT_ENTITIES_INFO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'gid'
#include "rmw_dds_common/msg/detail/gid__struct.h"
// Member 'node_entities_info_seq'
#include "rmw_dds_common/msg/detail/node_entities_info__struct.h"

/// Struct defined in msg/ParticipantEntitiesInfo in the package rmw_dds_common.
typedef struct rmw_dds_common__msg__ParticipantEntitiesInfo
{
  rmw_dds_common__msg__Gid gid;
  rmw_dds_common__msg__NodeEntitiesInfo__Sequence node_entities_info_seq;
} rmw_dds_common__msg__ParticipantEntitiesInfo;

// Struct for a sequence of rmw_dds_common__msg__ParticipantEntitiesInfo.
typedef struct rmw_dds_common__msg__ParticipantEntitiesInfo__Sequence
{
  rmw_dds_common__msg__ParticipantEntitiesInfo * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rmw_dds_common__msg__ParticipantEntitiesInfo__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RMW_DDS_COMMON__MSG__DETAIL__PARTICIPANT_ENTITIES_INFO__STRUCT_H_
