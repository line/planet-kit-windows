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

#include "PlanetKitCCParam.h"
#include "PlanetKitVideoCommon.h"
#include "IPlanetKitCallEvent.h"

namespace PlanetKit
{
    class PLANETKIT_API VerifyCallParam;
    typedef SharedPtr<VerifyCallParam> VerifyCallParamPtr;

    /// Call parameter for VerifyCall API
    class PLANETKIT_API VerifyCallParam {
    public:
        virtual ~VerifyCallParam() { }

        /**
         * Creates CallParam for using PlanetKitManager::VerifyCall with ccParam.
         * @remark
         *   You can create CCParamPtr by calling PlanetKitManager::CreateCCParam.
         */
        static VerifyCallParamPtr Create(UserIdPtr pMyID, CCParamPtr pCCParam);

        /// Gets CCParam
        virtual CCParamPtr GetCCParam() = 0;

        /// Gets the peer's user identifier information class.
        virtual UserIdPtr GetPeer() const = 0;

        /**
         * Gets the ring tone path.
         * @remark
         *  - The default value of ring tone path is L"./wav_files/ring_48k.wav".
         */
        virtual const WString& GetRingTonePath() = 0;

        /**
         * Gets the ringback tone path.
         * @remark
         *  - The default value of ringback tone path is L"./wav_files/ringback_48k.wav".
         */
        virtual const WString& GetRingBackTonePath() = 0;

        /**
         * Gets the hold tone path.
         * @remark
         *  - The default value of hold tone path is L"./wav_files/hold_48k.wav".
         */
        virtual const WString& GetHoldTonePath() = 0;

        /**
         * Gets the end tone path.
         * @remark
         *  - The default value of end tone path is L"./wav_files/end_48k.wav".
         */
        virtual const WString& GetEndTonePath() = 0;

        virtual ICallEventPtr CallEvent() = 0;

        /**
         * Gets the video receiving capability.
         */
        virtual const VideoCapabilityOptional RecvVideoCapability() = 0;

        /// Gets whether to allow making a 1-to-1 call even when PlanetKit can't start microphone.
        virtual bool IsAllowCallWithoutMic() = 0;

        /// Sets whether to allow making a 1-to-1 call even when PlanetKit can't start microphone.
        virtual void SetAllowCallWithoutMic(bool bAllowCallWithoutMic) = 0;

        /**
         * Sets the ring tone path.
         * @remark
         *  - The default value of ring tone path is L"./wav_files/ring_48k.wav".
         */
        virtual void SetRingTonePath(const WString& strRingTonePath) = 0;

        /**
         * Sets the ringback tone path.
         * @remark
         *  - The default value of ringback tone path is L"./wav_files/ringback_48k.wav".
         */
        virtual void SetRingBackTonePath(const WString& strRingBackTonePath) = 0;

        /**
         * Sets the hold tone path.
         * @remark
         *  - The default value of hold tone path is L"./wav_files/hold_48k.wav".
         */
        virtual void SetHoldTonePath(const WString& strHoldTonePath) = 0;

        /**
         * Sets the end tone path.
         * @remark
         *  - The default value of end tone path is L"./wav_files/end_48k.wav".
         */
        virtual void SetEndTonePath(const WString& strEndTonePath) = 0;

        /**
         * Sets the ICallEvent listener class.
         */
        virtual void SetCallEvent(ICallEventPtr pEvent) = 0;

        /**
         * Sets the video receiving capability.
         */
        virtual void SetRecvVideoCapability(const SVideoCapability& sCapa) = 0;

        /// Gets the local user's identifier information class.
        virtual UserIdPtr GetUser() const = 0;

        /// Checks whether the media type is a video call.
        virtual bool IsVideoCall() = 0;

        /// Gets the video sending capability.
        virtual const VideoCapabilityOptional SendVideoCapability() = 0;

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

        /// Sets the AEC flag.
        virtual void SetAecReferenceFromUser(bool bAecReferenceFromUser) = 0;

        /// Sets the flag for using statistics.
        virtual void SetEnableStatistics(bool bEnableStatistics) = 0;

        /// Sets the audio description update callback interval (ms).
        /// If you do not want the callback, set bUse to false.
        virtual void SetAudioDescriptionInfo(bool bUse, unsigned int unAudioDescriptionInterval) = 0;

        /// Gets the audio description information.
        virtual AudioDescriptionInfo GetAudioDescriptionInfo() = 0;

        /**
         * Sets whether the end tone should be played regardless of the call state.
         * @remark
         *  - When set to `true`, this function allows the end tone to be played regardless of the call state.<br>
         *  - The default value is `false`.
         */
        virtual void PlayEndtoneRegardlessOfCallState(bool bPlayEndtone) = 0;

        /**
         * Gets whether the end tone should be played regardless of the call state.
         */
        virtual bool IsPlayEndtoneRegardlessOfCallState() = 0;
    };
}
