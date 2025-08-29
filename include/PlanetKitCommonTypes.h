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

#include "PlanetKitAutoPtr.hpp"
#include "PlanetKitSharedPtr.hpp"
#include "PlanetKitContainer.hpp"
#include "PlanetKitOptional.hpp"
#include "PlanetKitString.hpp"

namespace PlanetKit {
    using ByteOptional = Optional<unsigned char>;

    using StringOptional = Optional<String>;
    using WStringOptional = Optional<WString>;

    using StringArray = Array<String>;
    using WStringArray = Array<WString>;

    using FloatOptional = Optional<float>;

    using UIntOptional = Optional<unsigned int>;

    using BoolOptional = Optional<bool>;

    using ByteArray = Array<unsigned char>;
};