
#include "jBlock.h"
#include "../../cell.h"


JBlock::~JBlock() {}

JBlock::JBlock() : Block('J', Colour::Blue)
{
    cells =
        {
            std::make_shared<Cell>(initialY - 1, initialX, this),
            std::make_shared<Cell>(initialY, initialX, this),
            std::make_shared<Cell>(initialY, initialX + 1, this),
            std::make_shared<Cell>(initialY, initialX + 2, this)
        };
}
