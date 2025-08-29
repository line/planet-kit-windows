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
#include "PlanetKitDataSessionInterface.h"
#include "PlanetKitVideoStatus.h"

#include "PlanetKitCommonVideoStatus.h"

#include "PlanetKitShortDataParam.h"
#include "PlanetKitRecordOnCloud.h"
#include "PlanetKitCallStartMessage.h"

#include "PlanetKitCallConnectedParam.h"
#include "PlanetKitCallVerifiedParam.h"
#include "PlanetKitCallDisconnectedParam.h"

namespace PlanetKit {
    class PLANETKIT_API PlanetKitCall;
    using PlanetKitCallPtr = AutoPtr<PlanetKitCall>;

    /// @brief Event callback APIs for 1-to-1 calls
    /**
     * PlanetKit calls these APIs of ICallEvent when some events occur.
     */
    class PLANETKIT_API ICallEvent {
    public:
        virtual ~ICallEvent() { }

        /**
         * Called when the call state is changed to connected.
         * @param pPlanetKitCall Call instance that the event was registered to.
         * @param pConnectedParam Information about this call.
         */
        virtual void OnConnected(PlanetKitCallPtr pPlanetKitCall, CallConnectedParamPtr pConnectedParam) = 0;

        /**
         * Called when the call state is changed to wait answer.
         * @param pPlanetKitCall Call instance that the event was registered to.
         */
        virtual void OnWaitAnswer(PlanetKitCallPtr pPlanetKitCall) = 0;

        /**
         * Called when the call state is changed to verified.
         * @param pPlanetKitCall Call instance that the event was registered to.
         * @param pVerifiedParam Information about this call.
         */
        virtual void OnVerified(PlanetKitCallPtr pPlanetKitCall, CallVerifiedParamPtr pVerifiedParam) = 0;

        /**
         * Called when the preparation is finished.
         * @param pPlanetKitCall Call instance that the event was registered to.
         */
        virtual void OnPreparationFinished(PlanetKitCallPtr pPlanetKitCall) = 0;

        /**
         * Called when the call state is changed to disconnected.
         * @param pPlanetKitCall Call instance that the event was registered to.
         * @param pDisconnectedParam Information parameter
         */
        virtual void OnDisconnected(PlanetKitCallPtr pPlanetKitCall, CallDisconnectedParamPtr pDisconnectedParam) = 0;

        /**
         * Called when the peer's video is paused.
         * @param pPlanetKitCall PlanetKitCall object
         * @param eVideoPauseReason Paused reason
         */
        virtual void OnPeerVideoPaused(PlanetKitCallPtr pPlanetKitCall, EVideoPauseReason eVideoPauseReason) = 0;

        /**
         * Called when the peer's video is resumed.
         * @param pPlanetKitCall PlanetKitCall object
         */
        virtual void OnPeerVideoResumed(PlanetKitCallPtr pPlanetKitCall) = 0;

        /**
         * Called when short data is received.
         * @param pPlanetKitCall Call instance that the event was registered to.
         * @param pShortDataParam
         */
        virtual void OnReceivedShortData(PlanetKitCallPtr pPlanetKitCall, ShortDataParamPtr pShortDataParam) = 0;

        /**
         * Called when video is enabled by the peer.
         * @param pPlanetKitCall Call instance that the event was registered to.
         */
        virtual void OnVideoEnabledByPeerAndMyVideoPaused(PlanetKitCallPtr pPlanetKitCall) = 0;

        /**
         * Called when video is disabled by the peer.
         * @param pPlanetKitCall Call instance that the event was registered to.
         */
        virtual void OnVideoDisabledByPeer(PlanetKitCallPtr pPlanetKitCall, const EMediaDisabledReason eReason) = 0;

        /**
         * Called when the peer calls Hold().
         * @param pPlanetKitCall Call instance that the event was registered to.
         */
        virtual void OnReceivedPeerHold(PlanetKitCallPtr pPlanetKitCall, const WString& strHoldReason) = 0;

        /**
         * Called when the peer calls Unhold().
         * @param pPlanetKitCall Call instance that the event was registered to.
         */
        virtual void OnReceivedPeerUnhold(PlanetKitCallPtr pPlanetKitCall) = 0;

        /**
         * Called when a network is unavailable.
         * @param pPlanetKitCall Call instance that the event was registered to.
         * @param bIsPeer If true, the peer's is unavailable. Otherwise, the local user's network is unavailable.
         * @param nDisconnectAfterSec Seconds left until the call is disconnected. If the network becomes available again before nDisconnectAfterSec, the call will not be disconnected.
         */
        virtual void OnNetworkUnavailable(PlanetKitCallPtr pPlanetKitCall, bool bIsPeer, int nDisconnectAfterSec) = 0;

        /**
         * Called when a network is available again.
         * @param pPlanetKitCall Call instance that the event was registered to.
         * @param bIsPeer If true, the peer's network is available again. Otherwise, the local user's network is available again.
         */
        virtual void OnNetworkReavailable(PlanetKitCallPtr pPlanetKitCall, bool bIsPeer) = 0;

        /**
         * Called when the peer has changed their microphone status to be muted.
         * @param pPlanetKitCall Call instance that the event was registered to.
         */
        virtual void OnPeerMicMuted(PlanetKitCallPtr pPlanetKitCall) = 0;

        /**
         * Called when the peer has changed their microphone status to be unmuted.
         * @param pPlanetKitCall Call instance that the event was registered to.
         */
        virtual void OnPeerMicUnmuted(PlanetKitCallPtr pPlanetKitCall) = 0;

        /**
         * Called when an audio mute request is received from the peer.
         * @param pPlanetKitCall Call instance that the event was registered to.
         * @param bEnableMute
         */
        virtual void OnReceivedMuteMyAudioRequest(PlanetKitCallPtr pPlanetKitCall, bool bEnableMute) = 0;

        /**
         * Called when the peer starts screen share.
         * @param pPlanetKitCall Call instance that the event was registered to.
         */
        virtual void OnPeerStartedScreenShare(PlanetKitCallPtr pPlanetKitCall) = 0;

        /**
         * Called when the peer stops screen share.
         * @param pPlanetKitCall Call instance that the event was registered to.
         * @param bHasReason If true, the peer stopped screen share with a user reason.
         * @param nUserReason Reason for the peer's stopping screen share. Valid if bHasReason is true.
         */
        virtual void OnPeerStoppedScreenShare(PlanetKitCallPtr pPlanetKitCall, bool bHasReason, int nUserReason) = 0;

        /**
         * Called when the peer sends data through a data session.
         * @param nStreamId Data session ID
         * @param eType Data session type
         */
        virtual void OnDataSessionIncoming(DataSessionStreamIdT nStreamId, EDataSessionType eType) = 0;

        /**
         * Called when there is no video source for a certain period of time.
         * @param pPlanetKitCall 1-to-1 call instance
         */
        virtual void OnMyVideoNoSource(PlanetKitCallPtr pPlanetKitCall) = 0;

        /**
         * Called when a peer volume value is received for each interval that was registered at the time of initializing the call.
         * @param pPlanetKitCall 1-to-1 call instance
         * @param ucAverageVolumeLevel Volume[0:100]
         * @remark If the interval is 0, it does not occur.
         */
        virtual void OnPeerAudioDescriptionUpdated(PlanetKitCallPtr pPlanetKitCall, unsigned char ucAverageVolumeLevel) = 0;

        /**
         * Called when the local user's volume value is received for each interval that was registered at the time of initializing the call.
         * @param pPlanetKitCall 1-to-1 call instance
         * @param ucAverageVolumeLevel Volume[0:100]
         * @remark If the interval is 0, it does not occur.
         */
        virtual void OnMyAudioDescriptionUpdated(PlanetKitCallPtr pPlanetKitCall, unsigned char ucAverageVolumeLevel) = 0;

        /**
         * Called when the local user holds the call during screen share.
         */
        virtual void OnMyScreenShareStoppedByHold(PlanetKitCallPtr pPlanetKitCall) = 0;

        /**
         * Called when there is an event related to recording on the cloud.
         * @param pPlanetKitCall 1-to-1 call instance
         * @param pRecordOnCloud Instance of RecordOnCloud
         */
        virtual void OnRecordOnCloudUpdated(PlanetKitCallPtr pPlanetKitCall, RecordOnCloudPtr pRecordOnCloud) = 0;
    };

    using ICallEventPtr = SharedPtr<ICallEvent>;
}
