
#include "oBlock.h"
#include "../../cell.h"


OBlock::~OBlock() {}

OBlock::OBlock() : Block(Colour::Yellow)
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cells.emplace_back(std::make_shared<Cell>(
                initialY + i, initialX + j, this)
            );
        }
    }
    
    cells.emplace_back(std::make_shared<Cell>(
        initialY - 1, initialX)
    );
}
