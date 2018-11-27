#ifndef _block_stream_h_
#define _block_stream_h_


#include <memory>
#include "../shape/iBlock.h"
#include "../shape/jBlock.h"
#include "../shape/lBlock.h"
#include "../shape/oBlock.h"
#include "../shape/sBlock.h"
#include "../shape/zBlock.h"
#include "../shape/tBlock.h"

class Block;

class BlockStream
{
    public:
    virtual std::shared_ptr<Block> getBlock() = 0;
};


#endif
