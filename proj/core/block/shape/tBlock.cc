
#include "tBlock.h"
#include "../../cell.h"


TBlock::~TBlock() {}

TBlock::TBlock() : Block(Colour::Magenta)
{
    for (int i = 0; i < 3; i++)
    {
        cells.emplace_back(std::make_shared<Cell>(
            initialY - 1, initialX + i, this)
        );
    }
    
    cells.emplace_back(std::make_shared<Cell>(
        initialY, initialX + 1)
    );
}
