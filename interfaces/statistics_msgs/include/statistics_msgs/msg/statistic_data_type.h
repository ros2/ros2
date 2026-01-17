// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// statistics_msgs/msg/StatisticDataType type

#ifndef STATISTICS_MSGS__MSG__STATISTIC_DATA_TYPE_H_
#define STATISTICS_MSGS__MSG__STATISTIC_DATA_TYPE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "statistics_msgs/msg/rosidl_generator_c__visibility_control.h"

#ifdef __cplusplus
extern "C" {
#endif

// Statistic data type constants
#define STATISTICS_MSGS__MSG__STATISTIC_DATA_TYPE__STATISTICS_DATA_TYPE_UNINITIALIZED ((uint8_t)0)
#define STATISTICS_MSGS__MSG__STATISTIC_DATA_TYPE__STATISTICS_DATA_TYPE_AVERAGE ((uint8_t)1)
#define STATISTICS_MSGS__MSG__STATISTIC_DATA_TYPE__STATISTICS_DATA_TYPE_MINIMUM ((uint8_t)2)
#define STATISTICS_MSGS__MSG__STATISTIC_DATA_TYPE__STATISTICS_DATA_TYPE_MAXIMUM ((uint8_t)3)
#define STATISTICS_MSGS__MSG__STATISTIC_DATA_TYPE__STATISTICS_DATA_TYPE_STDDEV ((uint8_t)4)
#define STATISTICS_MSGS__MSG__STATISTIC_DATA_TYPE__STATISTICS_DATA_TYPE_SAMPLE_COUNT ((uint8_t)5)

/// Constants-only message for statistic data types
typedef struct statistics_msgs__msg__StatisticDataType
{
  uint8_t structure_needs_at_least_one_member;
} statistics_msgs__msg__StatisticDataType;

typedef struct statistics_msgs__msg__StatisticDataType__Sequence
{
  statistics_msgs__msg__StatisticDataType * data;
  size_t size;
  size_t capacity;
} statistics_msgs__msg__StatisticDataType__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_statistics_msgs
bool statistics_msgs__msg__StatisticDataType__init(statistics_msgs__msg__StatisticDataType * msg);

ROSIDL_GENERATOR_C_PUBLIC_statistics_msgs
void statistics_msgs__msg__StatisticDataType__fini(statistics_msgs__msg__StatisticDataType * msg);

ROSIDL_GENERATOR_C_PUBLIC_statistics_msgs
statistics_msgs__msg__StatisticDataType * statistics_msgs__msg__StatisticDataType__create(void);

ROSIDL_GENERATOR_C_PUBLIC_statistics_msgs
void statistics_msgs__msg__StatisticDataType__destroy(statistics_msgs__msg__StatisticDataType * msg);

ROSIDL_GENERATOR_C_PUBLIC_statistics_msgs
bool statistics_msgs__msg__StatisticDataType__Sequence__init(
  statistics_msgs__msg__StatisticDataType__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_statistics_msgs
void statistics_msgs__msg__StatisticDataType__Sequence__fini(
  statistics_msgs__msg__StatisticDataType__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // STATISTICS_MSGS__MSG__STATISTIC_DATA_TYPE_H_
