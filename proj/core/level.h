#ifndef _level_h_
#define _level_h_


#include <vector>
#include <memory>
#include "effect.h"
#include "block/stream/blockStream.h"

class Block;

const int
    LEVEL_MIN = 0,
    LEVEL_MAX = 4;

class Level
{
    int number;
    std::unique_ptr<BlockStream> blockstream;
    std::vector<Effect> activeEffects;

public:
    static Level initLevel(int lvl, std::ifstream &levelInput);
    static std::vector<Level> initLevels(std::ifstream &);
    
    Level(std::unique_ptr<BlockStream>, std::vector<Effect>);
    
    std::shared_ptr<Block> getBlock() const;
    bool hasEffect(Effect) const;
};


#endif
