#ifndef _graphic_display_h_
#define _graphic_display_h_


#include "display.h"
class XWindow;

class GraphicDisplay : public Display
{
    public:
    void accept(const Game *) override;
    void accept(const Player *) override;
    void accept(const Board *) override;
    void accept(const Cell *) override;
};


#endif
