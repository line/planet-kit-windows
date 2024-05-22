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
#include "PlanetKitVideoCommon.h"
#include "PlanetKitAudioCommon.h"
#include "PlanetKitAudioDevice.h"

#include "IPlanetKitConferenceEvent.h"

namespace PlanetKit
{
    class PLANETKIT_API ConferenceParam;

    template class PLANETKIT_API AutoPtr<ConferenceParam>;
    typedef AutoPtr<ConferenceParam> ConferenceParamPtr;

    class PLANETKIT_API ConferenceParam : public Base {
    public:
        /**
         * Creates an instance of the ConferenceParam class with an API key.
         * @param pMyID Local user's ID and service ID
         * @param strRoomID Room ID string, which should be encoded in UTF-16 and null-terminated
         * @param strRoomServiceID Room service ID string, which should be encoded in UTF-16 and null-terminated
         * @param strAPIKey API key string, which should be encoded in UTF-16 and null-terminated
         * @return
         *  - This API can fail if either strRoomID, strRoomServiceID, or strAPIKey is nullptr.<br>
         *  - If failed to create a Configuration class, returns nullptr.
         * @deprecated
         *  - This API is deprecated and will be removed in a future release.
         */
        static ConferenceParamPtr CreateWithAPIKey(UserIdPtr pMyID, const WString& strRoomID, const WString& strRoomServiceID, const WString& strAPIKey);

        /**
         * Creates an instance of the ConferenceParam class with an access token.
         * @param pMyID Local user's ID and service ID
         * @param strRoomID Room ID string, which should be encoded in UTF-16 and null-terminated
         * @param strRoomServiceID Room service ID string, which should be encoded in UTF-16 and null-terminated
         * @param strToken Access token string, which should be encoded in UTF-16 and null-terminated
         * @return
         *  - This API can fail if either strRoomID, strRoomServiceID, or strToken is nullptr.<br>
         *  - If failed to create a Configuration class, returns nullptr.
         */
        static ConferenceParamPtr CreateWithAccessToken(UserIdPtr pMyID, const WString& strRoomID, const WString& strRoomServiceID, const WString& strToken);

        /**
         * Gets the local user's display name string.
         * @return
         *  - String which is encoded in UTF-16 and null-terminated.
         */
        virtual const WStringOptional& GetDisplayName() = 0;

        /**
         * Gets the room ID string.
         * @return
         *  - String which is encoded in UTF-16 and null-terminated.
         */
        virtual const WString& GetRoomId() = 0;

        /**
         * Gets the room service ID string.
         * @return
         *  - String which is encoded in UTF-16 and null-terminated.
         */
        virtual const WString& GetRoomServiceId() = 0;

        /**
         * Gets the instance of the IConferenceEvent listener class.
         */
        virtual IConferenceEvent* ConferenceEvent() = 0;
        
        /// Checks the hardware video codec.
        virtual bool UseRxHWVidCodec() = 0;

        /// Gets the "Allow Conference Without Mic" flag that you set.
        virtual bool IsAllowConferenceWithoutMic() = 0;

        /**
         * Gets the preferred video resolution and bitrate.
         * @param eResolution Preferred video resolution.
         * @param pBitrateKbps This will be set to 0 for default bitrate.
         */
        virtual bool PreferredVideoResolutionBitrate(EVideoResolution eResolution, int* pBitrateKbps) = 0;

        /**
         * Sets the display name.
         * @param strMyDisplayName The local user's display name string, which should be encoded in UTF-16 and null-terminated.<br>After being converted to UTF-8, it must not exceed 128 bytes including the null-termination character.
         * @remark
         *  - If the parameter is `NullOptional`, the `DisplayName` stored in the class will be cleared.<br>
         */
        virtual void SetDisplayName(const WStringOptional& strMyDisplayName) = 0;

        /**
         * Sets the room ID.
         * @param strRoomId Room ID string, which should be encoded in UTF-16 and null-terminated.
         * @remark
         *  - This API can fail when the parameter is nullptr.
         */
        virtual void SetRoomId(const WString& strRoomId) = 0;

        /**
         * Sets the room service ID.
         * @param strRoomServiceId Room service ID, which should be encoded in UTF-16 and null-terminated.
         * @remark
         *  - This API can fail when the parameter is nullptr.
         */
        virtual void SetRoomServiceId(const WString& strRoomServiceId) = 0;

        /// Sets a conference callback event instance.
        virtual void SetConferenceEvent(IConferenceEvent* pEvent) = 0;
        
        /// Sets the flag of using hardware video codec.
        virtual void SetUseRxHWVidCodec(bool bUseRxHWVidCodec) = 0;

        /**
         * Sets the "Allow Conference Without Mic" flag.<br>
         * Setting this flag to true enables joining the conference when PlanetKit can't start the microphone.
         */
        virtual void SetAllowConferenceWithoutMic(bool bAllowConferenceWithoutMic) = 0;

        /**
         * Sets the preferred video resolution bitrate.
         * @remark
         *   eResolution range [PLNK_VIDEO_RESOLUTION_THUMBNAIL : PLNK_VIDEO_RESOLUTION_MAX]<br>
         *   Do not set preferred bitrate to use the default PlanetKit bitrate.
         */
        virtual bool SetPreferredVideoResolutionBitrate(EVideoResolution eResolution, int nBitrateKbps) = 0;

        /// Gets the app server data.
        virtual const WString& GetAppServerData() = 0;

        /**
         * Sets the app server data.<br>
         * @param strAppServerData App server data that is encoded in UTF-16.
         * @remark
         *  - If the parameter is nullptr, the app server data stored in the class is cleared.<br>
         *  - After converting strAppServerData to UTF-8, if it exceeds 4096 bytes including the null-termination character, the connection will fail.<br>
         *  - In case of failure, the error code is PLNK_START_FAIL_REASON_TOO_LONG_APP_SERVER_DATA.
         */
        virtual void SetAppServerData(const WString& strAppServerData) = 0;

        /// Gets the API Key.
        virtual const WString& GetAPIKey() = 0;

        /// Gets the access token.
        virtual const WString& GetAccessToken() = 0;

        /// Gets the connect token.
        virtual EConnectToken ConnectToken() = 0;

        /// Sets the media type.
        virtual void SetIsVideoCall(bool bVideoCall) = 0;

        /// Gets the local user's identifier information class.
        virtual UserIdPtr GetUser() const = 0;

        /// Checks whether the media type is a video call.
        virtual bool IsVideoCall() = 0;

        // ConferenceParam does not add a reference to AudioDevice/VideoCapturer.
        /// Gets the audio input device.
        virtual AudioDeviceOptional GetAudioInputDevice() = 0;
        /// Gets the audio output device.
        virtual AudioDeviceOptional GetAudioOutputDevice() = 0;
        
        /// Gets the video sending capability.
        virtual const SVideoCapability& SendVideoCapability() = 0;
                /// Gets the maximum link bandwidth in kbps for sending.
        virtual unsigned int GetMaxSendLinkBandwidth() = 0;
        /// Gets the maximum link bandwidth in kbps for receiving.
        virtual unsigned int GetMaxReceiveLinkBandwidth() = 0;
        /// Gets the audio input no source timeout option.
        virtual int GetAudioInputNoSrcTimeOutSec() = 0;
        /// Gets the video input no source timeout option.
        virtual int GetVideoInputNoSrcTimeOutSec() = 0;

        // Set true to disable MLNS noise suppressor.
        /// Checks whether MLNS is used.
        virtual bool DisableMLNS() = 0;
        
        /// Checks AEC reference from user is used.
        virtual bool AecReferenceFromUser() = 0;

        /// Checks whether statistics are used.
        virtual bool EnableStatistics() = 0;

        // CallInitParam does not add a reference to AudioDevice/VideoCapturer.
        /// Sets the audio input device.
        virtual void SetAudioInputDevice(AudioDevicePtr pDevice) = 0;

        /// Sets the audio output device.
        virtual void SetAudioOutputDevice(AudioDevicePtr pDevice) = 0;

        /// Sets the video sending capability.
        virtual void SetSendVideoCapability(const SVideoCapability& sCapa) = 0;

        /// Sets the maximum link bandwidth in kbps for sending. Set 0 for default.
        virtual void SetMaxSendLinkBandwidth(unsigned int unMaxSendLinkBandwidth) = 0;
        /// Sets the maximum link bandwidth in kbps for receiving. Set 0 for default.
        virtual void SetMaxReceiveLinkBandwidth(unsigned int unMaxReceiveLinkBandwidth) = 0;
        /// Sets the audio input no source timeout option. Set 0 for no timeout.
        virtual void SetAudioInputNoSrcTimeOutSec(unsigned int nAudioInputNoSrcTimeOutSec) = 0;
        /// Sets the video input no source timeout option. Set 0 for no timeout.
        virtual void SetVideoInputNoSrcTimeOutSec(unsigned int nVideoInputNoSrcTimeOutSec) = 0;

        /// Enables/Disables MLNS.
        virtual void SetDisableMLNS(bool bDisable) = 0; // Set true to disable MLNS noise suppressor.

        /// Sets the end tone path.
        virtual void SetEndTonePath(const WString& strEndTonePath) = 0;
        /// Has the default value as ./wav_files/end_16k.wav.
        virtual const WString& EndTonePath() = 0;

        /// Sets the AEC flag.
        virtual void SetAecReferenceFromUser(bool bAecReferenceFromUser) = 0;

        /// Sets the flag for using statistics.
        virtual void SetEnableStatistics(bool bEnableStatistics) = 0;

        /// Sets the audio description update callback interval (ms).
        /// If you do not want the callback, set bUse to false.
        virtual void SetAudioDescriptionInfo(bool bUse, unsigned int unAudioDescriptionInterval) = 0;

        /// Gets the audio description information.
        virtual AudioDescriptionInfo GetAudioDescriptionInfo() = 0;

    protected:
        ConferenceParam() {}
        virtual ~ConferenceParam() {}
    };
}
