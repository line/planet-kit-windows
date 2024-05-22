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
#include "PlanetKitVideoCommon.h"
#include "IPlanetKitResultHandler.h"
#include "PlanetKitDataSessionInterface.h"
#include "PlanetKitStatistics.h"
#include "PlanetKitSendVoiceProcessor.h"

#include "PlanetKitContentShareInterface.h"
#include "PlanetKitMakeCallParam.h"
#include "PlanetKitVerifyCallParam.h"
#include "IPlanetKitCallEvent.h"
#include "PlanetKitVideoStatus.h"
#include "PlanetKitMyMediaStatus.h"


namespace PlanetKit
{
    /* Forward declaration */
    class PLANETKIT_API PlanetKitCall;
    class PLANETKIT_API ICallEvent;

    /**
     * PlanetKit state of a 1-to-1 call
     */
    typedef enum ECallState {
        /// Idle
        CALL_IDLE,
        /// Trying to call
        CALL_TRYING,
        /// Waiting for an answer
        CALL_WAIT_ANSWER,
        /// Verified
        CALL_VERIFIED,
        /// Connected
        CALL_CONNECTED,
        /// Disconnected
        CALL_DISCONNECTED

    } ECallState;


    /* PlanetKitCall Receiver */
    class PLANETKIT_API ICallAudioReceiver
    {
    public:
        /**
        * Audio data callback called by the call instance. Called synchronously after audio is sent or received to/from the peer and the server.
        * @param pAudioData
        */
        virtual void OnAudio(const SAudioData * pAudioData) = 0;
    };

    
    class PLANETKIT_API PlanetKitCall : public Base {
    public:

        /**
         * Accepts an incoming call.
         * @param bPreparation If this value is true, the callee can delay connection until it calls FinishPreparation().
         * @param pCallStartMessage Call start message to send before the connection
         * @param bRecordOnCloud Whether to enable recording on the cloud.<br>DO NOT set this to true before consulting with the LINE Planet team.<br>If you want to use this feature, please contact us. (https://docs.lineplanet.me/ko/help/contact)
         * @remark
         *  - [Preparation guide]( @see https://docs.lineplanet.me/windows/extended-functions/responder-preparation-status ) <br>
         *  - [CallStartMessage guide]( @see https://docs.lineplanet.me/windows/extended-functions/call-start-message ) <br>
         */
        virtual void AcceptCall(bool bPreparation, CallStartMessagePtr pCallStartMessage = CallStartMessagePtr(nullptr), bool bRecordOnCloud = false) = 0;


        /**
        * Ends an active/verified call.
        */
        virtual void EndCall() = 0;


        /**
         * Ends an active/verified call.
         * @param strUserReleaseCode The user-specific reason for ending a call. The string can be up to 128 bytes including the null-termination character.
         * @remark Call this function if you perform EndCall with a reason without any special errors.
         */
        virtual void EndCall(const WString& strUserReleaseCode) = 0;

        /**
        * Ends an active/verified call.
        * @param strUserReleaseCode The user-specific reason for ending a call. The string can be up to 128 bytes including the null-termination character.
        * @remark Call this function if you perform EndCall with a reason if an error occurs.
        */
        virtual void EndCallWithError(const WString& strUserReleaseCode) = 0;

        /**
        * Finishes call preparation.
        * @return true on success
        */
        virtual bool FinishPreparation() = 0;


        /**
        * Gets the current call state.
        * @return ECallState
        */
        virtual ECallState GetCallState() = 0;

        /**
         * Mutes or unmutes the local user's audio in the call.
         * @param bMute Whether to mute or unmute
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         */
        virtual bool MuteMyAudio(bool bMute, void *pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
        * Checks whether the local user's audio is muted.
        * @return true if muted
        */
        virtual bool IsMyAudioMuted() = 0;

        /**
        * Checks whether the peer's audio is muted.
        * @return true if muted
        */
        virtual bool IsPeerMuted() = 0;

        /**
         * Pauses the local user's video in the call.
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         */
        virtual bool PauseMyVideo(void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Resumes the local user's video in the call.
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         */
        virtual bool ResumeMyVideo(void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
        * Checks whether the local user's video is paused.
        * @return VideoStatus
        * @remark eVideoPauseReason in VideoStatus is only valid when eVideoState == PLNK_VIDEO_STATE_PAUSED.
        */
        virtual VideoStatus GetMyVideoStatus() = 0;

        /**
        * Registers a call event delegate to the call.
        * @param pCallEvent.
        * @return true on success.
        */
        virtual bool RegisterCallEvent(ICallEvent *pCallEvent) = 0;

        /**
        * Set audio input device used in the call. Pass nullptr to remove audio device from call.
        * @param pDevice Audio input device.
        * @return true on success
        */
        virtual bool SetAudioInputDevice(AudioDevicePtr pDevice) = 0;

        /**
        * Set audio output device used in the call. Pass nullptr to remove audio device from call.
        * @param pDevice Audio output device.
        * @return true on success
        */
        virtual bool SetAudioOutputDevice(AudioDevicePtr pDevice) = 0;

        /**
         * Sends short data to the peer.<br>
         * This API returns false when the szType or pData exceeds the size limit or when szType or pData are nullptr.
         * @param strType After being converted to UTF-8, it must not exceed 100 bytes including the null-termination character.
         * @param pData The maximum size of pData is 800 bytes.
         * @param nSize The size of pData.
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         */
        virtual bool SendShortData(const WString& strType, void* pData, unsigned int nSize, void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Enables video transmission. 
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         * @remark
         * - Switches to a video call.
         */
        virtual bool EnableVideo(void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Disables video transmission.
         * @param eDisableReason Reason for disabling video.<br>The default value is PLNK_MEDIA_DISABLE_REASON_USER.
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         */
        virtual bool DisableVideo(EMediaDisabledReason eDisableReason = PLNK_MEDIA_DISABLE_REASON_USER, void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
        * Gets the call duration.
        * @return Call duration in milliseconds. Returns -1 on error.
        */
        virtual int GetCallDuration() = 0;

        /**
         * Holds the call.
         * @param strHoldReason Hold reason string, which is encoded in UTF-16 and null-terminated.<br>The string can be up to 256 bytes.<br>If the string exceeds the size, content beyond the limit is truncated.
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @param pResultUSerData User data returned when pResultHandler is called.
         * @param pResultHandler Pointer to a listener class that notifies the result of this API.
         * @return true on success
         */
        virtual bool Hold(const WStringOptional& strHoldReason = NullOptional, void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Unholds the call.
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         */
        virtual bool Unhold(void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Sends a request to the peer to mute or unmute their audio. bMute will be sent to sId.    
         * @param bMute
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         */
        virtual bool RequestPeerMute(bool bMute, void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
        * Gets the peer's video pause state.
        * @return VideoStatus
        * @remark eVideoPauseReason in VideoStatus is only valid when eVideoState == PLNK_VIDEO_STATE_PAUSED.
        */            
        virtual VideoStatus GetPeerVideoStatus() = 0;

        /**
         * Silences the peer's audio.
         * @param bSilence Set true to silence peer audio. Set false to unsilence.
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         */
        virtual bool SilencePeerAudio(bool bSilence, void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
        * Gets the silence state for peer audio.
        * @return true on success
        */
        virtual bool IsPeerAudioSilenced() = 0;

        /**
         * Starts the local user's screen share. If the result is true, add a screen share capturer.
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         */
        virtual bool StartMyScreenShare(ScreenShareInfoPtr pScreenShareInfo, void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Stops the local user's screen share. If the result is true, remove the screen share capturer.
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         */
        virtual bool StopMyScreenShare(void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Stops the local user's screen share with a reason. If the result is true, remove the screen share capturer.
         * @param nUserReason Value must be between 0 and 39.
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         */
        virtual bool StopMyScreenShare(int nUserReason, void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
        * Gets the content share interface.<br>
        * On successful function call, reference to internal content share will be assigned to ppContentShareInterface.
        * @return
        *   ContentShareInterfacePtr on success.<br>
        *   ContentShareInterfacePtr with nullptr means API worked well but there is no ContentShareInterface.<br>
        *   If API fails, then you can get PlanetKit::NullOptional.
        */
        virtual ContentShareInterfaceOptional GetContentShareInterface() = 0;

        /**
        * Puts reference audio data for acoustic echo cancellation.
        * If PlanetKitCall::StartUserAcousticEchoCancellerReference() is called, the user must provide reference audio data for the AEC feature using this method.
        * @param pAudioData Reference audio data
        * @return Size of audio reference data written in bytes
        */
        virtual int PutUserAcousticEchoCancellerReference(const SAudioData* pAudioData) = 0;

        /**
         * Starts AEC reference data.
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         */
        virtual bool StartUserAcousticEchoCancellerReference(void *pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Stops AEC reference data.
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         */
        virtual bool StopUserAcousticEchoCancellerReference(void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        // For debug purposes.
        // Internal use only.
        virtual int DebugMonitoringInfo(char *szBuffer, size_t nBufferSize) = 0;

        /**
         * Makes an outbound data session.
         * @param nStreamId Stream ID from 100 to 999
         * @param eType Data session type
         * @param pResultUserData You can specify data to be passed along when pDataSessionHandler is called.
         * @param pDataSessionHandler This is a callback handler that notifies the result of success or failure of outbound data session creation.
         * @return true on successful function call. Must check the result.
         */
        virtual bool MakeOutboundDataSession(int nStreamId, EDataSessionType eType,
            NULLABLE void* pResultUserData, IOutboundDataSessionHandler* pDataSessionHandler
            ) = 0;

        /**
         * Makes an inbound data session.
         * @param nStreamId Stream ID from 100 to 999
         * @param pResultUserData You can specify data to be passed along when pResultHandler is called.
         * @param pDataSessionHandler Specifies the callback handler that is called when receiving data or when an exception occurs.
         * @return true on successful function call. Must check the result.
         */
        virtual bool MakeInboundDataSession(int nStreamId, NULLABLE void* pResultUserData, IInboundDataSessionHandler* pDataSessionHandler) = 0;

        /**
         * Gets the existing outbound data session.
         * @param nStreamId Stream ID of the data session to get.
         * @param pResult Result OutboundDataSession.
         * @return true on success, false if it does not exist.
         */
        virtual bool GetOutboundDataSession(int nStreamId, OutboundDataSessionPtr* pResult) = 0;

        /**
         * Gets the existing inbound data session.
         * @param nStreamId Stream ID of the data session to get.
         * @param pResult Result InboundDataSession.
         * @return true on success, false if it does not exist.
         */
        virtual bool GetInboundDataSession(int nStreamId, InboundDataSessionPtr* pResult) = 0;

        /**
        * Call this API when you do not want to support a specific StreamID.
        * @param nStreamId
        * @return true on success
        * @remark This API can only be called from the receiver of the DataSession.
        */
        virtual bool UnsupportInboundDataSession(DataSessionStreamIdT nStreamId) = 0;

        /**
         * Gets statistics information.
         * @return
         *  You can get Statistics* on success.
         *  Return value can be PlanetKit::NullOptional when this instance doesn't have statistics information.
         */
        virtual StatisticsOptional GetStatistics() = 0;

        /**
         * Gets the send voice processor.
         * @return Send voice processor
         */
        virtual SendVoiceProcessorPtr GetSendVoiceProcessor() = 0;

        /**
         * Enables or disables the video share mode in screen share.
         * @remark
         * The video share mode optimizes screen share for video clip sharing. When the video share mode is enabled, resource usage may increase.<br>
         * The video share mode can be enabled before starting screen share or during ongoing screen share.
         */
        virtual bool SetMyScreenShareVideoShareMode(bool bVideoShareMode) = 0;

        /**
         * Gets whether the video share mode is enabled.
         */
        virtual bool IsMyScreenShareVideoShareModeEnabled() = 0;

        /**
        * Registers the local user's audio receiver to the call.
        * @param pReceiver Audio receiver to register.
        * @return true on success
        */
        virtual bool RegisterMyAudioReceiver(ICallAudioReceiver *pReceiver) = 0;

        /**
        * Registers the peer's audio receiver to the call.
        * @param pReceiver Audio receiver to register.
        * @return true on success
        */
        virtual bool RegisterPeerAudioReceiver(ICallAudioReceiver *pReceiver) = 0;

        /**
        * Deregisters the local user's audio receiver from the call.
        * @param pReceiver Audio receiver to deregister.
        * @return true on success
        */
        virtual bool DeregisterMyAudioReceiver(ICallAudioReceiver *pReceiver) = 0;

        /**
        * Deregisters the peer's audio receiver from the call.
        * @param pReceiver Audio receiver to deregister.
        * @return true on success
        */
        virtual bool DeregisterPeerAudioReceiver(ICallAudioReceiver *pReceiver) = 0;

        /**
         * Gets an instance of MyMediaStatus.
         */
        virtual MyMediaStatusPtr GetMyMediaStatus() = 0;
    };
}
