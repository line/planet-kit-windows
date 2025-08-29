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
    class PLANETKIT_API MyMediaStatus;
    typedef AutoPtr<MyMediaStatus> MyMediaStatusPtr;

    /**
     * An interface for the local user's media status event listener.
     */
    class IMyMediaStatusEvent {
    public:
        virtual ~IMyMediaStatusEvent() { }

        /// Called to notify the result of MyStatus::Register.
        virtual void OnRegisterResult(MyMediaStatusPtr pMyStatus, bool bResult) = 0;
        /// Called when the local user's video status is updated.
        virtual void OnUpdateVideoStatus(MyMediaStatusPtr pMyStatus, VideoStatus sStatus) = 0;
        /// Called when the local user's video subgroup is updated.
        virtual void OnUpdateVideoSubgroup(MyMediaStatusPtr pMyStatus, const WString& strSubgroupName) = 0;
        /// Called when the local user's screen share state is updated.
        virtual void OnUpdateScreenShareState(MyMediaStatusPtr pMyStatus, EScreenShareState eState) = 0;
        /// Called when the local user's screen share subgroup is updated.
        virtual void OnUpdateScreenShareSubgroup(MyMediaStatusPtr pMyStatus, const WString& strSubgroupName) = 0;
        /// Called when the local user's audio is muted.
        virtual void OnMuted(MyMediaStatusPtr pMyStatus) = 0;
        /// Called when the local user's audio is unmuted.
        virtual void OnUnmuted(MyMediaStatusPtr pMyStatus) = 0;
        /// Called when the local user's audio subgroup is updated.
        virtual void OnAudioSubgroup(MyMediaStatusPtr pMyStatus, const WString& strDestinationSubgroup, const WString& strTaggedSubgroup) = 0;

        /**
         * Called at each interval registered during the initialization of the call or the conference, providing the local user's volume value.
         * @param pMyStatus MyMediaStatus instance that the event was registered to.
         * @param sMyAudioDescription The local user's audio description.
         * @remark If the interval is 0, it does not occur.
         */
        virtual void OnMyAudioDescriptionUpdated(MyMediaStatusPtr pMyStatus, const MyAudioDescription& sMyAudioDescription) = 0;
    };

    typedef SharedPtr<IMyMediaStatusEvent> IMyMediaStatusEventPtr;
};