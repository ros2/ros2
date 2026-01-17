// Copyright (c) 2024 ROS2 OpenHarmony Port Project
// type_description_interfaces visibility control

#ifndef TYPE_DESCRIPTION_INTERFACES__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_
#define TYPE_DESCRIPTION_INTERFACES__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32)
  #if defined(ROSIDL_GENERATOR_C_BUILDING_DLL_type_description_interfaces)
    #define ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces __declspec(dllexport)
  #else
    #define ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces __declspec(dllimport)
  #endif
#else
  #define ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
}
#endif

#endif  // TYPE_DESCRIPTION_INTERFACES__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_
