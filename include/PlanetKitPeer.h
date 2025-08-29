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
#include "PlanetKitUserId.h"
#include "PlanetKitPeerDefine.h"

#include "PlanetKitPeerControl.h"
#include "PlanetKitHoldStatus.h"
#include "PlanetKitVideoStatus.h"
#include "PlanetKitSharedContents.h"
#include "PlanetKitUserTypeContainer.h"

namespace PlanetKit {
    /**
     * Peer information.
     */
    class PLANETKIT_API Peer : public Base {
    public :
        /**
         * Gets the user's ID.
         */
        virtual UserIdPtr GetUserID() = 0;

        /// Gets the media type of the peer.
        virtual EMediaType GetMediaType() = 0;

        /// Gets the display name of the peer. The return value can be nullptr.
        virtual const WString& GetDisplayName() = 0;

        /// Gets the equipment type of the peer.
        virtual EUserEquipmentType GetUserEquipmentType() = 0;

        /// Gets the IP information of the peer. The return value can be nullptr.
        virtual const WString& GetSipLocalIP() = 0;

        /// Gets the device information of the peer. The return value can be nullptr.
        virtual const WString& GetDeviceInfo() = 0;

        /// Gets whether a data session is supported.
        virtual bool IsDataSessionSupported() = 0;

        /// Gets the audio mute status, where true means muted.
        virtual bool IsAudioMuted() = 0;

        /// Gets the hold status on the call.
        virtual const HoldStatus& GetHoldStatus() = 0;

        /**
         * Gets the subscribed subgroup name as an array class.
         * @return Subgroup name array.
         * @remark
         *  Conference call only.
         */
        virtual const WStringArray& GetSubscribedSubgroupNames() = 0;

        /**
         * Gets the name of the most recent subgroup where the video came from.
         * @return WStringOptional but it can be nullptr as `MainRoom` and it means the main room.
         * @see PlanetKitMainRoomName
         * @remark
         *  Conference call only.
         */
        virtual WStringOptional GetVideoSubgroupName() = 0;

        /**
         * Checks whether the peer is sharing screen.
         * @param szSubgroupName Subgroup name string which is encoded in UTF-16 and null-terminated but it can be `NullOptional` and it means `MainRoom`.
         */
        virtual ScreenShareStateResult GetScreenShareState(const WStringOptional& strSubgroupName = NullOptional) = 0;

        /**
         * Gets the peer's audio volume value.
         */
        virtual VolumeResult GetAudioVolumeLevelSetting() = 0;

        /**
         * Gets the peer's video status.
         * @param szSubgroupName Subgroup name string which is encoded in UTF-16 and null-terminated but it can be `NullOptional` and it means `MainRoom`.
         */
        virtual VideoStatusResult GetVideoStatus(const WStringOptional& strSubgroupName = NullOptional) = 0;

        /**
         * Gets the current video subgroup.
         * @return WStringOptional It is subgroup name string which is encoded in UTF-16 and null-terminated but it can be `NullOptional` that means `MainRoom`.
         */
        virtual WStringOptional GetCurrentVideoSubgroupName() = 0;

        /**
         * Gets the current screen share subgroup.
         * @return WStringOptional It is subgroup name string which is encoded in UTF-16 and null-terminated but it can be `NullOptional` that means `MainRoom`.
         */
        virtual WStringOptional GetCurrentScreenShareSubgroupName() = 0;

        /**
         * Creates PeerControl
         * @remark 
         *  - Conference call only
         */
        virtual PeerControlPtr CreatePeerControl( ) = 0;

        /// Gets shared contents.
        virtual SharedContentsOptional GetSharedContents() = 0;

        /**
         * Returns the type of the user.
         */
        virtual UserTypeContainerPtr GetUserType() = 0;
    };
};
