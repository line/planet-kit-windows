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
    /// The class for capturing with a camera.
    class PLANETKIT_API CameraController : virtual public VideoController  {
    public:

        /**
         * Get a list of camera devices.
         * @param arrCameraInfo The list of available camera devices.
         */
        virtual void GetCapturerInfo(CameraInfoArray& arrCameraInfo) = 0;

        /**
         * Changes the camera that will capture the current screen.
         * @param pCameraInfo The device to capture the screen.
         * @return
         *  - The result of the process of setting up the camera device.
         * @remark
         *  - If you want to use a specific device when starting capture, you can set it first with this function and then start.
         */
        virtual EVideoControlResult SelectCamera(CameraInfoPtr pCameraInfo) = 0;

        /**
         * Get selected camera information.
         * @return
         *  - The result of selected camera information class.
         * @remark
         *  - This API may return nullptr if no camera is selected.
         */
        virtual CameraInfoPtr GetSelectedCamera() = 0;

        /**
         * Starts the capture.
         * @return
         *  - The result of the process of starting the capture.
         * @remark
         *  - If you have not set a specific camera with SelectCamera, it starts using the default camera.
         */
        virtual EVideoControlResult StartCapture() = 0;

        /**
         * Stops the capture.
         * @return
         *  - Returns true if successful.
         */
        virtual bool StopCapture() = 0;

        /**        
         * Registers a delegate to handle device change events.
         * @param pDelegate The delegate to handle device change events.
         */
        virtual void RegisterDeviceEvent(IVideoCaptureDeviceEvent* pDelegate) = 0;

        /**
         * Deregisters a delegate to handle device change events.
         * @param pDelegate The delegate that you want to deregister.
         */
        virtual void DeregisterDeviceEvent(IVideoCaptureDeviceEvent* pDelegate) = 0;

        /**
         * Checks camera is running.
         * @return true on camera is running.
         */
        virtual bool IsRunning() = 0;
    };

    template class PLANETKIT_API AutoPtr<CameraController>;
    typedef AutoPtr<CameraController> CameraControllerPtr;
}