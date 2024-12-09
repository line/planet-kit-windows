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

#include "PlanetKit.h"
#include "PlanetKitVideoCommon.h"

namespace PlanetKit {
    /// Information for screen share.
    class PLANETKIT_API ScreenShareInfo : public Base {
    public:
        /**
         * Gets the name of the target to share the screen with.
         * @return The name of the target to share the screen with.
         */
        virtual const WString& GetName() = 0;

        /**
         * Gets the screen share target ID.
         * @return Screen share ID.
         */
        virtual ScreenShareID GetID() = 0;

        /**
         * Checks whether the screen has been minimized.
         * @return Whether the screen has been minimized.
         * @remark
         *  - This API can be used when EVideoCapturerType is set to window.
         */
        virtual bool GetMinimized() = 0;

        /**
         * Gets the current screen share type.
         * @return Screen share type.
         */
        virtual EVideoCapturerType GetType() = 0;
    };

    /// ScreenShareInfo pointer as AutoPtr
    template class PLANETKIT_API AutoPtr<ScreenShareInfo>;
    typedef AutoPtr<ScreenShareInfo> ScreenShareInfoPtr;

    /// Array of ScreenShareInfo
    template class PLANETKIT_API Array<ScreenShareInfoPtr>;
    typedef Array<ScreenShareInfoPtr> ScreenShareInfoArray;

    /**
     * Window state that is used by screen share.
     */
    typedef enum EWindowState
    {
        /// Window is unminimized.
        PLNK_CAPTURE_WINDOW_EVENT_UNMINIMIZED,
        /// Window is minimized.
        PLNK_CAPTURE_WINDOW_EVENT_MINIMIZED,
        /// Window rect is changed.
        PLNK_CAPTURE_WINDOW_EVENT_RECT_CHANGED,
        /// Window is closed.
        PLNK_CAPTURE_WINDOW_EVENT_WINDOW_CLOSED
    } EWindowState;

    /**
     * Parameter received through a listener when the state of the shared window is changed.
     */
    typedef struct SWindowStateChangeParam
    {
        /// Window information
        ScreenShareInfoPtr pInfo;
        /// Window state
        EWindowState newState;
    } SWindowStateChangeParam;

    /// The interface for receiving a callback when frame processing is finished.
    class PLANETKIT_API IVideoCapturerEvent {
    public:
        // A callback for VideoCaptureType::VIDEO_CAPTURE_WINDOW
        virtual void OnCaptureWindowStateChanged(const SWindowStateChangeParam* pParam) = 0;
    };

}