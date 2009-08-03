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

    if (f->flags & EFFECT_FLAG_DYNAMIC_DONE)
    {
        m_baseTime = time;
        m_effects++;
        return 1;
    }

    while (t + f->duration < time)
    {
        if (f->flags & EFFECT_FLAG_DYNAMIC)
        {
            break;
        }

        if (!f->duration)
        {
            return 0;
        }

        t += f->duration;
        m_baseTime += f->duration;
        f++;
    }

    if (f->flags & EFFECT_FLAG_DYNAMIC)
    {
        int dt = time - t;
        if (f->effect(dt, dt))
        {
            if (!(f->flags & EFFECT_FLAG_INFINITESIMAL))
            {
                f->flags |= EFFECT_FLAG_DYNAMIC_DONE;
            }
            else
            {
                f++;
            }
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
