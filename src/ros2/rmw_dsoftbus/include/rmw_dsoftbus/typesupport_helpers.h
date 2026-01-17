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

// Copyright 2026 The rmw_dsoftbus Authors
// Licensed under the Apache License, Version 2.0

#ifndef RMW_DSOFTBUS__TYPESUPPORT_HELPERS_H_
#define RMW_DSOFTBUS__TYPESUPPORT_HELPERS_H_

#include <cstring>

namespace rmw_dsoftbus {

/// Supported typesupport identifiers (introspection variants only)
///
/// We only support introspection variants because:
/// 1. They provide member layout information at runtime
/// 2. Callback variants have different struct layouts (not ABI stable)
/// 3. Forcing parse of callback variants would cause SIGSEGV
///
/// Unsupported variants will return RMW_RET_UNSUPPORTED.

constexpr const char* INTROSPECTION_C_IDENTIFIER = "rosidl_typesupport_introspection_c";
constexpr const char* INTROSPECTION_CPP_IDENTIFIER = "rosidl_typesupport_introspection_cpp";

/// Check if a typesupport identifier is an introspection variant
///
/// @param identifier The typesupport identifier string
/// @return true if this is an introspection variant we can safely parse
inline bool is_introspection_typesupport(const char* identifier) {
    if (!identifier) {
        return false;
    }

    // Check for introspection_c
    if (std::strstr(identifier, "introspection_c") != nullptr) {
        return true;
    }

    // Check for introspection_cpp
    if (std::strstr(identifier, "introspection_cpp") != nullptr) {
        return true;
    }

    return false;
}

/// Check if a typesupport identifier is C introspection variant
///
/// @param identifier The typesupport identifier string
/// @return true if this is rosidl_typesupport_introspection_c
inline bool is_introspection_c_typesupport(const char* identifier) {
    if (!identifier) {
        return false;
    }
    return std::strstr(identifier, "introspection_c") != nullptr &&
           std::strstr(identifier, "introspection_cpp") == nullptr;
}

/// Check if a typesupport identifier is C++ introspection variant
///
/// @param identifier The typesupport identifier string
/// @return true if this is rosidl_typesupport_introspection_cpp
inline bool is_introspection_cpp_typesupport(const char* identifier) {
    if (!identifier) {
        return false;
    }
    return std::strstr(identifier, "introspection_cpp") != nullptr;
}

/// Get a human-readable name for the typesupport variant
///
/// @param identifier The typesupport identifier string
/// @return Human-readable variant name
inline const char* get_typesupport_variant_name(const char* identifier) {
    if (!identifier) {
        return "null";
    }
    if (is_introspection_cpp_typesupport(identifier)) {
        return "introspection_cpp";
    }
    if (is_introspection_c_typesupport(identifier)) {
        return "introspection_c";
    }
    if (std::strstr(identifier, "rosidl_typesupport_cpp") != nullptr) {
        return "callback_cpp (unsupported)";
    }
    if (std::strstr(identifier, "rosidl_typesupport_c") != nullptr) {
        return "callback_c (unsupported)";
    }
    return "unknown";
}

}  // namespace rmw_dsoftbus

#endif  // RMW_DSOFTBUS__TYPESUPPORT_HELPERS_H_
