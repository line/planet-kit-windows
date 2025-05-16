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
     * Window state that is used by screen share.
     */
    typedef enum EWindowState {
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
     * Rotation of video
     */
    typedef enum EVideoRotation {
        /// No rotation
        PLNK_VIDEO_ROTATION_0 = 0,
        /// Rotation by 90 degrees
        PLNK_VIDEO_ROTATION_90 = 1,
        /// Rotation by 180 degrees
        PLNK_VIDEO_ROTATION_180 = 2,
        /// Rotation by 270 degrees
        PLNK_VIDEO_ROTATION_270 = 3
    }EVideoRotation;

    /**
     * Video frame information
     */
    typedef struct SVideoFrame {
        /// Pointer to the frame buffer
        unsigned char* pbuffer;
        /// Allocated buffer size
        unsigned int unBufferSize;
        /// Length (in bytes) of buffer
        unsigned int unDataLength;
        /// Width
        unsigned int unWidth;
        /// Height
        unsigned int unHeight;
        /// Tick
        long long llTick;
        /// Time stamp
        long long llTimeStamp;
        /// Duration
        long long llDuration;
        /// Rotation
        EVideoRotation eRotation;

        /// You can use this flag to check whether the frame belongs to the main room.
        bool bSubgroupMain;
        /// Subgroup name that can be used if bSubgroupMain flag is false
        wchar_t szSubgroupName[PLNK_BUFFER_SIZE_512];
    }SVideoFrame;

    template<typename T>
    inline T GET_VIDEO_DATA_LENGTH(const T& witdh, const T& height) {
        return (T)(witdh * height * 1.5);
    }
};