#ifndef _placed_block_h_
#define _placed_block_h_


#include "block.h"
class Cell;

class PlacedBlock : public Block
{
    public:
    ~PlacedBlock() override;
    int numCells() const;
    void cellCleared(const Cell *);
};


#endif
