#ifndef _display_h_
#define _display_h_


#include "../core/game.h"
#include "../core/player.h"
#include "../core/board.h"
#include "../core/cell.h"

class Display
{
    public:
    virtual void accept(const Game *) = 0;
    virtual void accept(const Player *) = 0;
    virtual void accept(const Board *) = 0;
    virtual void accept(const Cell *) = 0;
};


#endif
