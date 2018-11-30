
#include "lBlock.h"
#include "../../cell.h"


LBlock::~LBlock() {}

LBlock::LBlock() : Block('L', Colour::Orange)
{
    cells =
        {
            std::make_shared<Cell>(initialY, initialX, this),
            std::make_shared<Cell>(initialY, initialX + 1, this),
            std::make_shared<Cell>(initialY, initialX + 2, this),
            std::make_shared<Cell>(initialY - 1, initialX + 2, this)
        };
}
