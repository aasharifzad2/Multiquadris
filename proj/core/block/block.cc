
#include "block.h"
#include <vector>
#include <memory>
#include "../cell.h"
#include "../../excp/not_implemented.h"


// MARK: - Static
int Block::initialX = 0;
int Block::initialY = 1;


// MARK: - Constructors & Destructor
Block::Block(char symbol, Colour colour) :
    symbol(symbol),
    colour(colour)
{}

Block::~Block() {}


// MARK: - Setters
void Block::setLevelGenerated(int lvl) { levelGenerated = lvl; }


// MARK: - Getters
int Block::getLevelGenerated() const { return levelGenerated; }

char Block::getSymbol() const { return symbol; }

Colour Block::getColour() const { return colour; }

int Block::getNumCells() const
{
    return (int)cells.size();
}

std::shared_ptr<Cell> Block::getCell(int index) const
{
    return cells.at(index);
}

std::vector<std::shared_ptr<Cell>> Block::getCells() const
{
    return cells;
}


// MARK: - Public Functions
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

// MARK: Movement Functions
void Block::moveRight()
{
    for (std::shared_ptr<Cell> c : cells)
    {
        c->setCol(c->getCol() + 1);
    }
}

void Block::moveLeft()
{
    for (std::shared_ptr<Cell> c : cells)
    {
        c->setCol(c->getCol() - 1);
    }
}

void Block::moveUp()
{
    for (std::shared_ptr<Cell> c : cells)
    {
        c->setRow(c->getRow() - 1);
    }
}

void Block::moveDown()
{
    for (std::shared_ptr<Cell> c : cells)
    {
        c->setRow(c->getRow() + 1);
    }
}

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


// MARK: - Private Functions
void Block::getBounds
(
    int &leftmostX,
    int &rightmostX,
    int &highestY,
    int &lowestY
)
{
    leftmostX = INT_MAX;
    rightmostX = INT_MIN;
    highestY = INT_MAX;
    lowestY = INT_MIN;
    
    for (std::shared_ptr<Cell> c : cells)
    {
        int row = c->getRow();
        int col = c->getCol();
        
        leftmostX = std::min(leftmostX, col);
        rightmostX = std::max(rightmostX, col);
        highestY = std::min(highestY, row);
        lowestY = std::min(highestY, row);
    }
}
