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
#include "PlanetKitPeer.h"

namespace PlanetKit {
    /**
     * Exception message information class.
     * @see ConferenceExceptionMessage
     * @see OnException
     */
    class PLANETKIT_API ConferenceException {
    public:
        virtual ~ConferenceException() = default;

        /// Gets the peer information class.
        virtual PeerPtr GetPeer() = 0;
        /// Gets the subgroup information class.
        virtual SubgroupPtr GetSubgroup() = 0;
        /// Gets the exception type information.
        virtual EConferenceExceptionType GetExceptionType() = 0;
        /// Gets the exception message as a string that can be nullptr.
        virtual const WString& GetMessage() = 0;
    };

    typedef SharedPtr<ConferenceException> ConferenceExceptionPtr;
    typedef Array<ConferenceExceptionPtr> ConferenceExceptionArray;
};