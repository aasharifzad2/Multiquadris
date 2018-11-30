
#include "graphicDisplay.h"
#include "../excp/not_implemented.h"


void GraphicDisplay::accept(const Game *game) const
{
    throw not_implemented();
}

void GraphicDisplay::accept(const Player *player) const
{
    throw not_implemented();
}

void GraphicDisplay::accept(const Board *board) const
{
    throw not_implemented();
}

void GraphicDisplay::accept(const Cell *cell) const
{
    throw not_implemented();
}
