/**
 *  Copyright (C) 2009 by Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 */
#include "Audio.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <SDL.h>

static AudioRenderer* _renderer = 0;
static SDL_AudioSpec  _audioSpec;
static SampleFormat   _sampleFormat(0, 0, false);
static bool           _monoUpMix = false;
static bool           _8bitUpMix = false;

static void audioCallback(void* userData, Uint8* stream, int len)
{
    if (!_renderer)
    {
        return;
    }
    int mixLen = len / (_sampleFormat.bytesPerSample * _sampleFormat.channels);
    if (_monoUpMix && _8bitUpMix)
    {
        mixLen /= 2;
    }

    SampleChunk chunk(&_sampleFormat, (Sample8*)stream,
                      mixLen, _audioSpec.freq);
    _renderer->render(&chunk);

    if (_monoUpMix && _8bitUpMix)
    {
        assert(_sampleFormat.bytesPerSample == 1);
        int i;
        // mono & 16bit expansion
        for (i = len / 4; i >= 0; i--)
        {
            stream[i * 4] = 
            stream[i * 4 + 1] = 
            stream[i * 4 + 2] = 
            stream[i * 4 + 3] = stream[i];
        }
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
        printf("Unable to open audio device.\n");
    }
    printf("Audio: format 0x%x, %d channels, %d Hz\n", _audioSpec.format, _audioSpec.channels, _audioSpec.freq);

    bool signedData = false;
    if (_audioSpec.format == AUDIO_S8 || _audioSpec.format == AUDIO_S16LSB ||
        _audioSpec.format == AUDIO_S16MSB || _audioSpec.format == AUDIO_S16)
    {
        signedData = true;
    }

    _sampleFormat = SampleFormat(bits, _audioSpec.channels, signedData);

    if (_audioSpec.channels > 1 && !stereo)
    {
        _monoUpMix = true;
    }

    if (!(_audioSpec.format == AUDIO_S8 || _audioSpec.format == AUDIO_U8) && bits == 8)
    {
        _8bitUpMix = true;
    }

    assert((_monoUpMix && _8bitUpMix) || (!_monoUpMix && !_8bitUpMix));
}

Audio::~Audio()
{
    stop();
    SDL_CloseAudio();
}

void Audio::start(AudioRenderer* renderer)
{
    _renderer = renderer;
    SDL_PauseAudio(0);
}

void Audio::stop()
{
    SDL_PauseAudio(1);
    _renderer = 0;
}

int Audio::mixFreq()
{
    return _audioSpec.freq;
}

const SampleFormat& Audio::format() const
{
    return _sampleFormat;
}

