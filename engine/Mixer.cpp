/**
 * Copyright (C) 2009 Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 */

#include "Mixer.h"
#include <string.h>

extern int getTicks();

Channel::Channel(int _outputFreq):
        sample(0),
        pos(0),
        lspeed(0),
        hspeed(0),
        loopStart(0),
        loopLength(0),
        outputFreq(_outputFreq),
        volume(64)
{
}

bool Channel::isActive()
{
        return sample != 0;
}

void Channel::start(SampleChunk *_sample, int _freq, int _loopStart, int _loopLength)
{
        counter = 0;
        loopStart = _loopStart;
        loopLength = _loopLength;
        loopEnd = _loopStart + _loopLength;
        setSample(_sample);
        setPosition(0);
        setFrequency(_freq);
}

void Channel::stop()
{
        sample = 0;
}

void Channel::playSample(SampleChunk *sample, int freq, bool loop)
{
        start(sample, freq, 0, loop?sample->length:0);
}

void Channel::setFrequency(int _freq)
{
        freq = _freq;
        hspeed = _freq  / outputFreq;
        lspeed = ((_freq % outputFreq)<<16) / outputFreq;
}

void Channel::setSample(SampleChunk *_sample)
{
        sample = _sample;
}

void Channel::setPosition(int _pos)
{
        pos = _pos;
}

void Channel::setVolume(int _volume)
{
        volume = _volume;
}

void Channel::setOutputFrequency(int _outputFreq)
{
        outputFreq = _outputFreq;
}


Mixer::Mixer(int _outputFreq, int _channelCount):
        channelCount(_channelCount),
        outputFreq(_outputFreq),
        ticker(0)
{
        int ch;

        tickerCounter = 0;
        tickerInterval = 0x7fffffff;

        channel = new Channel[channelCount];
        for(ch=0; ch<channelCount; ch++)
                channel[ch].setOutputFrequency(outputFreq);
}

Mixer::~Mixer()
{
        delete[] channel;
}

void Mixer::render(SampleChunk *buffer)
{
        int ch;
        int count = buffer->length;

#if 0
        //ticker->tick();
        
        //int j;
        //for (j = 0; j < buffer->length; j++)
        //	buffer->data[j] = j << 4;

        //if (!ticker)
        if (0)
        {
            //memset(buffer->data, 0, buffer->bytes);
            return;
        }
        
        //memset(buffer->data, 0, buffer->bytes / 4);
        //return;
        switch(buffer->format.bytesPerSample)
        {
        case 2:
        {
                Sample16 *data = (Sample16*)buffer->data;

                while (count--)
                {
                        Sample32 a = 0;

                        for (ch=0; ch<channelCount; ch++)
                        {
                                if (channel[ch].sample)
                                {
                                    a+=channel[ch].play();
                                }
                        }

//                      *data++ = a / (channelCount*2);
//                      *data++ = a / (1);
                        *data++ = a >> 2;

                        if (++tickerCounter == tickerInterval)
                        {
                                tickerCounter = 0;
                                //ticker->tick();
                        }
                }
        }
        break;
        case 1:
        {
#endif
                Sample8 *data = (Sample8*)buffer->data;

//                                if (channelMask & (1 << channelNum))
//               								channelMask &= ~(1 << channelNum);
#define MIX_CHANNEL(channelNum) \
                                if (c->sample && c->pos <= c->sample->length)\
                                {\
                                    if (c->loopLength && \
                                        c->pos>=c->loopEnd) \
                                    { \
                                        c->pos-=c->loopLength;\
                                    }\
                                    else\
                                    {\
                                        a += (c->sample->data[c->pos]);\
                                        c->pos += c->hspeed;\
                                        c->counter += c->lspeed;\
                                        if (c->counter >> 16)\
                                        {\
                                            c->counter -= 0xffff;\
                                            c->pos++;\
                                        }\
                                    }\
                                }
#if 1
                Sample16 a;
                Channel* c;
				
                while (count)
                {
                        int dt = tickerInterval - tickerCounter;
                        int run = count < dt ? count : dt;
                		
                        count -= run;
                        tickerCounter += run;

                        while (run--)
                        {
                                a = 0;
                                c = &channel[0];
                                MIX_CHANNEL(0)
                                c++;
                                MIX_CHANNEL(1)
                                c++;
                                MIX_CHANNEL(2)
                                c++;
                                MIX_CHANNEL(3)
#if defined(CODEWARRIOR) || defined(_MSC_VER)
								/* Yay for portability */
                                *data++ = (a >> 2) ^ 0x80;
#else
                                *data++ = (a >> 2);
#endif
                        }

//                      *data++ = (a/(channelCount*2))>>8;
//                        *data = (unsigned char)((a>>8));
//                        *data ^= 0x80;
//						data++;

                        if (tickerCounter == tickerInterval)
                        {
                            tickerCounter = 0;
                            ticker->tick();
//                                channelMask = 0;
//                                for (ch=0; ch<channelCount; ch++)
//                                {
//                                    Channel* c = &channel[ch];
//                                    if (c->sample)
//                                    {
//                                    	channelMask |= (1 << ch);
//                                    }
//                                }
                        }
                }
#else
                while (count--)
                {
                        Sample16 a = 0;

                        for (ch=0; ch<channelCount; ch++)
                        {
                                //if (channel[ch].isActive())
                                Channel* c = &channel[ch];
                                if (c->sample)
                                {
                                        //a+=channel[ch].play();
                                        //a+=(Sample16)channel[ch].sample;
						                if (c->loopLength)
	          								if (c->pos>=c->loopEnd)
                        				{
                            				c->pos-=c->loopLength;
                        				}
				        		        else if (c->pos >= c->sample->length)
										{
               								c->sample = 0;
											continue;
										}
				                        a += (c->sample->data[c->pos]);
		        				        c->counter += c->lspeed;
                						c->pos += c->hspeed;
                
                						if (c->counter >> 16)
               							{
                        					c->counter -= 0xffff;
                        					c->pos++;
										}
                        		}
                        }

//                      *data++ = (a/(channelCount*2))>>8;
//                        *data = (unsigned char)((a>>8));
//                        *data ^= 0x80;
//						data++;
                        *data++ = (a >> 2);

                        if (++tickerCounter == tickerInterval)
                        {
                                tickerCounter = 0;
                                ticker->tick();
                        }
                }
#endif
#if 0
        }
        break;
        };
#endif
}

Channel *Mixer::playSample(SampleChunk *sample, int freq, bool loop, int ch)
{
        if (ch == -1)
        {
                for(ch=0; ch<channelCount-1; ch++)
                        if (!channel[ch].isActive())
                                break;
        }
        channel[ch].start(sample, freq, 0, loop?sample->length:0);

        return &channel[ch];
}

void Mixer::installTicker(Ticker *t, int hz)
{
        ticker = t;
        tickerCounter = 0;

        if (t && hz)
        {
            tickerInterval = outputFreq / hz;
        }
}

Channel *Mixer::getChannel(int ch) const
{
    if (ch < channelCount)
        return &channel[ch];
    return 0;
}
