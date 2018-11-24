#ifndef _block_stream_h_
#define _block_stream_h_


#include <memory>
#include "../fallingBlock.h"
#include "../shape/iBlock.h"
#include "../shape/jBlock.h"
#include "../shape/lBlock.h"
#include "../shape/oBlock.h"
#include "../shape/sBlock.h"
#include "../shape/zBlock.h"
#include "../shape/tBlock.h"

class FallingBlock;

class BlockStream
{
    public:
    virtual std::unique_ptr<FallingBlock> getBlock() = 0;
};


#endif
