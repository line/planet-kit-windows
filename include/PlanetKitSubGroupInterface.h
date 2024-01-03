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
#include "IPlanetKitResultHandler.h"
#include "PlanetKitDataSessionInterface.h"
#include "PlanetKitVideoStatus.h"
#include "PlanetKitUserId.h"
#include "PlanetKitPeer.h"

namespace PlanetKit
{

    constexpr wchar_t* PlanetKitMainRoomName = nullptr;

    /**
     * @brief Reasons for subgroup subscription failure
     */
    typedef enum ESubgroupSubscribeFailReason
    {
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


    class PLANETKIT_API ISubscribeSubgroupResultHandler
    {
    public:
        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         */
        void OnResult(Subgroup *pSubgroup, bool bSuccess, ESubgroupSubscribeFailReason eReason, void * pUserData);

        /**
         * Result of subscribing
         */
        virtual void OnResult(SubgroupPtr pSubgroup, bool bSuccess, ESubgroupSubscribeFailReason eReason, void * pUserData) = 0;
    };

    class PLANETKIT_API IUnsubscribeSubgroupResultHandler
    {
    public:
        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         */
        void OnResult(Subgroup *pSubgroup, bool bSuccess, ESubgroupUnsubscribeFailReason eReason, void * pUserData);

        /**
         * Result of unsubscribing
         */
        virtual void OnResult(SubgroupPtr pSubgroup, bool bSuccess, ESubgroupUnsubscribeFailReason eReason, void * pUserData) = 0;
    };

    PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use ConferencePeer class.")
    /**
     * @deprecated This will not be supported in 4.4 or later.
     * @see ConferencePeer
     */
    class SubgroupPeerInfo : public Base
    {
    public:
        virtual const char * UserId() = 0;
        virtual const char * ServiceId() = 0;

        virtual bool SendingVideo();
        virtual VideoStatus GetVideoStatus();
        virtual uint32_t AudioVolumeSetting();
    protected:
        virtual ~SubgroupPeerInfo() {}
    };

    PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
    /**
     * @deprecated This will not be supported in 5.2 or later.
     * @see SubgroupAttribute
     */
    class PLANETKIT_API SubgroupState {
    public:
        
    };

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

    typedef AutoPtr<SubgroupAttribute> SubgroupAttributePtr;

    class PLANETKIT_API Subgroup : public Base {
    public:

        PLANETKIT_DEPRECATED("This will not be supported in 4.4. Use GetPeerList(ConferencePeers*& pDstPeer)")
        /**
         * @deprecated This will not be supported in 4.4 or later.
         * @see ConferencePeer
         */
        bool GetPeerList(SubgroupPeerInfo **ppDstBuffer, size_t nBufferLength, size_t *nWrittenCount);

        PLANETKIT_DEPRECATED("This will not be supported in 5.0. Use PeerArray GetPeerList()")
        /**
         * @deprecated This will not be supported in 5.0 or later.
         * @see GetPeerList
         */
        bool GetPeerList(ConferencePeers*& pDstPeers);

        /**
        * Gets the peer list.
        * @return Array of Peers
        */
        virtual bool GetPeerList(PeerArray& arrResult) = 0;


        PLANETKIT_DEPRECATED("This will not be supported in 5.2. Use GetAttribute")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see GetAttribute
         */
        SubgroupState* GetState();

        /**
         * Gets the instance of subgroup's attribute..
         */
        virtual SubgroupAttributePtr GetAttribute() = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2. Use GetTotalPeersCount")
        /**
        * @deprecated This will not be supported in 5.2 or later.
        * @see GetTotalPeersCount
        */
        size_t GetPeerListLength();

        /**
        * Gets the current peer list length.
        * @return Length of peer list
        */
        virtual size_t GetTotalPeersCount() = 0;


        PLANETKIT_DEPRECATED("This will not be supported in 4.4. Use GetState()->IsSilenced")
        /**
        * @deprecated This will not be supported in 4.4 or later.
        * @see Subgroup
        */
        bool IsAudioRecvSilenced();


        PLANETKIT_DEPRECATED("This will not be supported in 4.4. Use GetState()->IsAutoVolumeFocused")
        /**
        * @deprecated This will not be supported in 4.4 or later.
        * @see Subgroup
        */
        bool IsAudioRecvAutoVolumeControlEnabled();


        /**
        * Gets the subgroup name string which is encoded in UTF-16 and null-terminated.
        * @return The subgroup name string.
        */
        virtual const wchar_t* GetSubgroupName() = 0;


        PLANETKIT_DEPRECATED("This will not be supported in 5.2. Use SubgroupAttribute::GetPeerUpdateType")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see SubgroupAttribute::GetPeerUpdateType
         */
        ESubgroupPeerUpdateType GetPeerUpdateType();


        PLANETKIT_DEPRECATED("This will not be supported in 4.4. Use GetState()->IsVideoUpdate")
        /**
        * @deprecated This will not be supported in 4.4 or later.
        * @see Subgroup
        */
        bool EnableVideoUpdate();

        PLANETKIT_DEPRECATED("This will not be supported in 4.4. Use GetState()->IsSupportedDataSession")
        /**
        * @deprecated This will not be supported in 4.4 or later.
        * @see Subgroup
        */
        bool DataSession();


        PLANETKIT_DEPRECATED("This will not be supported in 4.4. If it is not subscribed then GetState() will be nullptr")
        /**
        * @deprecated This will not be supported in 4.4 or later.
        * @see Subgroup
        */
        bool IsSubscribed();

        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later.")
        /**
         * @deprecated This will not be supported in 5.1 or later.
         */
        bool MakeSendDataSession(int nStreamId, EDataSessionType eType,
            NULLABLE void* pResultUserData, NULLABLE IDataSessionHandler* pResultHandler,
            void* pExceptionUserData, IDataSessionExceptionHandler* pExceptionHandler
        );

        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later. Use MakeReceiveDataSession.")
        /**
         * @deprecated This will not be supported in 5.1 or later.
         * @see MakeReceiveDataSession
         */
        bool MakeRecvDataSession(int nStreamId, IDataSessionReceiver* pIDataSessionReceiver,
            NULLABLE void* pResultUserData, NULLABLE IDataSessionHandler* pResultHandler,
            void* pExceptionUserData, IDataSessionExceptionHandler* pExceptionHandler);

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

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
        * @deprecated This will not be supported in 5.2 or later.
        * @see MakeOutboundDataSession
        */
        bool MakeSendDataSession(int nStreamId, EDataSessionType eType,
            NULLABLE void* pResultUserData, ISendDataSessionHandler* pSendDataSessionHandler
        );

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


        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
        * @deprecated This will not be supported in 5.2 or later.
        * @see MakeInboundDataSession
        */
        bool MakeReceiveDataSession(int nStreamId, NULLABLE void *pResultUserData, IReceiveDataSessionHandler* pReceiveDataSessionHandler);

        /**
         * Makes an inbound data session.
         * @param nStreamId Stream ID from 100 to 999
         * @param pResultUserData You can specify data to be passed along when pDataSessionHandler is called.
         * @param pDataSessionHandler Specifies the callback handler that is called when receiving data or when an exception occurs.
         * @return true on successful function call. The result must be checked.
         */
        virtual bool MakeInboundDataSession(int nStreamId, NULLABLE void *pResultUserData, IInboundDataSessionHandler* pDataSessionHandler) = 0;


        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
        * @deprecated This will not be supported in 5.2 or later.
        * @see UnsupportInboundDataSession
        */
        bool UnsupportRecvDataSession(DataSessionStreamIdT nStreamId);

        /**
        * Unsupports an inbound data session.
        * @param nStreamId
        * @return true on success
        */
        virtual bool UnsupportInboundDataSession(DataSessionStreamIdT nStreamId) = 0;
    };


    PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use SubgroupManager")
    /**
     * @deprecated This will not be supported in 4.4 or later.
     * @see SubgroupManager
     */
    class PLANETKIT_API SubgroupInterface
    {

    };

    class PLANETKIT_API SubgroupManager : public Base {
    public:

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         */
        bool SubscribeSubgroup(const char *szSubgroupName, ESubgroupPeerUpdateType eUpdateType,
            bool bEnableVideoUpdate, bool bPdtpDataSession, void *pResultUserData, ISubscribeSubgroupResultHandler *pResultHandler);

        /**
         * Subscribes to a Subgroup. If a subgroup exists, eUpdateType, bEnableVideoUpdate, and bUseDataSession must match the existing subgroup to join.
         * @param szSubgroupName Subgroup name string which is encoded in UTF-16 and null-terminated.
         * @param eUpdateType Update type
         * @param bEnableVideoUpdate The flag value of video update
         * @param bUseDataSession Whether to use data sessions
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pCallback A callback function to be called after the API worked.
         * @return true on success
         */
        virtual bool SubscribeSubgroup(const wchar_t* szSubgroupName, ESubgroupPeerUpdateType eUpdateType,
            bool bEnableVideoUpdate, bool bUseDataSession, void* pUserData, ISubscribeSubgroupResultHandler* pCallback) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         */
        bool UnsubscribeSubgroup(const char *szSubgroupName, void *pResultUserData, IUnsubscribeSubgroupResultHandler *pResultHandler);

        /**
         * Unsubscribes from a Subgroup.
         * @param szSubgroupName Subgroup name string which is encoded in UTF-16 and null-terminated.
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pCallback A callback function to be called after the API worked.
         * @return true on success
         */
        virtual bool UnsubscribeSubgroup(const wchar_t* szSubgroupName, void* pUserData, IUnsubscribeSubgroupResultHandler* pCallback) = 0;


        PLANETKIT_DEPRECATED("This will not be supported in 4.4 or later. Use GetSubgroup and pass nullptr as szSubgroupName")
        /**
         * @deprecated This will not be supported in 4.4 or later.
         * @see bool GetSubgroupManager
         */
        bool GetMainSubgroup(Subgroup** ppSubgroup);

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use SubgroupOptional GetSubgroup(const char *szSubgroupName)")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see bool GetSubgroup
        */
        bool GetSubgroup(const char *szSubgroupName, Subgroup** ppSubgroup);

        /**
         * Gets a Subgroup instance.
         * @param szSubgroupName Subgroup name string which is encoded in UTF-16 and null-terminated.
         * @return 
         *  - Subgroup instance.<br>
         *  - You can get SubgroupOptional(nullPtr) when SubgroupManager can't find a subgroup with the given szSubgroupName.
         */
        virtual SubgroupOptional GetSubgroup(const wchar_t* szSubgroupName) = 0;

        /**
         * Gets the main room subgroup instance.
         * @return
         *  - Subgroup instance.<br>
         */
        virtual SubgroupPtr GetMainRoom() = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use SubgroupArray GetSubgroupList()")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see bool GetSubgroupList
        */
        bool GetSubgroupList(Subgroup** pDstBuffer, size_t nBufferLength, size_t *pWrittenCount);

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


        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later.")
        /**
        * @deprecated This will not be supported in 5.1 or later.
        * @see OnMyAudioDescriptionUpdated
        */
        const String& GetMyAudioSubgroupName();


        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later.")
        /**
        * @deprecated This will not be supported in 5.1 or later.
        * @see OnMyAudioDescriptionUpdated
        */
        const String& GetMyAudioTaggedSubgroupName();


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use bool ChangeMyAudioSend()")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see bool ChangeMyAudioSend
        */
        bool AudioSendChangeSubgroup(const char *szDstSubgroupName, void *pResultUserData, IResultHandler *pResultHandler);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
        * @deprecated This will not be supported in 5.2 or later.
        * @see Subgroup : ChangeMyAudioDestination
        * @see Mainroom : ChangeMyAudioDestinationToMainRoom
        */
        bool ChangeMyAudioSend(const char *szDstSubgroupName, void *pResultUserData, IResultHandler *pResultHandler);

        /**
         * Changes the audio destination to the designated subgroup.
         * @param szSubgroupName Subgroup name string which is encoded in UTF-16 and null-terminated.
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pCallback A callback function to be called after the API worked.
         * @return true on success
         */
        virtual bool ChangeMyAudioDestination(const wchar_t* szSubgroupName, void* pUserData, IResultHandler* pCallback) = 0;

        /**
         * Changes the audio destination to the main room.
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pCallback A callback function to be called after the API worked.
         * @return true on success
         */
        virtual bool ChangeMyAudioDestinationToMainRoom(void* pUserData, IResultHandler* pCallback) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use bool TagMainRoomAudioSend()")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see bool TagMainRoomAudioSend
        */
        bool AudioSendTagSubgroupOfMainRoom(const char *szTagSubgroupName, void *pResultUserData, IResultHandler *pResultHandler);


        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use bool SetTagMyAudioOfMainRoom()")
        /**
        * @deprecated This will not be supported in 5.2 or later.
        * @see bool SetTagMyAudioOfMainRoom
        */
        bool TagMainRoomAudioSend(const char *szTagSubgroupName, void *pResultUserData, IResultHandler *pResultHandler);

        /**
         * Tags the audio destination subgroup of the main room.
         * @param szSubgroupName Subgroup name string which is encoded in UTF-16 and null-terminated.
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pCallback A callback function to be called after the API worked.
         * @return true on success
         */
        virtual bool SetTagMyAudioOfMainRoom(const wchar_t* szSubgroupName, void* pUserData, IResultHandler* pCallback) = 0;

        /**
         * Clears the tag set by SetTagMyAudioOfMainRoom.
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pCallback A callback function to be called after the API worked.
         * @return true on success
         */
        virtual bool ClearTagMyAudioOfMainRoom(void* pUserData, IResultHandler* pCallback) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use bool silenceAudio()")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see bool SilenceAudio
        */
        bool AudioRecvSilenceSubgroup(const char *szSubgroupName, bool bSilence, void *pResultUserData, IResultHandler *pResultHandler);


        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use bool SilencePeersAudio()")
        /**
        * @deprecated This will not be supported in 5.2 or later.
        * @see bool SilencePeersAudio
        */
        bool SilenceAudio(const char *szSubgroupName, bool bSilence, void *pResultUserData, IResultHandler *pResultHandler);

        /**
         * Silences or unsilences the audio received from the designated Subgroup.
         * @param szSubgroupName Subgroup name string which is encoded in UTF-16 and null-terminated.
         * @param bSilence The flag value of whether to silence or unsilence
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pCallback A callback function to be called after the API worked.
         * @return true on success
         */
        virtual bool SilencePeersAudio(const wchar_t* szSubgroupName, bool bSilence, void* pUserData, IResultHandler* pCallback) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use bool EnableAutoVolumeControl()")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see bool EnableAutoVolumeControl
        */
        bool AudioRecvEnableAutoVolumeControl(const char **szFocusSubgroups, size_t nFocusSubgroupCnt,
            void *pResultUserData, IResultHandler *pResultHandler);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use bool SetPeersAudioAutoVolumeControl()")
        /**
        * @deprecated This will not be supported in 5.2 or later.
        * @see bool SetPeersAudioAutoVolumeControl
        */
        bool EnableAutoVolumeControl(const char **szFocusSubgroups, size_t nFocusSubgroupCnt,
            void *pResultUserData, IResultHandler *pResultHandler);

        /**
         * Enables auto volume control for designated Subgroups.
         * @param arrSubgroupNames Array of subgroup name string.
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pCallback A callback function to be called after the API worked.
         * @return true on success
         */
        virtual bool SetPeersAudioAutoVolumeControl(const WStringArray& arrSubgroupNames, void* pUserData, IResultHandler* pCallback) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use bool DisableAutoVolumeControl()")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see bool DisableAutoVolumeControl
        */
        bool AudioRecvDisableAutoVolumeControl(void *pResultUserData, IResultHandler *pResultHandler);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use bool ClearPeersAudioAutoVolumeControl()")
        /**
        * @deprecated This will not be supported in 5.2 or later.
        * @see bool ClearPeersAudioAutoVolumeControl
        */
        bool DisableAutoVolumeControl(void *pResultUserData, IResultHandler *pResultHandler);

        /**
        * Disables auto volume control.
        * @param pResultUserData User's data that will be passed along when the callback function is called.
        * @param pResultHandler A callback function to be called after the API worked.
        * @return true on success
        */
        virtual bool ClearPeersAudioAutoVolumeControl(void *pResultUserData, IResultHandler *pResultHandler) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use bool setPeerVolumeSetting")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see bool SetPeerVolumeSetting
        */
        bool AudioRecvSetPeerVolume(const char *szPeerId, const char *szPeerServiceId, 
            bool bSetForAllSubgroups, const char *szSubgroupNameToApply, byte unTalkerVolume,
            void *pResultUserData, IResultHandler *pResultHandler);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use SetPeerAudioVolumeLevelSetting")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see SetPeerAudioVolumeLevelSetting
         */
        bool SetPeerVolumeSetting(const char *szPeerId, const char *szPeerServiceId,
            bool bSetForAllSubgroups, const char *szSubgroupNameToApply, unsigned char ucVolume,
            void *pResultUserData, IResultHandler *pResultHandler);

        /**
         * Sets the peer's volume.
         * @param pPeerId Peer ID.
         * @param bSetForAllSubgroups Whether to set the peer's volume for all subgroups. If false, provide the target subgroup name in szSubgroupName.
         * @param szSubgroupName Subgroup name string which is encoded in UTF-16 and null-terminated. PlanetKitMainRoomName means 'main room'.
         * @param unTalkerVolume Range [0:110]
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pCallback A callback function to be called after the API worked.
         * @return true on success
         */
        virtual bool SetPeerAudioVolumeLevelSetting(
            UserIdPtr pPeerId,
            bool bSetForAllSubgroups,
            const wchar_t* szSubgroupName,
            unsigned char ucVolume,
            void* pUserData,
            IResultHandler* pCallback
        ) = 0;

        /**
        * Gets the local user's current video subgroup name.
        * @return Video subgroup name in null terminated string
        */
        virtual const WString& GetMyVideoSubgroupName() = 0;



        PLANETKIT_DEPRECATED("This will not be supported in 5.0.")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        */
        const String& GetMyVideoTaggedSubgroupName();



        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
        * @deprecated This will not be supported in 5.2 or later.
        * @see subgroup : ChangeMyVideoDestination
        * @see mainroom : ChangeMyVideoDestinationToMainRoom
        */
        bool VideoSendChangeSubgroup(const char *szDstSubgroupName, void *pResultUserData, IResultHandler *pResultHandler);


        /**
         * Changes the video destination to the designated subgroup.
         * @param szSubgroupName Subgroup name string which is encoded in UTF-16 and null-terminated.
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pCallback A callback function to be called after the API worked.
         * @return true on success
         */
        virtual bool ChangeMyVideoDestination(const wchar_t* szSubgroupName, void* pUserData, IResultHandler* pCallback) = 0;

        /**
         * Changes the video destination to the main room.
         * @param pUserData User's data that will be passed along when the callback function is called.
         * @param pCallback A callback function to be called after the API worked.
         * @return true on success
         */
        virtual bool ChangeMyVideoDestinationToMainRoom(void* pUserData, IResultHandler* pCallback) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.0.")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        */
        bool VideoSendTagSubgroupOfMainRoom(const char *szTagSubgroupName, void *pResultUserData, IResultHandler *pResultHandler);
    };
}