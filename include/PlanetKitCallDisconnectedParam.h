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
#include "PlanetKitSharedPtr.hpp"

namespace PlanetKit {
    /**
     * Parameter used in ICallEvent::OnDisconnected.
     */
    class PLANETKIT_API CallDisconnectedParam {
    public:
        virtual ~CallDisconnectedParam() { }

        /**
         * Returns whether this call has been disconnected by the remote subject.
         */
        virtual bool IsDisconnectedByRemote() = 0;

        /**
         * Gets the reason for disconnection.
         */
        virtual EDisconnectReason GetReason() = 0;

        /**
         * Subject who performed disconnection.
         */
        virtual EDisconnectSource GetDisconnectSource() = 0;

        /**
         * Gets the reason string that is encoded in UTF-16 and null-terminated.
         * @remark
         *  - The return value can be nullptr.
         */
        virtual const WString& GetUserReleaseCode() = 0;
    };

    typedef SharedPtr<CallDisconnectedParam> CallDisconnectedParamPtr;
};