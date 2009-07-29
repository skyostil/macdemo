/**
 * Simple MOD player
 * Copyright (C) 2004-2009 Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 *                                                                         
 *   The following features/effects are NOT implemented:                   
 *                                                                         
 *     - effect 8xy (pan)                                                  
 *     - effect e0x (set filter)                                           
 *     - effect e4x (set vibrato waveform)                                 
 *     - effect e7x (set tremolo waveform)                                 
 *     - effect efx (invert loop)                                          
 *     - old 15 sample mods                                                
 *     - the portas are somewhat buggy                                     
 */
#include "ModPlayer.h"

#ifdef MOD_USE_TAGFILE
#include "TagFile.h"
#include <string.h>
#endif

#include "Config.h"
#include <stdio.h>
#include <assert.h>

static const unsigned short periodTable[][36] =
{
        {
        // Tuning 0, Normal
                856,808,762,720,678,640,604,570,538,508,480,453, // C-1 to B-1
                428,404,381,360,339,320,302,285,269,254,240,226, // C-2 to B-2
                214,202,190,180,170,160,151,143,135,127,120,113, // C-3 to B-3
        },
#ifdef MOD_USE_FINETUNING
        {
        // Tuning 1
                850,802,757,715,674,637,601,567,535,505,477,450, // same as above
                425,401,379,357,337,318,300,284,268,253,239,225, // but with 
                213,201,189,179,169,159,150,142,134,126,119,113, // finetune +1
        },
        {
        // Tuning 2
                844,796,752,709,670,632,597,563,532,502,474,447, // etc, 
                422,398,376,355,335,316,298,282,266,251,237,224, // finetune +2
                211,199,188,177,167,158,149,141,133,125,118,112,
        },
        {
        // Tuning 3
                838,791,746,704,665,628,592,559,528,498,470,444,
                419,395,373,352,332,314,296,280,264,249,235,222,
                209,198,187,176,166,157,148,140,132,125,118,111,
        },
        {
        // Tuning 4
                832,785,741,699,660,623,588,555,524,495,467,441,
                416,392,370,350,330,312,294,278,262,247,233,220,
                208,196,185,175,165,156,147,139,131,124,117,110,
        },
        {
        // Tuning 5
                826,779,736,694,655,619,584,551,520,491,463,437,
                413,390,368,347,328,309,292,276,260,245,232,219,
                206,195,184,174,164,155,146,138,130,123,116,109,
        },
        {
        // Tuning 6
                820,774,730,689,651,614,580,547,516,487,460,434,
                410,387,365,345,325,307,290,274,258,244,230,217,
                205,193,183,172,163,154,145,137,129,122,115,109,
        },
        {
        // Tuning 7
                814,768,725,684,646,610,575,543,513,484,457,431,
                407,384,363,342,323,305,288,272,256,242,228,216,
                204,192,181,171,161,152,144,136,128,121,114,108,
        },
        {
        // Tuning -8
                907,856,808,762,720,678,640,604,570,538,508,480,
                453,428,404,381,360,339,320,302,285,269,254,240,
                226,214,202,190,180,170,160,151,143,135,127,120,
        },
        {
        // Tuning -7
                900,850,802,757,715,675,636,601,567,535,505,477,
                450,425,401,379,357,337,318,300,284,268,253,238,
                225,212,200,189,179,169,159,150,142,134,126,119,
        },
        {
        // Tuning -6
                894,844,796,752,709,670,632,597,563,532,502,474,
                447,422,398,376,355,335,316,298,282,266,251,237,
                223,211,199,188,177,167,158,149,141,133,125,118,
        },
        {
        // Tuning -5
                887,838,791,746,704,665,628,592,559,528,498,470,
                444,419,395,373,352,332,314,296,280,264,249,235,
                222,209,198,187,176,166,157,148,140,132,125,118,
        },
        {
        // Tuning -4
                881,832,785,741,699,660,623,588,555,524,494,467,
                441,416,392,370,350,330,312,294,278,262,247,233,
                220,208,196,185,175,165,156,147,139,131,123,117,
        },
        {
        // Tuning -3
                875,826,779,736,694,655,619,584,551,520,491,463,
                437,413,390,368,347,328,309,292,276,260,245,232,
                219,206,195,184,174,164,155,146,138,130,123,116,
        },
        {
        // Tuning -2
                868,820,774,730,689,651,614,580,547,516,487,460,
                434,410,387,365,345,325,307,290,274,258,244,230,
                217,205,193,183,172,163,154,145,137,129,122,115,
        },
        {
        // Tuning -1
                862,814,768,725,684,646,610,575,543,513,484,457,
                431,407,384,363,342,323,305,288,272,256,242,228,
                216,203,192,181,171,161,152,144,136,128,121,114,
        }
#endif
};

static const unsigned char sineTable[] =
{
           0, 24, 49, 74, 97,120,141,161,
         180,197,212,224,235,244,250,253,
         255,253,250,244,235,224,212,197,
         180,161,141,120, 97, 74, 49, 24
};

ModPlayer::ModPlayer(Mixer *_mixer):
        mixer(_mixer),
        channels(0),
        songSpeed(7),
        channel(0),
        note(0),
        order(0),
        volume(64),
        playing(false)
{
        int i;
        for(i=0; i<sizeof(sample)/sizeof(sample[0]); i++)
                sample[i] = 0;
        play();
}

ModPlayer::~ModPlayer()
{
        unload();
}

bool ModPlayer::load(const char *file)
{
#ifdef CODEWARRIOR
#pragma pack(1)
#endif
        typedef struct
        {
                unsigned char   name[22];
                unsigned short  length;
                signed char     fineTune;
                signed char     volume;
                unsigned short  loopStart;
                unsigned short  loopLength;
        } PACKED SampleHeader;
        
        typedef struct
        {
                unsigned char   byte0;
                unsigned char   byte1;
                unsigned char   byte2;
                unsigned char   byte3;
        } PACKED Note;
#ifdef CODEWARRIOR
#pragma pack(0)
#endif

#ifdef MOD_USE_TAGFILE
        if (!strcmp(file + strlen(file)-4, ".tag"))
            return loadTagFile(file);
#endif


        FILE *f = fopen(file,"rb");
        char modType[4];
        int i, j, k;
        
        if (!f)
                return false;

        // check that the compiler didn't mess things up
        CT_ASSERT(sizeof(Note)==4);
        CT_ASSERT(sizeof(SampleHeader)==30);
        
        unload();

        fseek(f,1080,SEEK_SET);
        fread(modType, sizeof(modType), 1, f);
        
        // read module type
        if (modType[0]=='M' && modType[1]=='.' && modType[2]=='K' && modType[3]=='.')
                channels = 4;
        else if (modType[0]=='6' && modType[1]=='C' && modType[2]=='H' && modType[3]=='N')
                channels = 6;
        else if (modType[0]=='8' && modType[1]=='C' && modType[2]=='H' && modType[3]=='N')
                channels = 8;
        else
                // no support for old 15 sample mods
                return false;
                
        assert(mixer->channelCount >= channels);
        channel = new ModChannel[channels];
                
        // read sample information (skip the module name)
        fseek(f,20,SEEK_SET);   
        for(i=0; i<31; i++)
        {
                SampleHeader header;
                fread(&header, sizeof(SampleHeader), 1, f);
                
#ifndef BIG_ENDIAN
                // fix endianess
                header.length = bigEndian16(header.length) * 2;
                header.loopStart = bigEndian16(header.loopStart) * 2;
                header.loopLength = bigEndian16(header.loopLength) * 2;
#endif
                
                if (header.loopLength <= 2)
                        header.loopLength = 0;
                
#ifdef MOD_USE_FINETUNING
                 if (header.fineTune > 7)
                        header.fineTune -= 16;
#else
                header.fineTune = 0;
#endif
                
                if (header.length > 1)
                {
                        sample[i] = new ModSample(header.length, header.fineTune, header.volume,
                                                  header.loopStart, header.loopLength);
                }
        }
        
        songLength = fgetc(f);
        
        fseek(f,1,SEEK_CUR); // skip unused byte
        
        // read pattern order and figure out pattern count
        order = new signed char[songLength];
        fread(order, songLength, 1, f);
        patternCount = 0;
        for(i=0; i<songLength; i++)
        {
                if (order[i] > patternCount-1)
                        patternCount = order[i]+1;
        }
        
        fseek(f,128 - songLength + 4,SEEK_CUR); // skip rest of order and module id
                
        note = new ModNote[channels * 64 /* rows per channel */ * patternCount];
        
        // read notes
        ModNote *n = note;
        for(i=0; i<patternCount; i++)
                for(j=0; j<channels*64; j++)
                {
                        Note d;
                        
                        fread(&d, sizeof(Note), 1, f);
                        
                        n->sampleNumber = (d.byte0 & 0xf0) + (d.byte2 >> 4);
                        n->effectNumber = d.byte2 & 0xf;
                        n->effectParameter = d.byte3;
                        n->amigaPeriod = ((d.byte0 & 0xf) << 8) + d.byte1;
                        
                        n->note = -1;
                        
                        if (n->amigaPeriod > 0)
                                for(k=0; k<37; k++)
                                        if (n->amigaPeriod > periodTable[0][k]-2 && n->amigaPeriod < periodTable[0][k]+2)
                                        {
                                                n->note = k;
                                        }
                        
                        n++;
                }
        
        // read sample data
        for(i=0; i<31; i++)
        {
                if (sample[i])
                {
                        fread(sample[i]->sample->data, sizeof(char), sample[i]->sample->bytes, f); 
                }
        }
        fclose(f);

        return true;
}

unsigned short ModPlayer::bigEndian16(unsigned short x)
{
        return (x>>8) + ((x&0xff)<<8);
}


#ifdef CODEWARRIOR
#pragma pack(1)
#endif
typedef struct
{
    signed char     songLength, songSpeed;
    signed char     channelCount, sampleCount, patternCount;
} PACKED PackedModHeader;

typedef struct
{
    signed char     fineTune, volume;
    unsigned short  length, loopStart, loopLength;
} PACKED PackedModSample;

typedef struct
{
    unsigned char   sampleNumber;
    unsigned short  amigaPeriod;
    signed short    note;
    unsigned char   effectNumber;
    unsigned char   effectParameter;
} PACKED PackedModNote;
#ifdef CODEWARRIOR
#pragma pack(0)
#endif


#ifdef MOD_USE_TAGFILE

#ifdef MOD_USE_TAGFILE_SAVING
bool ModPlayer::save(const char *fileName) const
{
    PackedModHeader header;
    PackedModSample sampleHeader;
    PackedModNote *packedNote;
    int i;

    WriteTagFile file(fileName);

    header.sampleCount = 0;
    header.songLength = songLength;
    header.songSpeed = songSpeed;
    header.channelCount = channels;
    header.patternCount = patternCount;

    for(i=0; i<sizeof(sample)/sizeof(sample[0]); i++)
        if (sample[i])
            header.sampleCount++;
        else
            break;

    file.writeTag(0, (unsigned char*)&header, sizeof(header));
    file.writeTag(1, (unsigned char*)order, songLength);

    packedNote = new PackedModNote[channels * 64 /* rows per channel */ * patternCount];

    for(i=0; i<channels * 64 /* rows per channel */ * patternCount; i++)
    {
        packedNote[i].sampleNumber = note[i].sampleNumber;
        packedNote[i].amigaPeriod = note[i].amigaPeriod;
        packedNote[i].note = note[i].note;
        packedNote[i].effectNumber = note[i].effectNumber;
        packedNote[i].effectParameter = note[i].effectParameter;
    }

    file.writeTag(2, (unsigned char*)packedNote, channels * 64 /* rows per channel */ * patternCount * sizeof(PackedModNote));

    delete[] packedNote;

    for(i=0; i<sizeof(sample)/sizeof(sample[0]); i++)
    {
        if (!sample[i])
            continue;

        sampleHeader.fineTune = sample[i]->fineTune;
        sampleHeader.volume = sample[i]->volume;
        sampleHeader.length = sample[i]->sample->length;
        sampleHeader.loopStart = sample[i]->loopStart;
        sampleHeader.loopLength = sample[i]->loopLength;
        file.writeTag(3, (unsigned char*)&sampleHeader, sizeof(sampleHeader));
        file.writeTag(4, (unsigned char*)sample[i]->sample->data, sample[i]->sample->bytes);
    }

    return true;
}
#endif // MOD_USE_TAGFILE_SAVING

bool ModPlayer::loadTagFile(const char *fileName)
{
    int id, i, loadedSampleCount = 0;
    TagFile file(fileName);
    PackedModHeader header;
    PackedModSample sampleHeader;
    PackedModNote *packedNote;

    unload();

    while(1)
        switch(id = file.readTag())
        {
        case 0:
            file.readData((unsigned char*)&header, sizeof(header));

            // sampleCount = header.sampleCount;
            songLength = header.songLength ;
            songSpeed = header.songSpeed;
            channels = header.channelCount;
            patternCount = header.patternCount;

            channel = new ModChannel[channels];
            order = new signed char[songLength];
            note = new ModNote[channels * 64 /* rows per channel */ * patternCount];

            if (!channel || !order || !note)
                return false;
            break;
        case 1:
            file.readData((unsigned char*)order, songLength);
            break;
        case 2:
            packedNote = new PackedModNote[channels * 64 /* rows per channel */ * patternCount];

            if (!packedNote)
                return false;

            file.readData((unsigned char*)packedNote, channels * 64 /* rows per channel */ * patternCount * sizeof(PackedModNote));

            for(i=0; i<channels * 64 /* rows per channel */ * patternCount; i++)
            {
                note[i].sampleNumber = packedNote[i].sampleNumber;
                note[i].amigaPeriod = packedNote[i].amigaPeriod;
                note[i].note = packedNote[i].note;
                note[i].effectNumber = packedNote[i].effectNumber;
                note[i].effectParameter = packedNote[i].effectParameter;
            }
            delete[] packedNote;
            break;
        case 3:
            file.readData((unsigned char*)&sampleHeader, sizeof(sampleHeader));
            sample[loadedSampleCount] =
                new ModSample(sampleHeader.length, sampleHeader.fineTune, sampleHeader.volume,
                              sampleHeader.loopStart, sampleHeader.loopLength);
            break;
        case 4:
            if (sample[loadedSampleCount])
            {
                file.readData(
                    (unsigned char*)sample[loadedSampleCount]->sample->data,
                    sample[loadedSampleCount]->sample->bytes); 
                loadedSampleCount++;
            }
            break;
        default:
            return channels > 0;
            break;
        }
}
#endif // MOD_USE_TAGFILE

ModPlayer::ModSample::ModSample(int _length, char _fineTune, char _volume, unsigned short _loopStart, unsigned short _loopLength):
        fineTune(_fineTune),
        volume(_volume),
        loopStart(_loopStart),
        loopLength(_loopLength)
{
        SampleFormat sf(8,1);
        sample = new SampleChunk(&sf, _length, MOD_FREQ_BASE / (428*2));
}

ModPlayer::ModSample::~ModSample()
{
        delete sample;
}

void ModPlayer::unload()
{
        int i;

        stop();

        for(i=0; i<sizeof(sample)/sizeof(sample[0]); i++)
        {
                delete sample[i];
                sample[i] = 0;
        }
        delete[] note;
        delete[] channel;
        delete[] order;
        channels = 0;
		note = 0;
		channel = 0;
		order = 0;
}

void ModPlayer::play()
{
        if (playing)
            return;

        currentOrder = 0;
        currentTick = 0;
        currentRow = 0;
        patternDelay = 0;

        playing = true;
        
        if (sample && note && channel && order && songLength)
                mixer->installTicker(this, 2 * 125 / 5);
}

void ModPlayer::tick()
{
        // cache values so effects won't mess them up
        int ch;
        int cr = currentRow;
        int co = currentOrder;

        //printf("%d/%d %2d:%02d\n", currentTick, songSpeed, order[currentOrder], currentRow);

        if (!playing)
            return;
        
        for(ch=0; ch<channels; ch++)
//      ch=0;
        {
                ModNote *n = &note[order[co]*(channels<<6) + cr*channels + ch];
                
                if (currentTick == 0)
                {
                        if (!patternDelay)
                        {
                                playNote(ch, n);
                        }
                }
                else
                {
                        unsigned char x = n->effectParameter >> 4;
                        unsigned char y = n->effectParameter & 0xf;
                        
//                      printf("effect: %x%x%x\n", n->effectNumber, x, y);
                        
                        switch(n->effectNumber)
                        {
                        case 0x0: // arpeggio
                                switch(currentTick % 3)
                                {
                                case 0:
                                        if (channel[ch].amigaPeriod)
                                                mixer->getChannel(ch)->setFrequency(amigaToHz(channel[ch].amigaPeriod));
                                break;
                                case 1:
                                        mixer->getChannel(ch)->setFrequency(amigaToHz(periodTable[0][channel[ch].note+x]));
                                break;
                                case 2:
                                        mixer->getChannel(ch)->setFrequency(amigaToHz(periodTable[0][channel[ch].note+y]));
                                break;
                                }
                        break;
                        case 0x1: // porta up
                                channel[ch].amigaPeriod -= n->effectParameter;
                                if (channel[ch].amigaPeriod < 113)
                                        channel[ch].amigaPeriod = 113;
                                mixer->getChannel(ch)->setFrequency(amigaToHz(channel[ch].amigaPeriod));
                        break;
                        case 0x2: // porta down
                                if (channel[ch].amigaPeriod > 856)
                                        channel[ch].amigaPeriod = 856;
                                channel[ch].amigaPeriod += n->effectParameter;
                                mixer->getChannel(ch)->setFrequency(amigaToHz(channel[ch].amigaPeriod));
                        break;
                        case 0x5: // porta to note + volume slide
                        case 0x3: // porta to note
                                if (channel[ch].amigaPeriod < channel[ch].portaTarget)
                                        channel[ch].amigaPeriod += channel[ch].portaSpeed;
                                else if (channel[ch].amigaPeriod > channel[ch].portaTarget)
                                        channel[ch].amigaPeriod -= channel[ch].portaSpeed;
                                mixer->getChannel(ch)->setFrequency(amigaToHz(channel[ch].amigaPeriod));
                                
                                if (n->effectNumber == 0x5)
                                        goto do_volume_slide;
                        break;
                        case 0x6: // vibrato + volume slide
                        case 0x4: // vibrato
                        {
                                int vibrato = channel[ch].vibratoDepth * sineTable[channel[ch].vibratoPos] >> 7;
                                
                                switch(channel[ch].vibratoNeg)
                                {
                                case 0:
                                        mixer->getChannel(ch)->setFrequency(amigaToHz(channel[ch].amigaPeriod) + vibrato);
                                break;
                                case 1:
                                        mixer->getChannel(ch)->setFrequency(amigaToHz(channel[ch].amigaPeriod) - vibrato);
                                break;
                                };
                                
                                channel[ch].vibratoPos += channel[ch].vibratoSpeed;
                                
                                if (channel[ch].vibratoPos > 31)
                                {
                                        channel[ch].vibratoPos -= 32;
                                        channel[ch].vibratoNeg = !channel[ch].vibratoNeg;
                                }
                                if (n->effectNumber == 0x6)
                                        goto do_volume_slide;
                        }
                        break;
                        case 0x7: // tremolo
                        {
                                int tremolo = channel[ch].tremoloDepth * sineTable[channel[ch].tremoloPos] >> 6;
                                int vol;
                                
                                switch(channel[ch].tremoloNeg)
                                {
                                case 0:
                                        vol = channel[ch].volume + tremolo;
                                        mixer->getChannel(ch)->setVolume(calcVolume((vol>64)?64:vol));
                                break;
                                case 1:
                                        vol = channel[ch].volume - tremolo;
                                        mixer->getChannel(ch)->setVolume(calcVolume((vol<0)?0:vol));
                                break;
                                };
                                
                                channel[ch].tremoloPos += channel[ch].tremoloSpeed;
                                
                                if (channel[ch].tremoloPos > 31)
                                {
                                        channel[ch].tremoloPos -= 32;
                                        channel[ch].tremoloNeg = !channel[ch].tremoloNeg;
                                }
                        }
                        break;
                        case 0xa: // volume slide
do_volume_slide:
                                if (x > 0)
                                {
                                        channel[ch].volume += x;
                                        if (channel[ch].volume > 64)
                                                channel[ch].volume = 64;
                                        mixer->getChannel(ch)->setVolume(calcVolume(channel[ch].volume));
                                }
                                else if (y > 0)
                                {
                                        channel[ch].volume -= y;
                                        if (channel[ch].volume < 0)
                                                channel[ch].volume = 0;
                                        mixer->getChannel(ch)->setVolume(calcVolume(channel[ch].volume));
                                }
                        break;
                        case 0xe:
                        {
                                unsigned char x = n->effectParameter & 0xf;
                                
                                switch(n->effectParameter >> 4)
                                {
                                case 0x9: // retrigger note
                                        if (x && (currentTick % x) == 0)
                                        {
                                                playNote(ch, n);
                                        }
                                break;
                                case 0xc: // cut note
                                        if (currentTick == x)
                                        {
                                                mixer->getChannel(ch)->setVolume(0);
                                        }
                                break;
                                case 0xd: // delay note
                                        if (currentTick == x)
                                        {
                                                playNote(ch, n);
                                        }
                                break;
                                }
                        }
                        break;
                        }
                }
        }
        
        if (++currentTick == songSpeed)
        {
                currentTick = 0;
                
                if (patternDelay > 0)
                        patternDelay--;
                else
                {
                        currentRow++;
                
                        if (currentRow >= 64)
                        {
                                currentRow = 0;
                                currentOrder++;
                                if (currentOrder >= songLength)
                                        currentOrder = 0;
                        }
                }
        }
}

int ModPlayer::amigaToHz(int period)
{
        if (period)
                return MOD_FREQ_BASE / (period*2);
        else
                return 0;
}

void ModPlayer::playNote(int ch, ModNote *n)
{
        if (n->sampleNumber)
        {
                ModSample *s = sample[n->sampleNumber-1];
                
                if (s)
                {
                        channel[ch].sample = s;
                        channel[ch].volume = s->volume;
                        mixer->getChannel(ch)->setSample(s->sample);
                        mixer->getChannel(ch)->setVolume(calcVolume(s->volume));
//                      printf("%d\n", s->volume);
                }
        }
        
        if (n->note != -1)
        {
                // don't play note on porta to note, combined porta and volume slide or note delay
                if (n->effectNumber != 0x3 && n->effectNumber != 0x5 && (n->effectNumber>>4) != 0xed)
                {
                        int freq = amigaToHz(periodTable[channel[ch].sample->fineTune][n->note]);
                        
//                      printf("Channel %d: Playnote %3d, %6d Hz: len %d, loop start %d, len %d\n", ch, n->note, freq, channel[ch].sample->sample->length, channel[ch].sample->loopStart, channel[ch].sample->loopLength);
                        
                        channel[ch].amigaPeriod = n->amigaPeriod;
                        channel[ch].note = n->note;
                        mixer->getChannel(ch)->start(channel[ch].sample->sample, freq, channel[ch].sample->loopStart, channel[ch].sample->loopLength);
                        
                        // reset vibrato
                        channel[ch].vibratoNeg = 0;
                        channel[ch].vibratoPos = 0;
                
                        // reset tremolo
                        channel[ch].tremoloNeg = 0;
                        channel[ch].tremoloPos = 0;
                }
        }
        
        // process tick 0 effects
        switch(n->effectNumber)
        {
        case 0x3: // porta to note
                channel[ch].portaSpeed = n->effectParameter;
                if (n->amigaPeriod)
                        channel[ch].portaTarget = n->amigaPeriod;
        break;
        case 0x4: // vibrato
                if (n->effectParameter)
                {
                        channel[ch].vibratoSpeed = n->effectParameter >> 4;
                        channel[ch].vibratoDepth = n->effectParameter & 0xf;
                }
        case 0x7: // tremolo
                if (n->effectParameter)
                {
                        channel[ch].tremoloSpeed = n->effectParameter >> 4;
                        channel[ch].tremoloDepth = n->effectParameter & 0xf;
                }
        break;
        case 0x9: // sample offset
                mixer->getChannel(ch)->setPosition(n->effectParameter << 8);
        break;
        case 0xb: // jump to pattern
                currentOrder = (n->effectParameter>songLength-1)?(songLength-1):n->effectParameter;
        break;
        case 0xc: // set volume
                mixer->getChannel(ch)->setVolume(calcVolume(n->effectParameter));
        break;
        case 0xd: // pattern break
                currentRow = n->effectParameter;
                currentOrder++;
                if (currentRow > 63) currentRow = 0;
                if (currentOrder > songLength-1) currentOrder = 0;
        break;
        case 0xf: // set speed
                if (n->effectParameter < 0x1f)
                        songSpeed = n->effectParameter;
                else
                        mixer->installTicker(this, 7 * n->effectParameter / 16);
        break;
        case 0xe:
        {
                unsigned char x = n->effectParameter & 0xf;
                switch(n->effectParameter >> 4)
                {
                case 0x1: // fine porta up
                        channel[ch].amigaPeriod -= x;
                        mixer->getChannel(ch)->setFrequency(amigaToHz(channel[ch].amigaPeriod));
                break;
                case 0x2: // fine porta down
                        channel[ch].amigaPeriod += x;
                        mixer->getChannel(ch)->setFrequency(amigaToHz(channel[ch].amigaPeriod));
                break;
                case 0x3: // glissando control
                        channel[ch].glissando = x?true:false;
                break;
/*              
                case 0x4: // set vibrato waveform
                        if (x < 4)
                                channel[ch].vibratoWaveform = x;
                        else
                                channel[ch].vibratoWaveformRetrig = (1<<x);
                break;
*/              
                case 0x5: // set finetune
                        channel[ch].sample->fineTune = x;
                break;
                case 0x6: // loop
                        if (x == 0)
                                channel[ch].loopRow = currentRow;
                        else
                        {
                                if (!channel[ch].loopCounter)
                                        channel[ch].loopCounter = x;
                                else
                                        channel[ch].loopCounter--;
                                        
                                if (channel[ch].loopCounter)
                                        currentRow = channel[ch].loopRow-1;
                        }
                break;
/*              
                case 0x7: // set tremolo waveform
                        if (x < 4)
                                channel[ch].tremoloWaveform = x;
                        else
                                channel[ch].tremoloWaveformRetrig = (1<<x);
                break;
*/              
/*
                case 0x8: // panning
                break;
*/              
                case 0xa: // fine volumeslide up
                        channel[ch].volume += x;
                        if (channel[ch].volume > 64)
                                channel[ch].volume = 64;
                        mixer->getChannel(ch)->setVolume(calcVolume(channel[ch].volume));
                break;
                case 0xb: // fine volumeslide down
                        channel[ch].volume -= x;
                        if (channel[ch].volume < 0)
                                channel[ch].volume = 0;
                        mixer->getChannel(ch)->setVolume(calcVolume(channel[ch].volume));
                break;
                case 0xe: // pattern delay
                        patternDelay = x;
                break;
                }
        }
        break;
        }
}

ModPlayer::ModChannel::ModChannel():
        sample(0),
        note(0),
        glissando(false),
        portaSpeed(0),
//      vibratoWaveform(0),
//      vibratoWaveformRetrig(0),
        vibratoPos(0),
        vibratoSpeed(0),
        vibratoNeg(0),
//      tremoloWaveform(0),
//      tremoloWaveformRetrig(0),
        tremoloPos(0),
        tremoloSpeed(0),
        tremoloNeg(0),
        volume(64),
        arpeggioCounter(0),
        loopRow(0),
        loopCounter(0),
        amigaPeriod(0)
{
}

void ModPlayer::stop()
{
        int i;

        mixer->installTicker(NULL, 0);

        playing = false;

        for(i=0; i<channels; i++)
        {
                if (mixer->getChannel(i))
                   mixer->getChannel(i)->stop();
        }
}

void ModPlayer::setVolume(int vol)
{
    if (vol < 0) vol = 0;
    if (vol > 64) vol = 64;
    volume = (signed char)vol;
}

int ModPlayer::calcVolume(int v)
{
    return (v * volume) >> 6;
}

