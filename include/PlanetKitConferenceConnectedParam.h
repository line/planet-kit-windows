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

namespace PlanetKit {
    /**
     * Parameter used in IConferenceEvent::OnConnected.
     */
    class PLANETKIT_API ConferenceConnectedParam {
    public:
        virtual ~ConferenceConnectedParam() { }
        /**
         * Returns whether the sending video feature is using a hardware codec.
         */
        virtual bool IsVideoSendHardwareCodecEnabled() = 0;

        /**
         * Returns whether the screen share feature can support video share mode.
         * @see
         *  - PlanetKitConference::SetMyScreenShareVideoShareMode<br>
         *  - PlanetKitConference::IsMyScreenShareVideoShareModeEnabled
         */
        virtual bool IsSupportVideoShareMode() = 0;
    };

    typedef SharedPtr<ConferenceConnectedParam> ConferenceConnectedParamPtr;

};



