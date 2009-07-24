#include "monoxide.h"
#include <SDL.h>
#include <assert.h>

static SDL_Surface* win = 0;

MXSurface* mxCreateWindow(int w, int h)
{
    MXSurface* s;
    win = SDL_SetVideoMode(w, h, 32, 0);
    if (!win)
    {
        return NULL;
    }

    s = (MXSurface*)malloc(sizeof(MXSurface));
    s->pixelFormat = MX_PIXELFORMAT_I1;
    s->w = win->w;
    s->h = win->h;
    s->stride = s->w / 8;
    s->pixels = malloc(s->h * s->stride);
    return s;
}

void mxDestroyWindow(MXSurface* s)
{
    if (s)
    {
        free(s->pixels);
        free(s);
    }
    if (win)
    {
        SDL_FreeSurface(win);
        win = 0;
    }
}

void mxSwapBuffers(MXSurface* s)
{
    int x, y;
    const uint32_t palette[] = {
        0x00000000,
        0xffffffff,
    };
    uint32_t* dest = (uint32_t*)win->pixels;
    uint8_t* src = (uint8_t*)s->pixels;
    
    assert(win);
    assert(s->pixelFormat == MX_PIXELFORMAT_I1);

    SDL_LockSurface(win);

    for (y = 0; y < s->h; y++)
    {
        for (x = 0; x < s->w; x++)
        {
            dest[x] = palette[src[x / 8] & (1 << (x & 0x7)) ? 1 : 0];
        }
        dest += win->pitch / 4;
        src += s->stride;
    }

    SDL_UnlockSurface(win);
    SDL_Flip(win);
}

