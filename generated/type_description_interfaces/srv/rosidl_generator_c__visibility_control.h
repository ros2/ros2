#ifndef TYPE_DESCRIPTION_INTERFACES__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_
#define TYPE_DESCRIPTION_INTERFACES__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL_H_

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define ROSIDL_GENERATOR_C_EXPORT_type_description_interfaces __attribute__ ((dllexport))
    #define ROSIDL_GENERATOR_C_IMPORT_type_description_interfaces __attribute__ ((dllimport))
  #else
    #define ROSIDL_GENERATOR_C_EXPORT_type_description_interfaces __declspec(dllexport)
    #define ROSIDL_GENERATOR_C_IMPORT_type_description_interfaces __declspec(dllimport)
  #endif
  #ifdef ROSIDL_GENERATOR_C_BUILDING_DLL_type_description_interfaces
    #define ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces ROSIDL_GENERATOR_C_EXPORT_type_description_interfaces
  #else
    #define ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces ROSIDL_GENERATOR_C_IMPORT_type_description_interfaces
  #endif
#else
  #define ROSIDL_GENERATOR_C_EXPORT_type_description_interfaces __attribute__ ((visibility("default")))
  #define ROSIDL_GENERATOR_C_IMPORT_type_description_interfaces
  #if __GNUC__ >= 4
    #define ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces __attribute__ ((visibility("default")))
  #else
    #define ROSIDL_GENERATOR_C_PUBLIC_type_description_interfaces
  #endif
#endif

#endif
