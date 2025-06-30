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
#include "PlanetKitStatisticsNetwork.h"
#include "PlanetKitStatisticsVideo.h"
#include "PlanetKitUserId.h"

namespace PlanetKit {
    /**
     * @brief Incoming screen share statistics information
     */
    class PLANETKIT_API StatisticsScreenShareRecv {
    public:
        virtual ~StatisticsScreenShareRecv() { }

        /**
         * Gets the subscribed subgroup name.
         * @return
         *  - The subgroup name string which is encoded in UTF-16 and null-terminated.<br>
         *  - It also can be NullOptional and it means 'main room'.
         */
        virtual const WStringOptional& GetSubgroupName() = 0;

        /// Gets the peer's ID.
        virtual UserIdPtr GetPeerID() = 0;

        /// Network statistics information
        virtual StatisticsNetworkPtr Network() = 0;
        /// Video statistics information
        virtual StatisticsVideoPtr Video() = 0;
    };

    typedef SharedPtr<StatisticsScreenShareRecv> StatisticsScreenShareRecvPtr;
    typedef Array<StatisticsScreenShareRecvPtr> StatisticsScreenShareRecvArray;
};