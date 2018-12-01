#ifndef _text_display_h_
#define _text_display_h_


#include "display.h"
#include <iostream>

class TextDisplay : public Display
{
protected:
    std::ostream &out;
    
public:
    TextDisplay(std::ostream & = std::cout);
    
    // Visitor Pattern : Visit different classes
    void accept(const Game *) const override;
    void accept(const Player *) const override;
    void accept(const Board *) const override;
    void accept(const Cell *) const override;
    

protected:
    // TODO: should printRow be private?
    void printRow(std::vector<Cell *>, bool, Block *) const;
    virtual void printPlacedCell(const Cell *) const;
    virtual void printFallingCell(const Cell *) const;
    virtual void printBlindCell() const;
};


#endif

