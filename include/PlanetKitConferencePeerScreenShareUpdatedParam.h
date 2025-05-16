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
#include "PlanetKitPeer.h"

namespace PlanetKit {
    /**
     * Parameter used for updates of peer's screen share information.
     */
    class PLANETKIT_API ConferencePeerScreenShareUpdatedParam {
    public:
        virtual ~ConferencePeerScreenShareUpdatedParam() { }

        /// Gets the peer's information object.
        virtual PeerPtr GetPeer() = 0;

        /// Gets the subgroup information object.
        virtual SubgroupPtr GetSubgroup() = 0;

        /// Gets the screen share state.
        virtual EScreenShareState ScreenShareState() = 0;
    };

    typedef SharedPtr<ConferencePeerScreenShareUpdatedParam> ConferencePeerScreenShareUpdatedParamPtr;
};