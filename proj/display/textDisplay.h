#ifndef _text_display_h_
#define _text_display_h_


#include "display.h"
#include <ostream>

class TextDisplay : public Display
{
public:
    TextDisplay(std::ostream &);
    
    // Visitor Pattern : Visit different classes
    void accept(const Game *) const override;
    void accept(const Player *) const override;
    void accept(const Board *) const override;
    void accept(const Cell *) const override;
    
private:
    std::ostream &out;
    void printRow(std::vector<Cell *>, bool, Block *) const;
};


#endif

