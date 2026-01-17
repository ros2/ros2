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

#ifndef RMW_DSOFTBUS__DSOFTBUS_SESSION_H_
#define RMW_DSOFTBUS__DSOFTBUS_SESSION_H_

#include <cstdint>

// OpenHarmony dsoftbus session interface definitions
// When RMW_DSOFTBUS_USE_REAL_SOFTBUS is defined, use real dsoftbus headers
// Otherwise, use stub definitions for compilation without dsoftbus SDK

#ifdef RMW_DSOFTBUS_USE_REAL_SOFTBUS
// Use real dsoftbus headers - include them here for convenience
#include "transport/session.h"
#include "transport/socket.h"
#include "transport/trans_type.h"
#include "bus_center/softbus_bus_center.h"
#include "common/softbus_error_code.h"
#else
// Stub mode: define minimal types for compilation without dsoftbus SDK

#ifdef __cplusplus
extern "C" {
#endif

// NOTE:
// This header is used together with a dlopen() shim that calls the real
// libsoftbus_client at runtime. The ABI (enum values / struct layouts) MUST
// match OpenHarmony's official headers, otherwise OpenSession/CreateSession may
// fail with non-obvious transport errors.

// Session data type (must match transport/session.h)
typedef enum {
    TYPE_MESSAGE = 1,
    TYPE_BYTES,
    TYPE_FILE,
    TYPE_STREAM,
    TYPE_BUTT,
} SessionType;

// Stream type (must match transport/session.h)
typedef enum {
    INVALID = -1,
    RAW_STREAM,
    COMMON_VIDEO_STREAM,
    COMMON_AUDIO_STREAM,
    VIDEO_SLICE_STREAM,
} StreamType;

// Link type (must match transport/session.h)
typedef enum {
    LINK_TYPE_WIFI_WLAN_5G = 1,
    LINK_TYPE_WIFI_WLAN_2G = 2,
    LINK_TYPE_WIFI_P2P = 3,
    LINK_TYPE_BR = 4,
    LINK_TYPE_BLE = 5,
    LINK_TYPE_WIFI_P2P_REUSE = 6,
    LINK_TYPE_BLE_DIRECT = 7,
    LINK_TYPE_COC = 8,
    LINK_TYPE_COC_DIRECT = 9,
    LINK_TYPE_ETH = 10,
    LINK_TYPE_SLE = 11,
    LINK_TYPE_KHPLC = 12,
    LINK_TYPE_MAX = 13,
} LinkType;

// Opaque transport structs (only used as pointers in callbacks)
typedef struct StreamData StreamData;
typedef struct StreamFrameInfo StreamFrameInfo;
typedef struct QosTv QosTv;

// Session attribute (must match transport/session.h)
typedef struct {
    int dataType;
    int linkTypeNum;
    LinkType linkType[LINK_TYPE_MAX];
    union {
        struct StreamAttr {
            int streamType;
        } streamAttr;
        struct BytesAttr {
            int encryptType;
        } bytesAttr;
        struct StreamAttrEx {
            int streamType;
            int encryptType;
        } streamAttrEx;
    } attr;
    uint8_t *fastTransData;
    uint16_t fastTransDataSize;
} SessionAttribute;

// Session listener callbacks
typedef struct {
    int (*OnSessionOpened)(int sessionId, int result);
    void (*OnSessionClosed)(int sessionId);
    void (*OnBytesReceived)(int sessionId, const void *data, unsigned int dataLen);
    void (*OnMessageReceived)(int sessionId, const void *data, unsigned int dataLen);
    void (*OnStreamReceived)(int sessionId, const StreamData *data, const StreamData *ext,
                             const StreamFrameInfo *param);
    void (*OnQosEvent)(int sessionId, int eventId, int tvCount, const QosTv *tvList);
} ISessionListener;

// Publish callback
typedef struct {
    void (*OnPublishResult)(int publishId, int reason);
} IPublishCb;

// Discovery callback
typedef struct {
    void (*OnDeviceFound)(const void *device);
    void (*OnDiscoverResult)(int subscribeId, int reason);
} IDiscoveryCb;

// Basic constants (must match SoftBus headers)
#ifndef NETWORK_ID_BUF_LEN
#define NETWORK_ID_BUF_LEN 65
#endif
#ifndef DEVICE_NAME_BUF_LEN
#define DEVICE_NAME_BUF_LEN 128
#endif
#ifndef OS_VERSION_BUF_LEN
#define OS_VERSION_BUF_LEN 128
#endif

// Node basic info (must match bus_center/softbus_bus_center.h)
typedef struct {
    char networkId[NETWORK_ID_BUF_LEN];
    char deviceName[DEVICE_NAME_BUF_LEN];
    uint16_t deviceTypeId;
    int32_t osType;
    char osVersion[OS_VERSION_BUF_LEN];
} NodeBasicInfo;

// Return codes
#define SOFTBUS_OK 0
#define SOFTBUS_ERR (-1)
#define SOFTBUS_INVALID_PARAM (-2)
#define SOFTBUS_NO_INIT (-3)

// Session API function declarations (stubs implemented in dsoftbus_stubs.cpp)
int CreateSessionServer(const char *pkgName, const char *sessionName, const ISessionListener *listener);
int RemoveSessionServer(const char *pkgName, const char *sessionName);
int OpenSession(const char *mySessionName, const char *peerSessionName, const char *peerNetworkId,
                const char *groupId, const SessionAttribute* attr);
void CloseSession(int sessionId);
int SendBytes(int sessionId, const void *data, unsigned int len);
int SendMessage(int sessionId, const void *data, unsigned int len);

// Device discovery API function declarations (stubs implemented in dsoftbus_stubs.cpp)
int GetLocalNodeDeviceInfo(const char *pkgName, NodeBasicInfo *info);
int GetAllNodeDeviceInfo(const char *pkgName, NodeBasicInfo **nodeInfo, int32_t *infoNum);
void FreeNodeInfo(NodeBasicInfo *nodeInfo);

// Session info query functions (for inbound session tracking)
// These are essential for tracking inbound sessions opened by remote devices
int GetPeerDeviceId(int sessionId, char *peerNetworkId, unsigned int len);
int GetPeerSessionName(int sessionId, char *sessionName, unsigned int len);
int GetSessionSide(int sessionId);  // Returns: 0=server (inbound), 1=client (outbound)
int GetMySessionName(int sessionId, char *sessionName, unsigned int len);

#ifdef __cplusplus
}
#endif

#endif  // RMW_DSOFTBUS_USE_REAL_SOFTBUS

#endif  // RMW_DSOFTBUS__DSOFTBUS_SESSION_H_
