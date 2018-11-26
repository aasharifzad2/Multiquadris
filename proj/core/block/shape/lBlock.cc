
#include "lBlock.h"
#include "../../cell.h"



LBlock::~LBlock() {}

LBlock::LBlock() : Block('L', Colour::Orange)
{
    for (int i = 0; i < 3; i++)
    {
        cells.emplace_back(std::make_shared<Cell>(
            initialY, initialX + i, this)
        );
    }
    
    cells.emplace_back(std::make_shared<Cell>(
        initialY - 1, initialX + 2)
    );
}
