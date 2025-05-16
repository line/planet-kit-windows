#pragma once
// Copyright 2023 LINE Plus Corporation
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

#include "PlanetKitScreenShareInfo.h"
#include "PlanetKitVideoRender.h"
#include "IPlanetKitVideoCapturerEvent.h"

namespace PlanetKit
{
    /// The class for capturing with a screen share.
    class PLANETKIT_API ScreenShareController {
    public:
        virtual ~ScreenShareController() { }

        /**
         * Gets the information of the targets for screen share.
         * @param arrScreenShare The list of available screen share information.
         * @return
         *  - Returns true if successful.
         */
        virtual bool GetScreenShareInfos(ScreenShareInfoArray& arrScreenShare) = 0;

        /**
         * Gets a snapshot of a specific screen share information.
         * @param pScreenShareInfo The screen share information for the snapshot.
         * @return
         *  - The current snapshot of target screenInfo.
         */
        virtual VideoFramePtr GetScreenShareSnapshot(ScreenShareInfoPtr pScreenShareInfo) = 0;

        /**
         * Starts the screen capture.
         * @param pScreenShareInfo The screen share information to share.
         * @return
         *  - The result of the process of starting the capture.
         */
        virtual EVideoControlResult StartScreenShareCapture(ScreenShareInfoPtr pScreenShareInfo) = 0;

        /**
         * Stops the screen capture.
         * @return
         *  - Returns true if successful.
         */
        virtual bool StopScreenCapture() = 0;

        /**
         * Registers an event to receive in case the status of the shared window changes.
         * @param pDelegate The event to be notified.
         * @return
         *  - Returns true if successful.
         */
        virtual bool RegisterCapturerEvent(IVideoCapturerEventPtr pDelegate) = 0;

        /**
         * Deregisters an event to receive in case the status of the shared window changes.
         * @return
         *  - Returns true if successful.
         */
        virtual bool DeregisterCapturerEvent() = 0;

        /**
         * Gets the current capturer type.
         * @return
         *  - If successful, it returns the capturer type.
         *  - Unlike GetCapturerMediaType, GetCapturerType obtains the current capture target.
         */
        virtual EVideoCapturerType GetCapturerType() = 0;

        /**
         * Registers the video interceptor.
         * @param pInterceptor The video interceptor to register.
         * @return
         *  - Returns true if successful.
         * @remark
         *  - This intercepts the frame captured through the camera before delivering it to the counterpart.
         *  - If necessary, you can change the frame to be delivered to the counterpart.
         */
        virtual bool RegisterVideoInterceptor(IVideoInterceptorPtr pInterceptor) = 0;

        /**
         * Deregisters the video interceptor.
         * @return
         *  - Returns true if successful.
         */
        virtual bool DeregisterVideoInterceptor() = 0;

        /**
         * Obtains the renderer currently rendering the Window.
         * @param hWnd The window for which you want to obtain the currently rendering renderer.
         * @return
         *  - The renderer that is currently rendering.
         * @remark
         *  - You can change options of the window currently being rendered by calling this API.
         */
        virtual VideoRenderPtr GetRender(WindowHandle hWnd) = 0;

        /**
         * Sends frame data to the counterpart.
         * @param sVideoFrame The frame to send to the counterpart.
         * @return
         *  - Returns true if successful.
         */
        virtual bool WriteFrameData(SVideoFrame& sVideoFrame) = 0;

        /**
         * Checks whether it is currently possible to deliver frames to the counterpart.
         * @param ull64tick The tick count of the current frame.
         * @return
         *  - Returns true if it is possible to send frames to the counterpart.
         * @remark
         *  - In case there is a current FPS limit, you need to check the speed of the current frame through the tick count value .
         *  - You verify whether the current frame can be delivered at an appropriate FPS by checking the speed of this frame.
         */
        virtual bool IsPostingFrameAvailable(UINT64 ull64tick) = 0;
    };

    typedef SharedPtr<ScreenShareController> ScreenShareControllerPtr;
}