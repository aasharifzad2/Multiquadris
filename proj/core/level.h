#ifndef _level_h_
#define _level_h_


#include <vector>
#include <memory>
#include "effect.h"
#include "block/stream/blockStream.h"

class FallingBlock;

class Level
{
    private:
    int number;
    BlockStream *blockstream;
    std::vector<Effect> activeEffects;
    
    
    public:
    Level(int, BlockStream *);
    std::unique_ptr<FallingBlock> getBlock() const;
    bool hasEffect(Effect) const;
};


#endif
