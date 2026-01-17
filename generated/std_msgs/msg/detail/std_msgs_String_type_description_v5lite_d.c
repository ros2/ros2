// Auto-generated TypeDescription for std_msgs/msg/String
// Version: v5-lite-d - Add field.type.type_id = 17 (STRING)
//
// Testing if setting type_id causes the crash

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

static const rosidl_type_hash_t std_msgs_String_type_hash = {
  1,
  {0x2c, 0x98, 0x32, 0x2f, 0x67, 0x8b, 0x8b, 0x6b,
   0x96, 0x1c, 0xc7, 0x8e, 0x95, 0x1a, 0xd2, 0x25}
};

static rosidl_runtime_c__type_description__TypeDescription * g_type_desc = NULL;
static rosidl_runtime_c__type_description__TypeSource__Sequence * g_type_sources = NULL;
static pthread_once_t g_init_once = PTHREAD_ONCE_INIT;
static int g_init_success = 0;

static void std_msgs_String_do_init(void) {
  fprintf(stderr, "[std_msgs/String] v5-lite-d: Starting...\n");

  g_type_desc = rosidl_runtime_c__type_description__TypeDescription__create();
  if (!g_type_desc) { return; }

  // type_name
  if (!rosidl_runtime_c__String__assign(
        &g_type_desc->type_description.type_name, "std_msgs/msg/String")) {
    return;
  }

  // Initialize fields sequence with 1 element
  if (!rosidl_runtime_c__type_description__Field__Sequence__init(
        &g_type_desc->type_description.fields, 1)) {
    return;
  }

  // Get pointer to field[0]
  rosidl_runtime_c__type_description__Field * field =
    &g_type_desc->type_description.fields.data[0];

  // Set field name
  if (!rosidl_runtime_c__String__assign(&field->name, "data")) {
    return;
  }

  // ADD: Set field type
  field->type.type_id = rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING;
  field->type.capacity = 0;
  field->type.string_capacity = 0;
  // NOTE: NOT setting nested_type_name and default_value - leave as zeroed/NULL

  // Initialize referenced_type_descriptions (empty)
  if (!rosidl_runtime_c__type_description__IndividualTypeDescription__Sequence__init(
        &g_type_desc->referenced_type_descriptions, 0)) {
    return;
  }

  g_type_sources = rosidl_runtime_c__type_description__TypeSource__Sequence__create(0);
  if (!g_type_sources) { return; }

  g_init_success = 1;
  fprintf(stderr, "[std_msgs/String] v5-lite-d: OK - field[0].name='%s', type_id=%u (17=STRING)\n",
          field->name.data, field->type.type_id);
  fprintf(stderr, "  field.type.nested_type_name.data=%p\n", (void*)field->type.nested_type_name.data);
  fprintf(stderr, "  field.default_value.data=%p\n", (void*)field->default_value.data);
}

const rosidl_type_hash_t * std_msgs__msg__String__get_type_hash(void * unused) {
  (void)unused;
  return &std_msgs_String_type_hash;
}

const rosidl_runtime_c__type_description__TypeDescription *
std_msgs__msg__String__get_type_description(void * unused) {
  (void)unused;
  pthread_once(&g_init_once, std_msgs_String_do_init);
  if (!g_init_success) { return NULL; }
  return g_type_desc;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
std_msgs__msg__String__get_type_description_sources(void * unused) {
  (void)unused;
  pthread_once(&g_init_once, std_msgs_String_do_init);
  if (!g_init_success) { return NULL; }
  return g_type_sources;
}
