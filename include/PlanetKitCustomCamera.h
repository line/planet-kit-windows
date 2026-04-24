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

#include "PlanetKitSharedPtr.hpp"
#include "PlanetKitVideoCommon.h"

#include "PlanetKitCameraController.h"
#include "PlanetKitManager.h"

namespace PlanetKit {
    class CameraControllerImpl;

    class CustomCamera {
    public:
        virtual ~CustomCamera() = default;

        /**
         * Called when the camera needs to start capturing/generating video frames.
         * Implement this method to initialize your camera hardware, open video files, or start test pattern generation.
         * This callback is invoked by CameraControllerImpl when the camera should begin operation.
         */
        virtual void OnStart() = 0;

        /**
         * Called when the camera needs to stop capturing/generating video frames.
         * Implement this method to stop frame generation, clean up threads, and release any allocated resources.
         * This callback is invoked by CameraControllerImpl when the camera should cease operation.
         */
        virtual void OnStop() = 0;

    protected:
        /**
         * Writes video frame data to PlanetKit's camera controller.
         * This is a helper method that implementations can use to send captured/generated frames
         * to the PlanetKit system for processing and transmission.
         * @param sVideoFrame The video frame data to write, containing pixel buffer and metadata
         */
        void WriteFrameData(SVideoFrame& sVideoFrame) {
            auto pController = PlanetKitManager::GetInstance()->GetCameraController();
            if (pController) {
                pController->WriteFrameData(sVideoFrame);
            }
        }

        /**
         * Checks whether it is currently possible to deliver frames to the counterpart.
         * @return
         *  - Returns true if it is possible to send frames to the counterpart.
         * @remark
         *  - In case there is a current FPS limit, you need to check the speed of the current frame through the tick count value .
         *  - You can verify whether the current frame can be delivered at an appropriate FPS by checking the speed of this frame.
         */
        bool IsPostingFrameAvailable() {
            auto pController = PlanetKitManager::GetInstance()->GetCameraController();
            if (pController) {
                return pController->IsPostingFrameAvailable();
            }
            return false;
        }

        /**
         * Starts the custom camera and begins video capture/generation.
         * This method should initialize the camera hardware, video file, or test pattern generation.
         */
        void Start() {
            OnStart();
            m_bIsRunning = true;
        }

        /**
         * Stops the custom camera and releases resources.
         * This method should stop frame generation, clean up threads, and release any allocated resources.
         */
        void Stop() {
            OnStop();
            m_bIsRunning = false;
        }

        /**
         * Checks if the custom camera is currently running.
         * @return true if camera is active and capturing/generating frames, false otherwise
         */
        bool IsRunning() {
            return m_bIsRunning;
        }

        friend class CameraControllerImpl;

    private:
        bool m_bIsRunning = false;
    };

    using CustomCameraPtr = SharedPtr<CustomCamera>;
};
