/**
 *  monoxide 1-bit blitting library
 *  Copyright (C) 2009 Sami Kyöstilä <sami.kyostila@unrealvoodoo.org>
 */
#include "monoxide.h"
#include <malloc.h>
#include <memory.h>
#include <assert.h>

#define MX_SCANLINE_ALIGNMENT   0x10
#define MX_ASSERT(X)            assert(X)
#define MX_UNUSED(X)            (void)(X)

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

int log2i(int n)
{
    int x = 0;
    while ((1 << x) < n)
    {
        x++;
    }
    return x;
}

MXSurface* mxCreateSurface(int w, int h, MXPixelFormat format, int flags)
{
    MX_ASSERT(w >= 8);
    MX_ASSERT(h >= 8);
    {
        MXSurface* s = (MXSurface*)malloc(sizeof(MXSurface));
        if (!s)
        {
            return s;
        }
        s->pixelFormat = format;
        s->flags = flags;
        s->w = w;
        s->h = h;
        s->stride = (format == MX_PIXELFORMAT_I1) ? (s->w / 8) : s->w;
        s->stride += (MX_SCANLINE_ALIGNMENT - (s->stride & (MX_SCANLINE_ALIGNMENT - 1))) & (MX_SCANLINE_ALIGNMENT - 1);
        s->log2Stride = log2i(s->stride);
        s->planeSize = s->h << s->log2Stride;
        s->planes = 1;

        if (flags & MX_SURFACE_FLAG_PRESHIFT)
        {
            s->flags |= MX_SURFACE_FLAG_DIRTY;
            s->planes = 8;
        }

        s->pixels = malloc(s->planes * s->planeSize + 4);

        if (!s->pixels)
        {
            free(s);
            return NULL;
        }

        MX_ASSERT(isPowerOfTwo(s->stride));
        MX_ASSERT((s->stride & (MX_SCANLINE_ALIGNMENT - 1)) == 0);

        return s;
    }
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

static void blit_I1_I1(uint8_t* dest, const uint8_t* src, const MXRect* destRect, int srcStride, int destStride)
{
    int x;
    int w = destRect->w >> 3;

    /* Right lobe, sub-byte pixels */
    if ((destRect->x + destRect->w) & 0x7)
    {
        int h = destRect->h;
        uint8_t mask = (1 << ((destRect->x + destRect->w) & 0x7)) - 1;
        uint8_t invMask = ~mask;
        uint8_t* d = dest + w;
        const uint8_t* s = src + w;

        while (h--)
        {
            *d = (*d & invMask) | (*s & mask);
            d += destStride;
            s += srcStride;
        }
    }

    /* Left lobe, sub-byte pixels */
    if (destRect->x & 0x7)
    {
        int h = destRect->h;
        uint8_t mask = (1 << (destRect->x & 0x7)) - 1;
        uint8_t invMask = ~mask;
        uint8_t* d = dest;
        const uint8_t* s = src;

        while (h--)
        {
            *d = (*d & mask) | (*s & invMask);
            d += destStride;
            s += srcStride;
        }

        src++;
        dest++;
        w--;
    }

    /* Center lobe, 32-bit pixels */
    if (w >= 0x4)
    {
        int h = destRect->h;
        uint8_t* d = dest;
        const uint8_t* s = src;
        while (h--)
        {
            uint32_t* d32 = (uint32_t*)d;
            const uint32_t* s32 = (uint32_t*)s;

            for (x = 0; x <= w - 4; x += 4)
            {
                *d32++ = *s32++;
            }

            d += destStride;
            s += srcStride;
        }
        dest += x;
        src  += x;
        w    &= 0x3;
    }

    /* Center lobe, 8-bit pixels */
    if (w)
    {
        int h = destRect->h;
        while (h--)
        {
            uint8_t* d = dest;
            const uint8_t* s = src;

            for (x = 0; x < w; x++)
            {
                *d++ = *s++;
            }

            dest += destStride;
            src  += srcStride;
        }
    }
}

void mxBlit(MXSurface* dest, const MXSurface* src, const MXSurface* mask,
            int x, int y, const MXRect* srcRect, int flags)
{
    MX_ASSERT(dest);
    MX_ASSERT(dest->pixelFormat == MX_PIXELFORMAT_I1);
    MX_ASSERT(src);
    MX_ASSERT(!(src->flags & MX_SURFACE_FLAG_DIRTY));
    MX_UNUSED(mask);
    MX_UNUSED(flags);
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

            if (src->flags & MX_SURFACE_FLAG_PRESHIFT)
            {
                int plane = (clippedDestRect.x - (clippedDestRect.x - x)) & 0x7;
                srcPixels += src->planeSize * plane;
            }

            destPixels += (((clippedDestRect.y)     << dest->log2Stride) + ((clippedDestRect.x)         >> 3));
            srcPixels  += (((clippedDestRect.y - y) <<  src->log2Stride) + ((clippedDestRect.x - x + 7) >> 3));

            blit_I1_I1(destPixels, srcPixels, &clippedDestRect, src->stride, dest->stride);
            }
            break;
        default:
            MX_ASSERT(0);
            break;
        }

        dest->flags |= MX_SURFACE_FLAG_DIRTY;
    }
}

void mxFlushSurface(MXSurface* s)
{
    if (!(s->flags & MX_SURFACE_FLAG_PRESHIFT))
    {
        return;
    }

    MX_ASSERT(s->flags & MX_SURFACE_FLAG_DIRTY);
    MX_ASSERT(s->planes == 8);
    {
        int i, x, y;
        uint8_t* destPlane = s->pixels + s->planeSize;

        MX_ASSERT(s->planeSize == s->stride * s->h);

        for (i = 1; i < 8; i++)
        {
            const uint8_t* srcPlane = s->pixels;
            uint8_t mask = ((1 << i) - 1) << (8 - i);
            int invI = 8 - i;

            for (y = 0; y < s->h; y++)
            {
                const uint8_t* src = srcPlane;
                uint8_t*      dest = destPlane;

                *dest++ = (*src++) << i;
                for (x = 1; x < s->w / 8; x++)
                {
                    *dest++ = ((src[-1] & mask) >> invI) | (src[0] << i);
                    src++;
                }

                srcPlane  += s->stride;
                destPlane += s->stride;
            }
        }
        s->flags &= ~MX_SURFACE_FLAG_DIRTY;
    }
}

void mxFill(MXSurface* s, const MXRect* rect, int value)
{
    MX_ASSERT(rect == NULL);
    {
        memset(s->pixels, value ? 0xff : 0x00, s->planeSize);
        s->flags |= MX_SURFACE_FLAG_DIRTY;
    }
}

