// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// stereo_msgs/msg/DisparityImage type

#ifndef STEREO_MSGS__MSG__DISPARITY_IMAGE_H_
#define STEREO_MSGS__MSG__DISPARITY_IMAGE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "stereo_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "std_msgs/msg/header.h"
#include "sensor_msgs/msg/image.h"
#include "sensor_msgs/msg/region_of_interest.h"

#ifdef __cplusplus
extern "C" {
#endif

/// Separate header for DisiparityImage of image and target stamps
/// to accommodate dynamics of sensor and target interactions
///
/// Disparity image representation for stereo vision processing
/// The disparity d = x_l - x_r represents the difference in
/// the x coordinate of the same 3D point observed from the left
/// and right cameras.
///
/// The relationship between disparity and depth is:
///   Z = f * T / d
/// where f is focal length, T is baseline, and d is disparity.
typedef struct stereo_msgs__msg__DisparityImage
{
  /// Stamp and frame_id
  std_msgs__msg__Header header;

  /// Floating point disparity image. The depth to disparity
  /// relation is: d = f*T/Z, where T is the baseline between
  /// the cameras and Z is the depth.
  sensor_msgs__msg__Image image;

  /// Focal length, pixels
  float f;

  /// Baseline, world units
  float t;

  /// Subpixel interpolation factor used in computing the
  /// disparity. The search algorithm does 1/delta_d refinement.
  /// Standard Intel and/or Point Grey stereo cameras have delta_d = 16.
  float delta_d;

  /// Smallest allowed disparity value, in pixels
  float min_disparity;

  /// Largest allowed disparity value, in pixels
  float max_disparity;

  /// Region of the disparity image containing useful data
  sensor_msgs__msg__RegionOfInterest valid_window;
} stereo_msgs__msg__DisparityImage;

typedef struct stereo_msgs__msg__DisparityImage__Sequence
{
  stereo_msgs__msg__DisparityImage * data;
  size_t size;
  size_t capacity;
} stereo_msgs__msg__DisparityImage__Sequence;

ROSIDL_GENERATOR_C_PUBLIC_stereo_msgs
bool stereo_msgs__msg__DisparityImage__init(stereo_msgs__msg__DisparityImage * msg);

ROSIDL_GENERATOR_C_PUBLIC_stereo_msgs
void stereo_msgs__msg__DisparityImage__fini(stereo_msgs__msg__DisparityImage * msg);

ROSIDL_GENERATOR_C_PUBLIC_stereo_msgs
stereo_msgs__msg__DisparityImage * stereo_msgs__msg__DisparityImage__create(void);

ROSIDL_GENERATOR_C_PUBLIC_stereo_msgs
void stereo_msgs__msg__DisparityImage__destroy(stereo_msgs__msg__DisparityImage * msg);

ROSIDL_GENERATOR_C_PUBLIC_stereo_msgs
bool stereo_msgs__msg__DisparityImage__Sequence__init(
  stereo_msgs__msg__DisparityImage__Sequence * array, size_t size);

ROSIDL_GENERATOR_C_PUBLIC_stereo_msgs
void stereo_msgs__msg__DisparityImage__Sequence__fini(
  stereo_msgs__msg__DisparityImage__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // STEREO_MSGS__MSG__DISPARITY_IMAGE_H_
