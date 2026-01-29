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

#include "PlanetKitUserId.h"

namespace PlanetKit {
    /**
     * Audio device type
     */
    typedef enum EAudioDeviceType {
        /// Error type
        PLNK_AUDIO_DEVICE_TYPE_UNDEFINED = 0,
        /// Input device such as a microphone
        PLNK_AUDIO_DEVICE_TYPE_MIC,
        /// Output device such as a speaker
        PLNK_AUDIO_DEVICE_TYPE_SPEAKER
    } EAudioDeviceType;

    /**
     * EAudioDeviceType represents whether a device is an input or output device.<br>
     * However, some devices such as a two-way communicator require additional information to be recognized.<br>
     * For example, a two-way communicator such as a headphone is treated as both a microphone and a speaker, but is recognized by the OS as a microphone.<br>
     * If you want devices to be recognized more specifically, then use this value.<br>
     * @see https://docs.microsoft.com/en-us/windows/win32/coreaudio/pkey-audioendpoint-formfactor <br>
     */
    typedef enum EPhysicalFormFactor {
        /// Remote network device
        PLNK_PHYSICAL_FORM_FACTOR_REMOTE_NETWORK_DEVICE = 0,
        /// Speakers
        PLNK_PHYSICAL_FORM_FACTOR_SPEAKERS,
        /// Line level
        PLNK_PHYSICAL_FORM_FACTOR_LINE_LEVEL,
        /// Headphones
        PLNK_PHYSICAL_FORM_FACTOR_HEADPHONES,
        /// Mic
        PLNK_PHYSICAL_FORM_FACTOR_MIC,
        /// Headset
        PLNK_PHYSICAL_FORM_FACTOR_HEADSET,
        /// Handset
        PLNK_PHYSICAL_FORM_FACTOR_HANDSET,
        /// Digital pass through
        PLNK_PHYSICAL_FORM_FACTOR_UNKNOWN_DIGITAL_PASS_THROUGH,
        /// SPDIF
        PLNK_PHYSICAL_FORM_FACTOR_SPDIF,
        /// Digital audio display device
        PLNK_PHYSICAL_FORM_FACTOR_DIGITAL_AUDIO_DISPLAY_DEVICE,
        /// Unknown
        PLNK_PHYSICAL_FORM_FACTOR_UNKNOWN_FORM_FACTOR,
        /// Max count value (not used)
        PLNK_PHYSICAL_FORM_FACTOR_COUNT,
        /// None
        PLNK_PHYSICAL_FORM_FACTOR_NONE
    }EPhysicalFormFactor;


    /**
     * Audio data sample format
     */
    typedef enum EAudioDataSampleType {
        /// Sample format float
        PLNK_AUDIO_DATA_SAMPLE_TYPE_FLOAT_32,
        /// Sample format short
        PLNK_AUDIO_DATA_SAMPLE_TYPE_SHORT16

    } EAudioDataSampleType;

    /**
     * Audio device sampling rate
     */
    typedef enum EAudioDeviceSamplingRate {
        /// 48kHz
        SAMPLING_RATE_48K = 0,
        /// 32kHz
        SAMPLING_RATE_32K = 1,
        /// 16kHz
        SAMPLING_RATE_16K = 2,
        /// Max count (not used)
        SAMPLING_RATE_COUNT = 3

    } EAudioDeviceSamplingRate;

    /**
     * Audio sample type.
     */
    typedef enum EAudioSampleType {
        /// type float32
        PLNK_AUDIO_SAMPLE_TYPE_SIGNED_FLOAT32 = 0,
        /// type short16
        PLNK_AUDIO_SAMPLE_TYPE_SIGNED_SHORT16 = 1
    } EAudioSampleType;

    /// Acoustic Echo Canceller value
    typedef enum EPlanetKitAcousticEchoCanceller {
        /// Disabled
        PLNK_ACOUSTIC_ECHO_CANCELLER_DISABLED = 0,
        /// The recommended value<br>Default
        PLNK_ACOUSTIC_ECHO_CANCELLER_INTENSITY_RECOMMENDED = 1,
        /// Min
        PLNK_ACOUSTIC_ECHO_CANCELLER_INTENSITY_MIN = 2,
        /// Max
        PLNK_ACOUSTIC_ECHO_CANCELLER_INTENSITY_MAX = 3,
        /// Adaptive
        PLNK_ACOUSTIC_ECHO_CANCELLER_INTENSITY_ADAPTIVE = 4
    }EPlanetKitAcousticEchoCanceller;

    /// Auto Gain Control value
    typedef enum EPlanetKitAutoGainControl {
        /// Disabled
        PLNK_AUTO_GAIN_CONTROL_TYPE_DISABLED = 0,
        /// Use AGC by using software
        PLNK_AUTO_GAIN_CONTROL_TYPE_SOFTWARE = 1,
        /// Use AGC by using hardware<br>Default
        PLNK_AUTO_GAIN_CONTROL_TYPE_HARDWARE = 2,
        /// Use AGC by using hardware. 
        /// Adjusts the input gain based on the speaker's voice level, even when echo is present in the environment.
        PLNK_AUTO_GAIN_CONTROL_TYPE_HARDWARE_ECHO_TOLERANCE = 3,
    } EPlanetKitAutoGainControl;

    /// Noise Suppressor mode value
    typedef enum EPlanetkitNoiseSuppressorMode {
        /// Disabled
        PLNK_NOISE_SUPPRESSOR_MODE_DISABLED = 0,
        /// Enabled<br>Default
        PLNK_NOISE_SUPPRESSOR_MODE_ENABLE = 1,
    } EPlanetkitNoiseSuppressorMode;

    /**
     * Audio data
     */
    typedef struct SAudioData {
        /// Sampling rate
        unsigned int unAudioDataSamplingRate;
        /// Sample count
        unsigned int unAudioDataSampleCount;
        /// Sample format
        EAudioDataSampleType eAudioDataSampleFormat;
        /// Audio data buffer
        unsigned char* ucBuffer;
        /// Size of buffer
        unsigned int unBufferSize;
    } SAudioData;

    /**
     * Audio device volume information
     */
    typedef struct SAudioEndpointVolumeInfo {
        /// Mute flag
        bool bMuted;
        /// Device master volume
        float fMasterVolume;
    } SAudioEndpointVolumeInfo;

    /**
     * @brief Audio description of a peer, which can be obtained with IConferenceEvent::OnPeersAudioDescriptionUpdated
     */
    struct PLANETKIT_API PeerAudioDescription {
        /// Peer's user ID
        UserIdPtr pUserId;
        /// Peer's average volume level[0:100]
        unsigned char ucVolume;
        /// Name of the subgroup from which this audio originated. The value can be NullOptional, which means PlanetKitMainRoomName.
        WStringOptional strSentSubgroupName;
        /// Name of the subgroup where this audio was tagged by the peer. The value can be NullOptional, which means PlanetKitMainRoomName.
        WStringOptional strTaggedSubgroupName;
    };

    typedef Array<PeerAudioDescription> PeerAudioDescriptionArray;

    /**
     * @brief Audio description of the local user, which can be obtained with IConferenceEvent::OnMyAudioDescriptionUpdated or IMyMediaStatusEvent::OnMyAudioDescriptionUpdated
     */
    struct PLANETKIT_API MyAudioDescription {
        /// Local user's average volume level[0:100]
        unsigned char ucVolume;
        /// Name of the subgroup from which this audio originated. The value can be NullOptional, which means PlanetKitMainRoomName.
        WStringOptional strSentSubgroupName;
        /// Name of the subgroup where this audio was tagged by the peer. The value can be NullOptional, which means PlanetKitMainRoomName.
        WStringOptional strTaggedSubgroupName;
    };

    /**
     * Struct of audio data.
     */
    struct PLANETKIT_API AudioData {
        /// Buffer size of audio data
        unsigned int unBufferSize = 0;
        /// Audio data
        PlanetKitByte* pBuffer = nullptr;
    };

    /// @brief Peer Volume Result
    struct PLANETKIT_API VolumeResult {
        /// Volume Level(Optional) [0:100]
        ByteOptional ucAverageVolumeLevel;
        /// Reasons why ucAverageVolumeLevel is not exist
        EPeerGetFailReason ePeerGetFailReason = EPeerGetFailReason::PLNK_PEER_GET_FAIL_REASON_NONE;
    };

    struct PLANETKIT_API AudioDescriptionInfo {
        bool bEnableAudioDescription = true;
        unsigned int unAudioDescriptionInterval = 500;
    };
}