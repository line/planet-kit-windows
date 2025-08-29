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

#include "PlanetKitSharedPtr.hpp"
#include "PlanetKit.h"
#include "PlanetKitAudioCommon.h"
#include "PlanetkitCustomSpeaker.h"
#include "planetkitCustomMic.h"
#include "IPlanetKitMicExceptionEvent.h"
#include "IPlanetKitMicPreviewEvent.h"
#include "PlanetKitAudioDeviceInfo.h"
#include "IPlanetKitAudioVolumeLevelChangedEvent.h"

#include "IPlanetKitAudioDeviceEvent.h"

namespace PlanetKit {
    class PLANETKIT_API AudioManager {
    public:
        virtual ~AudioManager() { }

        /**
         * Retrieves the list of currently available microphones.
         * @param audioDeviceInfoArray List of currently available microphones.
         * @return true on success
         */
        virtual bool GetMicList(AudioDeviceInfoArray& audioDeviceInfoArray) = 0;

        /**
         * Retrieves the list of currently available speakers.
         * @param audioDeviceInfoArray List of currently available speakers.
         * @return true on success
         */
        virtual bool GetSpeakerList(AudioDeviceInfoArray& audioDeviceInfoArray) = 0;

        /**
         * Changes the currently active microphone.
         * @param pInfo Information about the device to be changed.
         * @return The changed device is returned.
         * @remark Setting the microphone to nullptr indicates "No microphone in use."
         *         If you pass the device returned after setting the microphone to nullptr to a call or a conference, it will be connected in a state with no microphone in use.
         */
        virtual MicOptional ChangeMic(AudioDeviceInfoPtr pInfo = nullptr) = 0;

        /**
         * Switches to use a custom microphone.
         * @param pCustomMic Custom microphone.
         * @return The selected custom device is returned.
         */
        virtual MicOptional ChangeMic(CustomMicPtr pCustomMic) = 0;

        /**
         * Changes the currently active speaker.
         * @param pInfo Information about the device to be changed.
         * @return The changed device is returned.
         * @remark Setting the speaker to nullptr indicates "No speaker in use."
         *         If you pass the device returned after setting the speaker to nullptr to a call or a conference, it will be connected in a state with no speaker in use.
         */
        virtual SpeakerOptional ChangeSpeaker(AudioDeviceInfoPtr pInfo = nullptr) = 0;

        /**
         * Switches to use a custom speaker.
         * @param pCustomMic Custom microphone.
         * @return The selected custom device is returned.
         */
        virtual SpeakerOptional ChangeSpeaker(CustomSpeakerPtr pCustomSpeaker) = 0;

        /**
         * Retrieves the default microphone information of the current system.
         * @return Default system microphone information.
         */
        virtual AudioDeviceInfoOptional GetDefaultMicInfo() = 0;

        /**
         * Retrieves the default speaker information of the current system.
         * @return Default system speaker information.
         */
        virtual AudioDeviceInfoOptional GetDefaultSpeakerInfo() = 0;

        /**
         * Registers an event to be notified of device changes.
         * @param pEvent Event to be notified of device changes.
         * @return true on success
         */
        virtual bool RegisterAudioDeviceEvent(IAudioDeviceEvent* pEvent) = 0;

        /**
         * Deregisters an event to be notified of device changes.
         * @return true on success
         */
        virtual bool DeregisterAudioDeviceEvent() = 0;

        /**
         * Retrieves the currently active speaker.
         * @return Active speaker.
         * If no speaker device is selected, a NullOptional is returned.
         */
        virtual SpeakerOptional GetCurrentSpeaker() = 0;

        /**
         * Retrieves the currently active microphone.
         * @return Active microphone.
         * If no microphone device is selected, a NullOptional is returned.
         */
        virtual MicOptional GetCurrentMic() = 0;

        /**
         * Registers an event to receive exceptions occurring during microphone device usage.
         * @param pMicExceptionEvent Microphone device exception event.
         * @return true on success
         */
        virtual bool RegisterMicExceptionEvent(MicExceptionEventPtr pMicExceptionEvent) = 0;

        /**
         * Deregisters an event to receive exceptions occurring during microphone device usage.
         * @return true on success
         */
        virtual bool DeregisterMicExceptionEvent() = 0;

        /**
         * Registers and starts a preview to check the currently selected microphone device.
         * @param pMicPreviewEvent Event for receiving the volume level incoming to the microphone device.
         * @param unInterval Interval for receiving volume events.(in milliseconds)
         * @return true on success
         * @remark Only one event can be registered for preview, and it cannot be executed redundantly. Therefore, if executed a second time, it returns false.
         */
        virtual bool StartMicPreview(MicPreviewEventPtr pMicPreviewEvent, unsigned int unInterval) = 0;

        /**
         * Deregisters and stops a preview to check the currently selected microphone device.
         * @return true on success
           */
        virtual bool StopMicPreview() = 0;
    };

    typedef SharedPtr<AudioManager> AudioManagerPtr;
}