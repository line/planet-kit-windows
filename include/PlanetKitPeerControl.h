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

#include "PlanetKitAudioCommon.h"
#include "PlanetKitVideoCommon.h"

#include "PlanetKitSubgroupInterface.h"
#include "PlanetKitCameraController.h"
#include "PlanetKitScreenShareController.h"

#include "IPlanetKitPeerControlEvent.h"
#include "IPlanetKitVideoReceiver.h"

namespace PlanetKit {
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
        virtual bool Register(IPeerControlEventPtr pEventListener) = 0;

        /**
         * Unregisters the event listener, RenderPtr, and IVideoReceiverPtr that PeerControl has.
         */
        virtual void Unregister() = 0;

        /**
         * Starts the peer's video.
         * @param strSubgroupName Peer's subgroup name.<br>This can be `NullOptional` that means `MainRoom`.
         * @param eVideoResolution Peer's video resolution.
         * @remark
         *  - You should set the VideoRender class or a custom class that inherits from IVideoReceiver for rendering the peer's video.<br>
         *  - You can create the VideoRender class using PlanetKit::VideoRender::CreateRender.<br>
         *  - The VideoRender class is an automatic rendering class, but the IVideoReceiver class must be rendered directly.<br>
         *  - So, you must select one method between PeerControl::SetRenderer and PeerControl::SetReceiver for rendering and may use both methods.<br>
         *   - This API works asynchronously. If you want to get the result of API calls, then use the other two overloaded APIs.

         */
        virtual bool StartVideo(const WStringOptional& strSubgroupName, EVideoResolution eVideoResolution) = 0;

        /**
         * Starts the peer's video.
         * @param strSubgroupName Peer's subgroup name.<br>This can be `NullOptional` that means `MainRoom`.
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
        virtual bool StartVideo(const WStringOptional& strSubgroupName, EVideoResolution eVideoResolution, void* pUserData, StartVideoResultCallback pCallback) = 0;

        /**
         * Starts the peer's video.
         * @param strSubgroupName Peer's subgroup name.<br>This can be `NullOptional` that means `MainRoom`.
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
        virtual bool StartVideo(const WStringOptional& strSubgroupName, EVideoResolution eVideoResolution, void* pUserData, StartVideoResolutionCallback pCallback) = 0;

        /**
         * Stops the peer's video.
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pCallback A callback function to be called after the API worked.
         * @remark
         *  - The handles set through PeerControl::SetRenderer and the receivers established through PeerControl::SetReceiver will both be reset.
         */
        virtual bool StopVideo(void* pUserData = nullptr, StoptVideoResultCallback pCallback = nullptr) = 0;

        /**
         * Starts rendering the peer's screen share.
         * @param strSubgroupName Peer's subgroup name.<br>This can be `NullOptional` that means `MainRoom`.
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @remark
         *   - You should set the VideoRender class or a custom class that inherits from IVideoReceiver for rendering the peer's screen share with calling SetScreenShareView or RegisterScreenShareReceiver.
         */
        virtual bool StartScreenShare(const WStringOptional& strSubgroupName, void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Stops rendering the peer's screen share.
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.         */
        virtual bool StopScreenShare(void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Sets the video rendering window.
         * @remark
         *  - Only one video rendering window can be set for rendering the video frame.
         */
        virtual void SetView(WindowHandle hWnd) = 0;

        /**
         * Clears the video rendering window.
         */
        virtual void ClearView() = 0;

        /**
         * Registers video receiver.
         * @remark
         *  - You can set multiple video receivers for receiving VideoFrameData that can be used rendering, writing files, etc.
         * @see DeregisterReceiver
         */
        virtual void RegisterReceiver(IVideoReceiverPtr pReceiver) = 0;

        /**
         * Deregisters video receiver.
         * @remark
         *  - You should deregister video receiver before you registered.
         * @see RegisterReceiver
         */
        virtual void DeregisterReceiver(IVideoReceiverPtr pReceiver) = 0;

        /**
         * Sets the screen share video renderer.
         * @remark
         *  - Only one video renderer can be set for rendering screen share.
         */
        virtual void SetScreenShareView(WindowHandle hWnd) = 0;

        /**
         * Clears the screen share rendering window.
         */
        virtual void ClearScreenShareView() = 0;

        /**
         * Registers screen share receiver.
         * @remark
         *  - You can set multiple video receivers for receiving VideoFrameData that can be used rendering, writing files, etc.
         * @see DeregisterReceiver
         */
        virtual void RegisterScreenShareReceiver(IVideoReceiverPtr pReceiver) = 0;

        /**
         * Deregisters screen share receiver.
         * @remark
         *  - You can deregister video receiver before you registered.
         * @see RegisterReceiver
         */
        virtual void DeregisterScreenShareReceiver(IVideoReceiverPtr pReceiver) = 0;

        /**
         * Sets the peer's volume.
         * @param ucVolume Volume level in the range [0:110]
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pCallback A callback function to be called after the API worked.
         * @return true on success
         */
        virtual bool SetVolumeLevelSetting(unsigned char ucVolume, void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

    };
};