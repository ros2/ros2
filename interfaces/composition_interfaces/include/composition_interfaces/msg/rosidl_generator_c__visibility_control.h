// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// composition_interfaces visibility control

#ifndef COMPOSITION_INTERFACES__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_
#define COMPOSITION_INTERFACES__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32)
  #if defined(ROSIDL_GENERATOR_C_BUILDING_DLL_composition_interfaces)
    #define ROSIDL_GENERATOR_C_PUBLIC_composition_interfaces __declspec(dllexport)
  #else
    #define ROSIDL_GENERATOR_C_PUBLIC_composition_interfaces __declspec(dllimport)
  #endif
#else
  #define ROSIDL_GENERATOR_C_PUBLIC_composition_interfaces __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
}
#endif

#endif  // COMPOSITION_INTERFACES__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_
