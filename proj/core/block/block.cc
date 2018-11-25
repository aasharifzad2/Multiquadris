
#include "block.h"
#include <vector>
#include <memory>
#include "../cell.h"
#include "../../excp/not_implemented.h"


// Destructor
Block::~Block() {}

// Constructor
Block::Block(Colour colour) :
    colour(colour)
{}

// Setter : levelGenerated
void Block::setLevelGenerated(int lvl)
{
    levelGenerated = lvl;
}

// Getter : number of cells
int Block::numCells() const
{
    return (int)cells.size();
}

// Getter : colour
Colour Block::getColour() const
{
    return colour;
}

// Getter : a cell
Cell *Block::getCell(int index) const
{
    return cells.at(index).get();
}

// Getter : cells
std::vector<Cell *> Block::getCells() const
{
    std::vector<Cell *> cellptrs;
    for (auto cell : cells)
    {
        cellptrs.emplace_back(cell.get());
    }
    
    return cellptrs;
}

// Observer Pattern : called by subject (Cell) when the cell is cleared
//   Tells the block to remove the cleared cell from it's list
void Block::cellCleared(Cell const * const cellptr)
{
    for (auto itr = cells.begin(); itr != cells.end(); )
    {
        if (itr->get() == cellptr)
        {
            itr = cells.erase(itr);
        }
        else
        {
            ++itr;
        }
    }
}

// Movement : right
void Block::moveRight()
{
    throw not_implemented();
}

// Movement : left
void Block::moveLeft()
{
    throw not_implemented();
}

// Movement : up
void Block::moveUp()
{
    throw not_implemented();
}

// Movement : down
void Block::moveDown()
{
    throw not_implemented();
}

// Movement : clockwise rotation
void Block::rotateCW()
{
    throw not_implemented();
}

// Movement : counter clockwise rotation
void Block::rotateCCW()
{
    throw not_implemented();
}
