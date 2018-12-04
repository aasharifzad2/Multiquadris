
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
    return Block::makeBlock(blockList[rand() % blockList.size()]);
}
