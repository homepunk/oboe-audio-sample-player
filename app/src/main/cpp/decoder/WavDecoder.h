//
// Created by Homepunk on 17.01.2020.
//

#ifndef AUDIO_FREQUENCY_FILTER_WAVDECODER_H
#define AUDIO_FREQUENCY_FILTER_WAVDECODER_H

#include <cstdint>

class WavDecoder {
public:
    void render(int16_t *buffer, int channel, int32_t channelStride, int32_t numFrames);

    void render(float *buffer, int channel, int32_t channelStride, int32_t numFrames);

    const void load(const char **filePaths, int nbFilePaths);

};


#endif //AUDIO_FREQUENCY_FILTER_WAVDECODER_H
