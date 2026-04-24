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

    using ConfigurationPtr = SharedPtr<Configuration>;

    /**
     * PlanetKit log level.
     */
    enum ELogLevel {
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
    };

    /**
     * This is the class used to initialize PlanetKit. An instance of this class can be created using Configuration::Create().
     */
    class PLANETKIT_API Configuration {
    public :
        /**
         * Creates an instance of the Configuration class.
         * @param strPlanetKitSystemDirectory Directory used internally by the PlanetKit SDK for its internal operations. You can use an absolute or relative path. If you put an empty string like L"", then the directory will be the working directory of the current process. String encoding must be UTF-16.<br>It can be an empty string like L"", but it can't be nullptr.
         * @return
         *  - If it successfully created an instance, it returns the pointer to the instance.<br>
         *  - If it failed to create an instance, it returns nullptr.
         */
        static ConfigurationPtr Create(const WString& strPlanetKitSystemDirectory);

        /**
         * Enables PlanetKit log output with log size limit.
         * @param strLogDirectory Directory for log files. If not set, the log files are created in the strPlanetKitSystemDirectory. String encoding must be UTF-16.
         * @param eLogLevel Log level. The default value is ELogLevel::PLNK_LOG_SIMPLE.
         * @param eLogSizeLimit Log file size limit. The default value is ELogSizeLimit::PLNK_LOG_SIZE_LIMIT_LARGE.
         */
        virtual void EnableLog(const WString& strLogDirectory, ELogLevel eLogLevel = ELogLevel::PLNK_LOG_SIMPLE, ELogSizeLimit eLogSizeLimit = ELogSizeLimit::PLNK_LOG_SIZE_LIMIT_LARGE) = 0;

        /**
         * Enables PlanetKit log output by specifying a log file name.
         * @param strLogDirectory Directory for log files. If not set, the log files are created in the strPlanetKitSystemDirectory. String encoding must be UTF-16.
         * @param strLogFileName Specifies the name of the log file. String encoding must be UTF-16.
         * @param eLogLevel Log level. The default value is ELogLevel::PLNK_LOG_SIMPLE.
         * @remark
         *  - There is no limit on the size of the log file.
         *  - If strLogFileName is not set, the log file is created using the default naming format: planetkitMMDD_HHMMSS.log (zero-padded timestamp).
         */
        virtual void EnableLog(const WString& strLogDirectory, WStringOptional strLogFileName, ELogLevel eLogLevel = ELogLevel::PLNK_LOG_SIMPLE) = 0;

        /**
         * Gets the PlanetKit system directory that you set.
         * @return
         *  - PlanetKit system directory string that is encoded in UTF-16.
         */
        virtual const WString& GetPlanetKitSystemDirectory() = 0;
    };
};