
#include "textDisplay.h"


TextDisplay::TextDisplay(std::ostream &out) : out(out) {}

void TextDisplay::accept(const Game *game)
{
    
}

void TextDisplay::accept(const Player *player)
{
    
}

void TextDisplay::accept(const Board *board)
{
    for (auto row : board->getRows())
    {
        accept(row);
        out << std::endl;
    }
}

void TextDisplay::accept(const Row *row)
{
    for (auto cell : row->getCells())
    {
        accept(cell);
    }
}

void TextDisplay::accept(const Cell *cell)
{
    out << cell->getSymbol();
}
