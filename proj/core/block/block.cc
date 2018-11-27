
#include "block.h"
#include <vector>
#include <memory>
#include "../cell.h"
#include "../../excp/not_implemented.h"

int Block::initialX = 0;
int Block::initialY = 1;

// Destructor
Block::~Block() {}

// Constructor
Block::Block(char symbol, Colour colour) :
    symbol(symbol), colour(colour)
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

// Getter : symbol
char Block::getSymbol() const
{
    return symbol;
}

// Getter : colour
Colour Block::getColour() const
{
    return colour;
}

// Getter : a cell
std::shared_ptr<Cell> Block::getCell(int index) const
{
    return cells.at(index);
}

// Getter : cells
std::vector<std::shared_ptr<Cell>> Block::getCells() const{
    return cells;
}

// Observer Pattern : called by subject (Cell) when the cell is cleared
//   Tells the block to remove the cleared cell from it's list
void Block::cellCleared(const Cell * cellptr)
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

// Movement: right
void Block::moveRight()
{
    for (std::shared_ptr<Cell> c : cells)
    {
        c->setCol(c->getCol() + 1);
    }
}

// Movement: left
void Block::moveLeft()
{
    for (std::shared_ptr<Cell> c : cells)
    {
        c->setCol(c->getCol() - 1);
    }
}

// Movement: up
void Block::moveUp()
{
    for (std::shared_ptr<Cell> c : cells)
    {
        c->setRow(c->getRow() - 1);
    }
}

// Movement: down
void Block::moveDown()
{
    for (std::shared_ptr<Cell> c : cells)
    {
        c->setRow(c->getRow() + 1);
    }
}

// Movement: roate clockwise
void Block::rotateCW()
{
    int leftMostX, rightMostX, highestY, lowestY;
    
    getBounds(leftMostX, rightMostX, highestY, lowestY);
    
    for (std::shared_ptr<Cell> c : cells)
    {
        c->setCol((leftMostX + (lowestY - c->getRow())));
        c->setRow(lowestY - (rightMostX - c->getCol()));
    }
}

// Movement: rotate counter clockwise
void Block::rotateCCW()
{
    int leftMostX, rightMostX, highestY, lowestY;
    
    getBounds(leftMostX, rightMostX, highestY, lowestY);
    
    int width = leftMostX - rightMostX;
    
    for (std::shared_ptr<Cell> c : cells)
    {
        c->setCol(leftMostX + c->getRow() - highestY);
        c->setRow(lowestY - (width - (rightMostX - c->getCol()) - 1));
    }
}

void Block::getBounds(int &leftMostX, int &rightMostX, int &highestY, int &lowestY)
{
    leftMostX = INT_MAX;
    rightMostX = INT_MIN;
    highestY = INT_MAX;
    lowestY = INT_MIN;
    
    for (std::shared_ptr<Cell> c : cells)
    {
        int row = c->getRow();
        int col = c->getCol();
        
        leftMostX = std::min(leftMostX, col);
        rightMostX = std::max(rightMostX, col);
        highestY = std::min(highestY, row);
        lowestY = std::min(highestY, row);
    }
}
