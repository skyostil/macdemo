/**
 *  Mac Demo
 *  Copyright (C) 2009 by Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 */
#ifndef DEMO_H
#define DEMO_H

#include "Config.h"

typedef int (*Effect)(int time, int duration);

enum EffectFlags
{
    EFFECT_FLAG_DYNAMIC       = 0x1,
    EFFECT_FLAG_INFINITESIMAL = 0x2,
    EFFECT_FLAG_DYNAMIC_DONE  = 0x4
};

typedef struct EffectEntry_t
{
    Effect effect;
    int duration;
    int flags;
} EffectEntry;

class Timeline
{
public:
    Timeline(EffectEntry* effects);
    bool run(int time);
    void reset();
private:
    EffectEntry* m_effects;
    EffectEntry* m_firstEffect;
    int m_baseTime;
};

#endif
