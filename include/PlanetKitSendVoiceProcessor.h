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

#include "PlanetKitAudioCommon.h"
#include "IPlanetKitResultHandler.h"

namespace PlanetKit
{
    class PLANETKIT_API SendVoiceProcessor;
    typedef AutoPtr<SendVoiceProcessor> SendVoiceProcessorPtr;

    /// Acoustic Echo Canceller value
    typedef enum EPlanetKitAcousticEchoCanceller
    {
        /// Disabled
        PLNK_ACOUSTIC_ECHO_CANCELLER_DISABLED               = 0,
        /// The recommended value<br>Default
        PLNK_ACOUSTIC_ECHO_CANCELLER_INTENSITY_RECOMMENDED  = 1,
        /// Min
        PLNK_ACOUSTIC_ECHO_CANCELLER_INTENSITY_MIN          = 2,
        /// Max
        PLNK_ACOUSTIC_ECHO_CANCELLER_INTENSITY_MAX          = 3,
        /// Adaptive
        PLNK_ACOUSTIC_ECHO_CANCELLER_INTENSITY_ADAPTIVE     = 4
    }EPlanetKitAcousticEchoCanceller;

    /// Auto Gain Control value
    typedef enum EPlanetKitAutoGainControl
    {
        /// Disabled
        PLNK_AUTO_GAIN_CONTROL_TYPE_DISABLED                = 0,
        /// Use AGC by using software
        PLNK_AUTO_GAIN_CONTROL_TYPE_SOFTWARE               = 1,
        /// Use AGC by using hardware<br>Default
        PLNK_AUTO_GAIN_CONTROL_TYPE_HARDWARE                = 2,
    } EPlanetKitAutoGainControl;

    /// Noise Suppressor mode value
    typedef enum EPlanetkitNoiseSuppressorMode {
        /// Disabled
        PLNK_NOISE_SUPPRESSOR_MODE_DISABLED                 = 0,
        /// Enabled<br>Default
        PLNK_NOISE_SUPPRESSOR_MODE_ENABLE                   = 1,
    } EPlanetkitNoiseSuppressorMode;

    /**
     * @brief Gets SendVoiceProcessor to control VQE (Voice Quality Enhancement). Use SendVoiceProcessor when you need to turn on or off the S/W VQE filter functionality depending on your environment.
     */
    class PLANETKIT_API SendVoiceProcessor : public Base
    {
    public:

        /**
         * Enables the Voice Processor.
         * @param pUserData         UserData for IResultHandler
         * @param pResultHandler    Completion Callback
         * @return true on success
         */
        virtual bool Enable(void * pUserData, IResultHandler * pResultHandler) = 0;

        /**
         * Disables the Voice Processor.
         * @param pUserData         UserData for IResultHandler
         * @param pResultHandler    Completion Callback
         * @return true on success
         */
        virtual bool Disable(void * pUserData, IResultHandler * pResultHandler) = 0;


        /**
         * Checks whether the Voice Processor is enabled.
         * @return true if enabled
         */
        virtual bool IsEnabled() = 0;

        /**
         * Sets the Acoustic Echo Canceller mode.
         * @param eAECMode          Acoustic Echo Canceller mode
         * @param pUserData         UserData for IResultHandler
         * @param pResultHandler    Completion Callback
         * @return true on success
         */
        virtual bool SetAcousticEchoCanceller(EPlanetKitAcousticEchoCanceller ePlanetKitAcousticEchoCancellerMode = EPlanetKitAcousticEchoCanceller::PLNK_ACOUSTIC_ECHO_CANCELLER_INTENSITY_RECOMMENDED, void * pUserData = nullptr, IResultHandler * pResultHandler = nullptr) = 0;
        
        /**
         * Gets the Acoustic Echo Canceller mode.
         * @return Current Acoustic Echo Canceller mode
         */
        virtual EPlanetKitAcousticEchoCanceller GetAcousticEchoCancellerMode() = 0;

        /**
         * Sets the Auto Gain Control mode.
         * @param ePlanetKitAutoGainControl     Auto Gain Control mode
         * @param pUserData                     UserData for IResultHandler
         * @param pResultHandler                Completion Callback
         * @return true on success
         */
        virtual bool SetAutoGainControl(EPlanetKitAutoGainControl ePlanetKitAutoGainControl = EPlanetKitAutoGainControl::PLNK_AUTO_GAIN_CONTROL_TYPE_SOFTWARE, void * pUserData = nullptr, IResultHandler * pResultHandler = nullptr) = 0;

        /**
         * Gets the Auto Gain Control mode.
         * @return Current Auto Gain Control mode
         */
        virtual EPlanetKitAutoGainControl GetAutoGainControlMode() = 0;

        /**
         * Gets the Noise Suppressor mode.
         * @return Current Noise Suppressor mode
         */
        virtual EPlanetkitNoiseSuppressorMode GetNoiseSuppressorMode() = 0;

        /**
         * Sets the Noise Suppressor mode.
         * @param ePlanetkitNoiseSuppressorMode Noise Suppressor mode
         * @param pUserData                     UserData for IResultHandler
         * @param pResultHandler                Completion Callback
         * @return true on success
         */
        virtual bool SetNoiseSuppressor(EPlanetkitNoiseSuppressorMode ePlanetkitNoiseSuppressorMode = EPlanetkitNoiseSuppressorMode::PLNK_NOISE_SUPPRESSOR_MODE_ENABLE, void * pUserData = nullptr, IResultHandler * pResultHandler = nullptr) = 0;
    };
}