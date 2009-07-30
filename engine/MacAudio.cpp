/**
 * Copyright (C) 2009 Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 */
#include "Audio.h"
#include "Config.h"

extern "C"
{
#ifndef __SOUND__
#include <Sound.h>
#include <SoundInput.h>
#endif

#ifndef __GESTALT__
#include <GestaltEqu.h>
#endif
}

static AudioRenderer*        renderer = NULL;
static SndChannelPtr         soundChannel = NULL;
static SndDoubleBufferHeader doubleHeader;
static SampleChunk*          currentChunk = NULL;
static int                   currentMixFreq, bufferSize, bits;
static bool                  stereo;
static SampleFormat*         sampleFormat;

static pascal void soundCallback(SndChannelPtr soundChannel, SndDoubleBufferPtr doubleBuffer)
{
#pragma unused(soundChannel)
#if GENERATING68K
	long oldA5=SetA5(doubleBuffer->dbUserInfo[0]);
#endif

	currentChunk->data = (Sample8*)&doubleBuffer->dbSoundData[0];
	renderer->render(currentChunk);
#if 0
	if (doubleHeader.dbhNumChannels == 2) written>>=1;
	if (doubleHeader.dbhSampleSize == 16) written>>=1
#endif   
	doubleBuffer->dbNumFrames = currentChunk->length;
	doubleBuffer->dbFlags |= dbBufferReady;

#if GENERATING68K
	SetA5(oldA5);
#endif
}

Audio::Audio(int bits_, int mixFreq_, bool stereo_, int bufferSize_)
{
	OSErr err,iErr;
	int i;
	SndDoubleBufferPtr doubleBuffer;
	long rate, maxrate, maxbits;
	long gestaltAnswer;
	NumVersion nVers;
	Boolean Stereo, StereoMixing, Audio16;
	Boolean NewSoundManager, NewSoundManager31;

	NewSoundManager31 = NewSoundManager = false;
	stereo = stereo_;
	currentMixFreq = mixFreq_;
	bits = bits_;
	bufferSize = bufferSize_;

	nVers = SndSoundManagerVersion();
	if (nVers.majorRev>=3)
	{
		NewSoundManager=true;
		if (nVers.minorAndBugRev>=0x10)
			NewSoundManager31=true;
	} else
	  if (nVers.majorRev<2)
		return; /* failure, need SoundManager 2.0+ for SndPlayDoubleBuffer */

	iErr = Gestalt(gestaltSoundAttr, &gestaltAnswer);
	if (iErr==noErr)
	{
		Stereo = (gestaltAnswer & (1<<gestaltStereoCapability)) != 0;
		StereoMixing = (gestaltAnswer & (1<<gestaltStereoMixing)) != 0;
		Audio16= (gestaltAnswer & (1<<gestalt16BitSoundIO)) != 0;
	} else {
		/* failure, couldn't get any sound info at all ? */
		Stereo = StereoMixing = Audio16 = false;
	}

#if !GENERATING68K || !GENERATINGCFM
/*
	if (NewSoundManager31) {
		iErr=GetSoundOutputInfo(0L,siSampleRate,(void*)&maxrate);
		if (iErr==noErr)
			iErr=GetSoundOutputInfo(0L,siSampleSize,(void*)&maxbits);
	}

	if (iErr!=noErr) {
*/
#endif
		maxrate=rate22khz;

		if (NewSoundManager && Audio16)
			maxbits=16;
		else
			maxbits=8;
#if !GENERATING68K || !GENERATINGCFM
//	}
#endif

	switch (currentMixFreq) {
//		case 48000:rate=rate48khz;break;
		case 44100:rate=rate44khz;break;
		case 22254:rate=rate22khz;break;
//		case 22050:rate=rate22050hz;break;
		case 11127:rate=rate11khz;break;
//		case 11025:rate=rate11025hz;break;
//		default:   rate=0;break;
		default:   rate=rate22khz;break;
	}

	if (maxbits < 16)
		bits = 8;

	if (!Stereo || !StereoMixing)
		stereo = false;

	if (rate > maxrate)
		rate = maxrate;
		
	if (currentMixFreq > (maxrate >> 16))
		currentMixFreq = maxrate >> 16;

	err = SndNewChannel(&soundChannel, sampledSynth,
	                   stereo ? initStereo : initMono, NULL);
	                   
	if (err!=noErr)
	{
		return;
	}

	doubleHeader.dbhCompressionID = 0;
	doubleHeader.dbhPacketSize    = 0;
	doubleHeader.dbhSampleRate    = rate;
	doubleHeader.dbhSampleSize    = bits;
	doubleHeader.dbhNumChannels   = stereo ? 2 : 1;
	doubleHeader.dbhDoubleBack    = NewSndDoubleBackProc(&soundCallback);
    
	for(i=0;i<2;i++)
	{
		doubleBuffer = (SndDoubleBufferPtr)NewPtrClear(sizeof(SndDoubleBuffer) + 
		                                               bufferSize);
		if (!doubleBuffer)
		{
			return;
		}

		doubleBuffer->dbNumFrames = 0;
		doubleBuffer->dbFlags = 0;
		doubleBuffer->dbUserInfo[0] = SetCurrentA5();
		doubleBuffer->dbUserInfo[1] = 0;

		doubleHeader.dbhBufferPtr[i] = doubleBuffer;
	}
	
	
	sampleFormat = new SampleFormat(bits, stereo ? 2 : 1);
	currentChunk = new SampleChunk(sampleFormat, NULL, 
	                               bufferSize / sampleFormat->bytesPerSample, currentMixFreq);
}

Audio::~Audio(void)
{
	int i;
	
	stop();
    
	SndDisposeChannel(soundChannel,true);
	soundChannel = NULL;

	DisposeRoutineDescriptor((UniversalProcPtr)doubleHeader.dbhDoubleBack);
	doubleHeader.dbhDoubleBack=NULL;

	for(i=0;i<doubleHeader.dbhNumChannels;i++)
	{
		DisposePtr((Ptr)doubleHeader.dbhBufferPtr[i]);
		doubleHeader.dbhBufferPtr[i]=NULL;
	}
	delete sampleFormat;
	delete currentChunk;
	currentChunk = NULL;
}

void Audio::start(AudioRenderer* renderer_)
{
	renderer = renderer_;

	soundCallback(soundChannel,doubleHeader.dbhBufferPtr[0]);
	soundCallback(soundChannel,doubleHeader.dbhBufferPtr[1]);

	SndPlayDoubleBuffer(soundChannel,&doubleHeader);
}

void Audio::stop(void)
{
	SndCommand cmd;

	cmd.cmd=quietCmd;
	cmd.param1=0;
	cmd.param2=0;
	SndDoImmediate(soundChannel,&cmd);
    
	cmd.cmd=flushCmd;
	cmd.param1=0;
	cmd.param2=0;
	SndDoImmediate(soundChannel,&cmd);
}

int Audio::mixFreq()
{
    return currentMixFreq;
}
