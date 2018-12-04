
#include "sBlock.h"
#include "../../cell.h"


SBlock::~SBlock() {}

SBlock::SBlock() : Block('S', Colour::Green)
{
    cells =
    {
        std::make_shared<Cell>(initialY, initialX, this),
        std::make_shared<Cell>(initialY, initialX + 1, this),
        std::make_shared<Cell>(initialY - 1, initialX + 1, this),
        std::make_shared<Cell>(initialY - 1, initialX + 2, this)
    };
}
