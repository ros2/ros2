// Minimal mock for rosidl_runtime_c/string.h
#ifndef ROSIDL_RUNTIME_C__STRING_H_
#define ROSIDL_RUNTIME_C__STRING_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>  // For realloc, free (C standard library)

#ifdef __cplusplus
extern "C" {
#endif

// ROS2 string type (heap-allocated, NUL-terminated)
typedef struct rosidl_runtime_c__String {
    char * data;
    size_t size;
    size_t capacity;
} rosidl_runtime_c__String;

// ROS2 bounded string sequence
typedef struct rosidl_runtime_c__String__Sequence {
    rosidl_runtime_c__String * data;
    size_t size;
    size_t capacity;
} rosidl_runtime_c__String__Sequence;

// Initialize a string to empty
static inline bool
rosidl_runtime_c__String__init(rosidl_runtime_c__String * str)
{
    if (!str) {
        return false;
    }
    str->data = NULL;
    str->size = 0;
    str->capacity = 0;
    return true;
}

// Finalize (free) a string
static inline void
rosidl_runtime_c__String__fini(rosidl_runtime_c__String * str)
{
    if (str && str->data) {
        free(str->data);
        str->data = NULL;
        str->size = 0;
        str->capacity = 0;
    }
}

// Assign a C string to a ROS string
static inline bool
rosidl_runtime_c__String__assign(rosidl_runtime_c__String * str, const char * value)
{
    if (!str || !value) {
        return false;
    }
    size_t len = 0;
    while (value[len]) { len++; }

    if (len + 1 > str->capacity) {
        char * new_data = (char *)realloc(str->data, len + 1);
        if (!new_data) {
            return false;
        }
        str->data = new_data;
        str->capacity = len + 1;
    }

    for (size_t i = 0; i <= len; i++) {
        str->data[i] = value[i];
    }
    str->size = len;
    return true;
}

#ifdef __cplusplus
}
#endif

#endif  // ROSIDL_RUNTIME_C__STRING_H_
