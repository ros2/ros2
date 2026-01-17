#ifndef UNIQUE_IDENTIFIER_MSGS__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_
#define UNIQUE_IDENTIFIER_MSGS__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define ROSIDL_GENERATOR_C_EXPORT_unique_identifier_msgs __attribute__ ((dllexport))
    #define ROSIDL_GENERATOR_C_IMPORT_unique_identifier_msgs __attribute__ ((dllimport))
  #else
    #define ROSIDL_GENERATOR_C_EXPORT_unique_identifier_msgs __declspec(dllexport)
    #define ROSIDL_GENERATOR_C_IMPORT_unique_identifier_msgs __declspec(dllimport)
  #endif
  #ifdef ROSIDL_GENERATOR_C_BUILDING_DLL_unique_identifier_msgs
    #define ROSIDL_GENERATOR_C_PUBLIC_unique_identifier_msgs ROSIDL_GENERATOR_C_EXPORT_unique_identifier_msgs
  #else
    #define ROSIDL_GENERATOR_C_PUBLIC_unique_identifier_msgs ROSIDL_GENERATOR_C_IMPORT_unique_identifier_msgs
  #endif
#else
  #define ROSIDL_GENERATOR_C_EXPORT_unique_identifier_msgs __attribute__ ((visibility("default")))
  #define ROSIDL_GENERATOR_C_IMPORT_unique_identifier_msgs
  #if __GNUC__ >= 4
    #define ROSIDL_GENERATOR_C_PUBLIC_unique_identifier_msgs __attribute__ ((visibility("default")))
  #else
    #define ROSIDL_GENERATOR_C_PUBLIC_unique_identifier_msgs
  #endif
#endif

#endif
