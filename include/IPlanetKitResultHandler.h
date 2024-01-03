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

namespace PlanetKit
{
    /// @brief Event callback API
    /**
     * PlanetKit calls this API for the result after the user calls PlanetKit's asynchronous APIs.
     */
    class PLANETKIT_API IResultHandler
    {
    public:
        /**
        * The result handler will be called upon completion of the PlanetKit API. Pass a user-managed data pointer along with this handler.
        * @param pUserData User-managed data pointer.
        * @param bSuccess Result of the function call.
        */
        virtual void OnResult(void * pUserData, bool bSuccess) = 0;
    };
}
