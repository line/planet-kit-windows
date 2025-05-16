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

#include "PlanetKit.h"
#include "PlanetKitVideoCommon.h"
#include "PlanetKitManager.h"

namespace PlanetKit {
    class PLANETKIT_API VideoSource {
    public :
        VideoSource(EVideoCapturerType eType) {
            m_eType = eType;
        }

        /**
         * Acquires the current capturer type.
         * @return Current capturer type.
         */
        EVideoCapturerType GetType() {
            return m_eType;
        }

        /**
         * Checks whether it is currently possible to send frames to the counterpart.
         * @param ullTick64 Current frame tick count
         * @return Returns true if it is possible to deliver frames to the counterpart.
         */
        bool IsPostingFrameAvailable(UINT64 ullTick64) {
            if (m_eType == EVideoCapturerType::PLNK_VID_CAPTURER_CAMERA) {
                CameraControllerPtr pController = GetCameraController();
                if (pController != nullptr) {
                    return pController->IsPostingFrameAvailable(ullTick64);
                }
            }
            else if (m_eType == EVideoCapturerType::PLNK_VID_CAPTURER_SCREEN || m_eType == EVideoCapturerType::PLNK_VID_CAPTURER_WINDOW) {
                ScreenShareControllerPtr pController = GetSCreenShareController();
                if (pController != nullptr) {
                    return pController->IsPostingFrameAvailable(ullTick64);
                }
            }

            return true;
        }

        /**
         * Delivers the frame to the counterpart.
         * @param sPlanetKitVideoFrame The captured frame.
         * @return Returns true when the frame processing is successful.
         */
        bool OnFrame(SVideoFrame& sPlanetKitVideoFrame) {
            if (m_eType == EVideoCapturerType::PLNK_VID_CAPTURER_CAMERA) {
                CameraControllerPtr pController = GetCameraController();
                if (pController != nullptr) {
                    return pController->WriteFrameData(sPlanetKitVideoFrame);
                }
            }
            else if (m_eType == EVideoCapturerType::PLNK_VID_CAPTURER_SCREEN || m_eType == EVideoCapturerType::PLNK_VID_CAPTURER_WINDOW) {
                ScreenShareControllerPtr pController = GetSCreenShareController();
                if (pController != nullptr) {
                    return pController->WriteFrameData(sPlanetKitVideoFrame);
                }
            }

            return false;
        }
    private:
        CameraControllerPtr GetCameraController() {
            PlanetKitManagerPtr pManager = PlanetKitManager::GetInstance();
            if (pManager.hasValue() == false) {
                CameraControllerPtr pCameraController;
                return pCameraController;
            }

            return pManager->GetCameraController();
        }

        ScreenShareControllerPtr GetSCreenShareController() {
            PlanetKitManagerPtr pManager = PlanetKitManager::GetInstance();
            if (pManager.hasValue() == false) {
                ScreenShareControllerPtr pScreenShareController;
                return pScreenShareController;
            }

            return pManager->GetScreenShareController();
        }

        EVideoCapturerType m_eType = EVideoCapturerType::PLNK_VID_CAPTURER_CAMERA;
    };
};