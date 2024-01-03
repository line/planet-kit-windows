// Copyright 2023 LINE Plus Corporation
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

namespace PlanetKit {

    /**
     * An instance of short data.<br>
     * Parameter used in ICallEvent::OnReceivedShortData or IConferenceEvent::OnReceivedShortData.
     */
    class PLANETKIT_API ShortDataParam : public Base {
    public:
        /**
         * Gets the ID of the peer that sent data.
         */
        virtual UserIdPtr GetPeerID() = 0;

        /**
         * Gets the type that the peer sets.
         */
        virtual const wchar_t* GetType() = 0;

        /**
         * Gets the data.
         */
        virtual const void* GetData() = 0;

        /**
         * Gets the size of data.
         */
        virtual unsigned int GetSize() = 0;
    };

    typedef AutoPtr<ShortDataParam> ShortDataParamPtr;
};