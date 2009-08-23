/**
 * Copyright (C) 2009 Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 */
#include "Config.h"
#include "ModPlayer.h"
#include "Mixer.h"
#include "Engine.h"
#include "MacAudio.h"
#include "MacVideo.h"
#include "monoxide.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <Desk.h>
#include <Devices.h>
#include <Processes.h>

void benchmark()
{
    printf("Lataillaan\n");

    Mixer mixer(22050, 4);
    ModPlayer player(&mixer);
    SampleFormat sampleFormat(8, 1);
    SampleChunk samples(&sampleFormat, 4096, mixer.outputFreq);
    int i = 0, t1, t2;
    
    if (!player.load("music.mod"))
    {
        printf("Failed to load song.\n");
        return;
    }
    
    player.play();
    printf("Ready.\n");

    t1 = time(NULL);
    for (i = 0; i < 200; i++)
    {
        //printf("%d\n", i++);
        mixer.render(&samples);
    }
    t2 = time(NULL);
    printf("diff: %d\n", t2 - t1);
}

void playback()
{
    printf("Lataillaan\n");
    MacAudio audio(8, 11127, 0, 512);
    //MacAudio audio(8, 22050, 0, 512);
    
    Mixer mixer(audio.mixFreq, 4);
    ModPlayer player(&mixer);
    int i = 0, t1, t2;
    
    if (!player.load("music.mod"))
    {
        printf("Failed to load song.\n");
        return;
    }
    
    player.play();
    printf("Ready.\n");
    audio.start(&mixer);

    t1 = time(NULL);
    while (!Button())
    {
    }
    t2 = time(NULL);
    printf("diff: %d\n", t2 - t1);
    audio.stop();
}

void renderCheckers(MacVideo& video)
{
    unsigned int* s = (unsigned int*)video.getScreen();
    unsigned int color;
    int x, y, y2;
    int t;
        
    t = video.getTicks() & 31;
    color = (0xffff << t) + (0xffff >> (32 - t));
        
    if (t > 0xf)
    {
        color = 0xffffffff ^ color;
    }
        
    for (y = 0; y < SCREEN_HEIGHT; y+=16)
    {
        for (y2 = t & 0xf; y2 < 16; y2++)
        for (x = 0; x < SCREEN_WIDTH; x+=32)
        {
            *s++ = color;
        }
        color = 0xffffffff ^ color;
        t = 0;
    }
    //color = (color >> 1) + (color << 31);
}

OSErr getCurrentProcessLocation(FSSpec *spec)
{
    ProcessSerialNumber currentPSN;
    ProcessInfoRec info;
    
    currentPSN.highLongOfPSN = 0;
    currentPSN.lowLongOfPSN = kCurrentProcess;
    info.processInfoLength = sizeof(ProcessInfoRec);
    info.processName = NULL;
    info.processAppSpec = spec;
    return GetProcessInformation(&currentPSN, &info);
}

void videotest()
{
    MacVideo video;

    while (!Button())
    {
        video.waitRefresh();
        renderCheckers(video);
    }
}

void avtest()
{
    MacVideo video;
    MacAudio audio(8, 11127, 0, 512);

    printf("Lataillaan\n");
    
    Mixer mixer(audio.mixFreq, 4);
    ModPlayer player(&mixer);
    
    if (!player.load("music.mod"))
    {
        printf("Failed to load song.\n");
        return;
    }
    
    player.play();
    printf("Ready.\n");
    audio.start(&mixer);

    while (!Button())
    {
        video.waitRefresh();
        renderCheckers(video);
    }
    audio.stop();
}

static far char ioBuffer[11025 * 4];
static volatile int ioDone = 1;

void ioFinished(ParmBlkPtr paramBlock: __A0)
{
    long a5 = SetCurrentA5();
    //SysBeep(10);
    //printf("IO FINISHED!\n");
    ioDone = 1;
    SetA5(a5);
}

void filetest()
{
    MacVideo video;
    FSSpec fsSpec;
    
    getCurrentProcessLocation(&fsSpec);
    
    //short vRefNum;
    //long freeBytes;
    //printf("Err: %d\n", GetVInfo(0, NULL, &vRefNum, &freeBytes));
    printf("Volume: %d, %d\n", fsSpec.vRefNum, fsSpec.parID);
    
    HParamBlockRec p;   
    ParamBlockRec p2;   
    Str255 fileName = "\pmusic.raw";
    memset(&p, 0, sizeof(p));
    memset(&p2, 0, sizeof(ParamBlockRec));
    memset(ioBuffer, 0, sizeof(ioBuffer));
    p.ioParam.ioCompletion = NULL;
    p.fileParam.ioNamePtr = fileName;
    p.fileParam.ioVRefNum = fsSpec.vRefNum;
    p.fileParam.ioDirID = fsSpec.parID;
    p.ioParam.ioPermssn = fsRdPerm;
    p.ioParam.ioMisc = 0;
    OSErr err = PBHOpenDFSync(&p);
    
    if (err != noErr)
    {
        printf("Unable to open file (%d)\n", err);
        return;
    }
    
    p.ioParam.ioCompletion = NewIOCompletionProc(ioFinished);
    //p.ioParam.ioBuffer = ioBuffer;
    //p.ioParam.ioReqCount = sizeof(ioBuffer);
    //p.ioParam.ioPosMode = fsFromStart;
    //p.ioParam.ioPosOffset = 0;
    //err = PBReadAsync(&p);
    //p.ioParam.ioCompletion = NewIOCompletionProc(ioFinished);
    printf("File: %d, %d\n", p.ioParam.ioRefNum, p.ioParam.ioVRefNum);
    //ParamBlockRec* p2 = new ParamBlockRec;
    //memset(p2, 0, sizeof(ParamBlockRec));

    long start = time(NULL);
    while (!Button() && p2.ioParam.ioResult >= 0)
    {
        int i, j = 0;
        for (i = 0; i < sizeof(ioBuffer); i++)
            j += ioBuffer[i];
        //printf("Sum: %d\n", j);
        //printf("Done: %d, %d\n", ioDone, p2.ioParam.ioResult);
        if (ioDone)
        {
            //printf("Result: %d\n", p.ioParam.ioResult);
            ioDone = 0;
            //p2 = new ParamBlockRec;
            memset(&p2, 0, sizeof(ParamBlockRec));
            p2.ioParam.ioRefNum = p.ioParam.ioRefNum;
            p2.ioParam.ioVRefNum = p.ioParam.ioVRefNum;
            p2.ioParam.ioResult = 0;
            p2.ioParam.ioActCount = 0;
            p2.ioParam.ioBuffer = ioBuffer;
            p2.ioParam.ioReqCount = sizeof(ioBuffer);
            p2.ioParam.ioPosMode = fsAtMark;
            p2.ioParam.ioPosOffset = 0;
            p2.ioParam.ioCompletion = NewIOCompletionProc(ioFinished);
            //PBSetFPos(&p, 0);
            err = PBReadAsync(&p2);
            //ioDone = 1;
            //printf("Read: %d\n", err);
            //if (err < 0)
            //{
            //  break;
            //}
        }
        //SystemTask();
        video.waitRefresh();
        renderCheckers(video);
    }
    printf("Time: %d\n", time(NULL) - start);
    printf("Done: %d, %d\n", ioDone, p.ioParam.ioResult);
    PBCloseSync(&p2);
    printf("Finished\n");
}

void fillPattern(MXSurface* s)
{
    int x, y;

    for (y = 0; y < s->h; y++)
    {
        for (x = 0; x < s->w; x += 8)
        {
            s->pixels[y * s->stride + x / 8] = x ^ y;
        }
    }
}

void fillCheckers(MXSurface* s, int cw, int ch)
{
    int x, y;

    for (y = 0; y < s->h; y++)
    {
        for (x = 0; x < s->w; x++)
        {
            int d = ((x >> cw) + (y >> ch)) & 0x1;
            if (d)
            {
                s->pixels[y * s->stride + x / 8] |= 0x80 >> (x & 0x7);
            }
            else
            {
                s->pixels[y * s->stride + x / 8] &= ~(0x80 >> (x & 0x7));
            }
        }
    }
}

void fillCircle(MXSurface* s, int cx, int cy, int r)
{
    int x, y;
    int r2 = r * r;

    for (y = 0; y < s->h; y++)
    {
        for (x = 0; x < s->w; x++)
        {
            int d2 = (x - cx) * (x - cx) + (y - cy) * (y - cy);
            if (d2 <= r2)
            {
                s->pixels[y * s->stride + x / 8] |= 0x80 >> (x & 0x7);
            }
            else
            {
                s->pixels[y * s->stride + x / 8] &= ~(0x80 >> (x & 0x7));
            }
        }
    }
}

void monoxideTest()
{
    MacVideo video;
    MXSurface* winSurf = mxCreateUserMemorySurface(SCREEN_WIDTH, SCREEN_HEIGHT, 
                                                   MX_PIXELFORMAT_I1, SCREEN_WIDTH >> 3, 
                                                   0, video.getScreen());
    MXSurface* backSurf = mxCreateSurface(SCREEN_WIDTH, SCREEN_HEIGHT, MX_PIXELFORMAT_I1, 0);
                                                   
    MXSurface* surf    = mxCreateSurface(256, 256, MX_PIXELFORMAT_I1, MX_SURFACE_FLAG_PRESHIFT);
    MXSurface* surf2   = mxCreateSurface(256, 256, MX_PIXELFORMAT_I1, MX_SURFACE_FLAG_PRESHIFT);
    int x = 93, y = 17;
    int dx = 1, dy = 1;

    fillCheckers(surf, 4, 4);
    mxFlushSurface(surf);

    fillCircle(surf2, 128, 128, 100);
    mxFlushSurface(surf2);

    while (!Button())
    {
        mxFill(backSurf, NULL, 1);
        //fillCheckers(backSurf, 0, 0);
        mxBlit(backSurf, surf, NULL, 32, 32, NULL, 0);
        mxBlit(backSurf, surf, surf2, x, y, NULL, 0);
        //mxBlit(backSurf, surf, NULL, 256 - (t & 0x3ff), (t & 0x3ff) - 128, NULL, 0);
        //mxBlit(backSurf, surf, NULL, -128 + (t & 0xf), -128 + (t & 0xf), NULL, 0);
        x += dx;
        y += dy;

        if (x < 0)
        {
            x = -x;
            dx = -dx;
        }

        if (x + surf->w > winSurf->w)
        {
            x += 2 * (winSurf->w - (x + surf->w));
            dx = -dx;
        }

        if (y < 0)
        {
            y = -y;
            dy = -dy;
        }

        if (y + surf->h > winSurf->h)
        {
            y += 2 * (winSurf->h - (y + surf->h));
            dy = -dy;
        }
        video.waitRefresh();
        mxBlit(winSurf, backSurf, NULL, 0, 0, NULL, 0);
    }
    mxDestroySurface(surf);
    mxDestroySurface(surf2);
    mxDestroySurface(winSurf);
}

int main(int argc, const char** argv)
{
    //benchmark();
    //playback();
    //videotest();
    //avtest();
    //filetest();
    monoxideTest();
    return 0;
}
