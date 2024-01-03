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

#include "PlanetKitTypes.h"

#include "PlanetKitVideoCommon.h"
#include "PlanetKitAudioCommon.h"
#include "PlanetKitVideoController.h"
#include "PlanetKitAudioDevice.h"
#include "PlanetKitConnectParam.h"
#include "PlanetKitCcParam.h"
#include "PlanetKitCallStartMessage.h"

namespace PlanetKit
{
    /* Forward declaration */
    class PLANETKIT_API ICallEvent;
    class PLANETKIT_API CallParam;
    typedef AutoPtr<CallParam> CallParamPtr;

    PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later. Use CallStartMessage")
    /**
    * @deprecated This will not be supported in 5.1 or later.
    * @see CallStartMessage
    */
    typedef struct SCallInitData
    {
    } SCallInitData;
    
    PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use CallParam")
    /**
    * @deprecated This will not be supported in 5.0 or later.
    * @see CallParam
    */
    class PLANETKIT_API CallInitParam
    {
    };

    class PLANETKIT_API CallParam : 
        virtual public ConnectParam
    {
    public:
        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see CreateMakeCallParamWithAccessToken
        */
        CallParam* CreateMakeCallParamWithAccessToken(const InitUserId& myID, const InitUserId& peerID, const char* szKey, int nKeyLen);

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see CallParam
        */
        CallParam* CreateMakeCallParamWithAPIKey(const InitUserId& myID, const InitUserId& peerID, const char* szKey);

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see CallParam
        */
        CallParam* CreateVerifyCallParam(const InitUserId& myID, const char* szCcParam);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see MakeCallParamPtr CreateMakeCallParamWithAccessToken(UserIdPtr pMyID, UserIdPtr pPeerID, const wchar_t* szToken)
         */
        MakeCallParamPtr CreateMakeCallParamWithAccessToken(const UserId& myID, const UserId& peerID, const char* szKey, int nKeyLen);

        /**
         * Creates an instance of the MakeCallParam class with an access token.
         * @param pMyID Local user's ID and service ID
         * @param pPeerID Peer's ID and service ID
         * @param szToken Access token string, which should be encoded in UTF-16 and null-terminated
         * @remark
         *  - The parameter 'szToken' must have a string value.<br>
         *  - This API can fail when the 'szToken' parameter is nullptr.
         */
        static MakeCallParamPtr CreateMakeCallParamWithAccessToken(UserIdPtr pMyID, UserIdPtr pPeerID, const wchar_t* szToken);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see MakeCallParamPtr CreateMakeCallParamWithAPIKey(UserIdPtr pMyID, UserIdPtr pPeerID, const wchar_t* szKey)
         */
        MakeCallParamPtr CreateMakeCallParamWithAPIKey(const UserId& myID, const UserId& peerID, const char* szKey);

        /**
         * Creates an instance of the MakeCallParam class with an API key.
         * @param pMyID Local user's ID and service ID
         * @param peerID Peer's ID and service ID
         * @param szKey API key string, which should be encoded in UTF-16 and null-terminated
         * @remark
         *  - The parameter 'szKey' must have a string value.<br>
         *  - This API can fail when the 'szKey' parameter is nullptr.
         */
        static MakeCallParamPtr CreateMakeCallParamWithAPIKey(UserIdPtr pMyID, UserIdPtr pPeerID, const wchar_t* szKey);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see VerifyCallParamPtr CreateVerifyCallParam(UserIdPtr pMyID, CCParamPtr pCCParam)
         */
        VerifyCallParamPtr CreateVerifyCallParam(const UserId& myID, CCParamPtr& pCCParam);

        /**
         * Creates CallParam for using PlanetKitManager::VerifyCall with ccParam.
         * @remark
         *   You can create CCParamPtr by calling PlanetKitManager::CreateCCParam.
         */
        static VerifyCallParamPtr CreateVerifyCallParam(UserIdPtr pMyID, CCParamPtr pCCParam);

        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use Peer().Id()")
        /**
         * @deprecated This will not be supported in 4.4 or later.
         * @see InitUserId
         */
        const char* PeerUserId();

        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use Peer().ServiceId()")
        /**
         * @deprecated This will not be supported in 4.4 or later.
         * @see InitUserId
         */
        const char* PeerServiceId();

        /// Gets the peer's user identifier information class.
        virtual UserIdPtr GetPeer() const = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use const wchar_t* GetRingTonePath()")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see const wchar_t* GetRingTonePath()
         */
        const char* RingTonePath();

        /**
         * Gets the ring tone path.
         * @remark
         *  - The default value of ring tone path is L"./wav_files/ring_48k.wav".
         */
        virtual const wchar_t* GetRingTonePath() = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use const wchar_t* GetRingBackTonePath()")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see const wchar_t* GetRingBackTonePath()
         */
        const char* RingBackTonePath();

        /**
         * Gets the ringback tone path.
         * @remark
         *  - The default value of ringback tone path is L"./wav_files/ringback_48k.wav".
         */
        virtual const wchar_t* GetRingBackTonePath() = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use const wchar_t* GetHoldTonePath()")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see const wchar_t* GetHoldTonePath()
         */
        const char* HoldTonePath();

        /**
         * Gets the hold tone path.
         * @remark
         *  - The default value of hold tone path is L"./wav_files/hold_48k.wav".
         */
        virtual const wchar_t* GetHoldTonePath() = 0;

        /**
         * Gets the end tone path.
         * @remark
         *  - The default value of end tone path is L"./wav_files/end_48k.wav".
         */
        virtual const wchar_t* GetEndTonePath() = 0;

        virtual ICallEvent* CallEvent() = 0;

        /**
         * Gets the flag value of 'ResponseOnVideoEnable'.
         * @see EResponseOnVideoEnable
         */        
        virtual EResponseOnVideoEnable ResponseOnVideoEnable() = 0;

        /**
         * Gets the video receiving capability.
         */        
        virtual const SVideoCapability& RecvVideoCapability() = 0;

        /// Gets whether to allow making a 1-to-1 call even when PlanetKit can't start microphone.
        virtual bool IsAllowCallWithoutMic() = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use GetPeer()->SetId(const char* lpszUserId)")
        /**
         * @deprecated This will not be supported in 4.4 or later.
         * @see InitUserId
         */
        void SetPeerUserId(const char* szPeerUserId);

        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use GetPeer()->SetServiceId(const char* lpszServiceId)")
        /**
         * @deprecated This will not be supported in 4.4 or later.
         * @see InitUserId
         */
        void SetPeerServiceId(const char* szPeerServiceId);

        /// Sets whether to allow making a 1-to-1 call even when PlanetKit can't start microphone.
        virtual void SetAllowCallWithoutMic(bool bAllowCallWithoutMic) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use void SetRingTonePath(const wchar_t* szRingTonePath)")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see void SetRingTonePath(const wchar_t* szRingTonePath)
         */
        void SetRingTonePath(const char* szRingTonePath);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use void SetRingBackTonePath(const wchar_t* szRingBackTonePath)")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see void SetRingBackTonePath(const wchar_t* szRingBackTonePath)
         */
        void SetRingBackTonePath(const char* szRingBackTonePath);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use void SetHoldTonePath(const wchar_t* szHoldTonePath)")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see void SetHoldTonePath(const wchar_t* szHoldTonePath)
         */
        void SetHoldTonePath(const char* szHoldTonePath);
        
        /**
         * Sets the ring tone path.
         * @remark
         *  - The default value of ring tone path is L"./wav_files/ring_48k.wav".
         */
        virtual void SetRingTonePath(const wchar_t* szRingTonePath) = 0;

        /**
         * Sets the ringback tone path.
         * @remark
         *  - The default value of ringback tone path is L"./wav_files/ringback_48k.wav".
         */
        virtual void SetRingBackTonePath(const wchar_t* szRingBackTonePath) = 0;

        /**
         * Sets the hold tone path.
         * @remark
         *  - The default value of hold tone path is L"./wav_files/hold_48k.wav".
         */
        virtual void SetHoldTonePath(const wchar_t* szHoldTonePath) = 0;

        /**
         * Sets the end tone path.
         * @remark
         *  - The default value of end tone path is L"./wav_files/end_48k.wav".
         */
        virtual void SetEndTonePath(const wchar_t* szEndTonePath) = 0;
        
        /**
         * Sets the ICallEvent listener class.
         */
        virtual void SetCallEvent(ICallEvent* pEvent) = 0;

        /**
         * Sets the flag value of 'ResponseOnVideoEnable'.
         * @see EResponseOnVideoEnable
         */
        virtual void SetResponseOnVideoEnable(EResponseOnVideoEnable eEnable) = 0;

        /**
         * Sets the video receiving capability.
         */
        virtual void SetRecvVideoCapability(const SVideoCapability& sCapa) = 0;
       
        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use GetCCParam()")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see GetCCParam
        */
        const char* CCParam();
    public:
        virtual int ToString(char* szBuff, int nSize) = 0;

    protected:
        CallParam() {}
        virtual ~CallParam() {}
    };
}
