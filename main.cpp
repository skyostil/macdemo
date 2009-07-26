/**
 *  Mac Demo
 *  Copyright (C) 2009 by Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 */
#include "demo.h"
#include "monoxide.h"
#include "Config.h"
#include "engine/Video.h"
#include "engine/Audio.h"
#include <stdio.h>

#if defined(USE_SDL)
#    include "monoxide_sdl.h"
#endif

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
#if !defined(USE_SDL)
static MXSurface* physicalScreen = 0;
#endif

void effect1(int time, int duration)
{
    mxFill(screen, NULL, 0);
    flipScreen();
}

void effect2(int time, int duration)
{
    mxFillCirclePattern(screen, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2);
    flipScreen();
}

void effect3(int time, int duration)
{
    mxFillSierpinskiPattern(screen);
    flipScreen();
}

void effect4(int time, int duration)
{
    mxFillCheckerPattern(screen, 4, 4);
    flipScreen();
}

const Effect timeline[] =
{
    {effect1, 0x10000},
    {effect2, 0x10000},
    {effect3, 0x10000},
    {effect4, 0x10000},
    {NULL, 0}
};

void setup()
{
#if defined(USE_SDL)
    screen = mxCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
#else
    video = new Video(SCREEN_WIDTH, SCREEN_HEIGHT);
    physicalScreen = mxCreateUserMemorySurface(video->screenWidth(), video->screenHeight(), 
                                               MX_PIXELFORMAT_I1, video->screenStride(), 
                                               0, video->getScreen());
    screen = mxCreateSurface(video->screenWidth(), video->screenHeight(), MX_PIXELFORMAT_I1, 0);
#endif
    //Audio(8, 11127, 0, 512);
    //Audio(8, 22050, 0, 512);
    audio = new Audio(8, 22050, 0, 512);
}

void teardown()
{
    delete audio;
#if defined(USE_SDL)
    mxDestroyWindow(screen);
#else
    mxDestroySurface(screen);
    mxDestroySurface(physicalScreen);
    delete video;
#endif
}

void flipScreen()
{
#if defined(USE_SDL)
    mxSwapBuffers(screen);
#else
    mxBlit(physicalScreen, screen, NULL, 0, 0, NULL, 0);
#endif
}

void demoTest()
{
    int time;

    for (time = 0; ; time += 0x100)
    {
        //printf("%d\n", time);
        if (!schedule(timeline, time))
        {
            time = 0;
        }
#if defined(USE_SDL)
        if (!mxProcessEvents())
        {
            break;
        }
#endif
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
