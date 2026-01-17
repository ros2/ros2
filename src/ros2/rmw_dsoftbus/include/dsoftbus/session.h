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
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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
 * @brief Provides high-speed, secure communications between devices.
 *
 * This module implements unified distributed communication management of
 * nearby devices, and provides link-independent device discovery and transmission interfaces
 * to support service publishing and data transmission.
 *
 * @since 1.0
 * @version 1.0
*/

/**
 * @file session.h
 *
 * @brief Declares unified data transmission interfaces.
 *
 * This file provides data transmission capabilities, including creating and removing a session server,
 * opening and closing sessions, receiving data, and querying basic session information. \n
 * You can use the interfaces to transmit data across the nearby devices that are discovered and networked.
 * \n
 *
 * @since 1.0
 * @version 1.0
 */
#ifndef SESSION_H
#define SESSION_H

#include <stdint.h>

#include "trans_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the session types.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    TYPE_MESSAGE = 1,  /**< Message */
    TYPE_BYTES,        /**< Bytes */
    TYPE_FILE,         /**< File */
    TYPE_STREAM,       /**< Stream */
    TYPE_BUTT,
} SessionType;

/**
 * @brief Enumerates the stream types.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum  {
    INVALID = -1,         /**< Invalid stream type. */
    RAW_STREAM,           /**< Send any segment of a frame each time. */
    COMMON_VIDEO_STREAM,  /**< Send a whole video frame each time. */
    COMMON_AUDIO_STREAM,  /**< Send a whole audio frame each time. */
    VIDEO_SLICE_STREAM,   /**< Slice frame mode. */
} StreamType;

/**
 * @brief Enumerates the link types.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum  {
    LINK_TYPE_WIFI_WLAN_5G = 1, /**< 5 GHz Wi-Fi link */
    LINK_TYPE_WIFI_WLAN_2G = 2,  /**< 2.4 GHz Wi-Fi link */
    LINK_TYPE_WIFI_P2P = 3,      /**< P2P link */
    LINK_TYPE_BR = 4,            /**< BR link */
    LINK_TYPE_BLE = 5,
    LINK_TYPE_WIFI_P2P_REUSE = 6,
    LINK_TYPE_BLE_DIRECT = 7,
    LINK_TYPE_COC = 8,
    LINK_TYPE_COC_DIRECT = 9,
    LINK_TYPE_ETH = 10,
    LINK_TYPE_SLE = 11,
    LINK_TYPE_KHPLC = 12, //Add by c000398 from kaihong Plc project
    LINK_TYPE_MAX = 13, //Change by c000398 from kaihong Plc project
} LinkType;

/**
 * @brief Defines the session attributes.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    int dataType;                      /**< Session type {@link SessionType} */
    int linkTypeNum;                   /**< Number of link types */
    LinkType linkType[LINK_TYPE_MAX];  /**< Link type {@link LinkType} */
    /**
     * @brief Defines the attributes.
     *
     * @since 1.0
     * @version 1.0
     */
    union {
        /**
         * @brief Defines the stream attributes.
         *
         * @since 1.0
         * @version 1.0
         */
        struct StreamAttr {
            int streamType; /**< Stream type {@link StreamType} */
        } streamAttr;

        /**
         * @brief Defines the bytes attributes with encryption control.
         *
         * @since 2.0
         * @version 2.0
         */
        struct BytesAttr {
            int encryptType; /**< Encryption type {@link EncryptType} */
        } bytesAttr;

        /**
         * @brief Defines the stream attributes with encryption control.
         *
         * @since 2.0
         * @version 2.0
         */
        struct StreamAttrEx {
            int streamType;  /**< Stream type {@link StreamType} */
            int encryptType; /**< Encryption type {@link EncryptType} */
        } streamAttrEx;
    } attr;
    uint8_t *fastTransData;
    uint16_t fastTransDataSize;
} SessionAttribute;

/**
 * @brief Enumerates the quality of service (QoS) types.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    QOS_IMPROVE = 0,     /**< Improve QoS */
    QOS_RECOVER = 1,     /**< Recover QoS */
} QosQuality;

/**
 * @brief Enumerates the QoS feedback types.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    TRANS_STREAM_QUALITY_EVENT = 1,  /**< Feedback on stream transmission quality */
    TRANS_CHANNEL_QUALITY_EVENT,     /**< Feedback on transmission channel quality */
    TRANS_CAN_DELAY_EVENT,           /**< Feedback on deferrable transmission */
    TRANS_CANT_DELAY_EVENT,          /**< Feedback on non-deferrable transmission */
    QOS_EVENT_MAX                    /**< Invalid feedback */
} QosEvent;

/**
 * @brief Enumerates the stream transmission QoS event types.
 *
 * @since 1.0
 * @version 1.0
 */
typedef enum {
    WIFI_CHANNEL_QUALITY = 1,      /**< Wi-Fi channel quality */
    FRAME_REALTIME_STATUS = 2,     /**< Real-time status of frame transmission */
    BANDWIDTH_ESTIMATE_VALUE = 3,  /**< Bandwidth estimation */
    JITTER_DETECTION_VALUE = 4,    /**< Jitter detection */
    STREAM_TRAFFIC_STASTICS = 5,   /**< Stream traffic statistics */
} TransEnumEventType;

/**
 * @brief Defines the Wi-Fi channel quality.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    int32_t channel;  /**< Wi-Fi channel */
    int32_t score;    /**< Wi-Fi channel score */
} WifiChannelQuality;

/**
 * @brief Defines the frame information.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    int32_t streamId;     /**< Stream ID */
    int32_t seqNum;       /**< Sequence number of the frame */
    int32_t level;        /**< Frame layer number */
    int32_t transStatus;  /**< Frame status */
    int32_t interval;     /**< Duration that unsent frames in the queue are cached */
} FrameStatus;

/**
 * @brief Defines the bandwidth detection information.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    uint32_t trend;  /**< Bandwidth change trend */
    uint32_t rate;   /**< Bandwidth rate */
} BandwidthDetection;

/**
 * @brief Defines the jitter estimation information.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    int32_t jitterLevel;  /**< Estimated network status */
    uint32_t bufferTime;  /**< Required buffer time */
} JitterEstimation;

/**
 * @brief Defines the stream transmission statistics information.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    uint64_t statisticsGotTime;               /**< Time when the statistics information is obtained */
    uint64_t periodRecvBits;                  /**< Number of bits received in a transmission period */
    uint32_t pktNum;                          /**< Number of packets */
    uint32_t periodRecvPkts;                  /**< Number of packets received in a transmission period */
    uint32_t periodRecvPktLoss;               /**< Number of RX packets lost in a transmission period */
    uint32_t periodRecvRate;                  /**< Receive rate in a transmission period, in kbit/s */
    uint64_t periodRecvRateBps;               /**< RX rate in a transmission period, in bit/s */
    uint32_t periodRtt;                       /**< Round-trip time (RTT), in ms */

    /**< RX packet loss rate displayed for high precision.
         For example, if the packet loss rate is 1.10%, the value is <b>110</b>. */
    uint32_t periodRecvPktLossHighPrecision;
    uint32_t periodSendLostPkts;              /**< Number of TX packets lost in a transmission period */
    uint32_t periodSendPkts;                  /**< Number of packets sent in a transmission period */

    /**< TX packet loss rate displayed for high precision.
         For example, if the packet loss rate is 1.10%, the value is <b>110</b>. */
    uint32_t periodSendPktLossHighPrecision;
    uint64_t periodSendBits;                  /**< Number of bits sent in a transmission period */
    uint64_t periodSendRateBps;               /**< TX rate in a transmission period, in bps */
} StreamStatistics;

/**
 * @brief Defines the video stream transmission QoS.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    TransEnumEventType type;                 /**< Stream transmission QoS event type {@link TransEnumEventType} */
    union {
        WifiChannelQuality wifiChannelInfo;  /**< Wi-Fi channel quality {@link WifiChannelQuality} */
        FrameStatus frameStatusInfo;         /**< Frame information {@link FrameStatus} */
        BandwidthDetection bandwidthInfo;    /**< Bandwidth detection {@link BandwidthDetection} */
        JitterEstimation jitterInfo;         /**< Network jitter estimation {@link JitterEstimation} */
        StreamStatistics appStatistics;      /**< Stream transmission statistics {@link StreamStatistics} */
    } info;
} QosTv;

typedef enum {
    SESSION_OPTION_MAX_SENDBYTES_SIZE = 0,   /**< Value type of this option is uint32_t, this option only can be get */
    SESSION_OPTION_MAX_SENDMESSAGE_SIZE,     /**< Value type of this option is uint32_t, this option only can be get */
    SESSION_OPTION_LINK_TYPE,                /**< Value type of this option is int32_t, this option only can be get */

    SESSION_OPTION_BUTT,
} SessionOption;

/**
 * @brief Defines session callbacks.
 *
 * When a session is opened or closed, or there is data to process, the related callback is invoked.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    /**
     * @brief Called when a session is opened.
     *
     * This callback is invoked to verify the session or initialize resources related to the session.
     *
     * @param sessionId Indicates the unique session ID.
     * @param result Indicates the result to return.
     * @return Returns <b>0</b> if the session is set up; returns a non-zero value
     * otherwise. You do not need to call {@link CloseSession} to close the session.
     * @since 1.0
     * @version 1.0
     */
    int (*OnSessionOpened)(int sessionId, int result);

    /**
     * @brief Called when a session is closed.
     *
     * This callback is invoked to release resources related to the session.
     * You do not need to call {@link CloseSession}.
     *
     * @param sessionId Indicates the unique session ID.
     * @since 1.0
     * @version 1.0
     */
    void (*OnSessionClosed)(int sessionId);

    /**
     * @brief Called when data is received.
     *
     * This callback is invoked to notify that data is received.
     *
     * @param sessionId Indicates the unique session ID.
     * @param data Indicates the pointer to the data received.
     * User-defined data type, users should apply for memory by themselves.
     * @param dataLen Indicates the length of the data received.
     * @since 1.0
     * @version 1.0
     */
    void (*OnBytesReceived)(int sessionId, const void *data, unsigned int dataLen);

    /**
     * @brief Called when a message is received.
     *
     * This callback is invoked to notify that a message is received.
     *
     * @param sessionId Indicates the unique session ID.
     * @param data Indicates the pointer to the message received.
     * @param dataLen Indicates the length of the message received.
     * @since 1.0
     * @version 1.0
     */
    void (*OnMessageReceived)(int sessionId, const void *data, unsigned int dataLen);

    /**
     * @brief Called when stream data is received.
     *
     * This callback is invoked to notify that stream data is received.
     *
     * @param sessionId Indicates the unique session ID.
     * @param data Indicates the pointer to the stream data received.
     * @param ext Indicates the pointer to the extended service data received.
     * @param param Indicates the pointer to the stream data frame information.
     * @since 1.0
     * @version 1.0
     */
    void (*OnStreamReceived)(int sessionId, const StreamData *data, const StreamData *ext,
        const StreamFrameInfo *param);

    /**
     * @brief Called when QoS information is retrieved.
     *
     * This callback is invoked to notify that QoS information is retrieved.
     *
     * @param sessionId Indicates the unique session ID.
     * @param eventId Indicates the type of QoS information, such as the channel quality and stream quality.
     * @param tvCount Indicates the number of TVs returned in the fourth parameter <b>tvList</b>.
     * @param tvList Indicates the pointer to the TV list.
     * @since 1.0
     * @version 1.0
     */
    void (*OnQosEvent)(int sessionId, int eventId, int tvCount, const QosTv *tvList);
} ISessionListener;

/**
 * @brief Defines the callbacks for file receiving.
 *
 * The callbacks are invoked to notify the file receiving status.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    /**
     * @brief Called when a file starts to be received.
     *
     * This callback is invoked to notify the start of file receiving.
     *
     * @param sessionId Indicates the unique session ID.
     * @param files Indicates the pointer to the files to receive.
     * @param fileCnt Indicates the number of files to receive.
     * @return Returns <b>0</b> if the file receiving starts; returns a non-zero value otherwise.
     * @since 1.0
     * @version 1.0
     */
    int (*OnReceiveFileStarted)(int sessionId, const char *files, int fileCnt);

    /**
     * @brief Called when a file is being received.
     *
     * This callback is invoked to notify that a file is being received.
     *
     * @param sessionId Indicates the unique session ID.
     * @param files Indicates the pointer to the first file received.
     * @param bytesUpload Indicates the size of the files received.
     * @param bytesTotal Indicates the total size of the files to receive, in bytes.
     * @return Returns <b>0</b> if a file is being received; returns a non-zero value otherwise.
     * @since 1.0
     * @version 1.0
     */
    int (*OnReceiveFileProcess)(int sessionId, const char *firstFile, uint64_t bytesUpload, uint64_t bytesTotal);

    /**
     * @brief Called when the file receiving ends.
     *
     * This callback is invoked to notify the end of file receiving.
     *
     * @param sessionId Indicates the unique session ID.
     * @param files Indicates the pointer to the files received.
     * @param fileCnt Indicates the number of files received.
     * @since 1.0
     * @version 1.0
     */
    void (*OnReceiveFileFinished)(int sessionId, const char *files, int fileCnt);

    /**
     * @brief Called when an error occurs during the file receiving process.
     *
     * This callback is invoked to notify a file receiving error.
     *
     * @param sessionId Indicates the unique session ID.
     * @since 1.0
     * @version 1.0
     */
    void (*OnFileTransError)(int sessionId);
} IFileReceiveListener;

/**
 * @brief Defines callbacks for file sending.
 *
 * The callbacks are invoked to notify the file sending status.
 *
 * @since 1.0
 * @version 1.0
 */
typedef struct {
    /**
     * @brief Called when a file is being sent.
     *
     * This callback is invoked to notify that a file is being sent.
     *
     * @param sessionId Indicates the unique session ID.
     * @param bytesUpload Indicates the size of the file sent, in bytes.
     * @param bytesTotal Indicates the total size of the file to send, in bytes.
     * @return Returns <b>0</b> if the file is being sent; returns a non-zero value otherwise.
     * @since 1.0
     * @version 1.0
     */
    int (*OnSendFileProcess)(int sessionId, uint64_t bytesUpload, uint64_t bytesTotal);

    /**
     * @brief Called when the file sending ends.
     *
     * This callback is invoked to notify the end of file sending.
     *
     * @param sessionId Indicates the unique session ID.
     * @param firstFile Indicates the pointer to the first file to send.
     * @return Returns<b>0</b> if the file sending is complete; returns a non-zero value otherwise.
     * @since 1.0
     * @version 1.0
     */
    int (*OnSendFileFinished)(int sessionId, const char *firstFile);

    /**
     * @brief Called when an error occurs during the file sending process.
     *
     * This callback is invoked to notify a file sending error.
     *
     * @param sessionId Indicates the unique session ID.
     * @since 1.0
     * @version 1.0
     */
    void (*OnFileTransError)(int sessionId);
} IFileSendListener;

/**
 * @brief Creates a session server.
 *
 * A maximum of 32 session servers can be created.
 *
 * @param pkgName Indicates the pointer to the service bundle name.
 * It is the unique identifier of the upper-layer service. The value cannot be empty or exceed 64 characters.
 * @param sessionName Indicates the pointer to the session name, which is the unique ID of the session server.
 * The value cannot be empty or exceed 255 characters.
 * @param listener Indicates the pointer to the session callback, which cannot be empty.
 *
 * @return Returns <b>0</b> if the operation is successful; returns <b>-1</b> otherwise.
 * @see RemoveSessionServer
 * @since 1.0
 * @version 1.0
 */
int CreateSessionServer(const char *pkgName, const char *sessionName, const ISessionListener *listener);

/**
 * @brief Removes a session server.
 *
 * @param pkgName Indicates the pointer to the service bundle name.
 * It is the unique identifier of the upper-layer service. The value cannot be empty or exceed 64 characters.
 * @param sessionName Indicates the pointer to the session name. The value cannot be empty or exceed 255 characters.
 *
 * @return Returns <b>0</b> if the operation is successful, returns <b>-1</b> otherwise.
 * @see CreateSessionServer
 * @since 1.0
 * @version 1.0
 */
int RemoveSessionServer(const char *pkgName, const char *sessionName);

/**
 * @brief Opens a session, which is an asynchronous process.
 *
 * The session is opened to trigger the first packet interaction process.
 * {@link OnSessionOpened} is invoked to return whether the session is successfully opened.
 * Data can be transmitted only after the session is successfully opened.
 *
 * @param mySessionName Indicates the pointer to the local session name.
 * @param peerSessionName Indicates the pointer to the remote session name.
 * @param peerNetworkId Indicates the pointer to the remote device ID.
 * @param Indicates the pointer to the group ID. This parameter can be left empty in automatic networking.
 * In manual networking, you need to apply for a valid group ID from HiChain.
 * @param attr Indicates the pointer to the session attributes {@link SessionAttribute}.
 *
 * @return Returns <b>SOFTBUS_TRANS_INVALID_PARAM</b> if invalid parameters are detected.
 * @return Returns <b>INVALID_SESSION_ID</b> if the operation fails.
 * @return Returns the session ID (an integer greater than <b>0</b>) if the session is opened;
 * returns an error code otherwise.
 * @since 1.0
 * @version 1.0
 */
int OpenSession(const char *mySessionName, const char *peerSessionName, const char *peerNetworkId,
    const char *groupId, const SessionAttribute* attr);

/**
 * @brief Closes a session.
 *
 * @param sessionId Indicates the unique session ID.
 * @return Returns no value.
 * @since 1.0
 * @version 1.0
 */
void CloseSession(int sessionId);

/**
 * @example sendbytes_message_demo.c
 */

/**
 * @brief Sends data.
 *
 * @param sessionId Indicates the unique session ID.
 * @param data Indicates the pointer to the data to send, which cannot be <b>NULL</b>.
 * @param len Indicates the length of the data to send.
 *
 * @return Returns <b>SOFTBUS_INVALID_PARAM</b> if invalid parameters are detected.
 * @return Returns <b>SOFTBUS_TRANS_SEND_LEN_BEYOND_LIMIT</b> if the data exceeds the maximum limit.
 * @return Returns <b>SOFTBUS_TRANS_INVALID_SESSION_ID</b> if <b>sessionId</b> is invalid.
 * @return Returns <b>SOFTBUS_TRANS_SESSION_NO_ENABLE</b> if the session is not open.
 * @return Returns <b>SOFTBUS_OK</b> if the operation is successful; returns an error code otherwise.
 * @since 1.0
 * @version 1.0
 */
int SendBytes(int sessionId, const void *data, unsigned int len);

/**
 * @brief Sends a message.
 *
 * @param sessionId Indicates the unique session ID.
 * @param data Indicates the pointer to the message to send, which cannot be <b>NULL</b>.
 * @param len Indicates the length of the message to send.
 *
 * @return Returns <b>SOFTBUS_INVALID_PARAM</b> if <b>data</b> is <b>NULL</b> or <b>len</b> is zero.
 * @return Returns <b>SOFTBUS_TRANS_SEND_LEN_BEYOND_LIMIT</b> if the message length exceeds the limit.
 * @return Returns <b>SOFTBUS_INVALID_SESSION_ID</b> if <b>sessionId</b> is invalid.
 * @return Returns <b>SOFTBUS_TRANS_SESSION_NO_ENABLE</b> if the session is not open.
 * @return Returns <b>SOFTBUS_OK</b> if the operation is successful; returns an error code otherwise.
 * @since 1.0
 * @version 1.0
 */
int SendMessage(int sessionId, const void *data, unsigned int len);

/**
 * @example sendstream_demo.c
 */

/**
 * @brief Sends stream data.
 *
 * @param sessionId Indicates the unique session ID.
 * @param data Indicates the pointer to the stream data to send, which cannot be <b>NULL</b>.
 * @param ext Indicates the pointer to the extended stream data to send, which cannot be <b>NULL</b>.
 * @param param Indicates the pointer to the stream frame information, which cannot be <b>NULL</b>.
 *
 * @return Returns <b>SOFTBUS_INVALID_PARAM</b> if any of the input parameters is <b>NULL</b>.
 * @return Returns <b>SOFTBUS_INVALID_SESSION_ID</b> if <b>sessionId</b> is invalid.
 * @return Returns <b>SOFTBUS_TRANS_SESSION_NO_ENABLE</b> if the session is not open.
 * @return Returns <b>SOFTBUS_OK</b> if the operation is successful; returns an error code otherwise.
 * @since 1.0
 * @version 1.0
 */
int SendStream(int sessionId, const StreamData *data, const StreamData *ext, const StreamFrameInfo *param);

/**
 * @example getsessioninfo_demo.c
 */

/**
 * @brief Obtains the session name registered by the local device.
 *
 * @param sessionId Indicates the unique session ID.
 * @param sessionName Indicates the pointer to the buffer for storing the session name.
 * @param len Indicates the length of the buffer.
 *
 * @return Returns <b>SOFTBUS_INVALID_PARAM</b> if invalid parameters are detected.
 * @return Returns <b>SOFTBUS_OK</b> if the operation is successful; returns an error code otherwise.
 * @since 1.0
 * @version 1.0
 */
int GetMySessionName(int sessionId, char *sessionName, unsigned int len);

/**
 * @brief Obtains the session name registered by the peer device.
 *
 * @param sessionId Indicates the unique session ID.
 * @param sessionName Indicates the pointer to the buffer for storing the session name.
 * @param len Indicates the length of the buffer.
 *
 * @return Returns <b>SOFTBUS_INVALID_PARAM</b> if invalid parameters are detected.
 * @return Returns <b>SOFTBUS_OK</b> if the operation is successful; returns an error code otherwise.
 * @since 1.0
 * @version 1.0
 */
int GetPeerSessionName(int sessionId, char *sessionName, unsigned int len);

/**
 * @brief Obtains the peer device ID.
 *
 * @param sessionId Indicates the unique session ID.
 * @param networkId Indicates the pointer to the buffer for storing the device ID.
 * @param len Indicates the length of the buffer.
 *
 * @return Returns <b>SOFTBUS_INVALID_PARAM</b> if invalid parameters are detected.
 * @return Returns <b>SOFTBUS_OK</b> if the operation is successful; returns an error code otherwise.
 * @since 1.0
 * @version 1.0
 */
int GetPeerDeviceId(int sessionId, char *networkId, unsigned int len);

/**
 * @brief Obtains the session role.
 *
 * @param sessionId Indicates the unique session ID.
 * @return Returns <b>-1</b> if the operation fails.
 * @return Returns <b>0</b> if the session role is a server.
 * @return Returns <b>1</b> if the session role is a client.
 * @since 1.0
 * @version 1.0
 */
int GetSessionSide(int sessionId);

/**
 * @brief Sets a listener for file receiving.
 *
 * @param pkgName Indicates the pointer to the registered bundle name, which can be used to check
 * whether the session server is in this package. The value cannot be empty or exceed 64 characters.
 * @param sessionName Indicates the pointer to the buffer for storing the session name.
 * @param recvListener Indicates the pointer to the file receive listener, which cannot be <b>NULL</b>.
 * @param rootDir Indicates the pointer to the root directory of the file. The length cannot exceed 255 bits.
 *
 * @return Returns <b>SOFTBUS_INVALID_PARAM</b> if invalid parameters are detected.
 * @return Returns <b>SOFTBUS_TRANS_SESSION_ADDPKG_FAILED</b> if the bundle specified by <b>pkgName</b>
 * fails to be added.
 * @return Returns <b>SOFTBUS_OK</b> if the operation is successful; returns an error code otherwise.
 * @since 1.0
 * @version 1.0
 */
int SetFileReceiveListener(const char *pkgName, const char *sessionName,
    const IFileReceiveListener *recvListener, const char *rootDir);

/**
 * @brief Sets a listener for file sending.
 *
 * @param pkgName Indicates the pointer to the service bundle name.
 * It is the unique identifier of the upper-layer service. The value cannot be empty or exceed 64 characters.
 * @param sessionName Indicates the pointer to the buffer for storing the session name.
 * @param sendListener Indicates the pointer to the file send listener, which cannot be <b>NULL</b>.
 *
 * @return Returns <b>SOFTBUS_INVALID_PARAM</b> if invalid parameters are detected.
 * @return Returns <b>SOFTBUS_TRANS_SESSION_ADDPKG_FAILED</b> if the bundle specified by <b>pkgName</b>
 * fails to be added.
 * @return Returns <b>SOFTBUS_OK</b> if the operation is successful; returns an error code otherwise.
 * @since 1.0
 * @version 1.0
 */
int SetFileSendListener(const char *pkgName, const char *sessionName, const IFileSendListener *sendListener);

/**
 * @example sendfile_demo.c
 */

/**
 * @brief Sends files.
 *
 * @param sessionId Indicates the unique session ID.
 * @param sFileList Indicates the pointer to the source files to send, which cannot be <b>NULL</b>.
 * @param dFileList Indicates the pointer to the destination files, which cannot be <b>NULL</b>.
 * @param fileCnt Indicates the number of files to send, which cannot be <b>0</b>.
 *
 * @return Returns <b>SOFTBUS_INVALID_PARAM</b> if <b>sFileList</b> is <b>NULL</b> or <b>fileCnt</b> is <b>0</b>.
 * @return Returns <b>SOFTBUS_INVALID_SESSION_ID</b> if <b>sessionId</b> is invalid.
 * @return Returns <b>SOFTBUS_TRANS_SESSION_NO_ENABLE</b> if the session is not open.
 * @return Returns <b>SOFTBUS_OK</b> if the operation is successful; returns an error code otherwise.
 * @since 1.0
 * @version 1.0
 */
int SendFile(int sessionId, const char *sFileList[], const char *dFileList[], uint32_t fileCnt);

/**
 * @brief Get Session based on a session ID.
 *
 * @param sessionId Indicates the session ID.
 * @param option Indicates the session option type to get.
 * @param optionValue Indicates the session option value to get, which cannot be <b>NULL</b>.
 * @param valueSize Indicates the size of data which optionValue point to, which cannot be <b>0</b>.
 * The common error codes are as follows:
 * @return Returns <b>SOFTBUS_INVALID_PARAM</b> if the option is invalid, optionValue is NULL or valueSize is Zero.
 * @return Returns <b>SOFTBUS_INVALID_SESSION_ID</b> if the sessionId is invalid.
 * @return Returns <b>SOFTBUS_TRANS_SESSION_NO_ENABLE</b> if the session current be not enabled.
 * @return Returns <b>SOFTBUS_OK</b>if the function is called successfully, return other internal errorcodes otherwise.
 * @since 1.0
 * @version 1.0
 */
int GetSessionOption(int sessionId, SessionOption option, void* optionValue, uint32_t valueSize);

#ifdef __cplusplus
}
#endif
#endif  // SESSION_H
