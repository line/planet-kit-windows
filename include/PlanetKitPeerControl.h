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
#include "PlanetKitSubgroupInterface.h"
#include "PlanetKitVideoCommon.h"
#include "PlanetKitVideoController.h"

namespace PlanetKit {
    /// Callback APIs for a peer's status
    class PLANETKIT_API IPeerControlEvent {
    public :
        /// Called when a peer is initialized.
        virtual void OnInitialized(PeerControlPtr pPeerControl, bool bResult) = 0;
        /// Called when a peer is muted.
        virtual void OnMuted(PeerControlPtr pPeerControl) = 0;
        /// Called when a peer is unmuted.
        virtual void OnUnmuted(PeerControlPtr pPeerControl) = 0;
        /// Called when a peer's video status is updated.
        virtual void OnVideoUpdated(PeerControlPtr pPeerControl, SubgroupPtr pSubgroup, const VideoStatus& videoStatus) = 0;
        /// Called when a peer's screen share is updated.
        virtual void OnScreenShareUpdated(PeerControlPtr pPeerControl, SubgroupPtr pSubgroup, EScreenShareState eState) = 0;
        /// Called when a peer subscribes to a subgroup.
        virtual void OnSubscribed(PeerControlPtr pPeerControl, SubgroupPtr pSubgroup) = 0;
        /// Called when a peer unsubscribes from a subgroup.
        virtual void OnUnsubscribed(PeerControlPtr pPeerControl, SubgroupPtr pSubgroup) = 0;
        /// Called when a peer is disconnected from the conference room.
        virtual void OnDisconnected(PeerControlPtr pPeerControl) = 0;
        
        /**
         * Called when a peer holds.
         * @param strHoldReason Reason string that can be nullptr.
         */
        virtual void OnHold(PeerControlPtr pPeerControl, const String& strHoldReason) = 0;
        /// Called when a peer unholds.
        virtual void OnUnHold(PeerControlPtr pPeerControl) = 0;

        /**
         * Called when a peer sets shared contents.
         * @param unElapsedAfterSet Setting time
         * @param pvData Shared contents data
         * @param unDataSize Data size of the parameter pvData
         */
        virtual void OnSetSharedContents(PeerControlPtr pPeerControl, unsigned int unElapsedAfterSet, const void* pvData, unsigned int unDataSize) = 0;
        /// Called when a peer unsets shared contents.
        virtual void OnUnsetSharedContents(PeerControlPtr pPeerControl) = 0;

        /// Called when a peer's average volume level is updated.
        virtual void OnPeerAudioDescriptionUpdated(PeerControlPtr pPeerControl, const PeerAudioDescription& sPeerAudioDescription) = 0;
    };

    /// Start/Stop video result callback API
    class PLANETKIT_API IPeerVideoResultHandler {
    public :
        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see StartVideoResultCallback
         */
        virtual void OnResult(PeerControlPtr pPeerControl, SRequestMediaResultParam* pRequestMediaResult, void* pUserData) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see StartVideoResolutionCallback
         */
        virtual void OnRequestVideoResolutionResult(PeerControlPtr pPeerControl, SRequestVideoResolutionResultParam* pReqVidResResultParam, void* pUserData) = 0;
    };

    /**
     * Result callback API that is called after working of PeerControl::StartVideo.
     */
    using StartVideoResultCallback = void(*)(PeerControlPtr pPeerControl, SRequestMediaResultParam* pRequestMediaResult, void* pUserData);

    /**
     * Result callback API that is called after working of PeerControl::StartVideo.
     */
    using StartVideoResolutionCallback = void(*)(PeerControlPtr pPeerControl, SRequestVideoResolutionResultParam* pRequestMediaResult, void* pUserData);

    /**
     * Result callback API that is called after working of PeerControl::StopVideo.
     */
    using StoptVideoResultCallback = void(*)(PeerControlPtr pPeerControl, SRequestMediaResultParam* pRequestMediaResult, void* pUserData);

    class PLANETKIT_API PeerControl : public Base {
    public :
        /**
         * Gets the Peer object.
         */
        virtual PeerPtr GetPeer() = 0;

        /**
         * Registers an event listener to receive events of peer's activity.
         * @param pEventListener Implementation class pointer of IPeerControlEvent to receive events.
         * @remark
         *   If PeerControl already has an event listener, then this API will fail.
         */
        virtual bool Register(IPeerControlEvent* pEventListener) = 0;

        /**
         * Unregisters the event listener, RenderPtr, and IVideoReceiver* that PeerControl has.
         */
        virtual void Unregister() = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         */
        bool StartVideo(const char* szSubgroupName, EVideoResolution eVideoResolution, void* pUserData, IPeerVideoResultHandler* pResultHandler, void* pResolutionResultData, IPeerVideoResultHandler* pResolutionResultHandler);

        /**
         * Starts the peer's video.
         * @param szSubgroupName Peer's subgroup name.
         * @param eVideoResolution Peer's video resolution.
         * @remark
         *  - You should set the VideoRender class or a custom class that inherits from IVideoReceiver for rendering the peer's video.<br>
         *  - You can create the VideoRender class using PlanetKit::VideoRender::CreateRender.<br>
         *  - The VideoRender class is an automatic rendering class, but the IVideoReceiver class must be rendered directly.<br>
         *  - So, you must select one method between PeerControl::SetRenderer and PeerControl::SetReceiver for rendering and may use both methods.<br>
         *   - This API works asynchronously. If you want to get the result of API calls, then use the other two overloaded APIs.

         */
        virtual bool StartVideo(const wchar_t* szSubgroupName, EVideoResolution eVideoResolution) = 0;

        /**
         * Starts the peer's video.
         * @param szSubgroupName Peer's subgroup name.
         * @param eVideoResolution Peer's video resolution.
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pCallback A callback function to be called after the API worked.
         * @remark
         *  - You should set the VideoRender class or a custom class that inherits from IVideoReceiver for rendering the peer's video.<br>
         *  - You can create the VideoRender class using PlanetKit::VideoRender::CreateRender.<br>
         *  - The VideoRender class is an automatic rendering class, but the IVideoReceiver class must be rendered directly.<br>
         *  - So, you must select one method between PeerControl::SetRenderer and PeerControl::SetReceiver for rendering and may use both methods.<br>
         *  - This API works asynchronously. The callback function is called immediately after the API worked.
         */
        virtual bool StartVideo(const wchar_t* szSubgroupName, EVideoResolution eVideoResolution, void* pUserData, StartVideoResultCallback pCallback) = 0;

        /**
         * Starts the peer's video.
         * @param szSubgroupName Peer's subgroup name.
         * @param eVideoResolution Peer's video resolution.
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pCallback A callback function to be called after the API worked.
         * @remark
         *  - You should set the VideoRender class or a custom class that inherits from IVideoReceiver for rendering the peer's video.<br>
         *  - You can create the VideoRender class using PlanetKit::VideoRender::CreateRender.<br>
         *  - The VideoRender class is an automatic rendering class, but the IVideoReceiver class must be rendered directly.<br>
         *  - So, you must select one method between PeerControl::SetRenderer and PeerControl::SetReceiver for rendering and may use both methods.<br>
         *  - This API works asynchronously. The callback function is called when max resolution is reached after the API worked.
         */
        virtual bool StartVideo(const wchar_t* szSubgroupName, EVideoResolution eVideoResolution, void* pUserData, StartVideoResolutionCallback pCallback) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         */
        bool StopVideo(void* pUserData, IPeerVideoResultHandler* pResultHandler);

        /**
         * Stops the peer's video.
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pCallback A callback function to be called after the API worked.
         * @remark
         *  - The handles set through PeerControl::SetRenderer and the receivers established through PeerControl::SetReceiver will both be reset.
         */
        virtual bool StopVideo(void* pUserData = nullptr, StoptVideoResultCallback pCallback = nullptr) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         */
        bool StartScreenShare(const char* szSubgroupName, void* pUserData, IResultHandler* pResultHandler);

        /**
         * Starts rendering the peer's screen share.
         * @param szSubgroupName Peer's subgroup name
         * @param pUserData User custom data that can be a parameter when IResultHandler::OnResult API is called back after working.
         * @param pResultHandler Call IResultHandler::OnResult callback API after working.
         * @remark
         *   - You should set the VideoRender class or a custom class that inherits from IVideoReceiver for rendering the peer's screen share with calling SetScreenShareRenderer.
         */
        virtual bool StartScreenShare(const wchar_t* szSubgroupName, void* pUserData, IResultHandler* pResultHandler) = 0;

        /**
         * Stops rendering the peer's screen share.
         * @param pUserData User custom data that can be a parameter when IResultHandler::OnResult API is called back after working.
         * @param pResultHandler Call IResultHandler::OnResult callback API after working.
         */
        virtual bool StopScreenShare(void* pUserData, IResultHandler* pResultHandler) = 0;


        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use SetView")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see SetView
         */
        void SetRenderer(VideoRender* pVideoRender);

        /**
         * Sets the video rendering window.
         * @remark
         *  - Only one video rendering window can be set for rendering the video frame.
         */
        virtual void SetView(WindowHandle hWnd) = 0;

        /**
         * Sets the video receiver.
         * @remark
         *  - Only one video receiver can be set for receiving VideoFrameData that can be used for rendering, writing files, etc.
         */
        virtual void SetReceiver(IVideoReceiver* pReceiver) = 0;

        /**
         * Sets the screen share video renderer.
         * @remark
         *  - Only one video renderer can be set for rendering screen share.
         */
        virtual void SetScreenShareView(WindowHandle hWnd) = 0;
    };
};