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
#include "PlanetKitUserId.h"
#include "PlanetKitTypes.h"

namespace PlanetKit
{
    class PLANETKIT_API Statistics;
    class PLANETKIT_API StatisticsVideoRecv;
    class PLANETKIT_API StatisticsVideoSend;

    class PLANETKIT_API StatisticsScreenShareRecv;
    class PLANETKIT_API StatisticsScreenShareSend;

    template class PLANETKIT_API AutoPtr<Statistics>;
    typedef AutoPtr<Statistics> StatisticsPtr;

    template class PLANETKIT_API Optional<StatisticsPtr>;
    typedef Optional<StatisticsPtr> StatisticsOptional;

    template class PLANETKIT_API AutoPtr<StatisticsVideoRecv>;
    typedef AutoPtr<StatisticsVideoRecv> StatisticsVideoRecvPtr;

    template class PLANETKIT_API Array<StatisticsVideoRecvPtr>;
    typedef Array<StatisticsVideoRecvPtr> StatisticsVideoRecvArray;


    template class PLANETKIT_API Optional<StatisticsVideoSend*>;
    typedef Optional<StatisticsVideoSend*> StatisticsVideoSendOptional;

    template class PLANETKIT_API AutoPtr<StatisticsScreenShareRecv>;
    typedef AutoPtr<StatisticsScreenShareRecv> StatisticsScreenShareRecvPtr;

    template class PLANETKIT_API Array<StatisticsScreenShareRecvPtr>;
    typedef Array<StatisticsScreenShareRecvPtr> StatisticsScreenShareRecvArray;

    template class PLANETKIT_API Optional<StatisticsScreenShareSend*>;
    typedef Optional<StatisticsScreenShareSend*> StatisticsScreenShareSendOptional;


    typedef void StatisticsScreenSharingSendOptional;
    typedef void StatisticsScreenSharingRecvArray;

    /**
     * @brief Network statistics information
     */
    class PLANETKIT_API StatisticsNetwork
    {
    public :
        /// Loss Rate
        virtual FloatOptional LossRate() = 0;

        /// Jitter ms
        virtual UIntOptional JitterMS() = 0;

        /// Latency ms
        virtual UIntOptional LatencyMS() = 0;

        /// Bits per second
        virtual unsigned int BPS() = 0;
    };

    /**
     * @brief Video statistics information
     */
    class PLANETKIT_API StatisticsVideo
    {
    public :
        /// Width of the screen
        virtual unsigned short Width() = 0;
        /// Height of the screen
        virtual unsigned short Height() = 0;
        /// Frames per second
        virtual unsigned short FPS() = 0;
    };

    /**
     * @brief Outgoing audio statistics information
     */
    class PLANETKIT_API StatisticsAudioSend {
    public :
        /// Network statistics information
        virtual StatisticsNetwork* Network() = 0;
    };

    /**
     * @brief Incoming audio statistics information
     */
    class PLANETKIT_API StatisticsAudioRecv
    {
    public:
        /// Network statistics information
        virtual StatisticsNetwork* Network() = 0;
    };

    /**
     * @brief Outgoing video statistics information
     */
    class PLANETKIT_API StatisticsVideoSend
    {
    public :
        /// Network statistics information
        virtual StatisticsNetwork* Network() = 0;
        /// Video statistics information
        virtual StatisticsVideo* Video() = 0;
    };

    /**
     * @brief Incoming video statistics information
     */
    class PLANETKIT_API StatisticsVideoRecv : public Base {
    public :
        /// Gets the peer's ID.
        virtual UserIdPtr GetPeerID() = 0;

        /**
         * Gets the subscribed subgroup name.
         * @return
         *  - The subgroup name string which is encoded in UTF-16 and null-terminated.<br>
         *  - It also can be NullOptional and it means 'main room'.
         */
        virtual const WStringOptional& GetSubgroupName() = 0;

        /// Network statistics information
        virtual StatisticsNetwork* Network() = 0;
        /// Video statistics information
        virtual StatisticsVideo* Video() = 0;
    };

    /**
     * @brief Outgoing screen share statistics information
     */
    class PLANETKIT_API StatisticsScreenShareSend
    {
    public:
        /// Network statistics information
        virtual StatisticsNetwork* Network() = 0;
        /// Video statistics information
        virtual StatisticsVideo* Video() = 0;
    };

    /**
     * @brief Incoming screen share statistics information
     */
    class PLANETKIT_API StatisticsScreenShareRecv : public Base {
    public:
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
        virtual StatisticsNetwork* Network() = 0;
        /// Video statistics information
        virtual StatisticsVideo* Video() = 0;
    };

    /**
     * @brief Statistics information
     */
    class PLANETKIT_API Statistics : public Base
    {
    public :
        /// Outgoing audio statistics information
        virtual StatisticsAudioSend* AudioSend() = 0;
        /// Incoming audio statistics information
        virtual StatisticsAudioRecv* AudioRecv() = 0;
        
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
};