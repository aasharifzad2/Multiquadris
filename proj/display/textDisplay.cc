
#include "textDisplay.h"
#include <iomanip>
#include "../core/game.h"
#include "../excp/not_implemented.h"

// Mark: - Static


// Mark: - Constructors & Destructor
TextDisplay::TextDisplay(std::ostream &out) :
    out(out)
{}


// Mark: - Visitors
void TextDisplay::accept(const Game *game) const
{
    auto players = game->getPlayers();
    accept(players[0]);
}

void TextDisplay::accept(const Player *player) const
{
    std::string horizontalBorder;
    for (int i = 0; i < player->getBoard()->getNumCols(); i++)
    {
        horizontalBorder += '-';
    }
    
    out << "Score: " << player->getScore() << std::endl;
    out << "High Score: " << player->getHighScore() << std::endl;
    out << "Level:  " << player->getCurLevel() << std::endl;
    
    out << horizontalBorder << std::endl;
    
    for (auto row : player->getBoard()->getCells())
    {
        printRow
        (
            row,
            player->hasEffect(Effect::Blind),
            player->getFallingBlock()
        );
        
        out << std::endl;
    }
    out << horizontalBorder << std::endl;
}

void TextDisplay::accept(const Board *board) const
{
    for (auto row : board->getCells())
    {
        for (auto cell : row)
        {
            printPlacedCell(cell);
        }
        out << std::endl;
    }
}

void TextDisplay::accept(const Cell *cell) const
{
    printPlacedCell(cell);
}


// MARK: - Private Functions
void TextDisplay::printRow
(
    std::vector<Cell *> row,
    bool playerIsBlind,
    Block *fallingBlock
)
const
{
    for (auto cell : row)
    {
        Cell *fallingCell = fallingBlock->getMatchingCell(cell);
        if (playerIsBlind && cell->isInBlindZone())
        {
            printBlindCell();
        }
        else if (fallingCell)
        {
            printFallingCell(fallingCell);
        }
        else
        {
            printPlacedCell(cell);
        }
    }
}

void TextDisplay::printPlacedCell(const Cell *cell) const
{
    out << cell->getSymbol();
}

void TextDisplay::printFallingCell(const Cell *cell) const
{
    out << cell->getSymbol();
}

void TextDisplay::printBlindCell() const
{
    out << '?';
}
