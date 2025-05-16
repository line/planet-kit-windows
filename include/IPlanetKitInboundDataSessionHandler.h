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
#include "PlanetKitDatasessionDefine.h"
#include "PlanetKitDataSessionFrame.h"

namespace PlanetKit {
    class PLANETKIT_API InboundDataSession;
    typedef AutoPtr<InboundDataSession> InboundDataSessionPtr;

    /**
     * Defines a set of callbacks related to changes of InboundDataSession.
     */
    class PLANETKIT_API IInboundDataSessionHandler {
    public:
        virtual ~IInboundDataSessionHandler() { }

        /**
         * Called when when a chunk of data is received from the peer.
         * @param nStreamId Stream ID
         * @param pFrame Received data
         */
        virtual void OnReceive(DataSessionStreamIdT nStreamId, DataSessionFramePtr pFrame) = 0;

        /**
         * Called when the inbound data session has been successfully made.
         * @param pInboundDataInterface Inbound data session that is made by the MakeInboundDataSession API.
         * @param pUserData User data that you sent when you called the MakeInboundDataSession API.
         */
        virtual void OnSuccess(InboundDataSessionPtr pInboundDataInterface, void* pUserData) = 0;

        /**
         * Called when a new inbound data session cannot be established.
         * @param pUserData User data that you sent when you called the MakeInboundDataSession API.
         * @param eFailReason Fail reason.
         * @see EDataSessionFailReason
         */
        virtual void OnError(void* pUserData, EDataSessionFailReason eFailReason) = 0;

        /**
         * Called when an inbound data session is closed.
         * @param pUserData User data that you sent when you called the MakeInboundDataSession API.
         * @param eClosedReason Reason for closure.
         * @see EDataSessionClosedReason
         */
        virtual void OnClosed(void* pUserData, EDataSessionClosedReason eClosedReason) = 0;
    };

    typedef SharedPtr<IInboundDataSessionHandler> IInboundDataSessionHandlerPtr;
};