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

namespace PlanetKit {
    constexpr wchar_t* PlanetKitMainRoomName = nullptr;

    class PLANETKIT_API Subgroup;
    typedef AutoPtr<Subgroup> SubgroupPtr;
    typedef Optional<SubgroupPtr> SubgroupOptional;
    typedef Array<SubgroupPtr> SubgroupArray;

    /**
     * @brief Reasons for subgroup subscription failure
     */
    typedef enum ESubgroupSubscribeFailReason {
        /// Undefined
        PLNK_SUBGRP_SUBS_FAIL_REASON_UNDEFINED = 0,
        /// Timeout
        PLNK_SUBGRP_SUBS_FAIL_REASON_TIMEOUT = 1,
        /// An attempt to subscribe using a different attribute than the attributes of this subgroup failed.
        PLNK_SUBGRP_SUBS_FAIL_REASON_WRONG_ATTR = 2,
        /// The maximum number of subgroups are created in the server.
        PLNK_SUBGRP_SUBS_FAIL_REASON_OVER_MAX_SUBGRP_CNT = 3,
        /// The local user has already subscribed to this subgroup.
        PLNK_SUBGRP_SUBS_FAIL_REASON_ALREADY_SUBSCRIBED = 4,
        /// Unknown
        PLNK_SUBGRP_SUBS_FAIL_REASON_UNKNOWN = 1000
    } ESubgroupSubscribeFailReason;

    /**
     * @brief Reasons for subgroup unsubscription failure
     */
    typedef enum ESubgroupUnsubscribeFailReason {
        /// Undefined
        PLNK_SUBGRP_UNSUBS_FAIL_REASON_UNDEFINED = 0,
        /// The local user is sending audio to this subgroup and can't unsubscribe.
        PLNK_SUBGRP_UNSUBS_FAIL_REASON_HAS_ACTIVE_AUDIO = 1,
        /// The local user is sending video to this subgroup and can't unsubscribe.
        PLNK_SUBGRP_UNSUBS_FAIL_REASON_HAS_ACTIVE_VIDEO = 2,
        /// This is a subgroup to which the local user has not subscribed.
        PLNK_SUBGRP_UNSUBS_FAIL_REASON_NOT_SUBSCRIBED = 3,
        /// The local user is sending screen share to this subgroup and can't unsubscribe.
        PLNK_SUBGRP_UNSUBS_FAIL_REASON_HAS_ACTIVE_SCREEN_SHARE = 4,
        /// Unknown
        PLNK_SUBGRP_UNSUBS_FAIL_REASON_UNKNOWN = 1000
    } ESubgroupUnsubscribeFailReason;

    /**
     * @brief Enum of the subgroup peer update type in Subgroup
     */
    typedef enum ESubgroupPeerUpdateType {
        /// None
        PLNK_SUBGRP_PEER_UPDATE_TYPE_NONE = 0,
        /// Public room
        PLNK_SUBGRP_PEER_UPDATE_TYPE_PUBLIC,
        /// Private room
        PLNK_SUBGRP_PEER_UPDATE_TYPE_PRIVATE,
    } ESubgroupPeerUpdateType;

    using SubscribeResult = void(*)(SubgroupPtr pSubgroup, bool bSuccess, ESubgroupSubscribeFailReason eReason, void* pUserData);
    using UnsubscribeResult = void(*)(SubgroupPtr pSubgroup, bool bSuccess, ESubgroupUnsubscribeFailReason eReason, void* pUserData);
};