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
#include "IPlanetKitResultHandler.h"
#include "PlanetKitDataSessionInterface.h"
#include "PlanetKitCameraController.h"
#include "PlanetKitScreenShareController.h"
#include "IPlanetKitConferenceEvent.h"
#include "PlanetKitStatistics.h"
#include "PlanetKitSendVoiceProcessor.h"
#include "PlanetKitMyMediaStatus.h"

#include "PlanetKitContentShareInterface.h"
#include "PlanetKitSubgroupInterface.h"
#include "PlanetKitConferenceParam.h"
#include "PlanetKitPeer.h"

#include "PlanetKitConferenceDefine.h"
#include "IPlanetKitConferenceAudioReceiver.h"
#include "IPlanetKitVideoReceiver.h"


namespace PlanetKit  {
    /* Forward declaration */
    class PLANETKIT_API IConferenceEvent;

    class PLANETKIT_API PlanetKitConference;
    typedef AutoPtr<PlanetKitConference> PlanetKitConferencePtr;

    class PLANETKIT_API PlanetKitConference : public Base {
    public:
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
        virtual bool RegisterConferenceEvent(IConferenceEventPtr pEvent) = 0;

        /**
         * Mutes the local user's audio in the conference.
         * @param bMute Whether to mute
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         */
        virtual bool MuteMyAudio(bool bMute, void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /// Gets whether the local user's audio is muted.
        virtual bool IsMyAudioMuted() = 0;

        /**
         * Pauses the local user's video in the conference.
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         */
        virtual bool PauseMyVideo(void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Resumes the local user's video in the conference.
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         */
        virtual bool ResumeMyVideo(void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /// Gets the local user's video status.
        virtual VideoStatus GetMyVideoStatus() = 0;

        /**
        * Registers the local user's audio receiver to the conference.
        * @param pReceiver Audio receiver to register.
        * @return true on success
        */
        virtual bool RegisterMyAudioReceiver(IConferenceAudioReceiverPtr pReceiver) = 0;

        /**
        * Registers the peer's audio receiver to the conference.
        * @param pReceiver Audio receiver to register.
        * @return true on success
        */
        virtual bool RegisterPeersAudioReceiver(IConferenceAudioReceiverPtr pReceiver) = 0;

        /**
        * Deregisters the local user's audio receiver from the conference.
        * @param pReceiver Audio receiver to deregister.
        * @return true on success
        */
        virtual bool DeregisterMyAudioReceiver(IConferenceAudioReceiverPtr pReceiver) = 0;

        /**
        * Deregisters the peer's audio receiver from the conference.
        * @param pReceiver Audio receiver to deregister.
        * @return true on success
        */
        virtual bool DeregisterPeersAudioReceiver(IConferenceAudioReceiverPtr pReceiver) = 0;

        /**
         * Requests a subgroup member's video from the server.<br>
         * This method returns false if the given member is not included in this session, or the given peer has not joined with video, or the given maxResolution is invalid.<br>
         * For a given peer, this API may be called several times. But only the last maxResolution will be applied.
         * @param pPeerId ID of the peer whose video you want to request.
         * @param strSubgroupName Subgroup name string, which is encoded in UTF-16 and null-terminated.<br>This can be `NullOptional` that means `MainRoom`.
         * @param eVideoResolution Max resolution of the video that you wish to receive from the peer.
         * @remark
         *  - This API works asynchronously. If you want to get the result of API call, use the other two overloaded APIs.
         * @see
         *  - https://docs.lineplanet.me/windows/extended-functions/peer-video-resolution-in-group-call
         * @deprecated
         *  - This API is deprecated and will be removed in a future release.
         */
        virtual bool RequestPeerVideo(UserIdPtr pPeerId, const WStringOptional& strSubgroupName, EVideoResolution eVideoResolution) = 0;

        /**
         * Requests a subgroup member's video from the server.<br>
         * This method returns false if the given member is not included in this session, or the given peer has not joined with video, or the given maxResolution is invalid.<br>
         * For a given peer, this API may be called several times. But only the last maxResolution will be applied.
         * @param pPeerId ID of the peer whose video you want to request.
         * @param strSubgroupName Subgroup name string, which is encoded in UTF-16 and null-terminated.<br>This can be `NullOptional` that means `MainRoom`.
         * @param eVideoResolution Max resolution of the video that you wish to receive from the peer.
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pCallback A callback function to be called after the API worked.
         * @remark
         *  - This API works asynchronously. The callback function is called immediately after the API worked.
         * @see
         *  - https://docs.lineplanet.me/windows/extended-functions/peer-video-resolution-in-group-call
         * @deprecated
         *  - This API is deprecated and will be removed in a future release.
         */
        virtual bool RequestPeerVideo(UserIdPtr pPeerId, const WStringOptional& strSubgroupName, EVideoResolution eVideoResolution, void* pUserData, RequestPeerVideoResultCallback pCallback) = 0;
        
        /**
         * Requests a subgroup member's video from the server.<br>
         * This method returns false if the given member is not included in this session, or the given peer has not joined with video, or the given maxResolution is invalid.<br>
         * For a given peer, this API may be called several times. But only the last maxResolution will be applied.
         * @param pPeerId ID of the peer whose video you want to request.
         * @param strSubgroupName Subgroup name string, which is encoded in UTF-16 and null-terminated.<br>This can be `NullOptional` that means `MainRoom`.
         * @param eVideoResolution Max resolution of the video that you wish to receive from the peer.
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pCallback A callback function to be called after the API worked.
         * @remark
         *  - This API works asynchronously. The callback is called when max resolution is reached after the API worked.
         * @see
         *  - https://docs.lineplanet.me/windows/extended-functions/peer-video-resolution-in-group-call
         * @deprecated
         *  - This API is deprecated and will be removed in a future release.
         */
        virtual bool RequestPeerVideo(UserIdPtr pPeerId, const WStringOptional& strSubgroupName, EVideoResolution eVideoResolution, void* pUserData, RequestPeerVideoResolutionCallback pCallback) = 0;

        /**
         * Stops the video stream from a peer in the conference instance.
         * @param pPeerId ID of the peer whose video you want to stop.
         * @param strSubgroupName Subgroup name string, which is encoded in UTF-16 and null-terminated.<br>This can be `NullOptional` that means `MainRoom`.
         * @param szPeerServiceId Service ID of the peer whose video you want to stop.
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pCallback A callback function to be called after the API worked.
         * @remark
         *  - This API works asynchronously. The callback function is called immediately after the API worked.
         * @deprecated
         *  - This API is deprecated and will be removed in a future release.
         */
        virtual bool StopPeerVideo(UserIdPtr pPeerId, const WStringOptional& strSubgroupName, void* pUserData = nullptr, RequestPeerVideoResultCallback pCallback = nullptr) = 0;

        /**
         * Gets the peer list in the main room.
         * @return Array of Peers
         */
        virtual bool GetPeerList(PeerArray& arrPeerListResult) = 0;

        /**
         * Sends short data to a connected peer in the conference.<br>
         * This API returns false when the szType or pData exceeds the size limit or when szType or pData are nullptr.
         * @param strType User-defined data type to be sent along with the short data. After being converted to UTF-8, it must not exceed 100 bytes including the null-termination character.
         * @param pData Short data. The maximum size of is 800 bytes.
         * @param nSize The size of pData.
         * @param pPeerId ID of the peer to whom to send the short data.
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         */
        virtual bool SendShortData(const WString& strType, void* pData, unsigned int nSize, UserIdPtr pPeerId, void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Sends short data to all peers.<br>
         * This API returns false when the szType or pData exceeds the size limit or when szType or pData are nullptr.
         * @param strType User-defined data type to be sent along with the short data. After being converted to UTF-8, it must not exceed 100 bytes including the null-termination character.
         * @param pData Short data. The maximum size of is 800 bytes.
         * @param nSize The size of pData.
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         */
        virtual bool SendShortDataToAllPeers(const WString& strType, void* pData, unsigned int nSize, void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Enables video transmission. 
         * @param eInitialMyVideoState Determines the initial video state. If it is set to PLNK_INITIAL_MY_VIDEO_STATE_PAUSE, the video will start in a paused state, and you will need to call ResumeMyVideo to send the video to the peer. 
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         * @remark
         * - Switches to a video call.
         */
        virtual bool EnableVideo(EInitialMyVideoState eInitialMyVideoState = PLNK_INITIAL_MY_VIDEO_STATE_RESUME, void *pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Disables video transmission.
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         */
        virtual bool DisableVideo(void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
        * Gets the conference duration.
        * @return Call duration in milliseconds. Returns -1 on error.
        */
        virtual int GetConferenceDuration() = 0;

        /**
         * Holds the conference.
         * @param szHoldReason Hold reason string that is encoded in UTF-16 and null-terminated.
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         */
        virtual bool Hold(const WStringOptional& strHoldReason = NullOptional, void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Unholds the conference.
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         */
        virtual bool Unhold(void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Sends a request to a peer to mute/unmute their audio. bMute will be sent to the peer.
         * @param pPeerId Peer's ID.
         * @param bMute Whether to mute or unmute
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return True on success
         */
        virtual bool RequestPeerMute(UserIdPtr pPeerId, bool bMute, void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Sends a request to all peers to mute/unmute their audio.
         * @param bMute Whether to mute or unmute
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         */
        virtual bool RequestPeersMute(bool bMute, void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Silences peer audio.
         * @param bSilence Set true to silence peer audio. Set false to unsilence.
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         */
        virtual bool SilencePeersAudio(bool bSilence, void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
        * Gets the silence state for peer audio.
        * @return true if silenced.
        */
        virtual bool IsPeersAudioSilenced() = 0;

        /**
         * Starts screen share.
         * @param pScreenShareInfo This is screen share infomation class.
         * @param strSubgroupName Destination subgroup name string that is encoded in UTF-16 and null-terminated.<br>This can be `NullOptional` that means `MainRoom`.
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         */
        virtual bool StartMyScreenShare(ScreenShareInfoPtr pScreenShareInfo, const WStringOptional& strSubgroupName, void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Stops screen share. If the result is true, remove the screen share capturer.
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         */
        virtual bool StopMyScreenShare(void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Stops screen share with a reason. If the result is true, remove the screen share capturer.
         * @param nUserReason Value must be between 0 and 39.
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pResultHandler A callback function to be called after the API worked.
         * @return true on success
         */
        virtual bool StopMyScreenShare(int nUserReason, void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Changes the screen share destination.
         * @param strToSubgroupName Destination subgroup name string that is encoded in UTF-16 and null-terminated.
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pResultHandler A callback function to be called after the API worked.
         * @return true on success
         */
        virtual bool ChangeMyScreenShareDestination(const WString& strToSubgroupName, void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Changes the screen share destination to the main room.
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pResultHandler A callback function to be called after the API worked.
         * @return true on success
         */
        virtual bool ChangeMyScreenShareDestinationToMainRoom(void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Requests a peer's screen share.
         * @param pPeerId ID of the peer to whom you want to request screen share.
         * @param strSubgroupName Subgroup name string, which is encoded in UTF-16 and null-terminated.<br>This can be `NullOptional` that means `MainRoom`.
         * @param pUSerData User's data that will be passed along when the callback function is called.
         * @param pCallback A callback function to be called after the API worked.
         * @remark
         *  - This API works asynchronously. The callback function is called immediately after the API worked.
         */
        virtual bool RequestPeerScreenShare(UserIdPtr pPeerId, const WStringOptional& strSubgroupName, void* pUserData, RequestPeerVideoResultCallback pCallback) = 0;

        /**
         * Stops a peer's screen share.
         * @param pPeerId ID of the peer whose screen share you want to stop.
         * @param strSubgroupName Subgroup name string, which is encoded in UTF-16 and null-terminated.<br>This can be `NullOptional` that means `MainRoom`.
         * @param pUSerData User's data that will be passed along when the callback function is called.
         * @param pCallback A callback function to be called after the API worked.
         * @remark
         *  - This API works asynchronously. The callback function is called immediately after the API worked.
         */
        virtual bool StopPeerScreenShare(UserIdPtr pPeerId, const WStringOptional& strSubgroupName, void* pUserData, RequestPeerVideoResultCallback pCallback) = 0;

        /**
         * Gets the content share interface.
         * @return
         *   ContentShareInterfacePtr on success.<br>
         *   ContentShareInterfacePtr with nullptr means the API worked well but there is no ContentShareInterface.<br> 
         *   If the API failed, you can get PlanetKit::NullOptional.
         */
        virtual ContentShareInterfaceOptional GetContentShareInterface() = 0;

        /**
        * Gets the Subgroup manager.
        * On a successful function call, a reference to the internal subgroup manager will be assigned to pSubgroupManager.
        * @return
        *   SubgroupManagerPtr on success.<br>
        *   SubgroupManagerPtr with nullptr means the API worked well but there is no Subgroup.<br> 
        *   If this API fails, you can get PlanetKit::NullOptional.
        * @remark
        *   There's no need to call the Release() API after using the return value but you can set nullptr to explicitly decrement the reference count.
        */
        virtual SubgroupManagerPtr GetSubgroupManager() = 0;

        /**
         * Puts reference audio data for automatic echo cancellation.
         * If PlanetKitConference::StartUserAcousticEchoCancellerReference() is called, the user must provide reference audio data for the AEC feature using this method.
         * @param sAudioData Reference audio data
         * @return Size of audio reference data in bytes
         */
        virtual int PutUserAcousticEchoCancellerReference(const SAudioData& sAudioData) = 0;

        /**
         * Starts AEC reference data.
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         */
        virtual bool StartUserAcousticEchoCancellerReference(void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Stops AEC reference data.
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         */
        virtual bool StopUserAcousticEchoCancellerReference(void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;


        // For debug purposes.
        // Internal use only.
        virtual int DebugMonitoringInfo(char* szBuffer, size_t nBufferSize) = 0;

        /// Gets the local user's equipment type.
        virtual EUserEquipmentType MyUserEquipmentType() = 0;

        /**
         * Gets the local user's display name.
         * @remark
         *  - Return value can be WStringOptional(nullOpt).
         */
        virtual const WStringOptional& GetMyDisplayName() = 0;

        /**
         * Gets statistics information.
         * @return
         *  You can get Statistics* on success.
         *  The return value can be PlanetKit::NullOptional when this instance doesn't have statistics information.
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

        /**
         * Adds a window handle to render the local user's video view.
         * @param hWind The window handle to render the local user's video view.
         * @return
         *  - Returns true if the local user's video view is successfully added.<br>
         *  - Returns false if the local user's video view is already added or if it fails to add the view.
         */
        virtual bool AddMyVideoView(WindowHandle hWind) = 0;

        /**
         * Adds a receiver to receive the local user's video frames.
         * @param pReceiver The receiver that will receive the local user's video frames.
         * @return
         *  - Returns true if the local user's video frame receiver is successfully added.<br>
         *  - Returns false if the local user's video frame receiver is already added or if it fails to add the frame receiver.
         */
        virtual bool AddMyVideoReceiver(IVideoReceiverPtr pReceiver) = 0;

        /**
         * Clears all of the local user's video views and video frame receivers that are currently stored.
         */
        virtual void RemoveAllMyVideoViewAndReceiver() = 0;

        /**
         * Removes a window handle to render the local user's video view.
         * @param hWind The window handle to render the local user's video view.
         * @return
         *  - Returns true if the local user's video view is successfully removed.<br>
         *  - Returns false if the local user's video view does not exist or if it fails to remove the view.
         */
        virtual bool RemoveMyVideoView(WindowHandle hWind) = 0;

        /**
         * Removes a receiver to receive the local user's video frames.
         * @param pReceiver The receiver that will receive the local user's video frames.
         * @return
         *  - Returns true if the local user's video frame receiver is successfully removed.<br>
         *  - Returns false if the local user's video frame receiver does not exist or if it fails to remove the frame receiver.
         */
        virtual bool RemoveMyVideoReceiver(IVideoReceiverPtr pReceiver) = 0;

        /**
         * Adds a window handle to render a peer's video view.
         * @param pPeerID Information on the Peer to be rendered.
         * @param hWind The window handle to render a peer's video view.
         * @return
         *  - Returns true if the peer's video view is successfully added.<br>
         *  - Returns false if the peer's video view is already added or if it fails to add the view.
         */
        virtual bool AddPeerVideoView(UserIdPtr pPeerID, WindowHandle hWind) = 0;

        /**
         * Adds a receiver to receive the peer's video frames.
         * @param pPeerID Information on the peer to be received.
         * @param pReceiver The receiver that will receive the peer's video frames.
         * @return
         *  - Returns true if the peer's video frame receiver is successfully added.<br>
         *  - Returns false if the peer's video frame receiver is already added or if it fails to add the frame receiver.
         */
        virtual bool AddPeerVideoReceiver(UserIdPtr pPeerID, IVideoReceiverPtr pReceiver) = 0;

        /**
         * Clears all of the peer's video views and video frame receivers that are currently stored.
         */
        virtual void RemoveAllPeerVideoViewAndReceiver() = 0;

        /**
         * Removes a window handle to render a peer's video view.
         * @param hWind The window handle to render a peer's video view.
         * @return
         *  - Returns true if the peer's video view is successfully removed.<br>
         *  - Returns false if the peer's video view does not exist or if it fails to remove the view.
         */
        virtual bool RemovePeerVideoView(WindowHandle hWind) = 0;

        /**
         * Removes a receiver Handle to receive a peer's video frames.
         * @param pReceiver The receiver that will receive the peer's video frames.
         * @return
         *  - If the peer's video frame receiver is successfully removed, it returns true.<br>
         *  - Returns false if the peer's video frame receiver does not exist or if it fails to remove the frame receiver.
         */
        virtual bool RemovePeerVideoReceiver(IVideoReceiverPtr pReceiver) = 0;

        /**
         * Adds a window handle to render the local user's screen share view.
         * @param hWind The window handle to render the local user's screen share view.
         * @return
         *  - Returns true if the local user's screen share view is successfully added.<br>
         *  - Returns false if the local user's screen share view is already added or if it fails to add the view.
         */
        virtual bool AddMyScreenShareVideoView(WindowHandle hWind) = 0;

        /**
         * Adds a receiver to receive the local user's screen share frames.
         * @param pReceiver The receiver that will receive the peer's screen share frames.
         * @return
         *  - Returns true if the local user's screen share frame receiver is successfully added.<br>
         *  - Returns false if the local user's screen share frame receiver is already added or if it fails to add the frame receiver.
         */
        virtual bool AddMyScreenShareVideoReceiver(IVideoReceiverPtr pReceiver) = 0;

        /**
         * Clears all of the local user's screen share views and screen share frame receivers that are currently stored.
         */
        virtual void RemoveAllMyScreenShareVideoViewAndReceiver() = 0;

        /**
         * Removes a window handle to render the local user's screen share view.
         * @param hWind The window handle to render the local user's screen share view.
         * @return
         *  - Returns true if the local user's screen share view is successfully removed.<br>
         *  - Returns false if the local user's screen share view does not exist or if it fails to remove the view.
         */
        virtual bool RemoveMyScreenShareVideoView(WindowHandle hWind) = 0;

        /**
         * Removes a receiver to receive the local user's screen share frames.
         * @param pReceiver The receiver that will receive the peer's screen share frames.
         * @return
         *  - Returns true if the local user's screen share frame receiver is successfully removed.<br>
         *  - Returns false if the local user's screen share frame receiver does not exist or if it fails to remove the frame receiver.
         */
        virtual bool RemoveMyScreenShareVideoReceiver(IVideoReceiverPtr pReceiver) = 0;

        /**
         * Adds a window handle to render a peer's screen share view.
         * @param pPeerID Information on the Peer to be rendered.
         * @param hWind The window handle to render a peer's screen share view.
         * @return
         *  - Returns true if the peer's screen share view is successfully added.<br>
         *  - Returns false if the peer's screen share view is already added or if it fails to add the view.
         */
        virtual bool AddPeerScreenShareVideoView(UserIdPtr pPeerID, WindowHandle hWind) = 0;

        /**
         * Adds a receiver to receive the peer's screen share frames.
         * @param pPeerID Information on the peer to be received.
         * @param pReceiver The receiver that will receive the peer's screen share frames.
         * @return
         *  - Returns true if the peer's screen share frame receiver is successfully added.<br>
         *  - Returns false if the peer's screen share frame receiver is already added or if it fails to add the frame receiver.
         */
        virtual bool AddPeerScreenShareVideoReceiver(UserIdPtr pPeerID, IVideoReceiverPtr pReceiver) = 0;

        /**
         * Clears all of the peer's screen share views and screen share frame receivers that are currently stored.
         */
        virtual void RemoveAllPeerScreenShareVideoViewAndReceiver() = 0;

        /**
         * Removes a window handle to render a peer's screen share view.
         * @param hWind The window handle to render a peer's screen share view.
         * @return
         *  - Returns true if the peer's screen share view is successfully removed.<br>
         *  - Returns false if the peer's screen share view does not exist or if it fails to remove the view.
         */
        virtual bool RemovePeerScreenShareVideoView(WindowHandle hWind) = 0;

        /**
         * Removes a receiver to receive the peer's screen share frames.
         * @param pReceiver The receiver that will receive the peer's screen share frames.
         * @return
         *  - Returns true if the peer's screen share frame receiver view is successfully removed.<br>
         *  - Returns false if the peer's screen share frame receiver does not exist or if it fails to remove the frame receiver.
         */
        virtual bool RemovePeerScreenShareVideoReceiver(IVideoReceiverPtr pReceiver) = 0;
    };
}
