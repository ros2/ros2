// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// composition_interfaces/srv/UnloadNode type

#ifndef COMPOSITION_INTERFACES__SRV__UNLOAD_NODE_H_
#define COMPOSITION_INTERFACES__SRV__UNLOAD_NODE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "composition_interfaces/msg/rosidl_generator_c__visibility_control.h"

#ifdef __cplusplus
extern "C" {
#endif

// =============================================================================
// UnloadNode Request
// =============================================================================

/// Request to unload a component node
typedef struct composition_interfaces__srv__UnloadNode__Request
{
  /// Unique identifier of the component to unload
  uint64_t unique_id;
} composition_interfaces__srv__UnloadNode__Request;

typedef struct composition_interfaces__srv__UnloadNode__Request__Sequence
{
  composition_interfaces__srv__UnloadNode__Request * data;
  size_t size;
  size_t capacity;
} composition_interfaces__srv__UnloadNode__Request__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_composition_interfaces
bool composition_interfaces__srv__UnloadNode__Request__init(
  composition_interfaces__srv__UnloadNode__Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_composition_interfaces
void composition_interfaces__srv__UnloadNode__Request__fini(
  composition_interfaces__srv__UnloadNode__Request * msg);

ROSIDL_GENERATOR_C_PUBLIC_composition_interfaces
composition_interfaces__srv__UnloadNode__Request *
composition_interfaces__srv__UnloadNode__Request__create(void);

ROSIDL_GENERATOR_C_PUBLIC_composition_interfaces
void composition_interfaces__srv__UnloadNode__Request__destroy(
  composition_interfaces__srv__UnloadNode__Request * msg);

// =============================================================================
// UnloadNode Response
// =============================================================================

/// Response from unloading a component node
typedef struct composition_interfaces__srv__UnloadNode__Response
{
  /// Whether the component was successfully unloaded
  bool success;
  /// Human-readable error message if not successful
  rosidl_runtime_c__String error_message;
} composition_interfaces__srv__UnloadNode__Response;

typedef struct composition_interfaces__srv__UnloadNode__Response__Sequence
{
  composition_interfaces__srv__UnloadNode__Response * data;
  size_t size;
  size_t capacity;
} composition_interfaces__srv__UnloadNode__Response__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_composition_interfaces
bool composition_interfaces__srv__UnloadNode__Response__init(
  composition_interfaces__srv__UnloadNode__Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_composition_interfaces
void composition_interfaces__srv__UnloadNode__Response__fini(
  composition_interfaces__srv__UnloadNode__Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_composition_interfaces
composition_interfaces__srv__UnloadNode__Response *
composition_interfaces__srv__UnloadNode__Response__create(void);

ROSIDL_GENERATOR_C_PUBLIC_composition_interfaces
void composition_interfaces__srv__UnloadNode__Response__destroy(
  composition_interfaces__srv__UnloadNode__Response * msg);

#ifdef __cplusplus
}
#endif

#endif  // COMPOSITION_INTERFACES__SRV__UNLOAD_NODE_H_
