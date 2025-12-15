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

namespace PlanetKit {
    namespace Unsecured {
        /**
         * Keeps the microphone device active even when it is not in use during a call.
         *
         * This API forces the microphone to remain turned on regardless of
         * whether the user is actively using it. This behavior may lead to
         * potential privacy and security risks, as the microphone could
         * continuously capture audio input unintentionally.
         *
         * Warning: Using this API is strongly discouraged due to privacy concerns.
         *
         * @warning Potential privacy and security risk.
         */
#ifndef PLANETKIT_UNSECURED_DEPRECATE
        PLANETKIT_DEPRECATED("Using this API is strongly discouraged due to privacy concerns.")
#endif
        PLANETKIT_API void DangerouslyKeepMicActiveDuringCall();
    }
}