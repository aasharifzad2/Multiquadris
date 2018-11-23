#ifndef _placed_block_h_
#define _placed_block_h_


#include "block.h"

class PlacedBlock : public Block
{
    public:
    ~PlacedBlock() override;
    void cellCleared();
};


#endif
