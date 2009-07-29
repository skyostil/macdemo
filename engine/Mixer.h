/**
 * Copyright (C) 2009 Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 */
#ifndef MIXER_H
#define MIXER_H

#include "Engine.h"
#include "Audio.h"

// 16 bit internal mixing
class Channel
{
public:
        Channel(int _outputFreq = 0);

        bool    isActive();
        
        inline Sample8 play()
        {
            Sample8 a;
            
            //if (!sample)
            //        return 0;
            
            if (loopLength)
            {
                if (pos>=loopEnd)
                {
                    pos-=loopLength;
                }                
            }
            else if (pos >= sample->length)
            {
                sample = 0;
                return 0;
            }

            //switch(sample->format.bytesPerSample)
            //{
            //case 1:
            //        a = (sample->data[pos] * volume);
                    a = (sample->data[pos]);
            //break;
            //case 2:
            //        a = (((Sample16*)sample->data)[pos] * volume) >> 8;
            //break;
            //}
            
            counter += lspeed;
            pos += hspeed;
            
            if (counter>0xffff)
            {
                counter -= 0xffff;
                pos++;
            }
            
            return a;
        }
        
        void    start(SampleChunk *_sample, int _freq, int _loopStart = 0, int _loopLength = 0);
        void    playSample(SampleChunk *sample, int freq, bool loop = false);
        void    setFrequency(int _freq);
        void    setOutputFrequency(int _outputFreq);
        void    setSample(SampleChunk *_sample);
        void    setPosition(int _pos);
        void    setVolume(int _volume);
        void    stop();

        SampleChunk             *sample;
        int                     pos, counter, freq;
        int                     lspeed, hspeed;
        int                     loopStart, loopLength, loopEnd;
        int                     volume;
        int                     outputFreq;
        char                    padding[20];
};

class Ticker
{
public:
        virtual void tick() = 0;
};

class Mixer: public AudioRenderer
{
public:
        Mixer(int _outputFreq, int _channelCount = 4);
        ~Mixer();

        void    render(SampleChunk *buffer);
        void    installTicker(Ticker *t, int hz);
        
        //! \returns the channel the sample ended up on.
        Channel *playSample(SampleChunk *sample, int freq, bool loop = false, int ch = -1);
        Channel *getChannel(int ch) const;

        int     channelCount;
        int     outputFreq;
protected:
        Channel *channel;
        Ticker  *ticker;
        int     tickerCounter, tickerInterval;
};

#endif
