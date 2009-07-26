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

int main(int argc, char** argv)
{
    MXSurface* winSurf = mxCreateWindow(512, 384);
    MXSurface* surf = mxCreateSurface(256, 256, MX_PIXELFORMAT_I1, MX_SURFACE_FLAG_PRESHIFT);
    int t = 0;
    (void)argc;
    (void)argv;

    fillCircle(surf, 128, 128, 100);
    mxFlushSurface(surf);

    while (mxProcessEvents())
    {
        mxBlit(winSurf, surf, NULL, 32, 32, NULL, 0);
        mxBlit(winSurf, surf, NULL, (t & 0x3ff) - 128, (t & 0x3ff) - 128, NULL, 0);
        //mxBlit(winSurf, surf, NULL, -128 + (t & 0xf), -128 + (t & 0xf), NULL, 0);
        mxSwapBuffers(winSurf);
        t++;
        SDL_Delay(100);
    }

    mxDestroyWindow(winSurf);
    mxDestroySurface(surf);
    return 0;
}
