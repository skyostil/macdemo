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

    s = mxCreateSurface(win->w, win->h, MX_PIXELFORMAT_I1);
    return s;
}

void mxDestroyWindow(MXSurface* s)
{
    if (s)
    {
        mxDestroySurface(s);
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

int mxProcessEvents(void)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    return 0;
                }
                break;
        }
    }
    return 1;
}
