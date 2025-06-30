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

namespace PlanetKit {
    class PLANETKIT_API Peer;
    typedef AutoPtr<Peer> PeerPtr;
    typedef Array<PeerPtr> PeerArray;

    class PLANETKIT_API PeerControl;
    typedef AutoPtr<PeerControl> PeerControlPtr;

    /**
     * Result callback API that is called after working of PeerControl::StartVideo.
     */
    using StartVideoResultCallback = void(*)(PeerControlPtr pPeerControl, SRequestMediaResultParam* pRequestMediaResult, void* pUserData);

    /**
     * Result callback API that is called after working of PeerControl::StartVideo.
     */
    using StartVideoResolutionCallback = void(*)(PeerControlPtr pPeerControl, SRequestVideoResolutionResultParam* pRequestMediaResult, void* pUserData);

    /**
     * Result callback API that is called after working of PeerControl::StopVideo.
     */
    using StoptVideoResultCallback = void(*)(PeerControlPtr pPeerControl, SRequestMediaResultParam* pRequestMediaResult, void* pUserData);

};