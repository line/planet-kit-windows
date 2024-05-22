// Copyright 2022 LINE Corporation
//
// LINE Corporation licenses this file to you under the Apache License,
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
#include "PlanetKitCommonTypes.h"

namespace PlanetKit {
    template class PLANETKIT_API AutoPtr<Peer>;
    typedef AutoPtr<Peer> PeerPtr;

    template class PLANETKIT_API AutoPtr<ConferenceException>;
    typedef AutoPtr<ConferenceException> ConferenceExceptionPtr;

    template class PLANETKIT_API AutoPtr<PeerControl>;
    typedef AutoPtr<PeerControl> PeerControlPtr;

    template class PLANETKIT_API AutoPtr<ConferenceSubgroupUpdatePeer>;
    typedef AutoPtr<ConferenceSubgroupUpdatePeer> ConferenceSubgroupUpdatePeerPtr;

    template class PLANETKIT_API AutoPtr<CommonSetSharedContent>;
    typedef AutoPtr<CommonSetSharedContent> CommonSetSharedContentPtr;

    template class PLANETKIT_API AutoPtr<Subgroup>;
    typedef AutoPtr<Subgroup> SubgroupPtr;

    template class PLANETKIT_API AutoPtr<SubgroupManager>;
    typedef AutoPtr<SubgroupManager> SubgroupManagerPtr;

    template class PLANETKIT_API AutoPtr<SharedContentsData>;
    typedef AutoPtr<SharedContentsData> SharedContentsDataPtr;

    template class PLANETKIT_API AutoPtr<SharedContents>;
    typedef AutoPtr<SharedContents> SharedContentsPtr;

    template class PLANETKIT_API AutoPtr<ConferencePeerUpdateParam>;
    typedef AutoPtr<ConferencePeerUpdateParam> ConferencePeerUpdateParamPtr;

    template class PLANETKIT_API AutoPtr<AudioDevice>;
    typedef AutoPtr<AudioDevice> AudioDevicePtr;

    template class PLANETKIT_API Optional<EScreenShareState>;
    typedef Optional<EScreenShareState> EScreenShareStateOptional;

    template class PLANETKIT_API Optional<SubgroupPtr>;
    typedef Optional<SubgroupPtr> SubgroupOptional;

    template class PLANETKIT_API Optional<SubgroupManagerPtr>;
    typedef Optional<SubgroupManagerPtr> SubgroupManagerOptional;

    template class PLANETKIT_API Optional<AudioDevicePtr>;
    typedef Optional<AudioDevicePtr> AudioDeviceOptional;

    template class PLANETKIT_API Optional<SharedContentsDataPtr>;
    typedef Optional<SharedContentsDataPtr> SharedContentsDataOptional;

    template class PLANETKIT_API Optional<SharedContentsPtr>;
    typedef Optional<SharedContentsPtr> SharedContentsOptional;

    template class PLANETKIT_API Array<PeerPtr>;
    typedef Array<PeerPtr> PeerArray;
    
    template class PLANETKIT_API Array<ConferenceExceptionPtr>;
    typedef Array<ConferenceExceptionPtr> ConferenceExceptionArray;

    template class PLANETKIT_API Array<ConferenceSubgroupUpdatePeerPtr>;
    typedef Array<ConferenceSubgroupUpdatePeerPtr> ConferenceSubgroupUpdatePeerArray;

    template class PLANETKIT_API Array<CommonSetSharedContentPtr>;
    typedef Array<CommonSetSharedContentPtr> CommonSetSharedContentArray;

    template class PLANETKIT_API Array<SubgroupPtr>;
    typedef Array<SubgroupPtr> SubgroupArray;

    template class PLANETKIT_API AutoPtr<MakeCallParam>;
    typedef AutoPtr<MakeCallParam> MakeCallParamPtr;

    template class PLANETKIT_API AutoPtr<VerifyCallParam>;
    typedef AutoPtr<VerifyCallParam> VerifyCallParamPtr;

    typedef struct ScreenShareStateResult {
        EScreenShareStateOptional eScreenShareState;
        EPeerGetFailReason ePeerGetFailReason = EPeerGetFailReason::PLNK_PEER_GET_FAIL_REASON_NONE;
    } ScreenShareStateResult;

    /// @struct VolumeResult
    /// @brief Peer Volume Result
    typedef struct VolumeResult {
        /// Volume Level(Optional) [0:100]
        ByteOptional ucAverageVolumeLevel;
        /// Reasons why ucAverageVolumeLevel is not exist
        EPeerGetFailReason ePeerGetFailReason = EPeerGetFailReason::PLNK_PEER_GET_FAIL_REASON_NONE;
    } VolumeResult;

    typedef struct AudioDescriptionInfo {
        bool bEnableAudioDescription = true;
        unsigned int unAudioDescriptionInterval = 500;
    }AudioDescriptionInfo;

};