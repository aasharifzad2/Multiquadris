
#include "randomBlockStream.h"


RandomBlockStream::RandomBlockStream(std::map<BlockShape, int> frequencies)
{
    int index = 0;
    for (auto pair : frequencies)
    {
        while (pair.second > 0)
        {
            blockList[index] = pair.first;
            --pair.second;
            index++;
        }
    }
    
}

std::shared_ptr<Block> RandomBlockStream::getBlock()
{
    BlockShape blockType = blockList[rand() % blockList.size()];
    switch (blockType)
    {
        case IShape:
            return std::make_shared<IBlock>();
        case JShape:
            return std::make_shared<JBlock>();
        case LShape:
            return std::make_shared<LBlock>();
        case OShape:
            return std::make_shared<OBlock>();
        case SShape:
            return std::make_shared<SBlock>();
        case ZShape:
            return std::make_shared<ZBlock>();
        case TShape:
            return std::make_shared<TBlock>();
    }
}
