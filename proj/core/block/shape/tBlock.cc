
#include "tBlock.h"
#include "../../cell.h"


TBlock::~TBlock() {}

TBlock::TBlock() : Block('T', Colour::Magenta)
{
    cells =
    {
        std::make_shared<Cell>(initialY - 1, initialX, this),
        std::make_shared<Cell>(initialY - 1, initialX + 1, this),
        std::make_shared<Cell>(initialY - 1, initialX + 2, this),
        std::make_shared<Cell>(initialY, initialX + 1, this)
    };
}
