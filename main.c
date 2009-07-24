#include "monoxide.h"
#include <malloc.h>
#include <assert.h>

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
    MXSurface* surf = mxCreateSurface(256, 256, MX_PIXELFORMAT_I1);
    int t = 0;

    fillCircle(surf, 128, 128, 128);

    while (mxProcessEvents())
    {
        mxBlit(winSurf, surf, NULL, t & 0x7f, t & 0x7f, NULL, 0);
        mxSwapBuffers(winSurf);
        t++;
        SDL_Delay(100);
    }

    mxDestroyWindow(winSurf);
    mxDestroySurface(surf);
    return 0;
}
