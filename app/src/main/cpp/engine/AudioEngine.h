//
// Created by Homepunk on 16.01.2020.
//

#ifndef AUDIO_FREQUENCY_FILTER_AUDIOENGINE_H
#define AUDIO_FREQUENCY_FILTER_AUDIOENGINE_H


#include "AudioFile.h"

class AudioEngine {
public:
    void add(int index, AudiFile file);

    void play(int index, AudiFile file);

    void play_together(int indexes[]);

    void play_sequentially(int indexes[]);

    void pause(int indexes[]);

    void stop(int indexes[]);

private:
//    todo: setup audio files array
};


#endif //AUDIO_FREQUENCY_FILTER_AUDIOENGINE_H
