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
#include "IPlanetKitVideoInterceptorDelegate.h"

namespace PlanetKit {
    /// The interface for receiving a callback when the status of the window in screen share changes.
    class PLANETKIT_API IVideoInterceptor {
    public:
        virtual ~IVideoInterceptor() { }

        /**
        * Returns SVideoFrame* if a video frame is processed synchronously
        */
        virtual SVideoFrame* ProcessVideoFrame(SVideoFrame* pVideoFrame) = 0;

        /**
         * Registers the frame processing completion callback.
         * @param pDelegate A callback that occurs when a capture is finished.
         * @return
         *  - Returns true if successful.
         */
        virtual bool RegisterDelegate(IVideoInterceptorDelegate* pDelegate) = 0;

        /**
         * Deregisters the frame processing completion callback.
         * @return
         *  - Returns true if successful.
         */
        virtual bool DeregisterDelegate() = 0;
    };

    typedef SharedPtr<IVideoInterceptor> IVideoInterceptorPtr;
};