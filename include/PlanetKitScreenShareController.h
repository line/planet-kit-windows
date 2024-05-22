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

#include "PlanetKitVideoController.h"

namespace PlanetKit
{
    /// The class for capturing with a screen share.
    class PLANETKIT_API ScreenShareController : virtual public VideoController {
    public:
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
        virtual bool RegisterCapturerEvent(IVideoCapturerEvent* pDelegate) = 0;

        /**
         * Deregisters an event to receive in case the status of the shared window changes.
         * @return
         *  - Returns true if successful.
         */
        virtual bool DeregisterCapturerEvent() = 0;
    };

    template class PLANETKIT_API AutoPtr<ScreenShareController>;
    typedef AutoPtr<ScreenShareController> ScreenShareControllerPtr;
}