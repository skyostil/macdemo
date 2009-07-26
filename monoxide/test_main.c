/**
 *  monoxide 1-bit blitting library
 *  Copyright (C) 2009 Sami Kyöstilä <sami.kyostila@unrealvoodoo.org>
 */
#include "monoxide.h"
#include "monoxide_sdl.h"
#include <malloc.h>
#include <assert.h>
#include <SDL.h>

void blitTest()
{
    MXSurface* winSurf = mxCreateWindow(512, 342);
    MXSurface* surf    = mxCreateSurface(256, 256, MX_PIXELFORMAT_I1, MX_SURFACE_FLAG_PRESHIFT);
    MXSurface* surf2   = mxCreateSurface(256, 256, MX_PIXELFORMAT_I1, MX_SURFACE_FLAG_PRESHIFT);
    MXRect rect;
    int t = 0;
    int x = 93, y = 17;
    int dx = 1, dy = 1;

    mxFillCheckerPattern(surf, 4, 4);
    mxFlushSurface(surf);

    mxFillCirclePattern(surf2, 128, 128, 100);
    mxFlushSurface(surf2);

    while (mxProcessEvents())
    {
        //fillCheckers(winSurf, 0, 0);
        mxFill(winSurf, NULL, 1);
        mxBlit(winSurf, surf, NULL, 32, 32, NULL, 0);
        mxBlit(winSurf, surf, surf2, x, y, NULL, 0);
        //mxBlit(winSurf, surf, NULL, 256 - (t & 0x3ff), (t & 0x3ff) - 128, NULL, 0);
        //mxBlit(winSurf, surf, NULL, -128 + (t & 0xf), -128 + (t & 0xf), NULL, 0);
        
        rect.x = x + 64;
        rect.y = y + 64;
        rect.w = 121;
        rect.h = 121;
        mxFill(winSurf, &rect, 1);

        mxSwapBuffers(winSurf);
        t++;
        SDL_Delay(100);

        x += dx;
        y += dy;

        if (x < 0)
        {
            x = -x;
            dx = -dx;
        }

        if (x + surf->w > winSurf->w)
        {
            x += 2 * (winSurf->w - (x + surf->w));
            dx = -dx;
        }

        if (y < 0)
        {
            y = -y;
            dy = -dy;
        }

        if (y + surf->h > winSurf->h)
        {
            y += 2 * (winSurf->h - (y + surf->h));
            dy = -dy;
        }
    }

    mxDestroySurface(surf);
    mxDestroySurface(surf2);
    mxDestroyWindow(winSurf);
}
