#ifndef _random_block_stream_h_
#define _random_block_stream_h_


#include <memory>
#include <map>
#include "blockStream.h"
#include "../blockShape.h"
class FallingBlock;

class RandomBlockStream : public BlockStream
{
    std::map<int, BlockShape> blockList{};
    
    public:
    RandomBlockStream(std::map<BlockShape, int>);
    std::unique_ptr<FallingBlock> getBlock() override;
};


#endif
