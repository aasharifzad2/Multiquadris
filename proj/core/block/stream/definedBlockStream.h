#ifndef _defined_block_stream_h_
#define _defined_block_stream_h_


#include <memory>
#include <fstream>
#include "blockStream.h"

class Block;

class DefinedBlockStream : public BlockStream
{
    std::shared_ptr<std::ifstream> sequence;
    
public:
    DefinedBlockStream(std::shared_ptr<std::ifstream>);
    std::shared_ptr<Block> getBlock() override;
};


#endif
