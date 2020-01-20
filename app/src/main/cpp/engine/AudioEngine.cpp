//
// Created by Homepunk on 16.01.2020.
//

#include "AudioEngine.h"
#include "../../lib-oboe/samples/hello-oboe/src/main/cpp/HelloOboeEngine.h"
#include "../../lib-oboe/apps/OboeTester/app/src/main/cpp/android_debug.h"


AudioEngine::AudioEngine() {
    wavDecoder = new WavDecoder();
    setUpPlaybackStream();
}

AudioEngine::~AudioEngine() {
    delete wavDecoder;
    closeOutputStream();
}


void AudioEngine::setupAudioStreamBuilder(oboe::AudioStreamBuilder *builder) {
    builder->setAudioApi(mAudioApi);
    builder->setDeviceId(mPlaybackDeviceId);
    builder->setChannelCount(mChannelCount);
    builder->setSharingMode(oboe::SharingMode::Exclusive);
    builder->setPerformanceMode(oboe::PerformanceMode::LowLatency);
    builder->setCallback(this);
}

oboe::DataCallbackResult
AudioEngine::onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) {
    int32_t bufferSize = audioStream->getBufferSizeInFrames();

    if (mBufferSizeSelection == kBufferSizeAutomatic) {
        mLatencyTuner->tune();
    } else if (bufferSize != (mBufferSizeSelection * mFramesPerBurst)) {
        audioStream->setBufferSizeInFrames(mBufferSizeSelection * mFramesPerBurst);
    }
    int32_t channelCount = audioStream->getChannelCount();
    if (audioStream->getFormat() == oboe::AudioFormat::Float) {
        for (int i = 0; i < channelCount; ++i) {
            wavDecoder->render(static_cast<float *>(audioData) + i, i, channelCount,
                                 numFrames);
        }
    } else {
        for (int i = 0; i < channelCount; ++i) {
            wavDecoder->render(static_cast<int16_t *>(audioData) + i, i, channelCount,
                                 numFrames);
        }
    }
    return oboe::DataCallbackResult::Continue;
}

void AudioEngine::onErrorAfterClose(oboe::AudioStream *oboeStream, oboe::Result error) {
    if (error == oboe::Result::ErrorDisconnected) restartStream();
}

void AudioEngine::restartStream() {
    if (mRestartingLock.try_lock()) {
        closeOutputStream();
        setUpPlaybackStream();
        mRestartingLock.unlock();
    } else {
        LOGW("Restart stream operation already in progress - ignoring this request");
    }
}

void AudioEngine::load(const char **filePaths, int nbFilePaths) {

}

void AudioEngine::play(int id) {

}

void AudioEngine::setUpPlaybackStream() {
    oboe::AudioStreamBuilder builder;
    setupAudioStreamBuilder(&builder);

    oboe::Result result = builder.openStream(&mPlayStream);
    if (result == oboe::Result::OK && mPlayStream != nullptr) {
        mFramesPerBurst = mPlayStream->getFramesPerBurst();

        int channelCount = mPlayStream->getChannelCount();

        if (channelCount != mChannelCount) {
            LOGW("Requested %d channels but received %d", mChannelCount, channelCount);
        }
        mPlayStream->setBufferSizeInFrames(mFramesPerBurst);
        mLatencyTuner = std::unique_ptr<oboe::LatencyTuner>(new oboe::LatencyTuner(*mPlayStream));

        result = mPlayStream->requestStart();
        if (result != oboe::Result::OK) {
            LOGE("Error starting stream. %s", oboe::convertToText(result));
        }
    } else {
        LOGE("Failed to create stream. Error: %s", oboe::convertToText(result));
    }
}

void AudioEngine::closeOutputStream() {
    if (mPlayStream != nullptr) {
        oboe::Result result = mPlayStream->requestStop();
        if (result != oboe::Result::OK) {
            LOGE("Error stopping output stream. %s", oboe::convertToText(result));
        }

        result = mPlayStream->close();
        if (result != oboe::Result::OK) {
            LOGE("Error closing output stream. %s", oboe::convertToText(result));
        }
    }
}
