//
// Created by Homepunk on 16.01.2020.
//

#ifndef AUDIO_FREQUENCY_FILTER_AUDIOENGINE_H
#define AUDIO_FREQUENCY_FILTER_AUDIOENGINE_H


#include <oboe/AudioStreamCallback.h>
#include <oboe/AudioStreamBuilder.h>
#include "AudioFile.h"
#include "../../lib-oboe/samples/hello-oboe/src/main/cpp/HelloOboeEngine.h"
#include "../decoder/WavDecoder.h"

class AudioEngine : oboe::AudioStreamCallback {
public:
    AudioEngine();

    ~AudioEngine();

    void load(const char **filePaths, int nbFilePaths);

    void play(int id);

    oboe::DataCallbackResult
    onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames);

    void onErrorAfterClose(oboe::AudioStream *oboeStream, oboe::Result error);

private:
    oboe::AudioStream *mPlayStream;

    oboe::AudioApi mAudioApi = oboe::AudioApi::Unspecified;
    int32_t mPlaybackDeviceId = oboe::kUnspecified;
    int32_t mChannelCount = 2;

    int32_t mFramesPerBurst;
    int32_t mBufferSizeSelection = kBufferSizeAutomatic;

    std::unique_ptr<oboe::LatencyTuner> mLatencyTuner;
    std::mutex mRestartingLock;

    WavDecoder *wavDecoder;

    void setUpPlaybackStream();

    void setupAudioStreamBuilder(oboe::AudioStreamBuilder *builder);

    void restartStream();

    void closeOutputStream();
};


#endif //AUDIO_FREQUENCY_FILTER_AUDIOENGINE_H
