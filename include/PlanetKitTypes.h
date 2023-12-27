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

namespace PlanetKit
{
    typedef AutoPtr<Peer> PeerPtr;
    typedef AutoPtr<ConferenceException> ConferenceExceptionPtr;
    typedef AutoPtr<PeerControl> PeerControlPtr;
    typedef AutoPtr<ConferenceSubgroupUpdatePeer> ConferenceSubgroupUpdatePeerPtr;
    typedef AutoPtr<CommonSetSharedContent> CommonSetSharedContentPtr;
    typedef AutoPtr<Subgroup> SubgroupPtr;
    typedef AutoPtr<SubgroupManager> SubgroupManagerPtr;
    typedef AutoPtr<SharedContentsData> SharedContentsDataPtr;
    typedef AutoPtr<ConferencePeerUpdateParam> ConferencePeerUpdateParamPtr;
    typedef AutoPtr<AudioDevice> AudioDevicePtr;

    typedef Optional<EScreenShareState> EScreenShareStateOptional;
    typedef Optional<VideoStatus> VideoStatusOptional;
    typedef Optional<unsigned char> ByteOptional;
    typedef Optional<SubgroupPtr> SubgroupOptional;
    typedef Optional<SubgroupManagerPtr> SubgroupManagerOptional;
    typedef Optional<AudioDevicePtr> AudioDeviceOptional;
    typedef Optional<SharedContentsDataPtr> SharedContentsDataOptional;
    typedef Optional<String> StringOptional;
    typedef Optional<WString> WStringOptional;
    
    typedef Array<PeerPtr> PeerArray;
    typedef Array<ConferenceExceptionPtr> ConferenceExceptionArray;
    typedef Array<ConferenceSubgroupUpdatePeerPtr> ConferenceSubgroupUpdatePeerArray;
    typedef Array<CommonSetSharedContentPtr> CommonSetSharedContentArray;
    typedef Array<SubgroupPtr> SubgroupArray;

    typedef Array<PeerAudioDescription> PeerAudioDescriptionArray;
    
    typedef AutoPtr<CallParam> CallParamPtr;
    typedef AutoPtr<MakeCallParam> MakeCallParamPtr;
    typedef AutoPtr<VerifyCallParam> VerifyCallParamPtr;

    typedef struct ScreenShareStateResult
    {
        EScreenShareStateOptional eScreenShareState;
        EPeerGetFailReason ePeerGetFailReason = EPeerGetFailReason::PLNK_PEER_GET_FAIL_REASON_NONE;
    }ScreenShareStateResult;

    /// @struct VolumeResult
    /// @brief Peer Volume Result
    typedef struct VolumeResult
    {
        /// Volume Level(Optional) [0:100]
        ByteOptional ucAverageVolumeLevel;
        /// Reasons why ucAverageVolumeLevel is not exist
        EPeerGetFailReason ePeerGetFailReason = EPeerGetFailReason::PLNK_PEER_GET_FAIL_REASON_NONE;
    }VolumeResult;
};