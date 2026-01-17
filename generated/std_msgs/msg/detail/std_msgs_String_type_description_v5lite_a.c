// Auto-generated TypeDescription for std_msgs/msg/String
// Version: v5-lite-a - Add type_name only (fields still empty)
//
// Testing if type_name causes the crash

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
  fprintf(stderr, "[std_msgs/String] v5-lite-a: Starting...\n");

  g_type_desc = rosidl_runtime_c__type_description__TypeDescription__create();
  if (!g_type_desc) { return; }

  // ADD: type_name (this is the only addition from v5-lite)
  if (!rosidl_runtime_c__String__assign(
        &g_type_desc->type_description.type_name, "std_msgs/msg/String")) {
    fprintf(stderr, "[std_msgs/String] v5-lite-a: Failed to assign type_name\n");
    return;
  }

  g_type_sources = rosidl_runtime_c__type_description__TypeSource__Sequence__create(0);
  if (!g_type_sources) { return; }

  g_init_success = 1;
  fprintf(stderr, "[std_msgs/String] v5-lite-a: OK - type_name='%s', fields.size=%zu\n",
          g_type_desc->type_description.type_name.data,
          g_type_desc->type_description.fields.size);
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
