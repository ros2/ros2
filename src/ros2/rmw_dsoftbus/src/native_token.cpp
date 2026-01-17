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

// Copyright (c) 2024 ROS2 KaihongOS Port Project
#include <string.h>  /* C memcpy/memset for OHOS SDK compatibility */
#include <stdlib.h>

// Licensed under the Apache License, Version 2.0

#include "rmw_dsoftbus/native_token.h"

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <mutex>

#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <dlfcn.h>

// OpenHarmony AccessToken APIs
extern "C" {
  // From nativetoken_kit.h
  typedef struct {
    int32_t dcapsNum;
    int32_t permsNum;
    int32_t aclsNum;
    const char** dcaps;
    const char** perms;
    const char** acls;
    const char* processName;
    const char* aplStr;  // "system_core", "system_basic", or "normal"
  } NativeTokenInfoParams;

  // Function pointers for dynamically loaded symbols
  typedef uint64_t (*GetAccessTokenId_t)(NativeTokenInfoParams*);
  typedef int (*SetSelfTokenID_t)(uint64_t);
  typedef int (*ReloadNativeTokenInfo_t)();

  static GetAccessTokenId_t _GetAccessTokenId = nullptr;
  static SetSelfTokenID_t _SetSelfTokenID = nullptr;
  static ReloadNativeTokenInfo_t _ReloadNativeTokenInfo = nullptr;

  // Load NativeToken API via dlopen
  static bool load_nativetoken_api() {
    static bool attempted = false;
    static bool loaded = false;

    if (attempted) {
      return loaded;
    }
    attempted = true;

    fprintf(stderr, "[NativeToken API] Loading AccessToken libraries...\n");

    // Try multiple paths for token libraries (prioritize chipset-pub-sdk)
    const char* lib_paths[] = {
      "/system/lib64/chipset-pub-sdk/libaccesstoken_sdk.z.so",
      "/system/lib64/platformsdk/libaccesstoken_sdk.z.so",
      "/system/lib64/libtokenid_sdk.z.so",
      "/system/lib64/platformsdk/libtokenid_sdk.z.so"
    };

    void* handle_native = nullptr;
    for (const char* path : lib_paths) {
      handle_native = dlopen(path, RTLD_NOW | RTLD_GLOBAL);
      if (handle_native) {
        fprintf(stderr, "[NativeToken API] Loaded: %s\n", path);
        break;
      }
    }

    if (!handle_native) {
      fprintf(stderr, "[NativeToken API] ❌ No token library found, tried:\n");
      for (const char* path : lib_paths) {
        fprintf(stderr, "  - %s\n", path);
      }
      fprintf(stderr, "[NativeToken API] Last error: %s\n", dlerror());
      return false;
    }

    _GetAccessTokenId = (GetAccessTokenId_t)dlsym(handle_native, "GetAccessTokenId");
    _SetSelfTokenID = (SetSelfTokenID_t)dlsym(handle_native, "SetSelfTokenID");

    if (!_GetAccessTokenId || !_SetSelfTokenID) {
      fprintf(stderr, "[NativeToken API] ❌ Required symbols not found in library\n");
      fprintf(stderr, "  GetAccessTokenId: %p\n", (void*)_GetAccessTokenId);
      fprintf(stderr, "  SetSelfTokenID: %p\n", (void*)_SetSelfTokenID);
      dlclose(handle_native);
      return false;
    }

    fprintf(stderr, "[NativeToken API] ✅ AVAILABLE: GetAccessTokenId=%p SetSelfTokenID=%p\n",
            (void*)_GetAccessTokenId, (void*)_SetSelfTokenID);
    loaded = true;
    return true;
  }

  // Wrappers that call dynamically loaded functions
  uint64_t GetAccessTokenId(NativeTokenInfoParams* tokenInfo) {
    if (!_GetAccessTokenId) {
      load_nativetoken_api();
    }
    if (_GetAccessTokenId) {
      return _GetAccessTokenId(tokenInfo);
    }
    return 0;
  }

  int SetSelfTokenID(uint64_t tokenId) {
    if (!_SetSelfTokenID) {
      load_nativetoken_api();
    }
    if (_SetSelfTokenID) {
      return _SetSelfTokenID(tokenId);
    }
    return -1;
  }
}

namespace rmw_dsoftbus {

namespace {

constexpr const char *kTokenIdDevnode = "/dev/access_token_id";
constexpr uint64_t kDefaultTokenId = 671463243ULL;  // Token ID for com.huawei.ros2_rmw_dsoftbus from nativetoken.json

constexpr char kAccessTokenIdIoctlBase = 'A';
constexpr unsigned int kGetTokenId = 1;
constexpr unsigned int kSetTokenId = 2;
constexpr unsigned int kSetFirstTokenId = 4;

constexpr unsigned long access_tokenid_get_tokenid =
    _IOR(kAccessTokenIdIoctlBase, kGetTokenId, uint64_t);
constexpr unsigned long access_tokenid_set_tokenid =
    _IOW(kAccessTokenIdIoctlBase, kSetTokenId, uint64_t);
constexpr unsigned long access_tokenid_set_ftokenid =
    _IOW(kAccessTokenIdIoctlBase, kSetFirstTokenId, uint64_t);

bool is_truthy(const char *value) {
  if (!value || value[0] == '\0') {
    return false;
  }
  return strcmp(value, "1") == 0 || strcmp(value, "true") == 0 ||
         strcmp(value, "TRUE") == 0 || strcmp(value, "yes") == 0 ||
         strcmp(value, "YES") == 0;
}

bool parse_token_id_env(const char *value, uint64_t *token_id_out) {
  if (!token_id_out) {
    return false;
  }
  if (!value || value[0] == '\0') {
    return false;
  }

  errno = 0;
  char *end = nullptr;
  unsigned long long parsed = strtoull(value, &end, 0);
  if (errno != 0 || !end || *end != '\0' || parsed == 0ULL) {
    return false;
  }

  *token_id_out = static_cast<uint64_t>(parsed);
  return true;
}

} // namespace

bool try_init_native_token() {
  static std::mutex mutex;
  static bool attempted = false;
  static bool initialized = false;

  std::lock_guard<std::mutex> lock(mutex);

  if (attempted) {
    return initialized;
  }
  attempted = true;

  const char *disable_env = std::getenv("RMW_DSOFTBUS_DISABLE_NATIVE_TOKEN");
  if (is_truthy(disable_env)) {
    return false;
  }

  uint64_t token_id = kDefaultTokenId;
  bool token_id_from_env = false;

  const char *token_env = std::getenv("RMW_DSOFTBUS_TOKEN_ID");
  if (token_env && token_env[0] != '\0') {
    if (!parse_token_id_env(token_env, &token_id)) {
      fprintf(stderr,
              "[rmw_dsoftbus] NativeToken: invalid RMW_DSOFTBUS_TOKEN_ID='%s' "
              "(expected integer)\n",
              token_env);
      return false;
    }
    token_id_from_env = true;
  }

  if (getuid() != 0 && !token_id_from_env) {
    return false;
  }

  int fd = open(kTokenIdDevnode, O_RDWR);
  if (fd < 0) {
    if (token_id_from_env || getuid() == 0) {
      fprintf(stderr,
              "[rmw_dsoftbus] NativeToken: open(%s) failed: errno=%d (%s)\n",
              kTokenIdDevnode, errno, strerror(errno));
    }
    return false;
  }

  int ret = ioctl(fd, access_tokenid_set_tokenid, &token_id);
  if (ret != 0) {
    fprintf(stderr,
            "[rmw_dsoftbus] NativeToken: ioctl(SET_TOKENID) failed: ret=%d "
            "errno=%d (%s)\n",
            ret, errno, strerror(errno));
    close(fd);
    return false;
  }

  // Best-effort: also set first caller token ID so IPC chains preserve
  // identity.
  (void)ioctl(fd, access_tokenid_set_ftokenid, &token_id);

  uint64_t verify = 0;
  if (ioctl(fd, access_tokenid_get_tokenid, &verify) == 0) {
    fprintf(stderr,
            "[rmw_dsoftbus] NativeToken: set token_id=%llu (verify=%llu)\n",
            static_cast<unsigned long long>(token_id),
            static_cast<unsigned long long>(verify));
  } else {
    fprintf(stderr,
            "[rmw_dsoftbus] NativeToken: set token_id=%llu (verify failed "
            "errno=%d)\n",
            static_cast<unsigned long long>(token_id), errno);
  }

  close(fd);
  initialized = true;
  return true;
}

// Initialize native token using OpenHarmony AccessToken API
bool InitializeNativeToken(const char* process_name) {
  static std::mutex mutex;
  static bool attempted = false;
  static bool initialized = false;

  std::lock_guard<std::mutex> lock(mutex);

  if (attempted) {
    return initialized;
  }
  attempted = true;

  if (!process_name || process_name[0] == '\0') {
    fprintf(stderr, "[rmw_dsoftbus] InitializeNativeToken: process_name is empty\n");
    return false;
  }

  // Define required permissions for DSoftBus Session operations
  const char* perms[] = {
      "ohos.permission.DISTRIBUTED_DATASYNC",
      "ohos.permission.DISTRIBUTED_SOFTBUS_CENTER",
      "ohos.permission.ACCESS_SERVICE_DM"
  };

  const char* acls[] = {
      "ohos.permission.DISTRIBUTED_DATASYNC"
  };

  NativeTokenInfoParams params = {
      .dcapsNum = 0,
      .permsNum = 3,
      .aclsNum = 1,
      .dcaps = nullptr,
      .perms = perms,
      .acls = acls,
      .processName = process_name,
      .aplStr = "system_core",  // APL=3: system core service level
  };

  // Step 1: Acquire AccessToken ID
  uint64_t tokenId = GetAccessTokenId(&params);
  if (tokenId == 0) {
    fprintf(stderr,
            "[rmw_dsoftbus] InitializeNativeToken: GetAccessTokenId() failed "
            "for process '%s'\n",
            process_name);
    return false;
  }

  fprintf(stderr,
          "[rmw_dsoftbus] InitializeNativeToken: acquired tokenId=%llu for "
          "process '%s'\n",
          static_cast<unsigned long long>(tokenId), process_name);

  // Step 2: Apply token to current process
  int ret = SetSelfTokenID(tokenId);
  if (ret != 0) {
    fprintf(stderr,
            "[rmw_dsoftbus] InitializeNativeToken: SetSelfTokenID(%llu) "
            "failed: ret=%d\n",
            static_cast<unsigned long long>(tokenId), ret);
    return false;
  }

  fprintf(stderr,
          "[rmw_dsoftbus] InitializeNativeToken: SetSelfTokenID() succeeded\n");

  // Step 3: Reload token info in AccessToken Manager (best-effort)
  if (_ReloadNativeTokenInfo) {
    ret = _ReloadNativeTokenInfo();
    if (ret != 0) {
      fprintf(stderr,
              "[rmw_dsoftbus] InitializeNativeToken: ReloadNativeTokenInfo() "
              "returned %d (non-fatal)\n",
              ret);
    } else {
      fprintf(stderr,
              "[rmw_dsoftbus] InitializeNativeToken: ReloadNativeTokenInfo() "
              "succeeded\n");
    }
  }

  initialized = true;
  return true;
}

} // namespace rmw_dsoftbus
