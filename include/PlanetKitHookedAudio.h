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
#include "PlanetKitAudioDefine.h"

namespace PlanetKit {
    /**
     * Defines the audio data used for the local user's audio modification feature.<br>
     * The audio is received through IAudioHook, and the modified audio is applied using SetAudioData.
     */
    class PLANETKIT_API HookedAudio : public Base {
    public:
        /**
         * Sample rate of audio data.
         */
        virtual const unsigned int GetSampleRate() = 0;

        /**
         * The number of channels.
         */
        virtual const unsigned int GetChannel() = 0;

        /**
         * The sample type.
         */
        virtual const EAudioSampleType GetAudioSampleType() = 0;

        /**
         * The sample count for each channel.
         */
        virtual const unsigned int GetSampleCount() = 0;

        /**
         * The sequence number of audio data.
         */
        virtual const unsigned long long GetSequenceNumber() = 0;

        /**
         * Sets raw data of audio.
         * @param pBuffer Raw data of audio.
         * @param unBufferSize Raw data buffer size.
         * @return true on success
         * @remark
         *  - If you want to modify the audio data, you can set the modified data using SetAudioData.<br>
         *  - The audio data size is determined by the sample rate, channel, sample count, and sample type.<br>
         *  - Currently, the sample rate, channel, sample count, and sample type are fixed values, so the buffer size cannot be changed.<br>
         *  - Therefore, even if you modify the data obtained with GetAudioData and set it with SetAudioData, the buffer size must match the size of the audio data obtained with GetAudioData.
         */
        virtual bool SetAudioData(const PlanetKitByte* pBuffer, unsigned int unBufferSize) = 0;

        /*
         * Gets raw data of audio.
         */
        virtual const AudioData& GetAudioData() = 0;
    };

    typedef AutoPtr<HookedAudio> HookedAudioPtr;
}