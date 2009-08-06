/**
 *  monoxide 1-bit blitting library
 *  Copyright (C) 2009 Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 */
#include "monoxide.h"

void blit_I1_to_I1(uint8_t* dest, const uint8_t* src, const MXRect* destRect,
                   int srcStride, int destStride, int srcFlags)
{
    int x = 0;
    int w = ((destRect->w + (destRect->x & 0x7)) >> 3);

    /* Right lobe, sub-byte pixels */
    if ((srcFlags & MX_SURFACE_FLAG_PRESHIFT) &&
       ((destRect->x + destRect->w) & 0x7))
    {
        int h = destRect->h;
        uint8_t pixelMask = ~(0xff >> ((destRect->x + destRect->w) & 0x7));
        uint8_t* d = dest + w;
        const uint8_t* s = src + w;

        while (h--)
        {
            *d = *d ^ ((*d ^ *s) & pixelMask);
            d += destStride;
            s += srcStride;
        }
    }

    /* Left lobe, sub-byte pixels */
    if ((srcFlags & MX_SURFACE_FLAG_PRESHIFT) &&
        (destRect->x & 0x7))
    {
        int h = destRect->h;
        uint8_t pixelMask = (0xff >> (destRect->x & 0x7));
        uint8_t* d = dest;
        const uint8_t* s = src;

        while (h--)
        {
            *d = *d ^ ((*d ^ *s) & pixelMask);
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

void blit_I1_to_I1_xor(uint8_t* dest, const uint8_t* src, const MXRect* destRect,
                       int srcStride, int destStride, int srcFlags)
{
    int x = 0;
    int w = ((destRect->w + (destRect->x & 0x7)) >> 3);

    /* Right lobe, sub-byte pixels */
    if ((srcFlags & MX_SURFACE_FLAG_PRESHIFT) &&
       ((destRect->x + destRect->w) & 0x7))
    {
        int h = destRect->h;
        uint8_t pixelMask = ~(0xff >> ((destRect->x + destRect->w) & 0x7));
        uint8_t* d = dest + w;
        const uint8_t* s = src + w;

        while (h--)
        {
            *d ^= *d ^ ((*d ^ *s) & pixelMask);
            d += destStride;
            s += srcStride;
        }
    }

    /* Left lobe, sub-byte pixels */
    if ((srcFlags & MX_SURFACE_FLAG_PRESHIFT) &&
        (destRect->x & 0x7))
    {
        int h = destRect->h;
        uint8_t pixelMask = (0xff >> (destRect->x & 0x7));
        uint8_t* d = dest;
        const uint8_t* s = src;

        while (h--)
        {
            *d ^= *d ^ ((*d ^ *s) & pixelMask);
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
                *d32++ ^= *s32++;
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
                *d++ ^= *s++;
            }

            dest += destStride;
            src  += srcStride;
        }
    }
}

void blit_I1_to_I1_mask_I1(uint8_t* dest, const uint8_t* src, const uint8_t* mask, const MXRect* destRect,
                           int srcStride, int destStride, int maskStride, int srcFlags)
{
    int x = 0;
    int w = ((destRect->w + (destRect->x & 0x7)) >> 3);

    /* Right lobe, sub-byte pixels */
    if ((srcFlags & MX_SURFACE_FLAG_PRESHIFT) &&
       ((destRect->x + destRect->w) & 0x7))
    {
        int h = destRect->h;
        uint8_t pixelMask = ~(0xff >> ((destRect->x + destRect->w) & 0x7));
        uint8_t* d = dest + w;
        const uint8_t* s = src + w;
        const uint8_t* m = mask + w;

        while (h--)
        {
            *d = *d ^ ((*d ^ *s) & pixelMask & *m);
            d += destStride;
            s += srcStride;
            m += maskStride;
        }
    }

    /* Left lobe, sub-byte pixels */
    if ((srcFlags & MX_SURFACE_FLAG_PRESHIFT) &&
        (destRect->x & 0x7))
    {
        int h = destRect->h;
        uint8_t pixelMask = ~(0xff >> (destRect->x & 0x7));
        uint8_t* d = dest;
        const uint8_t* s = src;
        const uint8_t* m = mask;

        while (h--)
        {
            *d = *d ^ ((*d ^ *s) & pixelMask & *m);
            d += destStride;
            s += srcStride;
            m += maskStride;
        }

        src++;
        dest++;
        mask++;
        w--;
    }

    /* Center lobe, 32-bit pixels */
    if (w >= 0x4)
    {
        int h = destRect->h;
        uint8_t* d = dest;
        const uint8_t* s = src;
        const uint8_t* m = mask;
        while (h--)
        {
            uint32_t* d32 = (uint32_t*)d;
            const uint32_t* s32 = (uint32_t*)s;
            const uint32_t* m32 = (uint32_t*)m;

            for (x = 0; x <= w - 4; x += 4, d32++)
            {
                *d32 = *d32 ^ ((*d32 ^ *s32++) & *m32++);
            }

            d += destStride;
            s += srcStride;
            m += maskStride;
        }
        dest += x;
        src  += x;
        mask += x;
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
            const uint8_t* m = mask;

            for (x = 0; x < w; x++, d++)
            {
                *d = *d ^ ((*d ^ *s++) & *m++);
            }

            dest += destStride;
            src  += srcStride;
            mask += maskStride;
        }
    }
}

void fill_I1(uint8_t* dest, const MXRect* destRect, int destStride, int color)
{
    int x = 0;
    int w = ((destRect->w + (destRect->x & 0x7)) >> 3);
    color = color ? 0xff : 0x00;

    /* Right lobe, sub-byte pixels */
    if ((destRect->x + destRect->w) & 0x7)
    {
        int h = destRect->h;
        uint8_t pixelMask = ~(0xff >> ((destRect->x + destRect->w) & 0x7));
        uint8_t* d = dest + w;

        while (h--)
        {
            *d = *d ^ ((*d ^ color) & pixelMask);
            d += destStride;
        }
    }

    /* Left lobe, sub-byte pixels */
    if (destRect->x & 0x7)
    {
        int h = destRect->h;
        uint8_t pixelMask = ~(0xff >> (destRect->x & 0x7));
        uint8_t* d = dest;

        while (h--)
        {
            *d = color ^ ((*d ^ color) & pixelMask);
            d += destStride;
        }

        dest++;
        w--;
    }

    /* Center lobe, 32-bit pixels */
    if (w >= 0x4)
    {
        int h = destRect->h;
        uint8_t* d = dest;
        int color32 = color ? 0xffffffff : 0x00000000;
        while (h--)
        {
            uint32_t* d32 = (uint32_t*)d;

            for (x = 0; x <= w - 4; x += 4)
            {
                *d32++ = color32;
            }

            d += destStride;
        }
        dest += x;
        w    &= 0x3;
    }

    /* Center lobe, 8-bit pixels */
    if (w)
    {
        int h = destRect->h;
        while (h--)
        {
            uint8_t* d = dest;

            for (x = 0; x < w; x++)
            {
                *d++ = color;
            }

            dest += destStride;
        }
    }
}

void invert_I1(uint8_t* dest, const MXRect* destRect, int destStride)
{
    int x = 0;
    int w = ((destRect->w + (destRect->x & 0x7)) >> 3);

    /* Right lobe, sub-byte pixels */
    if ((destRect->x + destRect->w) & 0x7)
    {
        int h = destRect->h;
        uint8_t pixelMask = ~(0xff >> ((destRect->x + destRect->w) & 0x7));
        uint8_t* d = dest + w;

        while (h--)
        {
            *d ^= pixelMask;
            d += destStride;
        }
    }

    /* Left lobe, sub-byte pixels */
    if (destRect->x & 0x7)
    {
        int h = destRect->h;
        uint8_t pixelMask = ~(0xff >> (destRect->x & 0x7));
        uint8_t* d = dest;

        while (h--)
        {
            *d ^= pixelMask;
            d += destStride;
        }

        dest++;
        w--;
    }

    /* Center lobe, 32-bit pixels */
    if (w >= 0x4)
    {
        int h = destRect->h;
        uint8_t* d = dest;
        while (h--)
        {
            uint32_t* d32 = (uint32_t*)d;

            for (x = 0; x <= w - 4; x += 4)
            {
                *d32 = ~*d32;
				d32++;
            }

            d += destStride;
        }
        dest += x;
        w    &= 0x3;
    }

    /* Center lobe, 8-bit pixels */
    if (w)
    {
        int h = destRect->h;
        while (h--)
        {
            uint8_t* d = dest;

            for (x = 0; x < w; x++)
            {
                *d = ~*d;
				d++;
            }

            dest += destStride;
        }
    }
}
