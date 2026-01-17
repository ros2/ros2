// Minimal mock for rcutils/allocator.h (for cross-compilation only)
#ifndef RCUTILS__ALLOCATOR_H_
#define RCUTILS__ALLOCATOR_H_

#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

// Return type for rcutils functions
typedef int rcutils_ret_t;
#define RCUTILS_RET_OK 0
#define RCUTILS_RET_ERROR 1
#define RCUTILS_RET_BAD_ALLOC 10
#define RCUTILS_RET_INVALID_ARGUMENT 11

typedef struct rcutils_allocator_t {
    void * (*allocate)(size_t size, void * state);
    void (*deallocate)(void * pointer, void * state);
    void * (*reallocate)(void * pointer, size_t size, void * state);
    void * (*zero_allocate)(size_t number_of_elements, size_t size_of_element, void * state);
    void * state;
} rcutils_allocator_t;

static inline void * rcutils_allocator_allocate(rcutils_allocator_t * allocator, size_t size) {
    return allocator->allocate(size, allocator->state);
}

static inline void rcutils_allocator_deallocate(rcutils_allocator_t * allocator, void * pointer) {
    allocator->deallocate(pointer, allocator->state);
}

// Default allocator using malloc/free
static inline void * __rcutils_default_allocate(size_t size, void * state) {
    (void)state;
    return malloc(size);
}

static inline void __rcutils_default_deallocate(void * pointer, void * state) {
    (void)state;
    free(pointer);
}

static inline void * __rcutils_default_reallocate(void * pointer, size_t size, void * state) {
    (void)state;
    return realloc(pointer, size);
}

static inline void * __rcutils_default_zero_allocate(size_t number, size_t size, void * state) {
    (void)state;
    return calloc(number, size);
}

static inline rcutils_allocator_t rcutils_get_default_allocator(void) {
    rcutils_allocator_t allocator = {
        __rcutils_default_allocate,
        __rcutils_default_deallocate,
        __rcutils_default_reallocate,
        __rcutils_default_zero_allocate,
        NULL
    };
    return allocator;
}

// ============================================================================
// String Array Type
// ============================================================================
typedef struct rcutils_string_array_s {
    size_t size;
    char ** data;
    rcutils_allocator_t allocator;
} rcutils_string_array_t;

/**
 * Initialize a string array with given size.
 */
static inline rcutils_ret_t rcutils_string_array_init(
    rcutils_string_array_t * string_array,
    size_t size,
    rcutils_allocator_t * allocator)
{
    if (!string_array || !allocator) {
        return RCUTILS_RET_INVALID_ARGUMENT;
    }
    string_array->size = size;
    string_array->allocator = *allocator;
    if (size == 0) {
        string_array->data = NULL;
        return RCUTILS_RET_OK;
    }
    string_array->data = (char **)allocator->allocate(size * sizeof(char *), allocator->state);
    if (!string_array->data) {
        return RCUTILS_RET_BAD_ALLOC;
    }
    for (size_t i = 0; i < size; ++i) {
        string_array->data[i] = NULL;
    }
    return RCUTILS_RET_OK;
}

/**
 * Finalize a string array.
 */
static inline rcutils_ret_t rcutils_string_array_fini(rcutils_string_array_t * string_array) {
    if (!string_array) {
        return RCUTILS_RET_INVALID_ARGUMENT;
    }
    if (string_array->data) {
        for (size_t i = 0; i < string_array->size; ++i) {
            if (string_array->data[i]) {
                string_array->allocator.deallocate(string_array->data[i], string_array->allocator.state);
            }
        }
        string_array->allocator.deallocate(string_array->data, string_array->allocator.state);
    }
    string_array->data = NULL;
    string_array->size = 0;
    return RCUTILS_RET_OK;
}

/**
 * Duplicate a string using an allocator.
 */
static inline char * rcutils_strdup(const char * str, rcutils_allocator_t allocator) {
    if (!str) {
        return NULL;
    }
    size_t len = 0;
    while (str[len] != '\0') ++len;
    char * copy = (char *)allocator.allocate(len + 1, allocator.state);
    if (!copy) {
        return NULL;
    }
    for (size_t i = 0; i <= len; ++i) {
        copy[i] = str[i];
    }
    return copy;
}

/**
 * Get zero-initialized string array.
 */
static inline rcutils_string_array_t rcutils_get_zero_initialized_string_array(void) {
    rcutils_string_array_t array;
    array.size = 0;
    array.data = NULL;
    // Note: allocator will be set during init
    return array;
}

#ifdef __cplusplus
}
#endif

#endif  // RCUTILS__ALLOCATOR_H_
