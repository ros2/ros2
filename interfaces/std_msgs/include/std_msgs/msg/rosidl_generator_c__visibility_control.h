// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// Visibility control for std_msgs

#ifndef STD_MSGS__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_
#define STD_MSGS__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32)
  #if defined(ROSIDL_GENERATOR_C_BUILDING_DLL_std_msgs)
    #define ROSIDL_GENERATOR_C_PUBLIC_std_msgs __declspec(dllexport)
  #else
    #define ROSIDL_GENERATOR_C_PUBLIC_std_msgs __declspec(dllimport)
  #endif
#else
  #define ROSIDL_GENERATOR_C_PUBLIC_std_msgs __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
}
#endif

#endif  // STD_MSGS__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_
