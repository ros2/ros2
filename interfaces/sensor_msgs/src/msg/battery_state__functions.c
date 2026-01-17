// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// sensor_msgs/msg/BatteryState functions implementation

#include <stdbool.h>
#include <stdlib.h>

#include "sensor_msgs/msg/battery_state.h"
#include "rcutils/allocator.h"
#include "rosidl_runtime_c/string_functions.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool sensor_msgs__msg__BatteryState__init(sensor_msgs__msg__BatteryState * msg)
{
  if (!msg) { return false; }
  if (!std_msgs__msg__Header__init(&msg->header)) { return false; }
  msg->voltage = 0.0;
  msg->temperature = 0.0;
  msg->current = 0.0;
  msg->charge = 0.0;
  msg->capacity = 0.0;
  msg->design_capacity = 0.0;
  msg->percentage = 0.0;
  msg->power_supply_status = 0;
  msg->power_supply_health = 0;
  msg->power_supply_technology = 0;
  msg->present = false;
  if (!rosidl_runtime_c__float__Sequence__init(&msg->cell_voltage, 0)) { return false; }
  if (!rosidl_runtime_c__float__Sequence__init(&msg->cell_temperature, 0)) { return false; }
  if (!rosidl_runtime_c__String__init(&msg->location)) { return false; }
  if (!rosidl_runtime_c__String__init(&msg->serial_number)) { return false; }
  return true;
}

void sensor_msgs__msg__BatteryState__fini(sensor_msgs__msg__BatteryState * msg)
{
  if (!msg) { return; }
  std_msgs__msg__Header__fini(&msg->header);
  rosidl_runtime_c__float__Sequence__fini(&msg->cell_voltage);
  rosidl_runtime_c__float__Sequence__fini(&msg->cell_temperature);
  rosidl_runtime_c__String__fini(&msg->location);
  rosidl_runtime_c__String__fini(&msg->serial_number);
}

sensor_msgs__msg__BatteryState * sensor_msgs__msg__BatteryState__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sensor_msgs__msg__BatteryState * msg =
    (sensor_msgs__msg__BatteryState *)allocator.allocate(
      sizeof(sensor_msgs__msg__BatteryState), allocator.state);
  if (!msg) { return NULL; }
  if (!sensor_msgs__msg__BatteryState__init(msg)) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void sensor_msgs__msg__BatteryState__destroy(sensor_msgs__msg__BatteryState * msg)
{
  if (!msg) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sensor_msgs__msg__BatteryState__fini(msg);
  allocator.deallocate(msg, allocator.state);
}

bool sensor_msgs__msg__BatteryState__Sequence__init(
  sensor_msgs__msg__BatteryState__Sequence * array, size_t size)
{
  if (!array) { return false; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (size) {
    array->data = (sensor_msgs__msg__BatteryState *)allocator.zero_allocate(
      size, sizeof(sensor_msgs__msg__BatteryState), allocator.state);
    if (!array->data) { return false; }
    for (size_t i = 0; i < size; ++i) {
      if (!sensor_msgs__msg__BatteryState__init(&array->data[i])) {
        for (size_t j = 0; j < i; ++j) {
          sensor_msgs__msg__BatteryState__fini(&array->data[j]);
        }
        allocator.deallocate(array->data, allocator.state);
        return false;
      }
    }
  } else {
    array->data = NULL;
  }
  array->size = size;
  array->capacity = size;
  return true;
}

void sensor_msgs__msg__BatteryState__Sequence__fini(
  sensor_msgs__msg__BatteryState__Sequence * array)
{
  if (!array) { return; }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array->data) {
    for (size_t i = 0; i < array->size; ++i) {
      sensor_msgs__msg__BatteryState__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  }
}
