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
#include "PlanetKitVideoDefine.h"

namespace PlanetKit {
    /// The interface for receiving a callback when frame processing is finished.
    class PLANETKIT_API IVideoInterceptorDelegate {
    public:
        virtual ~IVideoInterceptorDelegate() { }

        /**
         * A callback that occurs when a capture is finished.
         * @param pVideoFrame The frame being captured.
         * @return
         *  - Returns true if successful.
         */
        virtual bool onProcessFinished(SVideoFrame* pVideoFrame) = 0;
    };
};