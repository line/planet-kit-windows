#pragma once

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

#include "PlanetKit.h"

#include "PlanetKitPeerControl.h"
#include "PlanetKitSubgroupInterface.h"
#include "PlanetKitPeer.h"

namespace PlanetKit
{
    class PLANETKIT_API Subgroup;
    class PLANETKIT_API PeerVideoStatus;

    template class PLANETKIT_API AutoPtr<PeerVideoStatus>;
    typedef AutoPtr<PeerVideoStatus> PeerVideoStatusPtr;

    template class PLANETKIT_API Array<PeerVideoStatusPtr>;
    typedef Array<PeerVideoStatusPtr> PeerVideoStatusArray;

    struct VideoStatus {
        EVideoState eVideoState;
        EVideoPauseReason eVideoPauseReason = EVideoPauseReason::PLNK_VIDEO_PAUSE_REASON_UNDEFINED;
    };

    typedef Optional<VideoStatus> VideoStatusOptional;

    struct VideoStatusResult {
        VideoStatusOptional videoStatus;
        EPeerGetFailReason ePeerGetFailReason = EPeerGetFailReason::PLNK_PEER_GET_FAIL_REASON_NONE;
    };
    
    class PLANETKIT_API PeerVideoStatus : public Base {
    public:
#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1800)
        virtual ~PeerVideoStatus() = default;
#else
        virtual ~PeerVideoStatus() {

        }
#endif

        /// Gets VideoStatus.
        virtual VideoStatus GetVideoStatus() = 0;
        
        /// Gets Conference Peer.
        virtual PeerPtr GetPeer() = 0;
    };
};
