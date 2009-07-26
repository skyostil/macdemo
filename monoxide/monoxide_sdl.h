/**
 *  monoxide 1-bit blitting library
 *  Copyright (C) 2009 Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 */
#ifndef MONOXIDE_SDL_H
#define MONOXIDE_SDL_H

#include "monoxide.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Window management */
MXSurface* mxCreateWindow(int w, int h);
void mxDestroyWindow(MXSurface* s);
void mxSwapBuffers(MXSurface* s);

/* Miscellaneous */
int mxProcessEvents(void);

#ifdef __cplusplus
}
#endif

#endif /* MONOXIDE_H */
