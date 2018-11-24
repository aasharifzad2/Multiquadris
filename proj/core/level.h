#ifndef _level_h_
#define _level_h_


#include <vector>
#include "effect.h"

class FallingBlock;

class Level
{
    protected:
    int number;
    std::vector<Effect> activeEffects;
    Level(int);
    
    public:
    virtual FallingBlock getBlock() = 0;
    bool hasEffect(Effect);
};


#endif
