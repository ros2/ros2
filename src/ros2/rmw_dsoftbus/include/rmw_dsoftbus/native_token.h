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
 * @file native_token.h
 *
 * @brief Declares native token utilities for dsoftbus authentication.
 *
 * @since 1.0
 * @version 1.0
 */
#ifndef RMW_DSOFTBUS__NATIVE_TOKEN_H_
#define RMW_DSOFTBUS__NATIVE_TOKEN_H_

namespace rmw_dsoftbus {

// Best-effort: set NativeToken for current process (OpenHarmony
// /dev/access_token_id). Returns true if token was set successfully, false
// otherwise.
bool try_init_native_token();

// Initialize native token using OpenHarmony AccessToken API
// This function uses GetAccessTokenId() and SetSelfTokenID() from nativetoken_kit.h
// Returns true if initialization succeeded, false otherwise
bool InitializeNativeToken(const char* process_name = "rmw_discovery_daemon");

} // namespace rmw_dsoftbus

#endif // RMW_DSOFTBUS__NATIVE_TOKEN_H_
