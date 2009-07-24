#ifndef MONOXIDE_H
#define MONOXIDE_H

#include <stdint.h>

typedef enum MXPixelFormat_t
{
    MX_PIXELFORMAT_I1 = 1,
    MX_PIXELFORMAT_I8 = 8,
} MXPixelFormat;

typedef struct MXRect_t
{
    int x, y, w, h;
} MXRect;

typedef struct MXSurface_t
{
    int w, h, stride;
    MXPixelFormat pixelFormat;
    uint8_t* pixels;
} MXSurface;

/* Initialization */
MXSurface* mxCreateWindow(int w, int h);
void mxDestroyWindow(MXSurface* s);
void mxSwapBuffers(MXSurface* s);

/* Rendering */
void mxBlit(MXSurface* dest, const MXSurface* src, const MXSurface* mask, int x, int y, const MXRect* srcRect, int flags);

#endif /* MONOXIDE_H */
