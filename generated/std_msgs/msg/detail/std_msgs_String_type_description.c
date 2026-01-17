// Auto-generated TypeDescription for std_msgs/msg/String
// Version: v5 - Heap allocation with official rosidl_runtime_c API
//
// MEMORY CONTRACT:
// - All rosidl_runtime_c__String members use init() + assign() for heap allocation
// - All Sequence members use official Sequence__init() API
// - Thread-safe initialization via pthread_once
// - "Allocate and leak" pattern - metadata lives for process lifetime
//
// This fixes the SIGSEGV crash in v4 caused by:
// - Using static char[] pointers in String.data
// - Which caused free(static_ptr) or realloc(static_ptr) crashes in fini()/copy()

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
#include "rosidl_runtime_c/type_description/field__struct.h"
#include "rosidl_runtime_c/type_description/field__functions.h"
#include "rosidl_runtime_c/type_description/field_type__struct.h"
#include "rosidl_runtime_c/type_description/individual_type_description__struct.h"
#include "rosidl_runtime_c/type_description/individual_type_description__functions.h"

// ============================================================================
// Type Hash for std_msgs/msg/String (stable MD5-based hash)
// ============================================================================
static const rosidl_type_hash_t std_msgs_String_type_hash = {
  1,  // version
  {0x2c, 0x98, 0x32, 0x2f, 0x67, 0x8b, 0x8b, 0x6b,
   0x96, 0x1c, 0xc7, 0x8e, 0x95, 0x1a, 0xd2, 0x25}
};

// ============================================================================
// Heap-allocated TypeDescription (populated once, lives for process lifetime)
// ============================================================================
static rosidl_runtime_c__type_description__TypeDescription * g_type_desc = NULL;
static rosidl_runtime_c__type_description__TypeSource__Sequence * g_type_sources = NULL;

static pthread_once_t g_init_once = PTHREAD_ONCE_INIT;
static int g_init_success = 0;

// ============================================================================
// Thread-safe one-time initialization
// ============================================================================
static void std_msgs_String_do_init(void) {
  // 1. Create TypeDescription (heap allocated, zeroed, and init'd)
  g_type_desc = rosidl_runtime_c__type_description__TypeDescription__create();
  if (!g_type_desc) {
    fprintf(stderr, "[std_msgs/String] Failed to create TypeDescription\n");
    return;
  }

  // 2. Set type_name using heap allocation
  //    type_description.type_name is already initialized by create()
  if (!rosidl_runtime_c__String__assign(
        &g_type_desc->type_description.type_name, "std_msgs/msg/String")) {
    fprintf(stderr, "[std_msgs/String] Failed to assign type_name\n");
    return;
  }

  // 3. Initialize fields sequence with 1 element
  //    This allocates and inits the Field array on heap
  if (!rosidl_runtime_c__type_description__Field__Sequence__init(
        &g_type_desc->type_description.fields, 1)) {
    fprintf(stderr, "[std_msgs/String] Failed to init fields sequence\n");
    return;
  }

  // 4. Get pointer to the first (and only) field
  rosidl_runtime_c__type_description__Field * field =
    &g_type_desc->type_description.fields.data[0];

  // 5. Set field name (heap allocated)
  if (!rosidl_runtime_c__String__assign(&field->name, "data")) {
    fprintf(stderr, "[std_msgs/String] Failed to assign field name\n");
    return;
  }

  // 6. Set field type
  //    FIELD_TYPE_STRING = 17 (from field_type__struct.h)
  field->type.type_id = rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING;
  field->type.capacity = 0;
  field->type.string_capacity = 0;

  // 7. Set nested_type_name to empty string (heap allocated)
  //    Even empty strings must be properly allocated for fini() safety
  if (!rosidl_runtime_c__String__assign(&field->type.nested_type_name, "")) {
    fprintf(stderr, "[std_msgs/String] Failed to assign nested_type_name\n");
    return;
  }

  // 8. Set default_value to empty string (heap allocated)
  if (!rosidl_runtime_c__String__assign(&field->default_value, "")) {
    fprintf(stderr, "[std_msgs/String] Failed to assign default_value\n");
    return;
  }

  // 9. Initialize referenced_type_descriptions as empty sequence
  //    std_msgs/String has no nested types, so size = 0
  if (!rosidl_runtime_c__type_description__IndividualTypeDescription__Sequence__init(
        &g_type_desc->referenced_type_descriptions, 0)) {
    fprintf(stderr, "[std_msgs/String] Failed to init referenced_type_descriptions\n");
    return;
  }

  // 10. Create TypeSource sequence (empty for now)
  g_type_sources = rosidl_runtime_c__type_description__TypeSource__Sequence__create(0);
  if (!g_type_sources) {
    fprintf(stderr, "[std_msgs/String] Failed to create type_sources\n");
    return;
  }

  g_init_success = 1;

  // Debug output (once only)
  fprintf(stderr, "[std_msgs/String] TypeDescription v5 initialized successfully\n");
  fprintf(stderr, "  type_name.data=%p, size=%zu, capacity=%zu\n",
          (void*)g_type_desc->type_description.type_name.data,
          g_type_desc->type_description.type_name.size,
          g_type_desc->type_description.type_name.capacity);
  fprintf(stderr, "  fields.size=%zu, fields.data=%p\n",
          g_type_desc->type_description.fields.size,
          (void*)g_type_desc->type_description.fields.data);
  fprintf(stderr, "  field[0].name.data=%p (\"%s\")\n",
          (void*)field->name.data, field->name.data);
  fprintf(stderr, "  field[0].type.type_id=%u (expected 17=STRING)\n",
          field->type.type_id);
}

// ============================================================================
// Exported Functions
// ============================================================================

const rosidl_type_hash_t * std_msgs__msg__String__get_type_hash(void * unused) {
  (void)unused;
  return &std_msgs_String_type_hash;
}

const rosidl_runtime_c__type_description__TypeDescription *
std_msgs__msg__String__get_type_description(void * unused) {
  (void)unused;
  pthread_once(&g_init_once, std_msgs_String_do_init);
  if (!g_init_success) {
    fprintf(stderr, "[std_msgs/String] WARNING: get_type_description called but init failed\n");
    return NULL;
  }
  return g_type_desc;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
std_msgs__msg__String__get_type_description_sources(void * unused) {
  (void)unused;
  pthread_once(&g_init_once, std_msgs_String_do_init);
  if (!g_init_success) {
    fprintf(stderr, "[std_msgs/String] WARNING: get_type_description_sources called but init failed\n");
    return NULL;
  }
  return g_type_sources;
}
