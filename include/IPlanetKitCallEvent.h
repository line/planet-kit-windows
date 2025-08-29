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

//"This will not be supported in 4.4 or later. Use PlanetKitVideoStatus.h"
#include "PlanetKitCommonVideoStatus.h"

#include "PlanetKitCallEventParam.h"

#include "PlanetKitCallStartMessage.h"


namespace PlanetKit
{
    /* Forward declaration */
    class PLANETKIT_API PlanetKitCall;

    //template class PLANETKIT_API AutoPtr<PlanetKitCall>;
    typedef AutoPtr<PlanetKitCall> PlanetKitCallPtr;

    /**
     * Parameter used in ICallEvent::OnConnected.
     */
    class PLANETKIT_API CallConnectedParam : public Base {
    public :
        /**
         * Gets the peer's call start message.
         * @see [CallStartMessage guide]( @see https://docs.lineplanet.me/ko/windows/extended-functions/call-start-message )
         */
        virtual CallStartMessagePtr GetPeerStartMessage() = 0;

        /**
         * Returns whether you can delay connection until you call PlanetKitCall::FinishPreparation() API.
         * @see [Preparation guide]( @see https://docs.lineplanet.me/ko/windows/extended-functions/responder-preparation-status )
         */
        virtual bool ShouldFinishPreparation() = 0;

        /** 
         * Returns whether you are in the preparation stage.<br>
         * You must check the return value of ShouldFinishPreparation() and do one of the following:<br>
         * If the return value of ShouldFinishPreparation() is true, you need to call PlanetKitCall::FinishPreparation().<br>
         * If the return value of ShouldFinishPreparation() is false, you must wait until the peer calls PlanetKitCall::FinishPreparation().
         * @see [Preparation guide]( @see https://docs.lineplanet.me/ko/windows/extended-functions/responder-preparation-status ) 
         */
        virtual bool IsInPreparation() = 0;

        /**
         * Returns whether the sending video feature is using hardware codec.
         */
        virtual bool IsVideoSendHardwareCodecEnabled() = 0;

        /**
         * Returns whether this call can support data session or not.
         */
        virtual bool IsSupportDataSession() = 0;

        /**
         * Returns whether the screen share feature can support video share mode.
         * @see
         *  - PlanetKitCall::SetMyScreenShareVideoShareMode<br>
         *  - PlanetKitCall::IsMyScreenShareVideoShareModeEnabled
         */
        virtual bool IsSupportVideoShareMode() = 0;
    };

    template class PLANETKIT_API AutoPtr<CallConnectedParam>;
    typedef AutoPtr<CallConnectedParam> CallConnectedParamPtr;

    /**
     * Parameter used in ICallEvent::OnVerified.
     */
    class PLANETKIT_API CallVerifiedParam : public Base {
    public :
        /**
         * Gets the peer's call start message.
         * @see [CallStartMessage guide]( @see https://docs.lineplanet.me/ko/windows/extended-functions/call-start-message )
         */
        virtual CallStartMessagePtr GetPeerStartMessage() = 0;

        /**
         * Returns whether the peer set the preparation flag.
         * @see [Preparation guide]( @see https://docs.lineplanet.me/ko/windows/extended-functions/responder-preparation-status )
         */
        virtual bool IsPeerUsePreparation() = 0;
    };

    template class PLANETKIT_API AutoPtr<CallVerifiedParam>;
    typedef AutoPtr<CallVerifiedParam> CallVerifiedParamPtr;

    /**
     * Parameter used in ICallEvent::OnDisconnected.
     */
    class PLANETKIT_API CallDisconnectedParam : public Base {
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
         * Subject who performed disconnection.
         */
        virtual EDisconnectSource GetDisconnectSource() = 0;

        /**
         * Gets the reason string that is encoded in UTF-16 and null-terminated.
         * @remark
         *  - The return value can be nullptr.
         */
        virtual const WString& GetUserReleaseCode() = 0;
    };

    template class PLANETKIT_API AutoPtr<CallDisconnectedParam>;
    typedef AutoPtr<CallDisconnectedParam> CallDisconnectedParamPtr;

    /**
     * Reason code for deactivating recording on the cloud.
     */
    enum ERecordOnCloudDeactivateReason {
        /// Internal error. 
        PLNK_RECORD_ON_CLOUD_DEACTIVATE_REASON_INTERNAL = 0,
        /// Recording failed on the cloud.
        PLNK_RECORD_ON_CLOUD_DEACTIVATE_REASON_ACTIVATION_FAILED = 1,
    };

    typedef Optional<ERecordOnCloudDeactivateReason> DeactivateReasonOptional;

    /**
     * This is a class related to the state of recording on the cloud.
     */
    class PLANETKIT_API RecordOnCloud : public Base {
    public :
        /**
         * Gets the state of recording on the cloud.
         */
        virtual bool IsActivated() = 0;

        /**
         * Gets the reason for deactivating recording on the cloud.
         * @remark
         *  - Return value can be nullptr when the return value of IsActivated() is true.
         */
        virtual DeactivateReasonOptional GetDeactivatedReason() = 0;
    };

    template class PLANETKIT_API AutoPtr<RecordOnCloud>;
    typedef AutoPtr<RecordOnCloud> RecordOnCloudPtr;

    /// @brief Event callback APIs for 1-to-1 calls
    /**
     * PlanetKit calls these APIs of ICallEvent when some events occur.
     */
    class PLANETKIT_API ICallEvent {
    public:
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
         * @param bIsSendingMyVideo This indicates whether the local user's video is being sent to the peer. If this value is false, the local user's video is in a paused state.
         */
        virtual void OnVideoEnabledByPeer(PlanetKitCallPtr pPlanetKitCall, bool bIsSendingMyVideo) = 0;

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
}
