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

#include "PlanetKitOptional.hpp"

namespace PlanetKit {
    /**
     * Enum representing different predefined user types in PlanetKit.<br>
     * This enum is used to categorize agents provided by PlanetKit based on their roles or functionalities.
     */
    enum class PlanetKitUserType {
        /**
         * Represents an undefined user type. <br>
         * This is used when the user type is not specified.
         */
        Undefined = 0,

        /**
         * Represents an audio caller agent in the Planet Cloud. When this type is specified, the audio caller agent acts as the caller and establishes an audio call to the target user.<br>
         * For more details, see: https://docs.lineplanet.me/server-api/agent-call/server-api-audio-caller
         */
        AudioCaller = 10000,

        /**
         * Represents an audio echo callee agent in the Planet Cloud.<br>
         * When this type is specified, the agent acts as the callee and accepts an audio call from the user, echoing the received audio back to the user.
         */
        AudioEchoCallee = 10001,


        /**
         * Represents a video echo callee agent in the Planet Cloud.<br>
         * When this type is specified, the agent acts as the callee and accepts a video call from the user, returning the video along with the echoed audio.
         */
        VideoEchoCallee = 10002,

        /**
         * Represents a mental health counselor agent in the Planet Cloud.<br>
         * When this type is specified, the agent can act as the caller or the callee, providing audio-based counseling.
         */
        MentalHealthCounselor = 10003,

        /**
         * Reserved user types for future use.<br>
         * These values are currently not defined and are reserved for potential future extensions.<br>
         * This represents 10004.
         */
        Reserved01 = 10004,

        /**
         * This represents 10005.
         */
        Reserved02 = 10005,

        /**
         * This represents 10003.
         */
        Reserved03 = 10006,

        /**
         * This represents 10004.
         */
        Reserved04 = 10007,

        /**
         * This represents 10008.
         */
        Reserved05 = 10008,

        /**
         * Represents an interpreter participant agent in the Planet Cloud.<br>
         * When this type is specified, the agent interprets speech from one language to another in a group call, receiving and sending audio streams.<br>
         * Additional language setting is required at the time of joining.
         */
        ParticipantInterpreter = 20000,

        /**
         * Represents a transcriber participant agent in the Planet Cloud.<br>
         * When this type is specified, the agent provides speech-to-text (STT) functionality in a group call, receiving audio streams and sending text output.<br>
         * Additional language setting is required at the time of joining.
         */
        ParticipantTranscriber = 20001,

        /**
         * Represents a mental health counselor participant agent in the Planet Cloud.
         * When this type is specified, the agent provides counseling in a group audio call, receiving and sending audio.
         */
        ParticipantMentalHealthCounselor = 20002,

        /**
         * This represents 20003.
         */
        ParticipantReserved01 = 20003,

        /**
         * This represents 20004.
         */
        ParticipantReserved02 = 20004,

        /**
         * This represents 20005.
         */
        ParticipantReserved03 = 20005,

        /**
         * This represents 20006.
         */
        ParticipantReserved04 = 20006,

        /**
         * This represents 20007.
         */
        ParticipantReserved05 = 20007,

        /**
         * The user type for a value corresponding to an enum that is not defined in the current version is classified as Unknown.
         */
        Unknown = 99999
    };

    using PlanetKitUserTypeOptional = Optional<PlanetKitUserType>;
};