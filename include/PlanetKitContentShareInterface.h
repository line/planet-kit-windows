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
#include "IPlanetKitResultHandler.h"
#include "PlanetKitCommonSetSharedContent.h"

#include "PlanetKitOptional.hpp"

namespace PlanetKit
{
    class PLANETKIT_API ContentShareInterface;

    typedef AutoPtr<ContentShareInterface> ContentShareInterfacePtr;
    typedef Optional<ContentShareInterfacePtr> ContentShareInterfaceOptional;

    class PLANETKIT_API IContentShareEvent
    {
    public:
        PLANETKIT_DEPRECATED("This will not be supported in 4.3 or later. Use OnPeerSetSharedContents(PlanetKit::ContentShareInterface *pContentShareInterface, PlanetKit::CommonSetSharedContents * pCommonSetSharedContents)")
        /**
         * @deprecated This will not be supported in 4.3 or later.
         * @see OnPeerSetSharedContents
         */
        void OnPeerSetSharedContents(ContentShareInterface *pContentShareInterface, const char *szPeerId,
                const char *szPeerServiceId, unsigned int nElapsedAfterSetMsec, const void *pData, unsigned int nDataSize);

        PLANETKIT_DEPRECATED("This will not be supported in 4.3 or later. Use OnPeerUnsetSharedContents(PlanetKit::ContentShareInterface *pContentShareInterface, PlanetKit::CommonSetSharedContents * pCommonSetSharedContents)")
        /**
         * @deprecated This will not be supported in 4.3 or later.
         * @see OnPeerUnsetSharedContents
         */
        void OnPeerUnsetSharedContents(ContentShareInterface *pContentShareInterface, const char *szPeerId,
            const char *szPeerServiceId);

        PLANETKIT_DEPRECATED("This will not be supported in 4.3 or later. Use OnPeerSetExclusivelySharedContents(PlanetKit::ContentShareInterface *pContentShareInterface, PlanetKit::CommonSetSharedContents * pCommonSetSharedContents)")
        /**
         * @deprecated This will not be supported in 4.3 or later.
         * @see OnPeerSetExclusivelySharedContents
         */
        void OnPeerSetExclusivelySharedContents(ContentShareInterface *pContentShareInterface, const char *szPeerId,
                const char *szPeerServiceId, unsigned int nElapsedAfterSetMsec, const void *pData, unsigned int nDataSize);

        PLANETKIT_DEPRECATED("This will not be supported in 4.3 or later. Use OnPeerUnsetExclusivelySharedContents(PlanetKit::ContentShareInterface *pContentShareInterface, PlanetKit::CommonSetSharedContents * pCommonSetSharedContents)")
        /**
         * @deprecated This will not be supported in 4.3 or later.
         * @see OnPeerUnsetExclusivelySharedContents
         */
        void OnPeerUnsetExclusivelySharedContents(ContentShareInterface *pContentShareInterface, const char *szPeerId,
            const char *szPeerServiceId);


        PLANETKIT_DEPRECATED("This will not be supported in 4.3 or later. Use OnPeersSetRoomSharedContents(PlanetKit::ContentShareInterface *pContentShareInterface, PlanetKit::CommonSetSharedContents * pCommonSetSharedContents)")
        /**
         * @deprecated This will not be supported in 4.3 or later.
         * @see OnPeersSetRoomSharedContents
         */
        void OnPeerSetRoomSharedContents(ContentShareInterface *pContentShareInterface, const char *szPeerId,
                const char *szPeerServiceId, unsigned int nElapsedAfterSetMsec, const void *pData, unsigned int nDataSize);

        PLANETKIT_DEPRECATED("This will not be supported in 4.3 or later. Use OnPeersUnsetRoomSharedContents(PlanetKit::ContentShareInterface *pContentShareInterface, PlanetKit::CommonSetSharedContents * pCommonSetSharedContents)")
        /**
         * @deprecated This will not be supported in 4.3 or later.
         * @see OnPeersUnsetRoomSharedContents
         */
        void OnPeerUnsetRoomSharedContents(ContentShareInterface *pContentShareInterface, const char *szPeerId,
            const char *szPeerServiceId);


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         */
        void OnPeersSetSharedContents(ContentShareInterface *pContentShareInterface, CommonSetSharedContents * pConferenceSetSharedContents);

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         */
        void OnPeersUnsetSharedContents(ContentShareInterface *pContentShareInterface, CommonSetSharedContents * pConferenceSetSharedContents);

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         */
        void OnPeerSetExclusivelySharedContents(ContentShareInterface *pContentShareInterface, CommonSetSharedContent * pConferenceSetSharedContent);

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         */
        void OnPeerUnsetExclusivelySharedContents(ContentShareInterface *pContentShareInterface, CommonSetSharedContent * pConferenceSetSharedContent);


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         */
        void OnPeerSetRoomSharedContents(ContentShareInterface *pContentShareInterface, CommonSetSharedContent * pCommonSetSharedContent);


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         */
        void OnPeerUnsetRoomSharedContents(ContentShareInterface *pContentShareInterface, CommonSetSharedContent * pCommonSetSharedContent);

        /**
         * Called when peers set shared contents.
         * @remark
         *  - You can use these APIs.
         *    + CommonSetSharedContent::PeerId()
         *    + CommonSetSharedContent::ServiceId()
         *    + CommonSetSharedContent::GetPeer()
         *    + CommonSetSharedContent::ElapsedAfterSetMsec()
         *    + CommonSetSharedContent::Data()
         *    + CommonSetSharedContent::DataSize()
         */
        virtual void OnPeersSetSharedContents(ContentShareInterfacePtr pContentShareInterface, const CommonSetSharedContentArray& arrSharedContent) = 0;

        /**
         * Called when peers unset shared contents.
         * @remark
         *  - You can use these APIs.
         *    + CommonSetSharedContent::PeerId()
         *    + CommonSetSharedContent::ServiceId()
         *    + CommonSetSharedContent::GetPeer()
         */
        virtual void OnPeersUnsetSharedContents(ContentShareInterfacePtr pContentShareInterface, const CommonSetSharedContentArray& arrSharedContent) = 0;

        /**
         * Called when peers set exclusively shared contents.
         * @remark
         *  - You can use these APIs.
         *    + CommonSetSharedContent::PeerId()
         *    + CommonSetSharedContent::ServiceId()
         *    + CommonSetSharedContent::GetPeer()
         *    + CommonSetSharedContent::ElapsedAfterSetMsec()
         *    + CommonSetSharedContent::Data()
         *    + CommonSetSharedContent::DataSize()
         */
        virtual void OnPeerSetExclusivelySharedContents(ContentShareInterfacePtr pContentShareInterface, CommonSetSharedContentPtr pCommonSharedContent) = 0;

        /**
         * Called when peers unset exclusively shared contents.
         * @remark
         *  - You can use these APIs.
         *    + CommonSetSharedContent::PeerId()
         *    + CommonSetSharedContent::ServiceId()
         *    + CommonSetSharedContent::GetPeer()
         */
        virtual void OnPeerUnsetExclusivelySharedContents(ContentShareInterfacePtr pContentShareInterface, CommonSetSharedContentPtr pCommonSharedContent) = 0;

        /**
         * Called when any participant of conference call set 'Room Shared Content'.
         * @remark
         *  - Support only conference call.
         *  - You can use these APIs.
         *    + CommonSetSharedContent::PeerId()
         *    + CommonSetSharedContent::ServiceId()
         *    + CommonSetSharedContent::ElapsedAfterSetMsec()
         *    + CommonSetSharedContent::Data()
         *    + CommonSetSharedContent::DataSize()
        */
        virtual void OnPeerSetRoomSharedContents(ContentShareInterfacePtr pContentShareInterface, CommonSetSharedContentPtr pCommonSharedContent) = 0;

        /**
         * Called when any participant of conference call unset 'Room Shared Content'.
         * @remark
         *  - Support only conference call.
         *  - You can use these APIs.
         *    + CommonSetSharedContent::PeerId()
         *    + CommonSetSharedContent::ServiceId()
        */
        virtual void OnPeerUnsetRoomSharedContents(ContentShareInterfacePtr pContentShareInterface, CommonSetSharedContentPtr pCommonSharedContent) = 0;
    };


    class PLANETKIT_API ContentShareInterface : public Base
    {
    public:

        /**
        * Sets the event handler for shared content.
        * @return true on success.
        */
        virtual bool SetContentShareEvent(IContentShareEvent *pEvent) = 0;


        /**
        * Removes the event handler for shared content.
        * @return true on success.
        */
        virtual bool RemoveContentShareEvent() = 0;


        /**
        * Sets the shared contents.
        * @param pShareContents Shared contents
        * @param nShareContentsSize Size of the shared contents
        * @param pUserData User data to be passed when pResultHandler is called
        * @param pResultHandler Result handler to be called after executing the method
        * @return true on successful function call. Wait for IContentShareEvent::OnSetSharedContentsResult() to check the request result.
        */
        virtual bool SetSharedContents(const void *pShareContents, int nShareContentsSize, NULLABLE void * pUserData, NULLABLE IResultHandler *pResultHandler) = 0;


        /**
        * Unsets the shared contents.
        * @param pUserData User data to be passed when pResultHandler is called
        * @param pResultHandler Result handler to be called after executing the method
        * @return true on successful function call. Wait for IContentShareEvent::OnUnsetSharedContentsResult() to check the request result.
        */
        virtual bool UnsetSharedContents(NULLABLE void * pUserData, NULLABLE IResultHandler *pResultHandler) = 0;


        /**
        * Sets the exclusively shared contents.
        * @param pShareContents Shared contents
        * @param nShareContentsSize Size of the shared contents
        * @param pUserData User data to be passed when pResultHandler is called
        * @param pResultHandler Result handler to be called after executing the method
        * @return true on successful function call. Wait for IContentShareEvent::OnSetExclusivelySharedContentsResult() to check the request result.
        */
        virtual bool SetExclusivelySharedContents(const void *pShareContents, int nShareContentsSize, NULLABLE void * pUserData, NULLABLE IResultHandler *pResultHandler) = 0;


        /**
        * Unsets the exclusively shared contents.
        * @param pUserData User data to be passed when pResultHandler is called
        * @param pResultHandler Result handler to be called after executing the method
        * @return true on successful function call. Wait for IContentShareEvent::OnUnsetExclusivelySharedContentsResult() to check the request result.
        */
        virtual bool UnsetExclusivelySharedContents(NULLABLE void * pUserData, NULLABLE IResultHandler *pResultHandler) = 0;

        /**
        * Sets the room shared contents on a conference call.
        * This method is supported only in conference calls.
        * @param pShareContents Shared contents
        * @param nShareContentsSize Size of the shared contents
        * @param pUserData User data to be passed when pResultHandler is called
        * @param pResultHandler Result handler to be called after executing the method
        * @return true on successful function call. Wait for IResultHandler::OnResult() to check the request result.
        */
        virtual bool SetRoomSharedContents(const void *pShareContents, int nShareContentsSize, NULLABLE void * pUserData, NULLABLE IResultHandler *pResultHandler) = 0;

        /**
        * Unsets the shared contents on a conference call.
        * This method is supported only in conference calls.
        * @param pUserData User data to be passed when pResultHandler is called
        * @param pResultHandler Result handler to be called after executing the method
        * @return true on successful function call. Wait for IResultHandler::OnResult() to check the request result.
        */
        virtual bool UnsetRoomSharedContents(NULLABLE void * pUserData, NULLABLE IResultHandler *pResultHandler) = 0;
    };
}