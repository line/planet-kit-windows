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
#include "PlanetKitVideoCommon.h"
#include "PlanetKitVideoRender.h"
#include "PlanetKitVideoStatus.h"

#include "IPlanetKitMyMediaStatusEvent.h"

namespace PlanetKit {
    /**
     * The local user's media status information class.<br>
     * An event class that you can subscribe to for the local user's media status changes provided by PlanetKitConference APIs.<br>
     * Events provided by the IMyMediaStatusEvent class occurs when the video, screen share, or audio statuses change.<br>
     */
    class MyMediaStatus : public Base {
    public :
        /// Registers the IMyMediaStatusEvent listener. You can get IMyMediaStatusEvent::OnRegisterResult event after registering.
        virtual bool Register(IMyMediaStatusEventPtr pListener) = 0;

        /// Unregisters the IMyMediaStatusEvent listener.
        virtual bool Unregister() = 0;

        /**
         * Gets the local user's video subgroup name.
         * @remark
         *  - Returns String class if the local user's video is being sent to a subgroup, or NullOptional if not sending the local user's video to a subgroup.
         */
        virtual WStringOptional GetVideoSubgroupName() = 0;

        /// Gets the local user's video status.
        virtual bool GetVideoStatus(OUT VideoStatus* pResultStatus) = 0;

        /**
         * Gets the local user's screen share subgroup name.
         * @remark
         *  - Returns String class if the local user's screen share is being sent to a subgroup, or NullOptional if not sending the local user's screen share to a subgroup.
         */
        virtual WStringOptional GetScreenShareSubgroupName() = 0;

        /// Gets the local user's screen share state.
        virtual EScreenShareState GetScreenShareState() = 0;

        /// Gets whether the local user's audio is muted.
        virtual bool IsAudioMuted() = 0;
    };
};