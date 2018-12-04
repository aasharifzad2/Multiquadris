
#include "block.h"
#include <vector>
#include <memory>
#include <climits>
#include "../cell.h"
#include "../../excp/not_implemented.h"
#include "../../excp/invalid_block_char.h"
#include "shape/iBlock.h"
#include "shape/jBlock.h"
#include "shape/lBlock.h"
#include "shape/oBlock.h"
#include "shape/sBlock.h"
#include "shape/zBlock.h"
#include "shape/tBlock.h"


// MARK: - Static
int Block::initialX = 0;
int Block::initialY = 3;

std::shared_ptr<Block> Block::makeBlock(BlockShape shape)
{
    switch (shape)
    {
        case IShape:
            return std::make_shared<IBlock>();
            break;
        case JShape:
            return std::make_shared<JBlock>();
            break;
        case LShape:
            return std::make_shared<LBlock>();
            break;
        case OShape:
            return std::make_shared<OBlock>();
            break;
        case SShape:
            return std::make_shared<SBlock>();
            break;
        case ZShape:
            return std::make_shared<ZBlock>();
            break;
        case TShape:
            return std::make_shared<TBlock>();
            break;
    }
}

std::shared_ptr<Block> Block::makeBlock(char c)
{
    switch (std::toupper(c))
    {
        case 'I':
            return std::make_shared<IBlock>();
            break;
        case 'J':
            return std::make_shared<JBlock>();
            break;
        case 'L':
            return std::make_shared<LBlock>();
            break;
        case 'O':
            return std::make_shared<OBlock>();
            break;
        case 'S':
            return std::make_shared<SBlock>();
            break;
        case 'Z':
            return std::make_shared<ZBlock>();
            break;
        case 'T':
            return std::make_shared<TBlock>();
            break;
        default:
            throw invalid_block_char(c);
    }
}



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

Cell *Block::getMatchingCell(const Cell *c) const
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

void Block::getBounds
(
    int &leftest,
    int &rightest,
    int &highest,
    int &lowest
)
const
{
    leftest = INT_MAX;
    rightest = INT_MIN;
    highest = INT_MAX;
    lowest = INT_MIN;
    
    for (std::shared_ptr<Cell> c : cells)
    {
        int row = c->getRow();
        int col = c->getCol();
        
        leftest = std::min(leftest, col);
        rightest = std::max(rightest, col);
        highest = std::min(highest, row);
        lowest = std::max(lowest, row);
    }
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
    int leftest, rightest, highest, lowest;
    
    getBounds(leftest, rightest, highest, lowest);
    
    for (std::shared_ptr<Cell> c : cells)
    {
        int col = c->getCol();
        int row = c->getRow();
        c->setCol(leftest + lowest - row);
        c->setRow(lowest - rightest + col);
    }
    
    checkHeavyLevel();
}

void Block::rotateCCW()
{
    int leftest, rightest, highest, lowest;
    
    getBounds(leftest, rightest, highest, lowest);
    
    for (std::shared_ptr<Cell> c : cells)
    {
        int col = c->getCol();
        int row = c->getRow();
        c->setCol(leftest + row - highest);
        c->setRow(lowest - col + leftest);
    }
    
    checkHeavyLevel();
}


// MARK: - Private Functions
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
