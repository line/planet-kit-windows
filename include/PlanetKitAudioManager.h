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
#include "PlanetKitAudioCommon.h"
#include "PlanetKitAudioDevice.h"

namespace PlanetKit 
{
    /**
     * Event listeners to notify you of audio device changes
     */
    class PLANETKIT_API IAudioDeviceEvent
    {
    public:
        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later.")
        /**
         * @deprecated This will not be supported in 5.1 or later.
         */
        void OnDefaultAudioDeviceChanged(SAudioDeviceInfo *pAudioDeviceInfo);

        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later.")
        /**
         * @deprecated This will not be supported in 5.1 or later.
         */
        void OnAudioDeviceAdded(SAudioDeviceInfo *pAudioDeviceInfo);

        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later.")
        /**
         * @deprecated This will not be supported in 5.1 or later.
         */
        void OnAudioDeviceRemoved(SAudioDeviceInfo *pAudioDeviceInfo);

        /// Called when the default audio device is changed.
        virtual void OnDefaultAudioDeviceChanged(AudioDeviceInfoPtr pAudioDeviceInfo) = 0;
        /// Called when an audio device is added.
        virtual void OnAudioDeviceAdded(AudioDeviceInfoPtr pAudioDeviceInfo) = 0;
        /// Called when an audio device is removed.
        virtual void OnAudioDeviceRemoved(AudioDeviceInfoPtr pAudioDeviceInfo) = 0;

    };


    class PLANETKIT_API AudioManager : public Base
    {
    public:
        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later.")
        /**
         * @deprecated This will not be supported in 5.1 or later.
         */
        bool CopySAudioDeviceInfo(SAudioDeviceInfo *pDstSAudioDeviceInfo, const SAudioDeviceInfo *pSrcSAudioDeviceInfo);

        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later.")
        /**
         * @deprecated This will not be supported in 5.1 or later.
         * @see GetAudioInputDeviceList
         */
        AudioDevicePtr CreateAudioDevice(SAudioDeviceInfo *pInfo);


        /**
        * Creates an audio device.
        * @param pInfo
        * @return Created audio device object
        */
        virtual AudioDevicePtr CreateAudioDevice(AudioDeviceInfoPtr pInfo) = 0;

        /**
         * Creates the default input device.
         * @return Created input device object
         */
        virtual AudioDevicePtr CreateDefaultInputDevice() = 0;

        /**
         * Creates the default output device.
         * @return Created output device object
         */
        virtual AudioDevicePtr CreateDefaultOutputDevice( ) = 0;


        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later.")
        /**
         * @deprecated This will not be supported in 5.1 or later.
         * @see GetAudioInputDeviceList
         */
        bool GetAudioInputDeviceInfoList(SAudioDeviceInfo *pInputDeviceInfoListBuffer, size_t nBufferSize, size_t *pAudioInputDeviceCount);

        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later.")
        /**
         * @deprecated This will not be supported in 5.1 or later.
         * @see GetAudioOutputDeviceList
         */
        bool GetAudioOutputDeviceInfoList(SAudioDeviceInfo *pOutputDeviceInfoListBuffer, size_t nBufferSize, size_t *pAudioOutputDeviceCount);

        /**
        * Gets the available audio input device list.
        * @param pResultArray Array of SAudioDeviceInfo.
        * @return true on success
        */
        virtual bool GetAudioInputDeviceList(AudioDeviceInfoArray* pResultArray) = 0;

        /**
        * Gets the available audio output device list.
        * @param pResultArray Array of SAudioDeviceInfo.
        * @return true on success
        */
        virtual bool GetAudioOutputDeviceList(AudioDeviceInfoArray* pResultArray) = 0;


        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later.")
        /**
         * @deprecated This will not be supported in 5.1 or later.
         */
        bool GetDefaultAudioInputDeviceInfo(SAudioDeviceInfo* pAudioDeviceInfo);

        /**
        * Gets the default audio input device.
        * @param pAudioDeviceInfo Buffer to store default audio input device information. Must not be NULL.
        * @return true on success
        */
        virtual bool GetDefaultAudioInputDeviceInfo(AudioDeviceInfoPtr* pAudioDeviceInfo) = 0;


        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later.")
        /**
         * @deprecated This will not be supported in 5.1 or later.
         */
        bool GetDefaultAudioOutputDeviceInfo(SAudioDeviceInfo* pAudioDeviceInfo);

        /**
        * Gets the default audio output device.
        * @param pAudioDeviceInfo Buffer to store default audio output device information. Must not be NULL.
        * @return true on success
        */
        virtual bool GetDefaultAudioOutputDeviceInfo(AudioDeviceInfoPtr* pAudioDeviceInfo) = 0;


        /**
        * Registers an audio device event delegate.
        * @param pEvent
        * @return true on success
        */
        virtual bool RegisterAudioDeviceEvent(IAudioDeviceEvent* pEvent) = 0;


        /**
        * Deregisters the audio device event delegate.
        * @return true on success
        */
        virtual bool DeregisterAudioDeviceEvent() = 0;
    };
}