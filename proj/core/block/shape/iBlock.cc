
#include "iBlock.h"
#include "../../cell.h"


IBlock::~IBlock() {}

IBlock::IBlock() : Block('I', Colour::Cyan)
{
    cells =
        {
            std::make_shared<Cell>(initialY, initialX, this),
            std::make_shared<Cell>(initialY, initialX + 1, this),
            std::make_shared<Cell>(initialY, initialX + 2, this),
            std::make_shared<Cell>(initialY, initialX + 3, this)
        };
}
