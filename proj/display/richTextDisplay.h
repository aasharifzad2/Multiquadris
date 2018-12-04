#ifndef _rich_text_display_h_
#define _rich_text_display_h_


#include <iostream>
#include <string>
#include "textDisplay.h"
#include "../core/colour.h"
class Cell;


class RichTextDisplay : public TextDisplay
{
public:
    RichTextDisplay(std::ostream & = std::cout);

private:
    void printPlacedCell(const Cell *) const override;
    void printFallingCell(const Cell *, bool curTurn = false) const override;
    void printBlindCell() const override;
    void stylize(std::string &, Colour, bool = false, bool = false) const;
};


#endif

