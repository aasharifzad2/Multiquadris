
#include "sBlock.h"
#include "../../cell.h"


SBlock::~SBlock() {}

SBlock::SBlock() : Block(Colour::Green)
{
    for (int i = 1; i < 3; i++)
    {
        cells.emplace_back(std::make_shared<Cell>(
            initialY, initialX + i, this)
        );
    }
    
    for (int i = 0; i < 2; i++)
    {
        cells.emplace_back(std::make_shared<Cell>(
            initialY - 1, initialX + i, this)
        );
    }
}
