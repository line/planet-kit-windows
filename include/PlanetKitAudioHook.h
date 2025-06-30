#pragma once
#include "PlanetKit.h"

namespace PlanetKit {
    /**
     * Struct of audio data.
     */
    typedef struct AudioData {
        /// Buffer size of audio data
        unsigned int unBufferSize = 0;
        /// Audio data
        PlanetKitByte* pBuffer = nullptr;
    }AudioData;

    /**
     * Audio sample type.
     */
    typedef enum EAudioSampleType {
        /// type float32
        PLNK_AUDIO_SAMPLE_TYPE_SIGNED_FLOAT32 = 0,
        /// type short16
        PLNK_AUDIO_SAMPLE_TYPE_SIGNED_SHORT16 = 1
    } EAudioSampleType;

    class PLANETKIT_API PlanetKitHookedAudio;
    typedef AutoPtr<PlanetKitHookedAudio> PlanetKitHookedAudioPtr;

    /**
     * Defines the audio data used for the local user's audio modification feature.<br>
     * The audio is received through IPlanetKitAudioHook, and the modified audio is applied using SetAudioData.
     */
    class PLANETKIT_API PlanetKitHookedAudio : public Base {
    public:
        /**
         * Sample rate of audio data.
         */
        virtual const unsigned int GetSampleRate() = 0;

        /**
         * The number of channels.
         */
        virtual const unsigned int GetChannel() = 0;

        /**
         * The sample type.
         */
        virtual const EAudioSampleType GetAudioSampleType() = 0;

        /**
         * The sample count for each channel.
         */
        virtual const unsigned int GetSampleCount() = 0;

        /**
         * The sequence number of audio data.
         */
        virtual const unsigned long long GetSequenceNumber() = 0;

        /**
         * Sets raw data of audio.
         * @param pBuffer Raw data of audio.
         * @param unBufferSize Raw data buffer size.
         * @return true on success
         * @remark
         *  - If you want to modify the audio data, you can set the modified data using SetAudioData.<br>
         *  - The audio data size is determined by the sample rate, channel, sample count, and sample type.<br>
         *  - Currently, the sample rate, channel, sample count, and sample type are fixed values, so the buffer size cannot be changed.<br>
         *  - Therefore, even if you modify the data obtained with GetAudioData and set it with SetAudioData, the buffer size must match the size of the audio data obtained with GetAudioData.
         */
        virtual bool SetAudioData(const PlanetKitByte* pBuffer, unsigned int unBufferSize) = 0;

        /*
         * Gets raw data of audio.
         */
        virtual const AudioData GetAudioData() = 0;
    };

    /**
     * This is an interface used for audio reception in PlanetKitCall::EnableHookMyAudio.
     * @see PlanetKitCall::EnableHookMyAudio
     * @see PlanetKitCall::DisableHookMyAudio
     * @see PlanetKitCall::PutHookedMyAudioBack
     */
    class PLANETKIT_API IPlanetKitAudioHook {
    public:
        /**
         * @param pHookedAudio Audio frame data sent to peer.
         */
        virtual void OnHooked(PlanetKitHookedAudioPtr pHookedAudio) = 0;
    };
}