#ifndef _one_by_one_block_h_
#define _one_by_one_block_h_


#include "../block.h"

class OneByOneBlock : public Block
{
    public:
    ~OneByOneBlock() override;
    OneByOneBlock(int, int);
};


#endif
