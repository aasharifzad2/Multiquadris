
#include "oBlock.h"
#include "../../cell.h"


OBlock::~OBlock() {}

OBlock::OBlock() : Block('O', Colour::Yellow)
{
    cells =
        {
            std::make_shared<Cell>(initialY, initialX, this),
            std::make_shared<Cell>(initialY, initialX + 1, this),
            std::make_shared<Cell>(initialY - 1, initialX, this),
            std::make_shared<Cell>(initialY - 1, initialX + 1, this)
        };
}
