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

namespace PlanetKit {
    /**
     * Reason code for deactivating recording on the cloud.
     */
    enum ERecordOnCloudDeactivateReason {
        /// Internal error. 
        PLNK_RECORD_ON_CLOUD_DEACTIVATE_REASON_INTERNAL = 0,
        /// Recording failed on the cloud.
        PLNK_RECORD_ON_CLOUD_DEACTIVATE_REASON_ACTIVATION_FAILED = 1,
    };

    typedef Optional<ERecordOnCloudDeactivateReason> DeactivateReasonOptional;

    /**
     * This is a class related to the state of recording on the cloud.
     */
    class PLANETKIT_API RecordOnCloud {
    public:
        virtual ~RecordOnCloud() { }

        /**
         * Gets the state of recording on the cloud.
         */
        virtual bool IsActivated() = 0;

        /**
         * Gets the reason for deactivating recording on the cloud.
         * @remark
         *  - Return value can be nullptr when the return value of IsActivated() is true.
         */
        virtual DeactivateReasonOptional GetDeactivatedReason() = 0;
    };

    typedef SharedPtr<RecordOnCloud> RecordOnCloudPtr;
};