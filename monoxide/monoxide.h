/**
 *  monoxide 1-bit blitting library
 *  Copyright (C) 2009 Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 */
#ifndef MONOXIDE_H
#define MONOXIDE_H

#if defined(HAVE_STDINT_H)
#   include <stdint.h>
#else
typedef unsigned char uint8_t;
typedef unsigned int  uint32_t;
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef enum MXPixelFormat_t
{
    MX_PIXELFORMAT_I1   = 1,
    MX_PIXELFORMAT_LAST = (1 << 31)
} MXPixelFormat;

typedef struct MXRect_t
{
    int x, y, w, h;
} MXRect;

typedef enum MXSurfaceFlag_t
{
    MX_SURFACE_FLAG_PRESHIFT    = 0x1,
    MX_SURFACE_FLAG_DIRTY       = 0x2,
    MX_SURFACE_FLAG_USER_MEMORY = 0x4,
    MX_SURFACE_FLAG_LAST        = (1 << 31)
} MXSurfaceFlag;

typedef struct MXSurface_t
{
    int w, h;
    int stride;
    MXPixelFormat pixelFormat;
    int flags;
    int planeSize;
    int planes;
    uint8_t* pixels;
} MXSurface;

/* Surface management */
MXSurface* mxCreateSurface(int w, int h, MXPixelFormat format, int flags);
MXSurface* mxCreateUserMemorySurface(int w, int h, MXPixelFormat format, int stride, int flags, void* data);
void mxDestroySurface(MXSurface* s);
void mxFlushSurface(MXSurface* s);

/* Rendering */
void mxBlit(MXSurface* dest, const MXSurface* src, const MXSurface* mask,
            int x, int y, const MXRect* srcRect, int flags);
void mxFill(MXSurface* dest, const MXRect* rect, int color);
void mxFillCheckerPattern(MXSurface* dest, int cw, int ch);
void mxFillCirclePattern(MXSurface* s, int cx, int cy, int r);
void mxFillSierpinskiPattern(MXSurface* dest);

#ifdef __cplusplus
}
#endif

#endif /* MONOXIDE_H */
