/**
 * Copyright (C) 2009 Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 */
#ifndef AUDIO_H
#define AUDIO_H

#include "Engine.h"

class AudioRenderer
{
public:
    virtual void render(SampleChunk *buffer) = 0;
};

class Audio
{
public:
    Audio(int bits, int mixFreq, bool stereo, int bufferSize);
    ~Audio();
    void start(AudioRenderer* renderer);
    void stop();
    int mixFreq();
    const SampleFormat& format() const;
};

#endif
