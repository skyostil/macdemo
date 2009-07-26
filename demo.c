/**
 *  Mac Demo
 *  Copyright (C) 2009 by Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 */
#include "demo.h"

int schedule(const Effect* effects, int time)
{
    int t = 0;

    while (t + effects->duration < time)
    {
        t += effects->duration;
        effects++;
        if (!effects->func)
        {
            return 0;
        }
    }

    effects->func(time - t, effects->duration);

    return 1;
}
