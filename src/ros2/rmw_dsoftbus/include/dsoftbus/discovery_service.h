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
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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
 * @file discovery_service.h
 *
 * @brief Declares functions and constants for the discovery service of the Intelligent Soft Bus.
 *
 * The functions are used to perform
 * the following operations: \n
 * <ul>
 * <li>Publishing service and stop publishing service functions</li>
 * <li>Start the discovery function and stop the discover function</li>
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef DISCOVERY_SERVICE_H
#define DISCOVERY_SERVICE_H

#include "softbus_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/**
 * @brief Indicates the maximum length of the device address in <b>IDiscoveryCallback</b>.
 *
 */
#define CONNECT_ADDR_LEN 46

/**
 * @brief Enumerates error codes for service publishing failures.
 *
 * The error codes are returned to the caller through <b>IPublishCallback</b>.
 *
 */
typedef enum {
    /* Unsupported medium */
    PUBLISH_FAIL_REASON_NOT_SUPPORT_MEDIUM = 1,
    /* internal error */
    PUBLISH_FAIL_REASON_INTERNAL = 2,
    /* Unknown reason */
    PUBLISH_FAIL_REASON_UNKNOWN = 0xFF
} PublishFailReason;

/**
 * @brief Defines the callbacks for successful and failed service publishing.
 *
 */
typedef struct {
    /** Callback for successful publishing */
    void (*OnPublishSuccess)(int publishId);
    /** Callback for failed publishing */
    void (*OnPublishFail)(int publishId, PublishFailReason reason);
} IPublishCallback;

/**
 * @brief Enumerates error codes for service subscription failures.
 *
 * The error codes are returned to the caller through <b>IDiscoveryCallback</b>.
 *
 */
typedef enum {
    /* Unsupported medium */
    DISCOVERY_FAIL_REASON_NOT_SUPPORT_MEDIUM = 1,
    /* internal error */
    DISCOVERY_FAIL_REASON_INTERNAL = 2,
    /* Unknown error */
    DISCOVERY_FAIL_REASON_UNKNOWN = 0xFF
} DiscoveryFailReason;

/**
 * @brief Defines a callback for service subscription.
 *
 * Three types of callbacks are available.
 *
 */
typedef struct {
    /** Callback that is invoked when a device is found */
    void (*OnDeviceFound)(const DeviceInfo *device);
    /** Callback for a subscription failure */
    void (*OnDiscoverFailed)(int subscribeId, DiscoveryFailReason failReason);
    /** Callback for a subscription success */
    void (*OnDiscoverySuccess)(int subscribeId);
} IDiscoveryCallback;

/**
 * @brief Publishing service, the discovered end publishes its own information,
 * which can be discovered by other devices.
 * Peer devices in the same LAN as the device that publishes this service can discover this service as needed.
 * The service is identified by <b>publicId</b> and <b>pkgName</b>.
 * @see {@link UnPublishService}
 * @param[in] pkgName Indicates the pointer to the service package name, which can contain a maximum of 64 bytes.
 * @param[in] info Indicates the pointer to the service publishing information.
 * For details, see {@link PublishInfo}.
 * @param[in] cb Indicates the pointer to the service publishing callback.
 * For details, see {@link IPublishCallback}.
 * @return <b>SOFTBUS_INVALID_PARAM</b> if any parameter is null or invalid.
 * @return <b>SOFTBUS_DISCOVER_NOT_INIT</b> if the Intelligent SoftBus client fails to be initialized.
 * @return <b>SOFTBUS_LOCK_ERR</b> if the mutex fails to be locked.
 * @return <b>SOFTBUS_OK</b> if the service is successfully published.
 * @deprecated Please use PublishLNN instead, for details, see {@link PublishLNN}.
 */
int PublishService(const char *pkgName, const PublishInfo *info, const IPublishCallback *cb);

/**
 * @brief Stop publishing service functions, stop publishing its own capability information,
 * and other devices cannot find it.
 * @see {@link PublishService}
 * @param[in] pkgName Indicates the pointer to the service package name, which can contain a maximum of 64 bytes.
 * @param[in] publishId Indicates the service ID.
 * @return <b>SOFTBUS_INVALID_PARAM</b> if <b>pkgName</b> is invalid.
 * @return <b>SOFTBUS_DISCOVER_NOT_INIT</b> if the Intelligent SoftBus client fails to be initialized.
 * @return <b>SOFTBUS_OK</b> if the service is successfully unpublished.
 * @deprecated Please use StopPublishLNN instead, for details, see {@link StopPublishLNN}.
 */
int UnPublishService(const char *pkgName, int publishId);

/**
 * @brief Start the discovery function, the discovered end begins to discover other devices
 * and obtains the information of the remote device.
 * Information about the device that publishes the service will be reported to the device that subscribes to
 * the service. The service is identified by <b>subscribeId</b> and <b>pkgName</b>.
 * @see {@link StopDiscovery}
 * @param[in] pkgName Indicates the pointer to the service package name, which can contain a maximum of 64 bytes.
 * @param[in] info Indicates the pointer to the service subscription information.
 * For details, see {@link SubscribeInfo}.
 * @param[in] cb Indicates the service subscription callback. For details, see {@link IDiscoveryCallback}.
 * @return <b>SOFTBUS_INVALID_PARAM</b> if any parameter is null or invalid.
 * @return <b>SOFTBUS_DISCOVER_NOT_INIT</b> if the Intelligent SoftBus client fails to be initialized.
 * @return <b>SOFTBUS_LOCK_ERR</b> if the mutex fails to be locked.
 * @return <b>SOFTBUS_OK</b> if the service subscription is successful.
 * @deprecated Please use RefreshLNN instead, for details, see {@link RefreshLNN}.
 */
int StartDiscovery(const char *pkgName, const SubscribeInfo *info, const IDiscoveryCallback *cb);

/**
 * @brief Stop the discovery function, at this time no longer capture device information of other devices at this time.
 * @see {@link StartDiscovery}
 * @param[in] pkgName Indicates the pointer to the service package name, which can contain a maximum of 64 bytes.
 * @param[in] subscribeId Indicates the service ID.
 * @return <b>SOFTBUS_INVALID_PARAM</b> if <b>pkgName</b> is invalid.
 * @return <b>SOFTBUS_DISCOVER_NOT_INIT</b> if the Intelligent SoftBus client fails to be initialized.
 * @return <b>SOFTBUS_OK</b> if the service unsubscription is successful.
 * @deprecated Please use StopRefreshLNN instead, for details, see {@link StopRefreshLNN}.
 */
int StopDiscovery(const char *pkgName, int subscribeId);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* DISCOVERY_SERVICE_H */
