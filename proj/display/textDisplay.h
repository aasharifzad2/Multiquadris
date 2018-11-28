#ifndef _text_display_h_
#define _text_display_h_


#include "display.h"
#include <ostream>

class TextDisplay : public Display
{
    std::ostream &out;
    
    public:
    TextDisplay(std::ostream &);
    
    void accept(const Game *) override;
    void accept(const Player *) override;
    void accept(const Board *) override;
    void accept(const Cell *) override;
};


#endif

