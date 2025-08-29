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
#include "PlanetKitCommonTypes.h"

namespace PlanetKit {
    /**
     * @brief Network statistics information
     */
    class PLANETKIT_API StatisticsNetwork {
    public:
        virtual ~StatisticsNetwork() { }

        /// Loss Rate
        virtual FloatOptional LossRate() = 0;

        /// Jitter ms
        virtual UIntOptional JitterMS() = 0;

        /// Latency ms
        virtual UIntOptional LatencyMS() = 0;

        /// Bits per second
        virtual unsigned int BPS() = 0;
    };

    typedef SharedPtr<StatisticsNetwork> StatisticsNetworkPtr;
};