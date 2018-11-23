#ifndef _block_h_
#define _block_h_


#include <vector>
#include "colour.h"

class Cell;

class Block
{
    protected:
    std::vector<Cell *> cells;
    Colour colour;
    int levelGenerated;
    
    public:
    virtual ~Block() = 0;
};


#endif
