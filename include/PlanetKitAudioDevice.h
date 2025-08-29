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

#include "PlanetKitTypes.h"
#include "PlanetKitAudioCommon.h"

namespace PlanetKit
{
    
    class PLANETKIT_API IAudioDeviceInputDelegate {
    public:
        virtual bool DidCapture(const SAudioData *pPlanetKitAudioData) = 0;
    };

    class PLANETKIT_API IAudioDeviceOutputDelegate {
    public:
        virtual bool WillPlay(SAudioData *pPlanetKitAudioData) = 0;
    };

    class PLANETKIT_API IAudioDeviceVolumeChangedEvent {
    public:
        virtual void OnNotify(AudioDevice *pAudioDevice, const SAudioEndpointVolumeInfo *pInfo) = 0;
    };


    class PLANETKIT_API AudioDevice : public Base {
    public:
        /**
         * Starts the audio device.
         * @return true on success
         */
        virtual bool Start() = 0;

        /**
         * Checks whether the audio device is running.
         * @return true on success
         */
        virtual bool IsRunning() = 0;

        /**
         * Gets the audio device type.
         * @return EAudioDeviceType
         */
        virtual EAudioDeviceType GetDeviceType() = 0;

        /**
         * Sets the audio device volume.
         * @param fVolume Volume in the range [0.0F : 1.0F]
         * @return true on success
         */
        virtual bool  SetDeviceVolume(float fVolume) = 0;
        
        /**
         * Gets the audio device volume.
         * @param fVolume Buffer to store the volume value in the range [0.0F : 1.0F]
         * @return true on success
         */
        virtual bool  GetDeviceVolume(float *fVolume) = 0;
        
        /**
         * Registers an audio input delegate to the audio input device.
         * @param pAudioDeviceInputDelegate Audio delegate to be registered.
         * @return true on success
         */
        virtual bool RegisterAudioDeviceDelegate(IAudioDeviceInputDelegate* pDelegate) = 0;

        /**
         * Registers an audio output delegate to the audio output device.
         * @param pAudioDeviceOutputDelegate Audio delegate to be registered.
         * @return true on success
         */
        virtual bool RegisterAudioDeviceDelegate(IAudioDeviceOutputDelegate* pDelegate) = 0;

        /**
         * Deregisters an audio input delegate from the audio input device.
         * @param pAudioDeviceInputDelegate Audio delegate to be deregistered.
         * @return true on success
         */
        virtual bool DeregisterAudioDeviceDelegate(IAudioDeviceInputDelegate* pDelegate) = 0;

        /**
         * Deregisters an audio output delegate from the audio output device.
         * @param pAudioDeviceOutputDelegate Audio delegate to be deregistered.
         * @return true on success
         */
        virtual bool DeregisterAudioDeviceDelegate(IAudioDeviceOutputDelegate* pDelegate) = 0;

        /**
         * Gets the peak value of the audio device.
         * @param fVolume Buffer to store the meter value in range [0:1]
         * @return true on success
         */
        virtual bool GetPeakValue(float *fVolume) {
            UNREFERENCED_PARAMETER(fVolume);

            return false;
        }

        /**
         * Adds IAudioDeviceVolumeChangedEvent to the audio device.
         * @param pEvent Volume change event listener to add
         * @return true on success
         */
        virtual bool AddVolumeChangedEvent(IAudioDeviceVolumeChangedEvent *pEvent) = 0;

        /**
         * Removes IAudioDeviceVolumeChangedEvent from the audio device.
         * @param pEvent Volume change event listener to remove
         * @return true on success
         */
        virtual bool RemoveVolumeChangedEvent(IAudioDeviceVolumeChangedEvent *pEvent) = 0;

        /**
         * Plays the local audio file.
         * @param strFilePath Audio file path
         * @param unLoop Number of times to repeat playing the audio file
         */
        virtual bool PlayFile(const WString& strFilePath, unsigned int unLoop) = 0;

        /**
         * Stops playing the audio file.
         */
        virtual bool StopPlay() = 0;

        /**
         * Gets device information.
         */
        virtual void GetDeviceInfo(AudioDeviceInfoPtr* pResult) = 0;
    };
}