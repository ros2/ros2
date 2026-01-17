// Minimal mock for rosidl_runtime_c/primitives_sequence.h
#ifndef ROSIDL_RUNTIME_C__PRIMITIVES_SEQUENCE_H_
#define ROSIDL_RUNTIME_C__PRIMITIVES_SEQUENCE_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

// Macro to define sequence types for primitive types
#define ROSIDL_RUNTIME_C__DECLARE_PRIMITIVE_SEQUENCE(STRUCT_NAME, TYPE) \
typedef struct rosidl_runtime_c__##STRUCT_NAME##__Sequence { \
    TYPE * data; \
    size_t size; \
    size_t capacity; \
} rosidl_runtime_c__##STRUCT_NAME##__Sequence;

// Declare sequence types for all primitive types
ROSIDL_RUNTIME_C__DECLARE_PRIMITIVE_SEQUENCE(float, float)
ROSIDL_RUNTIME_C__DECLARE_PRIMITIVE_SEQUENCE(double, double)
ROSIDL_RUNTIME_C__DECLARE_PRIMITIVE_SEQUENCE(long_double, long double)
ROSIDL_RUNTIME_C__DECLARE_PRIMITIVE_SEQUENCE(char, signed char)
ROSIDL_RUNTIME_C__DECLARE_PRIMITIVE_SEQUENCE(wchar, uint16_t)
ROSIDL_RUNTIME_C__DECLARE_PRIMITIVE_SEQUENCE(boolean, bool)
ROSIDL_RUNTIME_C__DECLARE_PRIMITIVE_SEQUENCE(octet, uint8_t)
ROSIDL_RUNTIME_C__DECLARE_PRIMITIVE_SEQUENCE(uint8, uint8_t)
ROSIDL_RUNTIME_C__DECLARE_PRIMITIVE_SEQUENCE(int8, int8_t)
ROSIDL_RUNTIME_C__DECLARE_PRIMITIVE_SEQUENCE(uint16, uint16_t)
ROSIDL_RUNTIME_C__DECLARE_PRIMITIVE_SEQUENCE(int16, int16_t)
ROSIDL_RUNTIME_C__DECLARE_PRIMITIVE_SEQUENCE(uint32, uint32_t)
ROSIDL_RUNTIME_C__DECLARE_PRIMITIVE_SEQUENCE(int32, int32_t)
ROSIDL_RUNTIME_C__DECLARE_PRIMITIVE_SEQUENCE(uint64, uint64_t)
ROSIDL_RUNTIME_C__DECLARE_PRIMITIVE_SEQUENCE(int64, int64_t)

// Initialize a sequence
#define ROSIDL_RUNTIME_C__DEFINE_PRIMITIVE_SEQUENCE_INIT(STRUCT_NAME, TYPE) \
static inline bool \
rosidl_runtime_c__##STRUCT_NAME##__Sequence__init( \
    rosidl_runtime_c__##STRUCT_NAME##__Sequence * sequence, size_t size) \
{ \
    if (!sequence) { return false; } \
    if (size == 0) { \
        sequence->data = NULL; \
        sequence->size = 0; \
        sequence->capacity = 0; \
        return true; \
    } \
    sequence->data = (TYPE *)calloc(size, sizeof(TYPE)); \
    if (!sequence->data) { return false; } \
    sequence->size = size; \
    sequence->capacity = size; \
    return true; \
}

// Finalize a sequence
#define ROSIDL_RUNTIME_C__DEFINE_PRIMITIVE_SEQUENCE_FINI(STRUCT_NAME) \
static inline void \
rosidl_runtime_c__##STRUCT_NAME##__Sequence__fini( \
    rosidl_runtime_c__##STRUCT_NAME##__Sequence * sequence) \
{ \
    if (sequence && sequence->data) { \
        free(sequence->data); \
        sequence->data = NULL; \
        sequence->size = 0; \
        sequence->capacity = 0; \
    } \
}

// Define init/fini functions for all primitive sequences
ROSIDL_RUNTIME_C__DEFINE_PRIMITIVE_SEQUENCE_INIT(float, float)
ROSIDL_RUNTIME_C__DEFINE_PRIMITIVE_SEQUENCE_FINI(float)
ROSIDL_RUNTIME_C__DEFINE_PRIMITIVE_SEQUENCE_INIT(double, double)
ROSIDL_RUNTIME_C__DEFINE_PRIMITIVE_SEQUENCE_FINI(double)
ROSIDL_RUNTIME_C__DEFINE_PRIMITIVE_SEQUENCE_INIT(long_double, long double)
ROSIDL_RUNTIME_C__DEFINE_PRIMITIVE_SEQUENCE_FINI(long_double)
ROSIDL_RUNTIME_C__DEFINE_PRIMITIVE_SEQUENCE_INIT(char, signed char)
ROSIDL_RUNTIME_C__DEFINE_PRIMITIVE_SEQUENCE_FINI(char)
ROSIDL_RUNTIME_C__DEFINE_PRIMITIVE_SEQUENCE_INIT(wchar, uint16_t)
ROSIDL_RUNTIME_C__DEFINE_PRIMITIVE_SEQUENCE_FINI(wchar)
ROSIDL_RUNTIME_C__DEFINE_PRIMITIVE_SEQUENCE_INIT(boolean, bool)
ROSIDL_RUNTIME_C__DEFINE_PRIMITIVE_SEQUENCE_FINI(boolean)
ROSIDL_RUNTIME_C__DEFINE_PRIMITIVE_SEQUENCE_INIT(octet, uint8_t)
ROSIDL_RUNTIME_C__DEFINE_PRIMITIVE_SEQUENCE_FINI(octet)
ROSIDL_RUNTIME_C__DEFINE_PRIMITIVE_SEQUENCE_INIT(uint8, uint8_t)
ROSIDL_RUNTIME_C__DEFINE_PRIMITIVE_SEQUENCE_FINI(uint8)
ROSIDL_RUNTIME_C__DEFINE_PRIMITIVE_SEQUENCE_INIT(int8, int8_t)
ROSIDL_RUNTIME_C__DEFINE_PRIMITIVE_SEQUENCE_FINI(int8)
ROSIDL_RUNTIME_C__DEFINE_PRIMITIVE_SEQUENCE_INIT(uint16, uint16_t)
ROSIDL_RUNTIME_C__DEFINE_PRIMITIVE_SEQUENCE_FINI(uint16)
ROSIDL_RUNTIME_C__DEFINE_PRIMITIVE_SEQUENCE_INIT(int16, int16_t)
ROSIDL_RUNTIME_C__DEFINE_PRIMITIVE_SEQUENCE_FINI(int16)
ROSIDL_RUNTIME_C__DEFINE_PRIMITIVE_SEQUENCE_INIT(uint32, uint32_t)
ROSIDL_RUNTIME_C__DEFINE_PRIMITIVE_SEQUENCE_FINI(uint32)
ROSIDL_RUNTIME_C__DEFINE_PRIMITIVE_SEQUENCE_INIT(int32, int32_t)
ROSIDL_RUNTIME_C__DEFINE_PRIMITIVE_SEQUENCE_FINI(int32)
ROSIDL_RUNTIME_C__DEFINE_PRIMITIVE_SEQUENCE_INIT(uint64, uint64_t)
ROSIDL_RUNTIME_C__DEFINE_PRIMITIVE_SEQUENCE_FINI(uint64)
ROSIDL_RUNTIME_C__DEFINE_PRIMITIVE_SEQUENCE_INIT(int64, int64_t)
ROSIDL_RUNTIME_C__DEFINE_PRIMITIVE_SEQUENCE_FINI(int64)

#ifdef __cplusplus
}
#endif

#endif  // ROSIDL_RUNTIME_C__PRIMITIVES_SEQUENCE_H_
