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
 * @file cdr_serializer.h
 *
 * @brief Declares CDR serializer for ROS2 message serialization.
 *
 * @since 1.0
 * @version 1.0
 */
// CDR (Common Data Representation) Serializer for rmw_dsoftbus
// Implements PLAIN_CDR (XCDRv1) encoding compatible with ROS2

#ifndef RMW_DSOFTBUS__CDR_SERIALIZER_H_
#define RMW_DSOFTBUS__CDR_SERIALIZER_H_

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>
// Note: No <stdexcept> - OpenHarmony uses -fno-exceptions

#include "rmw_dsoftbus/compat_clib.h"  // Cross-compilation C library compatibility

// Include RMW types for serialize/deserialize functions
#include "rmw/rmw.h"

namespace rmw_dsoftbus {
namespace cdr {

// CDR encapsulation header (4 bytes)
// Format: [endianness_byte, options_byte, padding1, padding2]
// Little-endian: {0x00, 0x01, 0x00, 0x00}
// Big-endian:    {0x00, 0x00, 0x00, 0x00}
constexpr uint8_t CDR_ENCAPSULATION_LE[] = {0x00, 0x01, 0x00, 0x00};
constexpr uint8_t CDR_ENCAPSULATION_BE[] = {0x00, 0x00, 0x00, 0x00};
constexpr size_t CDR_ENCAPSULATION_SIZE = 4;

// CDR alignment requirements
constexpr size_t CDR_ALIGN_1 = 1;
constexpr size_t CDR_ALIGN_2 = 2;
constexpr size_t CDR_ALIGN_4 = 4;
constexpr size_t CDR_ALIGN_8 = 8;

// Endianness detection
inline bool is_little_endian() {
    uint16_t test = 0x0001;
    return *reinterpret_cast<uint8_t*>(&test) == 0x01;
}

/**
 * CdrBuffer - A simple CDR serialization buffer
 *
 * Manages memory and position tracking for CDR serialization/deserialization.
 */
class CdrBuffer {
public:
    // Constructor for serialization (allocates buffer)
    explicit CdrBuffer(size_t initial_capacity = 256)
        : buffer_(initial_capacity), position_(0), capacity_(initial_capacity), owns_buffer_(true) {}

    // Constructor for deserialization (wraps existing data)
    CdrBuffer(const uint8_t* data, size_t size)
        : external_data_(data), position_(0), capacity_(size), owns_buffer_(false) {}

    // Get current position
    size_t position() const { return position_; }

    // Get remaining bytes
    size_t remaining() const { return capacity_ - position_; }

    // Get total capacity/size
    size_t size() const { return owns_buffer_ ? position_ : capacity_; }

    // Get buffer data
    const uint8_t* data() const {
        return owns_buffer_ ? buffer_.data() : external_data_;
    }

    // Returns nullptr if buffer is external (read-only)
    uint8_t* mutable_data() {
        if (!owns_buffer_) return nullptr;
        return buffer_.data();
    }

    // Reset position for re-reading
    void reset() { position_ = 0; }

    // Seek to position - returns false if pos > capacity
    bool seek(size_t pos) {
        if (pos > capacity_) return false;
        position_ = pos;
        return true;
    }

    // Ensure capacity for serialization - returns false if external buffer
    bool ensure_capacity(size_t additional) {
        if (!owns_buffer_) return false;
        if (position_ + additional > capacity_) {
            size_t new_cap = capacity_ * 2;
            while (new_cap < position_ + additional) new_cap *= 2;
            buffer_.resize(new_cap);
            capacity_ = new_cap;
        }
        return true;
    }

    // Get aligned position
    static size_t align(size_t pos, size_t alignment) {
        return (pos + alignment - 1) & ~(alignment - 1);
    }

    // Move to aligned position (with padding)
    void align_to(size_t alignment) {
        size_t aligned = align(position_, alignment);
        if (owns_buffer_) {
            // Serialization: pad with zeros
            ensure_capacity(aligned - position_);
            while (position_ < aligned) {
                buffer_[position_++] = 0;
            }
        } else {
            // Deserialization: just skip padding
            position_ = aligned;
        }
    }

    // Copy finalized data to output
    std::vector<uint8_t> finalize() const {
        if (owns_buffer_) {
            return std::vector<uint8_t>(buffer_.begin(), buffer_.begin() + position_);
        }
        return std::vector<uint8_t>(external_data_, external_data_ + capacity_);
    }

protected:
    std::vector<uint8_t> buffer_;
    const uint8_t* external_data_{nullptr};
    size_t position_;
    size_t capacity_;
    bool owns_buffer_;
};

/**
 * CdrSerializer - CDR encoding (serialization)
 */
class CdrSerializer : public CdrBuffer {
public:
    explicit CdrSerializer(size_t initial_capacity = 256)
        : CdrBuffer(initial_capacity), little_endian_(is_little_endian()) {}

    // Write encapsulation header (must be called first)
    void write_encapsulation() {
        const uint8_t* header = little_endian_ ? CDR_ENCAPSULATION_LE : CDR_ENCAPSULATION_BE;
        ensure_capacity(CDR_ENCAPSULATION_SIZE);
        memcpy(buffer_.data() + position_, header, CDR_ENCAPSULATION_SIZE);
        position_ += CDR_ENCAPSULATION_SIZE;
    }

    // Primitive type serialization
    void serialize(bool value) {
        ensure_capacity(1);
        buffer_[position_++] = value ? 1 : 0;
    }

    void serialize(uint8_t value) {
        ensure_capacity(1);
        buffer_[position_++] = value;
    }

    void serialize(int8_t value) {
        serialize(static_cast<uint8_t>(value));
    }

    void serialize(char value) {
        serialize(static_cast<uint8_t>(value));
    }

    void serialize(uint16_t value) {
        align_to(CDR_ALIGN_2);
        ensure_capacity(2);
        if (little_endian_) {
            buffer_[position_++] = value & 0xFF;
            buffer_[position_++] = (value >> 8) & 0xFF;
        } else {
            buffer_[position_++] = (value >> 8) & 0xFF;
            buffer_[position_++] = value & 0xFF;
        }
    }

    void serialize(int16_t value) {
        serialize(static_cast<uint16_t>(value));
    }

    void serialize(uint32_t value) {
        align_to(CDR_ALIGN_4);
        ensure_capacity(4);
        if (little_endian_) {
            buffer_[position_++] = value & 0xFF;
            buffer_[position_++] = (value >> 8) & 0xFF;
            buffer_[position_++] = (value >> 16) & 0xFF;
            buffer_[position_++] = (value >> 24) & 0xFF;
        } else {
            buffer_[position_++] = (value >> 24) & 0xFF;
            buffer_[position_++] = (value >> 16) & 0xFF;
            buffer_[position_++] = (value >> 8) & 0xFF;
            buffer_[position_++] = value & 0xFF;
        }
    }

    void serialize(int32_t value) {
        serialize(static_cast<uint32_t>(value));
    }

    void serialize(uint64_t value) {
        align_to(CDR_ALIGN_8);
        ensure_capacity(8);
        if (little_endian_) {
            for (int i = 0; i < 8; ++i) {
                buffer_[position_++] = (value >> (i * 8)) & 0xFF;
            }
        } else {
            for (int i = 7; i >= 0; --i) {
                buffer_[position_++] = (value >> (i * 8)) & 0xFF;
            }
        }
    }

    void serialize(int64_t value) {
        serialize(static_cast<uint64_t>(value));
    }

    void serialize(float value) {
        align_to(CDR_ALIGN_4);
        ensure_capacity(4);
        uint32_t bits;
        memcpy(&bits, &value, 4);
        if (little_endian_) {
            buffer_[position_++] = bits & 0xFF;
            buffer_[position_++] = (bits >> 8) & 0xFF;
            buffer_[position_++] = (bits >> 16) & 0xFF;
            buffer_[position_++] = (bits >> 24) & 0xFF;
        } else {
            buffer_[position_++] = (bits >> 24) & 0xFF;
            buffer_[position_++] = (bits >> 16) & 0xFF;
            buffer_[position_++] = (bits >> 8) & 0xFF;
            buffer_[position_++] = bits & 0xFF;
        }
    }

    void serialize(double value) {
        align_to(CDR_ALIGN_8);
        ensure_capacity(8);
        uint64_t bits;
        memcpy(&bits, &value, 8);
        if (little_endian_) {
            for (int i = 0; i < 8; ++i) {
                buffer_[position_++] = (bits >> (i * 8)) & 0xFF;
            }
        } else {
            for (int i = 7; i >= 0; --i) {
                buffer_[position_++] = (bits >> (i * 8)) & 0xFF;
            }
        }
    }

    // String serialization (CDR string = length + chars + null terminator)
    void serialize(const std::string& value) {
        uint32_t len = static_cast<uint32_t>(value.size() + 1);  // Include null terminator
        serialize(len);
        ensure_capacity(len);
        memcpy(buffer_.data() + position_, value.c_str(), len);
        position_ += len;
    }

    void serialize(const char* value) {
        serialize(std::string(value ? value : ""));
    }

    // Raw bytes serialization (for sequences, arrays)
    void serialize_raw(const void* data, size_t size) {
        ensure_capacity(size);
        memcpy(buffer_.data() + position_, data, size);
        position_ += size;
    }

    // Sequence header (just the length)
    void serialize_sequence_header(uint32_t length) {
        serialize(length);
    }

    // Array of primitives
    template<typename T>
    void serialize_array(const T* data, size_t count) {
        for (size_t i = 0; i < count; ++i) {
            serialize(data[i]);
        }
    }

    // POD struct serialization (direct memcpy with alignment)
    void serialize_pod(const void* data, size_t size, size_t alignment) {
        align_to(alignment);
        ensure_capacity(size);
        memcpy(buffer_.data() + position_, data, size);
        position_ += size;
    }

private:
    bool little_endian_;
};

/**
 * CdrDeserializer - CDR decoding (deserialization)
 */
class CdrDeserializer : public CdrBuffer {
public:
    CdrDeserializer(const uint8_t* data, size_t size)
        : CdrBuffer(data, size), little_endian_(true) {}

    // Read encapsulation header (must be called first)
    bool read_encapsulation() {
        if (remaining() < CDR_ENCAPSULATION_SIZE) return false;

        // Check encapsulation format
        // Byte 1: options (0x00 or 0x01 for little-endian)
        little_endian_ = (external_data_[position_ + 1] == 0x01);
        position_ += CDR_ENCAPSULATION_SIZE;
        return true;
    }

    // Primitive type deserialization
    bool deserialize(bool& value) {
        if (remaining() < 1) return false;
        value = external_data_[position_++] != 0;
        return true;
    }

    bool deserialize(uint8_t& value) {
        if (remaining() < 1) return false;
        value = external_data_[position_++];
        return true;
    }

    bool deserialize(int8_t& value) {
        uint8_t v;
        if (!deserialize(v)) return false;
        value = static_cast<int8_t>(v);
        return true;
    }

    bool deserialize(char& value) {
        uint8_t v;
        if (!deserialize(v)) return false;
        value = static_cast<char>(v);
        return true;
    }

    bool deserialize(uint16_t& value) {
        align_to(CDR_ALIGN_2);
        if (remaining() < 2) return false;
        if (little_endian_) {
            value = external_data_[position_] | (external_data_[position_ + 1] << 8);
        } else {
            value = (external_data_[position_] << 8) | external_data_[position_ + 1];
        }
        position_ += 2;
        return true;
    }

    bool deserialize(int16_t& value) {
        uint16_t v;
        if (!deserialize(v)) return false;
        value = static_cast<int16_t>(v);
        return true;
    }

    bool deserialize(uint32_t& value) {
        align_to(CDR_ALIGN_4);
        if (remaining() < 4) return false;
        if (little_endian_) {
            value = external_data_[position_] |
                   (external_data_[position_ + 1] << 8) |
                   (external_data_[position_ + 2] << 16) |
                   (external_data_[position_ + 3] << 24);
        } else {
            value = (external_data_[position_] << 24) |
                   (external_data_[position_ + 1] << 16) |
                   (external_data_[position_ + 2] << 8) |
                   external_data_[position_ + 3];
        }
        position_ += 4;
        return true;
    }

    bool deserialize(int32_t& value) {
        uint32_t v;
        if (!deserialize(v)) return false;
        value = static_cast<int32_t>(v);
        return true;
    }

    bool deserialize(uint64_t& value) {
        align_to(CDR_ALIGN_8);
        if (remaining() < 8) return false;
        value = 0;
        if (little_endian_) {
            for (int i = 0; i < 8; ++i) {
                value |= static_cast<uint64_t>(external_data_[position_ + i]) << (i * 8);
            }
        } else {
            for (int i = 0; i < 8; ++i) {
                value |= static_cast<uint64_t>(external_data_[position_ + i]) << ((7 - i) * 8);
            }
        }
        position_ += 8;
        return true;
    }

    bool deserialize(int64_t& value) {
        uint64_t v;
        if (!deserialize(v)) return false;
        value = static_cast<int64_t>(v);
        return true;
    }

    bool deserialize(float& value) {
        align_to(CDR_ALIGN_4);
        if (remaining() < 4) return false;
        uint32_t bits;
        if (little_endian_) {
            bits = external_data_[position_] |
                  (external_data_[position_ + 1] << 8) |
                  (external_data_[position_ + 2] << 16) |
                  (external_data_[position_ + 3] << 24);
        } else {
            bits = (external_data_[position_] << 24) |
                  (external_data_[position_ + 1] << 16) |
                  (external_data_[position_ + 2] << 8) |
                  external_data_[position_ + 3];
        }
        position_ += 4;
        memcpy(&value, &bits, 4);
        return true;
    }

    bool deserialize(double& value) {
        align_to(CDR_ALIGN_8);
        if (remaining() < 8) return false;
        uint64_t bits = 0;
        if (little_endian_) {
            for (int i = 0; i < 8; ++i) {
                bits |= static_cast<uint64_t>(external_data_[position_ + i]) << (i * 8);
            }
        } else {
            for (int i = 0; i < 8; ++i) {
                bits |= static_cast<uint64_t>(external_data_[position_ + i]) << ((7 - i) * 8);
            }
        }
        position_ += 8;
        memcpy(&value, &bits, 8);
        return true;
    }

    // String deserialization
    bool deserialize(std::string& value) {
        uint32_t len;
        if (!deserialize(len)) return false;
        if (len == 0) {
            value.clear();
            return true;
        }
        if (remaining() < len) return false;
        // len includes null terminator
        value.assign(reinterpret_cast<const char*>(external_data_ + position_), len - 1);
        position_ += len;
        return true;
    }

    // Raw bytes deserialization
    bool deserialize_raw(void* data, size_t size) {
        if (remaining() < size) return false;
        memcpy(data, external_data_ + position_, size);
        position_ += size;
        return true;
    }

    // Sequence header
    bool deserialize_sequence_header(uint32_t& length) {
        return deserialize(length);
    }

    // Array of primitives
    template<typename T>
    bool deserialize_array(T* data, size_t count) {
        for (size_t i = 0; i < count; ++i) {
            if (!deserialize(data[i])) return false;
        }
        return true;
    }

    // POD struct deserialization (direct memcpy with alignment)
    bool deserialize_pod(void* data, size_t size, size_t alignment) {
        align_to(alignment);
        if (remaining() < size) return false;
        memcpy(data, external_data_ + position_, size);
        position_ += size;
        return true;
    }

private:
    bool little_endian_;
};

// Helper functions for size calculation

// Calculate CDR serialized size for a string
inline size_t cdr_string_size(const std::string& str, size_t current_pos) {
    // Align to 4 for length field
    size_t aligned_pos = CdrBuffer::align(current_pos, CDR_ALIGN_4);
    // 4 bytes for length + string data + null terminator
    return (aligned_pos - current_pos) + 4 + str.size() + 1;
}

// Calculate CDR serialized size for primitive types
template<typename T>
inline size_t cdr_primitive_size(size_t current_pos) {
    size_t alignment = sizeof(T) >= 8 ? CDR_ALIGN_8 :
                       sizeof(T) >= 4 ? CDR_ALIGN_4 :
                       sizeof(T) >= 2 ? CDR_ALIGN_2 : CDR_ALIGN_1;
    size_t aligned_pos = CdrBuffer::align(current_pos, alignment);
    return (aligned_pos - current_pos) + sizeof(T);
}

/**
 * Serialize a ROS message to CDR format.
 *
 * @param ros_message The ROS message to serialize
 * @param type_support The message type support
 * @param serialized_message Output buffer for serialized data
 * @return true on success, false on failure
 */
bool serialize_message(
    const void* ros_message,
    const rosidl_message_type_support_t* type_support,
    rmw_serialized_message_t* serialized_message);

/**
 * Deserialize a CDR message to a ROS message.
 *
 * @param serialized_message The serialized CDR data
 * @param type_support The message type support
 * @param ros_message Output ROS message (must be pre-allocated)
 * @return true on success, false on failure
 */
bool deserialize_message(
    const rmw_serialized_message_t* serialized_message,
    const rosidl_message_type_support_t* type_support,
    void* ros_message);

/**
 * Get the serialized size of a ROS message in CDR format.
 *
 * @param ros_message The ROS message
 * @param type_support The message type support
 * @return The serialized size, or 0 if unknown
 */
size_t get_serialized_size(
    const void* ros_message,
    const rosidl_message_type_support_t* type_support);

/**
 * Serialize a message to CDR format buffer.
 *
 * @param ros_message The ROS message to serialize
 * @param type_support The message type support
 * @param output Output vector for serialized data
 * @return true on success, false on failure
 */
bool serialize_message_to_buffer(
    const void* ros_message,
    const rosidl_message_type_support_t* type_support,
    std::vector<uint8_t>& output);

/**
 * Deserialize a CDR buffer to a ROS message.
 *
 * @param data The CDR data buffer
 * @param size The buffer size
 * @param type_support The message type support
 * @param ros_message Output ROS message (must be pre-allocated)
 * @return true on success, false on failure
 */
bool deserialize_buffer_to_message(
    const uint8_t* data,
    size_t size,
    const rosidl_message_type_support_t* type_support,
    void* ros_message);

}  // namespace cdr
}  // namespace rmw_dsoftbus

#endif  // RMW_DSOFTBUS__CDR_SERIALIZER_H_
