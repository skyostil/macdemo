/**
 * Copyright (C) 2009 Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 */
#ifndef VIDEO_H
#define VIDEO_H

#include "Config.h"

class Video
{
public:
    Video(int w, int h, bool fullscreen);
    ~Video();
    
    void waitRefresh();
    int refreshCount();
    int ticks();
    int screenWidth();
    int screenHeight();
    int screenStride();
    void* screenPixels();
    void swapBuffers();
    bool processInput();
};

#endif
