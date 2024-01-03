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

    //PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use OutboundDataSession.")
    /**
     * @deprecated This will not be supported in 5.2 or later.
     */
    class PLANETKIT_API SendDataSessionInterface;

    //PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use InboundDataSession.")
    /**
     * @deprecated This will not be supported in 5.2 or later.
     */
    class PLANETKIT_API RecvDataSessionInterface;

    class PLANETKIT_API OutboundDataSession;
    class PLANETKIT_API InboundDataSession;

    typedef AutoPtr<OutboundDataSession> OutboundDataSessionPtr;
    typedef AutoPtr<InboundDataSession> InboundDataSessionPtr;

    //PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use OutboundDataSessionPtr.")
    /**
     * @deprecated This will not be supported in 5.2 or later.
     */
    typedef AutoPtr<SendDataSessionInterface> SendDataSessionInterfacePtr;
    //PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use InboundDataSessionPtr.")
    /**
     * @deprecated This will not be supported in 5.2 or later.
     */
    typedef AutoPtr<RecvDataSessionInterface> ReceiveDataSessionInterfacePtr;

    
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
    
    PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later. Use EDataSessionFailReason.")
    /**
     * @deprecated This will not be supported in 5.1 or later.
     */
    typedef enum EMakeDataSessionResult
    {
        /// Succeed to create data session
        PLNK_MAKE_DATA_SESSION_RESULT_SUCCESS = 0,
        /// Failed to create data session
        PLNK_MAKE_DATA_SESSION_RESULT_FAILED_TO_CREATE,
        /// There is data session that has same stream ID<br>You can get DataSessionInterface with GetOutboundDataSession or GetInboundDataSession APIs.
        PLNK_MAKE_DATA_SESSION_RESULT_ALREADY_EXIST_STREAM_ID
    } EMakeDataSessionResult;

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
        PLNK_DATA_SESS_FAIL_REASON_INTERNAL,
        /// The data session is unsupported.
        PLNK_DATA_SESS_FAIL_REASON_UNSUPPORTED,
        /// There is no incoming data.
        PLNK_DATA_SESS_FAIL_REASON_NOT_INCOMING,
        /// The stream ID already exists.
        PLNK_DATA_SESS_FAIL_REASON_ALREADY_EXIST,
        /// The stream ID is invalid.
        PLNK_DATA_SESS_FAIL_REASON_INVALID_ID,
        /// The data session type is invalid.
        PLNK_DATA_SESS_FAIL_REASON_INVALID_TYPE,
    } EDataSessionFailReason;

    PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use DataSessionFrame")
    /**
     * @deprecated This will not be supported in 5.2 or later.
     * @see DataSessionFrame
     */
    typedef struct SDataSessionFrame {
    } SDataSessionFrame;

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

    typedef AutoPtr<DataSessionFrame> DataSessionFramePtr;

    PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later. Use ISendDataSessionHandler and IDataSessionReceiver.")
    /**
     * @deprecated This will not be supported in 5.1 or later.
     */
    class PLANETKIT_API IDataSessionExceptionHandler
    {
    public:
        void OnDataSessionException(void *pUserData, EDataSessException eException, bool bTriggered);
    };

    PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use IInboudDataSessionHandler.")
    /**
     * @deprecated This will not be supported in 5.2 or later.
     */
    class ISendDataSessionHandler;

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
    };

    class IReceiveDataSessionHandler;
    /**
     * Defines a set of callbacks related to changes of InboundDataSession.
     */
    class PLANETKIT_API IInboundDataSessionHandler {
    public:

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use OnReceive(DataSessionStreamIdT nStreamId, DataSessionFramePtr pFrame)")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see OnReceive(DataSessionStreamIdT nStreamId, DataSessionFramePtr pFrame)
         */
        void OnReceive(DataSessionStreamIdT nStreamId, SDataSessionFrame* pFrame);

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
    };

    PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later. Use IReceiveDataSessionHandler")
    /**
     * @deprecated This will not be supported in 5.1 or later.
     * @see IInboundDataSessionHandler
     */
    class PLANETKIT_API IDataSessionReceiver
    {
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
         * @param pUserData User data for result handler
         * @param pResultHandler Result callback handler
         * @return true if successful
         * @remark 
         *  - This API only works for outbound data sessions.
         *  - If you want to send a message to everyone, set the pPeerId to nullptr.
         *  - UserIdPtr(nullptr)
         */
        virtual bool ChangeDestination(UserIdPtr pPeerId, void* pUserData, IResultHandler* pResultHandler) = 0;
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

    PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later. Use ISendDataSessionHandler or IReceiveDataSessionHandler")
    /**
     * @deprecated This will not be supported in 5.1 or later.
     * @see IOutboundDataSessionHandler
     * @see IInboundDataSessionHandler
     */
    class PLANETKIT_API IDataSessionHandler
    {
    public:
        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use void OnMakeSendDataSessionResult(SendDataSessionInterfacePtr pSendDataInterface, void* pUserData, bool bSuccess, const char* szExceptDesc)")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         * @see OnMakeSendDataSessionResult
         */
        void OnMakeSendDataSessionResult(SendDataSessionInterface** pSendDataInterface, void* pUserData, bool bSuccess, const char* szExceptDesc);

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use void OnMakeRecvDataSessionResult(RecvDataSessionInterfacePtr pRecvDataInterface, void* pUserData, bool bSuccess, const char* szExceptDesc)")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         * @see OnMakeRecvDataSessionResult
         */
        void OnMakeRecvDataSessionResult(RecvDataSessionInterface** pRecvDataInterface, void* pUserData, bool bSuccess, const char* szExceptDesc);

        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later.")
        /**
         * @deprecated This will not be supported in 5.1 or later.
         */
        void OnMakeSendDataSessionResult(SendDataSessionInterfacePtr pSendDataInterface, void* pUserData, bool bSuccess, const char* szExceptDesc);

        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later.")
        /**
         * @deprecated This will not be supported in 5.1 or later.
         */
        void OnMakeRecvDataSessionResult(ReceiveDataSessionInterfacePtr pRecvDataInterface, void* pUserData, bool bSuccess, const char* szExceptDesc);

        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later.")
        /**
         * @deprecated This will not be supported in 5.1 or later.
         */
        void OnMakeSendDataSessionResult(SendDataSessionInterfacePtr pSendDataInterface, void* pUserData, EDataSessionFailReason eFailReason, IOutboundDataSessionHandler* pSessionHandler);

        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later.")
        /**
         * @deprecated This will not be supported in 5.1 or later.
         */
        void OnMakeRecvDataSessionResult(ReceiveDataSessionInterfacePtr pRecvDataInterface, void* pUserData, EDataSessionFailReason eFailReason, IDataSessionReceiver* pReceiver);
    };
}