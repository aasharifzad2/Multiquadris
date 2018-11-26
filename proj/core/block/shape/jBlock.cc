
#include "jBlock.h"
#include "../../cell.h"


JBlock::~JBlock() {}

JBlock::JBlock() : Block(Colour::Blue)
{
    for (int i = 0; i < 3; i++)
    {
        cells.emplace_back(std::make_shared<Cell>(
            initialY, initialX + i, this)
        );
    }
    
    cells.emplace_back(std::make_shared<Cell>(
        initialY - 1, initialX)
    );
}
