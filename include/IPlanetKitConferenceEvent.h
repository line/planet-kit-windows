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
#include "PlanetKitTypes.h"
#include "PlanetKitDataSessionInterface.h"
#include "PlanetKitConferencePeerInfo.h"
#include "PlanetKitPeerInfo.h"
#include "PlanetKitCommonVideoStatus.h"
#include "PlanetKitVideoStatus.h"
#include "PlanetKitPeerHold.h"
#include "PlanetKitPeer.h"
#include "PlanetKitCallEventParam.h"

namespace PlanetKit
{
    class PLANETKIT_API PlanetKitConference;
    typedef AutoPtr<PlanetKitConference> PlanetKitConferencePtr;

    /* Forward declaration */
    PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use class ConferencePeerUpdateParam")
    /**
     * @deprecated This will not be supported in 4.4 or later.
     * @see ConferencePeerUpdateParam
     */
    typedef struct SConferencePeerUpdateParam
    {
    } SConferencePeerUpdateParam;

    /// Updated information of peers list who are connected to or disconnected from a subgroup.
    class PLANETKIT_API ConferencePeerUpdateParam : public Base
    {
    public :
        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use const PeerArray& GetAddedPeer()")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         * @see GetAddedPeer
         */
        ConferencePeer* AddedAt(size_t index);

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. PeerArray& GetRemovedPeer()")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         * @see GetRemovedPeer
         */
        ConferencePeer* RemovedAt(size_t index);

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use const PeerArray& GetAddedPeer()")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         * @see GetAddedPeer
         */
        size_t AddedCount();
        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. PeerArray& GetRemovedPeer()")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         * @see GetRemovedPeer
         */
        size_t RemovedCount();

        /// Gets the conference subgroup instance.
        virtual SubgroupPtr GetSubgroup() = 0;

        /// Gets the array of added peers.
        virtual const PeerArray& GetAddedPeer() = 0;
        /// Gets the array of removed peers.
        virtual const PeerArray& GetRemovedPeer() = 0;

        /// Gets the total peers count.
        virtual size_t TotalCount() = 0;

    protected :
        virtual ~ConferencePeerUpdateParam() = default;
    };

    PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use class PeerVideoStatuses")
    /**
     * @deprecated This will not be supported in 4.4 or later.
     * @see PeerVideoStatuses
     */
    typedef struct SConferenceVideoUpdateParam
    {
        /// Call AddRef if you wish to keep using the reference after the update event
        Subgroup *pSubgroup;

        /// Array of SubgroupPeerInfo* with size nActivatedCnt
        SubgroupPeerInfo **ppVideoActivated;
        /// Array count of ppVideoActivated
        size_t nActivatedCnt;

        /// Array of SubgroupPeerInfo* with size nInactivatedCnt
        SubgroupPeerInfo **ppVideoInactivated; 
        /// Array count of nInactivatedCnt
        size_t nInactivatedCnt;
    } SConferenceVideoUpdateParam;
    

    /// Video update parameter
    class PLANETKIT_API ConferenceVideoUpdatedParam : public Base
    {
    public:
        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use const PeerVideoStatusArray& GetPeerVideoStatus()")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         * @see GetPeerVideoStatus
         */
        size_t GetCount();
        
        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use const PeerVideoStatusArray& GetPeerVideoStatus()")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         * @see GetPeerVideoStatus
         */
        PeerVideoStatus* At(size_t nIdx);

        /// Gets the VideoStatus array.
        virtual const PeerVideoStatusArray& GetPeerVideoStatus() = 0;

        /// Gets the Subgroup.
        virtual SubgroupPtr GetSubgroup() = 0;
        
    };

    PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use class ConferenceSubgroupUpdatePeer")
    /**
     * @deprecated This will not be supported in 4.4 or later.
     * @see ConferenceSubgroupUpdatePeer
     */
    typedef struct SConferenceSubgroupPeerUpdate
    {
        /// SubgroupPeerInfo of Updated
        SubgroupPeerInfo* pPeerInfo;

        /// Newly subscribed subgroup names (array)
        char** pSubscribed;
        /// subscribed count
        size_t nSubscribedCount;

        /// Unsubscribed subgroup names since last event (array)
        char** pUnsubscribed;
        /// unsubscribe count
        size_t nUnsubscribedCount;
    } SConferenceSubgroupPeerUpdate;

    PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use class ConferenceSubgroupUpdateParam")
    /**
     * @deprecated This will not be supported in 4.4 or later.
     * @see ConferenceSubgroupUpdateParam
     */
    typedef struct SConferenceSubgroupUpdateParam
    {
        /// Updated Peer (array)
        SConferenceSubgroupPeerUpdate* pUpdatedPeer;
        /// updated peers count
        size_t nUpdatedPeerCount;
    } SConferenceSubgroupUpdateParam;

    /**
     * Updated information of peers
     */
    class PLANETKIT_API ConferenceSubgroupUpdatePeer : public Base
    {
    public :

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        */
        ConferencePeerInfo* GetPeerInfo() const;

        /// Gets the peer object class.
        virtual PeerPtr GetPeer() const = 0;

        /// Gets the subscribed subgroup name array.
        virtual const WStringArray& GetSubscribedSubgroupNames() const = 0;

        /// Gets the unsubscribed subgroup name array.
        virtual const WStringArray& GetUnsubscribedSubgroup() const = 0;
    };

    PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
    /**
    * @deprecated This will not be supported in 5.0 or later.
    */
    class PLANETKIT_API ConferenceSubgroupUpdateParam
    {
    public :

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use GetConferenceSubgroupUpdatePeerArray()")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see GetConferenceSubgroupUpdatePeerArray()
        */
        const ConferenceSubgroupUpdatePeer* UpdatePeerAt(size_t index);

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use GetConferenceSubgroupUpdatePeerArray().Size()")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see GetConferenceSubgroupUpdatePeerArray().Size()
        */
        size_t UpdatePeerCount();
    };

    PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use ConferenceConnectedParam")
    /**
     * @deprecated This will not be supported in 5.2 or later.
     * @see ConferenceConnectedParam
     */
    typedef struct SConferenceConnectedParam
    {
        /// Send video using hardware codec
        bool                        bVideoSendHWCodecEnabled;
    } SConferenceConnectedParam;

    /**
     * Parameter used in IConferenceEvent::OnConnected.
     */
    class PLANETKIT_API ConferenceConnectedParam : virtual public Base {
    public :
        /**
         * Returns whether the sending video feature is using a hardware codec.
         */
        virtual bool IsVideoSendHardwareCodecEnabled() = 0;

        /**
         * Returns whether the screen share feature can support video share mode.
         * @see
         *  - PlanetKitConference::SetMyScreenShareVideoShareMode<br>
         *  - PlanetKitConference::IsMyScreenShareVideoShareModeEnabled
         */
        virtual bool IsSupportVideoShareMode() = 0;
    };

    typedef AutoPtr<ConferenceConnectedParam> ConferenceConnectedParamPtr;

    PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
    /**
     * @deprecated This will not be supported in 5.2 or later.
     */
    typedef struct SConferenceDisconnectedParam
    {
        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        */
        const char *                szUserRelCode;

        bool                        bByRemote;

        /// Disconnected relaser
        EDisconnectSource           eDisconnectSource;
        /// Reason of disconnection
        EDisconnectReason           eEndReason;
        /// String reason value of disconnection
        String                      strUserRelCode;
    } SConferenceDisconnectedParam;

    /**
     * Parameter used in IConferenceEvent::OnDisconnected.
     */
    class PLANETKIT_API ConferenceDisconnectedParam : virtual public Base {
    public :
        /**
         * Returns whether this call has been disconnected by the remote subject.
         */
        virtual bool IsDisconnectedByRemote() = 0;

        /**
         * Gets the reason for disconnection.
         */
        virtual EDisconnectReason GetReason() = 0;

        /**
         * Gets the subject who performed the disconnection.
         */
        virtual EDisconnectSource GetDisconnectSource() = 0;

        /**
         * Gets the reason string that is encoded in UTF-16 and null-terminated.
         * @remark
         *  - The return value can be nullptr.
         */
        virtual const WString& GetUserReleaseCode() = 0;
    };

    typedef AutoPtr<ConferenceDisconnectedParam> ConferenceDisconnectedParamPtr;

    PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use class ConferenceExceptionMessage")
    /**
     * @deprecated This will not be supported in 4.4 or later.
     * @see ConferenceExceptionMessage
     */
    typedef struct SConferenceExceptionMessage
    {
    } SConferenceExceptionMessage;

    /**
     * Exception message information class.
     * @see ConferenceExceptionMessage
     * @see OnException
     */
    class PLANETKIT_API ConferenceException : public Base {
    public :
        /// Gets the peer information class.
        virtual PeerPtr GetPeer() = 0;
        /// Gets the subgroup information class.
        virtual SubgroupPtr GetSubgroup() = 0;
        /// Gets the exception type information.
        virtual EConferenceExceptionType GetExceptionType() = 0;
        /// Gets the exception message as a string that can be nullptr.
        virtual const WString& GetMessage() = 0;

    protected :
        virtual ~ConferenceException() = default;
    };

    PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
    /**
     * @deprecated This will not be supported in 5.0 or later.
     */
    class PLANETKIT_API ConferenceExceptionMessage
    {
    public :
        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        */
        ConferenceException* ExceptionAt(size_t index);
        
        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        */
        size_t ExceptionCount();

    protected :
        virtual ~ConferenceExceptionMessage() = default;
    };

    PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use class ConferencePeerScreenSharingUpdatedParam")
    /**
     * @deprecated This will not be supported in 4.4 or later.
     * @see ConferencePeerScreenSharingUpdatedParam
     */
    typedef struct SConferencePeerScreenSharingUpdateInfo
    {
    }SConferencePeerScreenSharingUpdateInfo;

    PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use class ConferencePeerScreenSharingUpdatedParam")
    /**
    * @deprecated This will not be supported in 5.0 or later.
    * @see ConferencePeerScreenSharingUpdatedParam
    */
    typedef struct ConferencePeerScreenSharingUpdateInfo
    {

    }ConferencePeerScreenSharingUpdateInfo;

    /**
     * Parameter used for updates of peer's screen share information.
     */
    class PLANETKIT_API ConferencePeerScreenShareUpdatedParam
    {
    public :
        /// Gets the peer's information object.
        virtual PeerPtr GetPeer() = 0;
        
        /// Gets the subgroup information object.
        virtual SubgroupPtr GetSubgroup() = 0;

        /// Gets the screen share state.
        virtual EScreenShareState ScreenShareState() = 0;
    };

    /// @brief Event callback APIs for conference calls
    /**
     * PlanetKit calls these APIs of IConferenceEvent when some events occur.
     */
    class PLANETKIT_API IConferenceEvent
    {
    public:

        PLANETKIT_DEPRECATED("This will not be supported in 4.3 or later. Use OnPeerListUpdate")
        /**
         * @deprecated This will not be supported in 4.3 or later.
         * @see OnPeerListUpdate
         */
        void OnPeerUpdate(PlanetKitConference* pPlanetKitConference, const SConferencePeerUpdateParam* pParam);

        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use OnPeerListUpdate(PlanetKitConference *pPlanetKitConference, const ConferencePeerUpdateParam* pParam)")
        /**
         * @deprecated This will not be supported in 4.4 or later.
         * @see OnPeerListUpdate
         */
        void OnPeerListUpdate(PlanetKitConference* pPlanetKitConference, const SConferencePeerUpdateParam* pParam);


        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use OnPeersVideoUpdated(PlanetKitConference *pPlanetKitConference, ConferenceVideoUpdatedParam *pParam)")
        /**
         * @deprecated This will not be supported in 4.4 or later.
         * @see OnPeersVideoUpdated
         */
        void OnPeerVideoUpdate(PlanetKitConference* pPlanetKitConference, const SConferenceVideoUpdateParam* pParam);


        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use OnPublicSubgroupUpdated(PlanetKitConference *pPlanetKitConference, const ConferenceSubgroupUpdateParam *pParam)")
        /**
         * @deprecated This will not be supported in 4.4 or later.
         * @see OnPublicSubgroupUpdated
         */
        void OnPublicSubgroupPeerUpdate(PlanetKitConference* pPlanetKitConference, const SConferenceSubgroupUpdateParam* pParam);


        PLANETKIT_DEPRECATED("This will not be supported in 4.3 or later. Use OnPeersVideoPaused/Resumed")
        /**
         * @deprecated This will not be supported in 4.3 or later.
         * @see OnPeersVideoPaused
         * @see OnPeersVideoResumed
         */
        void OnPeerUpdate(PlanetKitConference* pPlanetKitConference, const SPeerUpdatedParam* pParam);


        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later.")
        /**
         * @deprecated This will not be supported in 4.4 or later.
         */
        void OnPeersVideoPaused(PlanetKitConference* pPlanetKitConference, CommonVideoStatuses* pParam);

        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later.")
        /**
         * @deprecated This will not be supported in 4.4 or later.
         */
        void OnPeersVideoResumed(PlanetKitConference* pPlanetKitConference, CommonVideoStatuses* pParam);

        PLANETKIT_DEPRECATED("This will not be supported in 4.3 or later. Use OnReceivedPeersHold(PlanetKitConference *pPlanetKitConference, CommonReceivedHoldPeersHoldParam * pPram)")
        /**
         * @deprecated This will not be supported in 4.3 or later. 
         * @see OnReceivedPeersHold
         */
        void OnPeerHold(PlanetKitConference* pPlanetKitConference, const char* szHoldReason);


        PLANETKIT_DEPRECATED("This will not be supported in 4.3 or later. Use OnPeerMicMuted/Unmuted")
        /**
         * @deprecated This will not be supported in 4.3 or later.
         * @see OnPeersMicMuted
         * @see OnPeersMicUnmuted
         */
         void OnPeerMicStatusShared(PlanetKitConference* pPlanetKitConference, SPeer* pParam, bool bMuted);


        PLANETKIT_DEPRECATED("This will not be supported in 4.3 or later. Use OnReceivedMyAudioMuteRequest(PlanetKitConference *pPlanetKitConference, PeerInfo* pParam, bool bEnableMute)")
        /**
         * @deprecated This will not be supported in 4.3 or later.
         * @see OnReceivedMyAudioMuteRequest
         */
        void OnMuteRequest(PlanetKitConference* pPlanetKitConference, SPeer* pParam, bool bEnableMute);


        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use OnPeerScreenSharingUpdated(ConferencePeerScreenSharingUpdatedParam* pPeerScreenSharingUpdateInfo)")
        /**
         * @deprecated This will not be supported in 4.4 or later.
         * @see OnPeerScreenSharingUpdated
         */
        void OnPeerScreenSharingUpdateInfo(SConferencePeerScreenSharingUpdateInfo* pPeerScreenSharingUpdateInfo);


        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use OnException(PlanetKitConference *pPlanetKitConference, const ConferenceExceptionMessage* pExceptionMessage)")
        /**
         * @deprecated This will not be supported in 4.4 or later.
         * @see OnException
         */
        void OnConferenceException(PlanetKitConference *pPlanetKitConference, SConferenceExceptionMessage* pExceptionMessage, int nExceptionCount);


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         */
        void OnConferenceConnect(PlanetKitConference *pPlanetKitConference, SConferenceConnectedParam* pParam);


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         */
        void OnConferenceDisconnect(PlanetKitConference *pPlanetKitConference, const SConferenceDisconnectedParam* pParam);


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         */
        void OnPeerListUpdate(PlanetKitConference *pPlanetKitConference, ConferencePeerUpdateParam* pParam);


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         */
        void OnPeerVideoUpdate(PlanetKitConference *pPlanetKitConference, ConferenceVideoUpdatedParam* pParam);


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         */
        void OnPublicSubgroupPeerUpdate(PlanetKitConference *pPlanetKitConference, const ConferenceSubgroupUpdateParam* pParam);

        
        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         */
        void OnShortDataReceived(PlanetKitConference *pPlanetKitConference, const SShortDataParam* pParam);


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         */
        void OnPeersHold(PlanetKitConference *pPlanetKitConference, CommonReceivedHolds* pParam);


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         */
        void OnPeersUnhold(PlanetKitConference *pPlanetKitConference);


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         */
        void OnPeersMicMuted(PlanetKitConference *pPlanetKitConference, PeerInfos* pPeerInfos);


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         */
        void OnPeersMicUnmuted(PlanetKitConference *pPlanetKitConference, PeerInfos* pPeerInfos);


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         */
        void OnMuteRequest(PlanetKitConference *pPlanetKitConference, PeerInfo* pParam, bool bEnableMute);


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         */
        void OnReceiveAppControlMessage(PlanetKitConference *pPlanetKitConference, const void* pMessage, int nMessageSize);


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         */
        void OnBadNetworkDetected(PlanetKitConference *pPlanetKitConference, int nWillDisconnectAfterSec);

        
        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         */
        void OnBadNetworkResolved(PlanetKitConference *pPlanetKitConference);


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         */
        void OnConferenceException(PlanetKitConference *pPlanetKitConference, ConferenceExceptionMessage* pExceptionMessage);


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         */
        void OnDataSessionIncoming(const char* szSubgroupName, DataSessionStreamIdT nStreamId, EDataSessionType eType);


        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later. Use OnConnected")
        /**
         * @deprecated This will not be supported in 5.1 or later.
         * @see OnConnected
         */
        void OnConferenceConnected(PlanetKitConferencePtr pPlanetKitConference, SConferenceConnectedParam* pParam);

        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later. Use OnDisconnected")
        /**
         * @deprecated This will not be supported in 5.1 or later.
         * @see OnDisconnected
         */
        void OnConferenceDisconnected(PlanetKitConferencePtr pPlanetKitConference, const SConferenceDisconnectedParam* pParam);


        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later. Use OnReceivedPeersUnhold")
        /**
         * @deprecated This will not be supported in 5.1 or later.
         * @see OnReceivedPeersUnhold
         */
        void OnPeersUnhold(PlanetKitConferencePtr pPlanetKitConference, const PeerArray& arrPeer);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         */
        void OnConnected(PlanetKitConferencePtr pPlanetKitConference, SConferenceConnectedParam* pParam);

        /**
        * Called when the conference state is changed to connected.
        * @param pPlanetKitConference Conference instance that the event was registered to.
        * @param pConnectedParam Information about this conference call.
        */
        virtual void OnConnected(PlanetKitConferencePtr pPlanetKitConference, ConferenceConnectedParamPtr pParam) = 0;
        
        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         */
        void OnDisconnected(PlanetKitConferencePtr pPlanetKitConference, const SConferenceDisconnectedParam* pParam);

        /**
         * Called when the conference state is changed to disconnected.
         * @param pPlanetKitConference Conference instance that the event was registered to.
         * @param pDisconnectedParam Information parameter
         */
        virtual void OnDisconnected(PlanetKitConferencePtr pPlanetKitConference, ConferenceDisconnectedParamPtr pParam) = 0;


        /**
        * Called when the list of peers who are connected to or disconnected from the conference is updated.
        * @param pPlanetKitConference Conference instance that the event was registered to.
        * @param pParam List of peers who are connected to or disconnected from the conference subgroup.
        */
        virtual void OnPeerListUpdate(PlanetKitConferencePtr pPlanetKitConference, ConferencePeerUpdateParamPtr pParam) = 0;


        /**
         * Called when the video state of one or more conference subgroup peers is updated.
         * @param pPlanetKitConference Conference instance that the event was registered to.
         * @param pParam Updated information of the peers' video.
         */
        virtual void OnPeersVideoUpdated(PlanetKitConferencePtr pPlanetKitConference, ConferenceVideoUpdatedParam* pParam) = 0;

        /**
         * Called when the state of one or more conference public subgroup peers is updated.
         * @param pPlanetKitConference Conference instance that the event was registered to.
         * @param pParam Updated information of the peers
         */
        virtual void OnPublicSubgroupUpdated(PlanetKitConferencePtr pPlanetKitConference, const ConferenceSubgroupUpdatePeerArray& arrSubgroupUpdatePeer) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         */
        void OnReceivedShortData(PlanetKitConferencePtr pPlanetKitConference, const SShortDataParam* pParam);

        /**
         * Called when short data is received.
         * @param pPlanetKitConference Conference instance that the event was registered to.
         * @param pParam Parameter for the short data
         */
        virtual void OnReceivedShortData(PlanetKitConferencePtr pPlanetKitConference, ShortDataParamPtr pParam) = 0;


        /**
        * Called when Hold() is called by a peer.
        * @param pPlanetKitConference Conference instance that the event was registered to.
        * @param arrPeerHold Parameter for the hold
        */
        virtual void OnReceivedPeersHold(PlanetKitConferencePtr pPlanetKitConference, const PeerHoldArray& arrPeerHold) = 0;


        /**
        * Called when Unhold() is called by a peer.
        * @param pPlanetKitConference Call instance that the event was registered to.
        */
        virtual void OnReceivedPeersUnhold(PlanetKitConferencePtr pPlanetKitConference, const PeerArray& arrPeer) = 0;


        /**
        * Called when peers' microphone status sharing (mute) has been shared.
        * @param pPlanetKitConference Conference instance that the event was registered to.
        * @param peerArray Information of peers who shared their mic status.
        */
        virtual void OnPeersMicMuted(PlanetKitConferencePtr pPlanetKitConference, const PeerArray& peerArray) = 0;

        /**
        * Called when peers' microphone status sharing (unmute) has been shared.
        * @param pPlanetKitConference Conference instance that the event was registered to.
        * @param peerArray Information of peers who shared their mic status.
        */
        virtual void OnPeersMicUnmuted(PlanetKitConferencePtr pPlanetKitConference, const PeerArray& peerArray) = 0;


        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use OnReceivedMuteMyAudioRequest")
        /**
        * @deprecated This will not be supported in 5.2 or later.
        * @see OnReceivedMuteMyAudioRequest
        */
        void OnReceivedMyAudioMuteRequest(PlanetKitConferencePtr pPlanetKitConference, PeerPtr pPeer, bool bEnableMute);


        /**
        * Called when an audio mute/unmute request is received.
        * @param pPlanetKitConference Conference instance that the event was registered to.
        * @param pPeer Information of the peer who requested mic mute/unmute.
        * @param bEnableMute Whether to mute or unmute audio.
        */
        virtual void OnReceivedMuteMyAudioRequest(PlanetKitConferencePtr pPlanetKitConference, PeerPtr pPeer, bool bEnableMute) = 0;


        /**
        * Called when an app control message is received.
        * @param pPlanetKitConference Conference instance that the event was registered to.
        * @param pMessage App control message
        * @param nMessageSize Size of the app control message
        */
        virtual void OnReceivedAppControlMessage(PlanetKitConferencePtr pPlanetKitConference, const void* pMessage, int nMessageSize) = 0;


        /**
        * Called when a bad network is detected.
        * @param pPlanetKitConference Conference instance that the event was registered to.
        * @param nWillDisconnectAfterSec
        */
        virtual void OnBadNetworkDetected(PlanetKitConferencePtr pPlanetKitConference, int nWillDisconnectAfterSec) = 0;

        
        /**
        * Called when a bad network is resolved.
        * @param pPlanetKitConference Conference instance that the event was registered to.
        */
        virtual void OnBadNetworkResolved(PlanetKitConferencePtr pPlanetKitConference) = 0;

        
        /**
        * Called when a peer sends a data through an inbound data session.
        * @param szSubgroupName Subgroup name
        * @param nStreamId Data session ID
        * @param eType Data session type
        */
        virtual void OnDataSessionIncoming(const WString& strSubgroupName, DataSessionStreamIdT nStreamId, EDataSessionType eType) = 0;
                

        /**
        * Called when a peer starts or stops screen share in a subgroup.
        * @param pPeerScreenShareUpdateInfo Peer information
        */
        virtual void OnPeerScreenShareUpdated(ConferencePeerScreenShareUpdatedParam* pPeerScreenShareUpdateInfo) = 0;

        

        /**
        * Called after some errors have occurred in the conference room.
        * @param pPlanetKitConference Conference instance that the event was registered to.
        * @param arrExceptionMessage Exception messages as an array
        */
        virtual void OnException(PlanetKitConferencePtr pPlanetKitConference, const ConferenceExceptionArray& arrExceptionMessage) = 0;


        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use OnMyVideoNoSource")
        /**
        * @deprecated This will not be supported in 5.2 or later.
        * @see OnMyVideoNoSource
        */
        void OnNoVideoSource(PlanetKitConferencePtr pPlanetKitCall);

        /**
        * Called when there is no video source for a certain period of time.
        * @param pPlanetKitConference Conference instance that the event was registered to.
        */
        virtual void OnMyVideoNoSource(PlanetKitConferencePtr pPlanetKitConference) = 0;

        /**
        * Called at each interval registered during the initialization of the conference, providing peers' volume values.
        * @param pPlanetKitConference Conference instance that the event was registered to.
        * @param ucAverageVolumeLevel Average volume level of all participants [0:100]
        * @param arrPeer Peer audio description array list
        * @remark If the interval is 0, it does not occur.
        * @remark If you want to get a specific peer's volume, call Peer.GetVolumeSetting.
        */
        virtual void OnPeersAudioDescriptionUpdated(PlanetKitConferencePtr pPlanetKitConference, unsigned char ucAverageVolumeLevel, const PeerAudioDescriptionArray& arrPeer) = 0;

        /**
        * Called at each interval registered during the initialization of the conference, providing the local user's volume value.
        * @param pPlanetKitConference Conference instance that the event was registered to.
        * @param peerAudioDescription The local user's audio description
        * @remark If the interval is 0, it does not occur.
        */
        virtual void OnMyAudioDescriptionUpdated(PlanetKitConferencePtr pPlanetKitConference, const PeerAudioDescription& sPeerAudioDescription) = 0;

        /**
        * Called when the local user holds during screen share.
        * @param pPlanetKitConference Conference instance that the event was registered to.
        */
        virtual void OnMyScreenShareStoppedByHold(PlanetKitConferencePtr pPlanetKitConference) = 0;
    };
}
