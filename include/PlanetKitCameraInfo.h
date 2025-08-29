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
#include "PlanetKitVideoCommon.h"

namespace PlanetKit {
    /**
     * Result of camera control
     */
    enum ECameraControlResult {
        /// NONE
        PLNK_CAMERA_CONTROL_RESULT_NONE = 0,
        /// Failed to create the camera device selected by the local user.
        PLNK_CAMERA_CONTROL_RESULT_FAILED_TO_CREATE_CAMERA_DEVICE,
        /// Selected camera device is removed.
        PLNK_CAMERA_CONTROL_RESULT_SELECTED_CAMERA_IS_REMOVED,
        /// No camera is selected.
        PLNK_CAMERA_CONTROL_RESULT_NO_CAMERA_SELECTED,
        /// Camera is already used by another application.
        PLNK_CAMERA_CONTROL_RESULT_CAMERA_IS_ALREADY_USED_BY_ANOTHER_APPLICATION,
        /// Failed to start the camera.
        PLNK_CAMERA_CONTROL_RESULT_START_CAMERA_FAIL,
    };

    /**
     * Camera device information
     */
    class PLANETKIT_API CameraInfo : public Base {

    public:
        /// Gets the camera device name.
        virtual const WString& GetDeviceName() const = 0;

        /// Gets the device unique ID.
        virtual const WString& GetDeviceUid() const = 0;

        /**
         * Gets the rotation state.
         * @remark
         *  - Default rotation mode is PLNK_VIDEO_ROTATION_0.
         * @see EVideoRotation
         */
        virtual EVideoRotation GetRotation() const = 0;

        /**
         * Sets the rotation state.
         * @remark
         *  - Default rotation mode is PLNK_VIDEO_ROTATION_0.
         * @see EVideoRotation
         */
        virtual void SetRotation(EVideoRotation eRotation) = 0;

        /**
         * Gets the preferred resolution.
         * @remark
         *  - Default preferred resolution is PLNK_CAMERA_RESOLUTION_HD.
         * @see ECameraResolution
         */
        virtual ECameraResolution GetPreferredResolution() const = 0;

        /**
         * Sets the preferred resolution.
         * @remark
         *  - Default preferred resolution is PLNK_CAMERA_RESOLUTION_HD.
         * @see ECameraResolution
        */
        virtual void SetPreferredResolution(ECameraResolution ePreferredResolution) = 0;

        /**
         * Gets the preferred max FPS.
         * @remark
         *  - Default preferred max FPS is PLNK_VIDEO_CAPTURE_FPS_DEFAULT.
         * @see EVideoCaptureFps
         */
        virtual EVideoCaptureFps GetPreferredMaxFps() const = 0;

        /**
         * Sets the preferred max FPS.
         * @remark
         *  - Default preferred max FPS is PLNK_VIDEO_CAPTURE_FPS_DEFAULT.
         * @see EVideoCaptureFps
         */
        virtual void SetPreferredMaxFps(EVideoCaptureFps ePreferredMaxFps) = 0;

        /**
         * Gets the camera type.
         * @see ECameraInfoType
         */
        virtual ECameraInfoType GetType() const = 0;

        /**
         * Sets the camera type.
         * @see ECameraInfoType
         */
        virtual void SetType(ECameraInfoType eCameraType) = 0;
    };

    /// CameraInfo pointer as AutoPtr
    template class PLANETKIT_API AutoPtr<CameraInfo>;
    typedef AutoPtr<CameraInfo> CameraInfoPtr;
    typedef Optional<CameraInfoPtr> CameraInfoOptional;

    /// Array of CameraInfo
    template class PLANETKIT_API Array<CameraInfoPtr>;
    typedef Array<CameraInfoPtr> CameraInfoArray;

    /// The interface for receiving a callback when there are changes to the capture device.
    class PLANETKIT_API IVideoCaptureDeviceEvent {
    public:
        /**
         * This callback method is called when a camera device is added.
         * @param pInfo Information of the added camera device.
         */
        virtual void OnDeviceAdded(CameraInfoPtr pInfo) = 0;

        /**
         * This callback method is called when a camera device is removed.
         * @param pInfo Information of the removed camera device.
         */
        virtual void OnDeviceRemoved(CameraInfoPtr pInfo) = 0;

        /**
         * This callback method is called when any camera control fails.
         * @param eCameraControlResult Reason of failure.
         */
        virtual void OnCameraError(ECameraControlResult eCameraControlResult) = 0;
    };
};