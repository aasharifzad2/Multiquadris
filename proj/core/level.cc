
#include "level.h"
#include "block/blockShape.h"
#include "block/stream/blockStream.h"
#include "block/stream/definedBlockStream.h"
#include "block/stream/randomBlockStream.h"


// STATIC FUNCTIONS
std::vector<Level> Level::initLevels(std::ifstream &level0input)
{
    std::vector<Level> levels;
    for (int i = LEVEL_MIN; i <= LEVEL_MAX; i++)
    {
        levels.emplace_back(initLevel(i, level0input));
    }
    
    return levels;
}


Level Level::initLevel(int lvl, std::ifstream &levelInput)
{
    std::unique_ptr<BlockStream> bs;
    std::vector<Effect> effects;

    if (lvl < LEVEL_MIN) lvl = LEVEL_MIN;
    if (lvl > LEVEL_MAX) lvl = LEVEL_MAX;
    
    switch (lvl) {
        case 0:
            bs = std::make_unique<DefinedBlockStream>(levelInput);
            break;
        case 1:
            bs = std::make_unique<RandomBlockStream>
            (
                std::map<BlockShape, int>
                {
                    {IShape, 2},
                    {JShape, 2},
                    {LShape, 2},
                    {OShape, 2},
                    {SShape, 1},
                    {ZShape, 1},
                    {TShape, 2},
                }
            );
            break;
        case 2:
            bs = std::make_unique<RandomBlockStream>
            (
                std::map<BlockShape, int>
                {
                    {IShape, 1},
                    {JShape, 1},
                    {LShape, 1},
                    {OShape, 1},
                    {SShape, 1},
                    {ZShape, 1},
                    {TShape, 1},
                }
             );
            break;
        case 4:
            effects.emplace_back(Wall);
        case 3:
            bs = std::make_unique<RandomBlockStream>
            (
                std::map<BlockShape, int>
                {
                    {IShape, 1},
                    {JShape, 1},
                    {LShape, 1},
                    {OShape, 1},
                    {SShape, 2},
                    {ZShape, 2},
                    {TShape, 1},
                }
            );
            effects.emplace_back(HeavyLevel);
            break;
        default:
            // TODO: throw exception here
            break;
    }
    
    return Level(lvl, std::move(bs), effects);
}
// STATIC FUNCTIONS (end)

Level::Level
(
    int number,
    std::unique_ptr<BlockStream> bs,
    std::vector<Effect> effects
) :
    number(number),
    blockstream(std::move(bs)),
    activeEffects(effects)
{}


std::shared_ptr<Block> Level::getBlock() const
{
    std::shared_ptr<Block> block = blockstream->getBlock();
    block->setLevelGenerated(number);
    return block;
}

bool Level::hasEffect(Effect e) const
{
    for (Effect curEffect : activeEffects)
    {
        if (e == curEffect) return true;
    }
    
    return false;
}
