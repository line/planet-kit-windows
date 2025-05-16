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
    /**
     * PlanetKit state of a 1-to-1 call
     */
    typedef enum ECallState {
        /// Idle
        CALL_IDLE,
        /// Trying to call
        CALL_TRYING,
        /// Waiting for an answer
        CALL_WAIT_ANSWER,
        /// Verified
        CALL_VERIFIED,
        /// Connected
        CALL_CONNECTED,
        /// Disconnected
        CALL_DISCONNECTED
    } ECallState;
};