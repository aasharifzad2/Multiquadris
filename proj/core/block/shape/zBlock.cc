
#include "zBlock.h"
#include "../../cell.h"


ZBlock::~ZBlock() {}

ZBlock::ZBlock() : Block(Colour::Red)
{
    for (int i = 0; i < 2; i++)
    {
        cells.emplace_back(std::make_shared<Cell>(
            initialY, initialX + i, this)
        );
    }
    
    for (int i = 1; i < 3; i++)
    {
        cells.emplace_back(std::make_shared<Cell>(
            initialY - 1, initialX + i, this)
        );
    }
}
