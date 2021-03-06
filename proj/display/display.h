#ifndef _display_h_
#define _display_h_


#include "../core/player.h"
#include "../core/board.h"
#include "../core/cell.h"

class Game;

class BQDisplay
{
public:
    virtual void accept(const Game *) = 0;
    virtual void accept(const Player *) const = 0;
    virtual void accept(const Board *) const = 0;
    virtual void accept(const Cell *) const = 0;
    
    virtual ~BQDisplay() {};
};


#endif
