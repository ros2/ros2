// Stub implementations for type description functions
#include <stddef.h>
#include "rosidl_runtime_c/type_hash.h"
#include "rosidl_runtime_c/type_description/type_description__struct.h"
#include "rosidl_runtime_c/type_description/type_source__struct.h"

static const rosidl_type_hash_t stub_type_hash = {{1}, {0}};
static const rosidl_runtime_c__type_description__TypeDescription stub_type_description = {{{NULL, 0, 0}, {NULL, 0, 0}}, {NULL, 0, 0}};
static const rosidl_runtime_c__type_description__TypeSource__Sequence stub_type_sources = {NULL, 0, 0};

#define DEFINE_TYPE_DESCRIPTION_STUBS(PKG, TYPE) \
  const rosidl_type_hash_t * PKG##__msg__##TYPE##__get_type_hash(void* unused) { (void)unused; return &stub_type_hash; } \
  const rosidl_runtime_c__type_description__TypeDescription * PKG##__msg__##TYPE##__get_type_description(void* unused) { (void)unused; return &stub_type_description; } \
  const rosidl_runtime_c__type_description__TypeSource__Sequence * PKG##__msg__##TYPE##__get_type_description_sources(void* unused) { (void)unused; return &stub_type_sources; }

DEFINE_TYPE_DESCRIPTION_STUBS(std_msgs, Bool)
DEFINE_TYPE_DESCRIPTION_STUBS(std_msgs, Byte)
DEFINE_TYPE_DESCRIPTION_STUBS(std_msgs, ByteMultiArray)
DEFINE_TYPE_DESCRIPTION_STUBS(std_msgs, Char)
DEFINE_TYPE_DESCRIPTION_STUBS(std_msgs, ColorRGBA)
DEFINE_TYPE_DESCRIPTION_STUBS(std_msgs, Empty)
DEFINE_TYPE_DESCRIPTION_STUBS(std_msgs, Float32)
DEFINE_TYPE_DESCRIPTION_STUBS(std_msgs, Float32MultiArray)
DEFINE_TYPE_DESCRIPTION_STUBS(std_msgs, Float64)
DEFINE_TYPE_DESCRIPTION_STUBS(std_msgs, Float64MultiArray)
DEFINE_TYPE_DESCRIPTION_STUBS(std_msgs, Header)
DEFINE_TYPE_DESCRIPTION_STUBS(std_msgs, Int16)
DEFINE_TYPE_DESCRIPTION_STUBS(std_msgs, Int16MultiArray)
DEFINE_TYPE_DESCRIPTION_STUBS(std_msgs, Int32)
DEFINE_TYPE_DESCRIPTION_STUBS(std_msgs, Int32MultiArray)
DEFINE_TYPE_DESCRIPTION_STUBS(std_msgs, Int64)
DEFINE_TYPE_DESCRIPTION_STUBS(std_msgs, Int64MultiArray)
DEFINE_TYPE_DESCRIPTION_STUBS(std_msgs, Int8)
DEFINE_TYPE_DESCRIPTION_STUBS(std_msgs, Int8MultiArray)
DEFINE_TYPE_DESCRIPTION_STUBS(std_msgs, MultiArrayDimension)
DEFINE_TYPE_DESCRIPTION_STUBS(std_msgs, MultiArrayLayout)
// DEFINE_TYPE_DESCRIPTION_STUBS(std_msgs, String)  // Using v5-lite for String
DEFINE_TYPE_DESCRIPTION_STUBS(std_msgs, UInt16)
DEFINE_TYPE_DESCRIPTION_STUBS(std_msgs, UInt16MultiArray)
DEFINE_TYPE_DESCRIPTION_STUBS(std_msgs, UInt32)
DEFINE_TYPE_DESCRIPTION_STUBS(std_msgs, UInt32MultiArray)
DEFINE_TYPE_DESCRIPTION_STUBS(std_msgs, UInt64)
DEFINE_TYPE_DESCRIPTION_STUBS(std_msgs, UInt64MultiArray)
DEFINE_TYPE_DESCRIPTION_STUBS(std_msgs, UInt8)
DEFINE_TYPE_DESCRIPTION_STUBS(std_msgs, UInt8MultiArray)
