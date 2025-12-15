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
#include "PlanetKitCameraInfo.h"
#include "PlanetKitVideoDefine.h"

namespace PlanetKit {
    /// The interface for receiving a callback when there are changes to the capture device.
    class PLANETKIT_API IVideoCaptureDeviceEvent {
    public:
        virtual ~IVideoCaptureDeviceEvent() { }

        /**
         * This callback method is called when a camera device is added.\n
         * This event is triggered for any camera device added to the system.
         * @param pInfo Information of the added camera device.
         */
        virtual void OnDeviceAdded(CameraInfoPtr pInfo) = 0;

        /**
         * This callback method is called when a camera device is removed.\n
         * This event is triggered for any camera device removed from the system, including the selected camera.
         * @param pInfo Information of the removed camera device.
         */
        virtual void OnDeviceRemoved(CameraInfoPtr pInfo) = 0;

        /**
         * This callback method is called when any camera control fails.\n
         * This event is triggered when there are issues with the selected camera device.
         * @param eCameraControlResult Reason of failure.
         */
        virtual void OnCameraError(ECameraControlResult eCameraControlResult) = 0;
    };

    using IVideoCaptureDeviceEventPtr = SharedPtr<IVideoCaptureDeviceEvent>;
};