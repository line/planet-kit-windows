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

#include "PlanetKitStatisticsAudioSend.h"
#include "PlanetKitStatisticsAudioRecv.h"

#include "PlanetKitStatisticsVideoSend.h"
#include "PlanetKitStatisticsVideoRecv.h"

#include "PlanetKitStatisticsScreenShareSend.h"
#include "PlanetKitStatisticsScreenShareRecv.h"


namespace PlanetKit {
    /**
     * @brief Statistics information
     */
    class PLANETKIT_API Statistics {
    public :
        virtual ~Statistics() { }

        /// Outgoing audio statistics information
        virtual StatisticsAudioSendPtr AudioSend() = 0;
        /// Incoming audio statistics information
        virtual StatisticsAudioRecvPtr AudioRecv() = 0;
        
        /**
         * @brief Gets the outgoing video statistics information.
         *   You can get StatisticsVideoSend* on success.
         *   Return value can be PlanetKit::NullOptional when this instance doesn't have statistic of video transmission.
         */
        virtual StatisticsVideoSendOptional GetVideoSend() = 0;

        /// Gets statistics of incoming video as an array.
        virtual const StatisticsVideoRecvArray& GetVideoRecv() = 0;

        /**
         * @brief Gets the outgoing screen share statistics information.
         * @return
         *   You can get StatisticsScreenSharingSend* on success.
         *   Return value can be PlanetKit::NullOptional when this instance doesn't have statistic of screen share Send.
         */
        virtual StatisticsScreenShareSendOptional GetScreenShareSend() = 0;

        /// Gets statistics of incoming screen share as an array.
        virtual const StatisticsScreenShareRecvArray& GetScreenShareRecv() = 0;
    };

    typedef SharedPtr<Statistics> StatisticsPtr;
    typedef Optional<StatisticsPtr> StatisticsOptional;

};