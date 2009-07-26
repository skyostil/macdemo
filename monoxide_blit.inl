/**
 *  monoxide 1-bit blitting library
 *  Copyright (C) 2009 Sami Kyöstilä <sami.kyostila@unrealvoodoo.org>
 */

static void blit_I1_to_I1(uint8_t* dest, const uint8_t* src, const MXRect* destRect, int srcStride, int destStride)
{
    int x;
    int w = (destRect->w + 7) >> 3;

    /* Right lobe, sub-byte pixels */
    if ((destRect->x + destRect->w) & 0x7)
    {
        int h = destRect->h;
        uint8_t pixelMask = (1 << ((destRect->x + destRect->w) & 0x7)) - 1;
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
    if (destRect->x & 0x7)
    {
        int h = destRect->h;
        uint8_t pixelMask = (1 << (destRect->x & 0x7)) - 1;
        uint8_t* d = dest;
        const uint8_t* s = src;

        while (h--)
        {
            *d = *s ^ ((*d ^ *s) & pixelMask);
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

static void blit_I1_to_I1_mask_I1(uint8_t* dest, const uint8_t* src, const uint8_t* mask, const MXRect* destRect,
                                  int srcStride, int destStride, int maskStride)
{
    int x;
    int w = (destRect->w + 7) >> 3;

    /* Right lobe, sub-byte pixels */
    if ((destRect->x + destRect->w) & 0x7)
    {
        int h = destRect->h;
        uint8_t pixelMask = (1 << ((destRect->x + destRect->w) & 0x7)) - 1;
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
    if (destRect->x & 0x7)
    {
        int h = destRect->h;
        uint8_t pixelMask = (1 << (destRect->x & 0x7)) - 1;
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


