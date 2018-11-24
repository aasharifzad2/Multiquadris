
#include "level.h"

Level::Level(int level) :
    number(level) {}

bool Level::hasEffect(Effect e)
{
    for (Effect curEffect : activeEffects)
    {
        if (e == curEffect) return true;
    }
    
    return false;
}
