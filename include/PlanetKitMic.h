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
#include "IPlanetKitMicEvent.h"
#include "IPlanetKitAudioVolumeLevelChangedEvent.h"

namespace PlanetKit {
    class PLANETKIT_API Mic;

    typedef SharedPtr<Mic> MicPtr;
    typedef Optional<MicPtr> MicOptional;

    class PLANETKIT_API Mic {
    public:
        virtual ~Mic() {};

        /**
         * Sets the audio device volume.
         * @param fVolume Volume in the range [0.0F : 1.0F]
         * @return true on success
         */
        virtual bool SetVolumeLevel(float fVolume) = 0;

        /**
         * Gets the audio device volume.
         * @param fVolume Volume in the range [0.0F : 1.0F]
         * @return true on success
         */
        virtual float GetVolumeLevel() = 0;

        /**
         * Registers a microphone event.
         * @param pEvent Microphone event.
         * @return true on success
         */
        virtual bool RegisterMicEvent(MicEventPtr pEvent) = 0;

        /**
         * Deregisters a microphone event.
         * @param pEvent Microphone event.
         * @return true on success
         */
        virtual bool DeregisterMicEvent(MicEventPtr pEvent) = 0;

        /**
         * Gets the peak value of the audio device.
         * @return Buffer to store the meter value in range [0:1]
         */
        virtual float GetPeakValue() = 0;

        /**
         * Checks whether the audio device is running.
         * @return true on running
         */
        virtual bool IsRunning() = 0;

        /**
         * Registers a volume change event.
         * @param pEvent Volume change event.
         * @return true on success
         */
        virtual bool RegisterVolumeLevelChangedEvent(AudioVolumeLevelChangedEventPtr pEvent) = 0;

        /**
         * Deregisters a volume change event.
         * @param pEvent Volume change event.
         * @return true on success
         */
        virtual bool DeregisterVolumeLevelChangedEvent(AudioVolumeLevelChangedEventPtr pEvent) = 0;

        /**
         * Gets device information.
         * @return On success, the function returns the information of the currently active device.
         */
        virtual AudioDeviceInfoPtr GetDeviceInfo() = 0;

        /**
         * Checks whether a custom mic is used for the audio input.
         * @return Returns true if it is custom audio.
         */
        virtual bool IsCustomMic() = 0;
    };
}
