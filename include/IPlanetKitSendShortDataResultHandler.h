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
     * Failure reasons for sending short data
     */
    enum ESendShortDataFailReason {
        // No failure. The short data was sent successfully.
        PLNK_SEND_SHORT_DATA_FAIL_REASON_NONE = 0,

        // One or more input parameters are invalid (e.g. data_size is 0 or data_ptr is NULL).
        PLNK_SEND_SHORT_DATA_FAIL_REASON_INVALID_PARAMETER,

        // The data_type exceeds the maximum allowed length (over 100 bytes including the null terminator).
        PLNK_SEND_SHORT_DATA_FAIL_REASON_TOO_LONG_DATA_TYPE,

        // The data payload exceeds the maximum allowed size (over 800 bytes).
        PLNK_SEND_SHORT_DATA_FAIL_REASON_TOO_LONG_DATA,

        // The short data was sent more frequently than allowed (rate limit exceeded). Only one sending operation is allowed per second.
        PLNK_SEND_SHORT_DATA_FAIL_REASON_TOO_FREQUENT,

        // The sending operation failed due to a timeout.
        PLNK_SEND_SHORT_DATA_FAIL_REASON_TIMEOUT
    };

    /**
     * The result handler for short data sending operation, which provides a detailed failure reason.
     * @param pUserData User-managed data pointer.
     * @param bSuccess Result of the function call.
     * @param eFailReason Detailed failure reason. PLNK_SEND_SHORT_DATA_FAIL_REASON_NONE if bSuccess is true.
     */
    using SendShortDataResultHandler = void(*)(void* pUserData, bool bSuccess, ESendShortDataFailReason eFailReason);
}
