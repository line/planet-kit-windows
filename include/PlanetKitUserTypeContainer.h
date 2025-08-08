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
#include "PlanetKitPredefine.h"
#include "PlanetKitCommonTypes.h"
#include "PlanetKitUserType.h"

namespace PlanetKit {
    /**
     * A container for user type.<br>
     * This class can hold either a predefined [PlanetKitUserType] or a custom user type represented by an unsigned integer.<br>
     * Custom user types are defined by the application and must be in the range of 1 to 9999.
     *
     * @see PlanetKitUserType
     */
    class PLANETKIT_API UserTypeContainer {
    public:
        virtual ~UserTypeContainer() { }

        /// If the user type matches a case in `PlanetKitUserType`, returns that enum.
        virtual PlanetKitUserTypeOptional GetPlanetKitUserType() = 0;

        /// If the user type is in the range 1 to 9999, returns that custom integer.
        virtual UIntOptional GetCustomUserType() = 0;

        /// Indicates whether the user type is a PlanetKit user type.
        virtual bool IsPlanetKitUserType() const = 0;
    };

    using UserTypeContainerPtr = SharedPtr<UserTypeContainer>;
};