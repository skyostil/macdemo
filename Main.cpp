/**
 *  Mac Demo
 *  Copyright (C) 2009 by Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 */
#include "Config.h"
#include "Demo.h"
#include "engine/Video.h"
#include "engine/Audio.h"
#include "monoxide.h"
#include <stdio.h>

void flipScreen();

/*
 * Configuration
 */
#define SCREEN_WIDTH    512
#define SCREEN_HEIGHT   342

/*
 * Global state
 */
static MXSurface* screen = 0;
static Audio*     audio = 0;
static Video*     video = 0;
static MXSurface* physicalScreen = 0;

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
