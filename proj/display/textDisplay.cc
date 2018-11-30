
#include "textDisplay.h"
#include <iomanip>
#include "../excp/not_implemented.h"


TextDisplay::TextDisplay(std::ostream &out) : out(out) {}

void TextDisplay::accept(const Game *game)
{
    throw not_implemented();
}

void TextDisplay::accept(const Player *player)
{
    out << "Score: " << player->getScore() << std::endl;
    out << "High Score: " << player->getHighScore() << std::endl;
    // TODO: Output level
    for (int i = 0; i < player->getBoard()->getNumCols(); i++)
    {
        out << "-";
    }
    out << std::endl;
    accept(player->getBoard());
}

void TextDisplay::accept(const Board *board)
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

void TextDisplay::accept(const Cell *cell)
{
    out << cell->getSymbol();
}
