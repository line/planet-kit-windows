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

#include "PlanetKitCallParam.h"


namespace PlanetKit
{
    /// Call parameter for MakeCall API
    class PLANETKIT_API MakeCallParam : virtual public CallParam {
    public:
        /// Gets the app server data.
        virtual const wchar_t* GetAppServerData() = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use const wchar_t* APIKey()")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see const wchar_t* APIKey()
         */
        void SetAppServerData(const char* szAppServerData);

        /**
         * Sets the app server data.<br>
         * @param szAppServerData App server data that is encoded in UTF-16.
         * @remark
         *  - If the parameter is nullptr, the app server data stored in the class is cleared.<br>
         *  - After converting szAppServerData to UTF-8, if it exceeds 4096 bytes including the null-termination character, the connection will fail.<br>
         *  - In case of failure, the error code is PLNK_START_FAIL_REASON_TOO_LONG_APP_SERVER_DATA.
         */
        virtual void SetAppServerData(const wchar_t* szAppServerData) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use CallStartMessagePtr GetCallStartMessage()")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see CallStartMessagePtr GetCallStartMessage()
         */
        void GetCallStartMessage(CallStartMessage* pResult);

        /// Gets the call start message.
        virtual CallStartMessagePtr GetCallStartMessage() = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use void SetCallStartMessage(CallStartMessagePtr pCallStartMessage)")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see void SetCallStartMessage(CallStartMessagePtr pCallStartMessage)
         */
        void SetCallStartMessage(const CallStartMessage& sCallStartMessage);

        /// Sets the call start message.
        /// The maximum size of call start message is 200 bytes including null termination.
        virtual void SetCallStartMessage(CallStartMessagePtr pCallStartMessage) = 0;

        /// Gets preparation status.
        virtual bool IsPreparation() = 0;

        /// Sets preparation status.
        virtual void SetPreparation(bool bPreparation) = 0;

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use const wchar_t* APIKey()")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see const wchar_t* APIKey()
         */
        const char* GetAPIKey();

        PLANETKIT_DEPRECATED("This will not be supported in 5.2 or later. Use const wchar_t* AccessToken()")
        /**
         * @deprecated This will not be supported in 5.2 or later.
         * @see const wchar_t* AccessToken()
         */
        const char* GetAccessToken();

        /// Gets the API Key.
        virtual const wchar_t* APIKey() = 0;

        /// Gets the access token.
        virtual const wchar_t* AccessToken() = 0;

        /// Gets the connect token.
        virtual EConnectToken ConnectToken() = 0;
        
        /// Sets the media type.
        virtual void SetIsVideoCall(bool bVideoCall) = 0;

        /**
         * Sets the flag of recording on the cloud.
         * @param bRecord true means enabling recording and false means disabling recording.
         * @remark
         *  - The default value of this flag is false.
         *  - DO NOT set this to true before consulting with the LINE Planet team.<br>
         *  - If you want to use this feature, please contact us. (https://docs.lineplanet.me/ko/help/contact)
         */
        virtual void SetRecordOnCloud(bool bRecord) = 0;

        /**
         * Returns whether recording on the cloud is enabled.
         * @remark
         *  - The default value of this flag is false.
         */
        virtual bool IsRecordOnCloud() = 0;

    };

    typedef AutoPtr<MakeCallParam> MakeCallParamPtr;
}
