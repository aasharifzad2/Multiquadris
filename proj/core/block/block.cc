
#include "block.h"
#include <vector>
#include <memory>
#include "../cell.h"


Block::~Block()
{
    
}

Colour Block::getColour() const
{
    return colour;
}

std::vector<std::shared_ptr<Cell>> Block::getCells() const
{
    return cells;
}

std::vector<std::pair<int, int>> Block::getCellCoords() const
{
    std::vector<std::pair<int, int>> coords;
    for (std::shared_ptr<Cell> c : cells)
    {
        coords.emplace_back(std::pair<int, int>{c->getRow(), c->getCol()});
    }
    return coords;
}
