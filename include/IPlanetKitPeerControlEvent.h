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
#include "PlanetKitPeerDefine.h"

namespace PlanetKit {
    /// Callback APIs for a peer's status
    class PLANETKIT_API IPeerControlEvent {
    public:
        virtual ~IPeerControlEvent() { }

        /// Called when a peer is initialized.
        virtual void OnInitialized(PeerControlPtr pPeerControl, bool bResult) = 0;
        /// Called when a peer is muted.
        virtual void OnMuted(PeerControlPtr pPeerControl) = 0;
        /// Called when a peer is unmuted.
        virtual void OnUnmuted(PeerControlPtr pPeerControl) = 0;
        /// Called when a peer's video status is updated.
        virtual void OnVideoUpdated(PeerControlPtr pPeerControl, SubgroupPtr pSubgroup, const VideoStatus& videoStatus) = 0;
        /// Called when a peer's screen share is updated.
        virtual void OnScreenShareUpdated(PeerControlPtr pPeerControl, SubgroupPtr pSubgroup, EScreenShareState eState) = 0;
        /// Called when a peer subscribes to a subgroup.
        virtual void OnSubscribed(PeerControlPtr pPeerControl, SubgroupPtr pSubgroup) = 0;
        /// Called when a peer unsubscribes from a subgroup.
        virtual void OnUnsubscribed(PeerControlPtr pPeerControl, SubgroupPtr pSubgroup) = 0;
        /// Called when a peer is disconnected from the conference room.
        virtual void OnDisconnected(PeerControlPtr pPeerControl) = 0;

        /**
         * Called when a peer holds.
         * @param strHoldReason Reason string that can be nullptr.
         */
        virtual void OnHold(PeerControlPtr pPeerControl, const WString& strHoldReason) = 0;
        /// Called when a peer unholds.
        virtual void OnUnHold(PeerControlPtr pPeerControl) = 0;

        /**
         * Called when a peer sets shared contents.
         * @param unElapsedAfterSet Setting time
         * @param pvData Shared contents data
         * @param unDataSize Data size of the parameter pvData
         */
        virtual void OnSetSharedContents(PeerControlPtr pPeerControl, unsigned int unElapsedAfterSet, const void* pvData, unsigned int unDataSize) = 0;
        /// Called when a peer unsets shared contents.
        virtual void OnUnsetSharedContents(PeerControlPtr pPeerControl) = 0;

        /// Called when a peer's average volume level is updated.
        virtual void OnPeerAudioDescriptionUpdated(PeerControlPtr pPeerControl, const PeerAudioDescription& sPeerAudioDescription) = 0;
    };

    typedef SharedPtr<IPeerControlEvent> IPeerControlEventPtr;
};