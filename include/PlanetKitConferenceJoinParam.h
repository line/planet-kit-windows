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

#include "PlanetKit.h"
#include "IPlanetKitConferenceEvent.h"
#include "PlanetKitVideoCommon.h"
#include "PlanetKitAudioCommon.h"
#include "PlanetKitAudioDevice.h"
#include "PlanetKitConnectParam.h"

namespace PlanetKit
{
    PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
    /**
     * @deprecated This will not be supported in 5.2 or later.
     */
    constexpr int PLNK_CONFERENCE_ROOM_TYPE_DEFAULT = 0;
    
    PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
    /**
     * @deprecated This will not be supported in 5.2 or later.
     */
    constexpr int PLNK_CONFERENCE_ROOM_TYPE_SUBGRP = 0;

    /**
     * @deprecated This will not be supported in 5.2 or later.
     * @remark
     *  - The option to set a room type when joining a conference room has been removed.
     */
    typedef enum EConferenceRoomType {
    } EConferenceRoomType;

    class PLANETKIT_API ConferenceJoinParam;
    typedef AutoPtr<ConferenceJoinParam> ConferenceJoinParamPtr;

    class PLANETKIT_API ConferenceJoinParam : virtual public ConnectParam {

    public:
        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         */
        ConferenceJoinParam* CreateWithAPIKey(const InitUserId& myID, const char* szAPIKey);

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         */
        ConferenceJoinParam* CreateWithAccessToken(const InitUserId& myID, const char* szAccessToken, int nAccessTokenLength);


        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use ConferenceJoinParamPtr CreateWithAPIKey(UserIdPtr pMyID, const wchar_t* szRoomID, const wchar_t* szRoomServiceID, const wchar_t* szAPIKey)")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see ConferenceJoinParamPtr CreateWithAPIKey(UserIdPtr pMyID, const wchar_t* szRoomID, const wchar_t* szRoomServiceID, const wchar_t* szAPIKey)
         */
        ConferenceJoinParamPtr CreateWithAPIKey(const UserId& myID, const char* szAPIKey);

        /**
         * Creates an instance of the ConferenceJoinParam class with an API key.
         * @param pMyID Local user's ID and service ID
         * @param szRoomID Room ID string, which should be encoded in UTF-16 and null-terminated
         * @param szRoomServiceID Room service ID string, which should be encoded in UTF-16 and null-terminated
         * @param szAPIKey API key string, which should be encoded in UTF-16 and null-terminated
         * @return
         *  - This API can fail if either szRoomID, szRoomServiceID, or szAPIKey is nullptr.<br>
         *  - If failed to create a Configuration class, returns nullptr.
         */
        static ConferenceJoinParamPtr CreateWithAPIKey(UserIdPtr pMyID, const wchar_t* szRoomID, const wchar_t* szRoomServiceID, const wchar_t* szAPIKey);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use ConferenceJoinParamPtr CreateWithAccessToken(UserIdPtr pMyID, const wchar_t* szRoomID, const wchar_t* szRoomServiceID, const wchar_t* szToken)")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see ConferenceJoinParamPtr CreateWithAccessToken(UserIdPtr pMyID, const wchar_t* szRoomID, const wchar_t* szRoomServiceID, const wchar_t* szToken)
         */
        ConferenceJoinParamPtr CreateWithAccessToken(const UserId& myID, const char* szAccessToken, int nAccessTokenLength);

        /**
         * Creates an instance of the ConferenceJoinParam class with an access token.
         * @param pMyID Local user's ID and service ID
         * @param szRoomID Room ID string, which should be encoded in UTF-16 and null-terminated
         * @param szRoomServiceID Room service ID string, which should be encoded in UTF-16 and null-terminated
         * @param szToken Access token string, which should be encoded in UTF-16 and null-terminated
         * @return
         *  - This API can fail if either szRoomID, szRoomServiceID, or szToken is nullptr.<br>
         *  - If failed to create a Configuration class, returns nullptr.
         */
        static ConferenceJoinParamPtr CreateWithAccessToken(UserIdPtr pMyID, const wchar_t* szRoomID, const wchar_t* szRoomServiceID, const wchar_t* szToken);

    public:

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use const wchar_t* GetDisplayName()")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see const wchar_t* GetDisplayName()
         */
        const char* DisplayName();

        /**
         * Gets the local user's display name string.
         * @return
         *  - String which is encoded in UTF-16 and null-terminated.
         */
        virtual const wchar_t* GetDisplayName() = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use const wchar_t* GetRoomId()")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see const wchar_t* GetRoomId()
         */
        const char* RoomId();

        /**
         * Gets the room ID string.
         * @return
         *  - String which is encoded in UTF-16 and null-terminated.
         */
        virtual const wchar_t* GetRoomId() = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use const wchar_t* GetRoomServiceId()")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see const wchar_t* GetRoomServiceId()
         */
        const char* RoomServiceId();

        /**
         * Gets the room service ID string.
         * @return
         *  - String which is encoded in UTF-16 and null-terminated.
         */
        virtual const wchar_t* GetRoomServiceId() = 0;

        /**
         * Gets the instance of the IConferenceEvent listener class.
         */
        virtual IConferenceEvent* ConferenceEvent() = 0;
        
        /// Checks the hardware video codec.
        virtual bool UseRxHWVidCodec() = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @remark
         *  - The option to set a room type when joining a conference room has been removed.
         */
        EConferenceRoomType ConferenceRoomType();

        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later.")
        /**
         * @deprecated This will not be supported in 4.4 or later.
         */
        bool ShareCameraStatus();

        /// Gets the flag of auto disconnect when the network is bad.
        virtual bool DisableAutoDisconnectOnBadNetwork() =0;

        /// Gets the "Allow Conference Without Mic" flag that you set.
        virtual bool IsAllowConferenceWithoutMic() = 0;

        // pBitrateKbps will be set to 0 for default bitrate
        /// Gets the preferred video resolution and bitrate.
        virtual bool PreferredVideoResolutionBitrate(EVideoResolution eResolution, int* pBitrateKbps) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use void SetDisplayName(const wchar_t* szMyDisplayName)")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see void SetDisplayName(const wchar_t* szMyDisplayName)
         */
        void SetDisplayName(const char* szMyDisplayName);

        /**
         * Sets the display name.
         * @param szMyDisplayName The local user's display name string, which should be encoded in UTF-16 and null-terminated.
         * @remark
         *  - If the parameter is nullptr, then clear stored "DisplayName" in class.
         */
        virtual void SetDisplayName(const wchar_t* szMyDisplayName) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use void SetRoomId(const wchar_t* szRoomId)")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see void SetRoomId(const wchar_t* szRoomId)
         */
        void SetRoomId(const char* szRoomId);

        /**
         * Sets the room ID.
         * @param szRoomId Room ID string, which should be encoded in UTF-16 and null-terminated.
         * @remark
         *  - This API can fail when the parameter is nullptr.
         */
        virtual void SetRoomId(const wchar_t* szRoomId) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use void SetRoomServiceId(const wchar_t* szRoomServiceId)")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see void SetRoomServiceId(const wchar_t* szRoomServiceId)
         */
        void SetRoomServiceId(const char* szRoomServiceId);

        /**
         * Sets the room service ID.
         * @param szRoomServiceId Room service ID, which should be encoded in UTF-16 and null-terminated.
         * @remark
         *  - This API can fail when the parameter is nullptr.
         */
        virtual void SetRoomServiceId(const wchar_t* szRoomServiceId) = 0;

        /// Sets a conference callback event instance.
        virtual void SetConferenceEvent(IConferenceEvent* pEvent) = 0;
        
        /// Sets the flag of using hardware video codec.
        virtual void SetUseRxHWVidCodec(bool bUseRxHWVidCodec) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later.")
        /**
         * @deprecated This will not be supported in 4.4 or later.
         */
        void SetShareCameraStatus(bool bShare);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @remark
         *  - The option to set a room type when joining a conference room has been removed.
         */
        void SetConferenceRoomType(EConferenceRoomType eRoomType);

        /// Sets the flag of auto disconnect when the network is bad.
        virtual void SetDisableAutoDisconnectOnBadNetwork(bool bDisable) = 0;

        /// Sets the "Allow Conference Without Mic" flag.
        /// Setting this flag to true enables joining the conference when PlanetKit can't start the microphone.
        virtual void SetAllowConferenceWithoutMic(bool bAllowConferenceWithoutMic) = 0;

        /**
        * Sets the preferred video resolution bitrate.
        * @remark
        *   eResolution range [PLNK_VIDEO_RESOLUTION_THUMBNAIL : PLNK_VIDEO_RESOLUTION_MAX]
        *   Do not set preferred bitrate to use the default PlanetKit bitrate.
        **/
        virtual bool SetPreferredVideoResolutionBitrate(EVideoResolution eResolution, int nBitrateKbps) = 0;


        /// Gets the app server data.
        virtual const wchar_t* GetAppServerData() = 0;


        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use void SetAppServerData(const wchar_t* szAppServerData)")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see void SetAppServerData(const wchar_t* szAppServerData)
         */
        void SetAppServerData(const char* szAppServerData);

        /**
         * Sets the app server data.<br>
         * @param szAppServerData App server data that is encoded in UTF-16.
         * @remark
         *  - If the parameter is nullptr, the app server data stored in the class is cleared.<br>
         *  - After converting szAppServerData to UTF-8, if it exceeds 4096 bytes including the null-termination character, the connection will fail.<br>
         *  - In case of failure, the error code is PLNK_START_FAIL_REASON_TOO_LONG_APP_SERVER_DATA.
         */
        virtual void SetAppServerData(const wchar_t* szAppServerData) = 0;

        /// Gets the API Key.
        virtual const wchar_t* GetAPIKey() = 0;

        /// Gets the access token.
        virtual const wchar_t* GetAccessToken() = 0;

        /// Gets the connect token.
        virtual EConnectToken ConnectToken() = 0;

        /// Sets the media type.
        virtual void SetIsVideoCall(bool bVideoCall) = 0;

    public:
        virtual int ToString(char* szBuff, int nSize) = 0;

    protected:
        ConferenceJoinParam() {}
        virtual ~ConferenceJoinParam() {}
    };
}
