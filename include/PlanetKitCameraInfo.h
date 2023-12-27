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
     * Camera device information
     */
    class PLANETKIT_API CameraInfo : public Base {

    public:
        /// Gets the camera device name.
        virtual const WString& GetDeviceName() const = 0;

        /// Gets the device unique ID.
        virtual const WString& GetDeviceUid() const = 0;

        /**
         * Checks whether the camera is mirrored.
         * @remark
         *  - Default mirror state is false.
         */
        virtual bool IsMirrored() const = 0;

        /**
         * Sets the camera mirror state.
         * @remark
         *  - Default mirror state is false.
         */
        virtual void SetMirror(bool bMirror) = 0;

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
    typedef AutoPtr<CameraInfo> CameraInfoPtr;
    /// Array of CameraInfo
    typedef Array<CameraInfoPtr> CameraInfoArray;
};