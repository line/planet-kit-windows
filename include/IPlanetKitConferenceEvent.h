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
#include "PlanetKitCommonVideoStatus.h"
#include "PlanetKitCallEventParam.h"
#include "PlanetKitAudioCommon.h"
#include "PlanetKitDataSessionInterface.h"

#include "PlanetKitPeer.h"
#include "PlanetKitPeerHold.h"
#include "PlanetKitVideoStatus.h"

namespace PlanetKit
{
    class PLANETKIT_API PlanetKitConference;

    //template class PLANETKIT_API AutoPtr<PlanetKitConference>;
    typedef AutoPtr<PlanetKitConference> PlanetKitConferencePtr;


    /// Updated information of peers list who are connected to or disconnected from a subgroup.
    class PLANETKIT_API ConferencePeerUpdateParam : public Base {
    public :
        /// Gets the conference subgroup instance.
        virtual SubgroupPtr GetSubgroup() = 0;

        /// Gets the array of added peers.
        virtual const PeerArray& GetAddedPeer() = 0;
        /// Gets the array of removed peers.
        virtual const PeerArray& GetRemovedPeer() = 0;

        /// Gets the total peers count.
        virtual size_t TotalCount() = 0;
    };

    /// Video update parameter
    class PLANETKIT_API ConferenceVideoUpdatedParam : public Base {
    public:
        /// Gets the VideoStatus array.
        virtual const PeerVideoStatusArray& GetPeerVideoStatus() = 0;

        /// Gets the Subgroup.
        virtual SubgroupPtr GetSubgroup() = 0;
        
    };

    /**
     * Updated information of peers
     */
    class PLANETKIT_API ConferenceSubgroupUpdatePeer : public Base
    {
    public :
        /// Gets the peer object class.
        virtual PeerPtr GetPeer() const = 0;

        /// Gets the subscribed subgroup name array.
        virtual const WStringArray& GetSubscribedSubgroupNames() const = 0;

        /// Gets the unsubscribed subgroup name array.
        virtual const WStringArray& GetUnsubscribedSubgroup() const = 0;
    };

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

    template class PLANETKIT_API AutoPtr<ConferenceConnectedParam>;
    typedef AutoPtr<ConferenceConnectedParam> ConferenceConnectedParamPtr;

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

    template class PLANETKIT_API AutoPtr<ConferenceDisconnectedParam>;
    typedef AutoPtr<ConferenceDisconnectedParam> ConferenceDisconnectedParamPtr;

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

    /**
     * PlanetKit calls these APIs of IConferenceEvent when some events occur.
     */
    class PLANETKIT_API IConferenceEvent {
    public:
        /**
         * Called when the conference state is changed to connected.
         * @param pPlanetKitConference Conference instance that the event was registered to.
         * @param pConnectedParam Information about this conference call.
         */
        virtual void OnConnected(PlanetKitConferencePtr pPlanetKitConference, ConferenceConnectedParamPtr pParam) = 0;

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
         * Called when a network is unavailable.<br>If a network is not recovered within nWillDisconnectAfterSec seconds, this session will be disconnected with PLNK_DISCONNECT_REASON_UNAVAILABLE_NETWORK.
         * @param pPlanetKitConference Conference instance that the event was registered to.
         * @param nWillDisconnectAfterSec Seconds left until the session is disconnected. If a network becomes available before nWillDisconnectAfterSec seconds, the session will not be disconnected.
         */
        virtual void OnNetworkUnavailable(PlanetKitConferencePtr pPlanetKitConference, int nWillDisconnectAfterSec) = 0;
        
        /**
         * Called when a network is available again.
         * @param pPlanetKitConference Conference instance that the event was registered to.
         */
        virtual void OnNetworkReavailable(PlanetKitConferencePtr pPlanetKitConference) = 0;
        
        /**
         * Called when a peer sends a data through an inbound data session.
         * @param strSubgroupName Subgroup name string which is encoded in UTF-16 and null-terminated.<br>This can be `NullOptional` that means `MainRoom`.
         * @param nStreamId Data session ID
         * @param eType Data session type
         */
        virtual void OnDataSessionIncoming(const WStringOptional& strSubgroupName, DataSessionStreamIdT nStreamId, EDataSessionType eType) = 0;

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
         * @param sMyAudioDescription The local user's audio description.
         * @remark If the interval is 0, it does not occur.
         */
        virtual void OnMyAudioDescriptionUpdated(PlanetKitConferencePtr pPlanetKitConference, const MyAudioDescription& sMyAudioDescription) = 0;

        /**
        * Called when the local user holds during screen share.
        * @param pPlanetKitConference Conference instance that the event was registered to.
        */
        virtual void OnMyScreenShareStoppedByHold(PlanetKitConferencePtr pPlanetKitConference) = 0;
    };
}
