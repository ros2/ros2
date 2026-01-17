/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file compat_clib.h
 *
 * @brief C library compatibility header for cross-compilation
 *
 * This header declares C library functions using extern "C" to work around
 * issues with gcc-linaro 7.5.0's sysroot configuration when using <cstring>.
 * Include this header BEFORE any standard C++ headers that need string/memory
 * functions.
 */

#ifndef RMW_DSOFTBUS__COMPAT_CLIB_H_
#define RMW_DSOFTBUS__COMPAT_CLIB_H_

#include <stddef.h>  // For size_t

#ifdef __cplusplus
extern "C" {
#endif

// Memory functions
void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
void *memchr(const void *s, int c, size_t n);

// String functions
size_t strlen(const char *s);
char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, size_t n);
char *strcat(char *dest, const char *src);
char *strncat(char *dest, const char *src, size_t n);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);
char *strchr(const char *s, int c);
char *strrchr(const char *s, int c);
char *strstr(const char *haystack, const char *needle);
char *strpbrk(const char *s, const char *accept);
size_t strspn(const char *s, const char *accept);
size_t strcspn(const char *s, const char *reject);
char *strtok(char *str, const char *delim);
char *strerror(int errnum);
int strcoll(const char *s1, const char *s2);
size_t strxfrm(char *dest, const char *src, size_t n);

// Note: Memory allocation (malloc/realloc/free) should be obtained from <stdlib.h>
// Do not redeclare them here to avoid noexcept conflicts with system headers.

#ifdef __cplusplus
}
#endif

#endif  // RMW_DSOFTBUS__COMPAT_CLIB_H_
