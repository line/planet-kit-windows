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
#include "PlanetKitOptional.hpp"
#include "IPlanetKitResultHandler.h"

#include "IPlanetKitContentShareEvent.h"

namespace PlanetKit {
    class PLANETKIT_API ContentShareInterface : public Base {
    public:
        /**
        * Sets the event handler for shared content.
        * @return true on success.
        */
        virtual bool SetContentShareEvent(IContentShareEventPtr pEvent) = 0;

        /**
        * Removes the event handler for shared content.
        * @return true on success.
        */
        virtual bool RemoveContentShareEvent() = 0;

        /**
         * Sets the shared contents.
         * @param pShareContents Shared contents that you want to share.
         * @param nShareContentsSize Size of pShareContents
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         */
        virtual bool SetSharedContents(const void* pShareContents, int nShareContentsSize, void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;


        /**
         * Unsets the shared contents.
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         */
        virtual bool UnsetSharedContents(void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;


        /**
         * Sets the exclusively shared contents.
         * @param pShareContents Shared contents
         * @param nShareContentsSize Size of the shared contents
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         */
        virtual bool SetExclusivelySharedContents(const void* pShareContents, int nShareContentsSize, void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;


        /**
         * Unsets the exclusively shared contents.
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         */
        virtual bool UnsetExclusivelySharedContents(void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Sets the room shared contents on a conference call.<br>
         * This method is supported only in conference calls.
         * @param pShareContents Shared contents
         * @param nShareContentsSize Size of the shared contents
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         */
        virtual bool SetRoomSharedContents(const void* pShareContents, int nShareContentsSize, void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Unsets the shared contents on a conference call.<br>
         * This method is supported only in conference calls.
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         */
        virtual bool UnsetRoomSharedContents(void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;
    };
}