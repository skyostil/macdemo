/**
 *  Copyright (C) 2009 by Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 */

#include "Video.h"
#include "../monoxide/monoxide.h"
#include <SDL.h>
#include <assert.h>
#include <stdio.h>

static SDL_Surface* win = 0;
static MXSurface* backbuffer = 0;
static bool timeSkip = false;
static bool paused = false;
static int timeSkipOffset = 0;
static int pauseTime = 0;

//#define DEMO_DEBUG

Video::Video(int w, int h, bool fullscreen)
{
    int flags = 0;

    if (fullscreen)
    {
        flags |= SDL_FULLSCREEN;
    }

    win = SDL_SetVideoMode(w, h, 32, flags);

    if (!win)
    {
        win = SDL_SetVideoMode(w, h, 16, flags);
        assert(win);
    }
    backbuffer = mxCreateSurface(win->w, win->h, MX_PIXELFORMAT_I1, 0);
    SDL_WM_SetCaption("Three and a half inches is enough", NULL);
    SDL_ShowCursor(0);

    printf("Video: %dx%d, 1 bpp\n", w, h);
}

Video::~Video()
{
    if (backbuffer)
    {
        mxDestroySurface(backbuffer);
        backbuffer = 0;
    }
    if (win)
    {
        SDL_FreeSurface(win);
        win = 0;
    }
}

void Video::waitRefresh()
{
}

int Video::refreshCount()
{
    return 0;
}

int Video::screenWidth()
{
    return win->w;
}

int Video::screenHeight()
{
    return win->h;
}

int Video::screenStride()
{
    return win->w / 8;
}

void* Video::screenPixels()
{
    return backbuffer->pixels;
}

static void _swap16()
{
    int x, y;
    const uint16_t palette[] = {
        0xffff,
        0x0000,
    };
    const MXSurface* s = backbuffer;
    const uint8_t* src = (uint8_t*)s->pixels;
    
    assert(win);
    assert(s->pixelFormat == MX_PIXELFORMAT_I1);

    SDL_LockSurface(win);
    uint16_t* dest = (uint16_t*)win->pixels;

    for (y = 0; y < s->h; y++)
    {
        for (x = 0; x < s->w; x++)
        {
            int color = (src[x / 8] & (1 << (7 - (x & 0x7)))) ? 1 : 0;
            dest[x] = palette[color];
        }
        dest += win->pitch / 2;
        src += s->stride;
    }

    SDL_UnlockSurface(win);
    SDL_Flip(win);
}

static void _swap32()
{
    int x, y;
    const uint32_t palette[] = {
        0xffffffff,
        0x00000000,
    };
    const MXSurface* s = backbuffer;
    const uint8_t* src = (uint8_t*)s->pixels;
    
    assert(win);
    assert(s->pixelFormat == MX_PIXELFORMAT_I1);

    SDL_LockSurface(win);
    uint32_t* dest = (uint32_t*)win->pixels;

    for (y = 0; y < s->h; y++)
    {
        for (x = 0; x < s->w; x++)
        {
            int color = (src[x / 8] & (1 << (7 - (x & 0x7)))) ? 1 : 0;
            dest[x] = palette[color];
        }
        dest += win->pitch / 4;
        src += s->stride;
    }

    SDL_UnlockSurface(win);
    SDL_Flip(win);
}

void Video::swapBuffers()
{
    assert(win);
    switch (win->format->BitsPerPixel)
    {
    case 16:
        _swap16();
        break;
    case 32:
        _swap32();
        break;
    }
}

bool Video::processInput(void)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    return false;
                }
#ifdef DEMO_DEBUG
                else if (event.key.keysym.sym == 'p')
                {
                    if (!paused)
                    {
                        pauseTime = SDL_GetTicks();
                    }
                    else
                    {
                        timeSkipOffset -= SDL_GetTicks() - pauseTime;
                    }
                    paused = !paused;
                }
                else if (event.key.keysym.sym == SDLK_LCTRL ||
                         event.key.keysym.sym == SDLK_RCTRL)
                {
                    timeSkip = true;
                }
                break;
            case SDL_KEYUP:
                if (event.key.keysym.sym == SDLK_LCTRL ||
                    event.key.keysym.sym == SDLK_RCTRL)
                {
                    timeSkip = false;
                }
                break;
#endif
        }
    }
    return true;
}

int Video::ticks()
{
    int t = SDL_GetTicks();
    if (timeSkip)
    {
        timeSkipOffset += 20;
    }
    if (paused)
    {
        return pauseTime + timeSkipOffset;
    }
    return t + timeSkipOffset;
}
