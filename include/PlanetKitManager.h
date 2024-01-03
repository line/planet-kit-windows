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
#include "PlanetKitLogStorageInterface.h"
#include "PlanetKitCcParam.h"

#include "PlanetKitCameraController.h"
#include "PlanetKitScreenShareController.h"

#include "PlanetKitConfiguration.h"

namespace PlanetKit 
{
    typedef struct SManagerInitParam
    {
        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         */
        char    szBasePath[PLNK_BUFFER_SIZE_256] = { 0, }; 
        
        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         */
        char    szDbPath[PLNK_BUFFER_SIZE_256] = { 0, }; 

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         */
        int     nLogLevel = 0; 

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         */
        bool    bEnableLog = false;

        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later.")
        /**
         * @deprecated This will not be supported in 5.1 or later.
         */
        bool    bEnableFileLog; 

        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later.")
        /**
         * @deprecated This will not be supported in 5.1 or later.
         */
        bool    bEnableStdOutLog;
    }SManagerInitParam;


    class PLANETKIT_API PlanetKitManager 
    {
    public:
        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use bool Initialize(ConfigurationPtr pConfiguration).")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see bool Initialize(ConfigurationPtr pConfiguration)
         */
        bool Initialize(const SManagerInitParam *pManagerInitParam);

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
        static bool                 IsInitialized();

        /**
        * Gets the PlanetKitManager instance.
        * @return Reference to PlanetKitManager singleton instance. Returns nullptr on failure.
        */
        static PlanetKitManager *   GetInstance();


        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use SStartResult MakeCall(CallParam *pParam, PlanetKitCallPtr& pPlanetKitCall)")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see MakeCall
        */
        SStartResult MakeCall(CallInitParam *pParam, PlanetKitCall** ppPlanetKitCall);
        
        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use SStartResult VerifyCall(CallParam *pParam, PlanetKitCallPtr& pPlanetKitCall)")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see VerifyCall
        */
        SStartResult VerifyCall(CallInitParam *pParam, PlanetKitCall** ppPlanetKitCall);

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later. Use SStartResult JoinConference(ConferenceJoinParam *pParam, PlanetKitConferencePtr& pPlanetKitConference)")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        * @see JoinConference
        */
        SStartResult JoinConference(ConferenceJoinParam *pParam, PlanetKitConference **ppPlanetKitConference);

        PLANETKIT_DEPRECATED("This will not be supported in 5.0 or later.")
        /**
        * @deprecated This will not be supported in 5.0 or later.
        */
        LogStorageInterface* CreateLogStorage(ELogStorageType eType, size_t nMaxSize);


        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later. Use SStartResult MakeCall(MakeCallParamPtr & pParam, PlanetKitCallPtr& pPlanetKitCall)")
        /**
        * @deprecated This will not be supported in 5.1 or later.
        * @see MakeCall
        */
        SStartResult MakeCall(CallParamPtr & pParam, PlanetKitCallPtr& pPlanetKitCall);

        /**
        * Makes a call.
        * @param pParam CallParam that is created by CallParam::CreateMakeCallParamWithAccessToken
        * @param pPlanetKitCall Assigns a PlanetKitCall instance on success.
        * @return SStartResult
        */
        virtual SStartResult MakeCall(MakeCallParamPtr pParam, PlanetKitCallPtr* pPlanetKitCall) = 0;


        PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later. Use SStartResult VerifyCall(VerifyCallParamPtr *pParam, PlanetKitCallPtr& pPlanetKitCall)")
        /**
        * @deprecated This will not be supported in 5.1 or later.
        * @see VerifyCall
        */
        SStartResult VerifyCall(CallParamPtr & pParam, PlanetKitCallPtr& pPlanetKitCall);

        /**
        * Verifies a call.
        * @param pParam CallParam that is created by CallParam::CreateVerifyCallParam
        * @param pPlanetKitCall  Assigns a PlanetKitCall instance on success.
        * @return SStartResult
        */
        virtual SStartResult VerifyCall(VerifyCallParamPtr pParam, PlanetKitCallPtr* pPlanetKitCall) = 0;

        /**
        * Joins a conference.
        * @param pJoinConferenceParam Setting values for a conference.
        * @param pPlanetKitConference Assigns a PlanetKitConference instance on success.
        * @return SStartResult
        */
        virtual SStartResult JoinConference(ConferenceJoinParamPtr pJoinConferenceParam, PlanetKitConferencePtr& pPlanetKitConference) = 0;

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
        AudioManager* GetAudioManager();

        typedef void* VideoCaptureManager;
        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later.")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see GetCameraController, GetScreenShareController
         * @remark
         * - 
         */
        VideoCaptureManager *GetVideoCaptureManager();

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

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use bool UpdateServerUrl(const wchar_t* szServerUrl)")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see bool UpdateServerUrl(const wchar_t* szServerUrl)
         */
        bool UpdateServerUrl(const char* szServerUrl);

        /**
         * Updates the VoIP server URL.
         * @param szServerUrl URL string which is encoded in UTF-16 and null-terminated.
         * @return true on success
         * @remark
         *  - The maximum number of bytes for szServerUrl is 2048.
         */
        bool UpdateServerUrl(const wchar_t* szServerUrl);

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. const WString& GetServerUrl()")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see const WString& GetServerUrl()
         */
        bool GetServerUrl(char * szServerUrl, size_t nBufferSize);

        /**
         * Gets the current VoIP server URL.
         * @return The URL string which is encoded in UTF-16 and null-terminated.
         * @remark
         *  - This API can return nullptr when the URL string is empty.
         */
        const wchar_t* GetServerUrl();

        /**
        * Gets the PlanetKit version. 
        * @return Reference to null-terminated PlanetKit version string. Reference is valid for the lifetime of PlanetKitManager.
        */
        const wchar_t* PlanetKitVersion();

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

        /**
         * Tests the camera device.
         */
        bool TestVideoDevice(PlanetKit::CameraInfoPtr pCamInfo, HWND hwnd);

        void StopTestVideoDevice();
        
    protected:
        PlanetKitManager();
        virtual ~PlanetKitManager();
    };
}
