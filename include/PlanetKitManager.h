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
#include "PlanetKitCcParam.h"

#include "PlanetKitCameraController.h"
#include "PlanetKitScreenShareController.h"

#include "PlanetKitConfiguration.h"

namespace PlanetKit 
{
    typedef AutoPtr<PlanetKitManager> PlanetKitManagerPtr;

    class PLANETKIT_API PlanetKitManager : public Base {
    public:
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
        * @param pPlanetKitCall Assigns a PlanetKitCall instance on success.
        * @return SStartResult
        */
        virtual SStartResult MakeCall(MakeCallParamPtr pParam, PlanetKitCallPtr* pPlanetKitCall) = 0;

        /**
        * Verifies a call.
        * @param pParam CallParam that is created by VerifyCallParam::Create
        * @param pPlanetKitCall  Assigns a PlanetKitCall instance on success.
        * @return SStartResult
        */
        virtual SStartResult VerifyCall(VerifyCallParamPtr pParam, PlanetKitCallPtr* pPlanetKitCall) = 0;

        /**
        * Joins a conference.
        * @param pConferenceParam Setting values for a conference.
        * @param pPlanetKitConference Assigns a PlanetKitConference instance on success.
        * @return SStartResult
        */
        virtual SStartResult JoinConference(ConferenceParamPtr pConferenceParam, PlanetKitConferencePtr& pPlanetKitConference) = 0;

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
        AudioManagerPtr GetAudioManager();

        /**
         * Gets the CameraController instance.
         * @return Reference to CameraController singleton instance. Returns nullptr on failure.
         */
        CameraControllerPtr GetCameraController();
        
        /**
         * Gets the ScreenShareController instance.
         * @return Reference to ScreenShareController singleton instance. Returns nullptr on failure.
         */
        ScreenShareControllerPtr GetScreenShareController();

        /**
         * Updates the VoIP server URL.
         * @param strServerUrl URL string which is encoded in UTF-16 and null-terminated.
         * @return true on success
         * @remark
         *  - The maximum number of bytes for szServerUrl is 2048.
         */
        bool UpdateServerUrl(const WString& strServerUrl);

        /**
         * Gets the current VoIP server URL.
         * @return The URL string which is encoded in UTF-16 and null-terminated.
         * @remark
         *  - This API can return nullptr when the URL string is empty.
         */
        const WString& GetServerUrl();

        /**
        * Gets the PlanetKit version. 
        * @return Reference to null-terminated PlanetKit version string. Reference is valid for the lifetime of PlanetKitManager.
        */
        const WString& PlanetKitVersion();

        /**
         * Gets user agent string. It includes `PlanetKit Version` and `Engine Version`.
         * @return Reference to null-terminated string. Reference is valid for the lifetime of PlanetKitManager.
         */
        const WString& UserAgentString();

        /**
        * Gets the default video transmission capability for the current system. 
        * @return true on success.
        */
        bool GetDefaultVideoCapSend(SVideoCapability *pSend);

        /**
        * Gets the default video receiving capability for the current system.
        * @return true on success.
        */
        bool GetDefaultVideoCapReceive(SVideoCapability *pReceive);

        /**
        * Checks whether the end device supports hardware video codec.
        * @return true if hardware codec is supported.
        */
        bool CanSupportVideoHWCodec();

        /**
         * Creates a cc param.
         */
        CCParamPtr CreateCCParam(const char* strCCParam);

        
    protected:
        PlanetKitManager();
        virtual ~PlanetKitManager();
    };
}
