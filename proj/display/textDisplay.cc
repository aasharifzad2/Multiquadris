
#include "textDisplay.h"
#include <iomanip>
#include "../excp/not_implemented.h"

// Mark: - Static

// Mark: - Constructors & Destructor
TextDisplay::TextDisplay(std::ostream &out) : out(out) {}

// Mark: - Visitors
void TextDisplay::accept(const Game *game) const
{
    throw not_implemented();
}

void TextDisplay::accept(const Player *player) const
{
    out << "Score: " << player->getScore() << std::endl;
    out << "High Score: " << player->getHighScore() << std::endl;
    out << "Level:  " << player->getCurLevel() << std::endl;
    
    for (int i = 0; i < player->getBoard()->getNumCols(); i++)
    {
        out << '-';
    }
    out << std::endl;
    
    for (auto row : player->getBoard()->getCells())
    {
        printRow
        (
                 row,
                 player->hasEffect(Effect::Blind),
                 player->getFallingBlock())
        ;
        out << std::endl;
    }
}

void TextDisplay::accept(const Board *board) const
{
    for (auto row : board->getCells())
    {
        for (auto cell : row)
        {
            accept(cell);
        }
        out << std::endl;
    }
}

void TextDisplay::accept(const Cell *cell) const
{
    out << cell->getSymbol();
}

// MARK: - Private Functions
void TextDisplay::printRow(std::vector<Cell *> row, bool isBlind, Block *fallingBlock) const
{
    for (auto cell : row)
    {
        Cell *curCell;
        curCell = fallingBlock->getMatchingCell(cell);
        if (curCell)
        {
            accept(curCell);
        }
        else
        {
            accept(cell);
        }
    }
}
