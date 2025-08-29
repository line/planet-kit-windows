// Copyright 2022 LINE Plus Corporation
//
// LINE Plus Corporation licenses this file to you under the Apache License,
// version 2.0 (the "License"); you may not use this file except in compliance
// with the License. You may obtain a copy of the License at:
//
//   https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
// License for the specific language governing permissions and limitations
// under the License.

#pragma once

#include "PlanetKitPredefine.h"
#include "PlanetKitAutoPtr.hpp"
#include "PlanetKitSharedPtr.hpp"
#include "PlanetKitOptional.hpp"
#include "PlanetKitContainer.hpp"
#include "PlanetKitString.hpp"


// CLASS1 inherits CLASS2::member via dominance
#pragma warning(disable: 4250)


#define PLNK_BUFFER_SIZE_256                    256
#define PLNK_BUFFER_SIZE_512                    512
#define PLNK_BUFFER_SIZE_1024                   1024

#define PLNK_CALL_USER_ID_MAX_SIZE              256
#define PLNK_CALL_API_KEY_MAX_SIZE              256
#define PLNK_CALL_SERVICE_ID_MAX_SIZE           256
#define PLNK_CALL_COUNTRY_CODE_MAX_SIZE         256
#define PLNK_CALL_DEVICE_KEY_MAX_SIZE           512
#define PLNK_CALL_CC_PARAM_MAX_SIZE             1024

#define PLNK_CALL_VERIFY_PARAM_MAX_SIZE         1024
#define PLNK_CALL_USER_REL_CODE_MAX_SIZE        300

#define PLNK_CALL_INIT_DATA_BUFFER_SIZE         200
#define PLNK_PEER_INFO_MAX_SUBGRPS              100
#define PLNK_PEER_INFO_MAX_SUBGRP_NAME_LEGNTH   16

#define NULLABLE 

#if __cplusplus >= 201402L
#define PLANETKIT_DEPRECATED(x) [[deprecated(x)]]
#elif (defined(_MSC_VER) && _MSC_VER >= 1900)
#define PLANETKIT_DEPRECATED(x) __declspec(deprecated(x)) 
#else
#define PLANETKIT_DEPRECATED(x)
#endif

#define PLNK_UNREFERENCED_PARAMETER(P)  (P)

namespace PlanetKit {
    using PlanetKitByte = const char;

    /**
     * @brief Fail reasons related to start
     */
    enum EStartFailReason {
        // Core start fail reason
        /// Reason none (default value)
        PLNK_START_FAIL_REASON_NONE = 0,
        /// Invalid parameter
        PLNK_START_FAIL_REASON_INVALID_PARAM = 1,
        /// Instance already exists.
        PLNK_START_FAIL_REASON_ALREADY_EXIST = 2,
        /// Failed to decode the argument of the verifyCall() API.
        PLNK_START_FAIL_REASON_DECODE_CALL_PARAM = 3,
        /// PlanetKit has a memory problem.
        PLNK_START_FAIL_REASON_MEM_ERR = 4,
        /// The user ID of the callee or room ID must not be the same as the user ID.
        PLNK_START_FAIL_REASON_ID_CONFLICT = 5,
        /// Cannot re-use an instance for a new call or conference that is already used before.
        PLNK_START_FAIL_REASON_REUSE = 6,
        /// The user ID string is not in a valid format (https://docs.lineplanet.me/overview/glossary#user-id).
        PLNK_START_FAIL_REASON_INVALID_USER_ID = 7,
        /// The service ID string is not in a valid format (https://docs.lineplanet.me/overview/glossary#service-id).
        PLNK_START_FAIL_REASON_INVALID_SERVICE_ID = 8,
        /// The API-key string is not in a valid format (https://docs.lineplanet.me/overview/glossary#api-key).
        PLNK_START_FAIL_REASON_INVALID_API_KEY = 9,
        /// The room ID string is not in a valid format (https://docs.lineplanet.me/overview/glossary#room-id).
        PLNK_START_FAIL_REASON_INVALID_ROOM_ID = 10,
        /// App server data is too long.
        PLNK_START_FAIL_REASON_TOO_LONG_APP_SERVER_DATA = 11,
        /// PlanetKit is not initialized.
        PLNK_START_FAIL_REASON_NOT_INITIALIZED = 12,
        /// Reason none (default value2)
        PLNK_START_FAIL_REASON_INTERNAL = 999,

        // Platform start fail reason (1000 ~ 1999)
        // Windows fail reason code range 1000 ~ 1999
        /// Some function has failed.
        PLNK_KIT_START_FAIL_REASON_CORE_LIBRARY_FAILED = 1000,
        /// Some problems have occurred in audio input device.
        PLNK_KIT_START_FAIL_REASON_AUDIO_INPUT_DEVICE_FAIL = 1001,
        /// Some problems have occurred in audio output device.
        PLNK_KIT_START_FAIL_REASON_AUDIO_OUTPUT_DEVICE_FAIL = 1002,
        /// Some problems have occurred in video capturer device.
        PLNK_KIT_START_FAIL_REASON_VIDEO_CAPTURER_FAIL = 1003,
        /// PlanetKit is not ready to start.
        PLNK_KIT_START_FAIL_REASON_NOT_READY = 1004,
        /// Invalid parameter
        PLNK_KIT_START_FAIL_REASON_INVALID_PARAM = 1005,
        /// Another PlanetKitConference instance already exists.
        PLNK_KIT_START_FAIL_REASON_OTHER_CONFERENCE_IS_ALREADY_EXIST = 1006,
        /// Peer ID is empty when you MakeCall.
        PLNK_KIT_START_FAIL_REASON_PEER_ID_IS_EMPTY = 1007,

        // Windows platform internal errors are reduced from value 1999.
        // If this error is returned, please contact the PlanetKit windows development team.

        // iOS / macOS fail reason code range 2000 ~2999

        // Android fail reason code range 3000 ~ 3999
    };

    /**
     * @brief Error information related to media requests
     */
    enum EMediaRequestError {
        /// None (default value)
        PLNK_MEDIA_REQ_ERROR_NONE = 0,
        /// Internal error
        PLNK_MEDIA_REQ_ERROR_INTERNAL,
        /// Invalid parameter
        PLNK_MEDIA_REQ_ERROR_INVALID_PARAM,
        /// Invalid state
        PLNK_MEDIA_REQ_ERROR_INVALID_STATE,
        /// Enum max count (not used)
        PLNK_MEDIA_REQ_ERROR_OVER_MAX_COUNT,
    };

    /**
     * @brief Result values of starting
     */
    struct SStartResult {
        /// Whether the start is successful or not
        bool bSuccess;
        /// Reason for failure
        EStartFailReason reason;
    };

    /**
     * @brief
     *   Source of disconnection.<br>
     *    - [Both] means it can occur in both 1:1 Call and Conference.<br>
     *    - [1:1] means it can occur only in 1:1 Call.<br>
     *    - [Conference] means it can occur only in Conference Call.<br>
     */
    enum EDisconnectSource {
        /// [Both] Undefined
        PLNK_DISCONNECT_SOURCE_UNDEFINED = 0,
        /// [1:1] Callee
        PLNK_DISCONNECT_SOURCE_CALLEE = 1,
        /// [1:1] Caller
        PLNK_DISCONNECT_SOURCE_CALLER = 2,
        /// [Conference] Participant
        PLNK_DISCONNECT_SOURCE_PARTICIPANT = 3,
        /// [Both] Cloud server
        PLNK_DISCONNECT_SOURCE_CLOUD_SERVER = 4,
        /// [Conference] App server
        PLNK_DISCONNECT_SOURCE_APP_SERVER = 5,
    };


    /**
     * @brief
     *   Reason for disconnection.<br>
     *    - [Both] means it can occur in both 1:1 Call and Conference.<br>
     *    - [1:1] means it can occur only in 1:1 Call.<br>
     *    - [Conference] means it can occur only in Conference Call.<br>
     */
    enum EDisconnectReason {
        // Kit Platform Layer can assign one of the following reasons when disconnection occurs
        // COMMON REASON (1001 ~ 1100)
        /// [Both][Caller, Callee, Participant] Disconnected without any errors.
        PLNK_DISCONNECT_REASON_NORMAL = 1001,
        /**
         * [Both][Callee, CloudServer]
         * - 1-to-1 call: The responder rejected a call.
         * - Group call: The previously joined group call has been declined when entering the same group call room (e.g. re-joining after crash).
         */
        PLNK_DISCONNECT_REASON_DECLINE = 1002,
        /**
         * [Both][Caller, Callee, Participant] Received a cellular call during the Planet call <br>
         */
        PLNK_DISCONNECT_REASON_CELL_CALL = 1003,

        // ERROR REASON (1101 ~ 1200)
        /// [Both][Caller, Callee, Participant, CloudServer] Disconnected by an internal error.
        PLNK_DISCONNECT_REASON_INTERNAL_ERROR = 1109,

        /**
         * [Both][Caller, Callee, AppServer] <br>
         * Application defined error. user_rel_code is accompanied <br>
         * - 1-to-1 call: user_rel_code is defined by the call peer. <br>
         * - Group call: user_rel_code is defined by AppServer. For example, https://docs.lineplanet.me/server-api/server-api-kickout
         */
        PLNK_DISCONNECT_REASON_USER_ERROR = 1110,
        /// [Both][Caller, Callee, Participant] Disconnected by an OS-specific error.
        PLNK_DISCONNECT_REASON_INTERNAL_KIT_ERROR = 1111,
        /// [Both][Caller, Callee, Participant] Audio source (e.g. mic) has not sent any audio data for a while.
        PLNK_DISCONNECT_REASON_AUDIO_TX_NO_SRC = 1112,



        // Kit Platform Layer can not assign below reasons when disconnect
        // COMMON REASON (1201 ~ 1300)
        /// [1:1][Caller] The initiator disconnected the call before the responder answers.
        PLNK_DISCONNECT_REASON_CANCEL = 1201,
        /// [1:1][Callee] The responder is calling.
        PLNK_DISCONNECT_REASON_BUSY = 1202,
        /// [1:1][Caller] The responder doesn't answer. The initiator waits for the answer for 60 seconds.
        PLNK_DISCONNECT_REASON_NOANSWER = 1203,
        /// [Both][CloudServer] The responder doesn't answer. The initiator waits for the answer for 60 seconds.
        PLNK_DISCONNECT_REASON_ALREADY_GOT_A_CALL = 1204,
        /// [Both][CloudServer] The same ID pair (user-id and service-id) is calling in another device.
        PLNK_DISCONNECT_REASON_MULTIDEV_IN_USE = 1205,
        /// [1:1][CloudServer] A responder using the same ID pair (user-id and service-id) answered the call in another device.
        PLNK_DISCONNECT_REASON_MULTIDEV_ANSWER = 1206,
        /// [1:1][CloudServer] A responder using the same ID pair (user-id and service-id) declined the call in another device.
        PLNK_DISCONNECT_REASON_MULTIDEV_DECLINE = 1207,
        ///< [Both][CloudServer] Maximum call time has been reached
        PLNK_DISCONNECT_REASON_MAX_CALL_TIME_EXCEEDED = 1208,

        // ERROR REASON (1301 ~ 1400)
        /// [Both][Caller, Callee, Participant, CloudServer] Network is unavailable to keep a call.
        PLNK_DISCONNECT_REASON_NETWORK_UNSTABLE = 1301,
        /// [1:1][CloudServer] LINE Planet Gateway failed to call the Notify callback, or the Notify callback returned a failure. Please check AppServer or the Notify callback's URL.
        PLNK_DISCONNECT_REASON_PUSH_ERROR = 1302,
        /// [Both][CloudServer] Authentication failure
        PLNK_DISCONNECT_REASON_AUTH_ERROR = 1303,
        /// [Both][CloudServer] The call was already released. For example, the initiator already canceled the call.
        PLNK_DISCONNECT_REASON_RELEASED_CALL = 1304,

        /// [Both][CloudServer] The server disconnected a call because of an internal error.
        PLNK_DISCONNECT_REASON_SERVER_INTERNAL_ERROR = 1305,
        /// [Both][Caller, Callee, Participant] Network is unavailable to keep a call.
        PLNK_DISCONNECT_REASON_UNAVAILABLE_NETWORK = 1308,
        /**
         * [Both][Caller, Callee, Participant] A user's device has been powered off.<br>
         */
        PLNK_DISCONNECT_REASON_APP_DESTROY = 1309,
        /// [Both][Caller, Callee, Participant] A user's device entered sleep mode.
        PLNK_DISCONNECT_REASON_SYSTEM_SLEEP = 1310,
        /// [Both][Caller, Callee, Participant] A user's session has been logged out.
        PLNK_DISCONNECT_REASON_SYSTEM_LOGOFF = 1311,
        /// [Both][Caller, Callee, Participant] The call is not connected because the maximum transmission unit (MTU) is exceeded.
        PLNK_DISCONNECT_REASON_MTU_EXCEEDED = 1312,
        ///< [Both][CloudServer] The Planet Cloud server failed to deliver app server data to the AppServer.
        PLNK_DISCONNECT_REASON_APP_SERVER_DATA_ERROR = 1313,
        ///< [Both][Caller, Callee, Participant] Desktop screen is locked
        PLNK_DISCONNECT_REASON_DESKTOP_SCREEN_LOCKED = 1314,

        // ERROR REASON GroupCall Only (1401 ~ 1500)
        /// [Group][CloudServer] The number of participants in this room reached the limit.
        PLNK_DISCONNECT_REASON_ROOM_IS_FULL = 1401,
        /// [Group][CloudServer] The server kicks out a user when the user stays in a group call room alone for a long time.
        PLNK_DISCONNECT_REASON_ALONE_KICK_OUT = 1402,
        /// [Group][CloudServer] The room is destroyed because all remaining participants left before the other participant's joining is complete.
        PLNK_DISCONNECT_REASON_ROOM_NOT_FOUND = 1404,
        /// [Group][Participant] Disconnected by trying to join from another instance.
        PLNK_DISCONNECT_REASON_ANOTHER_INSTANCE_TRY_TO_JOIN = 1405,


        // ERROR REASON related to HTTP (1501 ~ 1600)
        /// [Both][CloudServer] Invalid access token
        PLNK_DISCONNECT_REASON_SERVICE_ACCESS_TOKEN_ERROR = 1501,
        /**
         * [Both][CloudServer] An unacceptable character is used in service-id or user-id. <br>
         */
        PLNK_DISCONNECT_REASON_SERVICE_INVALID_ID = 1502,

        /// [Both][CloudServer] Under maintenance
        PLNK_DISCONNECT_REASON_SERVICE_MAINTENANCE = 1503,
        /// [Both][CloudServer] LINE Planet Gateway is busy for now.
        PLNK_DISCONNECT_REASON_SERVICE_BUSY = 1504,
        /// [Both][CloudServer] LINE Planet Gateway internal error. Joining failed in an old version (lower than 3.6) because the room has the SUBGROUP room attribute (created by PlanetKit 3.6 or higher).
        PLNK_DISCONNECT_REASON_SERVICE_INTERNAL_ERROR = 1505,
        /// [Both][Caller, Participant] SSL peer certificate or SSH remote key was invalid.
        PLNK_DISCONNECT_REASON_SERVICE_HTTP_INVALID_PEER_CERT = 1508,

        /** [Both][Caller, Participant] <br>
         *  Could not make an HTTP request. Please check the user's network environment: <br>
         *  Please check user network environment. <br>
         *  1. Firewall https://docs.lineplanet.me/help/troubleshooting/troubleshooting-firewall <br>
         *  2. Client vaccine program <br>
         */
        PLNK_DISCONNECT_REASON_SERVICE_HTTP_ERROR = 1506,
        /** [Both][Caller, Participant] <br>
         *  Could not make an HTTP request. Please check the user's network environment: <br>
         *  1. Firewall https://docs.lineplanet.me/help/troubleshooting/troubleshooting-firewall <br>
         *  2. Client vaccine program <br>
         */
        PLNK_DISCONNECT_REASON_SERVICE_HTTP_CONNECTION_TIME_OUT = 1507,
        /** [Both][Caller, Participant] <br>
         *  Could not make an HTTP request. Please check the user's network environment: <br>
         *  1. Firewall https://docs.lineplanet.me/help/troubleshooting/troubleshooting-firewall <br>
         *  2. Client vaccine program <br>
         */
        PLNK_DISCONNECT_REASON_SERVICE_HTTP_CONNECT_FAIL = 1509,

        /// [Both][Caller, Participant] The URL format is invalid, or the host or proxy name could not be resolved.
        PLNK_DISCONNECT_REASON_SERVICE_HTTP_INVALID_URL = 1510,
        /// [Both][CloudServer] The current PlanetKit version is deprecated. Need to upgrade.
        PLNK_DISCONNECT_REASON_SERVICE_INCOMPATIBLE_PLANETKIT_VER = 1511,
        ///< [Both][CloudServer] Too many call connection attempts in a short period of time
        PLNK_DISCONNECT_REASON_SERVICE_TOO_MANY_REQUESTS = 1512,

        /* Deprecated disconnect reason */
        // PLNK_DISCONNECT_REASON_AUDIO_TX_NO_SRC_BY_LOCAL    = 1101,
        // PLNK_DISCONNECT_REASON_AUDIO_TX_NO_SRC_BY_REMOTE   = 1102,
        // PLNK_DISCONNECT_REASON_INTERNAL_ERROR_BY_LOCAL     = 1103,
        // PLNK_DISCONNECT_REASON_INTERNAL_ERROR_BY_REMOTE    = 1104,
        // PLNK_DISCONNECT_REASON_USER_ERROR_BY_LOCAL         = 1105,
        // PLNK_DISCONNECT_REASON_USER_ERROR_BY_REMOTE        = 1106,
        // PLNK_DISCONNECT_REASON_INTERNAL_KIT_ERROR_BY_LOCAL = 1107,
        // PLNK_DISCONNECT_REASON_INTERNAL_KIT_ERROR_BY_REMOTE = 1108,

        // PLNK_DISCONNECT_REASON_UNAVAILABLE_BAD_NETWORK_IN_CONFERENCE = 1306,
        // PLNK_DISCONNECT_REASON_UNAVAILABLE_NETWORK_IN_CALL = 1307,

        // PLNK_DISCONNECT_REASON_WRONG_ROOM_ATTR = 1403,

    };



    /**
     * @brief Reason for disabled media
     */
    enum EMediaDisabledReason {
        /// None (Default value)
        PLNK_MEDIA_DISABLE_REASON_UNDEFINED = 0,
        /// User has disabled their own video.
        PLNK_MEDIA_DISABLE_REASON_USER = 1,
        /// Media has been declined.
        PLNK_MEDIA_DISABLE_REASON_DECLINE = 2,
    };

    /**
     * @brief Current video state
     */
    enum EVideoState {
        /// Video state is disabled.
        PLNK_VIDEO_STATE_DISABLED = 0,
        /// Video state is enabled.
        PLNK_VIDEO_STATE_ENABLED,
        /// Video state is paused.
        PLNK_VIDEO_STATE_PAUSED,
    };

    /**
     * @brief State of the peer's video activation
     */
    enum EPeerVideoState {
        /// Peer video is not activated (Default).
        PLNK_PEER_VIDEO_STATE_IDLE = 0,
        /// Peer video is ready to start.
        PLNK_PEER_VIDEO_STATE_READY = 1,
        /// Peer video has started.
        PLNK_PEER_VIDEO_STATE_STARTED = 2

    };

    /**
     * @brief Reason for pausing video
     */
    enum EVideoPauseReason {
        /// Paused by a user.
        PLNK_VIDEO_PAUSE_REASON_BY_USER = 0,
        /// Unknown interrupt has occurred.
        PLNK_VIDEO_PAUSE_REASON_BY_INTERRUPT,
        /// Unknown error
        PLNK_VIDEO_PAUSE_REASON_UNDEFINED,
        /// Internal error
        PLNK_VIDEO_PAUSE_REASON_INTERNAL,
        /// Paused when the peer requests enabling of a video call.
        PLNK_VIDEO_PAUSE_REASON_ENABLE_VIDEO_RESPONSE,
        /// Camera has become inactive.
        PLNK_VIDEO_PAUSE_REASON_CAMERA_INACTIVE,
        /// Paused by the request for hold.
        PLNK_VIDEO_PAUSE_REASON_HOLD,
    };

    /**
     * @brief Peer's media type
     */
    enum EMediaType {
        /// Unkown type
        PLNK_MEDIA_TYPE_UNKNOWN,
        /// Audio type only
        PLNK_MEDIA_TYPE_AUDIO,
        /// Video type only
        PLNK_MEDIA_TYPE_VIDEO,
        /// Audio and video
        PLNK_MEDIA_TYPE_AUDIOVIDEO,
        /// Max count (do not use)
        PLNK_MEDIA_TYPE_COUNT
    };

    /**
     * @brief
     *   This is an enum value added to handle unknown errors that may occur due to functional differences between versions.
     */
    enum EConferenceExceptionType {
        /// None
        PLNK_CONF_EXCEPTION_TYPE_NONE = 0,
        /// This is an exception that determines and informs the server when another user in the room uses a feature that is not supported by the local user's client.
        PLNK_CONF_EXCEPTION_TYPE_PEER_USED_UNSUPPORTED_FEATURE,
        /// A user-defined exception has occurred.
        PLNK_CONF_EXCEPTION_TYPE_USER,
    };

    /**
     * @brief State of screen share
     */
    enum EScreenShareState {
        /// Disabled
        PLNK_SCREEN_SHARE_STATE_DISABLED = 0,
        /// Enabled
        PLNK_SCREEN_SHARE_STATE_ENABLED = 1
    };

    /**
     * @brief Device definition of peer that can be utilized in statistics.
     */
    enum EUserEquipmentType {
        /// None
        PLNK_UE_TYPE_NONE = 0,
        /// Android
        PLNK_UE_TYPE_ANDROID = 1,
        /// iOS
        PLNK_UE_TYPE_IOS = 2,
        /// Linux
        PLNK_UE_TYPE_LINUX = 3,
        /// macOS
        PLNK_UE_TYPE_MAC = 4,
        /// Web
        PLNK_UE_TYPE_WEB = 5,
        /// Windows
        PLNK_UE_TYPE_WINDOWS = 6,

        /// Not used definition
        PLNK_UE_TYPE_SIP_TERMINAL = 100,
    };

    /**
     * @brief Type of connection token for connecting to the PlanetKit cloud server.
     */
    enum EConnectToken {
        /// This feature will be deprecated soon. It is only a value temporarily maintained for backward compatibility.
        API_KEY,
        /// Default feature of the connect token.
        ACCESS_TOKEN
    };

    /**
     * @brief Reason for the failure of getting screen share state.
     */
    enum EPeerGetFailReason {
        /// None
        PLNK_PEER_GET_FAIL_REASON_NONE = 0,
        /// Peer is not in the subgroup.
        PLNK_PEER_GET_FAIL_REASON_NOT_IN_SUBGROUP = 1,
        /// Peer is already disconnected.
        PLNK_PEER_GET_FAIL_REASON_DISCONNECTED = 2,
    };

    constexpr int PLNK_DISPLAY_NAME_MAX_SIZE_BYTES = 128;

    class EventManager;
    class PlanetKitManager;

    class PLANETKIT_API ContentShareInterface;
    class PLANETKIT_API SubgroupManager;
    class PLANETKIT_API VideoRender;
    class PLANETKIT_API Subgroup;
    class PLANETKIT_API Peer;
    class PLANETKIT_API PlanetKitCall;
    class PLANETKIT_API PeerControl;
    class PLANETKIT_API PlanetKitConference;
    class PLANETKIT_API PeerVideoStatus;
    class PLANETKIT_API PeerHold;
    class PLANETKIT_API ConnectParam;

    class PLANETKIT_API ConferencePeers;
    class PLANETKIT_API IPeerControlEvent;

    struct VideoStatus;
    struct VideoStatusResult;

    class PLANETKIT_API HookedAudio;

    class PLANETKIT_API SendVoiceProcessor;

    class PLANETKIT_API VideoFrame;

    class PLANETKIT_API CallInitData;

    class PLANETKIT_API MyMediaStatus;

    class PLANETKIT_API CreateVideoCapturerResult;

    class PLANETKIT_API Configuration;

    class PLANETKIT_API OutboundDataSession;
    class PLANETKIT_API InboundDataSession;

    class PLANETKIT_API PlanetKitManager;

    class PLANETKIT_API AudioManager;

    class PLANETKIT_API Image;

    class PLANETKIT_API Mic;
    class PLANETKIT_API Speaker;


    class Base {
    private:
        friend class EventManager;
        friend class PlanetKitManagerImpl;

    protected:
        /**
        * Adds a reference to the PlanetKit instance.
        * @return Reference count of the PlanetKit instance after addition.
        */
        virtual ULONG AddRef() = 0;
        /**
        * Releases the PlanetKit instance.
        * @return Reference count of the PlanetKit instance after release. If 0, the instance has been deleted.
        */
        virtual ULONG Release() = 0;

        friend class AutoPtr<ContentShareInterface>;
        friend class AutoPtr<SubgroupManager>;
        friend class AutoPtr<VideoRender>;
        friend class AutoPtr<Subgroup>;
        friend class AutoPtr<OutboundDataSession>;
        friend class AutoPtr<InboundDataSession>;
        friend class AutoPtr<Peer>;
        friend class AutoPtr<PlanetKitCall>;
        friend class AutoPtr<PlanetKitConference>;
        friend class AutoPtr<PeerVideoStatus>;
        friend class AutoPtr<PeerHold>;
        friend class AutoPtr<PeerControl>;
        friend class AutoPtr<ConnectParam>;
        friend class AutoPtr<SendVoiceProcessor>;
        friend class AutoPtr<VideoFrame>;
        friend class AutoPtr<CallInitData>;
        friend class AutoPtr<MyMediaStatus>;
        friend class AutoPtr<CreateVideoCapturerResult>;
        friend class AutoPtr<Configuration>;
        friend class AutoPtr<PlanetKitManager>;
        friend class AutoPtr<AudioManager>;
        friend class AutoPtr<HookedAudio>;
        friend class AutoPtr<Image>;

        friend class AutoPtr<Mic>;
        friend class AutoPtr<Speaker>;
    };

}
