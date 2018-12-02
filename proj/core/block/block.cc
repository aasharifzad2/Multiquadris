
#include "block.h"
#include <vector>
#include <memory>
#include "../cell.h"
#include "../../excp/not_implemented.h"


// MARK: - Static
int Block::initialX = 0;
int Block::initialY = 3;


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

Cell *Block::getMatchingCell(Cell *c)
{
    for (auto cell : cells)
    {
        if
        (
            cell->getRow() == c->getRow() &&
            cell->getCol() == c->getCol()
        )
        {
            return cell.get();
        }
    }
    return nullptr;
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
    
    checkHeavyLevel();
}

void Block::moveLeft()
{
    for (std::shared_ptr<Cell> c : cells)
    {
        c->setCol(c->getCol() - 1);
    }
    
    checkHeavyLevel();
}

void Block::moveUp()
{
    for (std::shared_ptr<Cell> c : cells)
    {
        c->setRow(c->getRow() - 1);
    }
    
    checkHeavyLevel();
}

void Block::moveDown()
{
    for (std::shared_ptr<Cell> c : cells)
    {
        c->setRow(c->getRow() + 1);
    }
    
    checkHeavyLevel();
}

void Block::rotateCW()
{
    int leftist, rightist, highest, lowest;
    
    getBounds(leftist, rightist, highest, lowest);
    
    for (std::shared_ptr<Cell> c : cells)
    {
        int col = c->getCol();
        int row = c->getRow();
        c->setCol(leftist + lowest - row);
        c->setRow(lowest - rightist + col);
    }
    
    checkHeavyLevel();
}

void Block::rotateCCW()
{
    int leftist, rightist, highest, lowest;
    
    getBounds(leftist, rightist, highest, lowest);
    
    for (std::shared_ptr<Cell> c : cells)
    {
        int col = c->getCol();
        int row = c->getRow();
        c->setCol(leftist + row - highest);
        c->setRow(lowest - col + leftist);
    }
    
    checkHeavyLevel();
}


// MARK: - Private Functions
void Block::getBounds
(
    int &leftist,
    int &rightest,
    int &highest,
    int &lowest
)
{
    leftist = INT_MAX;
    rightest = INT_MIN;
    highest = INT_MAX;
    lowest = INT_MIN;
    
    for (std::shared_ptr<Cell> c : cells)
    {
        int row = c->getRow();
        int col = c->getCol();
        
        leftist = std::min(leftist, col);
        rightest = std::max(rightest, col);
        highest = std::min(highest, row);
        lowest = std::max(lowest, row);
    }
}

void Block::checkHeavyLevel()
{
#ifndef DEBUG
    throw not_implemented();
#endif
}

void Block::checkHeavySpecial()
{
#ifndef DEBUG
    throw not_implemented();
#endif
}
