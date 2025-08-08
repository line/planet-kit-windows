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

#include "PlanetKitAudioDefine.h"

namespace PlanetKit {
    /**
     * Audio device information class
     */
    class PLANETKIT_API AudioDeviceInfo {
    public:
        virtual ~AudioDeviceInfo() {}

        /// Device ID
        virtual const WString& GetID() = 0;
        /// Device name
        virtual const WString& GetName() = 0;
        /// Device type
        virtual EAudioDeviceType GetDeviceType() = 0;
        /// Physical form factor of the device
        virtual EPhysicalFormFactor GetFormFactor() = 0;
    };

    using AudioDeviceInfoPtr = SharedPtr<AudioDeviceInfo>;
    using AudioDeviceInfoOptional = Optional<AudioDeviceInfoPtr>;
    using AudioDeviceInfoArray = Array<AudioDeviceInfoPtr>;
};