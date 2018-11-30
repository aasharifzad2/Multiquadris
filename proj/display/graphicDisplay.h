#ifndef _graphic_display_h_
#define _graphic_display_h_


#include "display.h"
class XWindow;

class GraphicDisplay : public Display
{
public:
    
    // Visitor Pattern : Visit different classes
    void accept(const Game *) const override;
    void accept(const Player *) const override;
    void accept(const Board *) const override;
    void accept(const Cell *) const override;
};


#endif
