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
#include "PlanetKitContainer.hpp"
#include "PlanetKitOptional.hpp"

namespace PlanetKit
{
    class PLANETKIT_API Statistics;
    class PLANETKIT_API StatisticsVideoRecv;
    class PLANETKIT_API StatisticsVideoSend;

    class PLANETKIT_API StatisticsScreenShareRecv;
    class PLANETKIT_API StatisticsScreenShareSend;

    typedef AutoPtr<Statistics> StatisticsPtr;
    typedef Optional<StatisticsPtr> StatisticsOptional;

    typedef AutoPtr<StatisticsVideoRecv> StatisticsVideoRecvPtr;
    typedef Array<StatisticsVideoRecvPtr> StatisticsVideoRecvArray;

    typedef Optional<StatisticsVideoSend*> StatisticsVideoSendOptional;
    typedef AutoPtr<StatisticsScreenShareRecv> StatisticsScreenShareRecvPtr;
    typedef Array<StatisticsScreenShareRecvPtr> StatisticsScreenShareRecvArray;
    typedef Optional<StatisticsScreenShareSend*> StatisticsScreenShareSendOptional;


    typedef void StatisticsScreenSharingSendOptional;
    typedef void StatisticsScreenSharingRecvArray;

    /**
     * @brief Network statistics information
     */
    class PLANETKIT_API StatisticsNetwork
    {
    public :
        /// Loss rate
        virtual float LossRate() = 0;
        /// Checks whether there is loss rate information.
        virtual bool HasLossRate() = 0;
        
        /// Jitter ms
        virtual unsigned int JitterMS() = 0;
        /// Checks whether there is jitter ms information.
        virtual bool HasJitterMS() = 0;

        /// Latency ms
        virtual unsigned int LatencyMS() = 0;
        /// Checks whether there is latency ms information.
        virtual bool HasLatency() = 0;

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
    class PLANETKIT_API StatisticsAudioSend
    {
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
        
        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use UserIdPtr GetPeerID()")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see UserIdPtr GetPeerID()
         */
        const char* PeerId();

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use UserIdPtr GetPeerID()")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see UserIdPtr GetPeerID()
         */
        const char* PeerServiceId();

        /// Gets the peer's ID.
        virtual UserIdPtr GetPeerID() = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use const wchar_t* GetSubgroupName()")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see const wchar_t* GetSubgroupName()
         */
        const char* SubgroupName();

        /**
         * Gets the subscribed subgroup name.
         * @return
         *  - The subgroup name string which is encoded in UTF-16 and null-terminated.<br>
         *  - It also can be nullptr and it means 'main room'.
         */
        virtual const wchar_t* GetSubgroupName() = 0;

        /// Network statistics information
        virtual StatisticsNetwork* Network() = 0;
        /// Video statistics information
        virtual StatisticsVideo* Video() = 0;
    };

    PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later.")
    /**
     * @deprecated This will not be supported in 5.1 or later.
     * @see StatisticsScreenShareSend
     */
    class PLANETKIT_API StatisticsScreenSharingSend
    {
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

    PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later.")
    /**
     * @deprecated This will not be supported in 5.1 or later.
     * @see StatisticsScreenShareRecv
     */
    class PLANETKIT_API StatisticsScreenSharingRecv
    {
    public:
    };

    /**
     * @brief Incoming screen share statistics information
     */
    class PLANETKIT_API StatisticsScreenShareRecv : public Base {
    public:
        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use UserIdPtr GetPeerID()")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see UserIdPtr GetPeerID()
         */
        const char* PeerId();
        
        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use UserIdPtr GetPeerID()")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see UserIdPtr GetPeerID()
         */
        const char* PeerServiceId();

        /// Gets the peer's ID.
        virtual UserIdPtr GetPeerID() = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use const wchar_t* GetSubgroupName()")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see const wchar_t* GetSubgroupName()
         */
        const char* SubgroupName();

        /**
         * Gets the subscribed subgroup name.
         * @return
         *  - The subgroup name string which is encoded in UTF-16 and null-terminated.<br>
         *  - It also can be nullptr and it means 'main room'.
         */
        virtual const wchar_t* GetSubgroupName() = 0;

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
        
        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use StatisticsVideoSendOptional GetVideoSend()")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         * @see GetVideoSend
         */
        StatisticsVideoSend* VideoSend();

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use StatisticsVideoSendOptional GetVideoSend()")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         * @see GetVideoSend
         */
        bool HasVideoSend();

        /**
         * @brief Gets the outgoing video statistics information.
         *   You can get StatisticsVideoSend* on success.
         *   Return value can be PlanetKit::nullOpt when this instance doesn't have statistic of video transmission.
         */
        virtual StatisticsVideoSendOptional GetVideoSend() = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use const StatisticsVideoRecvArray& GetVideoRecv()")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         * @see GetVideoRecv
         */
        StatisticsVideoRecv* VideoRecvAt(unsigned int nIdx);
        

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use const StatisticsVideoRecvArray& GetVideoRecv()")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         * @see GetVideoRecv
         */
        unsigned int VideoRecvCount();

        /// Gets statistics of incoming video as an array.
        virtual const StatisticsVideoRecvArray& GetVideoRecv() = 0;
        


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. StatisticsScreenSharingSendOptional GetScreenSharingSend()")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         * @see GetScreenSharingSend
         */
        StatisticsScreenSharingSend* ScreenSharingSend();
        
        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. StatisticsScreenSharingSendOptional GetScreenSharingSend()")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         * @see GetScreenSharingSend
         */
        bool HasScreenSharingSend();

        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later.")
        /**
         * @deprecated This will not be supported in 5.1 or later.
         * @see GetScreenShareSend
         */
        StatisticsScreenSharingSendOptional GetScreenSharingSend();

        /**
         * @brief Gets the outgoing screen share statistics information.
         * @return
         *   You can get StatisticsScreenSharingSend* on success.
         *   Return value can be PlanetKit::nullOpt when this instance doesn't have statistic of screen share Send.
         */
        virtual StatisticsScreenShareSendOptional GetScreenShareSend() = 0;


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use const StatisticsScreenSharingRecvArray& GetScreenSharingRecv()")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         * @see GetVideoRecv
         */
        StatisticsScreenSharingRecv* ScreenSharingRecvAt(unsigned int nIdx);
        
        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use const StatisticsScreenSharingRecvArray& GetScreenSharingRecv()")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         * @see GetScreenSharingRecv
         */
        unsigned int ScreenSharingRecvCount();

        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later.")
        /**
         * @deprecated This will not be supported in 5.1 or later.
         * @see GetScreenShareRecv
         */
        StatisticsScreenSharingRecvArray GetScreenSharingRecv();

        /// Gets statistics of incoming screen share as an array.
        virtual const StatisticsScreenShareRecvArray& GetScreenShareRecv() = 0;
    };
};