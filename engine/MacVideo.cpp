/**
 * Copyright (C) 2009 Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 */
#include "Video.h"
#include "Config.h"

#define VBL_RATE 1
#if 0
#define SCREEN_WIDTH 	(qd.screenBits.bounds.right - qd.screenBits.bounds.left)
#define SCREEN_HEIGHT	(qd.screenBits.bounds.bottom - qd.screenBits.bounds.top)
#else
#define SCREEN_WIDTH	512
#define SCREEN_HEIGHT   342
#endif

#include <Retrace.h>
#include <Timer.h>

#ifndef GENERATING68K
#error 68k only
#endif

void VBLRemoveAll(void);

typedef struct
{
    VBLTask	task;
    long	a5;
    int		ticks;
    volatile long vsyncFlag;
} VBLData;

static VBLData vblData;

VBLData* VBLGetData(void) =0x2008; /* MOVE.L A0, D0 */

void VBLInterruptServiceRoutine(void)
{
    long curA5;
    VBLData* data = VBLGetData();
    curA5 = SetA5(data->a5);
    
    /* Can access globals now */
    data->vsyncFlag = 1;
    data->ticks++;
    data->task.vblCount = VBL_RATE;
    
    SetA5(curA5);
}

void VBLInstall()
{
    vblData.a5 = SetCurrentA5();
    vblData.vsyncFlag = 0;
    vblData.ticks = 0;
    vblData.task.vblAddr = NewVBLProc(VBLInterruptServiceRoutine);
    vblData.task.vblCount = VBL_RATE;
    vblData.task.qType = vType;
    vblData.task.vblPhase = 0;
    VInstall((QElemPtr)&vblData.task);
}

void VBLRemove()
{
    VRemove((QElemPtr)&vblData.task);
}

Video::Video(int w, int h)
{
    (void)w;
    (void)h;
    MaxApplZone();
    InitGraf((Ptr) &qd.thePort);
    InitFonts();
    TEInit();
    InitWindows();
    InitMenus();
    InitDialogs( nil );
    InitCursor();
    HideCursor();
    FlushEvents( everyEvent, 0 );
    VBLInstall();
}
	
Video::~Video()
{
    VBLRemove();
}
	
void Video::waitRefresh()
{
    while (!vblData.vsyncFlag /* && !Button()*/)
    {
    }
    vblData.vsyncFlag = 0;
}

void* Video::screenPixels()
{
    return qd.screenBits.baseAddr;
}
    
int Video::refreshCount()
{
    return vblData.ticks;
}

int Video::screenWidth()
{
    return SCREEN_WIDTH;
}

int Video::screenHeight()
{
    return SCREEN_HEIGHT;
}

int Video::screenStride()
{
    return screenWidth() >> 3;
}

int Video::ticks()
{
	UnsignedWide t;
	Microseconds(&t);
    return t.lo / 1000;
}

int Video::processInput()
{
	return !Button();
}

void Video::swapBuffers()
{
}
