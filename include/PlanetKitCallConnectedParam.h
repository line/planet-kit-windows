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
#include "PlanetKitCallStartMessage.h"

namespace PlanetKit {
    /**
     * Parameter used in ICallEvent::OnConnected.
     */
    class PLANETKIT_API CallConnectedParam {
    public:
        virtual ~CallConnectedParam() { }

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

    typedef SharedPtr<CallConnectedParam> CallConnectedParamPtr;
};