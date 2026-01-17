// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// composition_interfaces/srv/LoadNode type

#ifndef COMPOSITION_INTERFACES__SRV__LOAD_NODE_H_
#define COMPOSITION_INTERFACES__SRV__LOAD_NODE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "composition_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "rcl_interfaces/msg/parameter.h"

#ifdef __cplusplus
extern "C" {
#endif

// =============================================================================
// LoadNode Request
// =============================================================================

/// Request to load a component node
typedef struct composition_interfaces__srv__LoadNode__Request
{
  /// The package containing the component
  rosidl_runtime_c__String package_name;
  /// The plugin name (class name) of the component
  rosidl_runtime_c__String plugin_name;
  /// The desired node name (optional, empty for default)
  rosidl_runtime_c__String node_name;
  /// The desired node namespace (optional, empty for default)
  rosidl_runtime_c__String node_namespace;
  /// Log level for the node
  uint8_t log_level;
  /// Remapping rules (from:=to format)
  rosidl_runtime_c__String__Sequence remap_rules;
  /// Parameters to set on the node
  rcl_interfaces__msg__Parameter__Sequence parameters;
  /// Extra arguments for the component
  rosidl_runtime_c__String__Sequence extra_arguments;
} composition_interfaces__srv__LoadNode__Request;

typedef struct composition_interfaces__srv__LoadNode__Request__Sequence
{
  composition_interfaces__srv__LoadNode__Request * data;
  size_t size;
  size_t capacity;
} composition_interfaces__srv__LoadNode__Request__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_composition_interfaces
bool composition_interfaces__srv__LoadNode__Request__init(
  composition_interfaces__srv__LoadNode__Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_composition_interfaces
void composition_interfaces__srv__LoadNode__Request__fini(
  composition_interfaces__srv__LoadNode__Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_composition_interfaces
composition_interfaces__srv__LoadNode__Request *
composition_interfaces__srv__LoadNode__Request__create(void);

ROSIDL_GENERATOR_C_PUBLIC_composition_interfaces
void composition_interfaces__srv__LoadNode__Request__destroy(
  composition_interfaces__srv__LoadNode__Request * msg);

// =============================================================================
// LoadNode Response
// =============================================================================

/// Response from loading a component node
typedef struct composition_interfaces__srv__LoadNode__Response
{
  /// Whether the component was successfully loaded
  bool success;
  /// Human-readable error message if not successful
  rosidl_runtime_c__String error_message;
  /// The full node name of the loaded component
  rosidl_runtime_c__String full_node_name;
  /// Unique identifier for this loaded component
  uint64_t unique_id;
} composition_interfaces__srv__LoadNode__Response;

typedef struct composition_interfaces__srv__LoadNode__Response__Sequence
{
  composition_interfaces__srv__LoadNode__Response * data;
  size_t size;
  size_t capacity;
} composition_interfaces__srv__LoadNode__Response__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_composition_interfaces
bool composition_interfaces__srv__LoadNode__Response__init(
  composition_interfaces__srv__LoadNode__Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_composition_interfaces
void composition_interfaces__srv__LoadNode__Response__fini(
  composition_interfaces__srv__LoadNode__Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_composition_interfaces
composition_interfaces__srv__LoadNode__Response *
composition_interfaces__srv__LoadNode__Response__create(void);

ROSIDL_GENERATOR_C_PUBLIC_composition_interfaces
void composition_interfaces__srv__LoadNode__Response__destroy(
  composition_interfaces__srv__LoadNode__Response * msg);

#ifdef __cplusplus
}
#endif

#endif  // COMPOSITION_INTERFACES__SRV__LOAD_NODE_H_
