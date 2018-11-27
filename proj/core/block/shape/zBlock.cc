
#include "zBlock.h"
#include "../../cell.h"


ZBlock::~ZBlock() {}

ZBlock::ZBlock() : Block('Z', Colour::Red)
{
    cells =
    {
        std::make_shared<Cell>(initialY - 1, initialX, this),
        std::make_shared<Cell>(initialY - 1, initialX + 1, this),
        std::make_shared<Cell>(initialY, initialX + 1, this),
        std::make_shared<Cell>(initialY, initialX + 2, this)
    };
}
