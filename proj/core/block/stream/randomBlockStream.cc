
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

std::unique_ptr<FallingBlock> RandomBlockStream::getBlock()
{
    BlockShape blockType = blockList[rand() % blockList.size()];
    switch (blockType)
    {
        case IShape:
            return std::unique_ptr<FallingBlock>(new IBlock());
        case JShape:
            return std::unique_ptr<FallingBlock>(new JBlock());
        case LShape:
            return std::unique_ptr<FallingBlock>(new LBlock());
        case OShape:
            return std::unique_ptr<FallingBlock>(new OBlock());
        case SShape:
            return std::unique_ptr<FallingBlock>(new SBlock());
        case ZShape:
            return std::unique_ptr<FallingBlock>(new ZBlock());
        case TShape:
            return std::unique_ptr<FallingBlock>(new TBlock());
    }
}
