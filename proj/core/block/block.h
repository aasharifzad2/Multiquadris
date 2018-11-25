#ifndef _block_h_
#define _block_h_


#include <vector>
#include <memory>
#include "../colour.h"

class Cell;

class Block
{
    protected:
    std::vector<std::shared_ptr<Cell>> cells;
    Colour colour;
    int levelGenerated;
    
    public:
    Colour getColour() const;
    std::vector<std::pair<int, int>> getCellCoords() const;
    std::vector<std::shared_ptr<Cell>> getCells() const;
    virtual ~Block() = 0;
};


#endif
