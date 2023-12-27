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
    PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use UserId")
    /**
    * @deprecated This will not be supported in 5.0 or later.
    * @see UserId
    */
    class PLANETKIT_API InitUserId
    {

    };

    class PLANETKIT_API UserId;

    typedef AutoPtr<UserId> UserIdPtr;

    /// User identifier information class
    class PLANETKIT_API UserId : public Base {
    public :
        /**
         * Creates an instance of the UserId class.
         * @param szID User ID string, which is encoded in UTF-16 and null-terminated.
         * @param szServiceID User service ID string, which is encoded in UTF-16 and null-terminated.
         * @param szCountryCode User country code string, which is encoded in UTF-16 and null-terminated.<br>It can be nullptr.
         * @return
         *  - If successfully created an instance of the UserId class, returns the pointer to the instance.<br>
         *  - If failed to create an instance of the UserId class, returns nullptr.
         */
        static UserIdPtr Create(const wchar_t* szID, const wchar_t* szServiceID, const wchar_t* szCountryCode = nullptr);

        /// Gets the user ID.
        virtual const wchar_t* GetID() const = 0;
        /// Gets the user service ID.
        virtual const wchar_t* GetServiceID() const = 0;
        /// Gets the user country code.
        virtual const wchar_t* GetCountry() const = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see UserId::Create(const wchar_t* szID, const wchar_t* szServiceID, const wchar_t* szCountryCode = nullptr);
         */
        bool SetId(const char* lpszUserId);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see const wchar_t* GetID() const
         */
        const char* GetId() const;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see UserId::Create(const wchar_t* szID, const wchar_t* szServiceID, const wchar_t* szCountryCode = nullptr);
         */
        bool SetServiceId(const char* lpszServiceId);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see const wchar_t* GetServiceID() const
         */
        const char* GetServiceId() const;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use bool SetCountry(const wchar_t* szCountry)")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see UserId::Create(const wchar_t* szID, const wchar_t* szServiceID, const wchar_t* szCountryCode = nullptr);
         */
        bool SetCountry(const char* lpszCountry);
    };
}