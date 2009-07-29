/**
 *  Mac Demo
 *  Copyright (C) 2009 by Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 */
#ifndef DEMO_H
#define DEMO_H

class Effect
{
public:
    typedef int (*Func)(int time, int duration);

    Effect(Func f);
    virtual int operator()(int time, int duration);
private:
    Func m_func;
};

enum EffectFlags
{
    EFFECT_FLAG_DYNAMIC       = 0x1,
    EFFECT_FLAG_INFINITESIMAL = 0x2
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
