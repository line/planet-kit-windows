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

#include "PlanetKitMic.h"

namespace PlanetKit {
    class CustomMic;
    typedef SharedPtr<CustomMic> CustomMicPtr;

    class CustomMic : public Mic {
    public:
        virtual ~CustomMic() {};

        virtual bool IsCustomMic() override{ return true; }

        virtual bool RegisterMicEvent(MicEventPtr pEvent) override {
            m_pMicEvent = pEvent;
            return true;
        }

        virtual bool DeregisterMicEvent(MicEventPtr pEvent) override {
            m_pMicEvent = nullptr;
            return true;
        }

        /**
         * Puts audio data to the PlanetKit.
         * @param audioData Audio data.
         * @return true on success
         * @remark To implement custom microphone and put audio data to a call or conference session, you need to call the respective function.
         */
        bool PutAudioData(SAudioData& audioData) {
            if (m_pMicEvent.hasValue() == false) {
                return false;
            }

            return m_pMicEvent->DidCapture(audioData);
        }
    protected:
        MicEventPtr m_pMicEvent;
    };
}