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

#include "PlanetKitMakeCallParam.h"
#include "PlanetKitVerifyCallParam.h"
#include "PlanetKitAudioDevice.h"

#include "IPlanetKitCallEvent.h"
#include "IPlanetKitVideoCapturerChange.h"

#include "IPlanetKitResultHandler.h"
#include "PlanetKitDataSessionInterface.h"
#include "PlanetKitContentShareInterface.h"

#include "PlanetKitStatistics.h"
#include "PlanetKitSendVoiceProcessor.h"

#include "PlanetKitVideoStatus.h"
#include "PlanetKitVideoCommon.h"


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

    PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use IVideoReceiver class.")
    /**
     * @deprecated This will not be supported in 5.2 or later.
     * @see IVideoReceiver
     */
    class PLANETKIT_API ICallVideoReceiver
    {
    };


    
    class PLANETKIT_API PlanetKitCall :
        public Base,
        public IVideoCapturerChange 
    {
    public:
        
        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later.")
        /**
        * @deprecated This will not be supported in 4.4 or later.
        * @see AcceptCall
        */
        SStartResult AcceptCall();

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see AcceptCall
        */
        void AcceptCall(EMediaType eMediaType, SCallInitData *pCallInitData);


        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
        * @deprecated This will not be supported in 5.2 or later.
        * @see AcceptCall
        */
        void AcceptCall(SCallInitData *pCallInitData);

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

        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later.")
        /**
        * @deprecated This will not be supported in 5.1 or later.
        * @see EndCall
        */
        void EndCall(EDisconnectReason eCallEndReason);

        /**
        * Ends an active/verified call.
        */
        virtual void EndCall() = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see void EndCall(const wchar_t* szUserReleaseCode)
         */
        void EndCallWithNormalUserCode(const char *szUserReleaseCode);

        /**
        * Ends an active/verified call.
        * @param szUserReleaseCode The user-specific reason for ending a call. The string can be up to 128 bytes including the null-termination character.
        * @remark Call this function if you perform EndCall with a reason without any special errors.
        */
        virtual void EndCall(const wchar_t* szUserReleaseCode) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
        * @deprecated This will not be supported in 5.2 or later.
        * @see EndCallWithError(const wchar_t* szUserReleaseCode)
        */
        void EndCallWithErrorUserCode(const char *strUserCode);

        /**
        * Ends an active/verified call.
        * @param szUserReleaseCode The user-specific reason for ending a call. The string can be up to 128 bytes including the null-termination character.
        * @remark Call this function if you perform EndCall with a reason if an error occurs.
        */
        virtual void EndCallWithError(const wchar_t* szUserReleaseCode) = 0;
            

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


        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use MuteMyAudio(void *pMuteResultUserData, IResultHandler *pMuteResultHandler)")
        /**
        * @deprecated This will not be supported in 4.4 or later.
        * @see MuteMyAudio
        */
        bool MuteMyAudio(void *pMuteResultUserData, IResultHandler *pMuteResultHandler,
            void *pShareResultUserData, IResultHandler *pShareResultHandler);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use MuteMyAudio(bool bMute, void *pMuteResultUserData, IResultHandler *pMuteResultHandler)")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see MuteMyAudio
         */
        bool MuteMyAudio(void *pMuteResultUserData, IResultHandler *pMuteResultHandler);

        /**
        * Mutes or unmutes the local user's audio in the call.
        * @param bMute Whether to mute or unmute
        * @return true on success
        */
        virtual bool MuteMyAudio(bool bMute, void *pMuteResultUserData, IResultHandler *pMuteResultHandler) = 0;


        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use UnmuteMyAudio(void *pMuteResultUserData, IResultHandler *pMuteResultHandler)")
        /**
        * @deprecated This will not be supported in 4.4 or later.
        * @see UnmuteMyAudio
        */
        bool UnmuteMyAudio(void *pMuteResultUserData, IResultHandler *pMuteResultHandler,
            void *pShareResultUserData, IResultHandler *pShareResultHandler);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use MuteMyAudio(bool bMute, void *pMuteResultUserData, IResultHandler *pMuteResultHandler)")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see MuteMyAudio
         */
        bool UnmuteMyAudio(void *pMuteResultUserData, IResultHandler *pMuteResultHandler);


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
        * @return true on success
        */
        virtual bool PauseMyVideo(void *pResultUserData, IResultHandler *pResultHandler) = 0;

        /**
        * Resumes the local user's video in the call.
        * @return true on success
        */
        virtual bool ResumeMyVideo(void *pResultUserData, IResultHandler *pResultHandler) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use bool ResumeMyVideo(VideoCapturerPtr pVideoCapture, void *pResultUserData, IResultHandler *pResultHandler)")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see ResumeMyVideo
        */
        bool ResumeMyVideo(VideoCapturer *pVideoCapture, void *pResultUserData, IResultHandler *pResultHandler);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use bool ResumeMyVideo(void *pResultUserData, IResultHandler *pResultHandler)")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see ResumeMyVideo
         * - If you wish to change the camera device, you can do so by calling the VideoController::SelectCamera method.
         */
        bool ResumeMyVideo(VideoCapturerPtr pVideoCapture, void *pResultUserData, IResultHandler *pResultHandler);


        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use GetMyVideoStatus")
        /**
        * @deprecated This will not be supported in 4.4 or later.
        * @see GetMyVideoStatus
        */
        bool IsMyVideoPaused();

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

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use bool SetAudioInputDevice(AudioDevicePtr pDevice)")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see SetAudioInputDevice
        */
        bool SetAudioInputDevice(AudioDevice *pDevice);

        /**
        * Set audio input device used in the call. Pass nullptr to remove audio device from call.
        * @param pDevice Audio input device.
        * @return true on success
        */
        virtual bool SetAudioInputDevice(AudioDevicePtr pDevice) = 0;


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use bool SetAudioOutputDevice(AudioDevicePtr pDevice)")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see SetAudioOutputDevice
        */
        bool SetAudioOutputDevice(AudioDevice *pDevice);


        /**
        * Set audio output device used in the call. Pass nullptr to remove audio device from call.
        * @param pDevice Audio output device.
        * @return true on success
        */
        virtual bool SetAudioOutputDevice(AudioDevicePtr pDevice) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use bool AddPeerRender(VideoRenderPtr pVideoRender)")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see AddPeerRender
        */
        bool AddPeerRender(VideoRender *pVideoRender);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see VideoController::AddPeerView
         * @remark
         * - If you wish to add a Peer View, you can use the AddPeerView method of the VideoController.
         */
        bool AddPeerRender(VideoRenderPtr pVideoRender);


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use bool RemovePeerRender(VideoRenderPtr pVideoRender)")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see RemovePeerRender
        */
        bool RemovePeerRender(VideoRender *pVideoRender);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see 
         * - VideoController::RemovePeerView 
         * - VideoController::ClearPeerView 
         * @remark
         * - If you wish to remove a Peer View, you can use the RemovePeerView or ClearPeerView method of the VideoController.
         */
        bool RemovePeerRender(VideoRenderPtr pVideoRender);


        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see VideoController::RegisterMyVideoReceiver
         * @remark
         * - Video-related controls are available via the VideoController from version 5.2 onward.
         */
        bool RegisterMyVideoReceiver(ICallVideoReceiver *pReceiver);


        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see VideoController::RegisterPeersVideoReceiver
         * @remark
         * - Video-related controls are available via the VideoController from version 5.2 onward.
         */
        bool RegisterPeersVideoReceiver(ICallVideoReceiver *pReceiver);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see ScreenShareController::RegisterPeerScreenShareVideoReceiver
         * @remark
         * - Screen share related controls are available via the ScreenShareController from version 5.2 onward.
         */
        bool RegisterPeerScreenShareVideoReceiver(ICallVideoReceiver *pReceiver);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see VideoController::DeregisterMyVideoReceiver
         * @remark
         * - Video-related controls are available via the VideoController from version 5.2 onward.
         */
        bool DeregisterMyVideoReceiver(ICallVideoReceiver *pReceiver);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see VideoController::DeregisterPeersVideoReceiver
         * @remark
         * - Video-related controls are available via the VideoController from version 5.2 onward.
         */
        bool DeregisterPeersVideoReceiver(ICallVideoReceiver *pReceiver);


        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see ScreenShareController::DeregisterPeerScreenShareVideoReceiver
         * @remark
         * - Screen share related controls are available via the ScreenShareController from version 5.2 onward.
         */
        bool DeregisterPeerScreenShareVideoReceiver();


        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use bool SendShortData(const wchar_t* szType, void* pData, unsigned int nSize, void *pResultUserData, IResultHandler *pResultHandler)")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see bool SendShortData(const wchar_t* szType, void* pData, unsigned int nSize, void *pResultUserData, IResultHandler *pResultHandler)
         */
        bool SendShortData(const SShortData *pShortData, void *pResultUserData, IResultHandler *pResultHandler);

        /**
         * Sends short data to the peer.<br>
         * This API returns false when the szType or pData exceeds the size limit or when szType or pData are nullptr.
         * @param szType After being converted to UTF-8, it must not exceed 100 bytes including the null-termination character.
         * @param pData The maximum size of pData is 800 bytes.
         * @param nSize The size of pData.
         * @return true on success
         */
        virtual bool SendShortData(const wchar_t* szType, void* pData, unsigned int nSize, void *pResultUserData, IResultHandler *pResultHandler) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use bool EnableVideo(VideoCapturerPtr pVideoCapture, void *pResultUserData, IResultHandler *pResultHandler)")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see EnableVideo
        */
        bool EnableVideoSend(VideoCapturer *pVideoCapturer, void *pResultUserData, IResultHandler *pResultHandler);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use bool EnableVideo(void *pResultUserData, IResultHandler *pResultHandler)")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see EnableVideo
         * @remark
         * - If you wish to change the Camera, please use the SelectCamera API of the VideoController.
         */
        bool EnableVideo(VideoCapturerPtr pVideoCapture, void *pResultUserData, IResultHandler *pResultHandler);

        /**
        * Enables video transmission. 
        * @return true on success
        * @remark
        * - Switches to a video call.
        */
        virtual bool EnableVideo(void *pResultUserData, IResultHandler *pResultHandler) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use bool DisableVideo(void *pResultUserData, IResultHandler *pResultHandler)")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see DisableVideo
        */
        bool DisableVideoSend(void *pResultUserData, IResultHandler *pResultHandler);

        /**
        * Disables video transmission.
        * @param eReason
        * @return true on success
        */
        virtual bool DisableVideo(void *pResultUserData, IResultHandler *pResultHandler) = 0;


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use ICallEvent.onMyVolumeUpdated")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see onMyVolumeUpdated
        */
        unsigned unsigned char GetMyAudioLevel();


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use ICallEvent.OnPeerAudioDescriptionUpdated")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see OnPeerAudioDescriptionUpdated
        */
        unsigned char GetPeerAudioLevel();



        /**
        * Gets the call duration.
        * @return Call duration in milliseconds. Returns -1 on error.
        */
        virtual int GetCallDuration() = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use Hold(const char *szHoldReason, bool bPauseReceive, void *pResultUserData, IResultHandler *pResultHandler)")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         * @see Hold(const char *szHoldReason, bool bPauseReceive, void *pResultUserData, IResultHandler *pResultHandler)
         */
        bool Hold(const char *szHoldReason, bool bPauseReceive, void *pResultUserData, IResultHandler *pResultHandler);


        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see RequestPeerMute
         */
        bool Hold(const char *szHoldReason, void *pResultUserData, IResultHandler *pResultHandler);

        /**
         * Holds the call.
         * @param szHoldReason Hold reason string, which is encoded in UTF-16 and null-terminated.<br>The string can be up to 256 bytes.<br>If the string exceeds the size, content beyond the limit is truncated.
         * @param pResultUSerData User data returned when pResultHandler is called.
         * @param pResultHandler Pointer to a listener class that notifies the result of this API.
         * @return true on success
         */
        virtual bool Hold(const wchar_t* szHoldReason, void* pResultUserData, IResultHandler* pResultHandler) = 0;

        /**
        * Unholds the call.
        * @return true on success
        */
        virtual bool Unhold(void *pResultUserData, IResultHandler *pResultHandler) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use RequestPeerMute")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see RequestPeerMute
         */
        bool RequestMutePeerAudioSend(bool bMute, void *pResultUserData, IResultHandler *pResultHandler);

        /**
        * Sends a request to the peer to mute or unmute their audio. bMute will be sent to sId.    
        * @param bMute
        * @return true on success
        */
        virtual bool RequestPeerMute(bool bMute, void *pResultUserData, IResultHandler *pResultHandler) = 0;
        

        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use GetPeerVideoStatus")
        /**
        * @deprecated This will not be supported in 4.4 or later.
        * @see GetPeerVideoPauseState
        */
        bool GetPeerVideoPauseState(bool  *bIsPaused, EVideoPauseReason *pReason);

        /**
        * Gets the peer's video pause state.
        * @return VideoStatus
        * @remark eVideoPauseReason in VideoStatus is only valid when eVideoState == PLNK_VIDEO_STATE_PAUSED.
        */            
        virtual VideoStatus GetPeerVideoStatus() = 0;


        /**
        * Silences the peer's audio.
        * @param bSilence Set true to silence peer audio. Set false to unsilence.
        * @return true on success
        */
        virtual bool SilencePeerAudio(bool bSilence, void *pResultUserData, IResultHandler *pResultHandler) = 0;


        /**
        * Gets the silence state for peer audio.
        * @return true on success
        */
        virtual bool IsPeerAudioSilenced() = 0;


        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use StartMyScreenShare(ScreenShareInfoPtr pScreenShareInfo, void *pResultUserData, IResultHandler *pResultHandler)")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see StartMyScreenShare(ScreenShareInfoPtr pScreenShareInfo, void *pResultUserData, IResultHandler *pResultHandler)
         */
        bool StartMyScreenShare(void *pResultUserData, IResultHandler *pResultHandler);


        /**
        * Starts the local user's screen share. If the result is true, add a screen share capturer.
        * @return true on success
        */
        virtual bool StartMyScreenShare(ScreenShareInfoPtr pScreenShareInfo, void *pResultUserData, IResultHandler *pResultHandler) = 0;



        /**
        * Stops the local user's screen share. If the result is true, remove the screen share capturer.
        * @return true on success
        */
        virtual bool StopMyScreenShare(void *pResultUserData, IResultHandler *pResultHandler) = 0;

        /**
        * Stops the local user's screen share with a reason. If the result is true, remove the screen share capturer.
        * @param nUserReason Value must be between 0 and 39.
        * @return true on success
        */
        virtual bool StopMyScreenShare(int nUserReason, void *pResultUserData, IResultHandler *pResultHandler) = 0;


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use bool SetMyScreenShareCapturer(VideoCapturerPtr pCapturer)")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         * @see SetMyScreenShareCapturer
         */
        bool SetMyScreenShareCapturer(VideoCapturer *pCapturer);
        
        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see ScreenShareController
         * @remark
         * - Direct usage of Capturer is no longer supported. Please select the window or screen you wish to capture using ScreenShareController.
         */
        bool SetMyScreenShareCapturer(VideoCapturerPtr pCapturer);

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use bool AddPeerScreenShareRender(VideoRenderPtr pRender)")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         * @see AddPeerScreenShareRender
         */
        bool AddPeerScreenShareRender(VideoRender *pRender);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see ScreenShareController::AddScreenShareView
         * @remark
         * - If you wish to add a window to be rendered, please use the ScreenShareController::AddScreenShareView API.
         */
        bool AddPeerScreenShareRender(VideoRenderPtr pRender);


        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see ScreenShareController::RemoveScreenShareView
         * @remark
         * - If you wish to add a window to be rendered, please use the ScreenShareController::RemoveScreenShareView API.
         */
        bool RemovePeerScreenShareRender();


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use ContentShareInterfaceOptional GetContentShareInterface()")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         * @see GetContentShareInterface
         */
        bool GetContentShareInterface(ContentShareInterface** ppContentShareInterface);

        /**
        * Gets the content share interface.<br>
        * On successful function call, reference to internal content share will be assigned to ppContentShareInterface.
        * @return
        *   ContentShareInterfacePtr on success.<br>
        *   ContentShareInterfacePtr with nullptr means API worked well but there is no ContentShareInterface.<br>
        *   If API fails, then you can get PlanetKit::nullOpt.
        */
        virtual ContentShareInterfaceOptional GetContentShareInterface() = 0;



        PLANETKIT_DEPRECATED("This will not be supported in 4.3 or later. Use GetSendVoiceProcessor")
        /**
        * @deprecated This will not be supported in 4.3 or later.
        * @see GetSendVoiceProcessor
        */
        bool SetNoiseSuppressor(bool bEnable, NULLABLE void *pResultUserData, NULLABLE IResultHandler *pResultHandler);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
        * @deprecated This will not be supported in 5.2 or later.
        * @see PutUserAcousticEchoCancellerReference
        */
       int PutAECReferenceData(const SAudioData* pAudioData);

        /**
        * Puts reference audio data for acoustic echo cancellation.
        * If PlanetKitCall::StartUserAcousticEchoCancellerReference() is called, the user must provide reference audio data for the AEC feature using this method.
        * @param pAudioData Reference audio data
        * @return Size of audio reference data written in bytes
        */
        virtual int PutUserAcousticEchoCancellerReference(const SAudioData* pAudioData) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
        * @deprecated This will not be supported in 5.2 or later.
        * @see StartUserAcousticEchoCancellerReference
        */
        bool StartAECReferenceData(void *pResultUserData, IResultHandler *pResultHandler);

        /**
        * Starts AEC reference data.
        * @param pResultUserData Callback parameter to be passed after executing the method.
        * @param pResultHandler Result handler to be called after executing the method.
        */
        virtual bool StartUserAcousticEchoCancellerReference(void *pResultUserData, IResultHandler *pResultHandler) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
        * @deprecated This will not be supported in 5.2 or later.
        * @see StartUserAcousticEchoCancellerReference
        */
        bool StopAECReferenceData(void *pResultUserData, IResultHandler *pResultHandler);

        /**
        * Stops AEC reference data.
        * @param pResultUserData Callback parameter to be passed after executing the method.
        * @param pResultHandler Result handler to be called after executing the method.
        */
        virtual bool StopUserAcousticEchoCancellerReference(void *pResultUserData, IResultHandler *pResultHandler) = 0;



        // For debug purposes.
        // Internal use only.
        virtual int DebugMonitoringInfo(char *szBuffer, size_t nBufferSize) = 0;


        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
        * @deprecated This will not be supported in 5.2 or later.
        * @see IDataSessionHandler::OnError(void* pUserData, EDataSessionFailReason eFailReason) 
        * @see EDataSessionFailReason = PLNK_DATA_SESS_FAIL_REASON_UNSUPPORTED
        */
        bool IsUsingDataSession(bool* pIsSupported);

        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later.")
        /**
         * @deprecated This will not be supported in 5.1 or later.
        */
        bool MakeSendDataSession(int nStreamId, EDataSessionType eType,
            NULLABLE void *pResultUserData, NULLABLE IDataSessionHandler* pResultHandler,
            void *pExceptionUserData, IDataSessionExceptionHandler *pExceptionHandler
        );

        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later.")
        /**
         * @deprecated This will not be supported in 5.1 or later.
         */
        bool MakeRecvDataSession(int nStreamId, IDataSessionReceiver* pIDataSessionReceiver,
            NULLABLE void* pResultUserData, NULLABLE IDataSessionHandler* pResultHandler,
            void* pExceptionUserData, IDataSessionExceptionHandler* pExceptionHandler);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
        * @deprecated This will not be supported in 5.2 or later.
        * @see MakeOutboundDataSession
        */
        bool MakeSendDataSession(int nStreamId, EDataSessionType eType,
            NULLABLE void* pResultUserData, ISendDataSessionHandler* pSendDataSessionHandler
        );

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


        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
        * @deprecated This will not be supported in 5.2 or later.
        * @see MakeInboundDataSession
        */
        bool MakeReceiveDataSession(int nStreamId, NULLABLE void* pResultUserData, IReceiveDataSessionHandler* pReceiveDataSessionHandler);

        /**
         * Makes an inbound data session.
         * @param nStreamId Stream ID from 100 to 999
         * @param pResultUserData You can specify data to be passed along when pResultHandler is called.
         * @param pDataSessionHandler Specifies the callback handler that is called when receiving data or when an exception occurs.
         * @return true on successful function call. Must check the result.
         */
        virtual bool MakeInboundDataSession(int nStreamId, NULLABLE void* pResultUserData, IInboundDataSessionHandler* pDataSessionHandler) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use GetDataSession")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see GetOutboundDataSession
         */
        bool GetSendDataSession(int nStreamId, SendDataSessionInterfacePtr* pResult);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use GetDataSession")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see GetInboundDataSession
         */
        bool GetReceiveDataSession(int nStreamId, ReceiveDataSessionInterfacePtr* pResult);

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


        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
        * @deprecated This will not be supported in 5.2 or later.
        * @see UnsupportInboundDataSession
        */
        bool UnsupportRecvDataSession(DataSessionStreamIdT nStreamId);

        /**
        * Call this API when you do not want to support a specific StreamID.
        * @param nStreamId
        * @return true on success
        * @remark This API can only be called from the receiver of the DataSession.
        */
        virtual bool UnsupportInboundDataSession(DataSessionStreamIdT nStreamId) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use void SetMyVideoCapture(VideoCapturerPtr pCapturer)")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         * @see SetMyVideoCapture
         */
        void SetMyVideoCapture(VideoCapturer *pCapturer);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use VideoController::SelectCamera")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         * @see VideoController::SelectCamera
         * - If you wish to change the camera device, you can do so by calling the VideoController::SelectCamera method.
         */
        void SetMyVideoCapture(VideoCapturerPtr pCapturer);


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use StatisticsOptional GetStatistics()")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         * @see GetStatistics
         */
        bool GetStatistics(Statistics** pOutResultStatistics);

        /**
         * Gets statistics information.
         * @return
         *  You can get Statistics* on success.
         *  Return value can be PlanetKit::nullOpt when this instance doesn't have statistics information.
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
    };
}
