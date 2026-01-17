// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// tf2_msgs/srv/FrameGraph_Response type

#ifndef TF2_MSGS__SRV__FRAMEGRAPH_RESPONSE_H_
#define TF2_MSGS__SRV__FRAMEGRAPH_RESPONSE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "tf2_msgs/msg/rosidl_generator_c__visibility_control.h"
#include "rosidl_runtime_c/string.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tf2_msgs__srv__FrameGraph_Response
{
  rosidl_runtime_c__String frame_yaml;
} tf2_msgs__srv__FrameGraph_Response;

typedef struct tf2_msgs__srv__FrameGraph_Response__Sequence
{
  tf2_msgs__srv__FrameGraph_Response * data;
  size_t size;
  size_t capacity;
} tf2_msgs__srv__FrameGraph_Response__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
bool tf2_msgs__srv__FrameGraph_Response__init(tf2_msgs__srv__FrameGraph_Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
void tf2_msgs__srv__FrameGraph_Response__fini(tf2_msgs__srv__FrameGraph_Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
tf2_msgs__srv__FrameGraph_Response * tf2_msgs__srv__FrameGraph_Response__create(void);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
void tf2_msgs__srv__FrameGraph_Response__destroy(tf2_msgs__srv__FrameGraph_Response * msg);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
bool tf2_msgs__srv__FrameGraph_Response__Sequence__init(
  tf2_msgs__srv__FrameGraph_Response__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_tf2_msgs
void tf2_msgs__srv__FrameGraph_Response__Sequence__fini(
  tf2_msgs__srv__FrameGraph_Response__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // TF2_MSGS__SRV__FRAMEGRAPH_RESPONSE_H_
