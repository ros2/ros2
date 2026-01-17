// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from statistics_msgs:msg/StatisticDataPoint.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "statistics_msgs/msg/detail/statistic_data_point__rosidl_typesupport_introspection_c.h"
#include "statistics_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "statistics_msgs/msg/detail/statistic_data_point__functions.h"
#include "statistics_msgs/msg/detail/statistic_data_point__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void statistics_msgs__msg__StatisticDataPoint__rosidl_typesupport_introspection_c__StatisticDataPoint_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  statistics_msgs__msg__StatisticDataPoint__init(message_memory);
}

void statistics_msgs__msg__StatisticDataPoint__rosidl_typesupport_introspection_c__StatisticDataPoint_fini_function(void * message_memory)
{
  statistics_msgs__msg__StatisticDataPoint__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember statistics_msgs__msg__StatisticDataPoint__rosidl_typesupport_introspection_c__StatisticDataPoint_message_member_array[2] = {
  {
    "data_type",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(statistics_msgs__msg__StatisticDataPoint, data_type),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "data",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(statistics_msgs__msg__StatisticDataPoint, data),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers statistics_msgs__msg__StatisticDataPoint__rosidl_typesupport_introspection_c__StatisticDataPoint_message_members = {
  "statistics_msgs__msg",  // message namespace
  "StatisticDataPoint",  // message name
  2,  // number of fields
  sizeof(statistics_msgs__msg__StatisticDataPoint),
  false,  // has_any_key_member_
  statistics_msgs__msg__StatisticDataPoint__rosidl_typesupport_introspection_c__StatisticDataPoint_message_member_array,  // message members
  statistics_msgs__msg__StatisticDataPoint__rosidl_typesupport_introspection_c__StatisticDataPoint_init_function,  // function to initialize message memory (memory has to be allocated)
  statistics_msgs__msg__StatisticDataPoint__rosidl_typesupport_introspection_c__StatisticDataPoint_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t statistics_msgs__msg__StatisticDataPoint__rosidl_typesupport_introspection_c__StatisticDataPoint_message_type_support_handle = {
  0,
  &statistics_msgs__msg__StatisticDataPoint__rosidl_typesupport_introspection_c__StatisticDataPoint_message_members,
  get_message_typesupport_handle_function,
  &statistics_msgs__msg__StatisticDataPoint__get_type_hash,
  &statistics_msgs__msg__StatisticDataPoint__get_type_description,
  &statistics_msgs__msg__StatisticDataPoint__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_statistics_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, statistics_msgs, msg, StatisticDataPoint)() {
  if (!statistics_msgs__msg__StatisticDataPoint__rosidl_typesupport_introspection_c__StatisticDataPoint_message_type_support_handle.typesupport_identifier) {
    statistics_msgs__msg__StatisticDataPoint__rosidl_typesupport_introspection_c__StatisticDataPoint_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &statistics_msgs__msg__StatisticDataPoint__rosidl_typesupport_introspection_c__StatisticDataPoint_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
