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
#include "PlanetKitTypes.h"
#include "PlanetKitAudioDevice.h"
#include "PlanetKitVideoController.h"
#include "IPlanetKitConferenceEvent.h"

#include "IPlanetKitResultHandler.h"
#include "PlanetKitDataSessionInterface.h"
#include "PlanetKitContentShareInterface.h"
#include "PlanetKitSubgroupInterface.h"
#include "PlanetKitConferenceJoinParam.h"
#include "PlanetKitPeer.h"
#include "IPlanetKitVideoCapturerChange.h"
#include "PlanetKitStatistics.h"
#include "PlanetKitSendVoiceProcessor.h"
#include "PlanetKitMyMediaStatus.h"


namespace PlanetKit 
{
    /* Forward declaration */
    class PLANETKIT_API IConferenceEvent;

    class PLANETKIT_API PlanetKitConference;
    typedef AutoPtr<PlanetKitConference> PlanetKitConferencePtr;

    class PLANETKIT_API IConferenceAudioReceiver
    {
    public:
        virtual void OnAudio(const SAudioData * pAudioData) = 0;
    };

    PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use IVideoReceiver class.")
    /**
     * @deprecated This will not be supported in 5.0 or later.
     * @see IVideoReceiver
     */
    class PLANETKIT_API IConferenceVideoReceiver
    {
    };

    PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
    /**
     * @deprecated This will not be supported in 5.2 or later.
     */
    typedef struct SShortDataTarget {
        const char* szUserId;
        const char* szServiceId;

    } SShortDataTarget;

    enum ERequestPeerVideoType {
        PLNK_REQUEST_PEER_VIDEO_CALLBACK_RESULT = 0,
        PLNK_REQUEST_PEER_VIDEO_CALLBACK_RESULT_AFTER_RESOLUTION
    };

    /// Request video result callback class for ConferenceCall
    class PLANETKIT_API IRequestVideoResultHandler {
    public:
        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         */
        void OnResult(PlanetKitConference *pPlanetKitConference, SRequestMediaResultParam* pRequestMediaResult, void* pUserData);

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         */
        void OnRequestVideoResolutionResult(PlanetKitConference *pPlanetKitConference, SRequestVideoResolutionResultParam* pReqVidResResultParam, void* pUserData);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use RequestPeerVideoResultCallback")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see RequestPeerVideoResultCallback
         */
        void OnResult(PlanetKitConferencePtr pPlanetKitConference, SRequestMediaResultParam* pRequestMediaResult, void* pUserData);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use RequestPeerVideoResolutionCallback")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see RequestPeerVideoResolutionCallback
         */
        void OnRequestVideoResolutionResult(PlanetKitConferencePtr pPlanetKitConference, SRequestVideoResolutionResultParam* pReqVidResResultParam, void* pUserData);
    };

    /**
     * Prototype of the callback function to receive the result of RequestPeerVideo
     */
    using RequestPeerVideoResultCallback = void(*)(PlanetKitConferencePtr pPlanetKitConference, SRequestMediaResultParam* pRequestMediaResult, void* pUserData);

    /**
     * Prototype of the callback function to receive the result of RequestPeerVideo
     */
    using RequestPeerVideoResolutionCallback = void(*)(PlanetKitConferencePtr pPlanetKitConference, SRequestVideoResolutionResultParam* pReqVidResResultParam, void* pUserData);
    


    class PLANETKIT_API PlanetKitConference :
        public Base,
        public IVideoCapturerChange
    {
    public:

        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later. Use Leave()")
        /**
        * @deprecated This will not be supported in 5.1 or later.
        * @see Leave
        */
        bool Leave(EDisconnectReason eCallEndReason);

        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later. Use LeaveConference()")
        /**
        * @deprecated This will not be supported in 5.1 or later.
        * @see LeaveConference
        */
        bool Leave();

        /**
        * Leaves the conference.
        * @return true on success
        */
        virtual bool LeaveConference() = 0;


        /**
        * Registers an event delegate.
        * @param pEvent
        * @return true on success
        */
        virtual bool RegisterConferenceEvent(IConferenceEvent *pEvent) = 0;
        

        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use MuteMyAudio(void *pMuteResultUserData, IResultHandler *pMuteResultHandler")
        /**
        * @deprecated This will not be supported in 4.4 or later.
        * @see UnmuteMyAudio
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
        * Mutes the local user's audio in the conference.
        * @param bMute Whether to mute
        * @return true on success
        */
        virtual bool MuteMyAudio(bool bMute, void *pMuteResultUserData, IResultHandler *pMuteResultHandler) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use UnmuteMyAudio(void *pMuteResultUserData, IResultHandler *pMuteResultHandler")
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

        /// Gets whether the local user's audio is muted.
        virtual bool IsMyAudioMuted() = 0;


        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use PauseMyVideo(void *pPauseResultUserData, IResultHandler *pPauseResultHandler")
        /**
        * @deprecated This will not be supported in 4.4 or later.
        * @see PauseMyVideo
        */
        bool PauseMyVideo(void *pPauseResultUserData, IResultHandler *pPauseResultHandler,
            void *pShareResultUserData, IResultHandler *pShareResultHandler);

        /**
        * Pauses the local user's video in the conference.
        * @return true on success
        */
        virtual bool PauseMyVideo(void *pPauseResultUserData, IResultHandler *pPauseResultHandler) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use ResumeMyVideo(void *pResumeResultUserData, IResultHandler *pResumeResultHandler")
        /**
        * @deprecated This will not be supported in 4.4 or later.
        * @see ResumeMyVideo
        */
        bool ResumeMyVideo(void *pResumeResultUserData, IResultHandler *pResumeResultHandler,
            void *pShareResultUserData, IResultHandler *pShareResultHandler);

        /**
        * Resumes the local user's video in the conference.
        * @return true on success
        */
        virtual bool ResumeMyVideo(void *pResumeResultUserData, IResultHandler *pResumeResultHandler) = 0;


        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use GetMyVideoStatus()")
        /**
        * @deprecated This will not be supported in 4.4 or later.
        * @see GetMyVideoStatus
        */
        bool IsMyVideoPaused();

        /// Gets the local user's video status.
        virtual VideoStatus GetMyVideoStatus() = 0;


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use bool SetAudioInputDevice(AudioDevicePtr pDevice)")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see SetAudioInputDevice
        */
        bool SetAudioInputDevice(AudioDevice *pDevice);


        /**
        * Sets the audio input device used in the conference. Pass nullptr to remove the audio device from the conference.
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
        * Sets the audio output device used in the conference. Pass nullptr to remove the audio device from the conference.
        * @param pDevice Audio output device.
        * @return true on success
        */
        virtual bool SetAudioOutputDevice(AudioDevicePtr pDevice) = 0;


        /**
        * Registers the local user's audio receiver to the conference.
        * @param pReceiver Audio receiver to register.
        * @return true on success
        */
        virtual bool RegisterMyAudioReceiver(IConferenceAudioReceiver *pReceiver) = 0;


        /**
        * Registers the peer's audio receiver to the conference.
        * @param pReceiver Audio receiver to register.
        * @return true on success
        */
        virtual bool RegisterPeersAudioReceiver(IConferenceAudioReceiver *pReceiver) = 0;


        /**
        * Deregisters the local user's audio receiver from the conference.
        * @param pReceiver Audio receiver to deregister.
        * @return true on success
        */
        virtual bool DeregisterMyAudioReceiver(IConferenceAudioReceiver *pReceiver) = 0;


        /**
        * Deregisters the peer's audio receiver from the conference.
        * @param pReceiver Audio receiver to deregister.
        * @return true on success
        */
        virtual bool DeregisterPeersAudioReceiver(IConferenceAudioReceiver *pReceiver) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see
         *  - bool RequestPeerVideo(UserIdPtr pPeerId, const wchar_t* szSubgroupName, EVideoResolution eVideoResolution)
         *  - bool RequestPeerVideo(UserIdPtr pPeerId, const wchar_t* szSubgroupName, EVideoResolution eVideoResolution, void* pUserData, RequestPeerVideoResultCallback pResultCallback)
         *  - bool RequestPeerVideo(UserIdPtr pPeerId, const wchar_t* szSubgroupName, EVideoResolution eVideoResolution, void* pUserData, RequestPeerVideoResolutionCallback pResultCallback)
         */
        bool RequestPeerVideo(
            const char *szPeerId,
            const char *szPeerServiceId,
            const char *szSubgroupName,
            EVideoResolution eVideoResolution,
            void* pResultUserData,
            IRequestVideoResultHandler* pResultHandler,
            void* pReqVidResResultUserData,
            IRequestVideoResultHandler* pReqVidResResultHandler
        );

        /**
         * Requests a subgroup member's video from the server.<br>
         * This method returns false if the given member is not included in this session, or the given peer has not joined with video, or the given maxResolution is invalid.<br>
         * For a given peer, this API may be called several times. But only the last maxResolution will be applied.
         * @param pPeerId ID of the peer whose video you want to request.
         * @param szSubgroupName Subgroup name string, which is encoded in UTF-16 and null-terminated.
         * @param eVideoResolution Max resolution of the video that you wish to receive from the peer.
         * @remark
         *  - This API works asynchronously. If you want to get the result of API call, use the other two overloaded APIs.
         * @see
         *  - https://docs.lineplanet.me/windows/extended-functions/peer-video-resolution-in-group-call
         */
        virtual bool RequestPeerVideo(
            UserIdPtr pPeerId,
            const wchar_t* szSubgroupName,
            EVideoResolution eVideoResolution
        ) = 0;

        /**
         * Requests a subgroup member's video from the server.<br>
         * This method returns false if the given member is not included in this session, or the given peer has not joined with video, or the given maxResolution is invalid.<br>
         * For a given peer, this API may be called several times. But only the last maxResolution will be applied.
         * @param pPeerId ID of the peer whose video you want to request.
         * @param szSubgroupName Subgroup name string, which is encoded in UTF-16 and null-terminated.
         * @param eVideoResolution Max resolution of the video that you wish to receive from the peer.
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pCallback A callback function to be called after the API worked.
         * @remark
         *  - This API works asynchronously. The callback function is called immediately after the API worked.
         * @see
         *  - https://docs.lineplanet.me/windows/extended-functions/peer-video-resolution-in-group-call
         */
        virtual bool RequestPeerVideo(
            UserIdPtr pPeerId,
            const wchar_t* szSubgroupName,
            EVideoResolution eVideoResolution,
            void* pUserData,
            RequestPeerVideoResultCallback pCallback
        ) = 0;
        
        /**
         * Requests a subgroup member's video from the server.<br>
         * This method returns false if the given member is not included in this session, or the given peer has not joined with video, or the given maxResolution is invalid.<br>
         * For a given peer, this API may be called several times. But only the last maxResolution will be applied.
         * @param pPeerId ID of the peer whose video you want to request.
         * @param szSubgroupName Subgroup name string, which is encoded in UTF-16 and null-terminated.
         * @param eVideoResolution Max resolution of the video that you wish to receive from the peer.
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pCallback A callback function to be called after the API worked.
         * @remark
         *  - This API works asynchronously. The callback is called when max resolution is reached after the API worked.
         * @see
         *  - https://docs.lineplanet.me/windows/extended-functions/peer-video-resolution-in-group-call
         */
        virtual bool RequestPeerVideo(
            UserIdPtr pPeerId,
            const wchar_t* szSubgroupName,
            EVideoResolution eVideoResolution,
            void* pUserData,
            RequestPeerVideoResolutionCallback pCallback
        ) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see bool StopPeerVideo(UserIdPtr pPeerId, const wchar_t* szSubgroupName, void* pUserData, RequestPeerVideoResultCallback pCallback)
         */
        bool StopPeerVideo(const char *szPeerId, const char *szPeerServiceId, const char *szSubgroupName, void* pUserData, IRequestVideoResultHandler* pResultHandler);

        /**
         * Stops the video stream from a peer in the conference instance.
         * @param pPeerId ID of the peer whose video you want to stop.
         * @param szSubgroupName Subgroup name string, which is encoded in UTF-16 and null-terminated.
         * @param szPeerServiceId Service ID of the peer whose video you want to stop.
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pCallback A callback function to be called after the API worked.
         * @remark
         *  - This API works asynchronously. The callback function is called immediately after the API worked.
         */
        virtual bool StopPeerVideo(UserIdPtr pPeerId, const wchar_t* szSubgroupName, void* pUserData, RequestPeerVideoResultCallback pCallback) = 0;


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use bool AddPeerRender(const char *szPeerId, const char *szPeerServiceId, VideoRenderPtr pRender)")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see AddPeerRender
        */
        bool AddPeerRender(const char *szPeerId, const char *szPeerServiceId, VideoRender *pRender);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see VideoController::AddPeerView()
         * @remark
         * - The logic to add a specific peer's view should be performed through the VideoController.
         */
        bool AddPeerRender(const char *szPeerId, const char *szPeerServiceId, VideoRenderPtr pRender);


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use bool RemovePeerRender(const char *szPeerId, const char *szPeerServiceId, VideoRenderPtr pRender)")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see RemovePeerRender
        */
        bool RemovePeerRender(const char *szPeerId, const char *szPeerServiceId, VideoRender *pRender);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see VideoController::RemovePeerView()
         * @remark
         * - The logic to remove a specific peer's view should be performed through the VideoController.
         */
        bool RemovePeerRender(const char *szPeerId, const char *szPeerServiceId, VideoRenderPtr pRender);


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        */
        bool RegisterMyVideoReceiver(IConferenceVideoReceiver *pReceiver);


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        */
        bool RegisterPeersVideoReceiver(IConferenceVideoReceiver *pReceiver);


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        */
        bool RegisterMyScreenShareReceiver(IConferenceVideoReceiver *pReceiver);


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        */
        bool RegisterPeerScreenShareReceiver(IConferenceVideoReceiver *pReceiver);


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        */
        bool DeregisterMyVideoReceiver(IConferenceVideoReceiver *pReceiver);


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        */
        bool DeregisterPeersVideoReceiver(IConferenceVideoReceiver *pReceiver);


        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see VideoController::AddMyView()
         * @remark
         * - The logic to add a local user's view should be performed through the VideoController.
         */
        bool AddMyVideoRender(VideoRenderPtr pRender);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see VideoController::RemoveMyView()
         * @remark
         * - The logic to remove a specific my view should be performed through the VideoController.
         */
        bool RemoveMyVideoRender(VideoRenderPtr pRender);


        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see VideoController::RegisterMyVideoReceiver
         * @remark
         * - Video-related controls are available via the VideoController from version 5.2 onward.
         */
        bool RegisterMyVideoReceiver(IVideoReceiver *pReceiver);



        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see VideoController::RegisterPeersVideoReceiver
         * @remark
         * - Video-related controls are available via the VideoController from version 5.2 onward.
         */
        bool RegisterPeersVideoReceiver(IVideoReceiver *pReceiver);


        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see ScreenShareController::RegisterMyScreenShareVideoReceiver
         * @remark
         * - Screen share related controls are available via the ScreenShareController from version 5.2 onward.
         */
        bool RegisterMyScreenShareReceiver(IVideoReceiver *pReceiver);


        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see ScreenShareController::RegisterPeerScreenShareVideoReceiver
         * @remark
         * - Screen share related controls are available via the ScreenShareController from version 5.2 onward.
         */
        bool RegisterPeerScreenShareReceiver(IVideoReceiver *pReceiver);


        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see VideoController::DeregisterMyVideoReceiver
         * @remark
         * - Video-related controls are available via the VideoController from version 5.2 onward.
         */
        bool DeregisterMyVideoReceiver(IVideoReceiver *pReceiver);


        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see VideoController::DeregisterPeersVideoReceiver
         * @remark
         * - Video-related controls are available via the VideoController from version 5.2 onward.
         */
        bool DeregisterPeersVideoReceiver(IVideoReceiver *pReceiver);


        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see VideoController::DeregisterMyVideoReceiver
         * @remark
         * - Video-related controls are available via the VideoController from version 5.2 onward.
         */
        bool DeregisterMyScreenShareReceiver();

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see ScreenShareController::RegisterPeerScreenShareVideoReceiver
         * @remark
         * - Screen share related controls are available via the ScreenShareController from version 5.2 onward.
         */
        bool DeregisterPeerScreenShareReceiver();


        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use GetPeerList(ConferencePeer*& pDstPeers)")
        /**
        * @deprecated This will not be supported in 4.4 or later.
        * @see GetPeerList
        */
        bool GetPeerList(ConferencePeerInfos** pDstPeerInfos);


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use PeerArray GetPeerList()")
        /**
        * @deprecated This will not be supported in 4.4 or later.
        * @see GetPeerList
        */
        bool GetPeerList(ConferencePeers*& pDstPeers);

        /**
        * Gets the peer list in the main room.
        * @return Array of Peers
        */
        virtual bool GetPeerList(PeerArray& arrPeerListResult) = 0;


        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use GetAudioActivePeerList(ConferencePeer*& pDstPeers)")
        /**
        * @deprecated This will not be supported in 4.4 or later.
        * @see GetAudioActivePeerList
        */
        bool GetAudioActivePeerList(ConferencePeerInfos** pDstPeerInfos);


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use PeerArray GetAudioActivePeerList()")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see IConferenceEvent.OnPeersAudioDescriptionUpdated
        */
        bool GetAudioActivePeerList(ConferencePeers*& pDstPeers);

        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later.")
        /**
         * @deprecated This will not be supported in 5.1 or later.
         */
        bool SendShortData(const SShortData *pShortData, SShortDataTarget *pTargets, unsigned int unTargetCount, void *pResultUserData, IResultHandler *pResultHandler);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. See bool SendShortData(const wchar_t* szType, void* pData, unsigned int nSize, UserIdPtr pPeerId, void* pUserData, IResultHandler* pResultHandler)")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see bool SendShortData(const wchar_t* szType, void* pData, unsigned int nSize, UserIdPtr pPeerId, void* pUserData, IResultHandler* pResultHandler)
         */
        bool SendShortData(const SShortData *pShortData, SShortDataTarget sTarget, void *pResultUserData, IResultHandler *pResultHandler);

        /**
         * Sends short data to a connected peer in the conference.<br>
         * This API returns false when the szType or pData exceeds the size limit or when szType or pData are nullptr.
         * @param szType User-defined data type to be sent along with the short data. After being converted to UTF-8, it must not exceed 100 bytes including the null-termination character.
         * @param pData Short data. The maximum size of is 800 bytes.
         * @param nSize The size of pData.
         * @param pPeerId ID of the peer to whom to send the short data.
         * @return true on success
         */
        virtual bool SendShortData(const wchar_t* szType, void* pData, unsigned int nSize, UserIdPtr pPeerId, void* pUserData, IResultHandler* pResultHandler) = 0;
    
        /**
         * Sends short data to all peers.<br>
         * This API returns false when the szType or pData exceeds the size limit or when szType or pData are nullptr.
         * @param szType User-defined data type to be sent along with the short data. After being converted to UTF-8, it must not exceed 100 bytes including the null-termination character.
         * @param pData Short data. The maximum size of is 800 bytes.
         * @param nSize The size of pData.
         * @return true on success
         */
        virtual bool SendShortDataToAllPeers(const wchar_t* szType, void* pData, unsigned int nSize, void* pUserData, IResultHandler* pResultHandler) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use bool EnableVideo(VideoCapturerPtr pVideoCapturer, void *pResultUserData, IResultHandler *pResultHandler)")
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
        bool EnableVideo(VideoCapturerPtr pVideoCapturer, void *pResultUserData, IResultHandler *pResultHandler);

        /**
         * Enables video transmission.
         * @return true on success
         * @remark
         * - Switches to a video call.
         * - If a specific camera has not been selected, the default camera will be chosen.
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
        * @return true on success
        */
        virtual bool DisableVideo(void *pResultUserData, IResultHandler *pResultHandler) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use IPlanetKitConferenceEvent.OnMyAudioDescriptionUpdated()")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see OnMyAudioDescriptionUpdated
        */
        unsigned char GetMyAudioLevel();

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use IPlanetKitConferenceEvent.OnPeersAudioDescriptionUpdated()")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see OnPeersAudioDescriptionUpdated
        */
        unsigned int GetConferenceAudioLevel();

        /**
        * Gets the conference duration.
        * @return Call duration in milliseconds. Returns -1 on error.
        */
        virtual int GetConferenceDuration() = 0;
        
        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use bool Hold(const wchar_t* szHoldReason, void* pUserData, IResultHandler* pResultHandler)")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see bool Hold(const wchar_t* szHoldReason, void* pUserData, IResultHandler* pResultHandler)
         */
        bool Hold(const char *szHoldReason, void *pResultUserData, IResultHandler *pResultHandler);

        /**
         * Holds the conference.
         * @param szHoldReason Hold reason string that is encoded in UTF-16 and null-terminated.
         * @return true on success
         */
        virtual bool Hold(const wchar_t* szHoldReason, void* pUserData, IResultHandler* pResultHandler) = 0;

        /**
         * Unholds the conference.
         * @return true on success
         */
        virtual bool Unhold(void* pResultUserData, IResultHandler* pResultHandler) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see Unicast : RequestPeerMute
         * @see Broadcast : RequestPeersMute
         */
        bool RequestMutePeerAudioSend(const char *szPeerId, const char *szPeerServiceId, bool bMute, void *pResultUserData, IResultHandler *pResultHandler);

        /**
         * Sends a request to a peer to mute/unmute their audio. bMute will be sent to the peer.
         * @param pPeerId Peer's ID.
         * @param bMute Whether to mute or unmute
         * @return true on success
         */
        virtual bool RequestPeerMute(UserIdPtr pPeerId, bool bMute, void* pUserData, IResultHandler* pResultHandler) = 0;

        /**
         * Sends a request to all peers to mute/unmute their audio.
         * @param bMute Whether to mute or unmute
         * @return true on success
         */
        virtual bool RequestPeersMute(bool bMute, void* pUserData, IResultHandler* pResultHandler) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see Unicast : RequestPeerMute
         * @see Broadcast : RequestPeersMute
         */
        bool RequestMuteAllPeerAudioSend(bool bMute, void* pResultUserData, IResultHandler* pResultHandler);

        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later.")
        /**
        * @deprecated This will not be supported in 4.4 or later.
        * @remark You can get peer's video state in ConferencePeer class that can get GetPeerList API.
        * @see GetPeerList
        * @see ConferencePeer
        */
        bool GetPeerVideoPauseState(const char *szPeerId, const char *szPeerServiceId, bool *bIsPaused, EVideoPauseReason *pReason);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
        * @deprecated This will not be supported in 5.2 or later.
        * @see SilencePeersAudio
        */
        bool SilencePeerAudio(bool bSilence, void *pResultUserData, IResultHandler *pResultHandler);

        /**
        * Silences peer audio.
        * @param bSilence Set true to silence peer audio. Set false to unsilence.
        * @return true on success
        */
        virtual bool SilencePeersAudio(bool bSilence, void *pResultUserData, IResultHandler *pResultHandler) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
        * @deprecated This will not be supported in 5.2 or later.
        * @see IsPeersAudioSilenced
        */
        bool IsPeerAudioSilenced();

        /**
        * Gets the silence state for peer audio.
        * @return true if silenced.
        */
        virtual bool IsPeersAudioSilenced() = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use bool StartMyScreenShare(const wchar_t* szSubgroupName, void *pUserData, IResultHandler *pResultHandler)")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see bool StartMyScreenShare(const wchar_t* szSubgroupName, void *pUserData, IResultHandler *pResultHandler)
         */
        bool StartMyScreenShare(const char* szSubgroupName, void *pResultUserData, IResultHandler *pResultHandler);

        /**
         * Starts screen share.
         * @param szToSubgroupName Destination subgroup name string that is encoded in UTF-16 and null-terminated.
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pResultHandler A callback function to be called after the API worked.
         * @return true on success
         */
        virtual bool StartMyScreenShare(ScreenShareInfoPtr pScreenShareInfo, const wchar_t* szSubgroupName, void *pUserData, IResultHandler* pResultHandler) = 0;

        /**
         * Stops screen share. If the result is true, remove the screen share capturer.
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pResultHandler A callback function to be called after the API worked.
         * @return true on success
         */
        virtual bool StopMyScreenShare(void* pUserData, IResultHandler* pResultHandler) = 0;

        /**
         * Stops screen share with a reason. If the result is true, remove the screen share capturer.
         * @param nUserReason Value must be between 0 and 39.
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pResultHandler A callback function to be called after the API worked.
         * @return true on success
         */
        virtual bool StopMyScreenShare(int nUserReason, void* pUserData, IResultHandler* pResultHandler) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see Subgroup : ChangeMyScreenShareDestination
         * @see Mainroom : ChangeMyScreenShareDestinationToMainRoom
         */
        bool ChangeMyScreenShareGroup(const char* szToSubgroupName, void *pResultUserData, IResultHandler *pResultHandler);

        /**
         * Changes the screen share destination.
         * @param szToSubgroupName Destination subgroup name string that is encoded in UTF-16 and null-terminated.
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pResultHandler A callback function to be called after the API worked.
         * @return true on success
         */
        virtual bool ChangeMyScreenShareDestination(const wchar_t* szToSubgroupName, void* pUserData, IResultHandler* pResultHandler) = 0;

        /**
         * Changes the screen share destination to the main room.
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pResultHandler A callback function to be called after the API worked.
         * @return true on success
         */
        virtual bool ChangeMyScreenShareDestinationToMainRoom(void* pUserData, IResultHandler* pResultHandler) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see bool RequestPeerScreenShare(UserIdPtr pPeerId, const wchar_t* szSubgroupName, void* pUserData, RequestPeerVideoResultCallback pCallback)
         */
        bool RequestPeerScreenShare(const char* szPeerId, const char* szPeerServiceId, const char* szSubgroupName, void *pResultUserData, IRequestVideoResultHandler* pResultHandler);

        /**
         * Requests a peer's screen share.
         * @param pPeerId ID of the peer to whom you want to request screen share.
         * @param szSubgroupName Subgroup name string, which is encoded in UTF-16 and null-terminated.
         * @param pUSerData User's data that will be passed along when the callback function is called.
         * @param pCallback A callback function to be called after the API worked.
         * @remark
         *  - This API works asynchronously. The callback function is called immediately after the API worked.
         */
        virtual bool RequestPeerScreenShare(
            UserIdPtr pPeerId,
            const wchar_t* szSubgroupName,
            void* pUserData,
            RequestPeerVideoResultCallback pCallback
        ) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see bool StopPeerScreenShare(UserIdPtr pPeerId, const wchar_t* szSubgroupName, void* pUserData, RequestPeerVideoResultCallback pCallback)
         */
        bool StopPeerScreenShare(const char* szPeerId, const char* szPeerServiceId, const char* szSubgroupName, void *pResultUserData, IRequestVideoResultHandler* pResultHandler);

        /**
         * Stops a peer's screen share.
         * @param pPeerId ID of the peer whose screen share you want to stop.
         * @param szSubgroupName Subgroup name string, which is encoded in UTF-16 and null-terminated.
         * @param pUSerData User's data that will be passed along when the callback function is called.
         * @param pCallback A callback function to be called after the API worked.
         * @remark
         *  - This API works asynchronously. The callback function is called immediately after the API worked.
         */
        virtual bool StopPeerScreenShare(UserIdPtr pPeerId, const wchar_t* szSubgroupName, void* pUserData, RequestPeerVideoResultCallback pCallback) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use bool SetMyScreenShareCapturer(VideoCapturerPtr pCapturer)")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see SetMyScreenShareCapturer
        */
        bool SetMyScreenShareCapturer(VideoCapturer *pCapturer);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see ScreenShareController::StartScreenShareCapture
         */
        bool SetMyScreenShareCapturer(VideoCapturerPtr pCapturer);

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use bool AddPeerScreenShareRender(const char *szPeerId, const char *szPeerServiceId, const char* szSubgrpName, VideoRenderPtr pRender)")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         * @see AddPeerScreenShareRender
         */
        bool AddPeerScreenShareRender(const char *szPeerId, const char *szPeerServiceId, const char* szSubgrpName, VideoRender *pRender);
        
        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see bool ScreenShareController::AddPeerView
         */
        bool AddPeerScreenShareRender(const char *szPeerId, const char *szPeerServiceId, const char* szSubgrpName, VideoRenderPtr pRender);

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use bool RemovePeerScreenShareRender(const char *szPeerId, const char *szPeerServiceId, const char* szSubgrpName, VideoRenderPtr pRender)")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         * @see RemovePeerScreenShareRender
         */
        bool RemovePeerScreenShareRender(const char *szPeerId, const char *szPeerServiceId, const char* szSubgrpName, VideoRender * pRender);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. bool RemovePeerScreenShareRender(UserIdPtr pPeerId, const wchar_t* szSubgroupName, VideoRenderPtr pRender)")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see bool RemovePeerScreenShareRender(UserIdPtr pPeerId, const wchar_t* szSubgroupName, VideoRenderPtr pRender)
         */
        bool RemovePeerScreenShareRender(const char *szPeerId, const char *szPeerServiceId, const char* szSubgrpName, VideoRenderPtr pRender);


        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see bool ScreenShareController::RemovePeerView
         */
        bool RemovePeerScreenShareRender(UserIdPtr pPeerId, const wchar_t* szSubgroupName, VideoRenderPtr pRender);

        PLANETKIT_DEPRECATED("This will not be supported in 4.3 or later. Use GetSendVoiceProcessor")
        /**
        * @deprecated This will not be supported in 4.3 or later.
        * @see GetSendVoiceProcessor
        */
        bool SetNoiseSuppressor(bool bEnable, NULLABLE void *pResultUserData, NULLABLE IResultHandler *pResultHandler);


        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later.")
        /**
         * @deprecated This will not be supported in 5.1 or later.
         */
        bool AudioSendSetHighPriority(bool bHighPriority, void *pResultUserData, IResultHandler *pResultHandler);

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use ContentShareInterfaceOptional GetContentShareInterface()")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         * @see GetContentShareInterface
         */
        bool GetContentShareInterface(ContentShareInterface** ppContentShareInterface);

        /**
         * Gets the content share interface.
         * @return
         *   ContentShareInterfacePtr on success.<br>
         *   ContentShareInterfacePtr with nullptr means the API worked well but there is no ContentShareInterface.<br> 
         *   If the API failed, you can get PlanetKit::nullOpt.
         */
        virtual ContentShareInterfaceOptional GetContentShareInterface() = 0;
        
        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use GetSubgroupManager(SubgroupManager*& pSubgroupInterface)")
        /**
         * @deprecated This will not be supported in 4.4 or later.
         * @see GetSubgroupManager
         */
        bool GetSubgroupInterface(SubgroupInterface** ppSubgroupInterface);


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use SubgroupManagerPtr GetSubgroupManager()")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         * @see GetSubgroupManager
         */
        bool GetSubgroupManager(SubgroupManager*& pSubgroupManager);

        /**
        * Gets the Subgroup manager.
        * On a successful function call, a reference to the internal subgroup manager will be assigned to pSubgroupManager.
        * @return
        *   SubgroupManagerPtr on success.<br>
        *   SubgroupManagerPtr with nullptr means the API worked well but there is no Subgroup.<br> 
        *   If this API fails, you can get PlanetKit::nullOpt.
        * @remark
        *   There's no need to call the Release() API after using the return value but you can set nullptr to explicitly decrement the reference count.
        */
        virtual SubgroupManagerPtr GetSubgroupManager() = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
        * @deprecated This will not be supported in 5.2 or later.
        * @see PutUserAcousticEchoCancellerReference
        */
        int PutAECReferenceData(const SAudioData* pAudioData);

        /**
         * Puts reference audio data for automatic echo cancellation.
         * If PlanetKitConference::StartUserAcousticEchoCancellerReference() is called, the user must provide reference audio data for the AEC feature using this method.
         * @param pAudioData Reference audio data
         * @return Size of audio reference data in bytes
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
         * @param pUserData Callback parameter to be passed after executing the method.
         * @param pResultHandler Result handler to be called after executing the method.
         */
        virtual bool StartUserAcousticEchoCancellerReference(void* pUserData, IResultHandler* pResultHandler) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
        * @deprecated This will not be supported in 5.2 or later.
        * @see StopUserAcousticEchoCancellerReference
        */
        bool StopAECReferenceData(void *pResultUserData, IResultHandler *pResultHandler);

        /**
        * Stops AEC reference data.
        * @param pResultUserData Callback parameter to be passed after executing method.
        * @param pResultHandler Result handler to be called after executing the method.
        */
        virtual bool StopUserAcousticEchoCancellerReference(void *pResultUserData, IResultHandler *pResultHandler) = 0;


        // For debug purposes.
        // Internal use only.
        virtual int DebugMonitoringInfo(char *szBuffer, size_t nBufferSize) = 0;

        /// Gets the local user's equipment type.
        virtual EUserEquipmentType MyUserEquipmentType() = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use const wchar_t* GetMyDisplayName()")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see const wchar_t* GetMyDisplayName()
         */
        const char* MyDisplayName();

        /// Gets the local user's display name.
        virtual const wchar_t* GetMyDisplayName() = 0;

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
         *  The return value can be PlanetKit::nullOpt when this instance doesn't have statistics information.
         */
        virtual StatisticsOptional GetStatistics() = 0;

        /**
         * Gets the send voice processor
         * @return Send voice processor
         */
        virtual SendVoiceProcessorPtr GetSendVoiceProcessor() = 0;

        /**
         * Returns the maximum number of peer videos that can be received simultaneously.
         * @return Maximum number of peer videos
         */
        virtual unsigned int GetPeersVideoMaxCount() = 0;

        /**
         * Returns the maximum number of peer screen share that can be received simultaneously.
         * @return Maximum number of peer screen share
         */
        virtual unsigned int GetPeersScreenShareMaxCount() = 0;

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
         * Gets an instance of MyMediaStatus.
         */
        virtual MyMediaStatusPtr GetMyMediaStatus() = 0;
    };
}
