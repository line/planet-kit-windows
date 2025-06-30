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

#include "PlanetKitSharedPtr.hpp"
#include "PlanetKitPeer.h"

namespace PlanetKit {
    /// Updated information of peers list who are connected to or disconnected from a subgroup.
    class PLANETKIT_API ConferencePeerUpdateParam {
    public:
        virtual ~ConferencePeerUpdateParam() { }

        /// Gets the conference subgroup instance.
        virtual SubgroupPtr GetSubgroup() = 0;

        /// Gets the array of added peers.
        virtual const PeerArray& GetAddedPeer() = 0;

        /// Gets the array of removed peers.
        virtual const PeerArray& GetRemovedPeer() = 0;

        /// Gets the total peers count.
        virtual size_t TotalCount() = 0;
    };

    typedef SharedPtr<ConferencePeerUpdateParam> ConferencePeerUpdateParamPtr;
}