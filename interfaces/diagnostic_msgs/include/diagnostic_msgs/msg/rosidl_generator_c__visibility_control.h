// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// diagnostic_msgs visibility control

#ifndef DIAGNOSTIC_MSGS__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_
#define DIAGNOSTIC_MSGS__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32)
  #if defined(ROSIDL_GENERATOR_C_BUILDING_DLL_diagnostic_msgs)
    #define ROSIDL_GENERATOR_C_PUBLIC_diagnostic_msgs __declspec(dllexport)
  #else
    #define ROSIDL_GENERATOR_C_PUBLIC_diagnostic_msgs __declspec(dllimport)
  #endif
#else
  #define ROSIDL_GENERATOR_C_PUBLIC_diagnostic_msgs __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
}
#endif

#endif  // DIAGNOSTIC_MSGS__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_
