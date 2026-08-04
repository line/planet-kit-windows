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

#include "PlanetKitSpeaker.h"

namespace PlanetKit {
    class CustomSpeaker;
    using CustomSpeakerPtr = SharedPtr<CustomSpeaker>;

    class CustomSpeaker : public Speaker {
    public:
        virtual ~CustomSpeaker() {};

        virtual bool IsCustomSpeaker() override{ return true; }

        virtual bool RegisterSpeakerEvent(SpeakerEventPtr pEvent) override {
            m_pSpeakerEvent = pEvent;
            return true;
        }

        virtual bool DeregisterSpeakerEvent(SpeakerEventPtr pEvent) override {
            PLNK_UNREFERENCED_PARAMETER(pEvent);
            m_pSpeakerEvent = nullptr;
            return true;
        }

        /**
         * Pulls audio data from the PlanetKit.
         * @param audioData Audio data.
         * @return true on success
         * @remark To implement custom audio and pull audio data from a call or conference session, you need to call the respective function.
         * @remark For optimal performance, it is recommended to set the `unAudioDataSamplingRate` member (in Hz) of SAudioData
         *         to one of the following values: 16000, 32000, or 48000.
         * @remark The caller must initialize the following SAudioData fields before calling this function;
         *         PlanetKit fills `ucBuffer` with audio data matching them:
         *         - `eAudioDataSampleFormat` — output sample format (FLOAT_32 or SHORT16).
         *         - `unAudioDataSampleCount` — number of samples to pull.
         *         - `unAudioDataSamplingRate` — sample rate in Hz.
         *         - `ucBuffer` / `unBufferSize` — destination buffer. `unBufferSize` must be at least
         *           `unAudioDataSampleCount * (eAudioDataSampleFormat == SHORT16 ? sizeof(short) : sizeof(float))`.
         */
        virtual bool PullAudioData(SAudioData& audioData) {
            if (m_pSpeakerEvent.hasValue() == false) {
                return false;
            }

            return m_pSpeakerEvent->WillPlay(audioData);
        }

    protected:
        SpeakerEventPtr m_pSpeakerEvent;
    };
}