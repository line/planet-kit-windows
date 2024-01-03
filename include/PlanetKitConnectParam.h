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

#include "PlanetKitAudioDevice.h"

#include "PlanetKitUserId.h"
#include "IPlanetKitConferenceEvent.h"
#include "PlanetKitVideoCommon.h"
#include "PlanetKitAudioCommon.h"


namespace PlanetKit
{
    typedef AutoPtr<VideoCapturer> VideoCapturerPtr;
    typedef struct AudioDescriptionInfo
    {
        bool bEnableAudioDescription = true; 
        unsigned int unAudioDescriptionInterval = 500;
    }AudioDescriptionInfo;

    class PLANETKIT_API ConnectParam : public Base
    {        

    public :
        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use User().ServiceId()")
        /**
         * @deprecated This will not be supported in 4.4 or later.
         * @see InitUserId
         */
        const char* UserServiceId();

        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use User().Country()")
        /**
         * @deprecated This will not be supported in 4.4 or later.
         * @see InitUserId
         */
        const char* UserCountryCode();

        /// Gets the local user's identifier information class.
        virtual UserIdPtr GetUser() const = 0;

        /// Checks whether the media type is a video call.
        virtual bool IsVideoCall() = 0;
                        

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use AudioDeviceOptional GetAudioInputDevice()")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         * @see GetAudioInputDevice
         */
        AudioDevice* AudioInputDevice();

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use AudioDeviceOptional GetAudioOutputDevice()")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         * @see GetAudioOutputDevice
         */
        AudioDevice* AudioOutputDevice();

        // ConferenceJoinParam does not add a reference to AudioDevice/VideoCapturer.
        /// Gets the audio input device.
        virtual AudioDeviceOptional GetAudioInputDevice() = 0;
        /// Gets the audio output device.
        virtual AudioDeviceOptional GetAudioOutputDevice() = 0;
        
        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use VideoCapturerOptional GetMyVideoCapturer()")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         * @see GetMyVideoCapturer
         */
        VideoCapturer*              MyVideoCapturer();
        /// Gets the video sending capability.
        virtual const SVideoCapability& SendVideoCapability() = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see GetMaxSendLinkBandwidth
        * @see GetMaxReceiveLinkBandwidth
        * @see GetAudioInputNoSrcTimeOutSec
        * @see GetVideoInputNoSrcTimeOutSec
        */
        const SCommParam& CommParam();

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
        
        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later.")
        /**
         * @deprecated This will not be supported in 4.4 or later.
         * @see InitUserId
         */
        bool ShareMicStatus();

        /// Checks AEC reference from user is used.
        virtual bool AecReferenceFromUser() = 0;

        /// Checks whether statistics are used.
        virtual bool EnableStatistics() = 0;

    public: // for max length used for each string parameter, please refer to member variable. 

        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use Constructor")
        /**
         * @deprecated This will not be supported in 4.4 or later.
         * @see InitUserId
         */
        void SetUserId(const char* szUserId);

        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use Constructor")
        /**
         * @deprecated This will not be supported in 4.4 or later.
         * @see InitUserId
         */
        void SetUserServiceId(const char* szUserServiceId);

        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use User().Country(const char* lpszCountry)")
        /**
         * @deprecated This will not be supported in 4.4 or later.
         * @see InitUserId
         */
        void SetUserCountryCode(const char* szUserCountryCode);
        
        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use void SetAudioInputDevice(AudioDevicePtr& pDevice)")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         * @see SetAudioInputDevice
         */
        void SetAudioInputDevice(AudioDevice* pDevice);

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use void SetAudioOutputDevice(AudioDevicePtr& pDevice)")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         * @see SetAudioOutputDevice
         */
        void SetAudioOutputDevice(AudioDevice* pDevice);

        // CallInitParam does not add a reference to AudioDevice/VideoCapturer.
        /// Sets the audio input device.
        virtual void SetAudioInputDevice(AudioDevicePtr& pDevice) = 0;

        /// Sets the audio output device.
        virtual void SetAudioOutputDevice(AudioDevicePtr& pDevice) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use void SetMyVideoCapturer(VideoCapturerPtr& pDevice)")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         * @see SetMyVideoCapturer
         */
        void SetMyVideoCapturer(VideoCapturer* pVideoCapturer);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see VideoController
         * @remark
         * - If you wish to change the capturer (camera), you can do so by calling SelectCamera from the VideoController.
         */
        void SetMyVideoCapturer(VideoCapturerPtr& pVideoCapturer);

        /// Sets the video sending capability.
        virtual void SetSendVideoCapability(const SVideoCapability& sCapa) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see SetMaxSendLinkBandwidth
        * @see SetMaxReceiveLinkBandwidth
        * @see SetAudioInputNoSrcTimeOutSec
        * @see SetVideoInputNoSrcTimeOutSec
        * @see SetAllowConnectWithoutMic
        */
        void SetCommParam(const SCommParam& sParam);

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
        virtual void SetEndTonePath(const char* szEndTonePath) = 0;
        /// Has the default value as ./wav_files/end_16k.wav.
        virtual const char* EndTonePath() = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later.")
        /**
         * @deprecated This will not be supported in 4.4 or later.
         * @see InitUserId
         */
        void SetShareMicStatus(bool bShare);

        /// Sets the AEC flag.
        virtual void SetAecReferenceFromUser(bool bAecReferenceFromUser) = 0;

        /// Sets the flag for using statistics.
        virtual void SetEnableStatistics(bool bEnableStatistics) = 0;

        /// Sets the audio description update callback interval (ms).
        /// If you do not want the callback, set bUse to false.
        virtual void SetAudioDescriptionInfo(bool bUse, unsigned int unAudioDescriptionInterval) = 0;

        /// Gets the audio description information.
        virtual AudioDescriptionInfo GetAudioDescriptionInfo() = 0;

    public:
        virtual int ToString(char* szBuff, int nSize) = 0;

    // protected apis
    protected :
        ConnectParam() {}
        virtual ~ConnectParam() {}
    };
};