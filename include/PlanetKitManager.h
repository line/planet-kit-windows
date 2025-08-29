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
#include "PlanetKitCall.h"
#include "PlanetKitConference.h"
#include "PlanetKitAudioManager.h"
#include "PlanetKitCCParam.h"

#include "PlanetKitCameraController.h"
#include "PlanetKitScreenShareController.h"

#include "PlanetKitConfiguration.h"

#include "PlanetKitVideoCommon.h"

namespace PlanetKit {
    class PLANETKIT_API PlanetKitManager;
    typedef SharedPtr<PlanetKitManager> PlanetKitManagerPtr;

    class PLANETKIT_API PlanetKitManager {
    public:
        virtual ~PlanetKitManager() {}
        /**
         * Initializes PlanetKit SDK.<br>This must be called before your application can use the PlanetKit library.<br>
         * @param pConfiguration This parameter contains configuration values.
         * @remark
         *  - If you call this function again after successfully initializing PlanetKit, the call is ignored and returns false.
         * @see Configuration
         */
        static bool Initialize(ConfigurationPtr pConfiguration);

        /**
        * Checks whether PlanetKit is initialized.
        * @return Returns true if PlanetKit is initialized.
        */
        static bool IsInitialized();

        /**
        * Gets the PlanetKitManager instance.
        * @return Reference to PlanetKitManager singleton instance. Returns nullptr on failure.
        */
        static PlanetKitManagerPtr  GetInstance();

        /**
        * Makes a call.
        * @param pParam CallParam that is created by MakeCallParam::CreateWithAccessToken
        * @param microphoneOptional Select the microphone to use for this call.
        * @param pPlanetKitCall Assigns a PlanetKitCall instance on success.
        * @return SStartResult
        * @remark If NullOptional or a deselected microphone value is passed, the call will proceed without a microphone. 
        *         Subsequently, the call may be terminated depending on the AllowCallWithoutMic setting in pParam.
        */
        virtual SStartResult MakeCall(MakeCallParamPtr pParam, MicOptional micOptional, PlanetKitCallPtr* pPlanetKitCall) = 0;

        /**
        * Verifies a call.
        * @param pParam CallParam that is created by VerifyCallParam::Create
        * @param microphoneOptional Select the microphone to use for this call.
        * @param pPlanetKitCall  Assigns a PlanetKitCall instance on success.
        * @return SStartResult
        * @remark If NullOptional or a deselected microphone value is passed, the call will proceed without a microphone. 
        *         Subsequently, the call may be terminated depending on the AllowCallWithoutMic setting in pParam.
        */
        virtual SStartResult VerifyCall(VerifyCallParamPtr pParam, MicOptional micOptional, PlanetKitCallPtr* pPlanetKitCall) = 0;

        /**
        * Joins a conference.
        * @param pConferenceParam Setting values for a conference.
        * @param microphoneOptional Select the microphone to use for this conference.
        * @param pPlanetKitConference Assigns a PlanetKitConference instance on success.
        * @return SStartResult
        * @remark If NullOptional or a deselected microphone value is passed, the conference will proceed without a microphone. 
        *         Subsequently, the con may be terminated depending on the AllowCallWithoutMic setting in pParam.
        */
        virtual SStartResult JoinConference(ConferenceParamPtr pConferenceParam, MicOptional micOptional, PlanetKitConferencePtr& pPlanetKitConference) = 0;

        /**
         * Gets the connected conference instance.
         * @remark
         *  It can be nullptr when you are not connected to a conference.
         */
        virtual PlanetKitConferencePtr GetConferenceInstance() = 0;

        /**
        * Gets the AudioManager instance.
        * @return Reference to AudioManager singleton instance. Returns nullptr on failure.
        */
        virtual AudioManagerPtr GetAudioManager() = 0;

        /**
         * Gets the CameraController instance.
         * @return Reference to CameraController singleton instance. Returns nullptr on failure.
         */
        virtual CameraControllerPtr GetCameraController() = 0;
        
        /**
         * Gets the ScreenShareController instance.
         * @return Reference to ScreenShareController singleton instance. Returns nullptr on failure.
         */
        virtual ScreenShareControllerPtr GetScreenShareController() = 0;

        /**
         * Updates the VoIP server URL.
         * @param strServerUrl URL string which is encoded in UTF-16 and null-terminated.
         * @return true on success
         * @remark
         *  - The maximum number of bytes for szServerUrl is 2048.
         */
        virtual bool UpdateServerUrl(const WString& strServerUrl) = 0;

        /**
         * Gets the current VoIP server URL.
         * @return The URL string which is encoded in UTF-16 and null-terminated.
         * @remark
         *  - This API can return nullptr when the URL string is empty.
         */
        virtual const WString& GetServerUrl() = 0;

        /**
        * Gets the PlanetKit version. 
        * @return Reference to null-terminated PlanetKit version string. Reference is valid for the lifetime of PlanetKitManager.
        */
        virtual const WString& PlanetKitVersion() = 0;

        /**
         * Gets user agent string. It includes `PlanetKit Version` and `Engine Version`.
         * @return Reference to null-terminated string. Reference is valid for the lifetime of PlanetKitManager.
         */
        virtual const WString& UserAgentString() = 0;

        /**
        * Checks whether the end device supports hardware video codec.
        * @return true if hardware codec is supported.
        */
        virtual bool CanSupportVideoHWCodec() = 0;

        /**
         * Creates a cc param.
         */
        virtual CCParamPtr CreateCCParam(const char* strCCParam) = 0;

        /**
         * Retrieves the default video settings applied when sending video to the peer during a call.
         * @remark
         *  - If PlanetKit is not initialized, NullOptional is returned.
         */
        virtual VideoCapabilityOptional GetCallDeviceDefaultVideoSendCapability() = 0;

        /**
         * Retrieves the default video settings applied when receiving video from the peer during a call.
         * @remark
         *  - If PlanetKit is not initialized, NullOptional is returned.
         */
        virtual VideoCapabilityOptional GetCallDeviceDefaultVideoReceiveCapability() = 0;

        /**
         * Retrieves the default video settings applied when sending video to the peer during a confernece.
         * @remark
         *  - If PlanetKit is not initialized, NullOptional is returned.
         */
        virtual VideoCapabilityOptional GetConferenceDeviceDefaultVideoSendCapability() = 0;

        /**
         * Retrieves the default video settings applied when receiving video from the peer during a confernece.
         * @remark
         *  - If PlanetKit is not initialized, NullOptional is returned.
         */
        virtual VideoCapabilityOptional GetConferenceDeviceDefaultVideoReceiveCapability() = 0;

        /**
         * Sets whether to attempt to use the hardware codec.
         * @param sPreferredHardwareCodec Configuration for whether to attempt to use the hardware codec.
         */
        virtual void SetPreferredHardwareCodec(SPreferredHardwareCodec sPreferredHardwareCodec) = 0;

        /**
         * Gets whether to attempt to use the hardware codec.
         * @return Configuration for whether to attempt to use the hardware codec.
         */
        virtual SPreferredHardwareCodec GetPreferredHardwareCodec() = 0;
    };
}
