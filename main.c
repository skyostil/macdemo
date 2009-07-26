/**
 *  monoxide 1-bit blitting library
 *  Copyright (C) 2009 Sami Kyöstilä <sami.kyostila@unrealvoodoo.org>
 */
#include "monoxide.h"
#include <malloc.h>
#include <assert.h>
#include <SDL.h>

void fillPattern(MXSurface* s)
{
    int x, y;

    for (y = 0; y < s->h; y++)
    {
        for (x = 0; x < s->w; x += 8)
        {
            s->pixels[y * s->stride + x / 8] = x ^ y;
        }
    }
}

void fillCheckers(MXSurface* s, int cw, int ch)
{
    int x, y;

    for (y = 0; y < s->h; y++)
    {
        for (x = 0; x < s->w; x++)
        {
            int d = ((x >> cw) + (y >> ch)) & 0x1;
            if (d)
            {
                s->pixels[y * s->stride + x / 8] |= 1 << (x & 0x7);
            }
            else
            {
                s->pixels[y * s->stride + x / 8] &= ~(1 << (x & 0x7));
            }
        }
    }
}

void fillCircle(MXSurface* s, int cx, int cy, int r)
{
    int x, y;
    int r2 = r * r;

    for (y = 0; y < s->h; y++)
    {
        for (x = 0; x < s->w; x++)
        {
            int d2 = (x - cx) * (x - cx) + (y - cy) * (y - cy);
            if (d2 <= r2)
            {
                s->pixels[y * s->stride + x / 8] |= 1 << (x & 0x7);
            }
            else
            {
                s->pixels[y * s->stride + x / 8] &= ~(1 << (x & 0x7));
            }
        }
    }
}

void blitTest()
{
    MXSurface* winSurf = mxCreateWindow(512, 384);
    MXSurface* surf    = mxCreateSurface(256, 256, MX_PIXELFORMAT_I1, MX_SURFACE_FLAG_PRESHIFT);
    MXSurface* surf2   = mxCreateSurface(256, 256, MX_PIXELFORMAT_I1, MX_SURFACE_FLAG_PRESHIFT);
    int t = 0;
    int x = 23, y = 17;
    int dx = 1, dy = 1;

    fillCheckers(surf, 4, 4);
    mxFlushSurface(surf);

    fillCircle(surf2, 128, 128, 100);
    mxFlushSurface(surf2);

    while (mxProcessEvents())
    {
        mxFill(winSurf, NULL, 0);
        //fillCheckers(winSurf, 0, 0);
        mxBlit(winSurf, surf, NULL, 32, 32, NULL, 0);
        mxBlit(winSurf, surf, surf2, x, y, NULL, 0);
        //mxBlit(winSurf, surf, NULL, 256 - (t & 0x3ff), (t & 0x3ff) - 128, NULL, 0);
        //mxBlit(winSurf, surf, NULL, -128 + (t & 0xf), -128 + (t & 0xf), NULL, 0);
        mxSwapBuffers(winSurf);
        t++;
        SDL_Delay(10);

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

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    blitTest();

    return 0;
}
