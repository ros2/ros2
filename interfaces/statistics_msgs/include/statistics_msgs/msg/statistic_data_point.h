// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// statistics_msgs/msg/StatisticDataPoint type

#ifndef STATISTICS_MSGS__MSG__STATISTIC_DATA_POINT_H_
#define STATISTICS_MSGS__MSG__STATISTIC_DATA_POINT_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "statistics_msgs/msg/rosidl_generator_c__visibility_control.h"

#ifdef __cplusplus
extern "C" {
#endif

/// A single statistic data point
typedef struct statistics_msgs__msg__StatisticDataPoint
{
  /// The type of statistic (see StatisticDataType constants)
  uint8_t data_type;
  /// The value of this statistic
  double data;
} statistics_msgs__msg__StatisticDataPoint;

typedef struct statistics_msgs__msg__StatisticDataPoint__Sequence
{
  statistics_msgs__msg__StatisticDataPoint * data;
  size_t size;
  size_t capacity;
} statistics_msgs__msg__StatisticDataPoint__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_statistics_msgs
bool statistics_msgs__msg__StatisticDataPoint__init(statistics_msgs__msg__StatisticDataPoint * msg);

ROSIDL_GENERATOR_C_PUBLIC_statistics_msgs
void statistics_msgs__msg__StatisticDataPoint__fini(statistics_msgs__msg__StatisticDataPoint * msg);

ROSIDL_GENERATOR_C_PUBLIC_statistics_msgs
statistics_msgs__msg__StatisticDataPoint * statistics_msgs__msg__StatisticDataPoint__create(void);

ROSIDL_GENERATOR_C_PUBLIC_statistics_msgs
void statistics_msgs__msg__StatisticDataPoint__destroy(statistics_msgs__msg__StatisticDataPoint * msg);

ROSIDL_GENERATOR_C_PUBLIC_statistics_msgs
bool statistics_msgs__msg__StatisticDataPoint__Sequence__init(
  statistics_msgs__msg__StatisticDataPoint__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_statistics_msgs
void statistics_msgs__msg__StatisticDataPoint__Sequence__fini(
  statistics_msgs__msg__StatisticDataPoint__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // STATISTICS_MSGS__MSG__STATISTIC_DATA_POINT_H_
