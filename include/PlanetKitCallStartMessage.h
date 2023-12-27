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

namespace PlanetKit {
    /**
     * Bytes of call start message string.
     */
    constexpr int CALL_INIT_DATA_LENGTH = 200;

    class PLANETKIT_API CallStartMessage;

    typedef AutoPtr<CallStartMessage> CallStartMessagePtr;

    /**
     * Local representation of data exchanged between caller and callee before PlanetKitCall session is established
     */
    class PLANETKIT_API CallStartMessage : public Base {
    public :
        /**
         * Creates the call start message.
         * @param szMessage Message data that you want to transfer to the peer, which must not exceed 200 bytes including the null-termination character after being converted to UTF-8.
         * @return CallStartMessagePtr
         * @remark
         *  - This API will return nullptr if szMessage is nullptr or if it exceeds 200 bytes after being converted to UTF-8. 
         */
        static CallStartMessagePtr Create(const wchar_t* szMessage);

        /**
         * Gets the call start message.
         * @return String message that is encoded in UTF-16 and null-terminated.
         */
        virtual const wchar_t* GetMessage() = 0;
    };
};