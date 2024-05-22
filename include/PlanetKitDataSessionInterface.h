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

namespace PlanetKit
{
    class PLANETKIT_API OutboundDataSession;
    class PLANETKIT_API InboundDataSession;

    template class PLANETKIT_API AutoPtr<OutboundDataSession>;
    typedef AutoPtr<OutboundDataSession> OutboundDataSessionPtr;

    template class PLANETKIT_API AutoPtr<InboundDataSession>;
    typedef AutoPtr<InboundDataSession> InboundDataSessionPtr;
    
    const unsigned int kDataSessionStreamIdMin = 100;
    const unsigned int kDataSessionStreamIdMax = 1000;

    typedef unsigned int DataSessionStreamIdT;

    /**
     * @brief Data session streaming type
     */
    typedef enum EDataSessionType 
    {
        /// Lost messages will be retransmitted.
        PLNK_DATA_SESS_TYPE_RELIABLE_MSG = 0,
        /// Lost packets will be retransmitted.
        PLNK_DATA_SESS_TYPE_RELIABLE_BYTES,
        /// Lost bytes are not retransmitted.
        PLNK_DATA_SESS_TYPE_UNRELIABLE_BYTES,
        /// Lost messages are not retransmitted.
        PLNK_DATA_SESS_TYPE_UNRELIABLE_MSG,
        /// Not supported type
        PLNK_DATA_SESS_TYPE_UNKNOWN
    } EDataSessionType;

    /**
     * @brief This is the definition of an exception that occurred during data session communication.
     */
    typedef enum EDataSessException 
    {
        /// The data traffic is too much.
        PLNK_DATA_SESS_EXCEPTION_TOO_LONG_QUEUED_DATA,
    } EDataSessException;

    /**
     * Fail reason related to data session
     */
    typedef enum EDataSessionFailReason
    {
        /// Reason none
        PLNK_DATA_SESS_FAIL_REASON_NONE = 0,
        /// An internal error occurred.
        PLNK_DATA_SESS_FAIL_REASON_INTERNAL = 1,
        /// There is no incoming data.
        PLNK_DATA_SESS_FAIL_REASON_NOT_INCOMING = 3,
        /// The stream ID already exists.
        PLNK_DATA_SESS_FAIL_REASON_ALREADY_EXIST = 4,
        /// The stream ID is invalid.
        PLNK_DATA_SESS_FAIL_REASON_INVALID_ID = 5,
        /// The data session type is invalid.
        PLNK_DATA_SESS_FAIL_REASON_INVALID_TYPE = 6,
    } EDataSessionFailReason;


    typedef enum EDataSessionClosedReason {
        /// Data session has ended.
        PLNK_DATA_SESSION_CLOSED_REASON_SESSION_END = 0,
        /// Unexpected error occurred internally.
        PLNK_DATA_SESSION_CLOSED_REASON_INTERNAL = 1,
        /// Data session ID is unsupported by the peer.
        PLNK_DATA_SESSION_CLOSED_REASON_UNSUPPORTED = 2,
    } EDataSessionClosedReason;

    /**
     * Data session frame
     */
    class PLANETKIT_API DataSessionFrame : public Base {
    public :
        /**
         * Gets the data buffer.
         */
        virtual const void* GetBuffer() = 0;

        /**
         * Gets the bytes length of the buffer size.
         */
        virtual unsigned int GetDataLength() = 0;

        /**
         * Gets the time stamp.
         */
        virtual long long GetTimeStamp() = 0;

        /**
         * Gets the offset.
         */
        virtual long long GetOffset() = 0;

        /**
         * Gets the peer's ID.
         */
        virtual UserIdPtr GetUserID() = 0;
    };

    template class PLANETKIT_API AutoPtr<DataSessionFrame>;
    typedef AutoPtr<DataSessionFrame> DataSessionFramePtr;

    /**
     * Defines a set of callbacks related to changes of OutboundDataSession.
     */
    class PLANETKIT_API IOutboundDataSessionHandler {
    public:
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

    class IReceiveDataSessionHandler;
    /**
     * Defines a set of callbacks related to changes of InboundDataSession.
     */
    class PLANETKIT_API IInboundDataSessionHandler {
    public:
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
        virtual IOutboundDataSessionHandler* GetHandler() = 0;

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

    class PLANETKIT_API InboundDataSession : public Base {
    public:
        /**
        * Gets the current stream ID.
        * @return Stream ID
        */
        virtual DataSessionStreamIdT GetStreamId() = 0;

        /**
        * Gets the current inbound data session handler instance.
        * @return IInboundDataSessionHandler instance
        */
        virtual IInboundDataSessionHandler* GetReceiver() = 0;
    };
}