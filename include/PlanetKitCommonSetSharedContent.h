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
    class PLANETKIT_API CommonSetSharedContent {
    public:
        virtual ~CommonSetSharedContent() { }

        /**
         * Gets the peer's ID.
         */
        virtual UserIdPtr GetPeerID() = 0;

        /// Gets Peer.
        virtual PeerPtr GetPeer() = 0;
        
        /// Elapsed time since the peer set the shared content (in milliseconds) 
        virtual unsigned int ElapsedAfterSetMsec() = 0;
        /// Shared data
        virtual BYTE* Data() = 0;
        /// Size of the shared data
        virtual unsigned int DataSize() = 0;
    };

    typedef SharedPtr<CommonSetSharedContent> CommonSetSharedContentPtr;
    typedef Array<CommonSetSharedContentPtr> CommonSetSharedContentArray;
};
