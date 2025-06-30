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
    enum EMicStartError {
        // This is an error caused by an internal issue.
        PLNK_MIC_START_ERROR_INTERNAL_REASON = 0,
        // The system is currently low on memory.
        PLNK_MIC_START_ERROR_NOT_ENOUGH_MEMORY,
        // The device is not valid.
        PLNK_MIC_START_ERROR_DEVICE_INVALID,
        // The audio service on the Windows system is not functioning properly.
        PLNK_MIC_START_ERROR_AUDIO_SERVICE_NOT_RUNNING,
        // The device is being used exclusively by another app.
        PLNK_MIC_START_ERROR_DEVICE_IN_USE_EXCLUSIVE_BY_OTHER_APPLICATION,
        // CPU usage has exceeded a threshold.
        PLNK_MIC_START_ERROR_CPU_USAGE_EXCEEDED,        
        // Mic preivew event is not valid.
        PLNK_MIC_START_ERROR_PREVIEW_EVENT_NOT_VALID,

    };
    
    class PLANETKIT_API IMicExceptionEvent;
    typedef SharedPtr<IMicExceptionEvent> MicExceptionEventPtr;

    /**
     * Event received when an error occurs while using the microphone device.
     */
    class PLANETKIT_API IMicExceptionEvent {
    public:
        virtual ~IMicExceptionEvent() {};
        /**
         * Event that occurs when there is a failure in using the microphone device.
         * @param eMicrophoneStartError Microphone device error code.
         */
        virtual void OnMicStartError(EMicStartError eMicrophoneStartError) = 0;
    };

}