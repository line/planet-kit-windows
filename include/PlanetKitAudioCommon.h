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

#include "PlanetKitAudioDeviceInfo.h"
#include "IPlanetKitAudioVolumeLevelChangedEvent.h"

namespace PlanetKit {
    /**
     * @brief Initial state of the local user's audio when a call or conference starts.
     */
    enum EInitialMyAudioState {
        /// Start with the local audio unmuted and sent to the peer from the beginning. This is the default.
        PLNK_INITIAL_MY_AUDIO_STATE_UNMUTED = 0,
        /// Start with the local audio muted. The microphone is not used at start, so the local audio is not sent to the peer and the peer is notified that the local user's audio is muted.
        PLNK_INITIAL_MY_AUDIO_STATE_MUTED   = 1,
    };
}
