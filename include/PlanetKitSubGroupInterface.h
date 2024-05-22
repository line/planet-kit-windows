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
#include "PlanetKitUserId.h"
#include "IPlanetKitResultHandler.h"

#include "PlanetKitDataSessionInterface.h"
#include "PlanetKitVideoStatus.h"
#include "PlanetKitPeer.h"

namespace PlanetKit {
    constexpr wchar_t* PlanetKitMainRoomName = nullptr;

    /**
     * @brief Reasons for subgroup subscription failure
     */
    typedef enum ESubgroupSubscribeFailReason {
        /// Undefined
        PLNK_SUBGRP_SUBS_FAIL_REASON_UNDEFINED = 0,
        /// Timeout
        PLNK_SUBGRP_SUBS_FAIL_REASON_TIMEOUT = 1,
        /// An attempt to subscribe using a different attribute than the attributes of this subgroup failed.
        PLNK_SUBGRP_SUBS_FAIL_REASON_WRONG_ATTR = 2,
        /// The maximum number of subgroups are created in the server.
        PLNK_SUBGRP_SUBS_FAIL_REASON_OVER_MAX_SUBGRP_CNT = 3,
        /// The local user has already subscribed to this subgroup.
        PLNK_SUBGRP_SUBS_FAIL_REASON_ALREADY_SUBSCRIBED = 4,
        /// Unknown
        PLNK_SUBGRP_SUBS_FAIL_REASON_UNKNOWN = 1000

    } ESubgroupSubscribeFailReason;

    /**
     * @brief Reasons for subgroup unsubscription failure
     */
    typedef enum ESubgroupUnsubscribeFailReason 
    {
        /// Undefined
        PLNK_SUBGRP_UNSUBS_FAIL_REASON_UNDEFINED = 0,
        /// The local user is sending audio to this subgroup and can't unsubscribe.
        PLNK_SUBGRP_UNSUBS_FAIL_REASON_HAS_ACTIVE_AUDIO = 1,
        /// The local user is sending video to this subgroup and can't unsubscribe.
        PLNK_SUBGRP_UNSUBS_FAIL_REASON_HAS_ACTIVE_VIDEO = 2,
        /// This is a subgroup to which the local user has not subscribed.
        PLNK_SUBGRP_UNSUBS_FAIL_REASON_NOT_SUBSCRIBED = 3,
        /// The local user is sending screen share to this subgroup and can't unsubscribe.
        PLNK_SUBGRP_UNSUBS_FAIL_REASON_HAS_ACTIVE_SCREEN_SHARE = 4,
        /// Unknown
        PLNK_SUBGRP_UNSUBS_FAIL_REASON_UNKNOWN = 1000
    } ESubgroupUnsubscribeFailReason;

    /**
     * @brief Enum of the subgroup peer update type in Subgroup
     */
    typedef enum ESubgroupPeerUpdateType
    {
        /// None
        PLNK_SUBGRP_PEER_UPDATE_TYPE_NONE = 0,
        /// Public room
        PLNK_SUBGRP_PEER_UPDATE_TYPE_PUBLIC,
        /// Private room
        PLNK_SUBGRP_PEER_UPDATE_TYPE_PRIVATE,

    } ESubgroupPeerUpdateType;

    using SubscribeResult = void(*)(SubgroupPtr pSubgroup, bool bSuccess, ESubgroupSubscribeFailReason eReason, void* pUserData);
    using UnsubscribeResult = void(*)(SubgroupPtr pSubgroup, bool bSuccess, ESubgroupUnsubscribeFailReason eReason, void* pUserData);

    /**
     * Information class about Subgroup's attribute.
     */
    class PLANETKIT_API SubgroupAttribute : public Base {
    public :
        /// Checks whether video update is enabled for this subgroup.
        virtual bool IsEnableVideoUpdate() = 0;
        /// Checks whether the subgroup's received audio is silenced.
        virtual bool IsSilenced() = 0;
        /// Checks whether the subgroup's received audio auto volume control is enabled.
        virtual bool IsPeersAudioAutoVolumeControlFocused() = 0;
        /// Checks whether DataSession is enabled for this subgroup.
        virtual bool IsUsingDataSession() = 0;
        /// Gets the peer update type.
        virtual ESubgroupPeerUpdateType GetPeerUpdateType() = 0;
    };

    template class PLANETKIT_API AutoPtr<SubgroupAttribute>;
    typedef AutoPtr<SubgroupAttribute> SubgroupAttributePtr;

    class PLANETKIT_API Subgroup : public Base {
    public:
        /**
        * Gets the peer list.
        * @return Array of Peers
        */
        virtual bool GetPeerList(PeerArray& arrResult) = 0;

        /**
         * Gets the instance of subgroup's attribute..
         */
        virtual SubgroupAttributePtr GetAttribute() = 0;

        /**
        * Gets the current peer list length.
        * @return Length of peer list
        */
        virtual size_t GetTotalPeersCount() = 0;

        /**
        * Gets the subgroup name string which is encoded in UTF-16 and null-terminated.<br>This can be `NullOptional` that means `MainRoom`.
        * @return The subgroup name string.
        */
        virtual const WStringOptional& GetSubgroupName() = 0;

        /**
         * Gets the existing outbound data session.
         * @param nStreamId Stream ID of the data session to get.
         * @param pResult Result OutboundDataSession.
         * @return true on success, false if it does not exist.
         */
        virtual bool GetOutboundDataSession(int nStreamId, OutboundDataSessionPtr* pResult) = 0;
        
        /**
         * Gets the existing inbound data session.
         * @param nStreamId Stream ID of the data session to get.
         * @param pResult Result InboundDataSession.
         * @return true on success, false if it does not exist.
         */
        virtual bool GetInboundDataSession(int nStreamId, InboundDataSessionPtr* pResult) = 0;

        /**
         * Makes an outbound data session.
         * @param nStreamId Stream ID from 100 to 999
         * @param eType Data session type
         * @param pResultUserData You can specify data to be passed along when pDataSessionHandler is called.
         * @param pDataSessionHandler This is a callback handler that occurs for exception handling when an exception occurs during data transmission.
         * @return true on successful function call. The result must be checked.
         */
        virtual bool MakeOutboundDataSession(int nStreamId, EDataSessionType eType,
            NULLABLE void* pResultUserData, IOutboundDataSessionHandler* pDataSessionHandler
        ) = 0;

        /**
         * Makes an inbound data session.
         * @param nStreamId Stream ID from 100 to 999
         * @param pResultUserData You can specify data to be passed along when pDataSessionHandler is called.
         * @param pDataSessionHandler Specifies the callback handler that is called when receiving data or when an exception occurs.
         * @return true on successful function call. The result must be checked.
         */
        virtual bool MakeInboundDataSession(int nStreamId, NULLABLE void *pResultUserData, IInboundDataSessionHandler* pDataSessionHandler) = 0;

        /**
        * Unsupports an inbound data session.
        * @param nStreamId
        * @return true on success
        */
        virtual bool UnsupportInboundDataSession(DataSessionStreamIdT nStreamId) = 0;
    };

    class PLANETKIT_API SubgroupManager : public Base {
    public:
        /**
         * Subscribes to a Subgroup. If a subgroup exists, eUpdateType, bEnableVideoUpdate, and bUseDataSession must match the existing subgroup to join.
         * @param strSubgroupName Subgroup name string which is encoded in UTF-16 and null-terminated.
         * @param eUpdateType Update type
         * @param bEnableVideoUpdate The flag value of video update
         * @param bUseDataSession Whether to use data sessions
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         */
        virtual bool SubscribeSubgroup(const WString& strSubgroupName, ESubgroupPeerUpdateType eUpdateType,
            bool bEnableVideoUpdate, bool bUseDataSession, void* pUserData = nullptr, SubscribeResult pCallback = nullptr) = 0;

        /**
         * Unsubscribes from a Subgroup.
         * @param strSubgroupName Subgroup name string which is encoded in UTF-16 and null-terminated.
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         */
        virtual bool UnsubscribeSubgroup(const WString& strSubgroupName, void* pUserData = nullptr, UnsubscribeResult pCallback = nullptr) = 0;

        /**
         * Gets a Subgroup instance.
         * @param strSubgroupName Subgroup name string which is encoded in UTF-16 and null-terminated.
         * @return 
         *  - Subgroup instance.<br>
         *  - You can get SubgroupOptional(nullPtr) when SubgroupManager can't find a subgroup with the given szSubgroupName.
         */
        virtual SubgroupOptional GetSubgroup(const WString& strSubgroupName) = 0;

        /**
         * Gets the main room subgroup instance.
         * @return
         *  - Subgroup instance.<br>
         */
        virtual SubgroupPtr GetMainRoom() = 0;

        /**
         * Gets the Subgroup list.
         * @return Subgroup array
         */
        virtual bool GetSubgroupList(SubgroupArray& arrResult) = 0;

        /**
        * Gets the Subgroup list length.
        * @return true on success
        */
        virtual size_t GetSubgroupListLength() = 0;

        /**
         * Changes the audio destination to the designated subgroup.
         * @param strDestinationSubgroupName Subgroup name string which is encoded in UTF-16 and null-terminated.
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pCallback A callback function to be called after the API worked.
         * @return true on success
         */
        virtual bool ChangeMyAudioDestination(const WString& strDestinationSubgroupName, void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Changes the audio destination to the main room.
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pCallback A callback function to be called after the API worked.
         * @return true on success
         */
        virtual bool ChangeMyAudioDestinationToMainRoom(void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Tags the audio destination subgroup of the main room.
         * @param strTagSubgroupName Subgroup name string which is encoded in UTF-16 and null-terminated.
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         */
        virtual bool SetTagMyAudioOfMainRoom(const WString& strTagSubgroupName, void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Clears the tag set by SetTagMyAudioOfMainRoom.
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pCallback A callback function to be called after the API worked.
         * @return true on success
         */
        virtual bool ClearTagMyAudioOfMainRoom(void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Silences or unsilences the audio received from the designated Subgroup.
         * @param strSubgroupName Subgroup name string which is encoded in UTF-16 and null-terminated.<br>This can be `NullOptional` that means `MainRoom`.
         * @param bSilence The flag value of whether to silence or unsilence
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pCallback A callback function to be called after the API worked.
         * @return true on success
         */
        virtual bool SilencePeersAudio(const WStringOptional& strSubgroupName, bool bSilence, void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Enables auto volume control for designated Subgroups.
         * @param arrSubgroupNames Array of subgroup name string.
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pCallback A callback function to be called after the API worked.
         * @return true on success
         */
        virtual bool SetPeersAudioAutoVolumeControl(const WStringArray& arrSubgroupNames, void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Disables auto volume control.
         * @param pUserData User data to be passed when pCallback is called.
         * @param pCallback This is a callback function that can receive the result.
         * @return true on success
         */
        virtual bool ClearPeersAudioAutoVolumeControl(void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Sets the peer's volume.
         * @param pPeerId Peer ID.
         * @param bSetForAllSubgroups Whether to set the peer's volume for all subgroups. If false, provide the target subgroup name in szSubgroupName.
         * @param strSubgroupNameToApply Subgroup name string which is encoded in UTF-16 and null-terminated.<br>This can be `NullOptional` that means `MainRoom`.
         * @param unTalkerVolume Range [0:110]
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pCallback A callback function to be called after the API worked.
         * @return true on success
         */
        virtual bool SetPeerAudioVolumeLevelSetting(UserIdPtr pPeerId, bool bSetForAllSubgroups, const WStringOptional& strSubgroupNameToApply, unsigned char ucVolume, void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Gets the local user's current video subgroup name.
         * @return WStringOptional Video subgroup name and it can have no value and it means PlanetKitMainRoomName.
         */
        virtual WStringOptional GetMyVideoSubgroupName() = 0;

        /**
         * Changes the video destination to the designated subgroup.
         * @param strDestinationSubgroupName Subgroup name string which is encoded in UTF-16 and null-terminated.
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pCallback A callback function to be called after the API worked.
         * @return true on success
         */
        virtual bool ChangeMyVideoDestination(const WString& strDestinationSubgroupName, void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;

        /**
         * Changes the video destination to the main room.
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pCallback A callback function to be called after the API worked.
         * @return true on success
         */
        virtual bool ChangeMyVideoDestinationToMainRoom(void* pUserData = nullptr, ResultCallback pCallback = nullptr) = 0;
    };
}