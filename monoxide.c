#include "monoxide.h"
#include <malloc.h>
#include <assert.h>

#define MX_SCANLINE_ALIGNMENT   0x10
#define MX_ASSERT(X)            assert(X)

MXSurface* mxCreateSurface(int w, int h, MXPixelFormat format)
{
    MXSurface* s = (MXSurface*)malloc(sizeof(MXSurface));
    if (!s)
    {
        return s;
    }
    s->pixelFormat = format;
    s->w = w;
    s->h = h;
    s->stride = (format == MX_PIXELFORMAT_I1) ? (s->w / 8) : s->w;
    s->stride += MX_SCANLINE_ALIGNMENT - (s->stride & (MX_SCANLINE_ALIGNMENT - 1));
    s->pixels = malloc(s->h * s->stride);
    return s;
}

void mxDestroySurface(MXSurface* s)
{
    if (s)
    {
        free(s->pixels);
        free(s);
    }
}

static int clipRect(const MXRect* srcRect, const MXRect* destRect, MXRect* result)
{
    
}

static void blit_I1_I1(uint8_t* dest, const uint8_t* src, int w, int h, int srcStride, int destStride)
{
    int x;

    while (h--)
    {
        uint8_t* d = dest;
        const uint8_t* s = src;

        for (x = 0; x < w; x += 8)
        {
            *d++ = *s++;
        }

        dest += destStride;
        src  += srcStride;
    }
}

void mxBlit(MXSurface* dest, const MXSurface* src, const MXSurface* mask,
            int x, int y, const MXRect* srcRect, int flags)
{
    MX_ASSERT(dest);
    MX_ASSERT(dest->pixelFormat == MX_PIXELFORMAT_I1);
    MX_ASSERT(src);
    {
        MXRect fullRect;

        if (!srcRect)
        {
            fullRect.x = fullRect.y = 0;
            fullRect.w = src->w;
            fullRect.h = src->h;
            srcRect = &fullRect;
        }

        switch (src->pixelFormat)
        {
        case MX_PIXELFORMAT_I1:
            {
            uint8_t* destPixels = dest->pixels;
            uint8_t* srcPixels  = src->pixels;

            destPixels += (y * dest->stride + x / 8);
            srcPixels  += (srcRect->y * src->stride + srcRect->x / 8);

            blit_I1_I1(destPixels, srcPixels, srcRect->w, srcRect->h, src->stride, dest->stride);
            }
            break;
        default:
            MX_ASSERT(0);
            break;
        }
    }
}
