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
#include "IPlanetKitResultHandler.h"
#include "PlanetKitUserId.h"
#include "IPlanetKitOutboundDataSessionHandler.h"

namespace PlanetKit {
    class PLANETKIT_API OutboundDataSession : public Base {
    public:
        /**
        * Sends data to a data session stream.
        * @param nStreamId Stream ID
        * @param pData Data to send
        * @param nDataSize Size of the data to send
        * @param llTimestamp Time stamp
        * @return true on success
        */
        virtual bool Send(const void* pData, unsigned int nDataSize, unsigned long long llTimestamp) = 0;

        /**
        * Gets the current stream ID.
        * @return Stream ID
        */
        virtual DataSessionStreamIdT GetStreamId() = 0;

        /**
        * Gets the current offset for the outbound data session.
        * @return Current offset in bytes
        */
        virtual unsigned long long GetCurrentOffset() = 0;

        /**
         * Gets the handler that you passed when calling the MakeOutboundDataSession API in PlanetKitCall or PlanetKitConference.
         */
        virtual IOutboundDataSessionHandlerPtr GetHandler() = 0;

        /**
         * Changes the target of the current data session.
         * @param pPeerId Peer's ID.
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true if successful
         * @remark
         *  - This API only works for outbound data sessions.<br>
         *  - If you want to send a message to everyone, set the pPeerId to nullptr.<br>
         *  - UserIdPtr(nullptr)
         */
        virtual bool ChangeDestination(UserIdPtr pPeerId, void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;
    };
};