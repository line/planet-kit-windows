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
#include "PlanetKitTypes.h"
#include "PlanetKitPeerControl.h"
#include "PlanetKitHoldStatus.h"
#include "PlanetKitOptional.hpp"
#include "PlanetKitVideoStatus.h"
#include "PlanetKitUserId.h"

namespace PlanetKit
{
    PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
    /**
    * @deprecated This will not be supported in 5.0 or later.
    */
    class PLANETKIT_API PeerState
    {
    };

    PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use PlanetKit::Peer")
    /**
    * @deprecated This will not be supported in 5.0 or later.
    * @see Peer
    */
    class PLANETKIT_API ConferencePeer
    {

    };

    class PLANETKIT_API SharedContentsData : public Base
    {
    public:
        SharedContentsData(const void * pData, unsigned int unDataSize, unsigned int unElapsedAfterSetMsec);
        ~SharedContentsData();

        void            *m_pData;
        unsigned int     m_unDataSize;
        unsigned int     m_unElapsedAfterSetMsec;
        
        ULONG AddRef();
        ULONG Release();

    private:
        volatile ULONG m_ulRef = 1;
    };

    /**
     * Peer information.
     */
    class PLANETKIT_API Peer : public Base
    {
    public :
        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use UserIdPtr GetId()")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see UserIdPtr GetUserID()
         */
        const String& GetUserId();
        
        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use UserIdPtr GetId()")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see UserIdPtr GetUserID()
         */
        const String& GetServiceId();

        /**
         * Gets the user's ID.
         */
        virtual UserIdPtr GetUserID() = 0;

        /// Gets the media type of the peer.
        virtual EMediaType GetMediaType() = 0;

        /// Gets the display name of the peer. The return value can be nullptr.
        virtual const WString& GetDisplayName() = 0;

        /// Gets the equipment type of the peer.
        virtual EUserEquipmentType GetUserEquipmentType() = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later. Use GetSipLocalIP")
        /**
         * @deprecated This will not be supported in 5.1 or later.
         * @see GetSipLocalIP
         */
        const String& GetIP();

        /// Gets the IP information of the peer. The return value can be nullptr.
        virtual const WString& GetSipLocalIP() = 0;

        /// Gets the device information of the peer. The return value can be nullptr.
        virtual const WString& GetDeviceInfo() = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later. Use IsDataSessionSupported")
        /**
         * @deprecated This will not be supported in 5.1 or later.
         * @see IsDataSessionSupported
         */
        bool GetSupportDataSession();

        /// Gets whether a data session is supported.
        virtual bool IsDataSessionSupported() = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later. Use IsAudioMuted")
        /**
         * @deprecated This will not be supported in 5.1 or later.
         * @see IsAudioMuted
         */
        bool GetAudioMuted();

        /// Gets the audio mute status, where true means muted.
        virtual bool IsAudioMuted() = 0;

        /// Gets the hold status on the call.
        virtual HoldStatus GetHoldStatus() = 0;


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use IConferenceEvent.OnPeersAudioDescriptionUpdated")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see OnPeersAudioDescriptionUpdated
        */
        unsigned char GetAudioLevel();

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use GetSubscribedSubgroupNames")
        /**
        * @deprecated This will not be supported in 5.2 or later.
        * @see GetSubscribedSubgroupNames
        */
        StringArray& GetSubscribedSubgroup();

        /**
         * Gets the subscribed subgroup name as an array class.
         * @return Subgroup name array.
         * @remark
         *  Conference call only.
         */
        virtual const WStringArray& GetSubscribedSubgroupNames() = 0;

        /**
         * Gets the name of the most recent subgroup where the video came from.
         * @return String but it can be nullptr as 'PlanetKitMainRoomName' and it means the main room.
         * @see PlanetKitMainRoomName
         * @remark
         *  Conference call only.
         */
        virtual const WString& GetVideoSubgroupName() = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use IConferenceEvent.OnPeersAudioDescriptionUpdated")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see OnPeersAudioDescriptionUpdated
        */
        const String& GetAudioSubgroupName();


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use IConferenceEvent.OnPeersAudioDescriptionUpdated")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see OnPeersAudioDescriptionUpdated
        */
        const String& GetAudioTaggedSubgroupName();

        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later.")
        /**
         * @deprecated This will not be supported in 5.1 or later.
         * @see GetScreenShareState
         */
        ScreenShareStateResult GetScreenSharingState(const char * strSubgroupName);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.1 or later.
         */
        ScreenShareStateResult GetScreenShareState(const char * strSubgroupName);

        /**
         * Checks whether the peer is sharing screen.
         * @param szSubgroupName Subgroup name string which is encoded in UTF-16 and null-terminated.
         */
        virtual ScreenShareStateResult GetScreenShareState(const wchar_t* szSubgroupName) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later. Use GetAudioVolumeLevelSetting")
        /**
         * @deprecated This will not be supported in 5.1 or later.
         * @see GetAudioVolumeLevelSetting
         */
        VolumeResult GetVolumeSetting(const char * strSubgroupName);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         */
        VolumeResult GetAudioVolumeLevelSetting(const char * strSubgroupName);

        /**
         * Gets the peer's audio volume value.
         * @param szSubgroupName Subgroup name string which is encoded in UTF-16 and null-terminated.
         */
        virtual VolumeResult GetAudioVolumeLevelSetting(const wchar_t* szSubgroupName) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         */
        VideoStatusResult GetVideoStatus(const char * strSubgroupName);

        /**
         * Gets the peer's video status.
         * @param szSubgroupName Subgroup name string which is encoded in UTF-16 and null-terminated.
         */
        virtual VideoStatusResult GetVideoStatus(const wchar_t* sSubgroupName) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use GetCurrentVideoSubgroupName")
        /**
        * @deprecated This will not be supported in 5.2 or later.
        * @see GetCurrentVideoSubgroupName
        */
        const String& GetCurrentVideoSubgroup(bool & bIsSubgroup);

        /// Gets the current video subgroup.
        virtual const WString& GetCurrentVideoSubgroupName(bool& bIsSubgroup) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later.")
        /**
         * @deprecated This will not be supported in 5.1 or later.
         * @see GetCurrentScreenShareSubgroup
         */
        const String& GetCurrentScreenSharingSubgroup(bool & bIsSubgroup);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
        * @deprecated This will not be supported in 5.2 or later.
        * @see GetCurrentScreenShareSubgroupName
        */
        const String& GetCurrentScreenShareSubgroup(bool & bIsSubgroup);

        /// Gets the current screen share subgroup.
        virtual const WString& GetCurrentScreenShareSubgroupName(bool& bIsSubgroup) = 0;

        /**
         * Creates PeerControl
         * @remark 
         *  - Conference call only
         */
        virtual PeerControlPtr CreatePeerControl( ) = 0;

        /// Gets shared contents data
        virtual SharedContentsDataOptional GetSharedContentsData() = 0;
    };


    PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
    /**
     * @deprecated This will not be supported in 5.0 or later.
     */
    class PLANETKIT_API ConferencePeers : public Base
    {
    public :
        /// Get the peer of the index location in the container.
        virtual ConferencePeer* PeerAt(size_t idx) = 0;
        /// Get peer count.
        virtual size_t PeerCount() = 0;

    protected :
        virtual ~ConferencePeers() = default;
    };
};
