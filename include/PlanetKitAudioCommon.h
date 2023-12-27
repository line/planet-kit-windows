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

#define MAX_DEVICE_ID_SIZE 512
#define MAX_DEVICE_NAME_SIZE 512

#include "PlanetKit.h"

namespace PlanetKit 
{
    /**
     * Audio device type
     */
    typedef enum EAudioDeviceType
    {
        /// Error type
        PLNK_AUDIO_DEVICE_TYPE_UNDEFINED = 0,
        /// Input device such as a microphone
        PLNK_AUDIO_DEVICE_TYPE_INPUT,
        /// Output device such as a speaker
        PLNK_AUDIO_DEVICE_TYPE_OUTPUT
    } EAudioDeviceType;
    
    /**
     * EAudioDeviceType represents whether a device is an input or output device.<br>
     * However, some devices such as a two-way communicator require additional information to be recognized.<br>
     * For example, a two-way communicator such as a headphone is treated as both a microphone and a speaker, but is recognized by the OS as a microphone.<br>
     * If you want devices to be recognized more specifically, then use this value.<br>
     * @see https://docs.microsoft.com/en-us/windows/win32/coreaudio/pkey-audioendpoint-formfactor <br>
     */
    typedef enum EPhysicalFormFactor
    {
        /// Remote network device
        PLNK_PHYSICAL_FORM_FACTOR_REMOTE_NETWORK_DEVICE = 0,
        /// Speakers
        PLNK_PHYSICAL_FORM_FACTOR_SPEAKERS,
        /// Line level
        PLNK_PHYSICAL_FORM_FACTOR_LINE_LEVEL,
        /// Headphones
        PLNK_PHYSICAL_FORM_FACTOR_HEADPHONES,
        /// Microphone
        PLNK_PHYSICAL_FORM_FACTOR_MICROPHONE,
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

    PLANETKIT_DEPRECATED("This will not be supported in 5.1 or later.")
    /**
     * @deprecated This will not be supported in 5.1 or later.
     * @see AudioDeviceInfo
     */
    class SAudioDeviceInfo : public Base
    {
    public :
        /// Device id
        wchar_t wszID;
        /// Device name
        wchar_t wszName;
        /// Device type
        EAudioDeviceType eAudioDeviceType = EAudioDeviceType::PLNK_AUDIO_DEVICE_TYPE_UNDEFINED;
        /// Physical form factor of device
        EPhysicalFormFactor ePhysicalFormFactor = EPhysicalFormFactor::PLNK_PHYSICAL_FORM_FACTOR_NONE;

    };

    /**
     * Audio device information class
     */
    class AudioDeviceInfo : public Base
    {
    public:
        /// Device ID
        virtual const WString& GetID() = 0;
        /// Device name
        virtual const WString& GetName() = 0;
        /// Device type
        virtual EAudioDeviceType GetDeviceType() = 0;
        /// Physical form factor of the device
        virtual EPhysicalFormFactor GetFormFactor() = 0;
    };

    typedef AutoPtr<AudioDeviceInfo> AudioDeviceInfoPtr;
    typedef Array<AudioDeviceInfoPtr> AudioDeviceInfoArray;

    /**
     * Audio data sample format
     */
    typedef enum EAudioDataSampleFormat
    {
        /// Sample format float
        PLNK_AUDIO_DATA_SAMPLE_FORMAT_FLOAT_32,
        /// Sample format short
        PLNK_AUDIO_DATA_SAMPLE_FORMAT_SHORT

    } EAudioDataSampleFormat;

    /**
     * Audio device sampling rate
     */
    typedef enum EAudioDeviceSamplingRate
    {
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
     * Audio data
     */
    typedef struct SAudioData
    {
        /// Sampling rate
        unsigned int            unAudioDataSamplingRate;
        /// Sample count
        unsigned int            unAudioDataSampleCount;
        /// Sample format
        EAudioDataSampleFormat  eAudioDataSampleFormat;
        /// Audio data buffer
        unsigned char           *ucBuffer;
        /// Size of buffer
        unsigned int            unBufferSize;
    } SAudioData;

    /**
     * Audio device volume information
     */
    typedef struct SAudioEndpointVolumeInfo
    {
        /// Mute flag
        bool bMuted;
        /// Device master volume
        float fMasterVolume;
    } SAudioEndpointVolumeInfo;
}