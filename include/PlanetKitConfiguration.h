// Copyright 2023 LINE Plus Corporation
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

namespace PlanetKit {
    class Configuration;

    template class PLANETKIT_API AutoPtr<Configuration>;
    typedef AutoPtr<Configuration> ConfigurationPtr;

    /**
     * PlanetKit log level.
     */
    enum ELogLevel {
        /// Doesn't write logs.
        PLNK_LOG_SILENT = 0,
        /// Writes simple logs and default value.
        PLNK_LOG_SIMPLE = 4,
        /// Writes more detailed logs.
        PLNK_LOG_DETAILED = 5
    };

    /**
     * PlanetKit log file size limit.
     */
    enum ELogSizeLimit {
        /**
         * Log file size limit is 16MB.
         */
        PLNK_LOG_SIZE_LIMIT_SMALL = 0,
        /**
         * Log file size limit is 64MB.
         */
        PLNK_LOG_SIZE_LIMIT_MEDIUM,
        /**
         * Log file size limit is 256MB.
         */
        PLNK_LOG_SIZE_LIMIT_LARGE,
        /**
         * No size limit to write logs.
         */
        PLNK_LOG_SIZE_LIMIT_UNLIMITED,
    };

    /**
     * This is the class used to initialize PlanetKit. An instance of this class can be created using Configuration::Create().
     */
    class PLANETKIT_API Configuration : public Base {
    public :
        /**
         * Create an instance of the Configuration class.
         * @param strBasePath Path of PlanetKit binaries. You can use absolute or relative path.<br>String encoding must be UTF-16.<br>It can be an empty string like "", but it can't be nullptr.
         * @param strDatabasePath Path of PlanetKit database that includes some configuration options. You can use absolute or relative path.<br>String encoding must be UTF-16.<br>It can be an empty string like "", but it can't be nullptr.
         * @return
         *  - If it successfully created an instance, it returns the pointer to the instance.<br>
         *  - If it failed to create an instance, it returns nullptr.
         * @remark
         *  - This API can fail when any parameters are nullptr.<br>
         *  - If you put an empty string like L"", then the path will be the path of the current process.
         */
        static ConfigurationPtr Create(const WString& strBasePath, const WString& strDatabasePath);

        /**
         * Sets the log level of PlanetKit.<br>Default value is PLNK_LOG_SILENT.
         * @param eLogLevel Log level that you want to set.
         * @see ELogLevel
         * @remark
         *  - If you set a parameter value that isn't included in ELogLevel, then this API will ignore the call.
         */
        virtual void SetLogLevel(ELogLevel eLogLevel) = 0;

        /**
         * Sets the log file size limit to write.<br>Default value is PLNK_LOG_SIZE_LIMIT_LARGE.
         * @param eLogSizeLimit Log file size limit that you want to set.
         * @see ELogSizeLimit
         */
        virtual void SetLogSizeLimit(ELogSizeLimit eLogSizeLimit) = 0;

        /**
         * Enables or disables log output to a file.<br>Default value is false.
         * @param bEnable true means enabling log output and false means disabling log output.
         */
        virtual void EnableLogOutput(bool bEnable) = 0;

        /**
         * Gets the base path that you set.
         * @return
         *  - Base path string that is encoded in UTF-16.
         */
        virtual const WString& GetBasePath() = 0;

        /**
         * Gets the database path that you set.
         * @return
         *  - Database path string that is encoded in UTF-16.
         */
        virtual const WString& GetDatabasePath() = 0;

        /**
         * Gets the log level that you set.
         */
        virtual ELogLevel GetLogLevel() = 0;

        /**
         * Gets the value of log file size limit that you set.
         */
        virtual ELogSizeLimit GetLogSizeLimit() = 0;

        /**
         * Gets whether log output is enabled.
         */
        virtual bool IsLogOutputEnabled() = 0;
    };
};