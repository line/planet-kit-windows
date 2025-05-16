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

#include "PlanetKitSubgroup.h"

namespace PlanetKit {
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

    typedef AutoPtr<SubgroupManager> SubgroupManagerPtr;
};