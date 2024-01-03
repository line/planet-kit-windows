#pragma once

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

#include "PlanetKit.h"

namespace PlanetKit
{
    class CommonVideoStatus
    {
    public:
        /// Gets the user ID.
        virtual const char* PeerId() = 0;
        /// Gets the service ID.
        virtual const char* ServiceId() = 0;

        /// Video pause reason
        virtual EVideoPauseReason VideoPauseReason() = 0;
    };

    /// @brief Array of CommonVideoStatus class.
    class CommonVideoStatuses : public Base
    {
    public:
        /// Gets the count of array elements.
        virtual size_t GetCount() = 0;
        /// Gets CommonVideoStatus* at index.
        virtual CommonVideoStatus* At(size_t nIdx) = 0;
    };
};
