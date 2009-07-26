/**
 *  Mac Demo
 *  Copyright (C) 2009 by Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 */
#ifndef DEMO_H
#define DEMO_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*EffectFunction)(int time, int duration);

typedef struct Effect_t
{
    EffectFunction func;
    int duration;
} Effect;

int schedule(const Effect* effects, int time);

#ifdef __cplusplus
}
#endif

#endif
