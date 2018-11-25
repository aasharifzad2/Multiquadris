#ifndef _i_block_h_
#define _i_block_h_


#include "../block.h"

class IBlock : public Block
{
    public:
    ~IBlock() override;
    IBlock();
};


#endif
