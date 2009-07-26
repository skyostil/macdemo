/**
 * Copyright (C) 2009 Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 */
#ifndef VIDEO_H
#define VIDEO_H

class Video
{
public:
    Video(int w, int h);
    ~Video();
    
    void waitRefresh();
    int refreshCount();
    int screenWidth();
    int screenHeight();
    int screenStride();
    void* screenPixels();
    void swapBuffers();
    bool processInput();
};

#endif
