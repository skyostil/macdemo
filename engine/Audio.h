/**
 * Copyright (C) 2009 Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 */
#ifndef AUDIO_H
#define AUDIO_H

#include "Mixer.h"

class Audio
{
public:
    Audio(int bits, int mixFreq, bool stereo, int bufferSize);
    ~Audio();
    void start(Mixer* mixer);
    void stop();
    int mixFreq();
};

#endif
