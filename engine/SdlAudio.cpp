/**
 *  Copyright (C) 2009 by Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 */
#include "Audio.h"
#include <stdio.h>
#include <string.h>
#include <SDL.h>

static Mixer*        _mixer = 0;
static SDL_AudioSpec _audioSpec;

static void audioCallback(void* userData, Uint8* stream, int len)
{
    if (!_mixer)
    {
        return;
    }
}

Audio::Audio(int bits, int mixFreq, bool stereo, int bufferSize)
{
    SDL_AudioSpec audio;

    memset(&audio, 0, sizeof(SDL_AudioSpec));
    audio.freq = mixFreq;
    audio.format = (bits == 8) ? AUDIO_S8 : AUDIO_S16;
    audio.channels = stereo ? 2 : 1;
    audio.samples = bufferSize;
    audio.callback = audioCallback;
    audio.userdata = NULL;

    if (SDL_OpenAudio(&audio, &_audioSpec))
    {
        fprintf(stderr, "Unable to open audio device.\n");
    }
}

Audio::~Audio()
{
    stop();
    SDL_CloseAudio();
}

void Audio::start(Mixer* mixer)
{
    _mixer = mixer;
    SDL_PauseAudio(0);
}

void Audio::stop()
{
    SDL_PauseAudio(1);
}

int Audio::mixFreq()
{
    return _audioSpec.freq;
}
