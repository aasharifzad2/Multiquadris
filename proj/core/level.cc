
#include "level.h"


Level::Level(int level, BlockStream *bs) :
    number(level), blockstream(bs) {}

std::unique_ptr<Block> Level::getBlock() const
{
    return blockstream->getBlock();
}

bool Level::hasEffect(Effect e) const
{
    for (Effect curEffect : activeEffects)
    {
        if (e == curEffect) return true;
    }
    
    return false;
}
