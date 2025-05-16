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
#include "PlanetKitUserId.h"
#include "PlanetKitVideoCommon.h"

namespace PlanetKit {
    /**
     * This class is provided to receive peer's video data and render it directly.
     * @remark
     *   You should create a custom class that inherits from this class.
     * @see
     *   - PlanetKitConference::RegisterMyVideoReceiver
     *   - PlanetKitConference::RegisterPeersVideoReceiver
     *   - PlanetKitConference::RegisterMyScreenShareReceiver
     *   - PlanetKitConference::RegisterPeerScreenShareReceiver
     *   - PlanetKitConference::DeregisterMyVideoReceiver
     *   - PlanetKitConference::DeregisterPeersVideoReceiver
     *   - PeerControl::SetReceiver
     */
    class PLANETKIT_API IVideoReceiver {
    public:
        virtual ~IVideoReceiver() { }

        /**
         * Called when the peer's video data is activated.
         * @param pVideoFrame Peer's video data. You can render the peer's video with this parameter.
         * @param szPeerId Peer's ID.
         * @param szPeerServiceId Peer's service ID.
         * @remark
         * - In the case of the local user's own frame, the ID and ServiceID will be nullptr.
         */
        virtual void OnVideo(const SVideoFrame& pVideoFrame, UserIdPtr pUserID) = 0;
    };

    typedef SharedPtr<IVideoReceiver> IVideoReceiverPtr;
};