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
    class PLANETKIT_API CameraInfo {
    public:
        virtual ~CameraInfo() { }

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

        /**
         * Checks whether the camera supports the given focus mode.
         * @param focusMode The focus mode to query.
         * @return true if supported. A camera with no focus control returns false for every mode.
         * @remark The capability is available as soon as the camera is enumerated by GetCapturerInfo;
         *         calling ChangeCamera first is not required, and the value does not change as a
         *         result of ChangeCamera. Querying the capability briefly opens the device: if the
         *         camera is momentarily held by another app the open can fail and this returns false
         *         even for a focus-capable camera. The next call re-queries, so callers should not
         *         permanently cache a false result.
         */
        virtual bool IsFocusModeSupported(EFocusMode focusMode) const = 0;

        /**
         * Gets the currently applied focus mode.
         * @param outFocusMode Receives the current focus mode.
         * @return PLNK_FOCUS_CONTROL_RESULT_SUCCESS on success,
         *         PLNK_FOCUS_CONTROL_RESULT_NOT_SUPPORTED if the camera supports no focus control at all,
         *         PLNK_FOCUS_CONTROL_RESULT_INTERNAL_ERROR if the OS call fails.
         */
        virtual EFocusControlResult GetFocusMode(EFocusMode& outFocusMode) const = 0;

        /**
         * Sets the focus mode.
         * @param focusMode AUTO enters auto mode and triggers auto-focus in one call;
         *                  MANUAL enters manual mode using the last manual focus value.
         * @return PLNK_FOCUS_CONTROL_RESULT_SUCCESS on success,
         *         PLNK_FOCUS_CONTROL_RESULT_NOT_SUPPORTED if the requested mode (or focus control itself) is not supported,
         *         PLNK_FOCUS_CONTROL_RESULT_INTERNAL_ERROR if the OS call fails.
         * @remark On an active camera the change applies on the next capture cycle without stop/start.
         *         Before activation (ChangeCamera) the value is stored as preferred.
         */
        virtual EFocusControlResult SetFocusMode(EFocusMode focusMode) = 0;

        /**
         * Gets the current manual focus value (0-100). See SetManualFocusValue for the value's meaning.
         * @return The manual focus value, in the range 0-100. Returns 0 when the camera does not support
         *         manual focus; because 0 is also a valid value, use
         *         IsFocusModeSupported(PLNK_FOCUS_MODE_MANUAL) to check support rather than this return value.
         * @remark When the camera is in AUTO mode, this returns the last set manual focus value
         *         (the value that will be used on the next SetFocusMode(MANUAL)), not a live
         *         reading of the camera's current focus position.
         */
        virtual unsigned int GetManualFocusValue() const = 0;

        /**
         * Sets the manual focus value (0-100). This sets the value only; it does NOT change the mode.
         * @param nValue A value in the range 0-100, mapped linearly onto the camera's focus range.
         *               On standard (UVC) cameras the value increases with focus distance — 0 is the
         *               nearest focus and 100 the farthest — but the exact direction and units are
         *               device/driver-dependent and not guaranteed.
         * @return PLNK_FOCUS_CONTROL_RESULT_SUCCESS on success,
         *         PLNK_FOCUS_CONTROL_RESULT_NOT_SUPPORTED if the camera does not support manual focus control,
         *         PLNK_FOCUS_CONTROL_RESULT_OUT_OF_RANGE if nValue > 100,
         *         PLNK_FOCUS_CONTROL_RESULT_INTERNAL_ERROR if the OS call fails.
         * @remark If the current mode is MANUAL, the value is applied immediately (next capture cycle);
         *         if AUTO, it is stored and used on the next SetFocusMode(MANUAL).
         */
        virtual EFocusControlResult SetManualFocusValue(unsigned int nValue) = 0;
    };

    using CameraInfoPtr = SharedPtr<CameraInfo>;
    using CameraInfoOptional = Optional<CameraInfoPtr>;
    using CameraInfoArray = Array<CameraInfoPtr>;
};