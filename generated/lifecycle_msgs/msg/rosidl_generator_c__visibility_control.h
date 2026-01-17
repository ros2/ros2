#ifndef LIFECYCLE_MSGS__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_
#define LIFECYCLE_MSGS__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define ROSIDL_GENERATOR_C_EXPORT_lifecycle_msgs __attribute__ ((dllexport))
    #define ROSIDL_GENERATOR_C_IMPORT_lifecycle_msgs __attribute__ ((dllimport))
  #else
    #define ROSIDL_GENERATOR_C_EXPORT_lifecycle_msgs __declspec(dllexport)
    #define ROSIDL_GENERATOR_C_IMPORT_lifecycle_msgs __declspec(dllimport)
  #endif
  #ifdef ROSIDL_GENERATOR_C_BUILDING_DLL_lifecycle_msgs
    #define ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs ROSIDL_GENERATOR_C_EXPORT_lifecycle_msgs
  #else
    #define ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs ROSIDL_GENERATOR_C_IMPORT_lifecycle_msgs
  #endif
#else
  #define ROSIDL_GENERATOR_C_EXPORT_lifecycle_msgs __attribute__ ((visibility("default")))
  #define ROSIDL_GENERATOR_C_IMPORT_lifecycle_msgs
  #if __GNUC__ >= 4
    #define ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs __attribute__ ((visibility("default")))
  #else
    #define ROSIDL_GENERATOR_C_PUBLIC_lifecycle_msgs
  #endif
#endif

#endif
