/**
 * Copyright (C) 2009 Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 */
#ifndef MODPLAYER_H
#define MODPLAYER_H

// PAL
#define MOD_FREQ_BASE   (int)(7159090.5)

// NTSC
//#define MOD_FREQ_BASE (int)(7093789.2)

//#define MOD_USE_TAGFILE
//#define MOD_USE_TAGFILE_SAVING
//#define MOD_USE_FINETUNING

#include "Mixer.h"
#include "Engine.h"

class ModPlayer: private Ticker
{
public:
    ModPlayer(Mixer *_mixer);
    virtual ~ModPlayer();

    bool    load(const char *file);
    void    unload();
    void    play();
    void    stop();
#ifdef MOD_USE_TAGFILE
    bool    loadTagFile(const char *fileName);
#ifdef MOD_USE_TAGFILE_SAVING
    bool    save(const char *fileName) const;
#endif
#endif

    //! \param vol is in the range [0, 64]
    void    setVolume(int vol);

    Mixer   *mixer;

protected:
    unsigned short  bigEndian16(unsigned short b);
    int             amigaToHz(int period);
    int             calcVolume(int v);

    class ModSample
    {
    public:
        ModSample(int _length, char _fineTune, char _volume, unsigned short _loopStart, unsigned short _loopLength);
        ~ModSample();

        SampleChunk             *sample;
        signed char             fineTune, volume;
        unsigned short          loopStart, loopLength;
        char                    padding[6];
    };

    class ModNote
    {
    public:
        unsigned char   sampleNumber;
        unsigned short  amigaPeriod;
        signed short    note;
        unsigned char   effectNumber;
        unsigned char   effectParameter;
        char            padding[1];
    };

    class ModChannel
    {
    public:
        ModChannel();

        ModSample       *sample;
        signed char     volume;
        unsigned short  amigaPeriod;
        short           note;

        unsigned char   portaSpeed;
        unsigned short  portaTarget;    // amiga period
        bool            glissando;

        //              char            vibratoWaveform;
        //              char            vibratoWaveformRetrig;  // four bits
        signed char     vibratoDepth;
        signed char     vibratoSpeed;
        signed char     vibratoPos;
        signed char     vibratoNeg;

        //              char            tremoloWaveform;
        //              char            tremoloWaveformRetrig;  // four bits
        signed char     tremoloDepth;
        signed char     tremoloSpeed;
        signed char     tremoloPos;
        signed char     tremoloNeg;

        signed char     arpeggioCounter;

        signed char     loopRow;
        signed char     loopCounter;
        
        char            padding[3];
    };

    ModSample       *sample[31];
    ModNote         *note;
    ModChannel      *channel;
    int             channels;
    signed char     *order;
    signed char     songLength, songSpeed;
    signed char     patternCount;
    signed char     currentOrder;
    signed char     currentTick;
    signed char     currentRow;
    signed char     patternDelay;
    bool            playing;
    signed char     volume;

private:
    void    tick();
    void    playNote(int ch, ModNote *n);
};

#endif
