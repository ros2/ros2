// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// statistics_msgs/msg/MetricsMessage type

#ifndef STATISTICS_MSGS__MSG__METRICS_MESSAGE_H_
#define STATISTICS_MSGS__MSG__METRICS_MESSAGE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "statistics_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "builtin_interfaces/msg/time.h"
#include "statistics_msgs/msg/statistic_data_point.h"

#ifdef __cplusplus
extern "C" {
#endif

/// General metrics message for system monitoring
typedef struct statistics_msgs__msg__MetricsMessage
{
  /// The name of the measurement (e.g., "topic_statistics")
  rosidl_runtime_c__String measurement_source_name;
  /// The source of the metric (e.g., node name)
  rosidl_runtime_c__String metrics_source;
  /// The unit of measurement
  rosidl_runtime_c__String unit;
  /// Start of the measurement window
  builtin_interfaces__msg__Time window_start;
  /// End of the measurement window
  builtin_interfaces__msg__Time window_stop;
  /// Array of statistic data points
  statistics_msgs__msg__StatisticDataPoint__Sequence statistics;
} statistics_msgs__msg__MetricsMessage;

typedef struct statistics_msgs__msg__MetricsMessage__Sequence
{
  statistics_msgs__msg__MetricsMessage * data;
  size_t size;
  size_t capacity;
} statistics_msgs__msg__MetricsMessage__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_statistics_msgs
bool statistics_msgs__msg__MetricsMessage__init(statistics_msgs__msg__MetricsMessage * msg);

ROSIDL_GENERATOR_C_PUBLIC_statistics_msgs
void statistics_msgs__msg__MetricsMessage__fini(statistics_msgs__msg__MetricsMessage * msg);

ROSIDL_GENERATOR_C_PUBLIC_statistics_msgs
statistics_msgs__msg__MetricsMessage * statistics_msgs__msg__MetricsMessage__create(void);

ROSIDL_GENERATOR_C_PUBLIC_statistics_msgs
void statistics_msgs__msg__MetricsMessage__destroy(statistics_msgs__msg__MetricsMessage * msg);

ROSIDL_GENERATOR_C_PUBLIC_statistics_msgs
bool statistics_msgs__msg__MetricsMessage__Sequence__init(
  statistics_msgs__msg__MetricsMessage__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_statistics_msgs
void statistics_msgs__msg__MetricsMessage__Sequence__fini(
  statistics_msgs__msg__MetricsMessage__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // STATISTICS_MSGS__MSG__METRICS_MESSAGE_H_
