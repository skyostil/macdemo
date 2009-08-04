/**
 *  Mac Demo
 *  Copyright (C) 2009 by Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 */
#include "Config.h"
#include "Demo.h"
#include "Font.h"
#include "Video.h"
#include "Audio.h"
#include "Mixer.h"
#include "ModPlayer.h"
#include "monoxide.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

#if defined(_MSC_VER)
#   include <sdl_main.h>
#endif

void flipScreen();
uint32_t swapEndian(uint32_t n);
MXSurface* loadImage(FILE* packFile);

/*
 * Configuration
 */
#define PACKFILE        "images.dat"
#define SONGFILE        "macmod.mod"
#define SONG_SPEED      6
#define SCREEN_WIDTH    512
#define SCREEN_HEIGHT   342
#define MUSIC_LENGTH    (2 * 60 + 15)
//#define MUSIC_STATS
//#define DEMO_STATS
//#define DEMO_LOOP
#define RAWMUSICFILE    "music.raw"

int sawtooth(int t)
{
    t &= 0xff;
    if (t > 0x7f)
    {
        t = 0x7f + (0x7f - t);
    }
    return t;
}

inline int min(int a, int b)
{
    return (a < b) ? a : b;
}

inline int max(int a, int b)
{
    return (a > b) ? a : b;
}

inline int absi(int v)
{
    const int mask = v >> sizeof(int) * 8 - 1;
    return (v + mask) ^ mask;
}

inline int pow2(int i)
{
    return i * i;
}

class MusicRenderer: public AudioRenderer
{
public:
    MusicRenderer(int _mixFreq)
    {
        mixFreq = _mixFreq;
        readBytes = playBytes = 0;

        SampleFormat format(8, 1);
        audioBuffer = new SampleChunk(&format, 0x80000, mixFreq);
        assert(audioBuffer);
        assert(audioBuffer->data);
    
        audioFile = fopen(RAWMUSICFILE, "rb");
        assert(audioFile);
        
        preload(audioBuffer->bytes >> 1);
    }

    ~MusicRenderer()
    {
        delete audioBuffer;
        fclose(audioFile);
		unlink(RAWMUSICFILE);
    }
    
    void preload(int bytesToLoad = 0x10000)
    {
        while (bytesToLoad > 0)
        {
            int readPos = readBytes & (audioBuffer->bytes - 1);
            int readSize = min(bytesToLoad, audioBuffer->bytes - readPos);
#ifdef MUSIC_STATS
            printf("LOAD %d bytes at %d (%d total)\n", readSize, readPos, readBytes);
#endif
            int n = fread(audioBuffer->data + readPos, 1, readSize, audioFile);
            if (n <= 0)
            {
                break;
            }
            bytesToLoad -= n;
            readBytes += n;
        }
    }

    void render(SampleChunk* buffer)
    {
        int bytesToPlay = buffer->bytes;
        while (playBytes + buffer->bytes > readBytes && !feof(audioFile))
        {
#ifdef MUSIC_STATS
            printf("UNDERRUN (%d read, %d played)\n", readBytes, playBytes);
#endif
            //preload();
            return;
        }
        while (bytesToPlay > 0)
        {
            int playPos = playBytes & (audioBuffer->bytes - 1);
            int playSize = min(bytesToPlay, audioBuffer->bytes - playPos);
#ifdef MUSIC_STATS
            printf("PLAY %d bytes (%d total, %d read)\n", playSize, playBytes, readBytes);
#endif
            memcpy(buffer->data, audioBuffer->data + playPos, playSize);
            bytesToPlay -= playSize;
            playBytes += playSize;
        }
    }

private:
    FILE* audioFile;
    SampleChunk* audioBuffer;
    int readBytes, playBytes, mixFreq;
};

/*
 * Global state
 */
static MXSurface*     screen = 0;
static Audio*         audio = 0;
static Video*         video = 0;
static MXSurface*     physicalScreen = 0;
static MusicRenderer* musicRenderer = 0;

#include "Effects.h"

void setup()
{
    video = new Video(SCREEN_WIDTH, SCREEN_HEIGHT);
    physicalScreen = mxCreateUserMemorySurface(video->screenWidth(), video->screenHeight(), 
                                               MX_PIXELFORMAT_I1, video->screenStride(), 
                                               0, video->screenPixels());
    screen = mxCreateSurface(video->screenWidth(), video->screenHeight(), MX_PIXELFORMAT_I1, 0);
    //Audio(8, 11127, 0, 512);
    //Audio(8, 22050, 0, 512);
#if defined(CODEWARRIOR)
    audio = new Audio(8, 11127, false, 0x1000);
#else
    audio = new Audio(8, 11127, false, 512);
#endif
    
    //assert(player.load(SONGFILE));
    
    //player.play();
    //audio->start(&mixer);

    setupEffects();
}

void teardown()
{
    teardownEffects();

    delete audio;
    mxDestroySurface(screen);
    mxDestroySurface(physicalScreen);
    delete video;
}

void flipScreen()
{
    video->waitRefresh();
    mxBlit(physicalScreen, screen, NULL, 0, 0, NULL, 0);
    video->swapBuffers();
}

uint32_t swapEndian(uint32_t x)
{
    return (x >> 24) |
           ((x << 8) & 0x00ff0000) |
           ((x >> 8) & 0x0000ff00) |
           (x << 24);
}

MXSurface* loadImage(FILE* packFile)
{
    MXSurface header;
    MXSurface* surf;
    assert(fread(&header, sizeof(int) * 7, 1, packFile) == 1);
    
#ifdef BIG_ENDIAN
    header.w = swapEndian(header.w);
    header.h = swapEndian(header.h);
    header.pixelFormat = (MXPixelFormat)swapEndian(header.pixelFormat);
    header.flags = swapEndian(header.flags);
    header.planeSize = swapEndian(header.planeSize);
#endif
    
    surf = mxCreateSurface(header.w, header.h, header.pixelFormat, header.flags);

    if (!surf)
    {
        return surf;
    }

    assert(fread(surf->pixels, header.planeSize, 1, packFile) == 1);
    mxFlushSurface(surf);

    return surf;
}

void demo()
{
    int time, startTime;
    int frameStartTime, frames = 0;
    char status[64];
    Timeline timeline(effects);

    status[0] = 0;
    frameStartTime = startTime = video->ticks();

    while (1)
    {
        time = video->ticks();
        if (!timeline.run(time - startTime))
        {
#if DEMO_LOOP
            timeline.reset();
            startTime = time;
#else
            break;
#endif
        }
#ifdef DEMO_STATS
        drawDebugText(screen, 512 - 20 * 8, 0, status);
#endif
        flipScreen();

        if (!video->processInput())
        {
            break;
        }
#ifdef DEMO_STATS
        if (++frames == 60 && time > frameStartTime)
        {
            int fps = 1000 * ((frames << 16) / ((time - frameStartTime)));
            frameStartTime = time;
            frames = 0;
            sprintf(status, "%d fps, %d ms", fps >> 16, time);
        }
#endif
    }
}

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    setup();
    demo();
    teardown();

    return 0;
}
