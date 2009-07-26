/**
 *  monoxide 1-bit blitting library
 *  Copyright (C) 2009 Sami Kyöstilä <sami.kyostila@unrealvoodoo.org>
 */
#ifndef MONOXIDE_H
#define MONOXIDE_H

#include <stdint.h>

typedef enum MXPixelFormat_t
{
    MX_PIXELFORMAT_I1   = 1,
    MX_PIXELFORMAT_I8   = 8,
    MX_PIXELFORMAT_LAST = (1 << 31),
} MXPixelFormat;

typedef struct MXRect_t
{
    int x, y, w, h;
} MXRect;

typedef enum MXSurfaceFlag_t
{
    MX_SURFACE_FLAG_PRESHIFT = 0x1,
    MX_SURFACE_FLAG_DIRTY    = 0x2,
    MX_SURFACE_FLAG_LAST     = (1 << 31),
} MXSurfaceFlag;

typedef struct MXSurface_t
{
    int w, h;
    int stride;
    int log2Stride;
    MXPixelFormat pixelFormat;
    int flags;
    int planeSize;
    int planes;
    uint8_t* pixels;
} MXSurface;

/* Surface management */
MXSurface* mxCreateWindow(int w, int h);
void mxDestroyWindow(MXSurface* s);
void mxSwapBuffers(MXSurface* s);
MXSurface* mxCreateSurface(int w, int h, MXPixelFormat format, int flags);
void mxDestroySurface(MXSurface* s);
void mxFlushSurface(MXSurface* s);

/* Rendering */
void mxBlit(MXSurface* dest, const MXSurface* src, const MXSurface* mask,
            int x, int y, const MXRect* srcRect, int flags);

/* Miscellaneous */
int mxProcessEvents(void);

#endif /* MONOXIDE_H */
