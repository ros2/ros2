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

#ifndef RMW_DSOFTBUS__VISIBILITY_H_
#define RMW_DSOFTBUS__VISIBILITY_H_

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32)
  #define RMW_DSOFTBUS_EXPORT __declspec(dllexport)
  #define RMW_DSOFTBUS_IMPORT __declspec(dllimport)
#else
  #define RMW_DSOFTBUS_EXPORT __attribute__((visibility("default")))
  #define RMW_DSOFTBUS_IMPORT
#endif

#ifdef RMW_DSOFTBUS_BUILDING_LIBRARY
  #define RMW_DSOFTBUS_PUBLIC RMW_DSOFTBUS_EXPORT
#else
  #define RMW_DSOFTBUS_PUBLIC RMW_DSOFTBUS_IMPORT
#endif

#define RMW_DSOFTBUS_LOCAL __attribute__((visibility("hidden")))

#ifdef __cplusplus
}
#endif

#endif  // RMW_DSOFTBUS__VISIBILITY_H_
