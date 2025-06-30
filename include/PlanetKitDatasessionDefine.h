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

namespace PlanetKit {
    const unsigned int kDataSessionStreamIdMin = 100;
    const unsigned int kDataSessionStreamIdMax = 1000;

    typedef unsigned int DataSessionStreamIdT;

    /**
     * @brief Data session streaming type
     */
    typedef enum EDataSessionType {
        /// Lost messages will be retransmitted.
        PLNK_DATA_SESS_TYPE_RELIABLE_MSG = 0,
        /// Lost packets will be retransmitted.
        PLNK_DATA_SESS_TYPE_RELIABLE_BYTES,
        /// Lost bytes are not retransmitted.
        PLNK_DATA_SESS_TYPE_UNRELIABLE_BYTES,
        /// Lost messages are not retransmitted.
        PLNK_DATA_SESS_TYPE_UNRELIABLE_MSG,
        /// Not supported type
        PLNK_DATA_SESS_TYPE_UNKNOWN
    } EDataSessionType;

    /**
     * @brief This is the definition of an exception that occurred during data session communication.
     */
    typedef enum EDataSessException {
        /// The data traffic is too much.
        PLNK_DATA_SESS_EXCEPTION_TOO_LONG_QUEUED_DATA,
    } EDataSessException;

    /**
     * Fail reason related to data session
     */
    typedef enum EDataSessionFailReason {
        /// Reason none
        PLNK_DATA_SESS_FAIL_REASON_NONE = 0,
        /// An internal error occurred.
        PLNK_DATA_SESS_FAIL_REASON_INTERNAL = 1,
        /// There is no incoming data.
        PLNK_DATA_SESS_FAIL_REASON_NOT_INCOMING = 3,
        /// The stream ID already exists.
        PLNK_DATA_SESS_FAIL_REASON_ALREADY_EXIST = 4,
        /// The stream ID is invalid.
        PLNK_DATA_SESS_FAIL_REASON_INVALID_ID = 5,
        /// The data session type is invalid.
        PLNK_DATA_SESS_FAIL_REASON_INVALID_TYPE = 6,
    } EDataSessionFailReason;


    typedef enum EDataSessionClosedReason {
        /// Data session has ended.
        PLNK_DATA_SESSION_CLOSED_REASON_SESSION_END = 0,
        /// Unexpected error occurred internally.
        PLNK_DATA_SESSION_CLOSED_REASON_INTERNAL = 1,
        /// Data session ID is unsupported by the peer.
        PLNK_DATA_SESSION_CLOSED_REASON_UNSUPPORTED = 2,
    } EDataSessionClosedReason;
};