/**
 *  Mac Demo
 *  Copyright (C) 2009 by Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 */
#include "Config.h"
#include "Demo.h"
#include "Font.h"
#include "engine/Video.h"
#include "engine/Audio.h"
#include "monoxide.h"
#include <stdio.h>
#include <assert.h>

void flipScreen();

/*
 * Configuration
 */
#define PACKFILE        "data/images.dat"
#define SCREEN_WIDTH    512
#define SCREEN_HEIGHT   342

/*
 * Global state
 */
static MXSurface* screen = 0;
static Audio*     audio = 0;
static Video*     video = 0;
static MXSurface* physicalScreen = 0;

static MXSurface* loadImage(FILE* packFile)
{
    MXSurface header;
    MXSurface* surf;
    assert(fread(&header, sizeof(header) - sizeof(void*), 1, packFile) == 1);
    surf = mxCreateSurface(header.w, header.h, header.pixelFormat, header.flags);

    if (!surf)
    {
        return surf;
    }

    assert(fread(surf->pixels, header.planeSize, 1, packFile) == 1);
    mxFlushSurface(surf);

    return surf;
}

#include "Effects.inl"

void setup()
{
    video = new Video(SCREEN_WIDTH, SCREEN_HEIGHT);
    physicalScreen = mxCreateUserMemorySurface(video->screenWidth(), video->screenHeight(), 
                                               MX_PIXELFORMAT_I1, video->screenStride(), 
                                               0, video->screenPixels());
    screen = mxCreateSurface(video->screenWidth(), video->screenHeight(), MX_PIXELFORMAT_I1, 0);
    //Audio(8, 11127, 0, 512);
    //Audio(8, 22050, 0, 512);
    audio = new Audio(8, 22050, 0, 512);
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

void demoTest()
{
    int time;
    Timeline timeline(effects);

    for (time = 0; ; time += 0x100)
    {
        //printf("%d\n", time);
        if (!timeline.run(time))
        {
            timeline.reset();
            time = 0;
        }
        if (!video->processInput())
        {
            break;
        }
    }
}

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    setup();
    demoTest();
    teardown();

    return 0;
}
