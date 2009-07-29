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

void flipScreen();
MXSurface* loadImage(FILE* packFile);

/*
 * Configuration
 */
#define PACKFILE        "images.dat"
#define SONGFILE        "macmod.mod"
#define SCREEN_WIDTH    512
#define SCREEN_HEIGHT   342

/*
 * Global state
 */
static MXSurface* screen = 0;
static Audio*     audio = 0;
static Video*     video = 0;
static MXSurface* physicalScreen = 0;
static Mixer      mixer(22050, 4);
//static ModPlayer  player(&mixer);

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
    audio = new Audio(8, 22050, 0, 2048);
    
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

#ifdef BIG_ENDIAN
uint32_t swapEndian(uint32_t x)
{
	return (x >> 24) |
	       ((x << 8) & 0x00ff0000) |
	       ((x >> 8) & 0x0000ff00) |
	       (x << 24);
}
#endif

MXSurface* loadImage(FILE* packFile)
{
    MXSurface header;
    MXSurface* surf;
    assert(fread(&header, sizeof(header) - sizeof(void*), 1, packFile) == 1);
    
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
            timeline.reset();
            startTime = time;
        }

        drawDebugText(screen, 512 - 8 * 8, 0, status);
        flipScreen();

        if (!video->processInput())
        {
            break;
        }
        if (++frames == 60)
        {
            int fps = 1000 * ((frames << 16) / ((time - frameStartTime)));
            frameStartTime = time;
            frames = 0;
            sprintf(status, "%d fps", fps >> 16);
        }
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
