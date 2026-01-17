// Auto-generated TypeDescription for std_msgs/msg/String
// Version: v5-lite - Heap allocation but minimal data (like stub)
//
// PURPOSE: Test if crash is caused by:
// A) Heap allocation itself, or
// B) The content/structure of TypeDescription
//
// If v5-lite works → issue is the content
// If v5-lite crashes → issue is heap allocation

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>

#include "rosidl_runtime_c/type_hash.h"
#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/string_functions.h"
#include "rosidl_runtime_c/type_description/type_description__struct.h"
#include "rosidl_runtime_c/type_description/type_description__functions.h"
#include "rosidl_runtime_c/type_description/type_source__struct.h"
#include "rosidl_runtime_c/type_description/type_source__functions.h"
#include "rosidl_runtime_c/type_description/individual_type_description__struct.h"
#include "rosidl_runtime_c/type_description/individual_type_description__functions.h"

// Type Hash (same as v5)
static const rosidl_type_hash_t std_msgs_String_type_hash = {
  1,
  {0x2c, 0x98, 0x32, 0x2f, 0x67, 0x8b, 0x8b, 0x6b,
   0x96, 0x1c, 0xc7, 0x8e, 0x95, 0x1a, 0xd2, 0x25}
};

// Heap-allocated but minimal TypeDescription
static rosidl_runtime_c__type_description__TypeDescription * g_type_desc = NULL;
static rosidl_runtime_c__type_description__TypeSource__Sequence * g_type_sources = NULL;

static pthread_once_t g_init_once = PTHREAD_ONCE_INIT;
static int g_init_success = 0;

static void std_msgs_String_do_init(void) {
  fprintf(stderr, "[std_msgs/String] v5-lite: Starting initialization...\n");

  // 1. Create TypeDescription (heap allocated)
  //    This calls init() internally which zeros everything
  g_type_desc = rosidl_runtime_c__type_description__TypeDescription__create();
  if (!g_type_desc) {
    fprintf(stderr, "[std_msgs/String] v5-lite: Failed to create TypeDescription\n");
    return;
  }

  fprintf(stderr, "[std_msgs/String] v5-lite: TypeDescription created at %p\n", (void*)g_type_desc);
  fprintf(stderr, "  type_description.type_name = {data=%p, size=%zu, cap=%zu}\n",
          (void*)g_type_desc->type_description.type_name.data,
          g_type_desc->type_description.type_name.size,
          g_type_desc->type_description.type_name.capacity);
  fprintf(stderr, "  type_description.fields = {data=%p, size=%zu, cap=%zu}\n",
          (void*)g_type_desc->type_description.fields.data,
          g_type_desc->type_description.fields.size,
          g_type_desc->type_description.fields.capacity);

  // 2. DON'T populate any fields - leave as zeroed/NULL
  //    This mimics stub behavior but with heap-allocated container

  // 3. Create empty TypeSource sequence
  g_type_sources = rosidl_runtime_c__type_description__TypeSource__Sequence__create(0);
  if (!g_type_sources) {
    fprintf(stderr, "[std_msgs/String] v5-lite: Failed to create type_sources\n");
    return;
  }

  g_init_success = 1;
  fprintf(stderr, "[std_msgs/String] v5-lite: Initialization complete (minimal data)\n");
}

const rosidl_type_hash_t * std_msgs__msg__String__get_type_hash(void * unused) {
  (void)unused;
  return &std_msgs_String_type_hash;
}

const rosidl_runtime_c__type_description__TypeDescription *
std_msgs__msg__String__get_type_description(void * unused) {
  (void)unused;
  pthread_once(&g_init_once, std_msgs_String_do_init);
  if (!g_init_success) {
    fprintf(stderr, "[std_msgs/String] v5-lite: get_type_description - init failed\n");
    return NULL;
  }
  fprintf(stderr, "[std_msgs/String] v5-lite: Returning type_desc=%p\n", (void*)g_type_desc);
  return g_type_desc;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
std_msgs__msg__String__get_type_description_sources(void * unused) {
  (void)unused;
  pthread_once(&g_init_once, std_msgs_String_do_init);
  if (!g_init_success) {
    return NULL;
  }
  return g_type_sources;
}
