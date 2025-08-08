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
#include "PlanetKitCommonSetSharedContent.h"

namespace PlanetKit {
    class PLANETKIT_API ContentShareInterface;
    
    using ContentShareInterfacePtr = AutoPtr<ContentShareInterface>;
    using ContentShareInterfaceOptional = Optional<ContentShareInterfacePtr>;

    class PLANETKIT_API IContentShareEvent {
    public:
        virtual ~IContentShareEvent() { }

        /**
         * Called when peers set shared contents.
         * @remark
         *  - You can use these APIs.<br>
         *    + CommonSetSharedContent::PeerId()<br>
         *    + CommonSetSharedContent::ServiceId()<br>
         *    + CommonSetSharedContent::GetPeer()<br>
         *    + CommonSetSharedContent::ElapsedAfterSetMsec()<br>
         *    + CommonSetSharedContent::Data()<br>
         *    + CommonSetSharedContent::DataSize()
         */
        virtual void OnPeersSetSharedContents(ContentShareInterfacePtr pContentShareInterface, const CommonSetSharedContentArray& arrSharedContent) = 0;

        /**
         * Called when peers unset shared contents.
         * @remark
         *  - You can use these APIs.<br>
         *    + CommonSetSharedContent::PeerId()<br>
         *    + CommonSetSharedContent::ServiceId()<br>
         *    + CommonSetSharedContent::GetPeer()<br>
         */
        virtual void OnPeersUnsetSharedContents(ContentShareInterfacePtr pContentShareInterface, const CommonSetSharedContentArray& arrSharedContent) = 0;

        /**
         * Called when peers set exclusively shared contents.
         * @remark
         *  - You can use these APIs.<br>
         *    + CommonSetSharedContent::PeerId()<br>
         *    + CommonSetSharedContent::ServiceId()<br>
         *    + CommonSetSharedContent::GetPeer()<br>
         *    + CommonSetSharedContent::ElapsedAfterSetMsec()<br>
         *    + CommonSetSharedContent::Data()<br>
         *    + CommonSetSharedContent::DataSize()
         */
        virtual void OnPeerSetExclusivelySharedContents(ContentShareInterfacePtr pContentShareInterface, CommonSetSharedContentPtr pCommonSharedContent) = 0;

        /**
         * Called when peers unset exclusively shared contents.
         * @remark
         *  - You can use these APIs.<br>
         *    + CommonSetSharedContent::PeerId()<br>
         *    + CommonSetSharedContent::ServiceId()<br>
         *    + CommonSetSharedContent::GetPeer()
         */
        virtual void OnPeerUnsetExclusivelySharedContents(ContentShareInterfacePtr pContentShareInterface, CommonSetSharedContentPtr pCommonSharedContent) = 0;

        /**
         * Called when any participant of conference call set 'Room Shared Content'.
         * @remark
         *  - Support only conference call.<br>
         *  - You can use these APIs.<br>
         *    + CommonSetSharedContent::PeerId()<br>
         *    + CommonSetSharedContent::ServiceId()<br>
         *    + CommonSetSharedContent::ElapsedAfterSetMsec()<br>
         *    + CommonSetSharedContent::Data()<br>
         *    + CommonSetSharedContent::DataSize()
        */
        virtual void OnPeerSetRoomSharedContents(ContentShareInterfacePtr pContentShareInterface, CommonSetSharedContentPtr pCommonSharedContent) = 0;

        /**
         * Called when any participant of conference call unset 'Room Shared Content'.
         * @remark
         *  - Support only conference call.<br>
         *  - You can use these APIs.<br>
         *    + CommonSetSharedContent::PeerId()<br>
         *    + CommonSetSharedContent::ServiceId()
        */
        virtual void OnPeerUnsetRoomSharedContents(ContentShareInterfacePtr pContentShareInterface, CommonSetSharedContentPtr pCommonSharedContent) = 0;
    };

    using IContentShareEventPtr = SharedPtr<IContentShareEvent>;
};