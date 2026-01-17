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

// Copyright (c) 2026 ROS2 KaihongOS Port Project
#include <string.h>  /* C memcpy/memset for OHOS SDK compatibility */
#include <stdlib.h>

// Licensed under the Apache License, Version 2.0
//
// Generic ROS2 Message Serializer using rosidl_typesupport_introspection_c

#include "rmw_dsoftbus/rmw_dsoftbus.h"
#include "rmw_dsoftbus/cdr_serializer.h"

#include <rosidl_typesupport_introspection_c/field_types.h>
#include <rosidl_typesupport_introspection_c/message_introspection.h>
#include <rosidl_typesupport_introspection_c/identifier.h>
#include <rosidl_runtime_c/string.h>
#include <rosidl_runtime_c/primitives_sequence.h>

#include <cstring>
#include <vector>

// C library function declarations
// Explicit declarations for cross-compiler compatibility
extern "C" {
void* memcpy(void* dest, const void* src, size_t n);
int strcmp(const char* s1, const char* s2);
size_t strlen(const char* s);
}

namespace rmw_dsoftbus {
namespace typesupport {

// C++ introspection identifier
static const char* const ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_IDENTIFIER =
    "rosidl_typesupport_introspection_cpp";

// Helper function to check if typesupport is C introspection (safe to use)
static bool is_c_introspection_typesupport(const char* identifier)
{
    if (!identifier) {
        return false;
    }
    return strcmp(identifier, rosidl_typesupport_introspection_c__identifier) == 0;
}

// Helper function to check if typesupport is C++ introspection
static bool is_cpp_introspection_typesupport(const char* identifier)
{
    if (!identifier) {
        return false;
    }
    return strcmp(identifier, ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_IDENTIFIER) == 0;
}

// Helper function to get introspection type support
// Currently only supports C introspection (C++ has different struct layout)
static const rosidl_message_type_support_t* get_message_typesupport_handle(
    const rosidl_message_type_support_t* type_support,
    const char* /* identifier */)
{
    if (!type_support) {
        return nullptr;
    }

    // Only accept C introspection typesupport (safe to cast to C struct)
    if (type_support->typesupport_identifier &&
        is_c_introspection_typesupport(type_support->typesupport_identifier)) {
        return type_support;
    }

    // C++ typesupport: different struct layout, skip serialization for now
    if (type_support->typesupport_identifier &&
        is_cpp_introspection_typesupport(type_support->typesupport_identifier)) {
        // C++ typesupport detected - we'll serialize an empty message for safety
        fprintf(stderr, "[INFO] C++ typesupport detected, using fallback serialization\n");
        return nullptr;  // Will use fallback path
    }

    fprintf(stderr, "[WARN] Unknown typesupport: %s\n",
            type_support->typesupport_identifier ? type_support->typesupport_identifier : "NULL");
    return nullptr;
}

// ============================================================================
// Generic CDR Serializer using TypeSupport Introspection
// ============================================================================

class GenericCDRSerializer
{
public:
    GenericCDRSerializer() = default;

    bool serialize_message(
        const void* ros_message,
        const rosidl_message_type_support_t* type_support,
        std::vector<uint8_t>& output)
    {
        if (!ros_message || !type_support) {
            fprintf(stderr, "[ERROR] Invalid input: ros_message=%p, type_support=%p\n", ros_message, (void*)type_support);
            return false;
        }

        // Get introspection type support
        const rosidl_message_type_support_t* ts = get_message_typesupport_handle(
            type_support,
            rosidl_typesupport_introspection_c__identifier);

        if (!ts) {
            // C++ introspection typesupport detected - different struct layout from C
            if (type_support->typesupport_identifier &&
                is_cpp_introspection_typesupport(type_support->typesupport_identifier)) {

                // ⚠️ CRITICAL WARNING ⚠️
                // This RMW currently does NOT support real serialization for C++ introspection typesupport.
                // Sending an empty CDR message as fallback (4 bytes: CDR header only).
                //
                // NOTE: This 4-byte buffer represents an empty CDR stream:
                //   Byte 0-1: Endianness indicator (0x00 0x01 = little-endian)
                //   Byte 2-3: Options (unused)
                // Conforms to OMG CDR 1.2 spec / Fast-CDR format
                // Used ONLY to satisfy RMW expectations during node initialization.
                // It MUST NOT be used for real data transport.

                fprintf(stderr, "[WARN] C++ introspection typesupport detected (type=%s).\n",
                        type_support->typesupport_identifier);
                fprintf(stderr, "[WARN] This RMW does NOT support real serialization for it.\n");
                fprintf(stderr, "[WARN] Sending empty CDR message (4 bytes header only).\n");
                fprintf(stderr, "[WARN] If this is NOT a system topic (/parameter*, /rosout), this is a BUG!\n");

                output.resize(cdr::CDR_ENCAPSULATION_SIZE);
                output[0] = 0x00;  // Endianness: little-endian (CDR_LE)
                output[1] = 0x01;  // Representation identifier
                output[2] = 0x00;  // Options (unused)
                output[3] = 0x00;  // Options (unused)
                return true;  // Return success with minimal message (use with caution!)
            }
            fprintf(stderr, "[ERROR] Failed to get introspection typesupport\n");
            return false;
        }

        const auto* members = static_cast<const rosidl_typesupport_introspection_c__MessageMembers*>(
            ts->data);

        if (!members) {
            fprintf(stderr, "[ERROR] TypeSupport members is null\n");
            return false;
        }

        // Calculate total size needed (starting from offset after CDR header)
        size_t size = calculate_serialized_size_from_offset(ros_message, members, cdr::CDR_ENCAPSULATION_SIZE);

        // Reserve space (CDR header + data)
        output.resize(cdr::CDR_ENCAPSULATION_SIZE + size);

        // Write CDR encapsulation header
        output[0] = 0x00;  // Encoding kind (CDR_BE / CDR_LE)
        output[1] = 0x01;  // Representation identifier (little-endian)
        output[2] = 0x00;  // Options (unused)
        output[3] = 0x00;  // Options (unused)

        // Serialize message members
        size_t offset = cdr::CDR_ENCAPSULATION_SIZE;
        bool result = serialize_members(ros_message, members, output.data(), output.size(), offset);
        return result;
    }

    bool deserialize_message(
        const uint8_t* cdr_data,
        size_t cdr_len,
        const rosidl_message_type_support_t* type_support,
        void* ros_message)
    {
        if (!cdr_data || !ros_message || !type_support) {
            fprintf(stderr, "[ERROR] Invalid input to deserialize\n");
            return false;
        }

        if (cdr_len < cdr::CDR_ENCAPSULATION_SIZE) {
            fprintf(stderr, "[ERROR] CDR data too short\n");
            return false;
        }

        // Verify CDR header
        if (cdr_data[0] != 0x00 || cdr_data[1] != 0x01) {
            fprintf(stderr, "[ERROR] Invalid CDR encapsulation\n");
            return false;
        }

        // Get introspection type support
        const rosidl_message_type_support_t* ts = get_message_typesupport_handle(
            type_support,
            rosidl_typesupport_introspection_c__identifier);

        if (!ts) {
            fprintf(stderr, "[ERROR] Failed to get type support\n");
            return false;
        }

        const auto* members = static_cast<const rosidl_typesupport_introspection_c__MessageMembers*>(
            ts->data);

        if (!members) {
            fprintf(stderr, "[ERROR] Members is null\n");
            return false;
        }

        // Deserialize message members
        size_t offset = cdr::CDR_ENCAPSULATION_SIZE;
        bool result = deserialize_members(cdr_data, cdr_len, members, ros_message, offset);
        return result;
    }

private:
    // Calculate serialized size for a message
    // Calculate serialized size starting from a specific offset (to account for alignment)
    size_t calculate_serialized_size_from_offset(
        const void* data,
        const rosidl_typesupport_introspection_c__MessageMembers* members,
        size_t start_offset)
    {
        size_t offset = start_offset;

        for (uint32_t i = 0; i < members->member_count_; ++i) {
            const auto& member = members->members_[i];
            const uint8_t* member_data = static_cast<const uint8_t*>(data) + member.offset_;

            offset += calculate_member_size_from_offset(member_data, &member, offset);
        }

        return offset - start_offset;  // Return the size, not the final offset
    }

    size_t calculate_serialized_size(
        const void* data,
        const rosidl_typesupport_introspection_c__MessageMembers* members)
    {
        return calculate_serialized_size_from_offset(data, members, 0);
    }

    // Calculate member size accounting for current offset (for alignment)
    size_t calculate_member_size_from_offset(
        const void* member_data,
        const rosidl_typesupport_introspection_c__MessageMember* member,
        size_t current_offset)
    {
        size_t offset = current_offset;

        // Handle arrays
        size_t array_size = member->is_array_ ? get_array_size(member_data, member) : 1;

        // Dynamic array length prefix
        if (member->is_array_ && !member->array_size_) {
            offset = align_offset(offset, 4);
            offset += 4;  // uint32_t for sequence length
        }

        for (size_t i = 0; i < array_size; ++i) {
            const void* element = get_array_element(member_data, member, i);

            switch (member->type_id_) {
                case rosidl_typesupport_introspection_c__ROS_TYPE_BOOL:
                case rosidl_typesupport_introspection_c__ROS_TYPE_BYTE:
                case rosidl_typesupport_introspection_c__ROS_TYPE_UINT8:
                case rosidl_typesupport_introspection_c__ROS_TYPE_INT8:
                    offset += 1;
                    break;
                case rosidl_typesupport_introspection_c__ROS_TYPE_UINT16:
                case rosidl_typesupport_introspection_c__ROS_TYPE_INT16:
                    offset = align_offset(offset, 2);
                    offset += 2;
                    break;
                case rosidl_typesupport_introspection_c__ROS_TYPE_UINT32:
                case rosidl_typesupport_introspection_c__ROS_TYPE_INT32:
                case rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT:
                    offset = align_offset(offset, 4);
                    offset += 4;
                    break;
                case rosidl_typesupport_introspection_c__ROS_TYPE_UINT64:
                case rosidl_typesupport_introspection_c__ROS_TYPE_INT64:
                case rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE:
                    offset = align_offset(offset, 8);
                    offset += 8;
                    break;
                case rosidl_typesupport_introspection_c__ROS_TYPE_STRING:
                {
                    const rosidl_runtime_c__String* str = static_cast<const rosidl_runtime_c__String*>(element);
                    offset = align_offset(offset, 4);
                    offset += 4;  // Length
                    offset += str->size + 1;  // String + null terminator
                    break;
                }
                case rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE:
                {
                    const auto* sub_members = static_cast<const rosidl_typesupport_introspection_c__MessageMembers*>(
                        member->members_->data);
                    size_t sub_size = calculate_serialized_size_from_offset(element, sub_members, offset);
                    offset += sub_size;
                    break;
                }
                default:
                    fprintf(stderr, "[ERROR] Unsupported type_id: %u\n", member->type_id_);
                    break;
            }
        }

        return offset - current_offset;
    }

    size_t calculate_member_size(
        const void* member_data,
        const rosidl_typesupport_introspection_c__MessageMember* member)
    {
        return calculate_member_size_from_offset(member_data, member, 0);
    }

    // Serialize message members
    bool serialize_members(
        const void* data,
        const rosidl_typesupport_introspection_c__MessageMembers* members,
        uint8_t* buffer,
        size_t buffer_size,
        size_t& offset)
    {
        for (uint32_t i = 0; i < members->member_count_; ++i) {
            const auto& member = members->members_[i];
            const uint8_t* member_data = static_cast<const uint8_t*>(data) + member.offset_;

            if (!serialize_member(member_data, &member, buffer, buffer_size, offset)) {
                fprintf(stderr, "[ERROR] Failed to serialize member %u (%s)\n", i, member.name_);
                return false;
            }
        }

        return true;
    }

    bool serialize_member(
        const void* member_data,
        const rosidl_typesupport_introspection_c__MessageMember* member,
        uint8_t* buffer,
        size_t buffer_size,
        size_t& offset)
    {
        // Handle arrays
        size_t array_size = member->is_array_ ? get_array_size(member_data, member) : 1;

        // Write sequence length for dynamic arrays
        if (member->is_array_ && !member->array_size_) {
            if (!write_uint32(buffer, buffer_size, offset, static_cast<uint32_t>(array_size))) {
                return false;
            }
        }

        // Serialize each element
        for (size_t i = 0; i < array_size; ++i) {
            const void* element = get_array_element(member_data, member, i);

            if (!serialize_primitive(element, member, buffer, buffer_size, offset)) {
                return false;
            }
        }

        return true;
    }

    bool serialize_primitive(
        const void* data,
        const rosidl_typesupport_introspection_c__MessageMember* member,
        uint8_t* buffer,
        size_t buffer_size,
        size_t& offset)
    {
        switch (member->type_id_) {
            case rosidl_typesupport_introspection_c__ROS_TYPE_BOOL:
            case rosidl_typesupport_introspection_c__ROS_TYPE_BYTE:
            case rosidl_typesupport_introspection_c__ROS_TYPE_UINT8:
            case rosidl_typesupport_introspection_c__ROS_TYPE_INT8:
                return write_uint8(buffer, buffer_size, offset, *static_cast<const uint8_t*>(data));

            case rosidl_typesupport_introspection_c__ROS_TYPE_UINT16:
            case rosidl_typesupport_introspection_c__ROS_TYPE_INT16:
                return write_uint16(buffer, buffer_size, offset, *static_cast<const uint16_t*>(data));

            case rosidl_typesupport_introspection_c__ROS_TYPE_UINT32:
            case rosidl_typesupport_introspection_c__ROS_TYPE_INT32:
            case rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT:
                return write_uint32(buffer, buffer_size, offset, *static_cast<const uint32_t*>(data));

            case rosidl_typesupport_introspection_c__ROS_TYPE_UINT64:
            case rosidl_typesupport_introspection_c__ROS_TYPE_INT64:
            case rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE:
                return write_uint64(buffer, buffer_size, offset, *static_cast<const uint64_t*>(data));

            case rosidl_typesupport_introspection_c__ROS_TYPE_STRING:
            {
                const rosidl_runtime_c__String* str = static_cast<const rosidl_runtime_c__String*>(data);
                return write_string(buffer, buffer_size, offset, str->data, str->size);
            }

            case rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE:
            {
                const auto* sub_members = static_cast<const rosidl_typesupport_introspection_c__MessageMembers*>(
                    member->members_->data);
                return serialize_members(data, sub_members, buffer, buffer_size, offset);
            }

            default:
                fprintf(stderr, "[ERROR] Unsupported type_id in serialize: %u\n", member->type_id_);
                return false;
        }
    }

    // Deserialize message members
    bool deserialize_members(
        const uint8_t* buffer,
        size_t buffer_size,
        const rosidl_typesupport_introspection_c__MessageMembers* members,
        void* data,
        size_t& offset)
    {
        for (uint32_t i = 0; i < members->member_count_; ++i) {
            const auto& member = members->members_[i];
            uint8_t* member_data = static_cast<uint8_t*>(data) + member.offset_;

            if (!deserialize_member(buffer, buffer_size, &member, member_data, offset)) {
                fprintf(stderr, "[ERROR] Failed to deserialize member %u (%s)\n", i, member.name_);
                return false;
            }
        }

        return true;
    }

    bool deserialize_member(
        const uint8_t* buffer,
        size_t buffer_size,
        const rosidl_typesupport_introspection_c__MessageMember* member,
        void* member_data,
        size_t& offset)
    {
        // Handle arrays
        size_t array_size = member->is_array_ ? member->array_size_ : 1;

        // Read sequence length for dynamic arrays
        if (member->is_array_ && !member->array_size_) {
            uint32_t length = 0;
            if (!read_uint32(buffer, buffer_size, offset, length)) {
                return false;
            }
            array_size = length;

            // Resize dynamic array (all Sequence types have same layout: data, size, capacity)
            struct GenericSequence {
                void* data;
                size_t size;
                size_t capacity;
            };

            GenericSequence* seq = static_cast<GenericSequence*>(member_data);
            if (seq->capacity < array_size) {
                // Reallocate
                void* new_data = realloc(seq->data, array_size * member->size_of_);
                if (!new_data && array_size > 0) {
                    fprintf(stderr, "[ERROR] Failed to allocate sequence of size %zu\n", array_size);
                    return false;
                }
                seq->data = new_data;
                seq->capacity = array_size;
            }
            seq->size = array_size;
        }

        // Deserialize each element
        for (size_t i = 0; i < array_size; ++i) {
            void* element = get_array_element(member_data, member, i);

            if (!deserialize_primitive(buffer, buffer_size, member, element, offset)) {
                return false;
            }
        }

        return true;
    }

    bool deserialize_primitive(
        const uint8_t* buffer,
        size_t buffer_size,
        const rosidl_typesupport_introspection_c__MessageMember* member,
        void* data,
        size_t& offset)
    {
        switch (member->type_id_) {
            case rosidl_typesupport_introspection_c__ROS_TYPE_BOOL:
            case rosidl_typesupport_introspection_c__ROS_TYPE_BYTE:
            case rosidl_typesupport_introspection_c__ROS_TYPE_UINT8:
            case rosidl_typesupport_introspection_c__ROS_TYPE_INT8:
                return read_uint8(buffer, buffer_size, offset, *static_cast<uint8_t*>(data));

            case rosidl_typesupport_introspection_c__ROS_TYPE_UINT16:
            case rosidl_typesupport_introspection_c__ROS_TYPE_INT16:
                return read_uint16(buffer, buffer_size, offset, *static_cast<uint16_t*>(data));

            case rosidl_typesupport_introspection_c__ROS_TYPE_UINT32:
            case rosidl_typesupport_introspection_c__ROS_TYPE_INT32:
            case rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT:
                return read_uint32(buffer, buffer_size, offset, *static_cast<uint32_t*>(data));

            case rosidl_typesupport_introspection_c__ROS_TYPE_UINT64:
            case rosidl_typesupport_introspection_c__ROS_TYPE_INT64:
            case rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE:
                return read_uint64(buffer, buffer_size, offset, *static_cast<uint64_t*>(data));

            case rosidl_typesupport_introspection_c__ROS_TYPE_STRING:
            {
                rosidl_runtime_c__String* str = static_cast<rosidl_runtime_c__String*>(data);
                uint32_t length = 0;
                if (!read_uint32(buffer, buffer_size, offset, length)) {
                    return false;
                }
                if (offset + length > buffer_size) {
                    fprintf(stderr, "[ERROR] String length %u exceeds buffer\n", length);
                    return false;
                }
                // Allocate string (length includes null terminator)
                str->data = (char*)malloc(length);
                if (!str->data) {
                    fprintf(stderr, "[ERROR] Failed to allocate string\n");
                    return false;
                }
                memcpy(str->data, buffer + offset, length);
                str->size = length - 1;  // Exclude null terminator from size
                str->capacity = length;
                offset += length;
                return true;
            }

            case rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE:
            {
                const auto* sub_members = static_cast<const rosidl_typesupport_introspection_c__MessageMembers*>(
                    member->members_->data);
                return deserialize_members(buffer, buffer_size, sub_members, data, offset);
            }

            default:
                fprintf(stderr, "[ERROR] Unsupported type_id in deserialize: %u\n", member->type_id_);
                return false;
        }
    }

    // Helper functions
    size_t get_array_size(
        const void* data,
        const rosidl_typesupport_introspection_c__MessageMember* member)
    {
        if (member->array_size_) {
            return member->array_size_;
        }
        // Dynamic array
        const auto* sequence = static_cast<const rosidl_runtime_c__uint8__Sequence*>(data);
        return sequence->size;
    }

    const void* get_array_element(
        const void* data,
        const rosidl_typesupport_introspection_c__MessageMember* member,
        size_t index)
    {
        if (!member->is_array_) {
            return data;
        }

        if (member->array_size_) {
            // Fixed-size array
            return static_cast<const uint8_t*>(data) + index * member->size_of_;
        } else {
            // Dynamic array
            const auto* sequence = static_cast<const rosidl_runtime_c__uint8__Sequence*>(data);
            return sequence->data + index * member->size_of_;
        }
    }

    void* get_array_element(
        void* data,
        const rosidl_typesupport_introspection_c__MessageMember* member,
        size_t index)
    {
        return const_cast<void*>(get_array_element(const_cast<const void*>(data), member, index));
    }

    size_t align_offset(size_t offset, size_t alignment)
    {
        return (offset + alignment - 1) & ~(alignment - 1);
    }

    // Low-level read/write functions
    bool write_uint8(uint8_t* buffer, size_t buffer_size, size_t& offset, uint8_t value)
    {
        if (offset + 1 > buffer_size) return false;
        buffer[offset++] = value;
        return true;
    }

    bool write_uint16(uint8_t* buffer, size_t buffer_size, size_t& offset, uint16_t value)
    {
        offset = align_offset(offset, 2);
        if (offset + 2 > buffer_size) return false;
        memcpy(buffer + offset, &value, 2);
        offset += 2;
        return true;
    }

    bool write_uint32(uint8_t* buffer, size_t buffer_size, size_t& offset, uint32_t value)
    {
        offset = align_offset(offset, 4);
        if (offset + 4 > buffer_size) return false;
        memcpy(buffer + offset, &value, 4);
        offset += 4;
        return true;
    }

    bool write_uint64(uint8_t* buffer, size_t buffer_size, size_t& offset, uint64_t value)
    {
        offset = align_offset(offset, 8);
        if (offset + 8 > buffer_size) {
            fprintf(stderr, "[ERROR] Buffer overflow: offset+8 (%zu) > buffer_size (%zu)\n",
                    offset + 8, buffer_size);
            return false;
        }
        memcpy(buffer + offset, &value, 8);
        offset += 8;
        return true;
    }

    bool write_string(uint8_t* buffer, size_t buffer_size, size_t& offset, const char* str, size_t len)
    {
        if (!write_uint32(buffer, buffer_size, offset, static_cast<uint32_t>(len + 1))) {
            return false;
        }
        if (offset + len + 1 > buffer_size) return false;
        memcpy(buffer + offset, str, len);
        buffer[offset + len] = '\0';
        offset += len + 1;
        return true;
    }

    bool read_uint8(const uint8_t* buffer, size_t buffer_size, size_t& offset, uint8_t& value)
    {
        if (offset + 1 > buffer_size) return false;
        value = buffer[offset++];
        return true;
    }

    bool read_uint16(const uint8_t* buffer, size_t buffer_size, size_t& offset, uint16_t& value)
    {
        offset = align_offset(offset, 2);
        if (offset + 2 > buffer_size) return false;
        memcpy(&value, buffer + offset, 2);
        offset += 2;
        return true;
    }

    bool read_uint32(const uint8_t* buffer, size_t buffer_size, size_t& offset, uint32_t& value)
    {
        offset = align_offset(offset, 4);
        if (offset + 4 > buffer_size) return false;
        memcpy(&value, buffer + offset, 4);
        offset += 4;
        return true;
    }

    bool read_uint64(const uint8_t* buffer, size_t buffer_size, size_t& offset, uint64_t& value)
    {
        offset = align_offset(offset, 8);
        if (offset + 8 > buffer_size) {
            fprintf(stderr, "[ERROR] read_uint64: Buffer underflow at offset %zu\n", offset);
            return false;
        }
        memcpy(&value, buffer + offset, 8);
        offset += 8;
        return true;
    }
};

// ============================================================================
// Global Serializer Instance
// ============================================================================

static GenericCDRSerializer g_serializer;

}  // namespace typesupport
}  // namespace rmw_dsoftbus

// ============================================================================
// C API Exports
// ============================================================================

extern "C" {

bool rmw_dsoftbus_serialize_ros_message(
    const void* ros_message,
    const rosidl_message_type_support_t* type_support,
    uint8_t** cdr_buffer,
    size_t* cdr_size)
{
    if (!ros_message || !type_support || !cdr_buffer || !cdr_size) {
        return false;
    }

    std::vector<uint8_t> output;
    if (!rmw_dsoftbus::typesupport::g_serializer.serialize_message(ros_message, type_support, output)) {
        return false;
    }

    // Allocate buffer
    *cdr_buffer = static_cast<uint8_t*>(malloc(output.size()));
    if (!*cdr_buffer) {
        return false;
    }

    memcpy(*cdr_buffer, output.data(), output.size());
    *cdr_size = output.size();

    return true;
}

bool rmw_dsoftbus_deserialize_ros_message(
    const uint8_t* cdr_buffer,
    size_t cdr_size,
    const rosidl_message_type_support_t* type_support,
    void* ros_message)
{
    if (!cdr_buffer || !type_support || !ros_message) {
        return false;
    }

    return rmw_dsoftbus::typesupport::g_serializer.deserialize_message(
        cdr_buffer, cdr_size, type_support, ros_message);
}

}  // extern "C"
