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
#include "PlanetKitCommonVideoStatus.h"
#include "PlanetKitShortDataParam.h"
#include "PlanetKitAudioCommon.h"
#include "PlanetKitDataSessionInterface.h"

#include "PlanetKitPeerHold.h"
#include "PlanetKitVideoStatus.h"

#include "PlanetKitConferencePeerUpdateParam.h"
#include "PlanetKitConferenceVideoUpdateParam.h"
#include "PlanetKitConferenceSubgroupUpdatePeer.h"
#include "PlanetKitConferenceConnectedParam.h"
#include "PlanetKitConferenceDisconnectedParam.h"
#include "PlanetKitConferenceException.h"
#include "PlanetKitConferencePeerScreenShareUpdatedParam.h"

namespace PlanetKit {
    class PLANETKIT_API PlanetKitConference;
    using PlanetKitConferencePtr = AutoPtr<PlanetKitConference>;

    /**
     * PlanetKit calls these APIs of IConferenceEvent when some events occur.
     */
    class PLANETKIT_API IConferenceEvent {
    public:
        virtual ~IConferenceEvent() { }

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
        virtual void OnPeersVideoUpdated(PlanetKitConferencePtr pPlanetKitConference, ConferenceVideoUpdatedParamPtr pParam) = 0;

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
        virtual void OnPeerScreenShareUpdated(ConferencePeerScreenShareUpdatedParamPtr pPeerScreenShareUpdateInfo) = 0;

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

    using IConferenceEventPtr = SharedPtr<IConferenceEvent>;
}
