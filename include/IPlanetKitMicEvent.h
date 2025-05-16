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

#include "PlanetKitAudioCommon.h"

namespace PlanetKit {
    class PLANETKIT_API IMicEvent;
    typedef SharedPtr<IMicEvent> MicEventPtr;

    /**
     * Event for receiving audio frames incoming through the microphone.
     */
    class PLANETKIT_API IMicEvent {
    public:
        virtual ~IMicEvent() {};
        /**
         * Event for receiving audio frames.
         * @param sAudioData Audio data
         */
        virtual bool DidCapture(const SAudioData& sAudioData) = 0;
    };
}