// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/BatteryState message type

#ifndef SENSOR_MSGS__MSG__BATTERYSTATE_H_
#define SENSOR_MSGS__MSG__BATTERYSTATE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "sensor_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "rosidl_runtime_c/primitives_sequence.h"
#include "rosidl_runtime_c/string.h"
#include "std_msgs/msg/header.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
  sensor_msgs__msg__BatteryState__POWER_SUPPLY_STATUS_UNKNOWN = 0,
  sensor_msgs__msg__BatteryState__POWER_SUPPLY_STATUS_CHARGING = 1,
  sensor_msgs__msg__BatteryState__POWER_SUPPLY_STATUS_DISCHARGING = 2,
  sensor_msgs__msg__BatteryState__POWER_SUPPLY_STATUS_NOT_CHARGING = 3,
  sensor_msgs__msg__BatteryState__POWER_SUPPLY_STATUS_FULL = 4,
  sensor_msgs__msg__BatteryState__POWER_SUPPLY_HEALTH_UNKNOWN = 0,
  sensor_msgs__msg__BatteryState__POWER_SUPPLY_HEALTH_GOOD = 1,
  sensor_msgs__msg__BatteryState__POWER_SUPPLY_HEALTH_OVERHEAT = 2,
  sensor_msgs__msg__BatteryState__POWER_SUPPLY_HEALTH_DEAD = 3,
  sensor_msgs__msg__BatteryState__POWER_SUPPLY_HEALTH_OVERVOLTAGE = 4,
  sensor_msgs__msg__BatteryState__POWER_SUPPLY_HEALTH_UNSPEC_FAILURE = 5,
  sensor_msgs__msg__BatteryState__POWER_SUPPLY_HEALTH_COLD = 6,
  sensor_msgs__msg__BatteryState__POWER_SUPPLY_HEALTH_WATCHDOG_TIMER_EXPIRE = 7,
  sensor_msgs__msg__BatteryState__POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE = 8,
  sensor_msgs__msg__BatteryState__POWER_SUPPLY_TECHNOLOGY_UNKNOWN = 0,
  sensor_msgs__msg__BatteryState__POWER_SUPPLY_TECHNOLOGY_NIMH = 1,
  sensor_msgs__msg__BatteryState__POWER_SUPPLY_TECHNOLOGY_LION = 2,
  sensor_msgs__msg__BatteryState__POWER_SUPPLY_TECHNOLOGY_LIPO = 3,
  sensor_msgs__msg__BatteryState__POWER_SUPPLY_TECHNOLOGY_LIFE = 4,
  sensor_msgs__msg__BatteryState__POWER_SUPPLY_TECHNOLOGY_NICD = 5,
  sensor_msgs__msg__BatteryState__POWER_SUPPLY_TECHNOLOGY_LIMN = 6
}};

typedef struct sensor_msgs__msg__BatteryState
{
  std_msgs__msg__Header header;
  float voltage;
  float temperature;
  float current;
  float charge;
  float capacity;
  float design_capacity;
  float percentage;
  uint8_t power_supply_status;
  uint8_t power_supply_health;
  uint8_t power_supply_technology;
  bool present;
  rosidl_runtime_c__float__Sequence cell_voltage;
  rosidl_runtime_c__float__Sequence cell_temperature;
  rosidl_runtime_c__String location;
  rosidl_runtime_c__String serial_number;
} sensor_msgs__msg__BatteryState;

typedef struct sensor_msgs__msg__BatteryState__Sequence
{
  sensor_msgs__msg__BatteryState * data;
  size_t size;
  size_t capacity;
} sensor_msgs__msg__BatteryState__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__BatteryState__init(sensor_msgs__msg__BatteryState * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__BatteryState__fini(sensor_msgs__msg__BatteryState * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
sensor_msgs__msg__BatteryState * sensor_msgs__msg__BatteryState__create(void);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__BatteryState__destroy(sensor_msgs__msg__BatteryState * msg);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
bool sensor_msgs__msg__BatteryState__Sequence__init(
  sensor_msgs__msg__BatteryState__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_sensor_msgs
void sensor_msgs__msg__BatteryState__Sequence__fini(
  sensor_msgs__msg__BatteryState__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // SENSOR_MSGS__MSG__BATTERYSTATE_H_
