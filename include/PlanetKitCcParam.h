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
    class PLANETKIT_API CCParam;

    template class PLANETKIT_API AutoPtr<CCParam>;
    typedef AutoPtr<CCParam> CCParamPtr;

    /**
     * @details Gets peer data from CCParam.
     */
    class CCParam : public Base {
    public:
        /**
        * Gets the peer ID from CCParam.
        * @return Peer ID
        */
        virtual const WString& GetPeerID() = 0;

        /**
        * Gets the peer service ID from CCParam.
        * @return Peer service ID
        */
        virtual const WString& GetPeerServiceID() = 0;

        /**
        * Gets the peer media type from CCParam.
        * @return Peer media type
        */
        virtual EMediaType GetMediaType() = 0;
    };

}
