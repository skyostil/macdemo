#include "monoxide.h"
#include <malloc.h>
#include <assert.h>

#define MX_SCANLINE_ALIGNMENT   0x10
#define MX_ASSERT(X)            assert(X)

inline int min(int a, int b)
{
    return (a < b) ? a : b;
}

inline int max(int a, int b)
{
    return (a > b) ? a : b;
}

int isPowerOfTwo(int n)
{
    return (n & (n - 1)) == 0;
}

int smallerPowerOfTwo(int n)
{
    int x = 0;
    while ((1 << x) < n)
    {
        x++;
    }
    return x;
}

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
    s->stride += (MX_SCANLINE_ALIGNMENT - (s->stride & (MX_SCANLINE_ALIGNMENT - 1))) & (MX_SCANLINE_ALIGNMENT - 1);
    s->log2stride = smallerPowerOfTwo(s->stride);
    s->pixels = malloc(s->h * s->stride);

    MX_ASSERT(isPowerOfTwo(s->stride & (MX_SCANLINE_ALIGNMENT - 1) == 0));
    MX_ASSERT(isPowerOfTwo(s->stride));

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
    int x2 = srcRect->x + srcRect->w;
    int y2 = srcRect->y + srcRect->h;
    result->x = max(srcRect->x, destRect->x);
    result->y = max(srcRect->y, destRect->y);
    x2        = min(x2, destRect->x + destRect->w);
    y2        = min(y2, destRect->y + destRect->h);

    if (result->x >= destRect->x + destRect->w || result->y >= destRect->y + destRect->h)
    {
        return 0;
    }

    result->w = x2 - result->x;
    result->h = y2 - result->y;

    if (result->w <= 0 || result->h <= 0)
    {
        return 0;
    }

    return 1; 
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
        MXRect fullSrcRect, fullDestRect, destRect, clippedDestRect;

        if (!srcRect)
        {
            fullSrcRect.x = fullSrcRect.y = 0;
            fullSrcRect.w = src->w;
            fullSrcRect.h = src->h;
            srcRect = &fullSrcRect;
        }
        fullDestRect.x = fullDestRect.y = 0;
        fullDestRect.w = dest->w;
        fullDestRect.h = dest->h;
        destRect.x = x;
        destRect.y = y;
        destRect.w = srcRect->w;
        destRect.h = srcRect->h;

        if (!clipRect(&destRect, &fullDestRect, &clippedDestRect))
        {
            return;
        }

        switch (src->pixelFormat)
        {
        case MX_PIXELFORMAT_I1:
            {
            uint8_t* destPixels = dest->pixels;
            uint8_t* srcPixels  = src->pixels;

            destPixels += ((clippedDestRect.y       << dest->log2stride) +  clippedDestRect.x      / 8);
            srcPixels  += (((clippedDestRect.y - y) <<  src->log2stride) + (clippedDestRect.x - x) / 8);

            blit_I1_I1(destPixels, srcPixels, clippedDestRect.w, clippedDestRect.h, src->stride, dest->stride);
            }
            break;
        default:
            MX_ASSERT(0);
            break;
        }
    }
}
