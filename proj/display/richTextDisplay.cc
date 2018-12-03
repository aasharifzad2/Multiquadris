
#include "richTextDisplay.h"
#include <string>
#include "../core/cell.h"
#include "../core/colour.h"

// MARK: - Constructors & Destructor
RichTextDisplay::RichTextDisplay(std::ostream &out) :
    TextDisplay(out)
{}

// MARK: - Setters


// MARK: - Getters


// MARK: - Public Functions


// MARK: - Private Functions
void RichTextDisplay::printPlacedCell(const Cell *cell) const
{
    std::string output(1, cell->getSymbol());
    stylize(output, cell->getColour(), true);
    out << output;
}

void RichTextDisplay::printFallingCell(const Cell *cell, bool curTurn) const
{
    std::string output(1, cell->getSymbol());
    stylize(output, cell->getColour(), false, curTurn);
    out << output;
}

void RichTextDisplay::printBlindCell() const
{
    std::string output = "?";
    stylize(output, Colour::Black);
    out << output;
}

void RichTextDisplay::stylize
(
    std::string &str,
    Colour colour,
    bool bold,
    bool flashing
)
const
{
    std::string styled = "\033[";
    if (bold) styled += "1;";
    if (flashing) styled += "5;";
        
    switch (colour)
    {
        case Cyan:
            styled += "30;106";
            break;
        case Blue:
            styled += "37;104";
            break;
        case Yellow:
            styled += "30;103";
            break;
        case Orange:
            styled += "37;41";
            break;
        case Green:
            styled += "30;102";
            break;
        case Magenta:
            styled += "30;105";
            break;
        case Red:
            styled += "37;101";
            break;
        case Black:
            styled += "37;40";
            break;
        case Brown:
            styled += "30;43";
            break;
        case White:
            styled += "30;107";
            break;
        case DarkGreen:
            styled += "30;42";
            break;
    }
    
    styled += "m" + str + "\033[0m";
    
    str = styled;
}
