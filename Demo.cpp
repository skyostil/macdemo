/**
 *  Mac Demo
 *  Copyright (C) 2009 by Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 */
#include "Demo.h"

Timeline::Timeline(EffectEntry* effects):
    m_effects(effects),
    m_firstEffect(effects),
    m_baseTime(0)
{
}

bool Timeline::run(int time)
{
    int t = m_baseTime;
    EffectEntry* f = m_effects;

    while (t + f->duration < time)
    {
        if (f->flags & EFFECT_FLAG_DYNAMIC)
        {
            break;
        }

        t += f->duration;
        m_baseTime += f->duration;
        f++;

        if (!f->duration)
        {
            return 0;
        }
    }

    if (f->flags & EFFECT_FLAG_DYNAMIC)
    {
        int dt = time - t;
        if (f->effect(dt, dt))
        {
            m_baseTime += dt;
            f++;
        }
    }
    else
    {
        f->effect(time - t, f->duration);
    }

    m_effects = f;
    return 1;
}

void Timeline::reset()
{
    m_effects = m_firstEffect;
    m_baseTime = 0;
}

Effect::Effect(Effect::Func f):
    m_func(f)
{
}

int Effect::operator()(int time, int duration)
{
    return m_func(time, duration);
}