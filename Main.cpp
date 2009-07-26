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
static int x = 93, y = 17;
static int dx = 1, dy = 1;
static MXSurface* checkers = 0;
static MXSurface* ball = 0;

void moveBall()
{
    x += dx;
    y += dy;

    if (x < 0)
    {
        x = -x;
        dx = -dx;
    }

    if (x + ball->w > screen->w)
    {
        x += 2 * (screen->w - (x + ball->w));
        dx = -dx;
    }

    if (y < 0)
    {
        y = -y;
        dy = -dy;
    }

    if (y + ball->h > screen->h)
    {
        y += 2 * (screen->h - (y + ball->h));
        dy = -dy;
    }
}

void effect1(int time, int duration)
{
    mxFill(screen, NULL, 0);
    mxBlit(screen, checkers, ball, x, y, NULL, 0);
    moveBall();
    flipScreen();
}

void effect2(int time, int duration)
{
    mxFillCirclePattern(screen, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2);
    mxBlit(screen, checkers, ball, x, y, NULL, 0);
    moveBall();
    flipScreen();
}

void effect3(int time, int duration)
{
    mxFillSierpinskiPattern(screen);
    mxBlit(screen, checkers, ball, x, y, NULL, 0);
    moveBall();
    flipScreen();
}

void effect4(int time, int duration)
{
    mxFillCheckerPattern(screen, 4, 4);
    mxBlit(screen, checkers, ball, x, y, NULL, 0);
    moveBall();
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
    video = new Video(SCREEN_WIDTH, SCREEN_HEIGHT);
    physicalScreen = mxCreateUserMemorySurface(video->screenWidth(), video->screenHeight(), 
                                               MX_PIXELFORMAT_I1, video->screenStride(), 
                                               0, video->screenPixels());
    screen = mxCreateSurface(video->screenWidth(), video->screenHeight(), MX_PIXELFORMAT_I1, 0);
    //Audio(8, 11127, 0, 512);
    //Audio(8, 22050, 0, 512);
    audio = new Audio(8, 22050, 0, 512);

    /* Demo data */
    checkers = mxCreateSurface(256, 256, MX_PIXELFORMAT_I1, MX_SURFACE_FLAG_PRESHIFT);
    ball = mxCreateSurface(256, 256, MX_PIXELFORMAT_I1, MX_SURFACE_FLAG_PRESHIFT);

    mxFillCheckerPattern(checkers, 4, 4);
    mxFlushSurface(checkers);

    mxFillCirclePattern(ball, 128, 128, 100);
    mxFlushSurface(ball);
}

void teardown()
{
    mxDestroySurface(ball);
    mxDestroySurface(checkers);

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

    for (time = 0; ; time += 0x100)
    {
        //printf("%d\n", time);
        if (!schedule(timeline, time))
        {
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
