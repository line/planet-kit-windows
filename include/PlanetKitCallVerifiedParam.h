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
     * Parameter used in ICallEvent::OnVerified.
     */
    class PLANETKIT_API CallVerifiedParam {
    public:
        virtual ~CallVerifiedParam() { }

        /**
         * Gets the peer's call start message.
         * @see [CallStartMessage guide](https://docs.lineplanet.me/windows/extended-functions/call-start-message)
         */
        virtual CallStartMessagePtr GetPeerStartMessage() = 0;

        /**
         * Returns whether the peer set the preparation flag.
         * @see [Preparation guide](https://docs.lineplanet.me/windows/extended-functions/responder-preparation-status)
         */
        virtual bool IsPeerUsePreparation() = 0;
    };

    typedef SharedPtr<CallVerifiedParam> CallVerifiedParamPtr;
};
