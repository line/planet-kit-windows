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
#include "PlanetKitAudioCommon.h"
#include "PlanetKitAudioDefine.h"

namespace PlanetKit {
    class PLANETKIT_API IAudioVolumeLevelChangedEvent;
    typedef SharedPtr<IAudioVolumeLevelChangedEvent> AudioVolumeLevelChangedEventPtr;

    /**
     * Event listener to notify when the volume level of an audio device changes.
     */
    class PLANETKIT_API IAudioVolumeLevelChangedEvent {
    public:
        virtual ~IAudioVolumeLevelChangedEvent() {};
        /**
         * Event that is triggered when the device's volume changes.
         * @param pAudioInfo Information about the device whose volume has changed.
         * @param sInfo Details of the changed volume level.
         */
        virtual void OnNotify(const AudioDeviceInfoPtr pAudioInfo, const SAudioEndpointVolumeInfo& sInfo) = 0;
    };
}