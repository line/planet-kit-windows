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

#include "PlanetKitPredefine.h"
#include "PlanetKitHookedAudio.h"

namespace PlanetKit {
    /**
      * This is an interface used for audio reception in PlanetKitCall::EnableHookMyAudio.
      * @see PlanetKitCall::EnableHookMyAudio
      * @see PlanetKitCall::DisableHookMyAudio
      * @see PlanetKitCall::PutHookedMyAudioBack
      */
    class PLANETKIT_API IAudioHook {
    public:
        virtual ~IAudioHook() { }

        /**
         * @param pHookedAudio Audio frame data sent to peer.
         */
        virtual void OnHooked(HookedAudioPtr pHookedAudio) = 0;
    };

    typedef SharedPtr<IAudioHook> IAudioHookPtr;
};
