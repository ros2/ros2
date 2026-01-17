// Minimal mock for rosidl_typesupport_introspection_c/identifier.h
#ifndef ROSIDL_TYPESUPPORT_INTROSPECTION_C__IDENTIFIER_H_
#define ROSIDL_TYPESUPPORT_INTROSPECTION_C__IDENTIFIER_H_

#ifdef __cplusplus
extern "C" {
#endif

// Typesupport identifier for introspection
#define ROSIDL_TYPESUPPORT_INTROSPECTION_C__IDENTIFIER_VALUE "rosidl_typesupport_introspection_c"

// Expose as both a function and a direct constant for compatibility
// Many codebases use it as a constant string
static const char * const rosidl_typesupport_introspection_c__identifier =
    ROSIDL_TYPESUPPORT_INTROSPECTION_C__IDENTIFIER_VALUE;

#ifdef __cplusplus
}
#endif

#endif  // ROSIDL_TYPESUPPORT_INTROSPECTION_C__IDENTIFIER_H_
