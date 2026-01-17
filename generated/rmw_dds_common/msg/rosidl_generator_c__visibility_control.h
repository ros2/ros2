#ifndef RMW_DDS_COMMON__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_
#define RMW_DDS_COMMON__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define ROSIDL_GENERATOR_C_EXPORT_rmw_dds_common __attribute__ ((dllexport))
    #define ROSIDL_GENERATOR_C_IMPORT_rmw_dds_common __attribute__ ((dllimport))
  #else
    #define ROSIDL_GENERATOR_C_EXPORT_rmw_dds_common __declspec(dllexport)
    #define ROSIDL_GENERATOR_C_IMPORT_rmw_dds_common __declspec(dllimport)
  #endif
  #ifdef ROSIDL_GENERATOR_C_BUILDING_DLL_rmw_dds_common
    #define ROSIDL_GENERATOR_C_PUBLIC_rmw_dds_common ROSIDL_GENERATOR_C_EXPORT_rmw_dds_common
  #else
    #define ROSIDL_GENERATOR_C_PUBLIC_rmw_dds_common ROSIDL_GENERATOR_C_IMPORT_rmw_dds_common
  #endif
#else
  #define ROSIDL_GENERATOR_C_EXPORT_rmw_dds_common __attribute__ ((visibility("default")))
  #define ROSIDL_GENERATOR_C_IMPORT_rmw_dds_common
  #if __GNUC__ >= 4
    #define ROSIDL_GENERATOR_C_PUBLIC_rmw_dds_common __attribute__ ((visibility("default")))
  #else
    #define ROSIDL_GENERATOR_C_PUBLIC_rmw_dds_common
  #endif
#endif

#endif
