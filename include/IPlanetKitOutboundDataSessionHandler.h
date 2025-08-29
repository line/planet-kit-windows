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


namespace PlanetKit {
    class PLANETKIT_API OutboundDataSession;
    typedef AutoPtr<OutboundDataSession> OutboundDataSessionPtr;

    /**
     * Defines a set of callbacks related to changes of OutboundDataSession.
     */
    class PLANETKIT_API IOutboundDataSessionHandler {
    public:
        virtual ~IOutboundDataSessionHandler() { }

        /**
         * Called when the data traffic is too much.
         * @param pDataSession The instance of OutboundDataSession where the exception occurred.
         * @param bEnabled true means that the application should stop or lower sending bitrate. false means that the network condition is improving and the application can send more data.
         */
        virtual void OnTooLongQueuedData(OutboundDataSessionPtr pDataSession, bool bEnabled) = 0;

        /**
         * Called when the peer has called UnsupportInboundDataSession().
         * @param pDataSession The instance of OutboundDataSession where the exception occurred.
         */
        virtual void OnUnsupportedStreamId(OutboundDataSessionPtr pDataSession) = 0;

        /**
         * Called when the outbound data session has been successfully made.
         * @param pDataSession Outbound data session that is made by MakeOutboundDataSession API.
         * @param pUserData User data that you sent when you called MakeOutboundDataSession API.
         */
        virtual void OnSuccess(OutboundDataSessionPtr pDataSession, void* pUserData) = 0;

        /**
         * Called when a new outbound data session cannot be established.
         * @param pUserData User data that you sent when you called MakeOutboundDataSession API.
         * @param eFailReason Fail reason.
         * @see EDataSessionFailReason
         */
        virtual void OnError(void* pUserData, EDataSessionFailReason eFailReason) = 0;

        /**
         * Called when an outbound data session is closed.
         * @param pUserData User data that you sent when you called the MakeInboundDataSession API.
         * @param eClosedReason Reason for closure.
         * @see EDataSessionClosedReason
         */
        virtual void OnClosed(void* pUserData, EDataSessionClosedReason eClosedReason) = 0;
    };

    typedef SharedPtr<IOutboundDataSessionHandler> IOutboundDataSessionHandlerPtr;
};