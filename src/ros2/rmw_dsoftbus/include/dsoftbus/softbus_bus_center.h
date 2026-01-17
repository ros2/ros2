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

/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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
 * @addtogroup SoftBus
 * @{
 *
 * @brief Provides high-speed, secure communication between devices.
 *
 * This module implements unified distributed communication capability management between nearby devices, and provides
 * link-independent device discovery and transmission interfaces to support service publishing and data transmission.
 *
 * @since 1.0
 * @version 1.0
 */
/** @} */

/**
 * @file softbus_bus_center.h
 *
 * @brief Declares functions and constants for the bus center of the Intelligent Soft Bus.
 *
 * The functions are used to perform
 * the following operations: \n
 * <ul>
 * <li>Adding a device to and removing a device from a LNN</li>
 * <li>Listening for device online, offline, and information change events</li>
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef SOFTBUS_BUS_CENTER_H
#define SOFTBUS_BUS_CENTER_H

#include <stdbool.h>
#include <stdint.h>

#include "softbus_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Indicates the length of a device name buffer, including the terminating null character <b>\0</b>.
 *
 * @since 1.0
 * @version 1.0
 */
#define DEVICE_NAME_BUF_LEN 128

/**
 * @brief Indicates the mask bit for a device online event.
 * If you want to receive such events, set the mask bit in {@link INodeStateCb.events}.
 *
 * @since 1.0
 * @version 1.0
 */
#define EVENT_NODE_STATE_ONLINE 0x1

/**
 * @brief Indicates the mask bit for a device offline event.
 * If you want to receive such events, set the mask bit in {@link INodeStateCb.events}.
 *
 * @since 1.0
 * @version 1.0
 */
#define EVENT_NODE_STATE_OFFLINE 0x02

/**
 * @brief Indicates the mask bit for a peer device information change event.
 * If you want to receive such events, set the mask bit in {@link INodeStateCb.events}.
 *
 * @since 1.0
 * @version 1.0
 */
#define EVENT_NODE_STATE_INFO_CHANGED 0x04

/**
 * @brief Indicates the mask bit for a LNN node running status change event.
 * If you want to receive such events, set the mask bit in {@link INodeStateCb.events}.
 *
 * @since 1.0
 * @version 1.0
 */
#define EVENT_NODE_STATUS_CHANGED 0x08

/**
 * @brief Indicates the mask bit for a LNN node network status change event.
 * If you want to receive such events, set the mask bit in {@link INodeStateCb.events}.
 *
 * @since 1.0
 * @version 1.0
 */
#define EVENT_NODE_STATE_NETWORK_CHANGED 0x10

/**
 * @brief Indicates mask bits for {@link INodeStateCb.events}.
 *
 * @since 1.0
 * @version 1.0
 */
#define EVENT_NODE_STATE_MASK 0xF

/**
 * @brief The maximum length of meta node bypass info {@link MetaNodeConfigInfo.bypassInfo}.
 *
 * @since 1.0
 * @version 1.0
 */
#define META_NODE_BYPASS_INFO_LEN 64

/**
 * @brief Indicates the maximum length of the callerId, including the terminating null character <b>\0</b>.
 *
 * @since 1.0
 * @version 1.0
 */
#define CALLER_ID_MAX_LEN 128

/**
 * @brief Indicates the maximum length of the custom user data.
 *
 * @since 1.0
 * @version 1.0
 */
#define USER_DATA_MAX_LEN 256

/**
 * @brief The maximum of meta node {@link MetaNodeConfigInfo.bypassInfo}.
 *
 * @since 1.0
 * @version 1.0
 */
#define MAX_META_NODE_NUM 3

/**
 * @brief Indicates the length of os version buffer, including the terminating null character <b>\0</b>.
 *
 * @since 1.0
 * @version 1.0
 */
#define OS_VERSION_BUF_LEN 128

/**
 * @brief Enumerates keys for an online device.
 * The key can be obtained via {@link GetNodeKeyInfo}.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    NODE_KEY_UDID = 0,    /**< UDID in string format*/
    NODE_KEY_UUID,        /**< UUID in string format */
    NODE_KEY_MASTER_UDID, /**< UDID of device in string format */
    NODE_KEY_BR_MAC,      /**< BR MAC in string format */
    NODE_KEY_SLE_MAC,    /**< SLE MAC in uint8 format */
    NODE_KEY_IP_ADDRESS,  /**< IP address in string format */
    NODE_KEY_DEV_NAME,    /**< Device name in string format */
    NODE_KEY_NETWORK_CAPABILITY, /**< Network capability in number format */
    NODE_KEY_NETWORK_TYPE,       /**< Network type in number format */
    NODE_KEY_BLE_OFFLINE_CODE,   /**< Ble offlinecode in string format */
    NODE_KEY_DATA_CHANGE_FLAG,   /**< Device info change flag in number format */
    NODE_KEY_NODE_ADDRESS,       /**< Node address in string format */
    NODE_KEY_P2P_IP_ADDRESS,     /**<  P2P IP address in string format */
    NODE_KEY_KHPLC_MAC,          /**< Add by c000398 from kaihong Plc project PLC MAC in string format */
    NODE_KEY_SERIAL_NUMBER = 20,   /**< KH device serial number in string format */
} NodeDeviceInfoKey;

/**
 * @brief Enumerates supported network capabilities.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    BIT_BLE = 0,    /**< Support BLE */
    BIT_BR,         /**< Support BR */
    BIT_WIFI,       /**< Support WIFI */
    BIT_WIFI_P2P,   /**< Support WIFI P2P */
    BIT_WIFI_24G,   /**< Support WIFI 2.4G */
    BIT_WIFI_5G,    /**< Support WIFI 5G */
    BIT_ETH,        /**< Support ETH */
    BIT_SLE,        /**< Support SLE */
    BIT_KHPLC,      /**< Support KHPLC Add by c000398 from kaihong Plc project */
    BIT_COUNT,      /**< Invalid type */
} NetCapability;

/**
 * @brief Enumerates network types for an online device.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    BIT_NETWORK_TYPE_UNKNOWN = 0,  /**< Unknown network type */
    BIT_NETWORK_TYPE_WIFI,         /**< WIFI network type */
    BIT_NETWORK_TYPE_BLE,          /**< BLE network type */
    BIT_NETWORK_TYPE_BR,           /**< BR network type */
    BIT_NETWORK_TYPE_P2P,          /**< P2P network type */
    BIT_NETWORK_TYPE_KHPLC,        /**< KHPLC network type Add by c000398 from kaihong Plc project */
    BIT_NETWORK_TYPE_COUNT,        /**< Invalid type */
} NetworkType;

/**
 * @brief Enumerates accuracy for time synchronize among device.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    LOW_ACCURACY = 0,              /**< Low accuracy */
    NORMAL_ACCURACY,               /**< Normal accuracy */
    HIGH_ACCURACY,                 /**< High accuracy */
    SUPER_HIGH_ACCURACY,           /**< Super high accuracy */
    UNAVAIL_ACCURACY = 0xFFFF,     /**< Invalid accuracy */
} TimeSyncAccuracy;

/**
 * @brief Enumerates time synchronize period among device.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    SHORT_PERIOD = 0,  /**< Short accuracy */
    NORMAL_PERIOD,     /**< Normal accuracy */
    LONG_PERIOD,       /**< Long accuracy */
} TimeSyncPeriod;

/**
 * @brief Enumerates time synchronize flag.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    NODE_SPECIFIC = 0,  /**< Time sync in a specific mode */
    ALL_LNN,            /**< Time sync during the entire networking */
    WRITE_RTC,          /**< Write RTC synchronization */
} TimeSyncFlag;

/**
 * @brief Defines the basic information of a device.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    char networkId[NETWORK_ID_BUF_LEN];    /**< Device network id */
    char deviceName[DEVICE_NAME_BUF_LEN];  /**< Device name */
    uint16_t deviceTypeId;                 /**< Device type id */
    int32_t osType;                        /**< Os type */
    char osVersion[OS_VERSION_BUF_LEN];    /**< Os version */
} NodeBasicInfo;

/**
 * @brief Enumerates device information change types. For details, see {@link INodeStateCb.onNodeBasicInfoChanged}.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    TYPE_NETWORK_ID = 0,  /**< Network ID change */
    TYPE_DEVICE_NAME,     /**< Device name change */
    TYPE_NETWORK_INFO,    /**< Device network info change */
} NodeBasicInfoType;

/**
 * @brief Defines the running status about a device.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    NodeBasicInfo basicInfo;     /**< The basic info of device */
    uint16_t authStatus;         /**< The auth state of device */
    uint16_t dataBaseStatus;     /**< The data base state of device */
    uint16_t meshType;           /**< The mesh type of device */
    uint16_t reserved[NODE_STATUS_MAX_NUM - 3];  /**< The reserved data of device */
} NodeStatus;

/**
 * @brief Enumerates device information change types. For details, see {@link INodeStateCb.onNodeStatusChanged}.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    TYPE_AUTH_STATUS = 2,     /**< Certify status change */
    TYPE_DATABASE_STATUS = 3, /**< Database  change */
    TYPE_MESH_TYPE = 4,       /**< Lnn mesh typechange */
    TYPE_STATUS_MAX = 5,      /**< Max num */
} NodeStatusType;

typedef struct {
    ConnectionAddrType type;          // 地址类型
    /**< Connection address information */
    union {
        /**< BR address */
        KhBrAddr br;
        /**< BLE address */
        KhBleAddr ble;
        /**< IPv4 or IPv6 address */
        KhIpAddr ip;
        //Add by c000398 from kaihong Plc project
        KhPlcMacAddress KhPlcMac;
    } linkInfo;
} KhDeviceNodeAddr;

/**
 * @brief Defines time synchronize result.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    int32_t millisecond;        /**< Number of milli second */
    int32_t microsecond;        /**< Number of micro second */
    TimeSyncAccuracy accuracy;  /**< Time sync accuracy */
} TimeSyncResult;

/**
 * @brief Defines time synchronize result info.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    TimeSyncResult result;    /**< Time synchronize result */
    TimeSyncFlag flag;        /**< Time synchronize flag */
    union {
        char targetNetworkId[NETWORK_ID_BUF_LEN];  /**< The network id of time sync target device */
        char masterNetworkId[NETWORK_ID_BUF_LEN];  /**< The network id of node */
    } target;
} TimeSyncResultInfo;

/**
 * @brief Enumerates error codes for service publishing failures.
 *
 * The error codes are returned to the caller through <b>IPublishCallback</b>.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    PUBLISH_LNN_SUCCESS = 0,              /**< Publish success */
    PUBLISH_LNN_NOT_SUPPORT_MEDIUM = 1,   /**< Unsupported medium */
    PUBLISH_LNN_INTERNAL = 2,             /**< Internal error */
    PUBLISH_LNN_UNKNOWN = 0xFF            /**< Unknown reason */
} PublishResult;

/**
 * @brief Enumerates error codes for service subscription failures.
 *
 * The error codes are returned to the caller through <b>IDiscoveryCallback</b>.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    REFRESH_LNN_SUCCESS = 0,             /**< Refresh success */
    REFRESH_LNN_NOT_SUPPORT_MEDIUM = 1,  /**< Unsupported medium */
    REFRESH_LNN_INTERNAL = 2,            /**< Internal error */
    REFRESH_LNN_UNKNOWN = 0xFF           /**< Unknown error */
} RefreshResult;

/**
 * @brief Defines the callbacks for successful and failed service publishing.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    /**
     * @brief Callback for publish result.
     *
     * @param publishId the publish Id which has been published.
     * @param reason the publish result of this time.
     *
     * @since 1.0
     * @version 1.0
     */
    void (*OnPublishResult)(int publishId, PublishResult reason);
} IPublishCb;

/**
 * @brief Defines a callback for service subscription.
 *
 * Three types of callbacks are available.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    /**
     * @brief Callback that is invoked when a device is found.
     *
     * @param device Indicates the pointer to the device info about device.
     * For details, see {@link DeviceInfo}.
     *
     * @since 1.0
     * @version 1.0
     */
    void (*OnDeviceFound)(const DeviceInfo *device);
    /**
     * @brief Callback for a subscription result.
     *
     * @param refreshId Indicates the refresh Id which.
     * @param reason Indicates the result of this time. For details, see {@link RefreshResult}.
     *
     * @since 1.0
     * @version 1.0
     */
    void (*OnDiscoverResult)(int32_t refreshId, RefreshResult reason);
} IRefreshCallback;

/**
 * @brief Defines a callback that is invoked when the device state or information changes.
 * For details, see {@link RegNodeDeviceStateCb}.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    /**
     * Mask of an event that is listened for.
     * The event can be received only if the corresponding mask bit is set and the callback is specified.
     */
    uint32_t events;
    /**
     * @brief Called when a specified device, rather than a specified ability, gets online.
     *
     * @param info Indicates the pointer to the basic information about the device.
     * For details, see {@link NodeBasicInfo}.
     *
     * @since 1.0
     * @version 1.0
     */
    void (*onNodeOnline)(NodeBasicInfo *info);
    /**
     * @brief Called when a specified device, rather than a specified ability, gets offline.
     *
     * @param info Indicates the pointer to the basic information about the device.
     * For details, see {@link NodeBasicInfo}.
     *
     * @since 1.0
     * @version 1.0
     */
    void (*onNodeOffline)(NodeBasicInfo *info);
    /**
     * @brief Called when the basic information of a device changes.
     *
     * @param type Indicates the device type. For details, see {@link NodeBasicInfoType}.
     * @param info Indicates the pointer to the new basic information of the device.
     * For details, see {@link NodeBasicInfo}.
     *
     * @since 1.0
     * @version 1.0
     */
    void (*onNodeBasicInfoChanged)(NodeBasicInfoType type, NodeBasicInfo *info);
    /**
     * @brief Called when the running status of a device changes.
     *
     * @param type Indicates the device type. For details, see {@link NodeStatusType}.
     * @param status Indicates the pointer to the new status of the device.
     * For details, see {@link NodeStatus}.
     *
     * @since 1.0
     * @version 1.0
     */
    void (*onNodeStatusChanged)(NodeStatusType type, NodeStatus *status);
} INodeStateCb;

/**
 * @brief Defines a callback that is invoked when the time synchronize has result.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    /**
     * @brief Called when the time synchronize has result.
     *
     * @param info Contains the time synchronize result info, see {@link TimeSyncResultInfo}.
     * @param retCode Indicates the result code. Value <b>0</b> indicates that the time synchronize is successful and
     * result is valid, and any other value indicates the opposite.
     *
     * @since 1.0
     * @version 1.0
     */
    void (*onTimeSyncResult)(const TimeSyncResultInfo *info, int32_t retCode);
} ITimeSyncCb;

/**
 * @brief Defines a meta node configuration, see {@link ActiveMetaNode}.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    char udid[UDID_BUF_LEN];                       /**< The udid of meta node */
    char deviceName[DEVICE_NAME_BUF_LEN];          /**< The name of meta node */
    uint16_t deviceTypeId;                         /**< The device type id of meta node */
    uint8_t addrNum;                               /**< The connection addr type of meta node */
    ConnectionAddr addr[CONNECTION_ADDR_MAX];      /**< The connection addr of meta node */
    char bypassInfo[META_NODE_BYPASS_INFO_LEN];    /**< The pass info of meta node */
} MetaNodeConfigInfo;

/**
 * @brief Defines a meta node information, see {@link MetaNodeInfo}.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    char metaNodeId[NETWORK_ID_BUF_LEN];  /**< The id of meta node */
    bool isOnline;                        /**< The online state of meta node */
    MetaNodeConfigInfo configInfo;        /**< The node ConfigInfo of meta node */
} MetaNodeInfo;

/**
 * @brief Defines heartbeat mode parameter, see {@link GearMode}.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    ModeCycle cycle;        /**< Heartbeat mode cycle */
    ModeDuration duration;  /**< Heartbeat mode duration */
    bool wakeupFlag;        /**< Heartbeat wakeup peer device or not */
} GearMode;

/**
 * @brief Called when a device is added to a LNN via {@link JoinLNN}.
 *
 * @param addr Indicates the pointer to the address of the peer device.
 * @param networkId Indicates the pointer to the network ID of the device if it is successfully added to the LNN.
 * This parameter makes no sense if the device fails to be added to the LNN.
 * @param retCode Indicates the result code. Value <b>0</b> indicates that the device is successfully added to the LNN,
 * and any other value indicates the opposite.
 *
 * @since 1.0
 * @version 1.0
 */
typedef void (*OnJoinLNNResult)(ConnectionAddr *addr, const char *networkId, int32_t retCode);

/**
 * @brief Called when a device is removed from a LNN via {@link LeaveLNN}.
 *
 * @param networkId Indicates the pointer to the network ID of the device.
 * @param retCode Indicates the result code. Value <b>0</b> indicates that the device is successfully
 * removed from the LNN, and any other value indicates the opposite.
 *
 * @since 1.0
 * @version 1.0
 */
typedef void (*OnLeaveLNNResult)(const char *networkId, int32_t retCode);

/**
 * @brief Adds the current device to the LNN where a specified device resides.
 *
 * @param pkgName Indicates the pointer to the caller ID, for example, the package name.
 * For the same caller, the value of this parameter must be the same for all functions.
 * @param target Indicates the pointer to the address of the specified device. For details, see {@link ConnectionAddr}.
 * @param cb Indicates the callback for the result. If you set this parameter to NULL, you will not receive the result.
 *
 * @return Returns <b>0</b> if the request to add the device is accepted, and the result can be obtained from the
 * callback; returns any other value if the device fails to be added to the network, in which case you will not receive
 * the result.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t JoinLNN(const char *pkgName, ConnectionAddr *target, OnJoinLNNResult cb);

/**
 * @brief Removes the current device from the LNN.
 *
 * @param pkgName Indicates the pointer to the caller ID, for example, the package name.
 * For the same caller, the value of this parameter must be the same for all functions.
 * @param networkId Indicates the pointer to the network ID that is returned
 * after the device is added to the LNN via {@link JoinLNN}.
 * @param cb Indicates the callback for the result. If you set this parameter to <b>NULL</b>,
 * you will not receive the result.
 *
 * @return Returns <b>0</b> if the request to remove the device is accepted, and the result can be obtained from the
 * callback; returns any other value if the device fails to be removed from the network, in which case you will not
 * receive the result.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t LeaveLNN(const char *pkgName, const char *networkId, OnLeaveLNNResult cb);

/**
 * @brief Registers a callback for device state changes, rather than a specified ability, gets online.
 *
 * @param pkgName Indicates the pointer to the caller ID, for example, the package name.
 * For the same caller, the value of this parameter must be the same for all functions.
 * @param callback Indicates the pointer to the callback to register. For details, see {@link INodeStateCb}.
 *
 * @return Returns <b>0</b> if the registration is successful; returns any other value otherwise.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t RegNodeDeviceStateCb(const char *pkgName, INodeStateCb *callback);

/**
 * @brief Unregisters a callback for device state changes.
 *
 * @param callback Indicates the pointer to the callback to unregister. For details, see {@link INodeStateCb}.
 *
 * @return Returns <b>0</b> if the unregistration is successful; returns any other value otherwise.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t UnregNodeDeviceStateCb(INodeStateCb *callback);

/**
 * @brief Obtains basic information about all the online devices.
 *
 * @param pkgName Indicates the pointer to the caller ID, for example, the package name.
 * For the same caller, the value of this parameter must be the same for all functions.
 * @param info Indicates the double pointer to the memory that stores the obtained basic information.
 * @param infoNum Indicates the pointer to the number of devices.
 *
 * @return Returns <b>0</b> if the basic information is obtained, in which case <b>info</b> and <b>infoNum</b> are
 * valid; returns any other value otherwise.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t GetAllNodeDeviceInfo(const char *pkgName, NodeBasicInfo **info, int32_t *infoNum);

/**
 * @brief Releases the memory returned by {@link GetAllNodeDeviceInfo}.
 *
 * @param info Indicates the pointer to the memory returned by {@link GetAllNodeDeviceInfo}.
 *
 * @since 1.0
 * @version 1.0
 */
void FreeNodeInfo(NodeBasicInfo *info);

/**
 * @brief Obtains basic information about the current device.
 *
 * @param pkgName Indicates the pointer to the caller ID, for example, the package name.
 * For the same caller, the value of this parameter must be the same for all functions.
 * @param info Indicates the double pointer to the memory that stores the obtained basic information.
 *
 * @return Returns <b>0</b> if the basic information is obtained, in which case <b>info</b> is valid;
 * returns any other value otherwise.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t GetLocalNodeDeviceInfo(const char *pkgName, NodeBasicInfo *info);

/**
 * @brief Set the Node Data Change Flag object.
 *
 * @param pkgName Indicates the pointer to the caller ID, for example, the package name.
 * For the same caller, the value of this parameter must be the same for all functions.
 * @param networkId Indicates the pointer to the network ID of the device.
 * @param dataChangeFlag Indicates the data change flag.
 *
 * @return Returns <b>0</b> if set change flag success, returns any other value otherwise.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t SetNodeDataChangeFlag(const char *pkgName, const char *networkId, uint16_t dataChangeFlag);

/**
 * @brief Obtains a specified {@link NodeDeviceInfoKey} of an online device.
 *
 * @param pkgName Indicates the pointer to the caller ID, for example, the package name.
 * For the same caller, the value of this parameter must be the same for all functions.
 * @param networkId Indicates the pointer to the network ID of the device.
 * @param key Indicates the key to be obtained.
 * @param info Indicates the pointer to the buffer that stores the obtained key.
 * @param infoLen Indicates the buffer length.
 *
 * @return Returns <b>0</b> if the {@link NodeDeviceInfoKey} is obtained, in which case <b>info</b> is valid;
 * returns any other value otherwise.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t GetNodeKeyInfo(const char *pkgName, const char *networkId,
    NodeDeviceInfoKey key, uint8_t *info, int32_t infoLen);

/**
 * @brief Start the time synchronize with specific target node.
 *
 * @param pkgName Indicates the pointer to the caller ID, for example, the package name.
 * For the same caller, the value of this parameter must be the same for all functions.
 * @param targetNetworkId Indicates the pointer to the address of the specified device.
 * @param accuracy Time synchronize accuracy.
 * @param period Time synchronize period
 * @param cb Indicates the callback for the result.
 *
 * @return Returns <b>0</b> if the request is accepted, and the result can be obtained from the
 * callback; returns any other value if the request fails, in which case you will not receive
 * the result.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t StartTimeSync(const char *pkgName, const char *targetNetworkId, TimeSyncAccuracy accuracy,
    TimeSyncPeriod period, ITimeSyncCb *cb);

/**
 * @brief Stop the time synchronize with specific target node.
 *
 * @param pkgName Indicates the pointer to the caller ID, for example, the package name.
 * For the same caller, the value of this parameter must be the same for all functions.
 * @param targetNetworkId Indicates the pointer to the address of the specified device.
 *
 * @return Returns <b>0</b> if the request is removed; returns any other value if the request fails.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t StopTimeSync(const char *pkgName, const char *targetNetworkId);

/**
 * @brief Publishes a specified service.
 *
 * Peer devices in the same LAN as the device that publishes this service can discover this service as needed.
 * The service is identified by <b>publicId</b> and <b>pkgName</b>.
 *
 * @param pkgName Indicates the pointer to the service package name, which can contain a maximum of 64 bytes.
 * @param info Indicates the pointer to the service publishing information. For details, see {@link PublishInfo}.
 * @param cb Indicates the pointer to the service publishing callback {@link IPublishCb}.
 *
 * @return Returns <b>SOFTBUS_INVALID_PARAM</b> if any parameter is null or invalid.
 * @return Returns <b>SOFTBUS_DISCOVER_NOT_INIT</b> if the Intelligent Soft Bus client fails to be initialized.
 * @return Returns <b>SOFTBUS_LOCK_ERR</b> if the mutex fails to be locked.
 * @return Returns <b>SOFTBUS_OK</b> if the service is successfully published.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t PublishLNN(const char *pkgName, const PublishInfo *info, const IPublishCb *cb);

/**
 * @brief stoppublishes a specified service.
 *
 * @param pkgName Indicates the pointer to the service package name, which can contain a maximum of 64 bytes.
 * @param publishId Indicates the service ID.
 *
 * @return Returns <b>SOFTBUS_INVALID_PARAM</b> if <b>pkgName</b> is invalid.
 * @return Returns <b>SOFTBUS_DISCOVER_NOT_INIT</b> if the Intelligent Soft Bus client fails to be initialized.
 * @return Returns <b>SOFTBUS_OK</b> if the service is successfully unpublished.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t StopPublishLNN(const char *pkgName, int32_t publishId);

/**
 * @brief Subscribes to a specified service.
 *
 * Information about the device that publishes the service will be reported to the device that subscribes to
 * the service.
 * The service is identified by <b>subscribeId</b> and <b>pkgName</b>.
 *
 * @param pkgName Indicates the pointer to the service package name, which can contain a maximum of 64 bytes.
 * @param info Indicates the pointer to the service subscription information. For details, see {@link SubscribeInfo}.
 * @param cb Indicates the service subscription callback {@link IRefreshCallback}.
 *
 * @return Returns <b>SOFTBUS_INVALID_PARAM</b> if any parameter is null or invalid.
 * @return Returns <b>SOFTBUS_DISCOVER_NOT_INIT</b> if the Intelligent Soft Bus client fails to be initialized.
 * @return Returns <b>SOFTBUS_LOCK_ERR</b> if the mutex fails to be locked.
 * @return Returns <b>SOFTBUS_OK</b> if the service subscription is successful.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t RefreshLNN(const char *pkgName, const SubscribeInfo *info, const IRefreshCallback *cb);

/**
 * @brief Unsubscribes from a specified service.
 *
 * @param pkgName Indicates the pointer to the service package name, which can contain a maximum of 64 bytes.
 * @param refreshId Indicates the service ID.
 *
 * @return Returns <b>SOFTBUS_INVALID_PARAM</b> if <b>pkgName</b> is invalid.
 * @return Returns <b>SOFTBUS_DISCOVER_NOT_INIT</b> if the Intelligent Soft Bus client fails to be initialized.
 * @return Returns <b>SOFTBUS_OK</b> if the service unsubscription is successful.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t StopRefreshLNN(const char *pkgName, int32_t refreshId);

/**
 * @brief Active meta node. The meta node online status will be notified by {@link INodeStateCb}
 *
 * @param pkgName Indicates the pointer to the caller ID, for example, the package name.
 * For the same caller, the value of this parameter must be the same for all functions.
 * @param info Meta node configuration information, see {@link MetaNodeConfigInfo}.
 * @param metaNodeId Save meta node ID when it is activated successfully, its buffer length must be not
 * less then NETWORK_ID_BUF_LEN.
 *
 * @return Returns <b>0</b> if the meta node is activated; returns any other value if the request fails.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t ActiveMetaNode(const char *pkgName, const MetaNodeConfigInfo *info, char *metaNodeId);

/**
 * @brief Deactive meta node. The meta node will be removed.
 *
 * @param pkgName Indicates the pointer to the caller ID, for example, the package name.
 * For the same caller, the value of this parameter must be the same for all functions.
 * @param metaNodeId The meta node ID which deactivated, it's obtained by {@link ActiveMetaNode}.
 *
 * @return Returns <b>0</b> if the meta node is deactivated; returns any other value if the request fails.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t DeactiveMetaNode(const char *pkgName, const char *metaNodeId);

/**
 * @brief Get all meta node by {@link ActiveMetaNode}.
 *
 * @param pkgName Indicates the pointer to the caller ID, for example, the package name.
 * For the same caller, the value of this parameter must be the same for all functions.
 * @param infos The buffer for save meta node info.
 * @param infoNum The infos buffer num which maximum is {@link MAX_META_NODE_NUM}.
 *
 * @return Returns <b>0</b> if the call is success; returns any other value if it fails.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t GetAllMetaNodeInfo(const char *pkgName, MetaNodeInfo *infos, int32_t *infoNum);

/**
 * @brief Modify heartbeat parameters and trigger a temporary heartbeat.
 *
 * @param pkgName Indicates the pointer to the caller ID, for example, the package name.
 * For the same caller, the value of this parameter must be the same for all functions.
 * @param callerId The id of the caller, whitch cannot be <b>NULL</b>, and maxium length is {@link CALLER_ID_MAX_LEN}.
 * @param targetNetworkId The networkId of the target device to refresh online state, and could be <b>NULL</b>.
 * @param mode The duration or cycle parameter of heartbeat. For details, see {@link GearMode}.
 *
 * @return Returns <b>0</b> if the call is success; returns any other value if it fails.
 *
 * @since 1.0
 * @version 1.0
 */
int32_t ShiftLNNGear(const char *pkgName, const char *callerId, const char *targetNetworkId, const GearMode *mode);

/**
 * @brief 获取指定networkId的在线设备的地址
 * @param networkId 获取设备的networkId
 * @param pDevAddrs 接收地址指针
 * @param addrNums 地址数量
 * @return SOFTBUS_OK表示成功，其它表示失败
 * @attention 调用者需要调用khFreeOnlineDevAddr释放内存
 */
int32_t GetKhDeviceNodeAddr(const char *pkgName, const char *networkId, KhDeviceNodeAddr **pDevAddrs, int32_t *addrNums);

/**
 * @brief 释放在线设备地址
 * @param pDevAddrs 需要释放内存的指针
 * @return SOFTBUS_OK表示成功，其它表示失败
 */
void FreeKhDeviceNodeAddr(KhDeviceNodeAddr *pDevAddrs);

#ifdef __cplusplus
}
#endif

#endif
