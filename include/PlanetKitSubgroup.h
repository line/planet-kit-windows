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
#include "PlanetKitSubgroupAttribute.h"
#include "PlanetKitPeer.h"
#include "PlanetKitDataSessionInterface.h"

namespace PlanetKit {
    class PLANETKIT_API Subgroup : public Base {
    public:
        /**
        * Gets the peer list.
        * @return Array of Peers
        */
        virtual bool GetPeerList(PeerArray& arrResult) = 0;

        /**
         * Gets the instance of subgroup's attribute..
         */
        virtual SubgroupAttributePtr GetAttribute() = 0;

        /**
        * Gets the current peer list length.
        * @return Length of peer list
        */
        virtual size_t GetTotalPeersCount() = 0;

        /**
        * Gets the subgroup name string which is encoded in UTF-16 and null-terminated.<br>This can be `NullOptional` that means `MainRoom`.
        * @return The subgroup name string.
        */
        virtual const WStringOptional& GetSubgroupName() = 0;

        /**
         * Gets the existing outbound data session.
         * @param nStreamId Stream ID of the data session to get.
         * @param pResult Result OutboundDataSession.
         * @return true on success, false if it does not exist.
         */
        virtual bool GetOutboundDataSession(int nStreamId, OutboundDataSessionPtr* pResult) = 0;

        /**
         * Gets the existing inbound data session.
         * @param nStreamId Stream ID of the data session to get.
         * @param pResult Result InboundDataSession.
         * @return true on success, false if it does not exist.
         */
        virtual bool GetInboundDataSession(int nStreamId, InboundDataSessionPtr* pResult) = 0;

        /**
         * Makes an outbound data session.
         * @param nStreamId Stream ID from 100 to 999
         * @param eType Data session type
         * @param pResultUserData You can specify data to be passed along when pDataSessionHandler is called.
         * @param pDataSessionHandler This is a callback handler that occurs for exception handling when an exception occurs during data transmission.
         * @return true on successful function call. The result must be checked.
         */
        virtual bool MakeOutboundDataSession(int nStreamId, EDataSessionType eType, NULLABLE void* pResultUserData, IOutboundDataSessionHandlerPtr pDataSessionHandler) = 0;

        /**
         * Makes an inbound data session.
         * @param nStreamId Stream ID from 100 to 999
         * @param pResultUserData You can specify data to be passed along when pDataSessionHandler is called.
         * @param pDataSessionHandler Specifies the callback handler that is called when receiving data or when an exception occurs.
         * @return true on successful function call. The result must be checked.
         */
        virtual bool MakeInboundDataSession(int nStreamId, NULLABLE void* pResultUserData, IInboundDataSessionHandlerPtr pDataSessionHandler) = 0;

        /**
        * Unsupports an inbound data session.
        * @param nStreamId
        * @return true on success
        */
        virtual bool UnsupportInboundDataSession(DataSessionStreamIdT nStreamId) = 0;
    };
};