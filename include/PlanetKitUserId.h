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
#include "PlanetKitCommonTypes.h"


namespace PlanetKit {
    class PLANETKIT_API UserId;
    typedef SharedPtr<UserId> UserIdPtr;

    /// User identifier information class
    class PLANETKIT_API UserId {
    public :
        virtual ~UserId() { }

        /**
         * Creates an instance of the UserId class.
         * @param strID User ID string, which is encoded in UTF-16 and null-terminated.
         * @param strServiceID User service ID string, which is encoded in UTF-16 and null-terminated.
         * @param strCountryCode User country code string, which is encoded in UTF-16 and null-terminated.<br>It can be WStringOptional(nullOpt).
         * @return
         *  - If successfully created an instance of the UserId class, returns the pointer to the instance.<br>
         *  - If failed to create an instance of the UserId class, returns nullptr.
         */
        static UserIdPtr Create(const WString& strID, const WString& strServiceID, const WStringOptional& strCountryCode = NullOptional);

        /// Gets the user ID.
        virtual const WString& GetID() const = 0;
        /// Gets the user service ID.
        virtual const WString& GetServiceID() const = 0;
        /// Gets the user country code.
        virtual const WStringOptional& GetCountry() const = 0;
    };
}